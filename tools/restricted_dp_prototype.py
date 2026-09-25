#!/usr/bin/env python3
"""Exact DP for a deliberately restricted, independently guarded C family.

This is a proof-of-concept separate from cnip -g. Each condition is a fresh
unconstrained scalar Boolean, both arms only read fixed array cells and update
an accumulator which is never used by later guards. The suffix optimum is
therefore independent of earlier choices. No general C state merge is claimed.
"""
import argparse
import csv
import os
import re
import subprocess
from pathlib import Path


def source(n: int, instrumented: bool) -> str:
    params = ", ".join(f"int b{i}" for i in range(n))
    lines = []
    if instrumented:
        lines += ["int reads = 0;", "int a[2] = {1, 2};",
                  "int rd(int i) { reads++; return a[i]; }"]
    lines += [f"int witness({params}) {{", "  int s = 0;"]
    if not instrumented:
        lines += ["  int a[2] = {1, 2};"]
    for i in range(n):
        a0 = "rd(0)" if instrumented else "a[0]"
        a1 = "rd(1)" if instrumented else "a[1]"
        lines += [f"  if (b{i}) {{",
                  f"    s = s + {a0};",
                  f"    s = s + {a1};",
                  "  } else {",
                  f"    s = s + {a0};",
                  "  }"]
    lines += ["  return s;", "}"]
    if instrumented:
        lines += ["#include <stdio.h>", "int main(void) {",
                  "  int largest = -1, value = -1;",
                  f"  for (unsigned mask = 0; mask < (1u << {n}); ++mask) {{",
                  "    reads = 0;",
                  f"    int got = witness({', '.join(f'(mask >> {i}) & 1u' for i in range(n))});",
                  "    if (reads > largest) { largest = reads; value = got; }",
                  "  }",
                  '  printf("%d %d\\n", largest, value);',
                  "  return 0;", "}"]
    return "\n".join(lines) + "\n"


def dp_exact(n: int) -> tuple[int, int, str]:
    # Each layer has two feasible successors with equal post-state relevance.
    # The branch's local access costs are 2 and 1, and later guards are fresh.
    value, states, trace = 0, 1, ""
    for _ in range(n):
        value += max(2, 1)
        states += 1
        trace += "1"
    return value, states, trace


def dfs_exact(n: int) -> tuple[int, int]:
    explored = 0
    def visit(i: int, cost: int) -> int:
        nonlocal explored
        explored += 1
        if i == n:
            return cost
        return max(visit(i + 1, cost + 2), visit(i + 1, cost + 1))
    return visit(0, 0), explored


def cnip_metric(label: str, text: str) -> str:
    found = re.findall(r"^\\[" + re.escape(label) + r"\\]:\\s*([^\\r\\n]+)", text, re.M)
    return found[-1].strip().split()[0] if found else ""


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--output-dir", type=Path, required=True)
    parser.add_argument("--cnip", type=Path)
    parser.add_argument("--sizes", type=int, nargs="+", default=[4, 8, 12])
    args = parser.parse_args()
    out = args.output_dir.resolve()
    out.mkdir(parents=True, exist_ok=True)
    rows = []
    for n in args.sizes:
        if not 1 <= n <= 16:
            parser.error("sizes must be 1..16 for independent concrete enumeration")
        c = out / f"independent_{n}.c"
        c.write_text(source(n, False))
        concrete = out / f"independent_{n}_instrumented.c"
        concrete.write_text(source(n, True))
        binary = out / f"instrumented_{n}"
        subprocess.run(["cc", "-O0", "-std=c11", str(concrete), "-o", str(binary)],
                       check=True, capture_output=True)
        observed = subprocess.check_output([str(binary)], text=True).split()
        dp, states, witness = dp_exact(n)
        dfs, visits = dfs_exact(n)
        row = {"branches": n, "dp_suffix_states": states,
               "dfs_prefix_states": visits, "dp_accesses_excluding_init": dp,
               "dfs_accesses_excluding_init": dfs,
               "source_instrumented_accesses_excluding_init": int(observed[0]),
               "dp_witness": witness, "cnip_dfs_mems": "", "cnip_prefix_mems": ""}
        if args.cnip and n <= 4:
            env = dict(os.environ, EPPATHER_MAXMEMS_CORE_ONLY="1",
                       EPPATHER_LOOP_SCC_ACCELERATE="0",
                       EPPATHER_LOOP_SCC_MEMORY_ACCELERATE="0")
            for flag, field, metric in [
                ("-q", "cnip_dfs_mems", "DFS MAX MEMS"),
                ("-g", "cnip_prefix_mems", "DP INTERNAL MEMS"),
            ]:
                run = subprocess.run([str(args.cnip.resolve()), flag,
                                      "--maxloop", "3", "--maxpaths", "0", str(c)],
                                     cwd=out, env=env, text=True,
                                     stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                                     timeout=90)
                (out / f"{n}_{flag[1:]}.log").write_text(run.stdout)
                if run.returncode:
                    raise RuntimeError(f"cnip {flag} failed for n={n}")
                row[field] = cnip_metric(metric, run.stdout)
            if not row["cnip_dfs_mems"] or row["cnip_dfs_mems"] != row["cnip_prefix_mems"]:
                raise AssertionError(f"cnip mismatch: {row}")
        if not dp == dfs == int(observed[0]):
            raise AssertionError(f"restricted DP / DFS / source mismatch: {row}")
        rows.append(row)
        print(row, flush=True)
    with (out / "restricted_dp.csv").open("w", newline="") as f:
        writer = csv.DictWriter(f, fieldnames=list(rows[0]))
        writer.writeheader()
        writer.writerows(rows)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
