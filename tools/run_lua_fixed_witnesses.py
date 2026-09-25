#!/usr/bin/env python3
"""Check Eppather's fixed-input counts against the source witness CSV."""
import argparse
import csv
import re
import subprocess
from pathlib import Path


CASES = [(0, 1), (1, 1), (2, 3), (3, 3)]
CALLER_ARRAY_WRITES = 10


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--cnip", type=Path, required=True)
    ap.add_argument("--projection", type=Path, required=True)
    ap.add_argument("--witness-csv", type=Path, required=True)
    ap.add_argument("--output-dir", type=Path, required=True)
    args = ap.parse_args()
    args.output_dir.mkdir(parents=True, exist_ok=True)
    with args.witness_csv.open(newline="") as f:
        witnesses = {(int(r["available"]), int(r["requested"])): int(r["original_source_accesses"])
                     for r in csv.DictReader(f)}
    rows = []
    for available, requested in CASES:
        stem = f"lua_fixed_{available}_{requested}"
        cfile = args.output_dir / (stem + ".c")
        cmd = ["python3", str(Path(__file__).with_name("make_lua_fixed_witness.py")),
               "--projection", str(args.projection), "--available", str(available),
               "--requested", str(requested), "--output", str(cfile)]
        subprocess.run(cmd, check=True)
        run = subprocess.run([str(args.cnip), "-q", "--maxloop", "3", "--maxpaths", "20", str(cfile)],
                             text=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, timeout=90)
        (args.output_dir / (stem + ".log")).write_text(run.stdout)
        match = re.search(r"^\[DFS MAX MEMS\]:\s*(\d+)\s*$", run.stdout, re.M)
        expected = witnesses[(available, requested)]
        static = int(match.group(1)) - CALLER_ARRAY_WRITES if match else None
        rows.append({"available": available, "requested": requested,
                     "source_witness": expected, "eppather_total": int(match.group(1)) if match else "",
                     "caller_array_writes": CALLER_ARRAY_WRITES, "eppather_function": static,
                     "matched": static == expected and run.returncode == 0})
        print(rows[-1], flush=True)
    out_csv = args.output_dir / "fixed_witness_comparison.csv"
    with out_csv.open("w", newline="") as f:
        writer = csv.DictWriter(f, fieldnames=list(rows[0]))
        writer.writeheader()
        writer.writerows(rows)
    return 0 if all(r["matched"] for r in rows) else 1


if __name__ == "__main__":
    raise SystemExit(main())
