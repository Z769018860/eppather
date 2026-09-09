#!/usr/bin/env bash
set -uo pipefail

IFS=$'\n\t'

CNIP="${CNIP:-./cnip}"
OUT_DIR="${OUT_DIR:-volce-regression-results}"
mkdir -p "$OUT_DIR/logs"
SUMMARY="$OUT_DIR/summary.csv"
echo "case,c_compile,eppather_run,path_count,solution_space_count,weighted_mems_sum,weighted_average_mems,dfs_max_mems" > "$SUMMARY"

cases=(
  testcase/test01.c
  testcase/test02.c
  testcase/test04.c
  testcase/dp_maxmem_branch.c
  testcase/test13.c
  testcase/test14.c
  testcase/test15.c
  testcase/test16.c
  testcase/dp_maxmem_single.c
  testcase/dp_maxmem_nested.c
)

failures=0
for source in "${cases[@]}"; do
  tag="$(basename "$source" .c)"
  log="$OUT_DIR/logs/$tag.log"
  compile=PASS
  run=PASS

  if ! gcc -std=c11 -fsyntax-only "$source" >"$OUT_DIR/logs/$tag.gcc.log" 2>&1; then
    compile=FAIL
    run=SKIP
    failures=$((failures + 1))
  elif ! timeout 120 "$CNIP" -q --maxloop 3 --maxpaths 100 \
      --volce --volce-lower -4 --volce-upper 4 "$source" >"$log" 2>&1; then
    run=FAIL
    failures=$((failures + 1))
  fi

  paths="$(grep -c '^  \[path [0-9][0-9]*\] mem=' "$log" 2>/dev/null || true)"
  solution_count="$(sed -n 's/^\[VOLCE SOLUTION SPACE COUNT\]: //p' "$log" 2>/dev/null | tail -1)"
  weighted_sum="$(sed -n 's/^\[VOLCE WEIGHTED MEMS SUM\]: //p' "$log" 2>/dev/null | tail -1)"
  weighted_average="$(sed -n 's/^\[VOLCE WEIGHTED AVERAGE MEMS\]: //p' "$log" 2>/dev/null | tail -1)"
  max_mems="$(sed -n 's/^\[DFS MAX MEMS\]: //p' "$log" 2>/dev/null | tail -1)"

  if [[ "$run" == PASS && ( -z "$solution_count" || -z "$weighted_average" ) ]]; then
    run=FAIL
    failures=$((failures + 1))
  fi
  echo "$source,$compile,$run,${paths:-0},${solution_count:-N/A},${weighted_sum:-N/A},${weighted_average:-N/A},${max_mems:-N/A}" >> "$SUMMARY"
done

cat "$SUMMARY"
exit "$failures"
