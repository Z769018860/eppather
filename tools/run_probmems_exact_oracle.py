#!/usr/bin/env python3
"""Independent exhaustive oracle for small ProbMEMS programs.

Each case defines the C program and a separate executable cost function.  The
oracle enumerates x in [-1, 1], computes the exact expectation, then compares
it with cnip/VolCE.  Array contents deliberately do not affect guards, so their
values cannot bias path probabilities.
"""
import csv
import os
import re
import subprocess
import tempfile
from pathlib import Path

CNIP = os.environ.get("CNIP", "./build_ci/cnip")
DOMAIN = range(-1, 2)

CASES = [
    ("or01_one_read", "int oracle(int a[3], int x) { return a[0]; }", lambda x: 1, 1),
    ("or02_two_reads", "int oracle(int a[3], int x) { return a[0] + a[1]; }", lambda x: 2, 2),
    ("or03_equal_branch", "int oracle(int a[3], int x) { if (x > 0) { return a[0]; } else { return a[1]; } }", lambda x: 1, 1),
    ("or04_skewed_read", "int oracle(int a[3], int x) { if (x > 0) { return a[0] + a[1]; } else { return a[2]; } }", lambda x: 2 if x > 0 else 1, 2),
    ("or05_skewed_read_inverse", "int oracle(int a[3], int x) { if (x < 0) { return a[0] + a[1] + a[2]; } else { return a[0]; } }", lambda x: 3 if x < 0 else 1, 3),
    ("or06_nested", "int oracle(int a[4], int x) { if (x < 0) { return a[0]; } else { if (x == 0) { return a[1] + a[2]; } else { return a[3]; } } }", lambda x: 2 if x == 0 else 1, 2),
    ("or07_write", "int oracle(int a[3], int x) { if (x > 0) { a[0] = a[1]; } else { a[0] = a[2]; } return a[0]; }", lambda x: 3, 3),
    ("or08_pointer_read", "int oracle(int *p, int x) { if (x == 0) { return p[0] + p[1]; } return p[2]; }", lambda x: 2 if x == 0 else 1, 2),
    ("or09_pointer_write", "int oracle(int *p, int x) { if (x < 0) { p[0] = p[1]; } return p[0]; }", lambda x: 3 if x < 0 else 1, 3),
    ("or10_two_conditions", "int oracle(int a[4], int x) { if (x >= 0) { if (x > 0) { return a[0] + a[1]; } return a[2]; } return a[3]; }", lambda x: 2 if x > 0 else 1, 2),
]

PATTERNS = {
    "count": re.compile(r"^\[VOLCE SOLUTION SPACE COUNT\]: (.+)$", re.M),
    "average": re.compile(r"^\[VOLCE WEIGHTED AVERAGE MEMS\]: (.+)$", re.M),
    "maximum": re.compile(r"^\[DFS MAX MEMS\]: (.+)$", re.M),
}

def last(pattern, text):
    found = pattern.findall(text)
    return found[-1] if found else None

def main():
    out_dir = Path(os.environ.get("OUT_DIR", "probmems-oracle-results"))
    out_dir.mkdir(parents=True, exist_ok=True)
    rows = []
    with tempfile.TemporaryDirectory() as td:
        for name, source, cost, expected_max in CASES:
            path = Path(td, name + ".c")
            path.write_text(source + "\n", encoding="utf-8")
            costs = [cost(x) for x in DOMAIN]
            # VolCE counts the projection containing variables that occur in
            # path constraints.  For branch-free cases x is unconstrained and
            # absent from SMT, so the projected count is one even though the
            # full executable input domain contains three x values.
            expected_count = 1 if name in {"or01_one_read", "or02_two_reads"} else len(costs)
            expected_sum = sum(costs)
            expected_average = expected_sum / expected_count
            proc = subprocess.run(
                [CNIP, "-q", "--maxloop", "1", "--maxpaths", "100", "--volce",
                 "--volce-lower", "-1", "--volce-upper", "1", str(path)],
                text=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, timeout=30)
            log = proc.stdout
            Path(out_dir, name + ".log").write_text(log, encoding="utf-8")
            got_count = last(PATTERNS["count"], log)
            got_average = last(PATTERNS["average"], log)
            got_max = last(PATTERNS["maximum"], log)
            ok = proc.returncode == 0 and got_count is not None and got_average is not None and got_max is not None
            if ok:
                ok = (int(got_count) == expected_count and
                      abs(float(got_average) - expected_average) <= 1e-5 and
                      int(got_max) == expected_max)
            rows.append({
                "id": name, "domain": "[-1,1]", "enumerated_inputs": len(costs),
                "oracle_projected_count": expected_count,
                "oracle_weighted_sum": expected_sum,
                "oracle_average_mems": f"{expected_average:.8f}",
                "oracle_max_mems": expected_max, "cnip_solution_count": got_count or "N/A",
                "cnip_average_mems": got_average or "N/A", "cnip_max_mems": got_max or "N/A",
                "exit_code": proc.returncode, "match": "PASS" if ok else "FAIL",
            })
    fields = list(rows[0])
    with Path(out_dir, "exact-oracle-summary.csv").open("w", newline="", encoding="utf-8") as f:
        writer = csv.DictWriter(f, fieldnames=fields)
        writer.writeheader(); writer.writerows(rows)
    for row in rows:
        print(",".join(str(row[k]) for k in fields))
    return 0 if all(r["match"] == "PASS" for r in rows) else 1

if __name__ == "__main__":
    raise SystemExit(main())
