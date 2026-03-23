import csv
import glob
import os
import re
import shlex
import subprocess
import tarfile
import zipfile
from pathlib import Path

ROOT = Path(__file__).resolve().parent
TESTCASE_DIR = ROOT / "testcase"
BENCH_BIN_DIR = TESTCASE_DIR / "benchmark_bin"
SUMMARY_DIR = TESTCASE_DIR / "function_summary"
DRIVER_DIR = TESTCASE_DIR / "benchmark_drivers"
CSV_FILE = ROOT / "function_summary_results.csv"

ARCHIVES = [
    TESTCASE_DIR / "lua-5.5.0.tar.gz",
    TESTCASE_DIR / "cJSON-master.zip",
    TESTCASE_DIR / "tinyexpr-master.zip",
]

DRIVERS = {
    "cJSON": DRIVER_DIR / "cjson_driver.c",
    "tinyexpr": DRIVER_DIR / "tinyexpr_driver.c",
    "lua": DRIVER_DIR / "lua_driver.c",
}


def extract_archives() -> None:
    for archive in ARCHIVES:
        if archive.suffix == ".zip":
            with zipfile.ZipFile(archive, "r") as zf:
                zf.extractall(TESTCASE_DIR)
        elif archive.suffixes[-2:] == [".tar", ".gz"]:
            with tarfile.open(archive, "r:gz") as tf:
                tf.extractall(TESTCASE_DIR)


def write_project_drivers() -> None:
    (TESTCASE_DIR / "cJSON-master" / "eppather_benchmark.c").write_text(
        DRIVERS["cJSON"].read_text(encoding="utf-8"), encoding="utf-8"
    )
    (TESTCASE_DIR / "tinyexpr-master" / "eppather_benchmark.c").write_text(
        DRIVERS["tinyexpr"].read_text(encoding="utf-8"), encoding="utf-8"
    )
    (TESTCASE_DIR / "lua-5.5.0" / "src" / "eppather_benchmark.c").write_text(
        DRIVERS["lua"].read_text(encoding="utf-8"), encoding="utf-8"
    )


def strip_comments(code: str) -> str:
    code = re.sub(r"//.*", "", code)
    return re.sub(r"/\*.*?\*/", "", code, flags=re.S)


def function_summary(source_file: Path) -> list[str]:
    code = strip_comments(source_file.read_text(encoding="utf-8", errors="ignore"))
    pattern = re.compile(
        r"(?m)^\s*(?:[A-Za-z_][\w\s\*\(\)]*?)\s+([A-Za-z_]\w*)\s*\([^;{}]*\)\s*\{"
    )
    names = []
    for name in pattern.findall(code):
        if name not in {"if", "for", "while", "switch"}:
            names.append(name)
    seen = set()
    ordered = []
    for name in names:
        if name not in seen:
            seen.add(name)
            ordered.append(name)
    return ordered


def run_cmd(cmd: list[str]) -> tuple[bool, str]:
    proc = subprocess.run(cmd, cwd=ROOT, text=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    return proc.returncode == 0, proc.stdout


def compile_and_run(compile_cmd: list[str], binary: Path) -> tuple[bool, bool, str]:
    ok_compile, compile_out = run_cmd(compile_cmd)
    if not ok_compile:
        return False, False, compile_out

    ok_run, run_out = run_cmd([str(binary)])
    return True, ok_run, run_out


def main() -> None:
    extract_archives()
    write_project_drivers()
    BENCH_BIN_DIR.mkdir(parents=True, exist_ok=True)
    SUMMARY_DIR.mkdir(parents=True, exist_ok=True)

    lua_src = TESTCASE_DIR / "lua-5.5.0" / "src"
    lua_c_files = [
        f
        for f in glob.glob(str(lua_src / "*.c"))
        if os.path.basename(f) not in {"lua.c", "luac.c", "eppather_benchmark.c"}
    ]

    benchmarks = [
        {
            "name": "cJSON",
            "source": TESTCASE_DIR / "cJSON-master" / "cJSON.c",
            "compile_cmd": [
                "gcc", "-std=c11",
                str(TESTCASE_DIR / "cJSON-master" / "cJSON.c"),
                str(TESTCASE_DIR / "cJSON-master" / "eppather_benchmark.c"),
                "-I", str(TESTCASE_DIR / "cJSON-master"),
                "-o", str(BENCH_BIN_DIR / "cjson_bench"),
            ],
            "binary": BENCH_BIN_DIR / "cjson_bench",
        },
        {
            "name": "tinyexpr",
            "source": TESTCASE_DIR / "tinyexpr-master" / "tinyexpr.c",
            "compile_cmd": [
                "gcc", "-std=c11",
                str(TESTCASE_DIR / "tinyexpr-master" / "tinyexpr.c"),
                str(TESTCASE_DIR / "tinyexpr-master" / "eppather_benchmark.c"),
                "-I", str(TESTCASE_DIR / "tinyexpr-master"),
                "-lm",
                "-o", str(BENCH_BIN_DIR / "tinyexpr_bench"),
            ],
            "binary": BENCH_BIN_DIR / "tinyexpr_bench",
        },
        {
            "name": "lua",
            "source": lua_src / "lapi.c",
            "compile_cmd": [
                "gcc", "-std=c11", *lua_c_files,
                str(lua_src / "eppather_benchmark.c"),
                "-I", str(lua_src),
                "-lm", "-ldl",
                "-o", str(BENCH_BIN_DIR / "lua_bench"),
            ],
            "binary": BENCH_BIN_DIR / "lua_bench",
        },
    ]

    rows = []
    for item in benchmarks:
        compiled, ran, output = compile_and_run(item["compile_cmd"], item["binary"])
        funcs = function_summary(item["source"])
        summary_path = SUMMARY_DIR / f"{item['name'].lower()}_summary.txt"
        summary_path.write_text("\n".join(funcs) + "\n", encoding="utf-8")
        rows.append(
            {
                "Project": item["name"],
                "CompileOK": compiled,
                "RunOK": ran,
                "FunctionCount": len(funcs),
                "FunctionSample": ", ".join(funcs[:10]),
                "RunOutput": output.strip().replace("\n", " | "),
                "CompileCommand": shlex.join(item["compile_cmd"]),
                "SummaryFile": str(summary_path.relative_to(ROOT)),
            }
        )

    with CSV_FILE.open("w", newline="", encoding="utf-8") as f:
        writer = csv.DictWriter(
            f,
            fieldnames=[
                "Project",
                "CompileOK",
                "RunOK",
                "FunctionCount",
                "FunctionSample",
                "RunOutput",
                "CompileCommand",
                "SummaryFile",
            ],
        )
        writer.writeheader()
        writer.writerows(rows)

    print(f"Done. Results written to {CSV_FILE}")


if __name__ == "__main__":
    main()
