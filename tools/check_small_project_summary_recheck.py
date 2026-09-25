#!/usr/bin/env python3
"""Reject incomplete original-source summary experiments."""
import argparse
import csv
import glob
import sys
from pathlib import Path

EXPECTED = {"list_new", "list_rpush", "list_lpush", "ini_strncpy0"}


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("results_glob", help="Glob matching the current run's final_summary.csv files")
    args = parser.parse_args()
    files = [Path(p) for p in glob.glob(args.results_glob)]
    found = {}
    for path in files:
        with path.open(newline="", encoding="utf-8") as stream:
            for row in csv.DictReader(stream):
                if row.get("entry") in EXPECTED:
                    found[row["entry"]] = row
    failures = []
    for entry in sorted(EXPECTED):
        row = found.get(entry)
        if row is None:
            failures.append(f"{entry}: no result row")
        elif row.get("estimate_scope") != "original_slice" or not row.get("validated_worst_mems", "").isdigit():
            failures.append(
                f"{entry}: original summary unavailable "
                f"(slice={row.get('slice_mode')}, rc={row.get('returncode')}, "
                f"reason={row.get('reason') or 'see analyzer log'})"
            )
        else:
            print(f"{entry}: original worst_mems={row['validated_worst_mems']}")
    for failure in failures:
        print(failure, file=sys.stderr)
    return 1 if failures else 0


if __name__ == "__main__":
    raise SystemExit(main())
