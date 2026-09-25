#!/usr/bin/env python3
"""Independent concrete validation for Eppather bounded MaxMEMS witnesses."""
from __future__ import annotations

import argparse
import csv
import itertools
import json
import os
import re
import subprocess
import sys
import tempfile
import time
from dataclasses import asdict, dataclass
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from e2e_path_validation import (
    UndefinedBehaviorError,
    expected_outcomes,
    instrument_conditions,
    parse_model,
    parse_signature,
    run,
)

MEM_RE = re.compile(r"\[mem\]:(-?\d+)")
DP_TIME_RE = re.compile(r"\[DP TIME COST\]:\s*([0-9.eE+-]+)")
DFS_TIME_RE = re.compile(r"\[DFS TIME COST\]:\s*([0-9.eE+-]+)")
DP_MEMO_LOOKUPS_RE = re.compile(r"\[DP MEMO LOOKUPS\]:\s*(\d+)")
DP_MEMO_HITS_RE = re.compile(r"\[DP MEMO HITS\]:\s*(\d+)")
DP_MEMO_RATE_RE = re.compile(r"\[DP MEMO HIT RATE\]:\s*([0-9.eE+-]+)")
DP_MEMO_STORES_RE = re.compile(r"\[DP MEMO STORES\]:\s*(\d+)")
DP_MEMO_ENTRIES_RE = re.compile(r"\[DP MEMO ENTRIES\]:\s*(\d+)")
DP_TERMINAL_EVALS_RE = re.compile(r"\[DP TERMINAL EVALS\]:\s*(\d+)")
DP_PATH_RE = re.compile(
    r"\[MAX MEMS PATH\]:\s*\n(.*?)(?=\n(?:\[DP INTERNAL MEMS\]|\[DP SCORE DELTA\]|MEMS:))",
    re.S,
)
DP_MEM_RE = re.compile(r"(?m)^MEMS:\s*(-?\d+)")
MARK = "/*EPP_MEM*/"

@dataclass
class Result:
    status: str
    dp_mems: int
    dfs_oracle_mems: int
    dynamic_witness_mems: int | None
    dynamic_oracle_mems: int | None
    witness_inputs: dict[str, int]
    dp_branches: list[int]
    actual_branches: list[int]
    feasible_paths: int
    defined_oracle_inputs: int
    undefined_oracle_inputs: int
    detail: str = ""
    dp_reported_seconds: float | None = None
    dfs_reported_seconds: float | None = None
    dp_wall_seconds: float | None = None
    dfs_wall_seconds: float | None = None
    memo_lookups: int | None = None
    memo_hits: int | None = None
    memo_hit_rate: float | None = None
    memo_stores: int | None = None
    memo_entries: int | None = None
    terminal_evals: int | None = None

def mem_instrument(source: str) -> str:
    out, pos = [], 0
    while True:
        idx = source.find(MARK, pos)
        if idx < 0:
            out.append(source[pos:])
            break
        out.append(source[pos:idx])
        start = idx + len(MARK)
        while start < len(source) and source[start].isspace():
            start += 1
        if start >= len(source) or source[start] != "(":
            raise ValueError(f"{MARK} must precede a parenthesized int lvalue")
        depth, end = 0, start
        while end < len(source):
            if source[end] == "(":
                depth += 1
            elif source[end] == ")":
                depth -= 1
                if depth == 0:
                    break
            end += 1
        if depth != 0:
            raise ValueError("unterminated memory annotation")
        inner = source[start + 1:end]
        out.append(f"(*epp_mem_ref(&({inner})))")
        pos = end + 1
    return "".join(out)

def env_for(cnip: Path) -> dict[str, str]:
    env = os.environ.copy()
    dirs = [cnip.parent, cnip.parent/"C", cnip.parent/"common",
            cnip.parent/"libParser/z3/bin", cnip.parent/"lpsolve"]
    env["LD_LIBRARY_PATH"] = ":".join(map(str, dirs)) + ":" + env.get("LD_LIBRARY_PATH", "")
    return env

def analyze(cnip: Path, src: Path, max_loop: int, work: Path, flag: str):
    start = time.perf_counter()
    proc = run([str(cnip), flag, str(src), str(max_loop)], work, env_for(cnip))
    return proc, time.perf_counter() - start

def _metric(pattern: re.Pattern[str], text: str, cast):
    match = pattern.search(text)
    return cast(match.group(1)) if match else None

def attach_search_metrics(result: Result, dp_text: str, dfs_text: str,
                          dp_wall: float, dfs_wall: float) -> Result:
    result.dp_reported_seconds = _metric(DP_TIME_RE, dp_text, float)
    result.dfs_reported_seconds = _metric(DFS_TIME_RE, dfs_text, float)
    result.dp_wall_seconds = dp_wall
    result.dfs_wall_seconds = dfs_wall
    result.memo_lookups = _metric(DP_MEMO_LOOKUPS_RE, dp_text, int)
    result.memo_hits = _metric(DP_MEMO_HITS_RE, dp_text, int)
    result.memo_hit_rate = _metric(DP_MEMO_RATE_RE, dp_text, float)
    result.memo_stores = _metric(DP_MEMO_STORES_RE, dp_text, int)
    result.memo_entries = _metric(DP_MEMO_ENTRIES_RE, dp_text, int)
    result.terminal_evals = _metric(DP_TERMINAL_EVALS_RE, dp_text, int)
    return result

def parse_dp(text: str):
    path_m = DP_PATH_RE.search(text)
    mem_m = DP_MEM_RE.search(text)
    if not path_m or not mem_m:
        raise RuntimeError("cannot parse -g MaxMEMS output")
    path = path_m.group(1).rstrip()
    return int(mem_m.group(1)), expected_outcomes(path)

def dfs_cases(work: Path, function: str, params: list[str], source: str):
    rows = []
    for rf in sorted(work.glob(f"result_{function}_*.txt")):
        txt = rf.read_text(encoding="utf-8", errors="replace")
        if not re.search(r"(?m)^feasible$", txt):
            continue
        mm = MEM_RE.search(txt)
        im = re.search(r"_(\d+)\.txt$", rf.name)
        if not mm or not im:
            continue
        pid = int(im.group(1))
        pf = work / f"path_{function}_{pid}.txt"
        if not pf.exists():
            continue
        path = pf.read_text(encoding="utf-8", errors="replace")
        rows.append({
            "mems": int(mm.group(1)),
            "branches": expected_outcomes(path),
            "inputs": parse_model(txt, params, source),
        })
    return rows

def compile_replay(source: str, function: str, params: list[str], work: Path, max_loop: int) -> Path:
    traced = instrument_conditions(mem_instrument(source), max_loop, function)
    decls = "\n".join(
        f"int {p}=(int)strtol(argv[{i+1}],0,10);" for i, p in enumerate(params)
    )
    args = ",".join(params)
    program = (
        "#include <stdio.h>\n#include <stdlib.h>\n"
        "static unsigned epp_loop_count[4096];\n"
        "static int epp_in_entry;\n"
        "static long long epp_mem_count;\n"
        "static int *epp_mem_ref(int *p){++epp_mem_count;return p;}\n"
        "static int epp_trace(int id,int v){printf(\"EPP_BRANCH %d %d\\n\",id,!!v);return v;}\n"
        "#define EPP_TRACE(id,expr) (epp_trace_enabled ? epp_trace((id),(expr)) : (expr))\n"
        "#define EPP_LOOP_TRACE(id,bound,expr) (epp_trace_enabled ? epp_trace((id),(epp_loop_count[(id)]++ < (bound)) && !!(expr)) : (expr))\n"
        + traced +
        f"\nint main(int argc,char **argv){{if(argc!={len(params)+1})return 2;{decls}"
        f"(void){function}({args});printf(\"EPP_MEMS %lld\\n\",epp_mem_count);return 0;}}\n"
    )
    cfile, exe = work/"replay.c", work/"replay"
    cfile.write_text(program, encoding="utf-8")
    built = run(["cc","-std=c11","-O0","-fsanitize=undefined",
                 "-fno-sanitize-recover=undefined",str(cfile),"-o",str(exe)], work)
    if built.returncode:
        raise RuntimeError("replay compile failed: " + built.stderr[-1600:])
    return exe

def replay(exe: Path, params: list[str], inputs: dict[str, int], work: Path):
    p = run([str(exe)] + [str(inputs[x]) for x in params], work)
    if p.returncode:
        if "runtime error:" in p.stderr:
            raise UndefinedBehaviorError(p.stderr.strip().splitlines()[-1])
        raise RuntimeError(f"replay exited {p.returncode}: {p.stderr[-400:]}")
    branches = [int(m.group(1)) for m in
                re.finditer(r"^EPP_BRANCH\s+\d+\s+([01])$", p.stdout, re.M)]
    mm = re.search(r"^EPP_MEMS\s+(\d+)$", p.stdout, re.M)
    if not mm:
        raise RuntimeError("missing EPP_MEMS")
    return branches, int(mm.group(1))

def dynamic_oracle(exe: Path, params: list[str], lo: int, hi: int, work: Path):
    best, defined, undefined = -1, 0, 0
    for vals in itertools.product(range(lo, hi + 1), repeat=len(params)):
        inp = dict(zip(params, vals))
        try:
            _, mem = replay(exe, params, inp, work)
        except UndefinedBehaviorError:
            undefined += 1
            continue
        defined += 1
        best = max(best, mem)
    if defined == 0:
        raise RuntimeError("no defined oracle executions")
    return best, defined, undefined

def validate(src: Path, function: str, cnip: Path, max_loop: int, lo: int, hi: int) -> Result:
    source = src.read_text(encoding="utf-8")
    selected, params = parse_signature(source, function)
    if MARK not in source:
        raise RuntimeError("controlled subject has no MEMS annotations")
    with tempfile.TemporaryDirectory(prefix="eppather-maxmems-") as td:
        root = Path(td)
        dpw, dfw, rpw = root/"dp", root/"dfs", root/"replay"
        dpw.mkdir(); dfw.mkdir(); rpw.mkdir()
        dp, dp_wall = analyze(cnip, src, max_loop, dpw, "-g")
        if dp.returncode:
            raise RuntimeError("cnip -g failed: " + (dp.stderr or dp.stdout)[-1200:])
        dp_mem, dp_branches = parse_dp(dp.stdout)
        dfs, dfs_wall = analyze(cnip, src, max_loop, dfw, "-q")
        if dfs.returncode:
            raise RuntimeError("cnip -q failed: " + (dfs.stderr or dfs.stdout)[-1200:])
        rows = dfs_cases(dfw, selected, params, source)
        if not rows:
            raise RuntimeError("no feasible DFS2 paths")
        dfs_max = max(r["mems"] for r in rows)
        # Prefer the exact DP branch sequence even when MEMS disagrees.  A
        # DP/DFS MEMS disagreement is an experiment result, not a missing-model
        # infrastructure error, so preserve a concrete witness for diagnosis.
        cand = [r for r in rows if r["branches"] == dp_branches]
        if not cand:
            cand = [r for r in rows if r["mems"] == dfs_max]
        if not cand:
            raise RuntimeError("no feasible DFS model usable as a witness")
        witness = cand[0]
        exe = compile_replay(source, selected, params, rpw, max_loop)
        try:
            actual, dyn_witness = replay(exe, params, witness["inputs"], rpw)
        except UndefinedBehaviorError as exc:
            return attach_search_metrics(
                Result("undefined_witness", dp_mem, dfs_max, None, None,
                       witness["inputs"], dp_branches, [], len(rows), 0, 1, str(exc)),
                dp.stdout, dfs.stdout, dp_wall, dfs_wall)
        dyn_max, defined, undefined = dynamic_oracle(exe, params, lo, hi, rpw)
        failures = []
        if dp_mem != dfs_max: failures.append(f"DP {dp_mem} != DFS {dfs_max}")
        if actual != dp_branches: failures.append("concrete branch sequence differs")
        if dyn_witness != dp_mem: failures.append(f"dynamic witness {dyn_witness} != DP {dp_mem}")
        if dyn_max != dp_mem: failures.append(f"dynamic oracle {dyn_max} != DP {dp_mem}")
        return attach_search_metrics(
            Result("pass" if not failures else "fail", dp_mem, dfs_max,
                   dyn_witness, dyn_max, witness["inputs"], dp_branches, actual,
                   len(rows), defined, undefined, "; ".join(failures)),
            dp.stdout, dfs.stdout, dp_wall, dfs_wall)

def subject(i, category, source, max_loop=4, lo=-2, hi=3):
    return {"id":f"mw{i:02d}","category":category,"function":f"mw{i:02d}",
            "source":source,"max_loop":max_loop,"lo":lo,"hi":hi}

SUBJECTS = [
subject(1,"branch-array","int mw01(int x){int a[3];int y=0;/*EPP_MEM*/(a[0])=x;/*EPP_MEM*/(a[1])=x+1;/*EPP_MEM*/(a[2])=x-1;if(x>0){y=/*EPP_MEM*/(a[0])+/*EPP_MEM*/(a[1]);}else{y=/*EPP_MEM*/(a[2]);}return y;}"),
subject(2,"nested-branch","int mw02(int x,int y){int a[4];int r=0;/*EPP_MEM*/(a[0])=x;/*EPP_MEM*/(a[1])=y;/*EPP_MEM*/(a[2])=x+y;/*EPP_MEM*/(a[3])=x-y;if(x>0){if(y>0){r=/*EPP_MEM*/(a[0])+/*EPP_MEM*/(a[1])+/*EPP_MEM*/(a[2]);}else{r=/*EPP_MEM*/(a[3]);}}else{r=/*EPP_MEM*/(a[2]);}return r;}"),
subject(3,"branch-write","int mw03(int x){int a[2];int r=0;/*EPP_MEM*/(a[0])=x;/*EPP_MEM*/(a[1])=0;if(x>=0){/*EPP_MEM*/(a[1])=/*EPP_MEM*/(a[0])+1;r=/*EPP_MEM*/(a[1]);}else{r=/*EPP_MEM*/(a[0]);}return r;}"),
subject(4,"fixed-for","int mw04(int x){int a[3];int i=0;int s=0;/*EPP_MEM*/(a[0])=x;/*EPP_MEM*/(a[1])=x+1;/*EPP_MEM*/(a[2])=x+2;for(i=0;i<3;i=i+1){s=s+/*EPP_MEM*/(a[i]);}return s;}"),
subject(5,"loop-branch","int mw05(int x){int a[3];int i=0;int s=0;/*EPP_MEM*/(a[0])=x;/*EPP_MEM*/(a[1])=x+1;/*EPP_MEM*/(a[2])=x+2;for(i=0;i<3;i=i+1){if(x>0){s=s+/*EPP_MEM*/(a[i])+/*EPP_MEM*/(a[0]);}else{s=s+/*EPP_MEM*/(a[i]);}}return s;}"),
subject(6,"fixed-while","int mw06(int x){int a[4];int i=0;int s=0;/*EPP_MEM*/(a[0])=x;/*EPP_MEM*/(a[1])=x+1;/*EPP_MEM*/(a[2])=x+2;/*EPP_MEM*/(a[3])=x+3;while(i<4){s=s+/*EPP_MEM*/(a[i]);i=i+1;}return s;}",5),
subject(7,"short-circuit-array","int mw07(int x){int a[2];int r=0;/*EPP_MEM*/(a[0])=1;/*EPP_MEM*/(a[1])=2;if((x>0)&&(x<3)){r=/*EPP_MEM*/(a[0])+/*EPP_MEM*/(a[1]);}else{r=/*EPP_MEM*/(a[0]);}return r;}"),
subject(8,"array-write-chain","int mw08(int x){int a[2];int r=0;/*EPP_MEM*/(a[0])=1;/*EPP_MEM*/(a[1])=2;if(x>=0){/*EPP_MEM*/(a[0])=/*EPP_MEM*/(a[0])+1;/*EPP_MEM*/(a[1])=/*EPP_MEM*/(a[0])+1;r=/*EPP_MEM*/(a[1]);}else{r=/*EPP_MEM*/(a[0]);}return r;}"),
subject(9,"array-loop-write","int mw09(int x){int a[3];int i=0;int s=0;/*EPP_MEM*/(a[0])=1;/*EPP_MEM*/(a[1])=2;/*EPP_MEM*/(a[2])=3;for(i=0;i<3;i=i+1){/*EPP_MEM*/(a[i])=/*EPP_MEM*/(a[i])+1;s=s+/*EPP_MEM*/(a[i]);}return s;}"),
subject(10,"array-two-branch","int mw10(int x){int a[3];int r=0;/*EPP_MEM*/(a[0])=1;/*EPP_MEM*/(a[1])=2;/*EPP_MEM*/(a[2])=3;if(x>1){r=/*EPP_MEM*/(a[0])+/*EPP_MEM*/(a[2]);}else{r=/*EPP_MEM*/(a[1]);}return r;}"),
subject(11,"three-read-branch","int mw11(int x){int a[3];int r=0;/*EPP_MEM*/(a[0])=1;/*EPP_MEM*/(a[1])=2;/*EPP_MEM*/(a[2])=3;if(x>=0){r=/*EPP_MEM*/(a[0])+/*EPP_MEM*/(a[1])+/*EPP_MEM*/(a[2]);}else{r=/*EPP_MEM*/(a[2]);}return r;}"),
subject(12,"two-arrays","int mw12(int x,int y){int a[2];int b[2];int r=0;/*EPP_MEM*/(a[0])=1;/*EPP_MEM*/(a[1])=2;/*EPP_MEM*/(b[0])=3;/*EPP_MEM*/(b[1])=4;if(x>y){r=/*EPP_MEM*/(a[0])+/*EPP_MEM*/(a[1])+/*EPP_MEM*/(b[0])+/*EPP_MEM*/(b[1]);}else{r=/*EPP_MEM*/(a[0])+/*EPP_MEM*/(b[0]);}return r;}"),
subject(13,"nested-loops","int mw13(int x){int a[4];int i=0;int j=0;int s=0;/*EPP_MEM*/(a[0])=x;/*EPP_MEM*/(a[1])=x+1;/*EPP_MEM*/(a[2])=x+2;/*EPP_MEM*/(a[3])=x+3;for(i=0;i<2;i=i+1){for(j=0;j<2;j=j+1){s=s+/*EPP_MEM*/(a[i*2+j]);}}return s;}"),
subject(14,"input-bounded-loop","int mw14(int n){int a[3];int i=0;int s=0;/*EPP_MEM*/(a[0])=n;/*EPP_MEM*/(a[1])=n+1;/*EPP_MEM*/(a[2])=n+2;while((i<n)&&(i<3)){s=s+/*EPP_MEM*/(a[i]);i=i+1;}return s;}",5),
subject(15,"memory-condition","int mw15(int x){int a[2];int r=0;/*EPP_MEM*/(a[0])=x;/*EPP_MEM*/(a[1])=x+1;if(/*EPP_MEM*/(a[0])>=0){r=/*EPP_MEM*/(a[0])+/*EPP_MEM*/(a[1]);}else{r=/*EPP_MEM*/(a[1]);}return r;}"),
subject(16,"conditional-writes","int mw16(int x){int a[3];int r=0;/*EPP_MEM*/(a[0])=x;/*EPP_MEM*/(a[1])=0;/*EPP_MEM*/(a[2])=0;if(x>0){/*EPP_MEM*/(a[1])=x+1;/*EPP_MEM*/(a[2])=x+2;r=/*EPP_MEM*/(a[1])+/*EPP_MEM*/(a[2]);}else{r=/*EPP_MEM*/(a[0]);}return r;}"),
subject(17,"sequential-branches","int mw17(int x,int y){int a[3];int r=0;/*EPP_MEM*/(a[0])=x;/*EPP_MEM*/(a[1])=y;/*EPP_MEM*/(a[2])=x+y;if(x>0){r=r+/*EPP_MEM*/(a[0]);}else{r=r+/*EPP_MEM*/(a[1]);}if(y>0){r=r+/*EPP_MEM*/(a[0])+/*EPP_MEM*/(a[1]);}else{r=r+/*EPP_MEM*/(a[2]);}return r;}"),
subject(18,"else-if","int mw18(int x){int a[4];int r=0;/*EPP_MEM*/(a[0])=x;/*EPP_MEM*/(a[1])=x+1;/*EPP_MEM*/(a[2])=x+2;/*EPP_MEM*/(a[3])=x+3;if(x>1){r=/*EPP_MEM*/(a[0])+/*EPP_MEM*/(a[1])+/*EPP_MEM*/(a[2]);}else{if(x==1){r=/*EPP_MEM*/(a[3])+/*EPP_MEM*/(a[2]);}else{r=/*EPP_MEM*/(a[0]);}}return r;}"),
subject(19,"array-condition-nested","int mw19(int x){int a[2];int r=0;/*EPP_MEM*/(a[0])=x;/*EPP_MEM*/(a[1])=1;if(/*EPP_MEM*/(a[0])>=0){if(x>1){r=/*EPP_MEM*/(a[0])+/*EPP_MEM*/(a[1]);}else{r=/*EPP_MEM*/(a[0]);}}else{r=/*EPP_MEM*/(a[1]);}return r;}"),
subject(20,"tie-paths","int mw20(int x){int a[2];int r=0;/*EPP_MEM*/(a[0])=x;/*EPP_MEM*/(a[1])=x+1;if(x>0){r=/*EPP_MEM*/(a[0])+/*EPP_MEM*/(a[1]);}else{r=/*EPP_MEM*/(a[1])+/*EPP_MEM*/(a[0]);}return r;}")
]

def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--cnip", type=Path, default=Path("./cnip"))
    ap.add_argument("--output-dir", type=Path, default=Path("maxmems-witness-results"))
    args = ap.parse_args()
    out = args.output_dir.resolve()
    out.mkdir(parents=True, exist_ok=True)
    subjects_dir = out/"subjects"
    subjects_dir.mkdir(exist_ok=True)
    rows = []
    for s in SUBJECTS:
        src = subjects_dir/f"{s['id']}.c"
        src.write_text(s["source"]+"\n", encoding="utf-8")
        try:
            result = validate(src, s["function"], args.cnip.resolve(),
                              s["max_loop"], s["lo"], s["hi"])
            row = {"id":s["id"],"category":s["category"],**asdict(result)}
        except Exception as exc:
            row = {"id":s["id"],"category":s["category"],"status":"error","detail":str(exc)}
        rows.append(row)
        (out/f"{s['id']}.json").write_text(json.dumps(row,indent=2)+"\n")
        print(f"{s['id']}: {row['status']} dp={row.get('dp_mems','')} dyn={row.get('dynamic_witness_mems','')} oracle={row.get('dynamic_oracle_mems','')}")
    passed = sum(r["status"]=="pass" for r in rows)
    failed = sum(r["status"]=="fail" for r in rows)
    errors = len(rows)-passed-failed
    perf_rows = [r for r in rows if r.get("dp_reported_seconds") is not None
                 and r.get("dfs_reported_seconds") is not None]
    memo_rows = [r for r in rows if r.get("memo_lookups") is not None
                 and r.get("memo_hits") is not None]
    total_lookups = sum(int(r["memo_lookups"]) for r in memo_rows)
    total_hits = sum(int(r["memo_hits"]) for r in memo_rows)
    performance = {
        "subjects_with_timing": len(perf_rows),
        "dp_total_seconds": sum(float(r["dp_reported_seconds"]) for r in perf_rows),
        "dfs_total_seconds": sum(float(r["dfs_reported_seconds"]) for r in perf_rows),
        "memo_lookups": total_lookups,
        "memo_hits": total_hits,
        "memo_hit_rate": (total_hits / total_lookups) if total_lookups else 0.0,
    }
    summary = {"subjects":len(rows),"passed":passed,"failed":failed,"errors":errors,
               "all_passed":bool(rows) and passed==len(rows),
               "performance":performance,"results":rows}
    (out/"summary.json").write_text(json.dumps(summary,indent=2)+"\n")
    fields=["id","category","status","dp_mems","dfs_oracle_mems","dynamic_witness_mems",
            "dynamic_oracle_mems","feasible_paths","defined_oracle_inputs",
            "undefined_oracle_inputs","dp_reported_seconds","dfs_reported_seconds",
            "dp_wall_seconds","dfs_wall_seconds","memo_lookups","memo_hits",
            "memo_hit_rate","memo_stores","memo_entries","terminal_evals","detail"]
    with (out/"summary.csv").open("w",newline="",encoding="utf-8") as fh:
        w=csv.DictWriter(fh,fieldnames=fields,extrasaction="ignore");w.writeheader();w.writerows(rows)
    md=["# Independent MaxMEMS witness validation","",
        f"- Subjects: **{len(rows)}**",f"- Passed: **{passed}**",
        f"- Failed: **{failed}**",f"- Errors: **{errors}**",
        f"- DP total reported time: **{performance['dp_total_seconds']:.6f} s**",
        f"- DFS total reported time: **{performance['dfs_total_seconds']:.6f} s**",
        f"- Memo hits/lookups: **{performance['memo_hits']}/{performance['memo_lookups']}** "
        f"({performance['memo_hit_rate']:.6f})","",
        "| ID | Category | DP | DFS max | Dynamic witness | Dynamic oracle | Status |",
        "|---|---|---:|---:|---:|---:|---|"]
    for r in rows:
        md.append(f"| {r['id']} | {r['category']} | {r.get('dp_mems','')} | {r.get('dfs_oracle_mems','')} | {r.get('dynamic_witness_mems','')} | {r.get('dynamic_oracle_mems','')} | {r['status']} |")
    (out/"summary.md").write_text("\n".join(md)+"\n",encoding="utf-8")
    print(json.dumps({k:summary[k] for k in ("subjects","passed","failed","errors","all_passed")}))
    return 0 if summary["all_passed"] else 1

if __name__ == "__main__":
    sys.exit(main())
