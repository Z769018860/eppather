#!/usr/bin/env python3
"""
Generic LLM-driven iterative repair runner for parser/semantic failures.

Usage example:
  export OPENAI_API_KEY=...
  python3 tools/auto_iterative_fix_with_llm.py \
    --input experiment_results/cjson/cjson.compat.i \
    --workdir experiment_results/cjson \
    --cmd "./build/cnip -s --maxloop 1 --maxpaths 20 {input}" \
    --max-iters 6

The script:
1) Runs target command.
2) Extracts failure points from stderr/stdout.
3) Sends source + diagnostics + strict repair prompt to an LLM API.
4) Writes repaired file and retries.
5) Stops when command succeeds (rc == 0) or max-iters is reached.
"""
import argparse
import json
import os
import re
import subprocess
from pathlib import Path
from typing import List, Dict, Tuple

import requests


SYSTEM_PROMPT = """You are a senior C compatibility-repair engineer.
Task: minimally repair a C source file so a static analyzer parser can proceed.
Hard constraints:
1) Preserve control-flow/function-body semantics as much as possible.
2) Prioritize syntactic repair and declaration normalization.
3) Never invent unrelated business logic.
4) Keep edits minimal and deterministic.
5) Output ONLY the full repaired C source code, no markdown, no explanation.
"""


USER_PROMPT_TEMPLATE = """You need to repair a C source file for parser compatibility.

## Context
- Project: {project}
- Iteration: {iteration}
- Previous return code: {rc}
- Analyzer command: {command}

## Failure diagnostics
{diagnostics}

## Repair policy (strict)
1) Fix declaration fragments, orphan commas/semicolons, broken prototypes.
2) Normalize unsupported GNU/libc syntax conservatively.
3) If a line is clearly irrecoverable noise (e.g., broken extern fragment), remove it.
4) Keep function signatures and control-flow blocks intact whenever possible.
5) Prefer local edits around reported failing lines.
6) Do not delete whole functions unless parser-breakage cannot be solved otherwise.

## Input source (full text)
{source}
"""


def run_cmd(cmd: str, cwd: Path) -> Tuple[int, str]:
    p = subprocess.run(
        cmd, shell=True, cwd=str(cwd), text=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT
    )
    return p.returncode, p.stdout


def extract_fail_points(output: str, source_name: str, max_points: int = 30) -> List[Dict]:
    pts = []
    seen = set()
    for m in re.finditer(rf"{re.escape(source_name)}:(\d+):(\d+)\s+(error|warning):\s+([^\n]+)", output):
        item = {"line": int(m.group(1)), "col": int(m.group(2)), "type": m.group(3), "msg": m.group(4).strip()}
        key = (item["line"], item["col"], item["msg"])
        if key not in seen:
            pts.append(item)
            seen.add(key)
        if len(pts) >= max_points:
            return pts
    for m in re.finditer(r"line\s+(\d+):(\d+)\s+([^\n]+)", output):
        item = {"line": int(m.group(1)), "col": int(m.group(2)), "type": "parser", "msg": m.group(3).strip()}
        key = (item["line"], item["col"], item["msg"])
        if key not in seen:
            pts.append(item)
            seen.add(key)
        if len(pts) >= max_points:
            break
    return pts


def format_diagnostics(points: List[Dict], source_text: str) -> str:
    lines = source_text.splitlines()
    blocks = []
    for p in points:
        ln = p["line"]
        start = max(1, ln - 1)
        end = min(len(lines), ln + 1)
        ctx = []
        for i in range(start, end + 1):
            prefix = ">>" if i == ln else "  "
            ctx.append(f"{prefix} L{i}: {lines[i - 1]}")
        blocks.append(f"- {p['type']} at {ln}:{p['col']} {p['msg']}\n" + "\n".join(ctx))
    return "\n\n".join(blocks) if blocks else "(no precise line extracted; use overall output)"


def call_openai(base_url: str, api_key: str, model: str, system_prompt: str, user_prompt: str) -> str:
    url = base_url.rstrip("/") + "/chat/completions"
    payload = {
        "model": model,
        "temperature": 0.0,
        "messages": [
            {"role": "system", "content": system_prompt},
            {"role": "user", "content": user_prompt},
        ],
    }
    headers = {"Authorization": f"Bearer {api_key}", "Content-Type": "application/json"}
    r = requests.post(url, headers=headers, data=json.dumps(payload), timeout=180)
    r.raise_for_status()
    data = r.json()
    return data["choices"][0]["message"]["content"]


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--input", required=True, help="Input C file to repair iteratively.")
    ap.add_argument("--workdir", required=True, help="Working directory to run analyzer command.")
    ap.add_argument("--cmd", required=True, help="Analyzer command; use {input} placeholder.")
    ap.add_argument("--project", default="generic-c-project")
    ap.add_argument("--max-iters", type=int, default=6)
    ap.add_argument("--model", default=os.environ.get("OPENAI_MODEL", "gpt-4o-mini"))
    ap.add_argument("--base-url", default=os.environ.get("OPENAI_BASE_URL", "https://api.openai.com/v1"))
    args = ap.parse_args()

    api_key = os.environ.get("OPENAI_API_KEY")
    if not api_key:
        raise SystemExit("OPENAI_API_KEY is required")

    inp = Path(args.input).resolve()
    workdir = Path(args.workdir).resolve()
    original = inp.read_text(encoding="utf-8", errors="ignore")
    current = original

    for it in range(1, args.max_iters + 1):
        iter_file = workdir / f"{inp.stem}.iter{it}.c"
        iter_file.write_text(current, encoding="utf-8")
        cmd = args.cmd.format(input=str(iter_file))
        rc, out = run_cmd(cmd, workdir)
        (workdir / f"iter{it}.log").write_text(out, encoding="utf-8")
        print(f"[ITER {it}] rc={rc} file={iter_file.name}")
        if rc == 0:
            final_file = workdir / f"{inp.stem}.fixed.c"
            final_file.write_text(current, encoding="utf-8")
            print(f"[SUCCESS] fixed source: {final_file}")
            return

        points = extract_fail_points(out, iter_file.name)
        diagnostics = format_diagnostics(points, current)
        user_prompt = USER_PROMPT_TEMPLATE.format(
            project=args.project,
            iteration=it,
            rc=rc,
            command=cmd,
            diagnostics=diagnostics,
            source=current,
        )
        repaired = call_openai(args.base_url, api_key, args.model, SYSTEM_PROMPT, user_prompt)
        repaired = repaired.strip()
        if not repaired:
            raise SystemExit(f"[ITER {it}] LLM returned empty content")
        current = repaired + ("\n" if not repaired.endswith("\n") else "")

    final_file = workdir / f"{inp.stem}.last_attempt.c"
    final_file.write_text(current, encoding="utf-8")
    raise SystemExit(f"[FAILED] max iterations reached. Last attempt: {final_file}")


if __name__ == "__main__":
    main()

