#!/usr/bin/env bash
set -uo pipefail

IFS=$'\n\t'

CNIP="${CNIP:-./cnip}"
OUT_DIR="${OUT_DIR:-volce-regression-results}"
mkdir -p "$OUT_DIR/logs"
SUMMARY="$OUT_DIR/summary.csv"
echo "case,c_compile,eppather_run,path_count,solution_space_count,weighted_mems_sum,weighted_average_mems,dfs_max_mems" > "$SUMMARY"

cases=(
  testcase/dp_maxmem_branch.c
  testcase/dp_maxmem_single.c
  testcase/dp_maxmem_nested.c
  testcase/summary_global_multi.c
  testcase/test08.c
  testcase/test09.c
  testcase/test17.c
  testcase/test24.c
  testcase/test26.c
  testcase/example9-test.c
)

failures=0
for source in "${cases[@]}"; do
  tag="$(basename "$source" .c)"
  log="$OUT_DIR/logs/$tag.log"
  compile=PASS
  run=PASS

  case_maxloop=1
  if [[ "$source" == testcase/dp_maxmem_single.c || "$source" == testcase/dp_maxmem_nested.c ]]; then
    case_maxloop=3
  fi

  if ! gcc -std=c11 -fsyntax-only "$source" >"$OUT_DIR/logs/$tag.gcc.log" 2>&1; then
    compile=FAIL
    run=SKIP
    failures=$((failures + 1))
  elif ! timeout 120 "$CNIP" -q --maxloop "$case_maxloop" --maxpaths 30 \
      --volce --volce-lower -1 --volce-upper 1 "$source" >"$log" 2>&1; then
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
