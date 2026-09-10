#!/usr/bin/env bash
set -uo pipefail
IFS=$'\n\t'

CNIP="${CNIP:-./build_ci/cnip}"
MANIFEST="${MANIFEST:-testcase/probmems_ground_truth/manifest.csv}"
CATEGORY="${CATEGORY:-all}"
OUT_DIR="${OUT_DIR:-probmems-dataset-results}"
LOWER_OVERRIDE="${LOWER_OVERRIDE:-}"
UPPER_OVERRIDE="${UPPER_OVERRIDE:-}"
MAXPATHS="${MAXPATHS:-100}"
MAXLOOP_OVERRIDE="${MAXLOOP_OVERRIDE:-}"
TIMEOUT_SECONDS="${TIMEOUT_SECONDS:-120}"
STRICT="${STRICT:-0}"

SHARD="$OUT_DIR/$CATEGORY"
mkdir -p "$SHARD/logs"
SUMMARY="$SHARD/summary.csv"
echo "id,source,category,features,memory_access_syntax,expected_support,lower,upper,maxloop,maxpaths,compile_status,run_status,elapsed_seconds,path_count,solution_space_count,weighted_mems_sum,weighted_average_mems,dfs_max_mems,path_limit_hit,zero_diagnostic,average_to_max_ratio" > "$SUMMARY"

failures=0
tail -n +2 "$MANIFEST" | while IFS=',' read -r id source category features lower upper maxloop expected_support; do
  if [[ "$CATEGORY" != all && "$category" != "$CATEGORY" ]]; then
    continue
  fi

  lower="${lower//[[:space:]]/}"
  upper="${upper//[[:space:]]/}"
  maxloop="${maxloop//[[:space:]]/}"
  expected_support="${expected_support//[[:space:]]/}"
  if [[ -n "$MAXLOOP_OVERRIDE" ]]; then
    maxloop="$MAXLOOP_OVERRIDE"
  fi
  if [[ -n "$LOWER_OVERRIDE" ]]; then
    lower="$LOWER_OVERRIDE"
  fi
  if [[ -n "$UPPER_OVERRIDE" ]]; then
    upper="$UPPER_OVERRIDE"
  fi

  memory_access_syntax=NO
  if grep -Eq '\[[^]]+\]|\*[[:space:]]*[A-Za-z_]' "$source"; then
    memory_access_syntax=YES
  fi

  compile_status=PASS
  run_status=PASS
  elapsed=0
  log="$SHARD/logs/$id.log"

  if ! gcc -std=c11 -fsyntax-only "$source" >"$SHARD/logs/$id.gcc.log" 2>&1; then
    compile_status=FAIL
    run_status=SKIP
  else
    SECONDS=0
    timeout "$TIMEOUT_SECONDS" "$CNIP" -q       --maxloop "$maxloop"       --maxpaths "$MAXPATHS"       --volce       --volce-lower "$lower"       --volce-upper "$upper"       "$source" >"$log" 2>&1
    exit_code=$?
    elapsed=$SECONDS
    if [[ $exit_code -eq 124 ]]; then
      run_status=TIMEOUT
    elif [[ $exit_code -ne 0 ]]; then
      run_status=FAIL
    fi
  fi

  paths="$(grep -c '^  \[path [0-9][0-9]*\] mem=' "$log" 2>/dev/null || true)"
  count="$(sed -n 's/^\[VOLCE SOLUTION SPACE COUNT\]: //p' "$log" 2>/dev/null | tail -1)"
  weighted_sum="$(sed -n 's/^\[VOLCE WEIGHTED MEMS SUM\]: //p' "$log" 2>/dev/null | tail -1)"
  weighted_average="$(sed -n 's/^\[VOLCE WEIGHTED AVERAGE MEMS\]: //p' "$log" 2>/dev/null | tail -1)"
  max_mems="$(sed -n 's/^\[DFS MAX MEMS\]: //p' "$log" 2>/dev/null | tail -1)"

  paths="${paths:-0}"
  count="${count:-N/A}"
  weighted_sum="${weighted_sum:-N/A}"
  weighted_average="${weighted_average:-N/A}"
  max_mems="${max_mems:-N/A}"

  if [[ "$run_status" != PASS ]]; then
    count=N/A
    weighted_sum=N/A
    weighted_average=N/A
    max_mems=N/A
  fi

  path_limit_hit=NO
  if [[ "$paths" =~ ^[0-9]+$ ]] && (( paths >= MAXPATHS )); then
    path_limit_hit=YES
  fi

  zero_diagnostic=NONZERO_OR_ZERO_COST
  if [[ "$run_status" == TIMEOUT ]]; then
    zero_diagnostic=COUNT_TIMEOUT
  elif [[ "$run_status" != PASS ]]; then
    zero_diagnostic=ANALYSIS_FAILURE
  elif [[ "$count" == N/A || "$weighted_average" == N/A ]]; then
    zero_diagnostic=MISSING_METRIC
    run_status=FAIL
  elif [[ "$count" =~ ^[0-9]+$ ]] && (( count == 0 )); then
    zero_diagnostic=EMPTY_SOLUTION_SPACE
  elif awk -v s="$weighted_sum" -v m="$max_mems" 'BEGIN { exit !((s+0)==0 && (m+0)>0) }'; then
    zero_diagnostic=ZERO_WEIGHT_REQUIRES_DIAGNOSIS
  elif awk -v s="$weighted_sum" -v m="$max_mems" 'BEGIN { exit !((s+0)==0 && (m+0)==0) }'; then
    if [[ "$memory_access_syntax" == YES ]]; then
      zero_diagnostic=ZERO_WITH_MEMORY_SYNTAX
    else
      zero_diagnostic=ZERO_NO_MEMORY_ACCESS
    fi
  fi

  if [[ "$compile_status" != PASS || "$run_status" != PASS ]]; then
    failures=$((failures + 1))
  fi

  ratio=N/A
  if [[ "$weighted_average" != N/A && "$max_mems" != N/A ]] &&
     awk -v m="$max_mems" 'BEGIN { exit !((m+0)>0) }'; then
    ratio="$(awk -v a="$weighted_average" -v m="$max_mems" 'BEGIN { printf "%.8f", a/m }')"
  fi

  printf '%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n'     "$id" "$source" "$category" "$features" "$memory_access_syntax" "$expected_support" "$lower" "$upper"     "$maxloop" "$MAXPATHS" "$compile_status" "$run_status" "$elapsed" "$paths"     "$count" "$weighted_sum" "$weighted_average" "$max_mems" "$path_limit_hit"     "$zero_diagnostic" "$ratio" >> "$SUMMARY"
done

cat "$SUMMARY"
if [[ "$STRICT" == 1 ]]; then
  exit "$failures"
fi
exit 0
