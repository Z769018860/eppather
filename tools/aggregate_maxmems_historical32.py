#!/usr/bin/env python3
"""Aggregate the frozen 32 historical DP/DFS MaxMEMS mismatches."""
from __future__ import annotations
import argparse, csv, json
from pathlib import Path

OLD = {
"averages-arithmetic-mean.c": (4,13), "averages-median-2.c": (1,32),
"combinations-1.c": (17,7), "compile-time-calculation-1.c": (2,8),
"dot-product.c": (2,14), "factorial-5.c": (2,8),
"fibonacci-sequence-4.c": (2,17), "file-input-output-2.c": (5,7),
"gray-code-1.c": (5,11), "greatest-subsequential-sum.c": (7,33),
"harshad-or-niven-series.c": (2,8), "jensens-device-2.c": (2,8),
"last-friday-of-each-month.c": (12,14), "left-factorials.c": (2,17),
"list-comprehensions-2.c": (1,10), "non-continuous-subsequences-3.c": (4,0),
"number-names.c": (2,6), "ordered-words-1.c": (4,12),
"pernicious-numbers.c": (2,8), "plot-coordinate-pairs-2.c": (20,63),
"price-fraction.c": (7,13), "read-a-specific-line-from-a-file-1.c": (3,34),
"rep-string-2.c": (2,13), "search-a-list.c": (1,16),
"sorting-algorithms-cocktail-sort-1.c": (9,24), "soundex.c": (6,20),
"string-case.c": (1,19), "sum-and-product-of-an-array.c": (7,25),
"sum-digits-of-an-integer.c": (2,8), "sum-multiples-of-3-and-5-1.c": (2,4),
"terminal-control-unicode-output.c": (6,12),
"use-another-language-to-call-a-function-2.c": (1,2),
}

def rows(root: Path, pattern: str):
    out=[]
    for p in sorted(root.rglob(pattern)):
        with p.open(encoding="utf-8") as f: out.extend(csv.DictReader(f))
    return out

def main():
    ap=argparse.ArgumentParser()
    ap.add_argument("--input",type=Path,required=True)
    ap.add_argument("--output",type=Path,required=True)
    a=ap.parse_args(); a.output.mkdir(parents=True,exist_ok=True)
    ps=rows(a.input,"programs-shard*.csv"); fs=rows(a.input,"functions-shard*.csv")
    by={}
    for r in fs:
        name=Path(r["source"]).name
        by.setdefault(name,[]).append(r)
    detail=[]
    for name,(old_dp,old_dfs) in OLD.items():
        prs=[p for p in ps if Path(p["source"]).name==name]
        fns=by.get(name,[])
        comparable=bool(fns)
        equal=comparable and all(x.get("static_equal")=="1" for x in fns)
        capped=any(x.get("path_limit_hit")=="1" for x in fns)
        new_dp=";".join(x.get("dp_mems","") for x in fns)
        new_dfs=";".join(x.get("dfs_max_mems","") for x in fns)
        delta=";".join(x.get("dp_score_delta","") for x in fns)
        status=prs[0].get("status","missing") if prs else "missing"
        detail.append({
            "file":name,"old_dp":old_dp,"old_dfs":old_dfs,"old_diff":old_dp-old_dfs,
            "new_dp":new_dp,"new_dfs":new_dfs,"score_delta":delta,
            "comparable":int(comparable),"static_equal":int(equal),
            "path_limit_hit":int(capped),"status":status,
        })
    resolved=sum(r["static_equal"]==1 for r in detail)
    comparable=sum(r["comparable"]==1 for r in detail)
    uncapped_resolved=sum(r["static_equal"]==1 and r["path_limit_hit"]==0 for r in detail)
    summary={"cases":32,"programs_collected":len(ps),"comparable":comparable,
             "resolved_static_equal":resolved,"resolved_uncapped":uncapped_resolved,
             "remaining_or_unavailable":32-resolved}
    with (a.output/"historical32.csv").open("w",newline="",encoding="utf-8") as f:
        w=csv.DictWriter(f,fieldnames=list(detail[0])); w.writeheader(); w.writerows(detail)
    (a.output/"summary.json").write_text(json.dumps(summary,indent=2)+"\n",encoding="utf-8")
    print("HISTORICAL32 "+json.dumps(summary,sort_keys=True))
    return 0

if __name__=="__main__": raise SystemExit(main())
