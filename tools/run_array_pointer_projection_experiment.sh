#!/usr/bin/env bash
set -uo pipefail
IFS=$'\n\t'

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
CNIP="${CNIP:-$ROOT/build_ci_array_pointer/cnip}"
MANIFEST="${MANIFEST:-$ROOT/testcase/probmems_array_pointer/manifest.csv}"
OUT_DIR="${OUT_DIR:-$ROOT/array-pointer-projection-results}"
LOWER="${LOWER:--1}"
UPPER="${UPPER:-1}"
MAXPATHS="${MAXPATHS:-100}"
TIMEOUT_SECONDS="${TIMEOUT_SECONDS:-60}"
MAXLOOP_OVERRIDE="${MAXLOOP_OVERRIDE:-}"
mkdir -p "$OUT_DIR/logs"

metric() {
  local pattern="$1" file="$2"
  sed -n "s/^${pattern}: //p" "$file" | tail -1
}

printf '%s\n' \
  'id,category,features,maxloop,mode,compile_status,run_status,path_count,solution_space_count,weighted_average_mems,dfs_max_mems,canonical_memory_regions,memory_projection_arity,memory_projection_status,max_bounded_memory_terms,zero_diagnostic' \
  > "$OUT_DIR/summary.csv"

while IFS=',' read -r id source category features maxloop; do
  if [[ -n "$MAXLOOP_OVERRIDE" ]]; then maxloop="$MAXLOOP_OVERRIDE"; fi
  compile_status=PASS
  if ! gcc -std=c11 -fsyntax-only "$ROOT/$source" \
      >"$OUT_DIR/logs/$id.gcc.log" 2>&1; then
    compile_status=FAIL
  fi

  for mode in scalar memory; do
    log="$OUT_DIR/logs/$id.$mode.log"
    run_status=PASS
    if [[ "$compile_status" != PASS ]]; then
      run_status=SKIP
    else
      env_args=()
      if [[ "$mode" == memory ]]; then
        env_args+=(EPPATHER_VOLCE_PROJECT_MEMORY=1)
      fi
      timeout "$TIMEOUT_SECONDS" env "${env_args[@]}" "$CNIP" -q \
        --maxloop "$maxloop" --maxpaths "$MAXPATHS" --volce \
        --volce-lower "$LOWER" --volce-upper "$UPPER" \
        "$ROOT/$source" >"$log" 2>&1
      exit_code=$?
      if [[ $exit_code -eq 124 ]]; then
        run_status=TIMEOUT
      elif [[ $exit_code -ne 0 ]]; then
        run_status=FAIL
      fi
    fi

    paths="$(grep -c '^  \[path [0-9][0-9]*\] mem=' "$log" 2>/dev/null || true)"
    count="$(metric '\[VOLCE SOLUTION SPACE COUNT\]' "$log")"
    average="$(metric '\[VOLCE WEIGHTED AVERAGE MEMS\]' "$log")"
    max_mems="$(metric '\[DFS MAX MEMS\]' "$log")"
    arity="$(metric '\[VOLCE MEMORY PROJECTION ARITY\]' "$log")"
    projection_status="$(metric '\[VOLCE MEMORY PROJECTION STATUS\]' "$log")"
    canonical_regions="$(sed -n 's/^\[VOLCE CANONICAL MEMORY REGIONS\]: //p' "$log" | sort -nr | head -1)"
    max_terms="$(sed -n 's/^\[VOLCE BOUNDED MEMORY TERMS\]: //p' "$log" | \
      sort -nr | head -1)"
    paths="${paths:-0}"
    count="${count:-N/A}"
    average="${average:-N/A}"
    max_mems="${max_mems:-N/A}"
    arity="${arity:-N/A}"
    projection_status="${projection_status:-N/A}"
    canonical_regions="${canonical_regions:-0}"
    max_terms="${max_terms:-0}"

    zero_diagnostic=NONZERO
    if [[ "$run_status" != PASS ]]; then
      zero_diagnostic=ANALYSIS_FAILURE
    elif [[ "$count" == N/A* || "$average" == N/A* ]]; then
      if [[ "$projection_status" == INCONSISTENT_ACROSS_PATHS ]]; then
        zero_diagnostic=INCOMPARABLE_MEMORY_PROJECTION
      else
        zero_diagnostic=MISSING_METRIC
      fi
    elif awk -v a="$average" -v m="$max_mems" \
        'BEGIN { exit !((a+0)==0 && (m+0)>0) }'; then
      zero_diagnostic=ZERO_WEIGHT_WITH_NONZERO_MEMS
    elif awk -v a="$average" -v m="$max_mems" \
        'BEGIN { exit !((a+0)==0 && (m+0)==0) }'; then
      zero_diagnostic=ZERO_MEMORY_COST
    fi

    printf '%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n' \
      "$id" "$category" "$features" "$maxloop" "$mode" \
      "$compile_status" "$run_status" "$paths" "$count" "$average" \
      "$max_mems" "$canonical_regions" "$arity" "$projection_status" "$max_terms" \
      "$zero_diagnostic" >> "$OUT_DIR/summary.csv"
  done
done < <(tail -n +2 "$MANIFEST")

cat "$OUT_DIR/summary.csv"
