#!/usr/bin/env bash
set -euo pipefail
IFS=$'\n\t'

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
CNIP="${CNIP:-$ROOT/build_ci_volce_summary/cnip}"
OUT_DIR="${OUT_DIR:-$ROOT/volce-loop-summary-results}"
TIMEOUT_SECONDS="${TIMEOUT_SECONDS:-90}"
mkdir -p "$OUT_DIR"

metric() {
  local pattern="$1"
  local file="$2"
  sed -n "s/^${pattern}: //p" "$file" | tail -1
}

printf 'id,status,summary_count,baseline_count,applied,rejected,summary_average,baseline_average\n'   > "$OUT_DIR/summary.csv"
for id in 01 04 08 11 19; do
  src="$(find "$ROOT/testcase/loop_hybrid" -maxdepth 1 -name "$id"_*.c -print -quit)"
  summary_log="$OUT_DIR/$id.summary.log"
  baseline_log="$OUT_DIR/$id.baseline.log"
  summary_work="$OUT_DIR/work-$id-summary"
  baseline_work="$OUT_DIR/work-$id-baseline"
  mkdir -p "$summary_work" "$baseline_work"

  common=( -q --maxloop 64 --maxpaths 40 --volce
           --volce-lower -4 --volce-upper 8 "$src" )
  summary_ok=0
  baseline_ok=0
  (cd "$summary_work" && timeout "$TIMEOUT_SECONDS" "$CNIP" "${common[@]}")     >"$summary_log" 2>&1 && summary_ok=1
  (cd "$baseline_work" && timeout "$TIMEOUT_SECONDS" env       EPPATHER_DISABLE_VOLCE_LOOP_SUMMARIES=1 "$CNIP" "${common[@]}")     >"$baseline_log" 2>&1 && baseline_ok=1

  summary_count="$(metric '\[VOLCE SOLUTION SPACE COUNT\]' "$summary_log")"
  baseline_count="$(metric '\[VOLCE SOLUTION SPACE COUNT\]' "$baseline_log")"
  summary_avg="$(metric '\[VOLCE WEIGHTED AVERAGE MEMS\]' "$summary_log")"
  baseline_avg="$(metric '\[VOLCE WEIGHTED AVERAGE MEMS\]' "$baseline_log")"
  applied="$(metric '\[VOLCE LOOP SUMMARIES APPLIED\]' "$summary_log" |     awk '{s+=$1} END {print s+0}')"
  rejected="$(metric '\[VOLCE LOOP SUMMARIES REJECTED\]' "$summary_log" |     awk '{s+=$1} END {print s+0}')"

  status=PASS
  (( summary_ok == 1 && baseline_ok == 1 )) || status=FAIL
  [[ "$summary_count" =~ ^[0-9]+$ ]] || status=FAIL
  [[ "$baseline_count" =~ ^[0-9]+$ ]] || status=FAIL
  [[ "$summary_count" == "$baseline_count" ]] || status=FAIL
  [[ -n "$summary_avg" && "$summary_avg" == "$baseline_avg" ]] || status=FAIL
  (( applied > 0 )) || status=FAIL

  printf '%s,%s,%s,%s,%s,%s,%s,%s\n'     "$id" "$status" "${summary_count:-N/A}" "${baseline_count:-N/A}"     "$applied" "$rejected" "${summary_avg:-N/A}" "${baseline_avg:-N/A}"     >> "$OUT_DIR/summary.csv"
done

cat "$OUT_DIR/summary.csv"
awk -F, 'NR>1 && $2!="PASS" {bad=1} END {exit bad}' "$OUT_DIR/summary.csv"
