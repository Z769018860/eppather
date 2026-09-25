#!/usr/bin/env python3
"""Audit whether MaxMemsDP reuses states; do not infer a speedup from this gate."""
import argparse
import csv
import os
import re
import subprocess
from pathlib import Path


CASES = [
    ("branch", "testcase/dp_maxmem_branch.c", 3),
    ("nested", "testcase/dp_maxmem_nested.c", 3),
    ("loop_array", "testcase/dp_maxmem_single.c", 4),
    ("fixed_cell", "testcase/loop_hybrid/27_spath_fixed_cell_memory.c", 4),
]


def metric(pattern: str, output: str) -> str:
    found = re.findall(r"^\[" + pattern + r"\]:\s*([^\r\n]+)", output, re.M)
    return found[-1].strip() if found else ""


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--root", type=Path, default=Path(__file__).resolve().parents[1])
    ap.add_argument("--cnip", type=Path, required=True)
    ap.add_argument("--output-dir", type=Path, required=True)
    args = ap.parse_args()
    root = args.root.resolve()
    out = args.output_dir.resolve()
    out.mkdir(parents=True, exist_ok=True)
    env = dict(os.environ, EPPATHER_MAXMEMS_CORE_ONLY="1",
               EPPATHER_LOOP_SCC_ACCELERATE="0",
               EPPATHER_LOOP_SCC_MEMORY_ACCELERATE="0")
    rows = []
    for name, relative, maxloop in CASES:
        source = root / relative
        outputs = {}
        for mode, flag in [("dfs2", "-q"), ("prefix_dp", "-g")]:
            run = subprocess.run([str(args.cnip.resolve()), flag,
                                  "--maxloop", str(maxloop), "--maxpaths", "0",
                                  str(source)], cwd=out, env=env, text=True,
                                 stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                                 timeout=90)
            (out / f"{name}.{mode}.log").write_text(run.stdout)
            outputs[mode] = run
        dfs = outputs["dfs2"].stdout
        dp = outputs["prefix_dp"].stdout
        lookups = metric("DP MEMO LOOKUPS", dp)
        hits = metric("DP MEMO HITS", dp)
        row = {
            "case": name, "source": relative, "maxloop": maxloop, "maxpaths": 0,
            "dfs_exit": outputs["dfs2"].returncode, "dp_exit": outputs["prefix_dp"].returncode,
            "dfs_mems": metric("DFS MAX MEMS", dfs), "dp_mems": metric("DP INTERNAL MEMS", dp),
            "memo_lookups": lookups, "memo_hits": hits,
            "memo_hit_rate": metric("DP MEMO HIT RATE", dp),
            "memo_stores": metric("DP MEMO STORES", dp),
            "memo_entries": metric("DP MEMO ENTRIES", dp),
            "leaf_solves": metric("DP LEAF SOLVES", dp),
            "dfs_seconds": metric("DFS TIME COST", dfs).split(" ")[0],
            "dp_seconds": metric("DP TIME COST", dp).split(" ")[0],
        }
        row["equal"] = (row["dfs_exit"] == row["dp_exit"] == 0
                        and row["dfs_mems"] == row["dp_mems"]
                        and row["dfs_mems"] not in ("", "-1")
                        and lookups.isdigit() and hits.isdigit())
        rows.append(row)
        print(row, flush=True)
    with (out / "memo_audit.csv").open("w", newline="") as f:
        writer = csv.DictWriter(f, fieldnames=list(rows[0]))
        writer.writeheader()
        writer.writerows(rows)
    return 0 if all(r["equal"] for r in rows) else 1


if __name__ == "__main__":
    raise SystemExit(main())
