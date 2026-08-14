#!/usr/bin/env python3
"""Run Eppather models against the original C function and compare branches."""
from __future__ import annotations

import argparse
import json
import os
import re
import subprocess
import sys
import tempfile
from dataclasses import asdict, dataclass
from pathlib import Path

FUNC_RE = re.compile(r"\b(?:int|long|short|unsigned|void)\s+(?P<name>[A-Za-z_]\w*)\s*\((?P<params>[^()]*)\)\s*\{", re.M)
PARAM_RE = re.compile(r"^\s*(?:signed\s+)?int\s+(?P<name>[A-Za-z_]\w*)\s*$")
MODEL_RE = re.compile(r"\bint\s+(?P<name>[A-Za-z_]\w*)\s*=\s*(?P<value>-?\d+)\s*;?")
COND_RE = re.compile(r"@\((.*?)\);", re.S)


@dataclass
class CaseResult:
    path_id: int
    status: str
    expected: list[int]
    actual: list[int]
    inputs: dict[str, int]
    detail: str = ""


class UndefinedBehaviorError(RuntimeError):
    """Concrete replay reached behavior for which ISO C defines no result."""


def signed_int32(value: int) -> int:
    if -(1 << 31) <= value < 0:
        return value
    if not 0 <= value <= 0xFFFFFFFF:
        raise ValueError(f"model value {value} is outside 32-bit range")
    return value if value < (1 << 31) else value - (1 << 32)


def parse_signature(source: str, requested: str | None) -> tuple[str, list[str]]:
    matches = [m for m in FUNC_RE.finditer(source) if not requested or m.group("name") == requested]
    if len(matches) != 1:
        raise ValueError("cannot select one entry function; pass --function")
    match = matches[0]
    params = []
    raw = match.group("params").strip()
    if raw and raw != "void":
        for item in raw.split(","):
            pm = PARAM_RE.match(item)
            if not pm:
                raise ValueError(f"unsupported parameter {item!r}; normalize pointers/arrays first")
            params.append(pm.group("name"))
    return match.group("name"), params


def parse_model(text: str, params: list[str], source: str = "") -> dict[str, int]:
    values = {m.group("name"): signed_int32(int(m.group("value"))) for m in MODEL_RE.finditer(text)}
    # Z3 omits unconstrained constants. Prefer zero, except for parameters used as
    # a divisor: one keeps concrete replay defined without changing path choices.
    divisor_params = {
        name for name in params
        if re.search(rf"(?:/|%)\s*\b{re.escape(name)}\b", source)
    }
    return {name: values.get(name, 1 if name in divisor_params else 0) for name in params}


def expected_outcomes(path: str) -> list[int]:
    outcomes = []
    for expr in COND_RE.findall(path):
        compact = re.sub(r"\s+", " ", expr.strip())
        outcomes.append(0 if compact.startswith("!(") and compact.endswith(")") else 1)
    return outcomes


def instrument_conditions(source: str, max_loop: int, function: str) -> str:
    counter = 0
    pattern = re.compile(r"\b(if|while)\s*\(([^{};]*)\)|\bfor\s*\(([^;]*);([^;]*);([^)]*)\)")

    def replace(match: re.Match[str]) -> str:
        nonlocal counter
        idx = counter
        counter += 1
        if match.group(1):
            keyword = match.group(1)
            tracer = "EPP_LOOP_TRACE" if keyword == "while" else "EPP_TRACE"
            prefix = f"epp_loop_count[{idx}] = 0; " if keyword == "while" else ""
            return f"{prefix}{keyword} ({tracer}({idx}, ({match.group(2)})))"
        condition = match.group(4).strip() or "1"
        return (f"epp_loop_count[{idx}] = 0; for ({match.group(3)}; "
                f"EPP_LOOP_TRACE({idx}, ({condition})); {match.group(5)})")

    match = next((m for m in FUNC_RE.finditer(source) if m.group("name") == function), None)
    if not match:
        raise ValueError(f"cannot instrument function {function!r}")
    opening = match.end() - 1
    depth, closing = 0, None
    for pos in range(opening, len(source)):
        if source[pos] == "{":
            depth += 1
        elif source[pos] == "}":
            depth -= 1
            if depth == 0:
                closing = pos
                break
    if closing is None:
        raise ValueError(f"unterminated function {function!r}")
    body = pattern.sub(replace, source[opening + 1:closing])
    guard = "\nint epp_trace_enabled = !epp_in_entry; epp_in_entry = 1;\n"
    return source[:opening + 1] + guard + body + source[closing:]


def run(cmd: list[str], cwd: Path, env: dict[str, str] | None = None) -> subprocess.CompletedProcess[str]:
    return subprocess.run(cmd, cwd=cwd, env=env, text=True, capture_output=True, timeout=120)


def concrete_trace(source: str, function: str, params: list[str], inputs: dict[str, int], work: Path, max_loop: int) -> list[int]:
    arguments = ", ".join(str(inputs[p]) for p in params)
    program = (
        '#include <stdio.h>\n'
        'static unsigned epp_loop_count[4096];\n'
        'static int epp_in_entry;\n'
        'static int epp_trace(int id,int v){printf("EPP_BRANCH %d %d\\n",id,!!v);return v;}\n'
        '#define EPP_TRACE(id,expr) (epp_trace_enabled ? epp_trace((id),(expr)) : (expr))\n'
        f'#define EPP_LOOP_TRACE(id,expr) (epp_trace_enabled ? epp_trace((id),(epp_loop_count[(id)]++ < {max_loop}) && !!(expr)) : (expr))\n'
        + instrument_conditions(source, max_loop, function)
        + f"\nint main(void){{(void){function}({arguments});return 0;}}\n"
    )
    cfile = work / "replay.c"
    cfile.write_text(program, encoding="utf-8")
    built = run(["cc", "-std=c11", "-O0",
                 "-fsanitize=undefined", "-fno-sanitize-recover=undefined",
                 str(cfile), "-o", "replay"], work)
    if built.returncode:
        raise RuntimeError("compile failed: " + built.stderr[-1500:])
    replay = run([str(work / "replay")], work)
    if replay.returncode:
        if "runtime error:" in replay.stderr:
            raise UndefinedBehaviorError(replay.stderr.strip().splitlines()[-1])
        raise RuntimeError(f"replay exited {replay.returncode}: {replay.stderr[-500:]}")
    return [int(m.group(1)) for m in re.finditer(r"^EPP_BRANCH\s+\d+\s+([01])$", replay.stdout, re.M)]


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("source", type=Path)
    ap.add_argument("--function")
    ap.add_argument("--cnip", type=Path, default=Path("./cnip"))
    ap.add_argument("--max-loop", type=int, default=3)
    ap.add_argument("--output", type=Path, default=Path("e2e-path-report.json"))
    args = ap.parse_args()
    source_path, cnip = args.source.resolve(), args.cnip.resolve()
    source = source_path.read_text(encoding="utf-8-sig")
    function, params = parse_signature(source, args.function)
    cases: list[CaseResult] = []

    with tempfile.TemporaryDirectory(prefix="eppather-e2e-") as temp:
        work = Path(temp)
        env = os.environ.copy()
        libdirs = [cnip.parent, cnip.parent / "C", cnip.parent / "common", cnip.parent / "libParser/z3/bin", cnip.parent / "lpsolve"]
        env["LD_LIBRARY_PATH"] = ":".join(map(str, libdirs)) + ":" + env.get("LD_LIBRARY_PATH", "")
        analysis = run([str(cnip), "-q", str(source_path), str(args.max_loop)], work, env)
        if analysis.returncode:
            raise RuntimeError(f"Eppather exited {analysis.returncode}: {analysis.stderr[-1500:]}")

        for result_file in sorted(work.glob(f"result_{function}_*.txt")):
            path_id = int(re.search(r"_(\d+)\.txt$", result_file.name).group(1))
            result_text = result_file.read_text(encoding="utf-8", errors="replace")
            if not re.search(r"(?m)^feasible$", result_text):
                continue
            path = (work / f"path_{function}_{path_id}.txt").read_text(encoding="utf-8", errors="replace")
            inputs, expected = parse_model(result_text, params, source), expected_outcomes(path)
            try:
                actual = concrete_trace(source, function, params, inputs, work, args.max_loop)
                status = "match" if actual == expected else "mismatch"
                detail = "" if status == "match" else "ordered branch outcomes differ"
            except UndefinedBehaviorError as exc:
                actual, status, detail = [], "undefined", str(exc)
            except Exception as exc:
                actual, status, detail = [], "error", str(exc)
            cases.append(CaseResult(path_id, status, expected, actual, inputs, detail))

    summary = {key: sum(c.status == key for c in cases) for key in ("match", "mismatch", "undefined", "error")}
    summary["total"] = len(cases)
    report = {"source": str(source_path), "function": function, "summary": summary, "cases": [asdict(c) for c in cases]}
    args.output.write_text(json.dumps(report, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    print(json.dumps(summary, ensure_ascii=False))
    return 0 if cases and all(c.status in ("match", "undefined") for c in cases) else 1


if __name__ == "__main__":
    sys.exit(main())
