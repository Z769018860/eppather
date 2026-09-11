#!/usr/bin/env bash
set -euo pipefail
IFS=$'\n\t'

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
CNIP="${CNIP:-$ROOT/build_ci_volce_summary/cnip}"
OUT_DIR="${OUT_DIR:-$ROOT/volce-loop-summary-results}"
TIMEOUT_SECONDS="${TIMEOUT_SECONDS:-90}"
mkdir -p "$OUT_DIR"

printf 'id,status,solution_count,applied,rejected,weighted_average\n'   > "$OUT_DIR/summary.csv"
for id in 01 04 08 11 19; do
  src="$(find "$ROOT/testcase/loop_hybrid" -maxdepth 1 -name "$id"_*.c -print -quit)"
  log="$OUT_DIR/$id.log"
  if timeout "$TIMEOUT_SECONDS" "$CNIP" -q --maxloop 64 --maxpaths 40       --volce --volce-lower -4 --volce-upper 8 "$src" >"$log" 2>&1; then
    count="$(sed -n 's/^\[VOLCE SOLUTION SPACE COUNT\]: //p' "$log" | tail -1)"
    applied="$(sed -n 's/^\[VOLCE LOOP SUMMARIES APPLIED\]: //p' "$log" |       awk '{s+=$1} END {print s+0}')"
    rejected="$(sed -n 's/^\[VOLCE LOOP SUMMARIES REJECTED\]: //p' "$log" |       awk '{s+=$1} END {print s+0}')"
    avg="$(sed -n 's/^\[VOLCE WEIGHTED AVERAGE MEMS\]: //p' "$log" | tail -1)"
    status=PASS
    [[ "$count" =~ ^[0-9]+$ ]] || status=FAIL
    (( applied > 0 )) || status=FAIL
    printf '%s,%s,%s,%s,%s,%s\n' "$id" "$status" "${count:-N/A}"       "$applied" "$rejected" "${avg:-N/A}" >> "$OUT_DIR/summary.csv"
  else
    printf '%s,FAIL,N/A,0,0,N/A\n' "$id" >> "$OUT_DIR/summary.csv"
  fi
done
cat "$OUT_DIR/summary.csv"
awk -F, 'NR>1 && $2!="PASS" {bad=1} END {exit bad}' "$OUT_DIR/summary.csv"
