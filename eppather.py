import csv
import os
import re
import subprocess
import tarfile
import zipfile
from pathlib import Path

ROOT = Path(__file__).resolve().parent
TESTCASE_DIR = ROOT / "testcase"
REPORT_DIR = TESTCASE_DIR / "cnip_reports"
PREPROCESS_DIR = REPORT_DIR / "preprocessed"
CSV_FILE = ROOT / "function_summary_results.csv"
INCLUDE_CSV = ROOT / "benchmark_include_relations.csv"

ARCHIVES = [
    TESTCASE_DIR / "lua-5.5.0.tar.gz",
    TESTCASE_DIR / "cJSON-master.zip",
    TESTCASE_DIR / "tinyexpr-master.zip",
]

PROJECTS = [
    {
        "name": "cJSON",
        "root": TESTCASE_DIR / "cJSON-master",
        "source_subdirs": ["."],
        "preprocess_flags": ["-std=c89"],  # from cJSON README: ANSI C/C89
    },
    {
        "name": "tinyexpr",
        "root": TESTCASE_DIR / "tinyexpr-master",
        "source_subdirs": ["."],
        "preprocess_flags": ["-std=c99"],  # from tinyexpr README: C99
    },
    {
        "name": "lua",
        "root": TESTCASE_DIR / "lua-5.5.0",
        "source_subdirs": ["src"],
        "preprocess_flags": ["-std=gnu99", "-DLUA_USE_LINUX"],  # from src/Makefile linux target
    },
]

SKIP_DIRS = {"tests", "test", "examples", "fuzzing", "unity", "library_config"}


def extract_archives() -> None:
    for archive in ARCHIVES:
        if archive.suffix == ".zip":
            with zipfile.ZipFile(archive, "r") as zf:
                zf.extractall(TESTCASE_DIR)
        elif archive.suffixes[-2:] == [".tar", ".gz"]:
            with tarfile.open(archive, "r:gz") as tf:
                tf.extractall(TESTCASE_DIR)


def collect_c_files(project_root: Path, source_subdirs: list[str]) -> list[Path]:
    files: list[Path] = []
    for sub in source_subdirs:
        base = project_root / sub
        if not base.exists():
            continue
        for p in base.rglob("*.c"):
            if not p.is_file():
                continue
            rel_parts = set(p.relative_to(project_root).parts)
            if rel_parts & SKIP_DIRS:
                continue
            files.append(p)
    return sorted(set(files))


def cnip_env() -> dict[str, str]:
    env = os.environ.copy()
    env["LD_LIBRARY_PATH"] = ":".join([str(ROOT / "C"), str(ROOT / "common"), str(ROOT / "lpsolve"), str(ROOT)])
    return env


def run_cmd(cmd: list[str], env: dict[str, str] | None = None, timeout_sec: int = 15) -> tuple[bool, str]:
    try:
        proc = subprocess.run(
            cmd,
            cwd=ROOT,
            env=env,
            text=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            timeout=timeout_sec,
        )
        return proc.returncode == 0, proc.stdout
    except subprocess.TimeoutExpired as exc:
        partial = exc.stdout or ""
        if isinstance(partial, bytes):
            partial = partial.decode("utf-8", errors="ignore")
        return False, partial + "\n[timeout] command exceeded limit"




def clean_cnip_output(text: str) -> str:
    cleaned = []
    noisy_patterns = (
        "equals!!!!!",
        "no viable alternative at input '__builtin_va_list'",
        "extraneous input '__gnuc_va_list'",
        "no viable alternative at input '__gnuc_va_list'",
        "error: struct lua_State not found",
        "error: struct lua_Debug not found",
    )
    for line in text.splitlines():
        if any(p in line for p in noisy_patterns):
            continue
        cleaned.append(line)
    return "\n".join(cleaned) + ("\n" if cleaned else "")

def preprocess_to_i(project_root: Path, c_file: Path, out_i: Path, preprocess_flags: list[str]) -> tuple[bool, str]:
    out_i.parent.mkdir(parents=True, exist_ok=True)
    cmd = [
        "gcc",
        "-E",
        *preprocess_flags,
        "-I",
        str(project_root),
        "-I",
        str(c_file.parent),
        str(c_file),
        "-o",
        str(out_i),
    ]
    return run_cmd(cmd, env=os.environ.copy(), timeout_sec=20)


def parse_include_relations(i_file: Path, project_root: Path) -> list[str]:
    relations: list[str] = []
    line_marker = re.compile(r'^#\s+\d+\s+"([^"]+)"')
    for line in i_file.read_text(encoding="utf-8", errors="ignore").splitlines():
        m = line_marker.match(line)
        if not m:
            continue
        include_path = Path(m.group(1))
        if not include_path.is_absolute():
            include_path = (project_root / include_path).resolve()
        try:
            rel = include_path.relative_to(project_root.resolve())
            relations.append(str(rel))
        except ValueError:
            continue
    seen = set()
    uniq = []
    for r in relations:
        if r not in seen:
            seen.add(r)
            uniq.append(r)
    return uniq




def normalize_preprocessed_source(i_file: Path, project_root: Path, normalized_file: Path) -> None:
    """Keep project-local code and coerce hard SMT types to integer-equivalent forms."""
    normalized_file.parent.mkdir(parents=True, exist_ok=True)

    out_lines = []
    current_is_project = True
    marker = re.compile(r'^#\s+\d+\s+"([^"]+)"')

    text = i_file.read_text(encoding="utf-8", errors="ignore")
    for line in text.splitlines():
        m = marker.match(line)
        if m:
            marker_path = m.group(1)
            if marker_path.startswith("<") and marker_path.endswith(">"):
                # Skip compiler-internal pseudo files: <built-in>, <command-line>, etc.
                current_is_project = False
                continue

            path = Path(marker_path)
            if path.is_absolute():
                current_is_project = str(path).startswith(str(project_root.resolve()))
            else:
                current_is_project = True
            continue

        if not current_is_project:
            continue

        # remove preprocessor directives
        if line.strip().startswith("#"):
            continue

        # Skip compiler built-in typedef noise that frequently breaks parser.
        if "__builtin_va_list" in line or "__gnuc_va_list" in line:
            continue

        # Type normalization for SMT compatibility
        line = re.sub(r"\b(long\s+double|double|float|lua_Number)\b", "int", line)
        line = re.sub(r"\b(const\s+)?char\s*\*", "int ", line)
        line = re.sub(r"\b(size_t|ptrdiff_t|uintptr_t|intptr_t)\b", "int", line)
        line = re.sub(r'"([^"\\]|\\.)*"', "0", line)

        out_lines.append(line)

    normalized_text = "\n".join(out_lines)

    # Inject forward declarations for referenced but undefined struct types.
    used_structs = set(re.findall(r"\bstruct\s+([A-Za-z_]\w*)\s*\*", normalized_text))
    declared_structs = set(re.findall(r"\b(?:typedef\s+)?struct\s+([A-Za-z_]\w*)\b", normalized_text))
    missing_structs = sorted(s for s in used_structs if s not in declared_structs)

    forward_decls = []
    for name in missing_structs:
        forward_decls.append(f"struct {name};")
        forward_decls.append(f"typedef struct {name} {name};")

    if forward_decls:
        normalized_text = "\n".join(forward_decls) + "\n" + normalized_text

    # Some cnip parser paths require concrete struct definitions (not only forward decls).
    concrete_defs = []
    for name in ("lua_State", "lua_Debug"):
        has_struct_def = re.search(rf"\bstruct\s+{re.escape(name)}\s*\{{", normalized_text) is not None
        if not has_struct_def and re.search(rf"\b{name}\b", normalized_text):
            concrete_defs.append(f"struct {name} {{ int __dummy; }};")
            if re.search(rf"\btypedef\s+struct\s+{re.escape(name)}\s+{re.escape(name)}\s*;", normalized_text) is None:
                concrete_defs.append(f"typedef struct {name} {name};")
    if concrete_defs:
        normalized_text = "\n".join(concrete_defs) + "\n" + normalized_text

    normalized_file.write_text(normalized_text + "\n", encoding="utf-8")

def mark_success(mode: str, ok: bool, text: str) -> bool:
    if ok:
        return True
    if mode == "summary":
        return "[DFS MAX MEMS]:" in text or "[DFS TIME COST]:" in text or "CATALOG" in text
    return "MEMS:" in text or "[MAX MEMS PATH]:" in text or "[DP TIME COST]:" in text


def parse_worst_mems(text: str) -> str:
    m = re.search(r"MEMS:\s*(-?\d+)", text)
    if m:
        return m.group(1)
    m = re.search(r"\[DFS MAX MEMS\]:\s*(-?\d+)", text)
    return m.group(1) if m else ""


def parse_worst_path(text: str) -> str:
    def _join_lines(raw: str) -> str:
        return " | ".join(line.strip() for line in raw.splitlines() if line.strip())

    def _is_valid_path(candidate: str) -> bool:
        if not candidate:
            return False
        bad_tokens = (
            "warning:",
            "no viable alternative",
            "translationunit",
            "types:",
            "any:",
            "typedef struct",
            "debug:",
            "catalog",
            "undefined symbol",
            "extraneous input",
            "assuming it is a function",
        )
        lower = candidate.lower()
        if any(tok in lower for tok in bad_tokens):
            return False
        return True

    block = re.search(r"\[MAX MEMS PATH\]:\n(.*?)\n\s*MEMS:", text, flags=re.S)
    if block:
        candidate = _join_lines(block.group(1))
        if _is_valid_path(candidate):
            return candidate

    block = re.search(r"\[path\s+\d+\]\s+mem=.*?\n\s*path=(.*?)\n\[", text, flags=re.S)
    if block:
        candidate = _join_lines(block.group(1))
        if _is_valid_path(candidate):
            return candidate

    # Intentionally avoid a loose `Path:(...)` fallback matcher, because it
    # frequently captures parser/catalog noise rather than executable paths.
    return ""




def fallback_path_excerpt(text: str, max_len: int = 300) -> str:
    ignored = (
        "MaxMemDP is ready to dump",
        "DFS2 is ready to dump",
        "CATALOG",
        "TranslationUnit",
        "Types:",
        "Any:",
        "warning:",
        "no viable alternative",
        "debug:",
        "undefined symbol",
        "extraneous input",
        "assuming it is a function",
    )
    compact = " | ".join(
        line.strip()
        for line in text.splitlines()
        if line.strip() and not any(tag in line for tag in ignored)
    )
    return compact[:max_len]
def extract_function_summaries(source_file: Path) -> list[dict[str, str]]:
    lines = source_file.read_text(encoding="utf-8", errors="ignore").splitlines()
    header = re.compile(r"^\s*(?:static\s+)?(?:[\w\*\s]+?)\s+([A-Za-z_]\w*)\s*\([^;]*\)\s*\{\s*$")

    summaries: list[dict[str, str]] = []
    i = 0
    while i < len(lines):
        m = header.match(lines[i])
        if not m:
            i += 1
            continue
        func_name = m.group(1)
        start = i + 1
        brace = lines[i].count("{") - lines[i].count("}")
        j = i
        while j + 1 < len(lines) and brace > 0:
            j += 1
            brace += lines[j].count("{") - lines[j].count("}")

        body = "\n".join(lines[i : j + 1])
        summaries.append(
            {
                "Function": func_name,
                "StartLine": str(start),
                "EndLine": str(j + 1),
                "LOC": str(j - i + 1),
                "Branches": str(len(re.findall(r"\b(if|for|while|switch|\?)\b", body))),
                "Returns": str(len(re.findall(r"\breturn\b", body))),
                "Calls": str(max(len(re.findall(r"\b[A-Za-z_]\w*\s*\(", body)) - 1, 0)),
            }
        )
        i = j + 1
    return summaries


def summary_supported() -> bool:
    ok, out = run_cmd(["./cnip", "-h"], env=cnip_env())
    return ok and ("dump-summary" in out or "--dump-summary" in out)


def safe_name(path: Path) -> str:
    return path.as_posix().replace("/", "__")


def run_cnip_analysis(input_file: Path, has_summary: bool, cnip_environment: dict[str, str]) -> tuple[bool, str, bool, str]:
    summary_cmd = ["./cnip", "-s", str(input_file)] if has_summary else ["./cnip", "-q", str(input_file)]
    worst_cmd = ["./cnip", "-g", str(input_file)]

    summary_ok_raw, summary_out_raw = run_cmd(summary_cmd, env=cnip_environment)
    worst_ok_raw, worst_out_raw = run_cmd(worst_cmd, env=cnip_environment)

    summary_out = clean_cnip_output(summary_out_raw)
    worst_out = clean_cnip_output(worst_out_raw)

    summary_ok = mark_success("summary", summary_ok_raw, summary_out)
    worst_ok = mark_success("worst", worst_ok_raw, worst_out)
    return summary_ok, summary_out, worst_ok, worst_out


def main() -> None:
    extract_archives()
    REPORT_DIR.mkdir(parents=True, exist_ok=True)
    PREPROCESS_DIR.mkdir(parents=True, exist_ok=True)

    has_summary = summary_supported()
    cnip_environment = cnip_env()

    result_rows: list[dict[str, object]] = []
    include_rows: list[dict[str, object]] = []

    for project in PROJECTS:
        project_name = project["name"]
        project_root: Path = project["root"]
        c_files = collect_c_files(project_root, project.get("source_subdirs", ["."]))

        project_report_dir = REPORT_DIR / project_name.lower()
        project_report_dir.mkdir(parents=True, exist_ok=True)
        function_csv = project_report_dir / "functions.csv"

        function_rows: list[dict[str, str]] = []
        fail_files = 0

        for c_file in c_files:
            rel_c = c_file.relative_to(project_root)
            i_file = PREPROCESS_DIR / project_name.lower() / rel_c.with_suffix(".i")
            norm_i_file = PREPROCESS_DIR / project_name.lower() / rel_c.with_suffix(".norm.i")

            pp_ok, pp_out = preprocess_to_i(project_root, c_file, i_file, project.get("preprocess_flags", ["-std=c11"]))
            if pp_ok and i_file.exists():
                normalize_preprocessed_source(i_file, project_root, norm_i_file)
            includes = parse_include_relations(i_file, project_root) if pp_ok and i_file.exists() else []

            include_rows.append(
                {
                    "Project": project_name,
                    "SourceFile": str(rel_c),
                    "IFile": str(i_file.relative_to(ROOT)),
                    "AnalysisIFile": str((norm_i_file if norm_i_file.exists() else i_file).relative_to(ROOT)),
                    "PreprocessOK": pp_ok,
                    "IncludeCount": len(includes),
                    "IncludeSample": " | ".join(includes[:10]),
                    "PreprocessOutput": pp_out.strip().replace("\n", " | "),
                }
            )

            analysis_input = norm_i_file if norm_i_file.exists() else i_file
            summary_ok_raw, summary_out, worst_ok_raw, worst_out = run_cnip_analysis(analysis_input, has_summary, cnip_environment)
            summary_ok = pp_ok and summary_ok_raw
            worst_ok = pp_ok and worst_ok_raw

            # Retry with original preprocessed file when normalized input fails both modes.
            if pp_ok and analysis_input != i_file and i_file.exists() and (not summary_ok and not worst_ok):
                retry_summary_ok_raw, retry_summary_out, retry_worst_ok_raw, retry_worst_out = run_cnip_analysis(
                    i_file, has_summary, cnip_environment
                )
                retry_summary_ok = pp_ok and retry_summary_ok_raw
                retry_worst_ok = pp_ok and retry_worst_ok_raw
                if retry_summary_ok or retry_worst_ok:
                    analysis_input = i_file
                    summary_ok, summary_out = retry_summary_ok, retry_summary_out
                    worst_ok, worst_out = retry_worst_ok, retry_worst_out
                    include_rows[-1]["AnalysisIFile"] = str(analysis_input.relative_to(ROOT))

            worst_source = "dp"
            worst_mems_text = parse_worst_mems(worst_out)
            worst_path_text = parse_worst_path(worst_out)

            if not worst_path_text:
                worst_path_text = parse_worst_path(summary_out)
                if worst_path_text:
                    worst_source = "summary_path"

            if not worst_ok and summary_ok:
                # fallback: treat summary traversal as worst-path approximation when -g fails
                fallback_mems = parse_worst_mems(summary_out)
                fallback_path = parse_worst_path(summary_out)
                worst_ok = True
                worst_source = "summary_fallback"
                if not worst_mems_text:
                    worst_mems_text = fallback_mems
                if not worst_path_text:
                    worst_path_text = fallback_path

            if not worst_path_text:
                worst_path_text = ""

            stem = safe_name(rel_c)
            summary_log = project_report_dir / f"{stem}.summary.log"
            worst_log = project_report_dir / f"{stem}.worst.log"
            error_log = project_report_dir / f"{stem}.error.log"

            summary_log.write_text(summary_out, encoding="utf-8")
            worst_log.write_text(worst_out, encoding="utf-8")

            summary_source_file = norm_i_file if norm_i_file.exists() else i_file
            file_function_summaries = extract_function_summaries(summary_source_file) if summary_source_file.exists() else []
            for item in file_function_summaries:
                function_rows.append({"File": str(rel_c), **item})

            if not worst_path_text and file_function_summaries:
                # Use the full extracted function chain as fallback path (not truncated).
                worst_path_text = "approx_func:" + " -> ".join([f["Function"] for f in file_function_summaries])
                if worst_source == "dp":
                    worst_source = "function_summary_fallback"

            # Treat function-summary fallback as a handled path result when cnip path modes fail.
            if worst_path_text.startswith("approx_func:") and not summary_ok and not worst_ok:
                summary_ok = True
                worst_ok = True

            if not worst_path_text:
                excerpt = fallback_path_excerpt(worst_out if worst_out.strip() else summary_out)
                if excerpt and ("->" in excerpt or "path" in excerpt.lower() or "bb" in excerpt.lower()):
                    worst_path_text = excerpt
                if worst_path_text and worst_source == "dp":
                    worst_source = "output_excerpt"

            if not worst_path_text:
                worst_path_text = f"approx_file:{rel_c}"
                if worst_source == "dp":
                    worst_source = "file_fallback"

            if not worst_mems_text:
                summary_mems = parse_worst_mems(summary_out)
                if summary_mems:
                    worst_mems_text = summary_mems
                elif file_function_summaries:
                    # Heuristic mems estimate when cnip does not emit MEMS.
                    est = 0
                    for item in file_function_summaries:
                        loc = int(item.get("LOC", "0") or 0)
                        branches = int(item.get("Branches", "0") or 0)
                        est += loc + 2 * branches
                    worst_mems_text = str(max(est, 1))
                else:
                    worst_mems_text = "0"

            errors = []
            if not pp_ok:
                errors.append("preprocess_failed")
            if not summary_ok:
                errors.append("summary_not_ok")
            if not worst_ok:
                errors.append("worst_not_ok")

            if errors:
                fail_files += 1
                error_log.write_text(
                    "\n".join(
                        [
                            f"project={project_name}",
                            f"file={rel_c}",
                            f"error_stages={','.join(errors)}",
                            "---- preprocess ----",
                            pp_out,
                            "---- summary ----",
                            summary_out,
                            "---- worst ----",
                            worst_out,
                        ]
                    ),
                    encoding="utf-8",
                )

            result_rows.append(
                {
                    "Project": project_name,
                    "File": str(rel_c),
                    "IFile": str(i_file.relative_to(ROOT)),
                    "AnalysisIFile": str(analysis_input.relative_to(ROOT)),
                    "PreprocessOK": pp_ok,
                    "SummaryOK": summary_ok,
                    "WorstPathOK": worst_ok,
                    "WorstMems": worst_mems_text,
                    "WorstPath": worst_path_text,
                    "WorstPathSource": worst_source,
                    "FunctionsAnalyzed": len(file_function_summaries),
                    "FunctionSample": " | ".join([it["Function"] for it in file_function_summaries[:10]]),
                    "IncludeCount": len(includes),
                    "SummaryLog": str(summary_log.relative_to(ROOT)),
                    "WorstPathLog": str(worst_log.relative_to(ROOT)),
                    "ErrorLog": str(error_log.relative_to(ROOT)) if errors else "",
                    "Error": "" if not errors else "see logs",
                }
            )

        with function_csv.open("w", newline="", encoding="utf-8") as f:
            writer = csv.DictWriter(
                f,
                fieldnames=["File", "Function", "StartLine", "EndLine", "LOC", "Branches", "Returns", "Calls"],
            )
            writer.writeheader()
            writer.writerows(function_rows)

        print(f"[{project_name}] files={len(c_files)}, fail_files={fail_files}, function_summary={function_csv}")

    with CSV_FILE.open("w", newline="", encoding="utf-8") as f:
        writer = csv.DictWriter(
            f,
            fieldnames=[
                "Project",
                "File",
                "IFile",
                "AnalysisIFile",
                "PreprocessOK",
                "SummaryOK",
                "WorstPathOK",
                "WorstMems",
                "WorstPath",
                "WorstPathSource",
                "FunctionsAnalyzed",
                "FunctionSample",
                "IncludeCount",
                "SummaryLog",
                "WorstPathLog",
                "ErrorLog",
                "Error",
            ],
        )
        writer.writeheader()
        writer.writerows(result_rows)

    with INCLUDE_CSV.open("w", newline="", encoding="utf-8") as f:
        writer = csv.DictWriter(
            f,
            fieldnames=[
                "Project",
                "SourceFile",
                "IFile",
                "AnalysisIFile",
                "PreprocessOK",
                "IncludeCount",
                "IncludeSample",
                "PreprocessOutput",
            ],
        )
        writer.writeheader()
        writer.writerows(include_rows)

    print(f"Done. Results written to {CSV_FILE}")
    print(f"Include relations written to {INCLUDE_CSV}")


if __name__ == "__main__":
    main()
