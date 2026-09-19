#!/usr/bin/env bash
set -euo pipefail
IFS=$'\n\t'

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
CNIP="${CNIP:-$ROOT/build_ci_volce_summary/cnip}"
OUT_DIR="${OUT_DIR:-$ROOT/loopscc-effect-results}"
TIMEOUT_SECONDS="${TIMEOUT_SECONDS:-90}"
MAXPATHS="${MAXPATHS:-80}"
VOLCE_LOWER="${VOLCE_LOWER:--8}"
VOLCE_UPPER="${VOLCE_UPPER:-8}"
mkdir -p "$OUT_DIR/logs"

metric() {
  local pattern="$1" file="$2"
  sed -n "s/^${pattern}: //p" "$file" | tail -1
}

sum_metric() {
  local pattern="$1" file="$2"
  sed -n "s/^${pattern}: //p" "$file" |
    awk '{sum += $1} END {print sum + 0}'
}

run_mode() {
  local mode="$1" src="$2" maxloop="$3" log="$4" time_file="$5"
  local start_ns end_ns rc=0
  start_ns="$(date +%s%N)"
  if [[ "$mode" == baseline ]]; then
    timeout "$TIMEOUT_SECONDS" env EPPATHER_DISABLE_VOLCE_LOOP_SUMMARIES=1 \
      "$CNIP" -q --maxloop "$maxloop" --maxpaths "$MAXPATHS" --volce \
      --volce-lower "$VOLCE_LOWER" --volce-upper "$VOLCE_UPPER" \
      "$src" >"$log" 2>&1 || rc=$?
  else
    timeout "$TIMEOUT_SECONDS" "$CNIP" -q --maxloop "$maxloop" \
      --maxpaths "$MAXPATHS" --volce --volce-lower "$VOLCE_LOWER" \
      --volce-upper "$VOLCE_UPPER" "$src" >"$log" 2>&1 || rc=$?
  fi
  end_ns="$(date +%s%N)"
  printf '%s\n' "$(((end_ns - start_ns) / 1000000))" >"$time_file"
  return "$rc"
}

printf '%s\n' \
  'id,category,expected_mode,maxloop,status,effect,summary_count,baseline_count,summary_wmems,baseline_wmems,ssa_applied,ground_validated,rejected,diagnostics,summary_ms,baseline_ms,speedup,summary_assertions,baseline_assertions,summary_projection_terms,baseline_projection_terms,summary_warmup_us,baseline_warmup_us,summary_check_us,summary_count_us,baseline_count_us,summary_counting_assertions,baseline_counting_assertions' \
  >"$OUT_DIR/effect.csv"

while IFS=, read -r id source category expected_mode expected_trip maxloop; do
  [[ "$id" == id ]] && continue
  src="$ROOT/$source"
  summary_log="$OUT_DIR/logs/$id.summary.log"
  baseline_log="$OUT_DIR/logs/$id.baseline.log"
  summary_time="$OUT_DIR/logs/$id.summary.ms"
  baseline_time="$OUT_DIR/logs/$id.baseline.ms"

  summary_ok=0
  baseline_ok=0
  run_mode summary "$src" "$maxloop" "$summary_log" "$summary_time" && summary_ok=1
  run_mode baseline "$src" "$maxloop" "$baseline_log" "$baseline_time" && baseline_ok=1

  summary_count="$(metric '\[VOLCE SOLUTION SPACE COUNT\]' "$summary_log")"
  baseline_count="$(metric '\[VOLCE SOLUTION SPACE COUNT\]' "$baseline_log")"
  summary_wmems="$(metric '\[VOLCE WEIGHTED AVERAGE MEMS\]' "$summary_log")"
  baseline_wmems="$(metric '\[VOLCE WEIGHTED AVERAGE MEMS\]' "$baseline_log")"
  applied="$(sum_metric '\[VOLCE LOOP SUMMARIES APPLIED\]' "$summary_log")"
  ground="$(sum_metric '\[VOLCE LOOP SUMMARIES GROUND-VALIDATED\]' "$summary_log")"
  rejected="$(sum_metric '\[VOLCE LOOP SUMMARIES REJECTED\]' "$summary_log")"
  diagnostics="$(grep -c '^\[VOLCE LOOP SUMMARY DIAGNOSTIC\]:' "$summary_log" || true)"
  summary_ms="$(cat "$summary_time")"
  baseline_ms="$(cat "$baseline_time")"
  summary_assertions="$(sum_metric '\[VOLCE FORMULA ASSERTIONS\]' "$summary_log")"
  baseline_assertions="$(sum_metric '\[VOLCE FORMULA ASSERTIONS\]' "$baseline_log")"
  summary_projection="$(sum_metric '\[VOLCE PROJECTION TERMS\]' "$summary_log")"
  baseline_projection="$(sum_metric '\[VOLCE PROJECTION TERMS\]' "$baseline_log")"
  summary_counting_assertions="$(sum_metric '\[VOLCE COUNTING ASSERTIONS\]' "$summary_log")"
  baseline_counting_assertions="$(sum_metric '\[VOLCE COUNTING ASSERTIONS\]' "$baseline_log")"
  summary_warmup_us="$(sum_metric '\[VOLCE SOLVER WARMUP US\]' "$summary_log")"
  baseline_warmup_us="$(sum_metric '\[VOLCE SOLVER WARMUP US\]' "$baseline_log")"
  summary_check_us="$(sum_metric '\[VOLCE SUMMARY CHECK US\]' "$summary_log")"
  summary_count_us="$(sum_metric '\[VOLCE MODEL COUNT US\]' "$summary_log")"
  baseline_count_us="$(sum_metric '\[VOLCE MODEL COUNT US\]' "$baseline_log")"
  speedup="$(awk -v b="$baseline_ms" -v s="$summary_ms" \
    'BEGIN {if (s > 0) printf "%.4f", b / s; else print "N/A"}')"

  effect=NONE
  (( diagnostics > 0 )) && effect=FALLBACK
  (( ground > 0 )) && effect=GROUND_VALIDATED
  (( applied > 0 )) && effect=SSA_APPLIED
  (( rejected > 0 )) && effect=REJECTED

  status=PASS
  (( summary_ok == 1 && baseline_ok == 1 )) || status=FAIL
  [[ "$summary_count" =~ ^[1-9][0-9]*$ ]] || status=FAIL
  [[ "$baseline_count" =~ ^[1-9][0-9]*$ ]] || status=FAIL
  [[ "$summary_count" == "$baseline_count" ]] || status=FAIL
  [[ -n "$summary_wmems" && "$summary_wmems" != N/A && \
     "$summary_wmems" == "$baseline_wmems" ]] || status=FAIL

  printf '%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n' \
    "$id" "$category" "$expected_mode" "$maxloop" "$status" "$effect" \
    "${summary_count:-N/A}" "${baseline_count:-N/A}" \
    "${summary_wmems:-N/A}" "${baseline_wmems:-N/A}" \
    "$applied" "$ground" "$rejected" "$diagnostics" \
    "$summary_ms" "$baseline_ms" "$speedup" \
    "$summary_assertions" "$baseline_assertions" \
    "$summary_projection" "$baseline_projection" \
    "$summary_warmup_us" "$baseline_warmup_us" "$summary_check_us" \
    "$summary_count_us" "$baseline_count_us" \
    "$summary_counting_assertions" "$baseline_counting_assertions" >>"$OUT_DIR/effect.csv"
done <"$ROOT/testcase/loop_hybrid/manifest.csv"

cat "$OUT_DIR/effect.csv"
awk -F, 'NR > 1 && $5 != "PASS" {bad=1} END {exit bad}' \
  "$OUT_DIR/effect.csv"

awk -F, '
  NR > 1 {
    total++
    if ($5 == "PASS") passed++
    if ($6 == "SSA_APPLIED") ssa++
    if ($6 == "GROUND_VALIDATED") ground++
    if ($6 == "FALLBACK") fallback++
    if ($6 == "REJECTED") rejected++
    summary_ms += $15
    baseline_ms += $16
    summary_warmup_us += $22
    baseline_warmup_us += $23
    summary_check_us += $24
    summary_count_us += $25
    baseline_count_us += $26
    summary_counting_assertions += $27
    baseline_counting_assertions += $28
  }
  END {
    print "total,passed,ssa_applied_cases,ground_validated_cases,fallback_cases,rejected_cases,summary_ms,baseline_ms,aggregate_speedup,summary_warmup_us,baseline_warmup_us,summary_check_us,summary_count_us,baseline_count_us,count_ratio,summary_counting_assertions,baseline_counting_assertions"
    speedup = summary_ms > 0 ? baseline_ms / summary_ms : 0
    count_ratio = summary_count_us > 0 ? baseline_count_us / summary_count_us : 0
    printf "%d,%d,%d,%d,%d,%d,%d,%d,%.4f,%d,%d,%d,%d,%d,%.4f,%d,%d\n", total, passed, ssa,
      ground, fallback, rejected, summary_ms, baseline_ms, speedup,
      summary_warmup_us, baseline_warmup_us, summary_check_us,
      summary_count_us, baseline_count_us, count_ratio,
      summary_counting_assertions, baseline_counting_assertions
  }
' "$OUT_DIR/effect.csv" >"$OUT_DIR/aggregate.csv"
cat "$OUT_DIR/aggregate.csv"
