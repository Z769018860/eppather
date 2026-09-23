#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
CNIP="${CNIP:-$ROOT/build_ci_volce_summary/cnip}"
OUT_DIR="${OUT_DIR:-$ROOT/loopscc-spath-results}"
mkdir -p "$OUT_DIR"

run_case() {
  local name="$1" source="$2" maxloop="$3"
  local log="$OUT_DIR/$name.log"
  EPPATHER_LOOP_SCC_ANALYZE=1 "$CNIP" -q     --maxloop "$maxloop" --maxpaths 12 "$ROOT/$source" >"$log" 2>&1
  if ! grep -q '^\[LOOPSCC SPATHS\]: ' "$log"; then
    echo "$name: missing LoopSCC structural metrics" >&2
    cat "$log" >&2
    return 1
  fi
}

run_case oscillation testcase/loop_hybrid/22_spath_oscillation.c 4
osc_spaths="$(sed -n 's/^\[LOOPSCC SPATHS\]: //p' "$OUT_DIR/oscillation.log" | sort -nr | head -1)"
osc_multi="$(sed -n 's/^\[LOOPSCC MULTI-NODE SCCS\]: //p' "$OUT_DIR/oscillation.log" | sort -nr | head -1)"
osc_complete="$(sed -n 's/^\[LOOPSCC GRAPH COMPLETE\]: //p' "$OUT_DIR/oscillation.log" | sort -nr | head -1)"
if [[ -z "$osc_spaths" || "$osc_spaths" -lt 2 ||
      -z "$osc_multi" || "$osc_multi" -lt 1 ||
      "$osc_complete" != 1 ]]; then
  echo "oscillation: expected >=2 SPaths, a multi-node SCC, complete graph" >&2
  cat "$OUT_DIR/oscillation.log" >&2
  exit 1
fi

run_case nested testcase/loop_hybrid/12_nested_for.c 4
nested_complete="$(sed -n 's/^\[LOOPSCC GRAPH COMPLETE\]: //p' "$OUT_DIR/nested.log" | sort -n | head -1)"
if [[ "$nested_complete" != 0 ]]; then
  echo "nested: expected conservative incomplete outer graph" >&2
  cat "$OUT_DIR/nested.log" >&2
  exit 1
fi
if ! grep -q '^\[LOOPSCC DIAGNOSTIC\]: nested loop requires inside-out LoopSCC summary' "$OUT_DIR/nested.log"; then
  echo "nested: missing inside-out fallback diagnostic" >&2
  cat "$OUT_DIR/nested.log" >&2
  exit 1
fi

echo "case,spaths,multi_node_sccs,complete"
echo "oscillation,$osc_spaths,$osc_multi,$osc_complete"
echo "nested,$(sed -n 's/^\[LOOPSCC SPATHS\]: //p' "$OUT_DIR/nested.log" | sort -nr | head -1),$(sed -n 's/^\[LOOPSCC MULTI-NODE SCCS\]: //p' "$OUT_DIR/nested.log" | sort -nr | head -1),$nested_complete"
