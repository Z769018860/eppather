#!/usr/bin/env python3
"""Aggregate sharded MaxMEMS corpus validation results."""
from __future__ import annotations
import argparse, csv, json
from pathlib import Path


def read_csvs(root: Path, pattern: str):
    rows = []
    for path in sorted(root.rglob(pattern)):
        with path.open(encoding="utf-8") as fh:
            rows.extend(csv.DictReader(fh))
    return rows


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--input", type=Path, required=True)
    ap.add_argument("--output", type=Path, required=True)
    ap.add_argument("--expected-programs", type=int, default=266)
    ap.add_argument("--strict", action="store_true")
    args = ap.parse_args()
    out=args.output.resolve(); out.mkdir(parents=True, exist_ok=True)
    programs=read_csvs(args.input.resolve(),"programs-shard*.csv")
    functions=read_csvs(args.input.resolve(),"functions-shard*.csv")
    program_sources={r["source"] for r in programs}
    hard=[r for r in programs if r.get("hard_failure")=="1"]
    static_equal=[r for r in programs if int(r.get("functions_checked") or 0)>0
                  and int(r.get("static_mismatch_functions") or 0)==0
                  and r.get("status") not in ("dp_failed","dfs_failed","dp_parse_error")]
    full=[r for r in programs if r.get("status")=="pass_full_replay"]
    partial=[r for r in programs if r.get("status")=="pass_partial_replay"]
    static_only=[r for r in programs if r.get("status")=="pass_static_only"]
    replay_match=sum(r.get("replay_status")=="match" for r in functions)
    replay_unsupported=sum(r.get("replay_status","").startswith("unsupported") for r in functions)
    replay_undefined=sum(r.get("replay_status")=="undefined" for r in functions)
    replay_error=sum(r.get("replay_status")=="error" for r in functions)
    replay_mismatch=sum(r.get("replay_status")=="mismatch" for r in functions)
    static_fn_equal=sum(r.get("static_equal")=="1" for r in functions)
    summary={
        "expected_programs":args.expected_programs,
        "programs_collected":len(programs),
        "unique_programs":len(program_sources),
        "static_equal_programs":len(static_equal),
        "hard_failure_programs":len(hard),
        "full_replay_programs":len(full),
        "partial_replay_programs":len(partial),
        "static_only_programs":len(static_only),
        "functions_checked":len(functions),
        "static_equal_functions":static_fn_equal,
        "replay_match_functions":replay_match,
        "replay_unsupported_functions":replay_unsupported,
        "replay_undefined_functions":replay_undefined,
        "replay_error_functions":replay_error,
        "replay_mismatch_functions":replay_mismatch,
    }
    for name, rows in (("programs.csv",programs),("functions.csv",functions)):
        if rows:
            with (out/name).open("w",newline="",encoding="utf-8") as fh:
                w=csv.DictWriter(fh,fieldnames=list(rows[0].keys())); w.writeheader(); w.writerows(rows)
    (out/"summary.json").write_text(json.dumps(summary,indent=2)+"\n",encoding="utf-8")
    md=["# MaxMEMS 266-program corpus validation","",
        f"- Programs collected: **{summary['programs_collected']} / {args.expected_programs}**",
        f"- Programs with complete static DP/DFS agreement: **{summary['static_equal_programs']}**",
        f"- Hard-failure programs: **{summary['hard_failure_programs']}**",
        f"- Full concrete-replay programs: **{summary['full_replay_programs']}**",
        f"- Partial concrete-replay programs: **{summary['partial_replay_programs']}**",
        f"- Static-only programs: **{summary['static_only_programs']}**",
        f"- Functions checked: **{summary['functions_checked']}**",
        f"- Static-equal functions: **{summary['static_equal_functions']}**",
        f"- Concrete witness branch matches: **{summary['replay_match_functions']}**",
        f"- Replay unsupported: **{summary['replay_unsupported_functions']}**",
        f"- Replay undefined: **{summary['replay_undefined_functions']}**",
        f"- Replay errors: **{summary['replay_error_functions']}**",
        f"- Replay mismatches: **{summary['replay_mismatch_functions']}**",""]
    (out/"summary.md").write_text("\n".join(md),encoding="utf-8")
    print("MAXMEMS266_SUMMARY "+json.dumps(summary,sort_keys=True))
    bad=(summary["programs_collected"]!=args.expected_programs or
         summary["unique_programs"]!=args.expected_programs or
         summary["static_equal_programs"]!=args.expected_programs or
         summary["hard_failure_programs"]!=0 or
         summary["replay_mismatch_functions"]!=0)
    return 1 if args.strict and bad else 0


if __name__=="__main__":
    raise SystemExit(main())
