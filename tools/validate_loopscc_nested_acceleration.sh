#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
CNIP="${CNIP:-$ROOT/build_ci_volce_summary/cnip}"
OUT_DIR="${OUT_DIR:-$ROOT/loopscc-nested-results}"
mkdir -p "$OUT_DIR"

run_mode() {
  local name="$1" accelerate="$2"
  EPPATHER_LOOP_SCC_ANALYZE=1 \
  EPPATHER_LOOP_SCC_ACCEL_VALIDATE=1 \
  EPPATHER_LOOP_SCC_ACCELERATE="$accelerate" \
    "$CNIP" -q --maxloop 1 --maxpaths 100 \
      --volce --volce-lower -8 --volce-upper 8 \
      "$ROOT/testcase/loop_hybrid/26_nested_scalar_inside_out.c" \
      >"$OUT_DIR/$name.log" 2>&1
}

metric_max() {
  local label="$1" log="$2"
  sed -n "s/^\\[$label\\]: //p" "$log" | sort -nr | head -1
}

run_mode baseline 0
run_mode accelerated 1

if ! grep -Eq '^\[LOOPSCC INSIDE OUT NESTED SUMMARIES\]: [1-9][0-9]*' "$OUT_DIR/baseline.log"; then
  echo "nested baseline: inner loop was not summarized inside-out" >&2
  cat "$OUT_DIR/baseline.log" >&2
  exit 1
fi

if ! grep -q '^\[LOOPSCC DFS SHORTCUT USED\]:' "$OUT_DIR/accelerated.log"; then
  echo "nested accelerated: certified outer shortcut was not used" >&2
  cat "$OUT_DIR/accelerated.log" >&2
  exit 1
fi

if ! grep -Eq '^\[LOOPSCC ACCELERATION PLAN\]: .*iterations=3 .*mems_preserving=1 skippable_iterations=3 exact=1' "$OUT_DIR/baseline.log"; then
  echo "nested baseline: missing exact outer three-iteration plan" >&2
  cat "$OUT_DIR/baseline.log" >&2
  exit 1
fi

if ! grep -Eq '^\[LOOPSCC COMPRESSED VOLCE\]: .*count_match=1 weighted_match=1' "$OUT_DIR/baseline.log"; then
  echo "nested baseline: compressed outer summary changed count/wMEMS" >&2
  cat "$OUT_DIR/baseline.log" >&2
  exit 1
fi

baseline_space="$(metric_max 'VOLCE SOLUTION SPACE COUNT' "$OUT_DIR/baseline.log")"
accelerated_space="$(metric_max 'VOLCE SOLUTION SPACE COUNT' "$OUT_DIR/accelerated.log")"
baseline_mem="$(metric_max 'DFS MAX MEMS' "$OUT_DIR/baseline.log")"
accelerated_mem="$(metric_max 'DFS MAX MEMS' "$OUT_DIR/accelerated.log")"
baseline_paths="$(grep -c '^feasible!!!' "$OUT_DIR/baseline.log" || true)"
accelerated_paths="$(grep -c '^feasible!!!' "$OUT_DIR/accelerated.log" || true)"
baseline_coverage="$(grep '^\[COVERAGE SIGNATURE\]: ' "$OUT_DIR/baseline.log" | sort -u | tr '\n' ';')"
accelerated_coverage="$(grep '^\[COVERAGE SIGNATURE\]: ' "$OUT_DIR/accelerated.log" | sort -u | tr '\n' ';')"

if [[ -z "$baseline_space" || "$baseline_space" != "$accelerated_space" ]]; then
  echo "nested accelerated: solution space differs" >&2
  exit 1
fi
if [[ -z "$baseline_mem" || "$baseline_mem" != "$accelerated_mem" ]]; then
  echo "nested accelerated: MEMS differs" >&2
  exit 1
fi
if [[ "$baseline_paths" != "$accelerated_paths" ]]; then
  echo "nested accelerated: feasible path count differs" >&2
  exit 1
fi
if [[ -z "$baseline_coverage" || "$baseline_coverage" != "$accelerated_coverage" ]]; then
  echo "nested accelerated: coverage signature differs" >&2
  echo "baseline=$baseline_coverage" >&2
  echo "accelerated=$accelerated_coverage" >&2
  exit 1
fi

echo "mode,solution_space,max_mems,feasible_paths,inside_out_summaries"
echo "baseline,$baseline_space,$baseline_mem,$baseline_paths,$(metric_max 'LOOPSCC INSIDE OUT NESTED SUMMARIES' "$OUT_DIR/baseline.log")"
echo "accelerated,$accelerated_space,$accelerated_mem,$accelerated_paths,$(metric_max 'LOOPSCC INSIDE OUT NESTED SUMMARIES' "$OUT_DIR/accelerated.log")"
