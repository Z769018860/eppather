#!/usr/bin/env python3
"""Run concrete path validation for a manifest of normalized C functions."""
from __future__ import annotations

import argparse
import concurrent.futures
import json
import subprocess
import sys
from pathlib import Path


def validate(item: dict[str, str], root: Path, cnip: Path, output: Path,
             max_loop: int) -> dict:
    source = (root / item["source"]).resolve()
    function = item["function"]
    report = output / f"{source.stem}__{function}.json"
    cmd = [sys.executable, str(root / "tools/e2e_path_validation.py"),
           str(source), "--function", function, "--cnip", str(cnip),
           "--max-loop", str(max_loop), "--output", str(report)]
    run = subprocess.run(cmd, cwd=root, text=True, capture_output=True, timeout=300)
    result = {"source": item["source"], "function": function,
              "returncode": run.returncode}
    if report.exists():
        result.update(json.loads(report.read_text(encoding="utf-8"))["summary"])
    else:
        result.update({"match": 0, "mismatch": 0, "undefined": 0, "error": 1,
                       "total": 0})
        result["detail"] = (run.stderr or run.stdout)[-1000:]
    return result


def main() -> int:
    root = Path(__file__).resolve().parents[1]
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--manifest", type=Path,
                    default=root / "tools/e2e_batch_manifest.json")
    ap.add_argument("--cnip", type=Path, default=root / "cnip")
    ap.add_argument("--max-loop", type=int, default=3)
    ap.add_argument("--jobs", type=int, default=2)
    ap.add_argument("--output-dir", type=Path,
                    default=root / "e2e-batch-reports")
    args = ap.parse_args()
    if args.max_loop < 0 or args.jobs < 1:
        ap.error("--max-loop must be non-negative and --jobs must be positive")
    items = json.loads(args.manifest.read_text(encoding="utf-8"))
    args.output_dir.mkdir(parents=True, exist_ok=True)
    with concurrent.futures.ThreadPoolExecutor(max_workers=args.jobs) as pool:
        futures = [pool.submit(validate, x, root, args.cnip.resolve(),
                               args.output_dir.resolve(), args.max_loop) for x in items]
        rows = [future.result() for future in futures]
    keys = ("match", "mismatch", "undefined", "error", "total")
    totals = {key: sum(row[key] for row in rows) for key in keys}
    aggregate = {"max_loop": args.max_loop, "programs": len(rows),
                 "summary": totals, "results": rows}
    aggregate_path = args.output_dir / "summary.json"
    aggregate_path.write_text(json.dumps(aggregate, ensure_ascii=False, indent=2) + "\n",
                              encoding="utf-8")
    for row in rows:
        print(f"{row['source']}::{row['function']} "
              f"match={row['match']} mismatch={row['mismatch']} "
              f"undefined={row['undefined']} error={row['error']}")
    print(json.dumps(totals, ensure_ascii=False))
    return 0 if rows and totals["mismatch"] == 0 and totals["error"] == 0 else 1


if __name__ == "__main__":
    sys.exit(main())
