#!/usr/bin/env python3
"""Check DFS2 max-only oracle against ordinary DFS2 on controlled MaxMEMS subjects."""
from __future__ import annotations

import argparse
import csv
import json
import os
import re
import subprocess
import tempfile
from pathlib import Path

from maxmems_witness_experiment import SUBJECTS, MEM_RE

MAX_ONLY_RE = re.compile(
    r"(?m)^\[DFS MAX ONLY FUNCTION\]:\s*(\S+)\s*$"
    r"\n^\[DFS MAX ONLY MEMS\]:\s*(-?\d+)\s*$"
    r"\n^\[DFS MAX ONLY FEASIBLE PATHS\]:\s*(\d+)\s*$"
)

def env_for(cnip: Path) -> dict[str, str]:
    env = os.environ.copy()
    dirs = [cnip.parent, cnip.parent / "C", cnip.parent / "common",
            cnip.parent / "libParser/z3/bin", cnip.parent / "lpsolve"]
    env["LD_LIBRARY_PATH"] = ":".join(map(str, dirs)) + ":" + env.get("LD_LIBRARY_PATH", "")
    return env

def run(cmd: list[str], cwd: Path, env: dict[str, str], timeout: int = 120):
    return subprocess.run(cmd, cwd=cwd, env=env, text=True,
                          capture_output=True, timeout=timeout)

def ordinary_summary(work: Path, function: str) -> tuple[int, int]:
    mems: list[int] = []
    for rf in sorted(work.glob(f"result_{function}_*.txt")):
        txt = rf.read_text(encoding="utf-8", errors="replace")
        if not re.search(r"(?m)^feasible$", txt):
            continue
        mm = MEM_RE.search(txt)
        if mm:
            mems.append(int(mm.group(1)))
    return (max(mems) if mems else -1, len(mems))

def max_only_summary(stdout: str, function: str) -> tuple[int, int]:
    for m in MAX_ONLY_RE.finditer(stdout):
        if m.group(1) == function:
            return int(m.group(2)), int(m.group(3))
    raise RuntimeError(f"missing max-only summary for {function}")

def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--cnip", type=Path, required=True)
    ap.add_argument("--output-dir", type=Path,
                    default=Path("dfs-max-only-equivalence"))
    args = ap.parse_args()
    cnip = args.cnip.resolve()
    out = args.output_dir.resolve()
    out.mkdir(parents=True, exist_ok=True)
    rows = []

    with tempfile.TemporaryDirectory(prefix="eppather-dfs-max-only-") as td:
        root = Path(td)
        for subject in SUBJECTS:
            sid = subject["id"]
            function = subject["function"]
            src = out / f"{sid}.c"
            src.write_text(subject["source"] + "\n", encoding="utf-8")
            ordinary = root / f"{sid}-ordinary"
            fast = root / f"{sid}-maxonly"
            ordinary.mkdir()
            fast.mkdir()
            env = env_for(cnip)

            p1 = run([str(cnip), "-q", str(src),
                      str(subject["max_loop"]), "1000"], ordinary, env)
            if p1.returncode:
                rows.append({
                    "id": sid, "status": "ordinary_error",
                    "ordinary_max": "", "max_only_max": "",
                    "ordinary_paths": "", "max_only_paths": "",
                    "detail": (p1.stderr or p1.stdout)[-500:].replace("\n", " "),
                })
                continue

            ordinary_max, ordinary_paths = ordinary_summary(ordinary, function)
            fast_env = dict(env)
            fast_env["EPPATHER_DFS2_MAX_ONLY"] = "1"
            p2 = run([str(cnip), "-q", str(src),
                      str(subject["max_loop"]), "1000"], fast, fast_env)
            if p2.returncode:
                rows.append({
                    "id": sid, "status": "max_only_error",
                    "ordinary_max": ordinary_max, "max_only_max": "",
                    "ordinary_paths": ordinary_paths, "max_only_paths": "",
                    "detail": (p2.stderr or p2.stdout)[-500:].replace("\n", " "),
                })
                continue

            fast_max, fast_paths = max_only_summary(p2.stdout, function)
            ok = ordinary_max == fast_max and ordinary_paths == fast_paths
            rows.append({
                "id": sid,
                "status": "pass" if ok else "mismatch",
                "ordinary_max": ordinary_max,
                "max_only_max": fast_max,
                "ordinary_paths": ordinary_paths,
                "max_only_paths": fast_paths,
                "detail": "" if ok else "ordinary and max-only DFS2 differ",
            })
            print(
                f"{sid}: ordinary={ordinary_max}/{ordinary_paths} "
                f"max-only={fast_max}/{fast_paths} "
                f"{'PASS' if ok else 'MISMATCH'}",
                flush=True,
            )

    fields = ["id","status","ordinary_max","max_only_max",
              "ordinary_paths","max_only_paths","detail"]
    with (out / "summary.csv").open("w", newline="", encoding="utf-8") as fh:
        w = csv.DictWriter(fh, fieldnames=fields)
        w.writeheader()
        w.writerows(rows)
    passed = sum(r["status"] == "pass" for r in rows)
    summary = {
        "subjects": len(rows),
        "passed": passed,
        "failed": len(rows) - passed,
        "all_passed": len(rows) == len(SUBJECTS) and passed == len(SUBJECTS),
        "results": rows,
    }
    (out / "summary.json").write_text(json.dumps(summary, indent=2) + "\n",
                                      encoding="utf-8")
    print("DFS_MAX_ONLY_EQUIVALENCE " + json.dumps(
        {k: summary[k] for k in ("subjects","passed","failed","all_passed")},
        sort_keys=True))
    return 0 if summary["all_passed"] else 1

if __name__ == "__main__":
    raise SystemExit(main())
