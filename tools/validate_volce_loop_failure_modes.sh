#!/usr/bin/env bash
set -euo pipefail
IFS=$'\n\t'

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
CNIP="${CNIP:-$ROOT/build_ci_volce_summary/cnip}"
OUT_DIR="${OUT_DIR:-$ROOT/volce-loop-failure-results}"
TIMEOUT_SECONDS="${TIMEOUT_SECONDS:-90}"
mkdir -p "$OUT_DIR"

run_case() {
  local id="$1" source="$2" maxloop="$3" expected="$4"
  local log="$OUT_DIR/$id.log"
  local status=PASS
  timeout "$TIMEOUT_SECONDS" "$CNIP" -q --maxloop "$maxloop" \
    --maxpaths 40 --volce --volce-lower -4 --volce-upper 8 \
    "$ROOT/$source" >"$log" 2>&1 || status=FAIL

  if ! grep -Eq "$expected" "$log"; then
    status=FAIL
  fi
  local applied ground rejected count
  applied="$(sed -n 's/^\[VOLCE LOOP SUMMARIES APPLIED\]: //p' "$log" | awk '{s+=$1} END {print s+0}')"
  ground="$(sed -n 's/^\[VOLCE LOOP SUMMARIES GROUND-VALIDATED\]: //p' "$log" | awk '{s+=$1} END {print s+0}')"
  rejected="$(sed -n 's/^\[VOLCE LOOP SUMMARIES REJECTED\]: //p' "$log" | awk '{s+=$1} END {print s+0}')"
  count="$(sed -n 's/^\[VOLCE SOLUTION SPACE COUNT\]: //p' "$log" | tail -1)"
  printf '%s,%s,%s,%s,%s,%s,%s\n' "$id" "$status" "$maxloop" \
    "$applied" "$ground" "$rejected" "${count:-N/A}" >> "$OUT_DIR/summary.csv"
}

printf 'id,status,maxloop,ssa_applied,ground_validated,rejected,solution_count\n' \
  > "$OUT_DIR/summary.csv"

# Exact affine trip count 4 is automatically lifted above maxloop=2. This is
# the regression for the old "forced false condition is infeasible" failure.
run_case exact_autolift testcase/loop_hybrid/01_for_lt.c 2 \
  '\[VOLCE LOOP SUMMARIES (APPLIED|GROUND-VALIDATED)\]: [1-9]'

# These loops intentionally remain unsummarized, but now explain why.
run_case while_metadata testcase/loop_hybrid/13_while_input.c 8 \
  'VOLCE LOOP SUMMARY DIAGNOSTIC.*while-loop lacks initializer/update metadata'
run_case early_break testcase/loop_hybrid/18_for_break.c 16 \
  'VOLCE LOOP SUMMARY DIAGNOSTIC.*break/return or truncated path'

cat "$OUT_DIR/summary.csv"
awk -F, 'NR>1 && $2!="PASS" {bad=1} END {exit bad}' "$OUT_DIR/summary.csv"
