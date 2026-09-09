#!/usr/bin/env bash
set -uo pipefail
IFS=$'\n\t'

CNIP="${CNIP:-./build_ci/cnip}"
OUT_DIR="${OUT_DIR:-project-volce-results}"
mkdir -p "$OUT_DIR/logs"
SUMMARY="$OUT_DIR/summary.csv"
echo "project,analysis_input,input_kind,c_compile,eppather_run,path_count,solution_space_count,weighted_mems_sum,weighted_average_mems,dfs_max_mems" > "$SUMMARY"

rows=(
  "cJSON|testcase/llm_summaries/cjson_parse_summary.c|normalized_large-project_summary"
  "tinyexpr|testcase/llm_summaries/tinyexpr_interp_summary.c|normalized_large-project_summary"
  "Lua|testcase/llm_summaries/lua_zread_summary.c|normalized_large-project_summary"
  "clibs-list|testcase/_eppather_preprocessed/list/slices/list_list_flat__list_at__auto_compat.c|auto_compat_function_slice"
  "inih|testcase/_eppather_preprocessed/inih/slices/inih_ini_flat__ini_rstrip__auto_compat.c|auto_compat_function_slice"
  "sds|testcase/_eppather_preprocessed/sds/slices/sds_sds_flat__sdscmp__auto_compat.c|auto_compat_function_slice"
)

failures=0
for row in "${rows[@]}"; do
  IFS='|' read -r project source input_kind <<< "$row"
  tag="$(printf '%s' "$project" | tr '[:upper:]' '[:lower:]' | tr -c 'a-z0-9_' '_')"
  log="$OUT_DIR/logs/$tag.log"
  compile=PASS
  run=PASS
  if ! gcc -std=c11 -fsyntax-only "$source" >"$OUT_DIR/logs/$tag.gcc.log" 2>&1; then
    compile=FAIL
    run=SKIP
    failures=$((failures + 1))
  elif ! timeout 180 "$CNIP" -q --maxloop 1 --maxpaths 40 \
      --volce --volce-lower -1 --volce-upper 1 "$source" >"$log" 2>&1; then
    run=FAIL
    failures=$((failures + 1))
  fi
  paths="$(grep -c '^  \[path [0-9][0-9]*\] mem=' "$log" 2>/dev/null || true)"
  count="$(sed -n 's/^\[VOLCE SOLUTION SPACE COUNT\]: //p' "$log" 2>/dev/null | tail -1)"
  sum="$(sed -n 's/^\[VOLCE WEIGHTED MEMS SUM\]: //p' "$log" 2>/dev/null | tail -1)"
  avg="$(sed -n 's/^\[VOLCE WEIGHTED AVERAGE MEMS\]: //p' "$log" 2>/dev/null | tail -1)"
  max="$(sed -n 's/^\[DFS MAX MEMS\]: //p' "$log" 2>/dev/null | tail -1)"
  if [[ "$run" == PASS && ( -z "$count" || -z "$avg" ) ]]; then
    run=FAIL
    failures=$((failures + 1))
  fi
  echo "$project,$source,$input_kind,$compile,$run,${paths:-0},${count:-N/A},${sum:-N/A},${avg:-N/A},${max:-N/A}" >> "$SUMMARY"
done
cat "$SUMMARY"
exit "$failures"
