#!/usr/bin/env bash
set -uo pipefail
IFS=$'\n\t'

CNIP="${CNIP:-./build_ci/cnip}"
MANIFEST="${MANIFEST:-testcase/probmems_ground_truth/manifest.csv}"
CATEGORY="${CATEGORY:-all}"
OUT_DIR="${OUT_DIR:-probmems-dataset-results}"
MAXPATHS="${MAXPATHS:-100}"
MAXLOOP_CEILING="${MAXLOOP_CEILING:-12}"
ADAPTIVE_RADIUS="${ADAPTIVE_RADIUS:-4}"
TIMEOUT_SECONDS="${TIMEOUT_SECONDS:-120}"
STRICT="${STRICT:-0}"

SHARD="$OUT_DIR/$CATEGORY"
mkdir -p "$SHARD/logs"
SUMMARY="$SHARD/summary.csv"
echo "id,source,category,features,memory_access_syntax,expected_support,lower,upper,requested_maxloop,selected_maxloop,attempted_maxloops,adaptive_retry_count,maxpaths,compile_status,run_status,elapsed_seconds,path_count,solution_space_count,weighted_mems_sum,weighted_average_mems,dfs_max_mems,path_limit_hit,zero_diagnostic,average_to_max_ratio" > "$SUMMARY"

append_candidate() {
  local value="$1"
  if (( value < 1 || value > MAXLOOP_CEILING )); then return; fi
  local seen
  for seen in "${candidates[@]:-}"; do
    if [[ "$seen" == "$value" ]]; then return; fi
  done
  candidates+=("$value")
}

failures=0
while IFS=',' read -r id source category features lower upper requested_maxloop expected_support entry_function; do
  if [[ "$CATEGORY" != all && "$category" != "$CATEGORY" ]]; then continue; fi
  lower="${lower//[[:space:]]/}"
  upper="${upper//[[:space:]]/}"
  requested_maxloop="${requested_maxloop//[[:space:]]/}"
  expected_support="${expected_support//[[:space:]]/}"

  memory_access_syntax=NO
  if grep -Eq '\[[^]]+\]|\*[[:space:]]*[A-Za-z_]' "$source"; then memory_access_syntax=YES; fi

  compile_status=PASS
  run_status=FAIL
  selected_maxloop=N/A
  attempted_maxloops=""
  retry_count=0
  elapsed=0
  paths=0
  count=N/A
  weighted_sum=N/A
  weighted_average=N/A
  max_mems=N/A
  last_failure=ANALYSIS_FAILURE

  if ! gcc -std=c11 -fsyntax-only "$source" >"$SHARD/logs/$id.gcc.log" 2>&1; then
    compile_status=FAIL
    run_status=SKIP
    last_failure=COMPILE_FAILURE
  else
    candidates=()
    append_candidate "$requested_maxloop"
    # Prefer a nearby smaller bound first: excessive while-loop expansion can
    # cause state explosion, while an insufficient bound is recovered by the
    # immediately following larger candidate.
    for ((delta=1; delta<=ADAPTIVE_RADIUS; delta++)); do
      append_candidate $((requested_maxloop - delta))
      append_candidate $((requested_maxloop + delta))
    done
    append_candidate "$MAXLOOP_CEILING"

    attempt_index=0
    for candidate in "${candidates[@]}"; do
      if [[ -n "$attempted_maxloops" ]]; then attempted_maxloops+="|"; fi
      attempted_maxloops+="$candidate"
      log="$SHARD/logs/$id.maxloop-$candidate.log"
      SECONDS=0
      analysis_flag="-q"
      if [[ -n "${entry_function:-}" ]]; then analysis_flag="-s"; fi
      timeout "$TIMEOUT_SECONDS" env EPPATHER_ENTRY="${entry_function:-main}" "$CNIP" "$analysis_flag" \
        --maxloop "$candidate" --maxpaths "$MAXPATHS" --volce \
        --volce-lower "$lower" --volce-upper "$upper" "$source" >"$log" 2>&1
      exit_code=$?
      elapsed=$((elapsed + SECONDS))

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

      if [[ $exit_code -eq 124 ]]; then
        last_failure=COUNT_TIMEOUT
      elif [[ $exit_code -ne 0 ]]; then
        last_failure=ANALYSIS_FAILURE
      elif [[ "$count" =~ ^[0-9]+$ ]] && (( count == 0 )); then
        last_failure=EMPTY_SOLUTION_SPACE
      elif [[ "$count" == N/A || "$weighted_average" == N/A || "$max_mems" == N/A ]]; then
        last_failure=MISSING_METRIC
      else
        run_status=PASS
        selected_maxloop="$candidate"
        retry_count="$attempt_index"
        break
      fi
      attempt_index=$((attempt_index + 1))
    done
  fi

  path_limit_hit=NO
  if [[ "$paths" =~ ^[0-9]+$ ]] && (( paths >= MAXPATHS )); then path_limit_hit=YES; fi

  zero_diagnostic=NONZERO_OR_ZERO_COST
  if [[ "$run_status" != PASS ]]; then
    retry_count="$attempt_index"
    zero_diagnostic="$last_failure"
    count=N/A
    weighted_sum=N/A
    weighted_average=N/A
    max_mems=N/A
    failures=$((failures + 1))
  elif awk -v s="$weighted_sum" -v m="$max_mems" 'BEGIN { exit !((s+0)==0 && (m+0)>0) }'; then
    zero_diagnostic=ZERO_WEIGHT_REQUIRES_DIAGNOSIS
  elif awk -v s="$weighted_sum" -v m="$max_mems" 'BEGIN { exit !((s+0)==0 && (m+0)==0) }'; then
    if [[ "$memory_access_syntax" == YES ]]; then
      zero_diagnostic=ZERO_WITH_MEMORY_SYNTAX
    else
      zero_diagnostic=ZERO_NO_MEMORY_ACCESS
    fi
  fi

  ratio=N/A
  if [[ "$weighted_average" != N/A && "$max_mems" != N/A ]] &&
     awk -v m="$max_mems" 'BEGIN { exit !((m+0)>0) }'; then
    ratio="$(awk -v a="$weighted_average" -v m="$max_mems" 'BEGIN { printf "%.8f", a/m }')"
  fi

  printf '%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n' \
    "$id" "$source" "$category" "$features" "$memory_access_syntax" "$expected_support" \
    "$lower" "$upper" "$requested_maxloop" "$selected_maxloop" "$attempted_maxloops" \
    "$retry_count" "$MAXPATHS" "$compile_status" "$run_status" "$elapsed" "$paths" \
    "$count" "$weighted_sum" "$weighted_average" "$max_mems" "$path_limit_hit" \
    "$zero_diagnostic" "$ratio" >> "$SUMMARY"
done < <(tail -n +2 "$MANIFEST")

cat "$SUMMARY"
if [[ "$STRICT" == 1 ]]; then exit "$failures"; fi
exit 0
