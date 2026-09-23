#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
CNIP="${CNIP:-$ROOT/build_ci_volce_summary/cnip}"
OUT_DIR="${OUT_DIR:-$ROOT/loopscc-spath-results}"
mkdir -p "$OUT_DIR"

run_case() {
  local name="$1" source="$2" maxloop="$3"
  local maxpaths="${4:-12}" with_volce="${5:-0}" debug="${6:-0}" accelerate="${7:-0}"
  local log="$OUT_DIR/$name.log"
  local args=(-q --maxloop "$maxloop" --maxpaths "$maxpaths")

  if [[ "$with_volce" == "1" ]]; then
    args+=(--volce --volce-lower -8 --volce-upper 8)
  fi

  if [[ "$debug" == "1" ]]; then
    args+=(-c)
    EPPATHER_LOOP_SCC_ANALYZE=1 \
    EPPATHER_LOOP_SCC_ACCEL_VALIDATE=1 \
    EPPATHER_LOOP_SCC_ACCELERATE="$accelerate" \
    EPPATHER_LOOP_SCC_BOUND_TRACE=1 \
    EPPATHER_DEBUG_EPAT_SCRIPT=1 \
      "$CNIP" "${args[@]}" "$ROOT/$source" >"$log" 2>&1
  else
    EPPATHER_LOOP_SCC_ANALYZE=1 \
    EPPATHER_LOOP_SCC_ACCEL_VALIDATE=1 \
    EPPATHER_LOOP_SCC_ACCELERATE="$accelerate" \
      "$CNIP" "${args[@]}" "$ROOT/$source" >"$log" 2>&1
  fi

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

# Ambiguous oscillation must remain structural-only.
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

# Baseline: full unfolded execution even though --maxloop is deliberately 1.
run_case periodic testcase/loop_hybrid/23_spath_determinate_cycle.c 1 100 1
periodic_cycles="$(metric_max 'LOOPSCC DETERMINATE CYCLES' "$OUT_DIR/periodic.log")"
periodic_osc="$(metric_max 'LOOPSCC OSCILLATING CYCLES' "$OUT_DIR/periodic.log")"
periodic_candidates="$(metric_max 'LOOPSCC CLOSED FORM CANDIDATES' "$OUT_DIR/periodic.log")"
periodic_max="$(metric_max 'LOOPSCC MAX PERIOD' "$OUT_DIR/periodic.log")"
periodic_complete="$(metric_max 'LOOPSCC GRAPH COMPLETE' "$OUT_DIR/periodic.log")"
periodic_relations="$(metric_max 'VOLCE LOOPSCC AFFINE RELATIONS APPLIED' "$OUT_DIR/periodic.log")"
periodic_rejected="$(metric_max 'VOLCE LOOPSCC AFFINE RELATIONS REJECTED' "$OUT_DIR/periodic.log")"
periodic_trip_count="$(metric_max 'LOOPSCC PROVED TRIP COUNT' "$OUT_DIR/periodic.log")"
periodic_accel_plans="$(metric_max 'LOOPSCC EXACT ACCELERATION PLANS' "$OUT_DIR/periodic.log")"

if [[ -z "$periodic_cycles" || "$periodic_cycles" -lt 1 ||
      -z "$periodic_osc" || "$periodic_osc" -lt 1 ||
      -z "$periodic_candidates" || "$periodic_candidates" -lt 1 ||
      "$periodic_max" != 2 || "$periodic_complete" != 1 ]]; then
  echo "periodic: expected one proved period-2 guarded closed-form candidate" >&2
  cat "$OUT_DIR/periodic.log" >&2
  exit 1
fi

if ! grep -q '^\[LOOPSCC PERIOD TRANSFORM\]: state_after_period=0$' "$OUT_DIR/periodic.log"; then
  echo "periodic: missing exact period transform state_after_period=0" >&2
  cat "$OUT_DIR/periodic.log" >&2
  exit 1
fi

if ! grep -Eq '^\[LOOPSCC PHASE TRACE\]: complete=1 matched=1 period=2 entry_phase=[01] iterations=4 full_periods=2 residual=0$' "$OUT_DIR/periodic.log"; then
  echo "periodic: concrete path was not mapped to two complete periods" >&2
  cat "$OUT_DIR/periodic.log" >&2
  exit 1
fi

if ! grep -Eq '^\[LOOPSCC CYCLE\]: .*phase_guards_proved=1 .*closed_form_candidate=1$' "$OUT_DIR/periodic.log"; then
  echo "periodic: deterministic phase guards were not proved" >&2
  cat "$OUT_DIR/periodic.log" >&2
  exit 1
fi

if ! grep -Eq '^\[LOOPSCC ACCELERATION PLAN\]: .*mems_preserving=1 skippable_iterations=4 exact=1$' "$OUT_DIR/periodic.log"; then
  echo "periodic: missing MEMS-preserving four-iteration shortcut certificate" >&2
  cat "$OUT_DIR/periodic.log" >&2
  exit 1
fi

if [[ "$periodic_trip_count" != 4 ]]; then
  echo "periodic: expected LoopSCC to prove four iterations despite --maxloop 1" >&2
  cat "$OUT_DIR/periodic.log" >&2
  exit 1
fi

if [[ -z "$periodic_accel_plans" || "$periodic_accel_plans" -lt 2 ]]; then
  echo "periodic: expected exact T^k plans for both entry phases" >&2
  cat "$OUT_DIR/periodic.log" >&2
  exit 1
fi

if ! grep -q '^\[LOOPSCC ACCELERATION TRACE\]: matched=1 ' "$OUT_DIR/periodic.log"; then
  echo "periodic: symbolic T^k plan did not match unfolded phase semantics" >&2
  cat "$OUT_DIR/periodic.log" >&2
  exit 1
fi

if ! grep -Eq '^\[LOOPSCC COMPRESSED VALIDATION\]: attempted=1 matched=1 status_match=1 mem_match=1 original_decisions=[0-9]+ compressed_decisions=[0-9]+ baseline_mem=[0-9]+ compressed_mem=[0-9]+$' "$OUT_DIR/periodic.log"; then
  echo "periodic: compressed acceleration path did not preserve feasibility/MEMS" >&2
  cat "$OUT_DIR/periodic.log" >&2
  exit 1
fi

if ! grep -Eq '^\[LOOPSCC COMPRESSED VOLCE\]: baseline_count=[0-9]+ compressed_count=[0-9]+ count_match=1 weighted_match=1$' "$OUT_DIR/periodic.log"; then
  echo "periodic: compressed acceleration path changed solution count/wMEMS contribution" >&2
  cat "$OUT_DIR/periodic.log" >&2
  exit 1
fi

if [[ -z "$periodic_relations" || "$periodic_relations" -lt 1 ]]; then
  echo "periodic: expected at least one SMT-entailed LoopSCC affine relation" >&2
  cat "$OUT_DIR/periodic.log" >&2
  exit 1
fi

if [[ -n "$periodic_rejected" && "$periodic_rejected" -gt 0 ]]; then
  echo "periodic: guarded periodic relation was unexpectedly rejected" >&2
  cat "$OUT_DIR/periodic.log" >&2
  exit 1
fi

# Execute the same subject with the certified DFS shortcut enabled.
run_case periodic_accel testcase/loop_hybrid/23_spath_determinate_cycle.c 1 100 1 0 1
if ! grep -q '^\[LOOPSCC DFS SHORTCUT USED\]:' "$OUT_DIR/periodic_accel.log"; then
  echo "periodic_accel: certified DFS shortcut was not used" >&2
  cat "$OUT_DIR/periodic_accel.log" >&2
  exit 1
fi

baseline_space="$(metric_max 'VOLCE SOLUTION SPACE COUNT' "$OUT_DIR/periodic.log")"
shortcut_space="$(metric_max 'VOLCE SOLUTION SPACE COUNT' "$OUT_DIR/periodic_accel.log")"
baseline_maxmem="$(metric_max 'DFS MAX MEMS' "$OUT_DIR/periodic.log")"
shortcut_maxmem="$(metric_max 'DFS MAX MEMS' "$OUT_DIR/periodic_accel.log")"
baseline_feasible="$(grep -c '^feasible!!!$' "$OUT_DIR/periodic.log" || true)"
shortcut_feasible="$(grep -c '^feasible!!!$' "$OUT_DIR/periodic_accel.log" || true)"
baseline_coverage="$(grep '^\[COVERAGE SIGNATURE\]: ' "$OUT_DIR/periodic.log" | sort -u | tr '\n' ';')"
shortcut_coverage="$(grep '^\[COVERAGE SIGNATURE\]: ' "$OUT_DIR/periodic_accel.log" | sort -u | tr '\n' ';')"

if [[ -z "$baseline_space" || "$baseline_space" != "$shortcut_space" ]]; then
  echo "periodic_accel: VolCE solution space differs from unfolded baseline" >&2
  echo "baseline=$baseline_space shortcut=$shortcut_space" >&2
  cat "$OUT_DIR/periodic_accel.log" >&2
  exit 1
fi

if [[ -z "$baseline_maxmem" || "$baseline_maxmem" != "$shortcut_maxmem" ]]; then
  echo "periodic_accel: maximum MEMS differs from unfolded baseline" >&2
  echo "baseline=$baseline_maxmem shortcut=$shortcut_maxmem" >&2
  cat "$OUT_DIR/periodic_accel.log" >&2
  exit 1
fi

if [[ "$baseline_feasible" != "$shortcut_feasible" ]]; then
  echo "periodic_accel: feasible path count differs from unfolded baseline" >&2
  echo "baseline=$baseline_feasible shortcut=$shortcut_feasible" >&2
  cat "$OUT_DIR/periodic_accel.log" >&2
  exit 1
fi

if [[ -z "$baseline_coverage" || "$baseline_coverage" != "$shortcut_coverage" ]]; then
  echo "periodic_accel: coverage signature differs from unfolded baseline" >&2
  echo "baseline=$baseline_coverage" >&2
  echo "shortcut=$shortcut_coverage" >&2
  cat "$OUT_DIR/periodic_accel.log" >&2
  exit 1
fi

# Nested loops remain conservative until inside-out SCC composition exists.
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

echo "case,spaths,multi_node_sccs,determinate_cycles,oscillating_cycles,closed_form_candidates,max_period,complete,entailed_affine_relations,proved_trip_count,exact_acceleration_plans"
echo "oscillation,$osc_spaths,$osc_multi,$(metric_max 'LOOPSCC DETERMINATE CYCLES' "$OUT_DIR/oscillation.log"),$(metric_max 'LOOPSCC OSCILLATING CYCLES' "$OUT_DIR/oscillation.log"),$(metric_max 'LOOPSCC CLOSED FORM CANDIDATES' "$OUT_DIR/oscillation.log"),$(metric_max 'LOOPSCC MAX PERIOD' "$OUT_DIR/oscillation.log"),$osc_complete,0,N/A,0"
echo "periodic,$(metric_max 'LOOPSCC SPATHS' "$OUT_DIR/periodic.log"),$(metric_max 'LOOPSCC MULTI-NODE SCCS' "$OUT_DIR/periodic.log"),$periodic_cycles,$periodic_osc,$periodic_candidates,$periodic_max,$periodic_complete,$periodic_relations,$periodic_trip_count,$periodic_accel_plans"
echo "nested,$(metric_max 'LOOPSCC SPATHS' "$OUT_DIR/nested.log"),$(metric_max 'LOOPSCC MULTI-NODE SCCS' "$OUT_DIR/nested.log"),$(metric_max 'LOOPSCC DETERMINATE CYCLES' "$OUT_DIR/nested.log"),$(metric_max 'LOOPSCC OSCILLATING CYCLES' "$OUT_DIR/nested.log"),$(metric_max 'LOOPSCC CLOSED FORM CANDIDATES' "$OUT_DIR/nested.log"),$(metric_max 'LOOPSCC MAX PERIOD' "$OUT_DIR/nested.log"),$nested_complete,0,N/A,0"
