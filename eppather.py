import csv
import os
import re
import subprocess
import tarfile
import zipfile
from pathlib import Path

ROOT = Path(__file__).resolve().parent
TESTCASE_DIR = ROOT / "testcase"
DRIVER_DIR = TESTCASE_DIR / "benchmark_drivers"
REPORT_DIR = TESTCASE_DIR / "cnip_reports"
CSV_FILE = ROOT / "function_summary_results.csv"

ARCHIVES = [
    TESTCASE_DIR / "lua-5.5.0.tar.gz",
    TESTCASE_DIR / "cJSON-master.zip",
    TESTCASE_DIR / "tinyexpr-master.zip",
]

BENCHMARKS = [
    {
        "name": "cJSON",
        "driver_src": DRIVER_DIR / "cjson_driver.c",
        "driver_dst": TESTCASE_DIR / "cJSON-master" / "eppather_benchmark.c",
    },
    {
        "name": "tinyexpr",
        "driver_src": DRIVER_DIR / "tinyexpr_driver.c",
        "driver_dst": TESTCASE_DIR / "tinyexpr-master" / "eppather_benchmark.c",
    },
    {
        "name": "lua",
        "driver_src": DRIVER_DIR / "lua_driver.c",
        "driver_dst": TESTCASE_DIR / "lua-5.5.0" / "src" / "eppather_benchmark.c",
    },
]


def extract_archives() -> None:
    for archive in ARCHIVES:
        if archive.suffix == ".zip":
            with zipfile.ZipFile(archive, "r") as zf:
                zf.extractall(TESTCASE_DIR)
        elif archive.suffixes[-2:] == [".tar", ".gz"]:
            with tarfile.open(archive, "r:gz") as tf:
                tf.extractall(TESTCASE_DIR)


def write_project_drivers() -> None:
    for item in BENCHMARKS:
        item["driver_dst"].write_text(item["driver_src"].read_text(encoding="utf-8"), encoding="utf-8")


def cnip_env() -> dict[str, str]:
    env = os.environ.copy()
    env["LD_LIBRARY_PATH"] = ":".join([str(ROOT / "C"), str(ROOT / "common"), str(ROOT / "lpsolve"), str(ROOT)])
    return env


def run_cmd(cmd: list[str], timeout_sec: int = 20) -> tuple[bool, str]:
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
        return "[DFS MAX MEMS]:" in text or "[DFS TIME COST]:" in text or "Function " in text
    return "MEMS:" in text or "[MAX MEMS PATH]:" in text


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

    # fallback: show first feasible path in DFS output
    block = re.search(r"\[path\s+\d+\]\s+mem=.*?\n\s*path=(.*?)\n\[", text, flags=re.S)
    if block:
        return " | ".join(line.strip() for line in block.group(1).splitlines() if line.strip())
    return ""


def has_error_text(text: str) -> bool:
    return any(token in text for token in ["Error:", "Segmentation fault", "[timeout]", "file input error"])


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
                "Calls": str(len(re.findall(r"\b[A-Za-z_]\w*\s*\(", body)) - 1),
            }
        )
        i = j + 1
    return summaries


def write_function_summary_csv(path: Path, function_summaries: list[dict[str, str]]) -> None:
    with path.open("w", newline="", encoding="utf-8") as f:
        writer = csv.DictWriter(f, fieldnames=["Function", "StartLine", "EndLine", "LOC", "Branches", "Returns", "Calls"])
        writer.writeheader()
        writer.writerows(function_summaries)


def main() -> None:
    extract_archives()
    write_project_drivers()
    REPORT_DIR.mkdir(parents=True, exist_ok=True)

    has_summary = summary_supported()

    rows = []
    for item in BENCHMARKS:
        src = str(item["driver_dst"])
        project_tag = item["name"].lower()

        summary_cmd = ["./cnip", "-s", src] if has_summary else ["./cnip", "-q", src]
        worst_cmd = ["./cnip", "-g", src]

        summary_ok_raw, summary_out = run_cmd(summary_cmd)
        worst_ok_raw, worst_out = run_cmd(worst_cmd)

        summary_ok = mark_success("summary", summary_ok_raw, summary_out)
        worst_ok = mark_success("worst", worst_ok_raw, worst_out)

        summary_log = REPORT_DIR / f"{project_tag}_summary.log"
        worst_log = REPORT_DIR / f"{project_tag}_worst.log"
        error_log = REPORT_DIR / f"{project_tag}_error.log"
        function_csv = REPORT_DIR / f"{project_tag}_functions.csv"

        summary_log.write_text(summary_out, encoding="utf-8")
        worst_log.write_text(worst_out, encoding="utf-8")

        func_summaries = extract_function_summaries(item["driver_dst"])
        write_function_summary_csv(function_csv, func_summaries)

        errors = []
        if has_error_text(summary_out):
            errors.append("summary")
        if has_error_text(worst_out):
            errors.append("worst")
        if not summary_ok:
            errors.append("summary_not_ok")
        if not worst_ok:
            errors.append("worst_not_ok")

        if errors:
            error_log.write_text(
                "\n".join(
                    [
                        f"project={item['name']}",
                        f"error_stages={','.join(errors)}",
                        "---- summary ----",
                        summary_out,
                        "---- worst ----",
                        worst_out,
                    ]
                ),
                encoding="utf-8",
            )

        worst_mems = parse_worst_mems(worst_out)
        worst_path = parse_worst_path(worst_out)

        print(f"[{item['name']}] worst_mems={worst_mems or 'N/A'}")
        print(f"[{item['name']}] worst_path={worst_path or 'N/A'}")

        rows.append(
            {
                "Project": item["name"],
                "SummaryCommand": " ".join(summary_cmd),
                "SummaryOK": summary_ok,
                "WorstPathCommand": " ".join(worst_cmd),
                "WorstPathOK": worst_ok,
                "WorstMems": worst_mems,
                "WorstPath": worst_path,
                "FunctionsAnalyzed": len(func_summaries),
                "FunctionSummaryCSV": str(function_csv.relative_to(ROOT)),
                "SummaryLog": str(summary_log.relative_to(ROOT)),
                "WorstPathLog": str(worst_log.relative_to(ROOT)),
                "ErrorLog": str(error_log.relative_to(ROOT)) if errors else "",
                "Error": "" if (summary_ok and worst_ok and not errors) else "see logs",
            }
        )

    with CSV_FILE.open("w", newline="", encoding="utf-8") as f:
        writer = csv.DictWriter(
            f,
            fieldnames=[
                "Project",
                "SummaryCommand",
                "SummaryOK",
                "WorstPathCommand",
                "WorstPathOK",
                "WorstMems",
                "WorstPath",
                "FunctionsAnalyzed",
                "FunctionSummaryCSV",
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
