#!/usr/bin/env python3
"""Validate Eppather MaxMEMS witnesses across the 266-program normalized corpus."""
from __future__ import annotations

import argparse
import csv
import json
import os
import re
import subprocess
import tempfile
from pathlib import Path

from e2e_path_validation import (
    UndefinedBehaviorError,
    concrete_trace,
    expected_outcomes,
    parse_model,
    parse_signature,
)

MEM_RE = re.compile(r"\\[mem\\]:(-?\\d+)")
DP_PATH_RE = re.compile(r"\\[MAX MEMS PATH\\]:\\s*\\n(.*?)\\nMEMS:\\s*(-?\\d+)", re.S)


def env_for(cnip: Path) -> dict[str, str]:
    env = os.environ.copy()
    dirs = [cnip.parent, cnip.parent / "C", cnip.parent / "common",
            cnip.parent / "libParser/z3/bin", cnip.parent / "lpsolve"]
    env["LD_LIBRARY_PATH"] = ":".join(map(str, dirs)) + ":" + env.get("LD_LIBRARY_PATH", "")
    return env


def run_cmd(cmd: list[str], cwd: Path, timeout: int, env: dict[str, str] | None = None):
    try:
        p = subprocess.run(cmd, cwd=cwd, env=env, text=True, capture_output=True, timeout=timeout)
        return {"status": "ok", "returncode": p.returncode, "stdout": p.stdout, "stderr": p.stderr}
    except subprocess.TimeoutExpired as exc:
        return {"status": "timeout", "returncode": 124,
                "stdout": exc.stdout or "", "stderr": exc.stderr or ""}


def parse_dp_blocks(text: str) -> list[dict]:
    blocks = []
    parts = text.split("[FUNCTION TAG]:")
    for part in parts[1:]:
        first, _, rest = part.partition("\n")
        tag = first.strip()
        m = DP_PATH_RE.search(rest)
        if not tag or not m:
            continue
        blocks.append({"function": tag, "path": m.group(1), "mems": int(m.group(2)),
                       "branches": expected_outcomes(m.group(1))})
    return blocks


def dfs_rows(work: Path, function: str) -> list[dict]:
    rows = []
    for rf in sorted(work.glob(f"result_{function}_*.txt")):
        txt = rf.read_text(encoding="utf-8", errors="replace")
        if not re.search(r"(?m)^feasible$", txt):
            continue
        mm = MEM_RE.search(txt)
        im = re.search(r"_(\\d+)\\.txt$", rf.name)
        if not mm or not im:
            continue
        pid = int(im.group(1))
        pf = work / f"path_{function}_{pid}.txt"
        if not pf.exists():
            continue
        path = pf.read_text(encoding="utf-8", errors="replace")
        rows.append({"path_id": pid, "mems": int(mm.group(1)),
                     "branches": expected_outcomes(path), "result_text": txt})
    return rows


def analyze_program(src: Path, cnip: Path, max_loop: int, max_paths: int,
                    timeout: int) -> tuple[dict, list[dict]]:
    source = src.read_text(encoding="utf-8-sig", errors="replace")
    prog = {
        "source": str(src), "status": "", "dp_status": "", "dfs_status": "",
        "dp_blocks": 0, "functions_checked": 0, "static_equal_functions": 0,
        "static_mismatch_functions": 0, "replay_match_functions": 0,
        "replay_unsupported_functions": 0, "replay_undefined_functions": 0,
        "replay_error_functions": 0, "hard_failure": 0, "detail": "",
    }
    functions = []
    with tempfile.TemporaryDirectory(prefix="eppather-maxmems266-") as td:
        root = Path(td)
        dpw, dfw, rpw = root / "dp", root / "dfs", root / "replay"
        dpw.mkdir(); dfw.mkdir(); rpw.mkdir()
        env = env_for(cnip)
        dp = run_cmd([str(cnip), "-g", str(src), str(max_loop)], dpw, timeout, env)
        dfs = run_cmd([str(cnip), "-q", str(src), str(max_loop), str(max_paths)],
                      dfw, timeout, env)
        prog["dp_status"] = dp["status"] if dp["status"] != "ok" else str(dp["returncode"])
        prog["dfs_status"] = dfs["status"] if dfs["status"] != "ok" else str(dfs["returncode"])
        if dp["status"] != "ok" or dp["returncode"] != 0:
            prog.update(status="dp_failed", hard_failure=1,
                        detail=(dp["stderr"] or dp["stdout"])[-500:].replace("\n", " "))
            return prog, functions
        if dfs["status"] != "ok" or dfs["returncode"] != 0:
            prog.update(status="dfs_failed", hard_failure=1,
                        detail=(dfs["stderr"] or dfs["stdout"])[-500:].replace("\n", " "))
            return prog, functions

        blocks = parse_dp_blocks(dp["stdout"])
        prog["dp_blocks"] = len(blocks)
        if not blocks:
            prog.update(status="dp_parse_error", hard_failure=1,
                        detail="no tagged MaxMEMS block in -g output")
            return prog, functions

        has_main = bool(re.search(r"\\bmain\\s*\\(", source))
        for block in blocks:
            tag = block["function"]
            row = {
                "source": str(src), "function": tag, "dp_mems": block["mems"],
                "dfs_max_mems": "", "feasible_paths": 0, "static_equal": 0,
                "witness_found": 0, "replay_status": "not_attempted", "detail": "",
            }
            rows = dfs_rows(dfw, tag)
            row["feasible_paths"] = len(rows)
            if block["mems"] < 0:
                if not rows:
                    row["static_equal"] = 1
                    row["replay_status"] = "no_feasible_path"
                    prog["static_equal_functions"] += 1
                else:
                    row["detail"] = "DP reports no feasible path but DFS has feasible paths"
                    prog["static_mismatch_functions"] += 1
                functions.append(row)
                continue
            if not rows:
                row["detail"] = "no feasible DFS2 path artifacts for tagged function"
                prog["static_mismatch_functions"] += 1
                functions.append(row)
                continue

            dfs_max = max(x["mems"] for x in rows)
            row["dfs_max_mems"] = dfs_max
            row["static_equal"] = int(dfs_max == block["mems"])
            if row["static_equal"]:
                prog["static_equal_functions"] += 1
            else:
                prog["static_mismatch_functions"] += 1
                row["detail"] = f"DP {block['mems']} != DFS {dfs_max}"

            candidates = [x for x in rows
                          if x["mems"] == block["mems"] and x["branches"] == block["branches"]]
            if not candidates:
                candidates = [x for x in rows if x["mems"] == block["mems"]]
            if not candidates:
                row["replay_status"] = "witness_not_found"
                row["detail"] = (row["detail"] + "; " if row["detail"] else "") +                                 "no feasible DFS model realizes DP MaxMEMS"
                functions.append(row)
                continue
            row["witness_found"] = 1

            if has_main or tag == "main":
                row["replay_status"] = "unsupported_main"
                prog["replay_unsupported_functions"] += 1
                functions.append(row)
                continue
            try:
                selected, params = parse_signature(source, tag)
            except Exception as exc:
                row["replay_status"] = "unsupported_signature"
                row["detail"] = (row["detail"] + "; " if row["detail"] else "") + str(exc)
                prog["replay_unsupported_functions"] += 1
                functions.append(row)
                continue

            witness = candidates[0]
            inputs = parse_model(witness["result_text"], params, source)
            try:
                actual = concrete_trace(source, selected, params, inputs, rpw, max_loop)
                if actual == block["branches"]:
                    row["replay_status"] = "match"
                    prog["replay_match_functions"] += 1
                else:
                    row["replay_status"] = "mismatch"
                    row["detail"] = (row["detail"] + "; " if row["detail"] else "") +                                     "ordered concrete branch trace differs from DP witness"
            except UndefinedBehaviorError as exc:
                row["replay_status"] = "undefined"
                row["detail"] = (row["detail"] + "; " if row["detail"] else "") + str(exc)
                prog["replay_undefined_functions"] += 1
            except Exception as exc:
                row["replay_status"] = "error"
                row["detail"] = (row["detail"] + "; " if row["detail"] else "") + str(exc)
                prog["replay_error_functions"] += 1
            functions.append(row)

        prog["functions_checked"] = len(functions)
        replay_mismatch = sum(r["replay_status"] == "mismatch" for r in functions)
        witness_missing = sum(r["replay_status"] == "witness_not_found" for r in functions)
        if prog["static_mismatch_functions"] or replay_mismatch or witness_missing:
            prog["status"] = "mismatch"
            prog["hard_failure"] = 1
        elif prog["replay_match_functions"] and not (
            prog["replay_unsupported_functions"] or prog["replay_undefined_functions"] or
            prog["replay_error_functions"]
        ):
            prog["status"] = "pass_full_replay"
        elif prog["replay_match_functions"]:
            prog["status"] = "pass_partial_replay"
        else:
            prog["status"] = "pass_static_only"
    return prog, functions


def write_csv(path: Path, rows: list[dict], fields: list[str]):
    with path.open("w", newline="", encoding="utf-8") as fh:
        w = csv.DictWriter(fh, fieldnames=fields, extrasaction="ignore")
        w.writeheader(); w.writerows(rows)


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--cnip", type=Path, default=Path("./cnip"))
    ap.add_argument("--corpus", type=Path, default=Path("testcase/output_complete2"))
    ap.add_argument("--output-dir", type=Path, default=Path("maxmems-266-results"))
    ap.add_argument("--max-loop", type=int, default=3)
    ap.add_argument("--max-paths", type=int, default=1000)
    ap.add_argument("--timeout", type=int, default=120)
    ap.add_argument("--shard-index", type=int, default=0)
    ap.add_argument("--shard-count", type=int, default=1)
    args = ap.parse_args()

    cnip, corpus = args.cnip.resolve(), args.corpus.resolve()
    files = sorted(corpus.glob("*.c"))
    selected = [p for i, p in enumerate(files) if i % args.shard_count == args.shard_index]
    out = args.output_dir.resolve(); out.mkdir(parents=True, exist_ok=True)
    programs, functions = [], []
    for pos, src in enumerate(selected, 1):
        prog, funcs = analyze_program(src, cnip, args.max_loop, args.max_paths, args.timeout)
        programs.append(prog); functions.extend(funcs)
        print(f"[{pos}/{len(selected)}] {src.name}: {prog['status']} "
              f"static={prog['static_equal_functions']}/{prog['functions_checked']} "
              f"replay={prog['replay_match_functions']}")
    suffix = f"shard{args.shard_index}"
    program_fields = ["source","status","dp_status","dfs_status","dp_blocks","functions_checked",
                      "static_equal_functions","static_mismatch_functions","replay_match_functions",
                      "replay_unsupported_functions","replay_undefined_functions",
                      "replay_error_functions","hard_failure","detail"]
    function_fields = ["source","function","dp_mems","dfs_max_mems","feasible_paths","static_equal",
                       "witness_found","replay_status","detail"]
    write_csv(out / f"programs-{suffix}.csv", programs, program_fields)
    write_csv(out / f"functions-{suffix}.csv", functions, function_fields)
    summary = {
        "shard_index": args.shard_index, "shard_count": args.shard_count,
        "corpus_files_seen": len(files), "programs_in_shard": len(programs),
        "hard_failures": sum(int(r["hard_failure"]) for r in programs),
        "static_equal_programs": sum(r["functions_checked"] > 0 and
                                     r["static_mismatch_functions"] == 0 for r in programs),
        "replay_match_functions": sum(r["replay_match_functions"] for r in programs),
    }
    (out / f"summary-{suffix}.json").write_text(json.dumps(summary, indent=2) + "\n",
                                                encoding="utf-8")
    print("MAXMEMS266_SHARD " + json.dumps(summary, sort_keys=True))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
