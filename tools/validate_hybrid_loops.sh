#!/usr/bin/env bash
set -euo pipefail
IFS=$'\n\t'

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
OUT_DIR="${OUT_DIR:-$ROOT/loop-hybrid-results}"
CNIP="${CNIP:-$ROOT/build/cnip}"
MAXPATHS="${MAXPATHS:-80}"
TIMEOUT_SECONDS="${TIMEOUT_SECONDS:-60}"
mkdir -p "$OUT_DIR/logs"

g++ -std=c++17 -Wall -Wextra -pedantic -I"$ROOT"   "$ROOT/tests/LoopBoundPredictorTests.cpp" -o "$OUT_DIR/loop_predictor_tests"
"$OUT_DIR/loop_predictor_tests" | tee "$OUT_DIR/predictor-results.csv"

printf 'id,compile,cnip_run,dfs_max_mems,reason\n' > "$OUT_DIR/integration-results.csv"
while IFS=, read -r id source category expected_mode expected_trip maxloop; do
  [[ "$id" == "id" ]] && continue
  src="$ROOT/$source"
  compile=PASS
  run=SKIP
  mems=N/A
  reason=CNIP_NOT_AVAILABLE
  if ! gcc -std=c11 -Wall -Wextra -pedantic -fsyntax-only "$src"       >"$OUT_DIR/logs/$id.gcc.log" 2>&1; then
    compile=FAIL
    reason=C_COMPILE_FAILURE
  elif [[ -x "$CNIP" ]]; then
    work="$OUT_DIR/work-$id"
    mkdir -p "$work"
    if (cd "$work" && timeout "$TIMEOUT_SECONDS" "$CNIP" -q         --maxloop "$maxloop" --maxpaths "$MAXPATHS" "$src")         >"$OUT_DIR/logs/$id.cnip.log" 2>&1; then
      mems="$(sed -n 's/^\[DFS MAX MEMS\]: //p'         "$OUT_DIR/logs/$id.cnip.log" | tail -1)"
      mems="${mems:-N/A}"
      if [[ "$mems" =~ ^[0-9]+$ ]]; then
        run=PASS
        reason=OK
      else
        run=FAIL
        reason=NO_FEASIBLE_MEMS
      fi
    else
      run=FAIL
      reason=CNIP_FAILURE_OR_TIMEOUT
    fi
  fi
  printf '%s,%s,%s,%s,%s\n' "$id" "$compile" "$run" "$mems" "$reason"     >> "$OUT_DIR/integration-results.csv"
done < "$ROOT/testcase/loop_hybrid/manifest.csv"

cat "$OUT_DIR/integration-results.csv"
awk -F, 'NR>1 && $2!="PASS" {bad=1} END {exit bad}'   "$OUT_DIR/integration-results.csv"
if [[ -x "$CNIP" ]]; then
  awk -F, 'NR>1 && ($3!="PASS" || $4 !~ /^[0-9]+$/) {bad=1} END {exit bad}'     "$OUT_DIR/integration-results.csv"
fi
