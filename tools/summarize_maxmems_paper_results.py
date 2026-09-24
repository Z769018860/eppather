#!/usr/bin/env python3
"""Extract paper-facing MaxMEMS metrics from a completed 266 aggregate directory."""
from __future__ import annotations
import argparse, csv, json
from pathlib import Path

def read_csv(path: Path):
    if not path.exists():
        return []
    with path.open(encoding="utf-8", newline="") as fh:
        return list(csv.DictReader(fh))

def i(row, key):
    try:
        return int(row.get(key) or 0)
    except ValueError:
        return 0

def main():
    ap=argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--input", type=Path, required=True,
                    help="directory containing programs.csv/functions.csv/summary.json")
    ap.add_argument("--output", type=Path, default=None)
    args=ap.parse_args()
    root=args.input.resolve()
    programs=read_csv(root/"programs.csv")
    functions=read_csv(root/"functions.csv")
    base={}
    if (root/"summary.json").exists():
        base=json.loads((root/"summary.json").read_text(encoding="utf-8"))

    analyzed=[r for r in programs if i(r,"functions_checked")>0]
    equal=[r for r in analyzed if i(r,"static_mismatch_functions")==0]
    uncapped_equal=[r for r in equal if i(r,"path_limit_functions")==0]
    fallback=[r for r in programs if i(r,"dfs_max_only_fallback")==1]
    dp_timeouts=[r for r in programs if r.get("status")=="dp_failed" and r.get("dp_status")=="timeout"]
    dfs_timeouts=[r for r in programs if r.get("status")=="dfs_failed" and r.get("dfs_status")=="timeout"]
    true_mismatch=[r for r in programs if i(r,"static_mismatch_functions")>0]
    replay_match=[r for r in functions if r.get("replay_status")=="match"]
    replay_undefined=[r for r in functions if r.get("replay_status")=="undefined"]
    replay_unsupported=[r for r in functions if (r.get("replay_status") or "").startswith("unsupported")]
    replay_mismatch=[r for r in functions if r.get("replay_status")=="mismatch"]
    pathlimited=[r for r in functions if i(r,"path_limit_hit")==1]

    result={
        "programs": len(programs),
        "analyzed_programs": len(analyzed),
        "static_equal_programs": len(equal),
        "static_equal_rate_all": len(equal)/266 if programs else 0,
        "static_equal_rate_analyzed": len(equal)/len(analyzed) if analyzed else 0,
        "uncapped_static_equal_programs": len(uncapped_equal),
        "true_static_mismatch_programs": len(true_mismatch),
        "dp_timeout_programs": len(dp_timeouts),
        "dfs_timeout_programs": len(dfs_timeouts),
        "dfs_max_only_fallback_programs": len(fallback),
        "path_limit_functions": len(pathlimited),
        "replay_match_functions": len(replay_match),
        "replay_undefined_functions": len(replay_undefined),
        "replay_unsupported_functions": len(replay_unsupported),
        "replay_mismatch_functions": len(replay_mismatch),
        "historical_static_equal_programs": 145,
        "gain_vs_historical": len(equal)-145,
        "fallback_sources": [Path(r["source"]).name for r in fallback],
        "dp_timeout_sources": [Path(r["source"]).name for r in dp_timeouts],
        "dfs_timeout_sources": [Path(r["source"]).name for r in dfs_timeouts],
        "true_mismatch_sources": [Path(r["source"]).name for r in true_mismatch],
    }
    # Preserve authoritative aggregate fields for cross-checking.
    result["aggregate_summary"]=base

    out=args.output or root/"paper-metrics.json"
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_text(json.dumps(result, indent=2)+"\n", encoding="utf-8")

    md=out.with_suffix(".md")
    md.write_text("\n".join([
        "# MaxMEMS final 266 paper metrics",
        "",
        f"- Programs collected: **{result['programs']} / 266**",
        f"- Programs reaching DP/DFS comparison: **{result['analyzed_programs']}**",
        f"- DP=DFS programs: **{result['static_equal_programs']} / 266 ({result['static_equal_rate_all']:.1%})**",
        f"- DP=DFS among analyzed: **{result['static_equal_programs']} / {result['analyzed_programs']} ({result['static_equal_rate_analyzed']:.1%})**" if result['analyzed_programs'] else "- DP=DFS among analyzed: N/A",
        f"- Complete agreement with no DFS maxpaths hit: **{result['uncapped_static_equal_programs']} programs**",
        f"- Gain over historical 145/266 baseline: **{result['gain_vs_historical']:+d} programs**",
        f"- True static mismatch programs: **{result['true_static_mismatch_programs']}**",
        f"- DP timeouts after retry: **{result['dp_timeout_programs']}**",
        f"- DFS timeouts after retry/fallback: **{result['dfs_timeout_programs']}**",
        f"- DFS max-only fallback programs: **{result['dfs_max_only_fallback_programs']}**",
        f"- Path-limit-hit functions: **{result['path_limit_functions']}**",
        f"- Replay match / undefined / unsupported / mismatch functions: **{result['replay_match_functions']} / {result['replay_undefined_functions']} / {result['replay_unsupported_functions']} / {result['replay_mismatch_functions']}**",
        "",
        "## Residual sources",
        "",
        f"- DP timeout: {', '.join(result['dp_timeout_sources']) or 'none'}",
        f"- DFS timeout: {', '.join(result['dfs_timeout_sources']) or 'none'}",
        f"- True static mismatch: {', '.join(result['true_mismatch_sources']) or 'none'}",
        f"- DFS max-only fallback: {', '.join(result['fallback_sources']) or 'none'}",
        "",
    ]), encoding="utf-8")
    print("MAXMEMS_PAPER_METRICS "+json.dumps(result, sort_keys=True))

if __name__=="__main__":
    main()
