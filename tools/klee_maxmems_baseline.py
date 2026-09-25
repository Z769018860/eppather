#!/usr/bin/env python3
"""KLEE path-discovery baseline for the 20 controlled MaxMEMS subjects.

KLEE is used only to generate concrete test inputs.  Every generated test is
replayed with the same dynamic MEMS instrumentation used by the independent
MaxMEMS witness experiment, so the compared quantity is attained MEMS rather
than KLEE's native coverage metric.
"""
from __future__ import annotations

import argparse
import csv
import json
import re
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from e2e_path_validation import parse_signature
from maxmems_witness_experiment import SUBJECTS, compile_replay, dynamic_oracle, replay

KLEE_IMAGE = "klee/klee:3.1"

def run(cmd, cwd=None, timeout=None):
    return subprocess.run(cmd, cwd=cwd, stdout=subprocess.PIPE,
                          stderr=subprocess.PIPE, text=True, timeout=timeout)

def make_harness(source: str, function: str, params: list[str], lo: int, hi: int) -> str:
    symbolic = []
    for name in params:
        symbolic.extend([
            f"    int {name};",
            f'    klee_make_symbolic(&{name}, sizeof({name}), "{name}");',
            f"    klee_assume({name} >= {lo});",
            f"    klee_assume({name} <= {hi});",
        ])
    args = ", ".join(params)
    return (
        "#include <klee/klee.h>\n"
        + source + "\n"
        + "int main(void) {\n"
        + "\n".join(symbolic) + "\n"
        + f"    (void){function}({args});\n"
        + "    return 0;\n}\n"
    )

def parse_ktest_dump(text: str) -> list[dict[str, int]]:
    tests = []
    current = {}
    pending_name = None
    for line in text.splitlines():
        if line.startswith("=== KTEST "):
            if current:
                tests.append(current)
            current = {}
            pending_name = None
            continue
        m = re.search(r"object\s+\d+:\s+name:\s+'([^']+)'", line)
        if m:
            pending_name = m.group(1)
            continue
        m = re.search(r"object\s+\d+:\s+data:\s+(-?\d+)\s*$", line)
        if m and pending_name:
            current[pending_name] = int(m.group(1))
            pending_name = None
    if current:
        tests.append(current)
    return tests

def write_runner(root: Path) -> None:
    script = r'''#!/usr/bin/env bash
set -u
for d in /work/mw*; do
  [ -d "$d" ] || continue
  cd "$d"
  rm -rf klee-out
  clang -I /home/klee/klee_src/include -emit-llvm -c -g -O0     -Xclang -disable-O0-optnone harness.c -o harness.bc >compile.log 2>&1
  crc=$?
  echo "$crc" > compile.rc
  if [ "$crc" -ne 0 ]; then
    continue
  fi
  start="$(date +%s%N)"
  klee --output-dir=klee-out --max-time=30s harness.bc >klee.log 2>&1
  krc=$?
  end="$(date +%s%N)"
  echo "$krc" > klee.rc
  echo $(( (end - start) / 1000000 )) > klee.ms
  : > tests.txt
  if [ -d klee-out ]; then
    for f in klee-out/*.ktest; do
      [ -f "$f" ] || continue
      echo "=== KTEST $f" >> tests.txt
      ktest-tool --write-ints "$f" >> tests.txt 2>&1
    done
  fi
done
'''
    p = root / "run_klee.sh"
    p.write_text(script, encoding="utf-8")
    p.chmod(0o755)

def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--output-dir", type=Path, default=Path("klee-maxmems-results"))
    ap.add_argument("--image", default=KLEE_IMAGE)
    ap.add_argument("--skip-pull", action="store_true")
    args = ap.parse_args()

    out = args.output_dir.resolve()
    if out.exists():
        shutil.rmtree(out)
    out.mkdir(parents=True)
    # The official KLEE image runs as a non-root user. GitHub Actions creates
    # the bind-mounted output tree with runner-only write permissions, so make
    # the experiment workspace writable before entering the container.
    out.chmod(0o777)
    meta = {}

    for s in SUBJECTS:
        d = out / s["id"]
        d.mkdir()
        d.chmod(0o777)
        source = s["source"] + "\n"
        selected, params = parse_signature(source, s["function"])
        (d / "subject.c").write_text(source, encoding="utf-8")
        (d / "harness.c").write_text(
            make_harness(source, selected, params, s["lo"], s["hi"]),
            encoding="utf-8")
        meta[s["id"]] = {
            "function": selected, "params": params, "max_loop": s["max_loop"],
            "lo": s["lo"], "hi": s["hi"], "category": s["category"],
        }

    write_runner(out)
    if not args.skip_pull:
        pull = run(["docker", "pull", args.image], timeout=1200)
        if pull.returncode:
            sys.stderr.write(pull.stdout + pull.stderr)
            return pull.returncode

    docker = run([
        "docker", "run", "--rm", "--ulimit", "stack=-1:-1",
        "-v", f"{out}:/work", args.image, "bash", "/work/run_klee.sh"
    ], timeout=1800)
    (out / "docker.log").write_text(docker.stdout + docker.stderr, encoding="utf-8")

    rows = []
    for s in SUBJECTS:
        d = out / s["id"]
        m = meta[s["id"]]
        row = {
            "id": s["id"], "category": s["category"], "status": "error",
            "klee_tests": 0, "klee_attained_mems": "", "concrete_oracle_mems": "",
            "attains_oracle": 0, "klee_ms": "",
        }
        try:
            crc = int((d / "compile.rc").read_text().strip())
            row["compile_rc"] = crc
            if crc != 0:
                row["detail"] = "KLEE harness compile failed"
                rows.append(row)
                continue
            krc = int((d / "klee.rc").read_text().strip())
            row["klee_rc"] = krc
            row["klee_ms"] = int((d / "klee.ms").read_text().strip())
            tests = parse_ktest_dump((d / "tests.txt").read_text(
                encoding="utf-8", errors="replace"))
            row["klee_tests"] = len(tests)
            if not tests:
                row["detail"] = "KLEE generated no tests"
                rows.append(row)
                continue

            source = (d / "subject.c").read_text(encoding="utf-8")
            with tempfile.TemporaryDirectory(prefix=f"klee-replay-{s['id']}-") as td:
                work = Path(td)
                exe = compile_replay(source, m["function"], m["params"], work,
                                     m["max_loop"])
                attained = -1
                replayed = 0
                for inputs in tests:
                    if any(p not in inputs for p in m["params"]):
                        continue
                    _, mem = replay(exe, m["params"], inputs, work)
                    replayed += 1
                    attained = max(attained, mem)
                oracle, defined, undefined = dynamic_oracle(
                    exe, m["params"], m["lo"], m["hi"], work)

            row.update({
                "status": "pass" if attained == oracle else "miss",
                "replayed_tests": replayed,
                "klee_attained_mems": attained,
                "concrete_oracle_mems": oracle,
                "attains_oracle": int(attained == oracle),
                "defined_oracle_inputs": defined,
                "undefined_oracle_inputs": undefined,
                "detail": "" if attained == oracle else "generated tests missed concrete maximum",
            })
        except Exception as exc:
            row["detail"] = str(exc)
        rows.append(row)

    fields = [
        "id","category","status","compile_rc","klee_rc","klee_tests",
        "replayed_tests","klee_attained_mems","concrete_oracle_mems",
        "attains_oracle","klee_ms","defined_oracle_inputs",
        "undefined_oracle_inputs","detail"
    ]
    with (out / "summary.csv").open("w", newline="", encoding="utf-8") as fh:
        w = csv.DictWriter(fh, fieldnames=fields, extrasaction="ignore")
        w.writeheader()
        w.writerows(rows)

    completed = [r for r in rows if r["status"] in {"pass", "miss"}]
    summary = {
        "image": args.image,
        "subjects": len(rows),
        "completed": len(completed),
        "attains_oracle": sum(int(r.get("attains_oracle", 0)) for r in completed),
        "total_klee_ms": sum(int(r.get("klee_ms") or 0) for r in completed),
        "results": rows,
    }
    (out / "summary.json").write_text(json.dumps(summary, indent=2) + "\n",
                                      encoding="utf-8")
    print(json.dumps({k: summary[k] for k in
          ("image","subjects","completed","attains_oracle","total_klee_ms")}))
    return 0 if completed and all(r["status"] == "pass" for r in completed) else 1

if __name__ == "__main__":
    raise SystemExit(main())
