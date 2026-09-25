#!/usr/bin/env python3
"""Measure MaxMEMS DP memo reuse and DP/DFS search time on the 20 witness subjects."""
from __future__ import annotations

import argparse
import csv
import json
import os
import re
import statistics
import subprocess
import sys
import tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from maxmems_witness_experiment import SUBJECTS, env_for

DP_MEM_RE = re.compile(r"(?m)^MEMS:\s*(-?\d+)")
DFS_MEM_RE = re.compile(r"(?m)^\[DFS MAX MEMS\]:\s*(-?\d+)")
DP_TIME_RE = re.compile(r"(?m)^\[DP TIME COST\]:\s*([0-9.eE+-]+)\s+seconds")
DFS_TIME_RE = re.compile(r"(?m)^\[DFS TIME COST\]:\s*([0-9.eE+-]+)\s+seconds")
INT_METRICS = {
    "memo_lookups": re.compile(r"(?m)^\[DP MEMO LOOKUPS\]:\s*(\d+)"),
    "memo_hits": re.compile(r"(?m)^\[DP MEMO HITS\]:\s*(\d+)"),
    "memo_misses": re.compile(r"(?m)^\[DP MEMO MISSES\]:\s*(\d+)"),
    "memo_stores": re.compile(r"(?m)^\[DP MEMO STORES\]:\s*(\d+)"),
    "memo_entries": re.compile(r"(?m)^\[DP MEMO ENTRIES\]:\s*(\d+)"),
}

def parse_one(rx: re.Pattern[str], text: str, label: str, cast):
    m = rx.search(text)
    if not m:
        raise RuntimeError(f"missing {label}")
    return cast(m.group(1))

def run_mode(cnip: Path, source: Path, maxloop: int, flag: str, timeout: int):
    env = env_for(cnip)
    env["EPPATHER_MAXMEMS_CORE_ONLY"] = "1"
    env["EPPATHER_PREFIX_FEASIBILITY"] = "0"
    proc = subprocess.run(
        [str(cnip), flag, "--maxloop", str(maxloop), "--maxpaths", "1000", str(source)],
        cwd=source.parent,
        text=True,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        env=env,
        timeout=timeout,
    )
    if proc.returncode:
        raise RuntimeError(f"{flag} exited {proc.returncode}: {proc.stdout[-1600:]}")
    return proc.stdout

def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--cnip", type=Path, default=Path("./cnip"))
    ap.add_argument("--output-dir", type=Path, default=Path("maxmems-performance-results"))
    ap.add_argument("--repetitions", type=int, default=3)
    ap.add_argument("--timeout", type=int, default=120)
    args = ap.parse_args()

    if args.repetitions < 1:
        raise SystemExit("--repetitions must be >= 1")

    cnip = args.cnip.resolve()
    out = args.output_dir.resolve()
    out.mkdir(parents=True, exist_ok=True)

    raw_rows = []
    suite_totals = []
    with tempfile.TemporaryDirectory(prefix="eppather-maxmems-perf-") as td:
        root = Path(td)
        subject_paths = {}
        for s in SUBJECTS:
            p = root / f"{s['id']}.c"
            p.write_text(s["source"] + "\n", encoding="utf-8")
            subject_paths[s["id"]] = p

        for rep in range(1, args.repetitions + 1):
            suite_dp = 0.0
            suite_dfs = 0.0
            for s in SUBJECTS:
                src = subject_paths[s["id"]]
                dp = run_mode(cnip, src, s["max_loop"], "-g", args.timeout)
                dfs = run_mode(cnip, src, s["max_loop"], "-q", args.timeout)
                dp_mem = parse_one(DP_MEM_RE, dp, "DP MEMS", int)
                dfs_mem = parse_one(DFS_MEM_RE, dfs, "DFS MEMS", int)
                dp_sec = parse_one(DP_TIME_RE, dp, "DP time", float)
                dfs_sec = parse_one(DFS_TIME_RE, dfs, "DFS time", float)
                row = {
                    "subject": s["id"],
                    "category": s["category"],
                    "rep": rep,
                    "maxloop": s["max_loop"],
                    "dp_mems": dp_mem,
                    "dfs_mems": dfs_mem,
                    "equal": int(dp_mem == dfs_mem),
                    "dp_seconds": dp_sec,
                    "dfs_seconds": dfs_sec,
                }
                for key, rx in INT_METRICS.items():
                    row[key] = parse_one(rx, dp, key, int)
                row["memo_hit_rate"] = (
                    row["memo_hits"] / row["memo_lookups"]
                    if row["memo_lookups"] else 0.0
                )
                raw_rows.append(row)
                suite_dp += dp_sec
                suite_dfs += dfs_sec
            suite_totals.append({
                "rep": rep,
                "dp_seconds": suite_dp,
                "dfs_seconds": suite_dfs,
                "dfs_over_dp": suite_dfs / suite_dp if suite_dp else None,
            })

    raw_fields = [
        "subject","category","rep","maxloop","dp_mems","dfs_mems","equal",
        "dp_seconds","dfs_seconds","memo_lookups","memo_hits","memo_misses",
        "memo_stores","memo_entries","memo_hit_rate",
    ]
    with (out / "raw.csv").open("w", newline="", encoding="utf-8") as fh:
        w = csv.DictWriter(fh, fieldnames=raw_fields)
        w.writeheader()
        w.writerows(raw_rows)

    subject_rows = []
    for s in SUBJECTS:
        rows = [r for r in raw_rows if r["subject"] == s["id"]]
        lookups = sum(r["memo_lookups"] for r in rows)
        hits = sum(r["memo_hits"] for r in rows)
        subject_rows.append({
            "subject": s["id"],
            "category": s["category"],
            "maxloop": s["max_loop"],
            "all_equal": int(all(r["equal"] for r in rows)),
            "median_dp_seconds": statistics.median(r["dp_seconds"] for r in rows),
            "median_dfs_seconds": statistics.median(r["dfs_seconds"] for r in rows),
            "dfs_over_dp": (
                statistics.median(r["dfs_seconds"] for r in rows) /
                statistics.median(r["dp_seconds"] for r in rows)
                if statistics.median(r["dp_seconds"] for r in rows) else None
            ),
            "memo_lookups": lookups,
            "memo_hits": hits,
            "memo_hit_rate": hits / lookups if lookups else 0.0,
        })
    with (out / "subjects.csv").open("w", newline="", encoding="utf-8") as fh:
        fields = list(subject_rows[0].keys())
        w = csv.DictWriter(fh, fieldnames=fields)
        w.writeheader()
        w.writerows(subject_rows)

    total_lookups = sum(r["memo_lookups"] for r in raw_rows)
    total_hits = sum(r["memo_hits"] for r in raw_rows)
    aggregate = {
        "subjects": len(SUBJECTS),
        "repetitions": args.repetitions,
        "all_dp_dfs_equal": all(r["equal"] for r in raw_rows),
        "memo_lookups": total_lookups,
        "memo_hits": total_hits,
        "memo_misses": sum(r["memo_misses"] for r in raw_rows),
        "memo_hit_rate": total_hits / total_lookups if total_lookups else 0.0,
        "median_suite_dp_seconds": statistics.median(r["dp_seconds"] for r in suite_totals),
        "median_suite_dfs_seconds": statistics.median(r["dfs_seconds"] for r in suite_totals),
        "median_suite_dfs_over_dp": statistics.median(r["dfs_over_dp"] for r in suite_totals),
        "suite_repetitions": suite_totals,
        "prefix_feasibility": "off",
        "maxpaths": 1000,
        "per_run_timeout_seconds": args.timeout,
    }
    (out / "summary.json").write_text(json.dumps(aggregate, indent=2) + "\n", encoding="utf-8")
    print("MAXMEMS_PERFORMANCE " + json.dumps(aggregate, sort_keys=True))
    if not aggregate["all_dp_dfs_equal"]:
        return 1
    return 0

if __name__ == "__main__":
    raise SystemExit(main())
