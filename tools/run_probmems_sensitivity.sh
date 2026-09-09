#!/usr/bin/env bash
set -uo pipefail
IFS=$'\n\t'

CNIP="${CNIP:-./build_ci/cnip}"
OUT_DIR="${OUT_DIR:-probmems-sensitivity-results}"
SUBJECT_KEY="${SUBJECT_KEY:-cjson}"
DOMAIN_LABEL="${DOMAIN_LABEL:-d1}"
LOWER="${LOWER:--1}"
UPPER="${UPPER:-1}"
MAXPATHS="${MAXPATHS:-40}"
MAXLOOPS="${MAXLOOPS:-1 2 3 5}"
TIMEOUT_SECONDS="${TIMEOUT_SECONDS:-180}"
STRICT="${STRICT:-0}"

case "$SUBJECT_KEY" in
  cjson)
    SUBJECT="cJSON"
    SOURCE="testcase/llm_summaries/cjson_parse_summary.c"
    INPUT_KIND="normalized_large-project_summary"
    ;;
  tinyexpr)
    SUBJECT="tinyexpr"
    SOURCE="testcase/llm_summaries/tinyexpr_interp_summary.c"
    INPUT_KIND="normalized_large-project_summary"
    ;;
  lua)
    SUBJECT="Lua"
    SOURCE="testcase/llm_summaries/lua_zread_summary.c"
    INPUT_KIND="normalized_large-project_summary"
    ;;
  list)
    SUBJECT="clibs-list"
    SOURCE="testcase/_eppather_preprocessed/list/slices/list_list_flat__list_at__auto_compat.c"
    INPUT_KIND="auto_compat_function_slice"
    ;;
  inih)
    SUBJECT="inih"
    SOURCE="testcase/_eppather_preprocessed/inih/slices/inih_ini_flat__ini_rstrip__auto_compat.c"
    INPUT_KIND="auto_compat_function_slice"
    ;;
  sds)
    SUBJECT="sds"
    SOURCE="testcase/_eppather_preprocessed/sds/slices/sds_sds_flat__sdscmp__auto_compat.c"
    INPUT_KIND="auto_compat_function_slice"
    ;;
  *)
    echo "unknown SUBJECT_KEY: $SUBJECT_KEY" >&2
    exit 2
    ;;
esac

SHARD="$OUT_DIR/${SUBJECT_KEY}-${DOMAIN_LABEL}"
mkdir -p "$SHARD/logs"
SUMMARY="$SHARD/summary.csv"
echo "subject,source,input_kind,domain_label,lower,upper,maxloop,maxpaths,compile_status,run_status,elapsed_seconds,path_count,solution_space_count,weighted_mems_sum,weighted_average_mems,dfs_max_mems,path_limit_hit,zero_diagnostic,average_to_max_ratio" > "$SUMMARY"

compile_status=PASS
if ! gcc -std=c11 -fsyntax-only "$SOURCE" >"$SHARD/logs/compile.log" 2>&1; then
  compile_status=FAIL
fi

failures=0
for maxloop in $MAXLOOPS; do
  log="$SHARD/logs/maxloop-${maxloop}.log"
  run_status=PASS
  elapsed=0

  if [[ "$compile_status" != PASS ]]; then
    run_status=SKIP
  else
    SECONDS=0
    timeout "$TIMEOUT_SECONDS" "$CNIP" -q       --maxloop "$maxloop"       --maxpaths "$MAXPATHS"       --volce       --volce-lower "$LOWER"       --volce-upper "$UPPER"       "$SOURCE" >"$log" 2>&1
    exit_code=$?
    elapsed=$SECONDS
    if [[ $exit_code -eq 124 ]]; then
      run_status=TIMEOUT
      failures=$((failures + 1))
    elif [[ $exit_code -ne 0 ]]; then
      run_status=FAIL
      failures=$((failures + 1))
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
    failures=$((failures + 1))
  elif awk -v s="$weighted_sum" -v m="$max_mems" 'BEGIN { exit !((s+0)==0 && (m+0)>0) }'; then
    zero_diagnostic=ZERO_WEIGHT_REQUIRES_DIAGNOSIS
  elif awk -v s="$weighted_sum" -v m="$max_mems" 'BEGIN { exit !((s+0)==0 && (m+0)==0) }'; then
    zero_diagnostic=ZERO_COST_PATHS
  fi

  ratio=N/A
  if [[ "$weighted_average" != N/A && "$max_mems" != N/A ]] &&
     awk -v m="$max_mems" 'BEGIN { exit !((m+0)>0) }'; then
    ratio="$(awk -v a="$weighted_average" -v m="$max_mems" 'BEGIN { printf "%.8f", a/m }')"
  fi

  printf '%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n'     "$SUBJECT" "$SOURCE" "$INPUT_KIND" "$DOMAIN_LABEL" "$LOWER" "$UPPER"     "$maxloop" "$MAXPATHS" "$compile_status" "$run_status" "$elapsed" "$paths"     "$count" "$weighted_sum" "$weighted_average" "$max_mems" "$path_limit_hit"     "$zero_diagnostic" "$ratio" >> "$SUMMARY"
done

cat "$SUMMARY"
if [[ "$STRICT" == 1 ]]; then
  exit "$failures"
fi
exit 0
