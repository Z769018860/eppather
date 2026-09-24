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
    FUNC_RE,
    UndefinedBehaviorError,
    concrete_trace,
    expected_outcomes,
    parse_model,
    parse_signature,
)

MEM_RE = re.compile(r"\[mem\]:(-?\d+)")
DP_PATH_RE = re.compile(
    r"\\[MAX MEMS PATH\\]:\\s*\\n(.*?)(?=\\n(?:\\[DP INTERNAL MEMS\\]|\\[DP SCORE DELTA\\]|MEMS:))",
    re.S,
)
DP_MEM_RE = re.compile(r"(?m)^MEMS:\\s*(-?\\d+)")
DP_INTERNAL_RE = re.compile(r"(?m)^\\[DP INTERNAL MEMS\\]:\\s*(-?\\d+)")
DP_DELTA_RE = re.compile(r"(?m)^\\[DP SCORE DELTA\\]:\\s*(-?\\d+)")


def env_for(cnip: Path) -> dict[str, str]:
    env = os.environ.copy()
    dirs = [cnip.parent, cnip.parent / "C", cnip.parent / "common",
            cnip.parent / "libParser/z3/bin", cnip.parent / "lpsolve"]
    env["LD_LIBRARY_PATH"] = ":".join(map(str, dirs)) + ":" + env.get("LD_LIBRARY_PATH", "")
    return env


def _text(value) -> str:
    if value is None:
        return ""
    if isinstance(value, bytes):
        return value.decode("utf-8", errors="replace")
    return str(value)


def run_cmd(cmd: list[str], cwd: Path, timeout: int, env: dict[str, str] | None = None):
    try:
        p = subprocess.run(cmd, cwd=cwd, env=env, text=True, capture_output=True, timeout=timeout)
        return {"status": "ok", "returncode": p.returncode,
                "stdout": _text(p.stdout), "stderr": _text(p.stderr)}
    except subprocess.TimeoutExpired as exc:
        return {"status": "timeout", "returncode": 124,
                "stdout": _text(exc.stdout), "stderr": _text(exc.stderr)}


def parse_dp_blocks(text: str) -> list[dict]:
    blocks = []
    parts = text.split("[FUNCTION TAG]:")
    for part in parts[1:]:
        first, _, rest = part.partition("\n")
        tag = first.strip()
        path_m = DP_PATH_RE.search(rest)
        mem_m = DP_MEM_RE.search(rest)
        if not tag or not path_m or not mem_m:
            continue
        path = path_m.group(1).rstrip()
        internal_m = DP_INTERNAL_RE.search(rest)
        delta_m = DP_DELTA_RE.search(rest)
        blocks.append({
            "function": tag,
            "path": path,
            "mems": int(mem_m.group(1)),
            "internal_mems": int(internal_m.group(1)) if internal_m else "",
            "score_delta": int(delta_m.group(1)) if delta_m else "",
            "branches": expected_outcomes(path),
        })
    return blocks


def rename_function_definition(source: str, old: str, new: str) -> str:
    """Rename one function definition without rewriting unrelated identifiers."""
    for match in FUNC_RE.finditer(source):
        if match.group("name") == old:
            start, end = match.span("name")
            return source[:start] + new + source[end:]
    raise ValueError(f"cannot find function definition {old!r}")


def load_manifest(manifest: Path, corpus: Path) -> list[Path]:
    """Load the frozen SANER corpus and reject drift or duplicate entries."""
    repo_root = Path(__file__).resolve().parents[1]
    files: list[Path] = []
    seen: set[Path] = set()
    for raw in manifest.read_text(encoding="utf-8").splitlines():
        line = raw.strip()
        if not line or line.startswith("#"):
            continue
        candidate = Path(line)
        if not candidate.is_absolute():
            candidate = (repo_root / candidate).resolve()
        else:
            candidate = candidate.resolve()
        if candidate in seen:
            raise ValueError(f"duplicate manifest entry: {line}")
        if not candidate.is_file():
            raise FileNotFoundError(f"manifest entry does not exist: {line}")
        if candidate.suffix != ".c":
            raise ValueError(f"non-C manifest entry: {line}")
        if candidate.parent != corpus.resolve():
            raise ValueError(f"manifest entry outside corpus: {line}")
        seen.add(candidate)
        files.append(candidate)
    return files


def dfs_rows(work: Path, function: str) -> list[dict]:
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
        rows.append({"path_id": pid, "mems": int(mm.group(1)),
                     "branches": expected_outcomes(path), "result_text": txt})
    return rows


def analyze_program(src: Path, cnip: Path, max_loop: int, max_paths: int,
                    timeout: int, retry_timeout: int) -> tuple[dict, list[dict]]:
    source = src.read_text(encoding="utf-8-sig", errors="replace")
    prog = {
        "source": str(src), "status": "", "dp_status": "", "dfs_status": "",
        "dp_blocks": 0, "functions_checked": 0, "static_equal_functions": 0,
        "static_mismatch_functions": 0, "replay_match_functions": 0,
        "replay_unsupported_functions": 0, "replay_undefined_functions": 0,
        "replay_error_functions": 0, "path_limit_functions": 0,
        "dp_retried": 0, "dfs_retried": 0,
        "hard_failure": 0, "detail": "",
    }
    functions = []
    with tempfile.TemporaryDirectory(prefix="eppather-maxmems266-") as td:
        root = Path(td)
        dpw, dfw, rpw = root / "dp", root / "dfs", root / "replay"
        dpw.mkdir(); dfw.mkdir(); rpw.mkdir()
        env = env_for(cnip)
        dp = run_cmd([str(cnip), "-g", str(src), str(max_loop)], dpw, timeout, env)
        if dp["status"] == "timeout" and retry_timeout > timeout:
            prog["dp_retried"] = 1
            dp = run_cmd([str(cnip), "-g", str(src), str(max_loop)],
                         dpw, retry_timeout, env)
        prog["dp_status"] = dp["status"] if dp["status"] != "ok" else str(dp["returncode"])
        if dp["status"] != "ok" or dp["returncode"] != 0:
            prog.update(status="dp_failed", hard_failure=1,
                        detail=(dp["stderr"] or dp["stdout"])[-500:].replace("\n", " "))
            return prog, functions

        blocks = parse_dp_blocks(dp["stdout"])
        prog["dp_blocks"] = len(blocks)
        if not blocks:
            prog.update(status="dp_parse_error", hard_failure=1,
                        detail="no tagged MaxMEMS block in -g output")
            return prog, functions

        # Do not spend the full DFS budget when the frontend/DP stage did not
        # produce a usable MaxMEMS result.
        dfs = run_cmd([str(cnip), "-q", str(src), str(max_loop), str(max_paths)],
                      dfw, timeout, env)
        if dfs["status"] == "timeout" and retry_timeout > timeout:
            prog["dfs_retried"] = 1
            # Retry in a fresh directory so partial artifacts from the first
            # timed-out enumeration cannot contaminate the second result.
            for p in dfw.iterdir():
                if p.is_file():
                    p.unlink()
            dfs = run_cmd([str(cnip), "-q", str(src), str(max_loop), str(max_paths)],
                          dfw, retry_timeout, env)
        prog["dfs_status"] = dfs["status"] if dfs["status"] != "ok" else str(dfs["returncode"])
        if dfs["status"] != "ok" or dfs["returncode"] != 0:
            prog.update(status="dfs_failed", hard_failure=1,
                        detail=(dfs["stderr"] or dfs["stdout"])[-500:].replace("\n", " "))
            return prog, functions

        has_main = bool(re.search(r"\bmain\s*\(", source))
        for block in blocks:
            tag = block["function"]
            row = {
                "source": str(src), "function": tag, "dp_mems": block["mems"],
                "dp_internal_mems": block.get("internal_mems", ""),
                "dp_score_delta": block.get("score_delta", ""),
                "dfs_max_mems": "", "feasible_paths": 0, "paths_enumerated": 0,
                "path_limit_hit": 0, "static_equal": 0, "witness_found": 0,
                "witness_inputs": "", "expected_branches": "", "actual_branches": "",
                "replay_status": "not_attempted", "detail": "",
            }
            rows = dfs_rows(dfw, tag)
            row["feasible_paths"] = len(rows)
            row["paths_enumerated"] = len(list(dfw.glob(f"result_{tag}_*.txt")))
            row["path_limit_hit"] = int(
                max_paths > 0 and row["paths_enumerated"] >= max_paths
            )
            prog["path_limit_functions"] += row["path_limit_hit"]
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

            replay_source = source
            replay_tag = tag
            if has_main:
                try:
                    if tag == "main":
                        replay_tag = "epp_target_main"
                        replay_source = rename_function_definition(
                            source, "main", replay_tag
                        )
                    else:
                        replay_source = rename_function_definition(
                            source, "main", "epp_original_main"
                        )
                except Exception as exc:
                    row["replay_status"] = "unsupported_main"
                    row["detail"] = (row["detail"] + "; " if row["detail"] else "") + str(exc)
                    prog["replay_unsupported_functions"] += 1
                    functions.append(row)
                    continue
            if re.search(r"\\bswitch\\s*\\(", replay_source):
                row["replay_status"] = "unsupported_switch"
                row["detail"] = (row["detail"] + "; " if row["detail"] else "") + \
                    "concrete replay does not instrument switch/case decisions"
                prog["replay_unsupported_functions"] += 1
                functions.append(row)
                continue
            try:
                selected, params = parse_signature(replay_source, replay_tag)
            except Exception as exc:
                row["replay_status"] = "unsupported_signature"
                row["detail"] = (row["detail"] + "; " if row["detail"] else "") + str(exc)
                prog["replay_unsupported_functions"] += 1
                functions.append(row)
                continue

            witness = candidates[0]
            inputs = parse_model(witness["result_text"], params, source)
            row["witness_inputs"] = json.dumps(inputs, sort_keys=True)
            row["expected_branches"] = json.dumps(block["branches"])
            try:
                actual = concrete_trace(replay_source, selected, params, inputs, rpw, max_loop)
                row["actual_branches"] = json.dumps(actual)
                if actual == block["branches"]:
                    row["replay_status"] = "match"
                    prog["replay_match_functions"] += 1
                else:
                    row["replay_status"] = "mismatch"
                    row["detail"] = (row["detail"] + "; " if row["detail"] else "") + \
                        "ordered concrete branch trace differs from DP witness"
            except UndefinedBehaviorError as exc:
                row["replay_status"] = "undefined"
                row["detail"] = (row["detail"] + "; " if row["detail"] else "") + str(exc)
                prog["replay_undefined_functions"] += 1
            except Exception as exc:
                msg = str(exc)
                if "compile failed:" in msg:
                    row["replay_status"] = "unsupported_compile"
                    prog["replay_unsupported_functions"] += 1
                else:
                    row["replay_status"] = "error"
                    prog["replay_error_functions"] += 1
                row["detail"] = (row["detail"] + "; " if row["detail"] else "") + msg
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
    ap.add_argument("--manifest", type=Path, default=Path("docs/maxmems-266-corpus-manifest.txt"))
    ap.add_argument("--expected-programs", type=int, default=266)
    ap.add_argument("--output-dir", type=Path, default=Path("maxmems-266-results"))
    ap.add_argument("--max-loop", type=int, default=3)
    ap.add_argument("--max-paths", type=int, default=1000)
    ap.add_argument("--timeout", type=int, default=120)
    ap.add_argument("--retry-timeout", type=int, default=300,
                    help="second-chance timeout used only after a timeout; <= --timeout disables retry")
    ap.add_argument("--shard-index", type=int, default=0)
    ap.add_argument("--shard-count", type=int, default=1)
    args = ap.parse_args()

    cnip, corpus = args.cnip.resolve(), args.corpus.resolve()
    manifest = args.manifest.resolve()
    files = load_manifest(manifest, corpus)
    if len(files) != args.expected_programs:
        raise RuntimeError(
            f"frozen corpus size mismatch: {len(files)} != {args.expected_programs}"
        )
    selected = [p for i, p in enumerate(files) if i % args.shard_count == args.shard_index]
    out = args.output_dir.resolve(); out.mkdir(parents=True, exist_ok=True)
    programs, functions = [], []
    suffix = f"shard{args.shard_index}"
    program_fields = ["source","status","dp_status","dfs_status","dp_blocks","functions_checked",
                      "static_equal_functions","static_mismatch_functions","replay_match_functions",
                      "replay_unsupported_functions","replay_undefined_functions",
                      "replay_error_functions","path_limit_functions","dp_retried","dfs_retried",
                      "hard_failure","detail"]
    function_fields = ["source","function","dp_mems","dp_internal_mems","dp_score_delta",
                       "dfs_max_mems","feasible_paths","paths_enumerated","path_limit_hit",
                       "static_equal","witness_found","witness_inputs","expected_branches",
                       "actual_branches","replay_status","detail"]

    for pos, src in enumerate(selected, 1):
        try:
            prog, funcs = analyze_program(
                src, cnip, args.max_loop, args.max_paths, args.timeout, args.retry_timeout
            )
        except Exception as exc:
            prog = {
                "source": str(src), "status": "harness_error", "dp_status": "", "dfs_status": "",
                "dp_blocks": 0, "functions_checked": 0, "static_equal_functions": 0,
                "static_mismatch_functions": 0, "replay_match_functions": 0,
                "replay_unsupported_functions": 0, "replay_undefined_functions": 0,
                "replay_error_functions": 0, "path_limit_functions": 0,
                "dp_retried": 0, "dfs_retried": 0,
                "hard_failure": 1, "detail": repr(exc),
            }
            funcs = []
        programs.append(prog); functions.extend(funcs)
        write_csv(out / f"programs-{suffix}.csv", programs, program_fields)
        write_csv(out / f"functions-{suffix}.csv", functions, function_fields)
        print(f"[{pos}/{len(selected)}] {src.name}: {prog['status']} "
              f"static={prog['static_equal_functions']}/{prog['functions_checked']} "
              f"replay={prog['replay_match_functions']}", flush=True)
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
