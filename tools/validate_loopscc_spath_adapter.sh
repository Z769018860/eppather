#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
CNIP="${CNIP:-$ROOT/build_ci_volce_summary/cnip}"
OUT_DIR="${OUT_DIR:-$ROOT/loopscc-spath-results}"
mkdir -p "$OUT_DIR"

run_case() {
  local name="$1" source="$2" maxloop="$3" maxpaths="${4:-12}"
  local log="$OUT_DIR/$name.log"
  EPPATHER_LOOP_SCC_ANALYZE=1 "$CNIP" -q \
    --maxloop "$maxloop" --maxpaths "$maxpaths" "$ROOT/$source" >"$log" 2>&1
  if ! grep -q '^\[LOOPSCC SPATHS\]: ' "$log"; then
    echo "$name: missing LoopSCC structural metrics" >&2
    cat "$log" >&2
    return 1
  fi
}

metric_max() {
  local label="$1" log="$2"
  sed -n "s/^\\[$label\\]: //p" "$log" | sort -nr | head -1
}

run_case oscillation testcase/loop_hybrid/22_spath_oscillation.c 4
osc_spaths="$(metric_max 'LOOPSCC SPATHS' "$OUT_DIR/oscillation.log")"
osc_multi="$(metric_max 'LOOPSCC MULTI-NODE SCCS' "$OUT_DIR/oscillation.log")"
osc_complete="$(metric_max 'LOOPSCC GRAPH COMPLETE' "$OUT_DIR/oscillation.log")"
if [[ -z "$osc_spaths" || "$osc_spaths" -lt 2 ||
      -z "$osc_multi" || "$osc_multi" -lt 1 ||
      "$osc_complete" != 1 ]]; then
  echo "oscillation: expected >=2 SPaths, a multi-node SCC, complete graph" >&2
  cat "$OUT_DIR/oscillation.log" >&2
  exit 1
fi

run_case periodic testcase/loop_hybrid/23_spath_determinate_cycle.c 4 100
periodic_cycles="$(metric_max 'LOOPSCC DETERMINATE CYCLES' "$OUT_DIR/periodic.log")"
periodic_osc="$(metric_max 'LOOPSCC OSCILLATING CYCLES' "$OUT_DIR/periodic.log")"
periodic_candidates="$(metric_max 'LOOPSCC CLOSED FORM CANDIDATES' "$OUT_DIR/periodic.log")"
periodic_max="$(metric_max 'LOOPSCC MAX PERIOD' "$OUT_DIR/periodic.log")"
periodic_complete="$(metric_max 'LOOPSCC GRAPH COMPLETE' "$OUT_DIR/periodic.log")"
if [[ -z "$periodic_cycles" || "$periodic_cycles" -lt 1 ||
      -z "$periodic_osc" || "$periodic_osc" -lt 1 ||
      -z "$periodic_candidates" || "$periodic_candidates" -lt 1 ||
      "$periodic_max" != 2 || "$periodic_complete" != 1 ]]; then
  echo "periodic: expected one proved period-2 guarded closed-form candidate" >&2
  cat "$OUT_DIR/periodic.log" >&2
  exit 1
fi
if ! grep -q '^\[LOOPSCC PERIOD TRANSFORM\]: x_after_period=x
  echo "periodic: missing exact canonical period transform for x" >&2
  cat "$OUT_DIR/periodic.log" >&2
  exit 1
fi
if ! grep -Eq '^\[LOOPSCC PHASE TRACE\]: complete=1 matched=1 period=2 entry_phase=[01] iterations=4 full_periods=2 residual=0$' "$OUT_DIR/periodic.log"; then
  echo "periodic: concrete path was not mapped to two complete periods" >&2
  cat "$OUT_DIR/periodic.log" >&2
  exit 1
fi

run_case nested testcase/loop_hybrid/12_nested_for.c 4
nested_complete="$(sed -n 's/^\[LOOPSCC GRAPH COMPLETE\]: //p' "$OUT_DIR/nested.log" | sort -n | head -1)"
if [[ "$nested_complete" != 0 ]]; then
  echo "nested: expected conservative incomplete outer graph" >&2
  cat "$OUT_DIR/nested.log" >&2
  exit 1
fi
if ! grep -q '^\[LOOPSCC DIAGNOSTIC\]: nested loop requires inside-out LoopSCC summary$' "$OUT_DIR/nested.log"; then
  echo "nested: missing inside-out fallback diagnostic" >&2
  cat "$OUT_DIR/nested.log" >&2
  exit 1
fi

echo "case,spaths,multi_node_sccs,determinate_cycles,oscillating_cycles,closed_form_candidates,max_period,complete"
echo "oscillation,$osc_spaths,$osc_multi,$(metric_max 'LOOPSCC DETERMINATE CYCLES' "$OUT_DIR/oscillation.log"),$(metric_max 'LOOPSCC OSCILLATING CYCLES' "$OUT_DIR/oscillation.log"),$(metric_max 'LOOPSCC CLOSED FORM CANDIDATES' "$OUT_DIR/oscillation.log"),$(metric_max 'LOOPSCC MAX PERIOD' "$OUT_DIR/oscillation.log"),$osc_complete"
echo "periodic,$(metric_max 'LOOPSCC SPATHS' "$OUT_DIR/periodic.log"),$(metric_max 'LOOPSCC MULTI-NODE SCCS' "$OUT_DIR/periodic.log"),$periodic_cycles,$periodic_osc,$periodic_candidates,$periodic_max,$periodic_complete"
echo "nested,$(metric_max 'LOOPSCC SPATHS' "$OUT_DIR/nested.log"),$(metric_max 'LOOPSCC MULTI-NODE SCCS' "$OUT_DIR/nested.log"),$(metric_max 'LOOPSCC DETERMINATE CYCLES' "$OUT_DIR/nested.log"),$(metric_max 'LOOPSCC OSCILLATING CYCLES' "$OUT_DIR/nested.log"),$(metric_max 'LOOPSCC CLOSED FORM CANDIDATES' "$OUT_DIR/nested.log"),$(metric_max 'LOOPSCC MAX PERIOD' "$OUT_DIR/nested.log"),$nested_complete"
 "$OUT_DIR/periodic.log"; then
  echo "periodic: missing exact canonical period transform for x" >&2
  cat "$OUT_DIR/periodic.log" >&2
  exit 1
fi
if ! grep -Eq '^\[LOOPSCC PHASE TRACE\]: complete=1 matched=1 period=2 entry_phase=[01] iterations=4 full_periods=2 residual=0$' "$OUT_DIR/periodic.log"; then
  echo "periodic: concrete path was not mapped to two complete periods" >&2
  cat "$OUT_DIR/periodic.log" >&2
  exit 1
fi

run_case nested testcase/loop_hybrid/12_nested_for.c 4
nested_complete="$(sed -n 's/^\[LOOPSCC GRAPH COMPLETE\]: //p' "$OUT_DIR/nested.log" | sort -n | head -1)"
if [[ "$nested_complete" != 0 ]]; then
  echo "nested: expected conservative incomplete outer graph" >&2
  cat "$OUT_DIR/nested.log" >&2
  exit 1
fi
if ! grep -q '^\[LOOPSCC DIAGNOSTIC\]: nested loop requires inside-out LoopSCC summary$' "$OUT_DIR/nested.log"; then
  echo "nested: missing inside-out fallback diagnostic" >&2
  cat "$OUT_DIR/nested.log" >&2
  exit 1
fi

echo "case,spaths,multi_node_sccs,determinate_cycles,oscillating_cycles,closed_form_candidates,max_period,complete"
echo "oscillation,$osc_spaths,$osc_multi,$(metric_max 'LOOPSCC DETERMINATE CYCLES' "$OUT_DIR/oscillation.log"),$(metric_max 'LOOPSCC OSCILLATING CYCLES' "$OUT_DIR/oscillation.log"),$(metric_max 'LOOPSCC CLOSED FORM CANDIDATES' "$OUT_DIR/oscillation.log"),$(metric_max 'LOOPSCC MAX PERIOD' "$OUT_DIR/oscillation.log"),$osc_complete"
echo "periodic,$(metric_max 'LOOPSCC SPATHS' "$OUT_DIR/periodic.log"),$(metric_max 'LOOPSCC MULTI-NODE SCCS' "$OUT_DIR/periodic.log"),$periodic_cycles,$periodic_osc,$periodic_candidates,$periodic_max,$periodic_complete"
echo "nested,$(metric_max 'LOOPSCC SPATHS' "$OUT_DIR/nested.log"),$(metric_max 'LOOPSCC MULTI-NODE SCCS' "$OUT_DIR/nested.log"),$(metric_max 'LOOPSCC DETERMINATE CYCLES' "$OUT_DIR/nested.log"),$(metric_max 'LOOPSCC OSCILLATING CYCLES' "$OUT_DIR/nested.log"),$(metric_max 'LOOPSCC CLOSED FORM CANDIDATES' "$OUT_DIR/nested.log"),$(metric_max 'LOOPSCC MAX PERIOD' "$OUT_DIR/nested.log"),$nested_complete"
