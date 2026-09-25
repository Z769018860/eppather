#!/usr/bin/env python3
"""Profile MaxMEMS search reuse, DP-vs-DFS time, and a flow-only structural baseline."""
from __future__ import annotations

import argparse
import csv
import json
import os
import re
import statistics
import subprocess
import sys
import tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from maxmems_witness_experiment import SUBJECTS

FLOAT = r"([0-9]+(?:\.[0-9]+)?(?:[eE][+-]?[0-9]+)?)"
DP_TIME_RE = re.compile(r"(?m)^\[DP TIME COST\]:\s*" + FLOAT + r"\s+seconds$")
DFS_TIME_RE = re.compile(r"(?m)^\[DFS TIME COST\]:\s*" + FLOAT + r"\s+seconds$")
DP_MEM_RE = re.compile(r"(?m)^MEMS:\s*(-?\d+)$")
DFS_MEM_RE = re.compile(r"(?m)^\[DFS MAX MEMS\]:\s*(-?\d+)$")

EXTRA_SUBJECTS = [
    {
        "id": "mb01", "category": "correlated-branches", "function": "mb01",
        "max_loop": 4,
        "source": "int mb01(int x){int a[5];int r=0;a[0]=x;a[1]=x+1;a[2]=x+2;a[3]=x+3;a[4]=x+4;if(x>0){r=a[0]+a[1];}if(x<=0){r=r+a[2]+a[3]+a[4];}return r;}",
    },
    {
        "id": "mb02", "category": "equality-conflict", "function": "mb02",
        "max_loop": 4,
        "source": "int mb02(int x){int a[6];int r=0;a[0]=x;a[1]=1;a[2]=2;a[3]=3;a[4]=4;a[5]=5;if(x==0){r=a[0]+a[1]+a[2];}if(x!=0){r=r+a[3]+a[4]+a[5];}return r;}",
    },
    {
        "id": "mb03", "category": "range-conflict", "function": "mb03",
        "max_loop": 4,
        "source": "int mb03(int x){int a[5];int r=0;a[0]=x;a[1]=1;a[2]=2;a[3]=3;a[4]=4;if(x>5){r=a[0]+a[1]+a[2];}if(x<0){r=r+a[3]+a[4];}return r;}",
    },
    {
        "id": "mb04", "category": "three-way-correlation", "function": "mb04",
        "max_loop": 4,
        "source": "int mb04(int x){int a[6];int r=0;a[0]=x;a[1]=1;a[2]=2;a[3]=3;a[4]=4;a[5]=5;if(x>0){r=a[0]+a[1];}if(x==0){r=r+a[2]+a[3];}if(x<0){r=r+a[4]+a[5];}return r;}",
    },
    {
        "id": "mb05", "category": "loop-exit-correlation", "function": "mb05",
        "max_loop": 4,
        "source": "int mb05(int n){int a[4];int i=0;int r=0;a[0]=n;a[1]=1;a[2]=2;a[3]=3;while((i<n)&&(i<2)){r=r+a[i];i=i+1;}if(n<=0){r=r+a[2]+a[3];}return r;}",
    },
]


def env_for(cnip: Path, extra: dict[str, str] | None = None) -> dict[str, str]:
    env = os.environ.copy()
    dirs = [
        cnip.parent,
        cnip.parent / "C",
        cnip.parent / "common",
        cnip.parent / "libParser/z3/bin",
        cnip.parent / "lpsolve",
    ]
    env["LD_LIBRARY_PATH"] = ":".join(map(str, dirs)) + ":" + env.get("LD_LIBRARY_PATH", "")
    env["EPPATHER_MAXMEMS_CORE_ONLY"] = "1"
    env["EPPATHER_PREFIX_FEASIBILITY"] = "0"
    if extra:
        env.update(extra)
    return env


def run_mode(
    cnip: Path,
    src: Path,
    max_loop: int,
    max_paths: int,
    flag: str,
    cwd: Path,
    timeout: int,
    extra_env: dict[str, str] | None = None,
) -> subprocess.CompletedProcess[str]:
    cmd = [
        str(cnip),
        flag,
        "--maxloop", str(max_loop),
        "--maxpaths", str(max_paths),
        str(src),
    ]
    return subprocess.run(
        cmd,
        cwd=cwd,
        env=env_for(cnip, extra_env),
        text=True,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        timeout=timeout,
        check=False,
    )


def scalar(text: str, label: str, cast=int):
    m = re.search(r"(?m)^\[" + re.escape(label) + r"\]:\s*([^\r\n]+)$", text)
    if not m:
        raise RuntimeError(f"missing [{label}]")
    value = m.group(1).strip()
    return cast(value)


def parse_dp(text: str) -> dict:
    tm = DP_TIME_RE.search(text)
    mm = DP_MEM_RE.search(text)
    if not tm or not mm:
        raise RuntimeError("missing DP MEMS/time output")
    return {
        "mems": int(mm.group(1)),
        "time_s": float(tm.group(1)),
        "calls": scalar(text, "DP SEARCH CALLS"),
        "memo_enabled": scalar(text, "DP MEMO ENABLED"),
        "memo_lookups": scalar(text, "DP MEMO LOOKUPS"),
        "memo_hits": scalar(text, "DP MEMO HITS"),
        "memo_misses": scalar(text, "DP MEMO MISSES"),
        "memo_hit_rate": scalar(text, "DP MEMO HIT RATE", float),
        "memo_states": scalar(text, "DP MEMO STATES"),
        "terminal_evals": scalar(text, "DP TERMINAL EVALS"),
        "terminal_infeasible": scalar(text, "DP TERMINAL INFEASIBLE"),
        "prefix_solver_calls": scalar(text, "DP PREFIX SOLVER CALLS"),
        "prefix_prunes": scalar(text, "DP PREFIX PRUNES"),
        "feasibility_mode": scalar(text, "DP FEASIBILITY MODE", str),
    }


def parse_dfs(text: str) -> dict:
    tm = DFS_TIME_RE.search(text)
    mm = DFS_MEM_RE.search(text)
    if not tm or not mm:
        raise RuntimeError("missing DFS MEMS/time output")
    return {"mems": int(mm.group(1)), "time_s": float(tm.group(1))}


def normalize_subjects() -> list[dict]:
    rows = []
    for s in SUBJECTS:
        rows.append({
            "id": s["id"],
            "category": s["category"],
            "function": s["function"],
            "source": s["source"],
            "max_loop": s["max_loop"],
            "group": "witness20",
        })
    for s in EXTRA_SUBJECTS:
        rows.append({**s, "group": "correlation5"})
    return rows


def one_subject(
    subject: dict,
    cnip: Path,
    root: Path,
    max_paths: int,
    timeout: int,
) -> dict:
    case = root / subject["id"]
    case.mkdir(parents=True, exist_ok=True)
    src = case / f"{subject['id']}.c"
    src.write_text(subject["source"] + "\n", encoding="utf-8")

    modes = {
        "dp": ("-g", {}),
        "no_memo": ("-g", {"EPPATHER_DISABLE_DP_MEMO": "1"}),
        "structural": (
            "-g",
            {
                "EPPATHER_DISABLE_DP_MEMO": "1",
                "EPPATHER_MAXMEMS_FEASIBILITY_BLIND": "1",
            },
        ),
        "dfs": ("-q", {}),
    }
    parsed = {}
    for name, (flag, extra) in modes.items():
        work = case / name
        work.mkdir(exist_ok=True)
        try:
            proc = run_mode(
                cnip, src, subject["max_loop"], max_paths,
                flag, work, timeout, extra,
            )
        except subprocess.TimeoutExpired:
            return {
                "id": subject["id"], "group": subject["group"],
                "category": subject["category"], "status": "timeout",
                "detail": f"{name} exceeded {timeout}s",
            }
        (case / f"{name}.stdout.txt").write_text(proc.stdout, encoding="utf-8")
        (case / f"{name}.stderr.txt").write_text(proc.stderr, encoding="utf-8")
        if proc.returncode != 0:
            return {
                "id": subject["id"], "group": subject["group"],
                "category": subject["category"], "status": "error",
                "detail": f"{name} rc={proc.returncode}: {(proc.stderr or proc.stdout)[-800:]}",
            }
        parsed[name] = parse_dfs(proc.stdout) if name == "dfs" else parse_dp(proc.stdout)

    failures = []
    if parsed["dp"]["mems"] != parsed["no_memo"]["mems"]:
        failures.append("memo on/off changed MaxMEMS")
    if parsed["dp"]["mems"] != parsed["dfs"]["mems"]:
        failures.append("DP differs from feasible DFS")
    if parsed["structural"]["mems"] < parsed["dp"]["mems"]:
        failures.append("flow-only baseline fell below feasible MaxMEMS")
    return {
        "id": subject["id"],
        "group": subject["group"],
        "category": subject["category"],
        "status": "pass" if not failures else "fail",
        "max_loop": subject["max_loop"],
        "dp_mems": parsed["dp"]["mems"],
        "no_memo_mems": parsed["no_memo"]["mems"],
        "dfs_mems": parsed["dfs"]["mems"],
        "structural_mems": parsed["structural"]["mems"],
        "structural_gap": parsed["structural"]["mems"] - parsed["dp"]["mems"],
        "dp_time_s": parsed["dp"]["time_s"],
        "no_memo_time_s": parsed["no_memo"]["time_s"],
        "dfs_time_s": parsed["dfs"]["time_s"],
        "structural_time_s": parsed["structural"]["time_s"],
        "dp_calls": parsed["dp"]["calls"],
        "memo_lookups": parsed["dp"]["memo_lookups"],
        "memo_hits": parsed["dp"]["memo_hits"],
        "memo_misses": parsed["dp"]["memo_misses"],
        "memo_hit_rate": parsed["dp"]["memo_hit_rate"],
        "memo_states": parsed["dp"]["memo_states"],
        "terminal_evals": parsed["dp"]["terminal_evals"],
        "terminal_infeasible": parsed["dp"]["terminal_infeasible"],
        "detail": "; ".join(failures),
    }


def aggregate(rows: list[dict]) -> dict:
    passed = [r for r in rows if r.get("status") == "pass"]
    if not passed:
        return {"subjects": len(rows), "passed": 0}
    def total(key: str) -> float:
        return sum(float(r[key]) for r in passed)
    def median(key: str) -> float:
        return statistics.median(float(r[key]) for r in passed)
    lookups = sum(int(r["memo_lookups"]) for r in passed)
    hits = sum(int(r["memo_hits"]) for r in passed)
    dp_total = total("dp_time_s")
    no_memo_total = total("no_memo_time_s")
    dfs_total = total("dfs_time_s")
    return {
        "subjects": len(rows),
        "passed": len(passed),
        "failed_or_error": len(rows) - len(passed),
        "memo_lookups": lookups,
        "memo_hits": hits,
        "memo_hit_rate": hits / lookups if lookups else 0.0,
        "dp_total_s": dp_total,
        "no_memo_total_s": no_memo_total,
        "dfs_total_s": dfs_total,
        "structural_total_s": total("structural_time_s"),
        "memo_on_vs_off_ratio": no_memo_total / dp_total if dp_total else None,
        "dfs_over_dp_ratio": dfs_total / dp_total if dp_total else None,
        "median_dp_s": median("dp_time_s"),
        "median_no_memo_s": median("no_memo_time_s"),
        "median_dfs_s": median("dfs_time_s"),
        "structural_gap_cases": sum(int(r["structural_gap"]) > 0 for r in passed),
        "structural_equal_cases": sum(int(r["structural_gap"]) == 0 for r in passed),
        "correlation_gap_cases": sum(
            r["group"] == "correlation5" and int(r["structural_gap"]) > 0
            for r in passed
        ),
    }


def write_outputs(out: Path, rows: list[dict], agg: dict) -> None:
    fields = [
        "id","group","category","status","max_loop",
        "dp_mems","no_memo_mems","dfs_mems","structural_mems","structural_gap",
        "dp_time_s","no_memo_time_s","dfs_time_s","structural_time_s",
        "dp_calls","memo_lookups","memo_hits","memo_misses","memo_hit_rate",
        "memo_states","terminal_evals","terminal_infeasible","detail",
    ]
    with (out / "methodology.csv").open("w", newline="", encoding="utf-8") as fh:
        w = csv.DictWriter(fh, fieldnames=fields, extrasaction="ignore")
        w.writeheader()
        w.writerows(rows)
    (out / "methodology.json").write_text(
        json.dumps({"aggregate": agg, "results": rows}, indent=2) + "\n",
        encoding="utf-8",
    )
    md = [
        "# MaxMEMS methodology profile", "",
        "This experiment holds the bounded CFG and MEMS objective fixed and compares:",
        "",
        "- exact path-sensitive search with memoization enabled;",
        "- the same search with memoization disabled;",
        "- exhaustive feasible DFS2;",
        "- a feasibility-blind flow-only structural maximum (IPET-style reference).",
        "",
        "The flow-only mode is an experiment baseline only; it is not a valid Eppather MaxMEMS result.",
        "",
        "## Aggregate", "",
        "| Metric | Result |", "|---|---:|",
    ]
    for k, v in agg.items():
        md.append(f"| {k} | {v} |")
    md += [
        "", "## Per subject", "",
        "| ID | Group | Memo hits/lookups | DP s | No-memo s | DFS s | Feasible MaxMEMS | Flow-only | Gap |",
        "|---|---|---:|---:|---:|---:|---:|---:|---:|",
    ]
    for r in rows:
        if r.get("status") != "pass":
            md.append(f"| {r['id']} | {r.get('group','')} | - | - | - | - | - | - | {r['status']} |")
            continue
        md.append(
            f"| {r['id']} | {r['group']} | {r['memo_hits']}/{r['memo_lookups']} | "
            f"{r['dp_time_s']:.6g} | {r['no_memo_time_s']:.6g} | {r['dfs_time_s']:.6g} | "
            f"{r['dp_mems']} | {r['structural_mems']} | {r['structural_gap']} |"
        )
    (out / "methodology.md").write_text("\n".join(md) + "\n", encoding="utf-8")


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--cnip", type=Path, default=Path("./cnip"))
    ap.add_argument("--output-dir", type=Path, default=Path("maxmems-methodology-results"))
    ap.add_argument("--max-paths", type=int, default=1000)
    ap.add_argument("--timeout", type=int, default=120)
    args = ap.parse_args()
    cnip = args.cnip.resolve()
    out = args.output_dir.resolve()
    out.mkdir(parents=True, exist_ok=True)
    rows = []
    with tempfile.TemporaryDirectory(prefix="eppather-methodology-") as td:
        root = Path(td)
        for subject in normalize_subjects():
            row = one_subject(subject, cnip, root, args.max_paths, args.timeout)
            rows.append(row)
            print(
                f"{subject['id']}: {row.get('status')} "
                f"memo={row.get('memo_hits','?')}/{row.get('memo_lookups','?')} "
                f"dp={row.get('dp_time_s','?')} dfs={row.get('dfs_time_s','?')} "
                f"gap={row.get('structural_gap','?')}"
            )
            case_dir = root / subject["id"]
            if case_dir.exists():
                target = out / subject["id"]
                target.mkdir(exist_ok=True)
                for item in case_dir.iterdir():
                    if item.is_file():
                        (target / item.name).write_bytes(item.read_bytes())
    agg = aggregate(rows)
    write_outputs(out, rows, agg)
    print(json.dumps(agg, sort_keys=True))
    return 0 if agg.get("passed") == len(rows) else 1


if __name__ == "__main__":
    raise SystemExit(main())
