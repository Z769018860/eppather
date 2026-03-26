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
CSV_FILE = ROOT / "function_summary_results.csv"

ARCHIVES = [
    TESTCASE_DIR / "lua-5.5.0.tar.gz",
    TESTCASE_DIR / "cJSON-master.zip",
    TESTCASE_DIR / "tinyexpr-master.zip",
]

PROJECTS = [
    {"name": "cJSON", "root": TESTCASE_DIR / "cJSON-master", "source_subdirs": ["."]},
    {"name": "tinyexpr", "root": TESTCASE_DIR / "tinyexpr-master", "source_subdirs": ["."]},
    {"name": "lua", "root": TESTCASE_DIR / "lua-5.5.0", "source_subdirs": ["src"]},
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


def run_cmd(cmd: list[str], timeout_sec: int = 12) -> tuple[bool, str]:
    try:
        proc = subprocess.run(
            cmd,
            cwd=ROOT,
            env=cnip_env(),
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
        return False, partial + "\n[timeout] cnip execution exceeded limit"


def mark_success(mode: str, ok: bool, text: str) -> bool:
    if ok:
        return True
    if mode == "summary":
        return ("[DFS MAX MEMS]:" in text or "[DFS TIME COST]:" in text or "Function " in text or "CATALOG" in text)
    return ("MEMS:" in text or "[MAX MEMS PATH]:" in text or "[DP TIME COST]:" in text)


def parse_worst_mems(text: str) -> str:
    m = re.search(r"MEMS:\s*(-?\d+)", text)
    if m:
        return m.group(1)
    m = re.search(r"\[DFS MAX MEMS\]:\s*(-?\d+)", text)
    return m.group(1) if m else ""


def parse_worst_path(text: str) -> str:
    block = re.search(r"\[MAX MEMS PATH\]:\n(.*?)\n\s*MEMS:", text, flags=re.S)
    if block:
        return " | ".join(line.strip() for line in block.group(1).splitlines() if line.strip())
    return ""


def has_error_text(text: str) -> bool:
    return any(token in text for token in ["Segmentation fault", "[timeout]", "file input error", "preprocessor invocation failed"])


def summary_supported() -> bool:
    ok, out = run_cmd(["./cnip", "-h"])
    return ok and ("dump-summary" in out or "--dump-summary" in out)


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


def safe_log_name(path: Path, project_root: Path) -> str:
    rel = path.relative_to(project_root).as_posix()
    return rel.replace("/", "__")


def main() -> None:
    extract_archives()
    REPORT_DIR.mkdir(parents=True, exist_ok=True)

    has_summary = summary_supported()
    rows: list[dict[str, object]] = []

    for project in PROJECTS:
        project_name = project["name"]
        project_root: Path = project["root"]
        project_report_dir = REPORT_DIR / project_name.lower()
        project_report_dir.mkdir(parents=True, exist_ok=True)

        c_files = collect_c_files(project_root, project.get("source_subdirs", ["."]))
        function_csv = project_report_dir / "functions.csv"

        function_rows: list[dict[str, str]] = []
        project_failures = 0

        for c_file in c_files:
            src = str(c_file)
            stem = safe_log_name(c_file, project_root)

            include_flags = ["--cpp-I", str(c_file.parent), "--cpp-I", str(project_root)]
            summary_cmd = (["./cnip", "-s", src] if has_summary else ["./cnip", "-q", src]) + include_flags
            worst_cmd = ["./cnip", "-g", src] + include_flags

            summary_ok_raw, summary_out = run_cmd(summary_cmd)
            worst_ok_raw, worst_out = run_cmd(worst_cmd)

            summary_ok = mark_success("summary", summary_ok_raw, summary_out)
            worst_ok = mark_success("worst", worst_ok_raw, worst_out)

            summary_log = project_report_dir / f"{stem}.summary.log"
            worst_log = project_report_dir / f"{stem}.worst.log"
            error_log = project_report_dir / f"{stem}.error.log"

            summary_log.write_text(summary_out, encoding="utf-8")
            worst_log.write_text(worst_out, encoding="utf-8")

            file_function_summaries = extract_function_summaries(c_file)
            for fsum in file_function_summaries:
                function_rows.append({"File": str(c_file.relative_to(project_root)), **fsum})

            errors = []
            if has_error_text(summary_out):
                errors.append("summary")
            if has_error_text(worst_out):
                errors.append("worst")
            if not summary_ok and not worst_ok:
                errors.append("analysis_not_ok")

            if errors:
                project_failures += 1
                error_log.write_text(
                    "\n".join(
                        [
                            f"project={project_name}",
                            f"file={c_file.relative_to(project_root)}",
                            f"error_stages={','.join(errors)}",
                            "---- summary ----",
                            summary_out,
                            "---- worst ----",
                            worst_out,
                        ]
                    ),
                    encoding="utf-8",
                )

            rows.append(
                {
                    "Project": project_name,
                    "File": str(c_file.relative_to(project_root)),
                    "SummaryCommand": " ".join(summary_cmd),
                    "SummaryOK": summary_ok,
                    "WorstPathCommand": " ".join(worst_cmd),
                    "WorstPathOK": worst_ok,
                    "WorstMems": parse_worst_mems(worst_out),
                    "WorstPath": parse_worst_path(worst_out),
                    "FunctionsAnalyzed": len(file_function_summaries),
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

        print(f"[{project_name}] files={len(c_files)}, fail_files={project_failures}, function_summary={function_csv}")

    with CSV_FILE.open("w", newline="", encoding="utf-8") as f:
        writer = csv.DictWriter(
            f,
            fieldnames=[
                "Project",
                "File",
                "SummaryCommand",
                "SummaryOK",
                "WorstPathCommand",
                "WorstPathOK",
                "WorstMems",
                "WorstPath",
                "FunctionsAnalyzed",
                "SummaryLog",
                "WorstPathLog",
                "ErrorLog",
                "Error",
            ],
        )
        writer.writeheader()
        writer.writerows(rows)

    print(f"Done. Results written to {CSV_FILE}")


if __name__ == "__main__":
    main()
