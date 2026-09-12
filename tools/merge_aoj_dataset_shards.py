#!/usr/bin/env python3
"""Merge verified AOJ shards and emit reproducible experiment data."""
from __future__ import annotations
import argparse, csv, json, shutil
from collections import Counter
from pathlib import Path

def valid(metadata: dict, count: int) -> bool:
    rows = metadata.get("solutions", [])
    return len(rows) == count and all(
        s.get("verification", {}).get("compiled")
        and s["verification"].get("total", 0) > 0
        and s["verification"].get("passed") == s["verification"].get("total")
        and ({"array", "pointer"} & set(s.get("compatibility", {}).get("features", [])))
        for s in rows)

def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--shards", type=Path, required=True)
    ap.add_argument("--output", type=Path, required=True)
    ap.add_argument("--problem-limit", type=int, default=100)
    ap.add_argument("--solutions-per-problem", type=int, default=10)
    args = ap.parse_args()
    found = {}
    for path in sorted(args.shards.glob("**/problems/*/metadata.json")):
        data = json.loads(path.read_text(encoding="utf-8"))
        if valid(data, args.solutions_per_problem):
            found.setdefault(data["problem_id"], (data, path.parent))
    selected = sorted(found.values(), key=lambda x: (-int(x[0].get("topic_score", 0)), x[0]["problem_id"]))[:args.problem_limit]
    if len(selected) < args.problem_limit:
        raise SystemExit(f"only {len(selected)} fully verified unique problems; need {args.problem_limit}")
    if args.output.exists(): shutil.rmtree(args.output)
    (args.output / "problems").mkdir(parents=True)
    features = Counter(); rows = []; tests = passed = 0; manifest_rows = []
    for metadata, source_dir in selected:
        shutil.copytree(source_dir, args.output / "problems" / metadata["problem_id"])
        manifest_rows.append(metadata); tests += int(metadata.get("downloaded_test_count", 0))
        for solution in metadata["solutions"]:
            fs = solution["compatibility"].get("features", []); features.update(fs)
            verification = solution["verification"]; passed += int(verification["passed"])
            rows.append({"problem_id": metadata["problem_id"], "judge_id": solution["judge_id"],
                         "language": solution.get("language", ""), "features": ";".join(fs),
                         "official_tests": verification["total"], "passed_tests": verification["passed"],
                         "compiled": verification["compiled"], "sha256": solution["sha256"]})
    summary = {"site": "Aizu Online Judge", "collected_problems": len(selected), "solutions": len(rows),
               "downloaded_official_test_files": tests, "solution_test_executions_passed": passed,
               "feature_occurrences": dict(features),
               "acceptance": "10 distinct public C AC solutions; C11 compile; all downloaded official tests pass; array or pointer required",
               "problems": manifest_rows}
    (args.output / "manifest.json").write_text(json.dumps(summary, ensure_ascii=False, indent=2), encoding="utf-8")
    with (args.output / "experiment_results.csv").open("w", newline="", encoding="utf-8") as fp:
        writer = csv.DictWriter(fp, fieldnames=list(rows[0])); writer.writeheader(); writer.writerows(rows)
    print(json.dumps({k:v for k,v in summary.items() if k != "problems"}, ensure_ascii=False, indent=2))
    return 0
if __name__ == "__main__": raise SystemExit(main())
