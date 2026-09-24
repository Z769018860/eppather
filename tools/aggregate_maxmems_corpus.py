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
    path_limit_functions=sum(r.get("path_limit_hit")=="1" for r in functions)
    path_limit_programs=sum(int(r.get("path_limit_functions") or 0)>0 for r in programs)
    static_fn_equal=sum(r.get("static_equal")=="1" for r in functions)
    uncapped_static_fn_equal=sum(
        r.get("static_equal")=="1" and r.get("path_limit_hit")!="1" for r in functions
    )
    uncapped_static_equal_programs=sum(
        int(r.get("functions_checked") or 0)>0
        and int(r.get("static_mismatch_functions") or 0)==0
        and int(r.get("path_limit_functions") or 0)==0
        and r.get("status") not in ("dp_failed","dfs_failed","dp_parse_error")
        for r in programs
    )
    analyzed_programs=sum(int(r.get("functions_checked") or 0)>0 for r in programs)
    valid_c_programs=sum(r.get("c_syntax_status")=="valid" for r in programs)
    invalid_c_programs=sum(r.get("c_syntax_status")=="invalid" for r in programs)
    syntax_timeout_programs=sum(r.get("c_syntax_status")=="timeout" for r in programs)
    dp_timeout_programs=sum(r.get("status")=="dp_failed" and r.get("dp_status")=="timeout" for r in programs)
    dfs_timeout_programs=sum(r.get("status")=="dfs_failed" and r.get("dfs_status")=="timeout" for r in programs)
    dp_parse_error_programs=sum(r.get("status")=="dp_parse_error" for r in programs)
    true_static_mismatch_programs=sum(int(r.get("static_mismatch_functions") or 0)>0 for r in programs)
    replay_mismatch_programs=sum(
        int(r.get("static_mismatch_functions") or 0)==0
        and any(f.get("source")==r.get("source") and f.get("replay_status")=="mismatch" for f in functions)
        for r in programs
    )
    retry_attempted_programs=sum(
        r.get("dp_retried")=="1" or r.get("dfs_retried")=="1" for r in programs
    )
    retry_rescued_programs=sum(
        (r.get("dp_retried")=="1" or r.get("dfs_retried")=="1")
        and r.get("status") not in ("dp_failed","dfs_failed") for r in programs
    )
    delta_known=[r for r in functions if str(r.get("dp_score_delta","")).strip()!=""]
    delta_nonzero=sum(int(r.get("dp_score_delta") or 0)!=0 for r in delta_known)
    replay_status_counts={}
    for r in functions:
        st=r.get("replay_status") or "missing"
        replay_status_counts[st]=replay_status_counts.get(st,0)+1
    summary={
        "expected_programs":args.expected_programs,
        "programs_collected":len(programs),
        "unique_programs":len(program_sources),
        "valid_c_programs":valid_c_programs,
        "invalid_c_programs":invalid_c_programs,
        "syntax_timeout_programs":syntax_timeout_programs,
        "analyzed_programs":analyzed_programs,
        "static_equal_programs":len(static_equal),
        "static_equal_rate_all":(len(static_equal)/args.expected_programs if args.expected_programs else 0.0),
        "static_equal_rate_analyzed":(len(static_equal)/analyzed_programs if analyzed_programs else 0.0),
        "true_static_mismatch_programs":true_static_mismatch_programs,
        "replay_only_mismatch_programs":replay_mismatch_programs,
        "dp_timeout_programs":dp_timeout_programs,
        "dfs_timeout_programs":dfs_timeout_programs,
        "dp_parse_error_programs":dp_parse_error_programs,
        "retry_attempted_programs":retry_attempted_programs,
        "retry_rescued_programs":retry_rescued_programs,
        "hard_failure_programs":len(hard),
        "full_replay_programs":len(full),
        "partial_replay_programs":len(partial),
        "static_only_programs":len(static_only),
        "functions_checked":len(functions),
        "static_equal_functions":static_fn_equal,
        "uncapped_static_equal_functions":uncapped_static_fn_equal,
        "uncapped_static_equal_programs":uncapped_static_equal_programs,
        "path_limit_functions":path_limit_functions,
        "path_limit_programs":path_limit_programs,
        "replay_match_functions":replay_match,
        "replay_unsupported_functions":replay_unsupported,
        "replay_undefined_functions":replay_undefined,
        "replay_error_functions":replay_error,
        "replay_mismatch_functions":replay_mismatch,
        "dp_score_delta_known_functions":len(delta_known),
        "dp_score_delta_nonzero_functions":delta_nonzero,
        "replay_status_counts":replay_status_counts,
        "historical_20260509_static_equal_programs":145,
        "gain_vs_20260509_static_equal_programs":len(static_equal)-145,
    }
    for name, rows in (("programs.csv",programs),("functions.csv",functions)):
        if rows:
            with (out/name).open("w",newline="",encoding="utf-8") as fh:
                w=csv.DictWriter(fh,fieldnames=list(rows[0].keys())); w.writeheader(); w.writerows(rows)
    failures=[r for r in programs if r.get("hard_failure")=="1" or r.get("status")=="mismatch"]
    path_limited=[r for r in functions if r.get("path_limit_hit")=="1"]
    replay_residual=[r for r in functions if r.get("replay_status") in
                     ("error","mismatch","witness_not_found")]
    for name, rows in (
        ("failures.csv", failures),
        ("path-limit-functions.csv", path_limited),
        ("replay-residual-functions.csv", replay_residual),
    ):
        if rows:
            with (out/name).open("w",newline="",encoding="utf-8") as fh:
                w=csv.DictWriter(fh,fieldnames=list(rows[0].keys())); w.writeheader(); w.writerows(rows)
    (out/"summary.json").write_text(json.dumps(summary,indent=2)+"\n",encoding="utf-8")
    md=["# MaxMEMS 266-program corpus validation","",
        f"- Programs collected: **{summary['programs_collected']} / {args.expected_programs}**",
        f"- GNU C syntax-valid normalized programs: **{summary['valid_c_programs']}**",
        f"- GNU C syntax-invalid normalized programs: **{summary['invalid_c_programs']}**",
        f"- Programs reaching function-level DP/DFS comparison: **{summary['analyzed_programs']}**",
        f"- Programs with DP/DFS equality (including capped DFS where applicable): **{summary['static_equal_programs']}** "
        f"({summary['static_equal_rate_all']:.1%} of frozen corpus; {summary['static_equal_rate_analyzed']:.1%} of analyzed programs)",
        f"- Historical 2026-05-09 DP=DFS baseline: **145 / 266**; current gain: **{summary['gain_vs_20260509_static_equal_programs']:+d}**",
        f"- True static-mismatch programs: **{summary['true_static_mismatch_programs']}**",
        f"- Replay-only mismatch programs: **{summary['replay_only_mismatch_programs']}**",
        f"- DP timeout programs after retry: **{summary['dp_timeout_programs']}**",
        f"- DFS timeout programs after retry: **{summary['dfs_timeout_programs']}**",
        f"- DP parse-error programs: **{summary['dp_parse_error_programs']}**",
        f"- Retry attempted/rescued programs: **{summary['retry_attempted_programs']} / {summary['retry_rescued_programs']}**",
        f"- Non-zero DP score-delta diagnostics: **{summary['dp_score_delta_nonzero_functions']} / {summary['dp_score_delta_known_functions']}**",
        f"- Hard-failure programs: **{summary['hard_failure_programs']}**",
        f"- Full concrete-replay programs: **{summary['full_replay_programs']}**",
        f"- Partial concrete-replay programs: **{summary['partial_replay_programs']}**",
        f"- Static-only programs: **{summary['static_only_programs']}**",
        f"- Functions checked: **{summary['functions_checked']}**",
        f"- Static-equal functions: **{summary['static_equal_functions']}**",
        f"- Static-equal functions without a DFS path-limit hit: **{summary['uncapped_static_equal_functions']}**",
        f"- Programs with no DFS path-limit hit and complete static agreement: **{summary['uncapped_static_equal_programs']}**",
        f"- Functions hitting maxpaths: **{summary['path_limit_functions']}**",
        f"- Programs containing a maxpaths hit: **{summary['path_limit_programs']}**",
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
