#!/usr/bin/env python3
"""Compare MaxMEMS baseline vs prefix-feasibility rescue results."""
from __future__ import annotations
import argparse, csv, json
from pathlib import Path

PASS = {"pass_full_replay", "pass_partial_replay", "pass_static_only"}

def read_programs(root: Path):
    rows = {}
    for path in sorted(root.rglob("programs-shard*.csv")):
        with path.open(encoding="utf-8") as fh:
            for row in csv.DictReader(fh):
                rows[Path(row["source"]).name] = row
    return rows

def is_static_pass(row):
    if not row:
        return False
    return (
        row.get("status") in PASS
        and int(row.get("functions_checked") or 0) > 0
        and int(row.get("static_mismatch_functions") or 0) == 0
    )

def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--baseline", type=Path, required=True)
    ap.add_argument("--prefix", type=Path, required=True)
    ap.add_argument("--output", type=Path, required=True)
    ap.add_argument("--expected", type=int, default=9)
    args = ap.parse_args()

    b = read_programs(args.baseline)
    p = read_programs(args.prefix)
    names = sorted(set(b) | set(p))
    out = args.output.resolve()
    out.mkdir(parents=True, exist_ok=True)

    rows = []
    rescued = []
    regressed = []
    for name in names:
        br, pr = b.get(name), p.get(name)
        bp, pp = is_static_pass(br), is_static_pass(pr)
        if not bp and pp:
            verdict = "rescued_by_prefix"
            rescued.append(name)
        elif bp and not pp:
            verdict = "regressed_with_prefix"
            regressed.append(name)
        elif bp and pp:
            verdict = "pass_both"
        else:
            verdict = "fail_both"
        rows.append({
            "program": name,
            "baseline_status": (br or {}).get("status", "missing"),
            "baseline_dp_status": (br or {}).get("dp_status", ""),
            "baseline_dfs_status": (br or {}).get("dfs_status", ""),
            "prefix_status": (pr or {}).get("status", "missing"),
            "prefix_dp_status": (pr or {}).get("dp_status", ""),
            "prefix_dfs_status": (pr or {}).get("dfs_status", ""),
            "verdict": verdict,
        })

    with (out / "comparison.csv").open("w", newline="", encoding="utf-8") as fh:
        w = csv.DictWriter(fh, fieldnames=list(rows[0].keys()) if rows else [
            "program","baseline_status","baseline_dp_status","baseline_dfs_status",
            "prefix_status","prefix_dp_status","prefix_dfs_status","verdict"
        ])
        w.writeheader()
        w.writerows(rows)

    summary = {
        "expected_programs": args.expected,
        "baseline_programs_collected": len(b),
        "prefix_programs_collected": len(p),
        "baseline_static_passes": sum(is_static_pass(r) for r in b.values()),
        "prefix_static_passes": sum(is_static_pass(r) for r in p.values()),
        "rescued_by_prefix": rescued,
        "regressed_with_prefix": regressed,
        "pass_both": sum(r["verdict"] == "pass_both" for r in rows),
        "fail_both": sum(r["verdict"] == "fail_both" for r in rows),
    }
    (out / "summary.json").write_text(json.dumps(summary, indent=2) + "\n", encoding="utf-8")
    md = [
        "# MaxMEMS prefix-pruning A/B rescue",
        "",
        f"- Baseline static passes: **{summary['baseline_static_passes']} / {args.expected}**",
        f"- Prefix-pruned static passes: **{summary['prefix_static_passes']} / {args.expected}**",
        f"- Rescued by prefix pruning: **{len(rescued)}**",
        f"- Regressed with prefix pruning: **{len(regressed)}**",
        f"- Pass in both: **{summary['pass_both']}**",
        f"- Fail in both: **{summary['fail_both']}**",
        "",
        "## Rescued",
        *(f"- {x}" for x in rescued),
        "",
        "## Regressed",
        *(f"- {x}" for x in regressed),
        "",
    ]
    (out / "summary.md").write_text("\n".join(md), encoding="utf-8")
    print("PREFIX_RESCUE_AB " + json.dumps(summary, sort_keys=True))

if __name__ == "__main__":
    main()
