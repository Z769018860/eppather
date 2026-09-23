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

compare_modes() {
  local baseline="$1" shortcut="$2"
  local baseline_log="$OUT_DIR/$baseline.log"
  local shortcut_log="$OUT_DIR/$shortcut.log"

  local baseline_space shortcut_space
  local baseline_maxmem shortcut_maxmem
  local baseline_feasible shortcut_feasible
  local baseline_coverage shortcut_coverage

  baseline_space="$(metric_max 'VOLCE SOLUTION SPACE COUNT' "$baseline_log")"
  shortcut_space="$(metric_max 'VOLCE SOLUTION SPACE COUNT' "$shortcut_log")"
  baseline_maxmem="$(metric_max 'DFS MAX MEMS' "$baseline_log")"
  shortcut_maxmem="$(metric_max 'DFS MAX MEMS' "$shortcut_log")"
  baseline_feasible="$(grep -c '^feasible!!!' "$baseline_log" || true)"
  shortcut_feasible="$(grep -c '^feasible!!!' "$shortcut_log" || true)"
  baseline_coverage="$(grep '^\[COVERAGE SIGNATURE\]: ' "$baseline_log" | sort -u | tr '\n' ';')"
  shortcut_coverage="$(grep '^\[COVERAGE SIGNATURE\]: ' "$shortcut_log" | sort -u | tr '\n' ';')"

  if [[ -z "$baseline_space" || "$baseline_space" != "$shortcut_space" ]]; then
    echo "$shortcut: VolCE solution space differs from unfolded baseline" >&2
    echo "baseline=$baseline_space shortcut=$shortcut_space" >&2
    cat "$shortcut_log" >&2
    return 1
  fi
  if [[ -z "$baseline_maxmem" || "$baseline_maxmem" != "$shortcut_maxmem" ]]; then
    echo "$shortcut: maximum MEMS differs from unfolded baseline" >&2
    echo "baseline=$baseline_maxmem shortcut=$shortcut_maxmem" >&2
    cat "$shortcut_log" >&2
    return 1
  fi
  if [[ "$baseline_feasible" != "$shortcut_feasible" ]]; then
    echo "$shortcut: feasible path count differs from unfolded baseline" >&2
    echo "baseline=$baseline_feasible shortcut=$shortcut_feasible" >&2
    cat "$shortcut_log" >&2
    return 1
  fi
  if [[ -z "$baseline_coverage" || "$baseline_coverage" != "$shortcut_coverage" ]]; then
    echo "$shortcut: coverage signature differs from unfolded baseline" >&2
    echo "baseline=$baseline_coverage" >&2
    echo "shortcut=$shortcut_coverage" >&2
    cat "$shortcut_log" >&2
    return 1
  fi
}

# 1. Ambiguous oscillation remains structural-only.
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

# 2. Period-2, four exact iterations. maxloop=1 must be lifted by proof.
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
if [[ "$periodic_trip_count" != 4 ]]; then
  echo "periodic: expected proved trip count 4 despite --maxloop 1" >&2
  cat "$OUT_DIR/periodic.log" >&2
  exit 1
fi
if [[ -z "$periodic_accel_plans" || "$periodic_accel_plans" -lt 2 ]]; then
  echo "periodic: expected exact T^k plans for both entry phases" >&2
  cat "$OUT_DIR/periodic.log" >&2
  exit 1
fi
if ! grep -q '^\[LOOPSCC PERIOD TRANSFORM\]: state_after_period=0' "$OUT_DIR/periodic.log"; then
  echo "periodic: missing exact period transform state_after_period=0" >&2
  cat "$OUT_DIR/periodic.log" >&2
  exit 1
fi
if ! grep -Eq '^\[LOOPSCC PHASE TRACE\]: complete=1 matched=1 period=2 entry_phase=[01] iterations=4 full_periods=2 residual=0' "$OUT_DIR/periodic.log"; then
  echo "periodic: concrete path was not mapped to two complete periods" >&2
  cat "$OUT_DIR/periodic.log" >&2
  exit 1
fi
if ! grep -Eq '^\[LOOPSCC CYCLE\]: .*phase_guards_proved=1 .*closed_form_candidate=1' "$OUT_DIR/periodic.log"; then
  echo "periodic: deterministic phase guards were not proved" >&2
  cat "$OUT_DIR/periodic.log" >&2
  exit 1
fi
if ! grep -Eq '^\[LOOPSCC ACCELERATION PLAN\]: .*mems_preserving=1 skippable_iterations=4 exact=1' "$OUT_DIR/periodic.log"; then
  echo "periodic: missing MEMS-preserving shortcut certificate" >&2
  cat "$OUT_DIR/periodic.log" >&2
  exit 1
fi
if ! grep -q '^\[LOOPSCC ACCELERATION TRACE\]: matched=1 ' "$OUT_DIR/periodic.log"; then
  echo "periodic: symbolic T^k plan did not match unfolded semantics" >&2
  cat "$OUT_DIR/periodic.log" >&2
  exit 1
fi
if ! grep -Eq '^\[LOOPSCC COMPRESSED VALIDATION\]: attempted=1 matched=1 status_match=1 mem_match=1 ' "$OUT_DIR/periodic.log"; then
  echo "periodic: compressed path did not preserve feasibility/MEMS" >&2
  cat "$OUT_DIR/periodic.log" >&2
  exit 1
fi
if ! grep -Eq '^\[LOOPSCC COMPRESSED VOLCE\]: .*count_match=1 weighted_match=1' "$OUT_DIR/periodic.log"; then
  echo "periodic: compressed path changed model count/wMEMS contribution" >&2
  cat "$OUT_DIR/periodic.log" >&2
  exit 1
fi
if [[ -z "$periodic_relations" || "$periodic_relations" -lt 1 ||
      ( -n "$periodic_rejected" && "$periodic_rejected" -gt 0 ) ]]; then
  echo "periodic: expected accepted, unrejected LoopSCC affine relation" >&2
  cat "$OUT_DIR/periodic.log" >&2
  exit 1
fi

run_case periodic_accel testcase/loop_hybrid/23_spath_determinate_cycle.c 1 100 1 0 1
if ! grep -q '^\[LOOPSCC DFS SHORTCUT USED\]:' "$OUT_DIR/periodic_accel.log"; then
  echo "periodic_accel: certified DFS shortcut was not used" >&2
  cat "$OUT_DIR/periodic_accel.log" >&2
  exit 1
fi
compare_modes periodic periodic_accel

# 3. Residual phase: five iterations = 2 complete periods + 1 residual.
run_case residual testcase/loop_hybrid/25_spath_residual_cycle.c 1 100 1
run_case residual_accel testcase/loop_hybrid/25_spath_residual_cycle.c 1 100 1 0 1
if ! grep -Eq '^\[LOOPSCC ACCELERATION PLAN\]: .*iterations=5 .*period=2 .*full_periods=2 .*residual=1 .*mems_preserving=1 skippable_iterations=5 exact=1' "$OUT_DIR/residual.log"; then
  echo "residual: missing exact two-period-plus-residual plan" >&2
  cat "$OUT_DIR/residual.log" >&2
  exit 1
fi
if ! grep -q '^\[LOOPSCC DFS SHORTCUT USED\]:' "$OUT_DIR/residual_accel.log"; then
  echo "residual_accel: certified residual shortcut was not used" >&2
  cat "$OUT_DIR/residual_accel.log" >&2
  exit 1
fi
if ! grep -Eq '^\[LOOPSCC COMPRESSED VALIDATION\]: attempted=1 matched=1 status_match=1 mem_match=1 ' "$OUT_DIR/residual.log"; then
  echo "residual: compressed residual path did not preserve feasibility/MEMS" >&2
  cat "$OUT_DIR/residual.log" >&2
  exit 1
fi
if ! grep -Eq '^\[LOOPSCC COMPRESSED VOLCE\]: .*count_match=1 weighted_match=1' "$OUT_DIR/residual.log"; then
  echo "residual: compressed residual path changed model count/wMEMS contribution" >&2
  cat "$OUT_DIR/residual.log" >&2
  exit 1
fi
compare_modes residual residual_accel

# 4. Symbolic entry phase: input x selects one of the two cycle phases.
run_case symbolic_entry testcase/loop_hybrid/24_spath_symbolic_entry_cycle.c 1 100 1
run_case symbolic_entry_accel testcase/loop_hybrid/24_spath_symbolic_entry_cycle.c 1 100 1 0 1
if ! grep -q '^\[LOOPSCC DFS SHORTCUT USED\]:' "$OUT_DIR/symbolic_entry_accel.log"; then
  echo "symbolic_entry_accel: certified shortcut was not used" >&2
  cat "$OUT_DIR/symbolic_entry_accel.log" >&2
  exit 1
fi
symbolic_feasible="$(grep -c '^feasible!!!' "$OUT_DIR/symbolic_entry.log" || true)"
symbolic_accel_feasible="$(grep -c '^feasible!!!' "$OUT_DIR/symbolic_entry_accel.log" || true)"
if [[ "$symbolic_feasible" -lt 2 ||
      "$symbolic_feasible" != "$symbolic_accel_feasible" ]]; then
  echo "symbolic_entry_accel: expected the same two input-selected phase paths" >&2
  echo "baseline=$symbolic_feasible shortcut=$symbolic_accel_feasible" >&2
  cat "$OUT_DIR/symbolic_entry_accel.log" >&2
  exit 1
fi
symbolic_weighted_matches="$(grep -c '^\[LOOPSCC COMPRESSED VOLCE\]: .*count_match=1 weighted_match=1' "$OUT_DIR/symbolic_entry.log" || true)"
if [[ "$symbolic_weighted_matches" -lt 2 ]]; then
  echo "symbolic_entry: expected both phase partitions to preserve count/wMEMS" >&2
  cat "$OUT_DIR/symbolic_entry.log" >&2
  exit 1
fi
compare_modes symbolic_entry symbolic_entry_accel

# 5. Safe scalar nested while-loops are summarized inside-out and may use
# the same certified DFS shortcut as flat determinate cycles.
run_case nested_while testcase/loop_hybrid/26_nested_scalar_inside_out.c 1 100 1
run_case nested_while_accel testcase/loop_hybrid/26_nested_scalar_inside_out.c 1 100 1 0 1
nested_while_inside_out="$(metric_max 'LOOPSCC INSIDE OUT NESTED SUMMARIES' "$OUT_DIR/nested_while.log")"
nested_while_complete="$(metric_max 'LOOPSCC GRAPH COMPLETE' "$OUT_DIR/nested_while.log")"
if [[ -z "$nested_while_inside_out" || "$nested_while_inside_out" -lt 1 ||
      "$nested_while_complete" != 1 ]]; then
  echo "nested_while: expected complete inside-out outer summary" >&2
  cat "$OUT_DIR/nested_while.log" >&2
  exit 1
fi
if ! grep -q '^\[LOOPSCC DFS SHORTCUT USED\]:' "$OUT_DIR/nested_while_accel.log"; then
  echo "nested_while_accel: certified outer shortcut was not used" >&2
  cat "$OUT_DIR/nested_while_accel.log" >&2
  exit 1
fi
compare_modes nested_while nested_while_accel

# 6. Safe scalar nested for-loops are summarized inside-out and may use
# the same certified DFS shortcut as flat determinate cycles.
run_case nested_scalar testcase/loop_hybrid/26_spath_nested_scalar_for.c 1 100 1
run_case nested_scalar_accel testcase/loop_hybrid/26_spath_nested_scalar_for.c 1 100 1 0 1
nested_inside_out="$(metric_max 'LOOPSCC INSIDE OUT NESTED SUMMARIES' "$OUT_DIR/nested_scalar.log")"
nested_complete="$(metric_max 'LOOPSCC GRAPH COMPLETE' "$OUT_DIR/nested_scalar.log")"
if [[ -z "$nested_inside_out" || "$nested_inside_out" -lt 1 ||
      "$nested_complete" != 1 ]]; then
  echo "nested_scalar: expected a complete outer graph with inside-out nested summary" >&2
  cat "$OUT_DIR/nested_scalar.log" >&2
  exit 1
fi
if ! grep -q '^\[LOOPSCC DIAGNOSTIC\]: inside-out summarized nested loop:' "$OUT_DIR/nested_scalar.log"; then
  echo "nested_scalar: missing inside-out summary diagnostic" >&2
  cat "$OUT_DIR/nested_scalar.log" >&2
  exit 1
fi
if ! grep -q '^\[LOOPSCC DFS SHORTCUT USED\]:' "$OUT_DIR/nested_scalar_accel.log"; then
  echo "nested_scalar_accel: certified outer shortcut was not used" >&2
  cat "$OUT_DIR/nested_scalar_accel.log" >&2
  exit 1
fi
compare_modes nested_scalar nested_scalar_accel

# 7. Array/pointer loops expose exact MEMS observations but remain outside
# scalar-only acceleration until an alias-aware memory transition is proved.
run_case array_memory_probe testcase/loop_hybrid/16_array_scan.c 1 100
array_memory_spaths="$(metric_max 'LOOPSCC MEMORY SPATHS' "$OUT_DIR/array_memory_probe.log")"
array_memory_mems="$(metric_max 'LOOPSCC OBSERVED MEMORY MEMS' "$OUT_DIR/array_memory_probe.log")"
array_accel="$(metric_max 'LOOPSCC EXACT ACCELERATION PLANS' "$OUT_DIR/array_memory_probe.log")"
if [[ -z "$array_memory_spaths" || "$array_memory_spaths" -lt 1 ||
      -z "$array_memory_mems" || "$array_memory_mems" -lt 1 ||
      "$array_accel" != 0 ]]; then
  echo "array_memory_probe: expected MEMS certificate with acceleration fallback" >&2
  cat "$OUT_DIR/array_memory_probe.log" >&2
  exit 1
fi

run_case pointer_memory_probe testcase/loop_hybrid/17_pointer_walk.c 1 100
pointer_memory_spaths="$(metric_max 'LOOPSCC MEMORY SPATHS' "$OUT_DIR/pointer_memory_probe.log")"
pointer_memory_mems="$(metric_max 'LOOPSCC OBSERVED MEMORY MEMS' "$OUT_DIR/pointer_memory_probe.log")"
pointer_accel="$(metric_max 'LOOPSCC EXACT ACCELERATION PLANS' "$OUT_DIR/pointer_memory_probe.log")"
if [[ -z "$pointer_memory_spaths" || "$pointer_memory_spaths" -lt 1 ||
      -z "$pointer_memory_mems" || "$pointer_memory_mems" -lt 2 ||
      "$pointer_accel" != 0 ]]; then
  echo "pointer_memory_probe: expected pointer MEMS certificate with acceleration fallback" >&2
  cat "$OUT_DIR/pointer_memory_probe.log" >&2
  exit 1
fi

# 8. Fixed-cell writes may produce a machine-readable memory-transition
# candidate, but still must not authorize acceleration before VolCE/alias proof.
run_case fixed_cell_memory testcase/loop_hybrid/27_spath_fixed_cell_memory.c 1 100
fixed_cell_candidates="$(metric_max 'LOOPSCC MEMORY CELL TRANSITION CANDIDATES' "$OUT_DIR/fixed_cell_memory.log")"
fixed_cell_mems="$(metric_max 'LOOPSCC OBSERVED MEMORY MEMS' "$OUT_DIR/fixed_cell_memory.log")"
fixed_cell_accel="$(metric_max 'LOOPSCC EXACT ACCELERATION PLANS' "$OUT_DIR/fixed_cell_memory.log")"
if [[ -z "$fixed_cell_candidates" || "$fixed_cell_candidates" -lt 1 ||
      -z "$fixed_cell_mems" || "$fixed_cell_mems" -lt 2 ||
      "$fixed_cell_accel" != 0 ]]; then
  echo "fixed_cell_memory: expected transition candidate with acceleration fallback" >&2
  cat "$OUT_DIR/fixed_cell_memory.log" >&2
  exit 1
fi

# 9. Array-writing nested loops remain conservative because their memory
# transition is not yet alias-safe for inside-out acceleration.
run_case nested_memory testcase/loop_hybrid/12_nested_for.c 4
nested_memory_complete="$(sed -n 's/^\[LOOPSCC GRAPH COMPLETE\]: //p' "$OUT_DIR/nested_memory.log" | sort -n | head -1)"
if [[ "$nested_memory_complete" != 0 ]]; then
  echo "nested_memory: expected conservative incomplete outer graph" >&2
  cat "$OUT_DIR/nested_memory.log" >&2
  exit 1
fi
if ! grep -q '^\[LOOPSCC DIAGNOSTIC\]: nested loop requires inside-out LoopSCC summary' "$OUT_DIR/nested_memory.log"; then
  echo "nested_memory: missing alias-safe inside-out fallback diagnostic" >&2
  cat "$OUT_DIR/nested_memory.log" >&2
  exit 1
fi

echo "case,spaths,multi_node_sccs,determinate_cycles,oscillating_cycles,closed_form_candidates,max_period,complete,entailed_affine_relations,proved_trip_count,exact_acceleration_plans"
echo "oscillation,$osc_spaths,$osc_multi,$(metric_max 'LOOPSCC DETERMINATE CYCLES' "$OUT_DIR/oscillation.log"),$(metric_max 'LOOPSCC OSCILLATING CYCLES' "$OUT_DIR/oscillation.log"),$(metric_max 'LOOPSCC CLOSED FORM CANDIDATES' "$OUT_DIR/oscillation.log"),$(metric_max 'LOOPSCC MAX PERIOD' "$OUT_DIR/oscillation.log"),$osc_complete,0,N/A,0"
echo "periodic,$(metric_max 'LOOPSCC SPATHS' "$OUT_DIR/periodic.log"),$(metric_max 'LOOPSCC MULTI-NODE SCCS' "$OUT_DIR/periodic.log"),$periodic_cycles,$periodic_osc,$periodic_candidates,$periodic_max,$periodic_complete,$periodic_relations,$periodic_trip_count,$periodic_accel_plans"
echo "residual,$(metric_max 'LOOPSCC SPATHS' "$OUT_DIR/residual.log"),$(metric_max 'LOOPSCC MULTI-NODE SCCS' "$OUT_DIR/residual.log"),$(metric_max 'LOOPSCC DETERMINATE CYCLES' "$OUT_DIR/residual.log"),$(metric_max 'LOOPSCC OSCILLATING CYCLES' "$OUT_DIR/residual.log"),$(metric_max 'LOOPSCC CLOSED FORM CANDIDATES' "$OUT_DIR/residual.log"),$(metric_max 'LOOPSCC MAX PERIOD' "$OUT_DIR/residual.log"),$(metric_max 'LOOPSCC GRAPH COMPLETE' "$OUT_DIR/residual.log"),$(metric_max 'VOLCE LOOPSCC AFFINE RELATIONS APPLIED' "$OUT_DIR/residual.log"),$(metric_max 'LOOPSCC PROVED TRIP COUNT' "$OUT_DIR/residual.log"),$(metric_max 'LOOPSCC EXACT ACCELERATION PLANS' "$OUT_DIR/residual.log")"
echo "symbolic_entry,$(metric_max 'LOOPSCC SPATHS' "$OUT_DIR/symbolic_entry.log"),$(metric_max 'LOOPSCC MULTI-NODE SCCS' "$OUT_DIR/symbolic_entry.log"),$(metric_max 'LOOPSCC DETERMINATE CYCLES' "$OUT_DIR/symbolic_entry.log"),$(metric_max 'LOOPSCC OSCILLATING CYCLES' "$OUT_DIR/symbolic_entry.log"),$(metric_max 'LOOPSCC CLOSED FORM CANDIDATES' "$OUT_DIR/symbolic_entry.log"),$(metric_max 'LOOPSCC MAX PERIOD' "$OUT_DIR/symbolic_entry.log"),$(metric_max 'LOOPSCC GRAPH COMPLETE' "$OUT_DIR/symbolic_entry.log"),$(metric_max 'VOLCE LOOPSCC AFFINE RELATIONS APPLIED' "$OUT_DIR/symbolic_entry.log"),$(metric_max 'LOOPSCC PROVED TRIP COUNT' "$OUT_DIR/symbolic_entry.log"),$(metric_max 'LOOPSCC EXACT ACCELERATION PLANS' "$OUT_DIR/symbolic_entry.log")"
echo "nested_while,$(metric_max 'LOOPSCC SPATHS' "$OUT_DIR/nested_while.log"),$(metric_max 'LOOPSCC MULTI-NODE SCCS' "$OUT_DIR/nested_while.log"),$(metric_max 'LOOPSCC DETERMINATE CYCLES' "$OUT_DIR/nested_while.log"),$(metric_max 'LOOPSCC OSCILLATING CYCLES' "$OUT_DIR/nested_while.log"),$(metric_max 'LOOPSCC CLOSED FORM CANDIDATES' "$OUT_DIR/nested_while.log"),$(metric_max 'LOOPSCC MAX PERIOD' "$OUT_DIR/nested_while.log"),$nested_while_complete,$(metric_max 'VOLCE LOOPSCC AFFINE RELATIONS APPLIED' "$OUT_DIR/nested_while.log"),$(metric_max 'LOOPSCC PROVED TRIP COUNT' "$OUT_DIR/nested_while.log"),$(metric_max 'LOOPSCC EXACT ACCELERATION PLANS' "$OUT_DIR/nested_while.log")"
echo "nested_scalar,$(metric_max 'LOOPSCC SPATHS' "$OUT_DIR/nested_scalar.log"),$(metric_max 'LOOPSCC MULTI-NODE SCCS' "$OUT_DIR/nested_scalar.log"),$(metric_max 'LOOPSCC DETERMINATE CYCLES' "$OUT_DIR/nested_scalar.log"),$(metric_max 'LOOPSCC OSCILLATING CYCLES' "$OUT_DIR/nested_scalar.log"),$(metric_max 'LOOPSCC CLOSED FORM CANDIDATES' "$OUT_DIR/nested_scalar.log"),$(metric_max 'LOOPSCC MAX PERIOD' "$OUT_DIR/nested_scalar.log"),$nested_complete,$(metric_max 'VOLCE LOOPSCC AFFINE RELATIONS APPLIED' "$OUT_DIR/nested_scalar.log"),$(metric_max 'LOOPSCC PROVED TRIP COUNT' "$OUT_DIR/nested_scalar.log"),$(metric_max 'LOOPSCC EXACT ACCELERATION PLANS' "$OUT_DIR/nested_scalar.log")"
echo "nested_memory,$(metric_max 'LOOPSCC SPATHS' "$OUT_DIR/nested_memory.log"),$(metric_max 'LOOPSCC MULTI-NODE SCCS' "$OUT_DIR/nested_memory.log"),$(metric_max 'LOOPSCC DETERMINATE CYCLES' "$OUT_DIR/nested_memory.log"),$(metric_max 'LOOPSCC OSCILLATING CYCLES' "$OUT_DIR/nested_memory.log"),$(metric_max 'LOOPSCC CLOSED FORM CANDIDATES' "$OUT_DIR/nested_memory.log"),$(metric_max 'LOOPSCC MAX PERIOD' "$OUT_DIR/nested_memory.log"),$nested_memory_complete,0,N/A,0"
