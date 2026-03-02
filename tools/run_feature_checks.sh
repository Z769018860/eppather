#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT_DIR"

BUILD_DIR="build_local"
CNIP="$BUILD_DIR/cnip"

cmake -S . -B "$BUILD_DIR" >/tmp/eppather_cmake.log
cmake --build "$BUILD_DIR" -j"$(nproc)" >/tmp/eppather_build.log

issues=()

# 1) DFS2 + feasible pruning + path/SMT/MEMS outputs
rm -f path_merge_*.txt smt_merge_*.txt result_merge_*.txt
if ! timeout 120 "$CNIP" -q --maxpaths 200 test2.c >/tmp/eppather_dfs2.log; then
  issues+=("DFS2 run failed or timed out")
fi

path_count=$(find . -maxdepth 1 -name 'path_merge_*.txt' | wc -l)
smt_count=$(find . -maxdepth 1 -name 'smt_merge_*.txt' | wc -l)
result_count=$(find . -maxdepth 1 -name 'result_merge_*.txt' | wc -l)
result_feasible_paths=$(rg -l '^feasible$' result_merge_*.txt 2>/dev/null | wc -l)
result_infeasible_paths=$( (rg -l '^infeasible$' result_merge_*.txt 2>/dev/null || true) | wc -l)

if [[ "$path_count" -eq 0 ]]; then
  issues+=("DFS2 produced zero path artifacts")
fi
if [[ "$path_count" -ne "$smt_count" || "$path_count" -ne "$result_count" ]]; then
  issues+=("DFS2 artifact count mismatch: path=$path_count smt=$smt_count result=$result_count")
fi
if [[ "$result_feasible_paths" -eq 0 ]]; then
  issues+=("DFS2 has no feasible result path")
fi

# 2) --volce range + per-path count/prob + weighted average mems
if ! timeout 120 "$CNIP" -q --maxpaths 20 --volce --volce-lower -4 --volce-upper 4 test.c >/tmp/eppather_volce.log; then
  issues+=("VolCE run failed or timed out")
fi

volce_range_line="$(rg -n "\[VOLCE RANGE\]: \[-4, 4\]" /tmp/eppather_volce.log | head -n 1 || true)"
volce_total_line="$(rg -n "\[VOLCE TOTAL COUNT \(LattE\)\]:" /tmp/eppather_volce.log | tail -n 1 || true)"
volce_weight_line="$(rg -n "\[WEIGHTED AVG MEMS BY PROB\]:" /tmp/eppather_volce.log | tail -n 1 || true)"
prob_sum="$(awk '{
  for(i=1;i<=NF;i++) if($i ~ /^prob=/){split($i,a,"="); s+=a[2]}
} END {printf "%.6f", s+0}' /tmp/eppather_volce.log)"

if [[ -z "$volce_range_line" ]]; then
  issues+=("VolCE range line missing or not [-4, 4]")
fi
if [[ -z "$volce_total_line" ]]; then
  issues+=("VolCE total model count line missing")
fi
if [[ -z "$volce_weight_line" ]]; then
  issues+=("VolCE weighted average MEMS line missing")
fi
awk -v p="$prob_sum" 'BEGIN{if (p<0.99 || p>1.01) exit 1}' || issues+=("VolCE path probabilities do not sum to ~1 (sum=$prob_sum)")

# 3) function summary + program worst path / weighted average (multi-function)
if ! timeout 120 "$CNIP" -s summary-test.c >/tmp/eppather_summary.log; then
  issues+=("summary run failed or timed out")
fi

summary_ready="$(rg -n "Function summaries are ready to dump" /tmp/eppather_summary.log | head -n 1 || true)"
program_summary="$(rg -n "\[PROGRAM SUMMARY\]" /tmp/eppather_summary.log | head -n 1 || true)"
worst_line="$(rg -n "^worst_mems=" /tmp/eppather_summary.log | tail -n 1 || true)"
weighted_line="$(rg -n "^weighted_avg_mems=" /tmp/eppather_summary.log | tail -n 1 || true)"
undefined_count="$(rg -c "find an undefined symbol" /tmp/eppather_summary.log || true)"

if [[ -z "$summary_ready" || -z "$program_summary" || -z "$worst_line" || -z "$weighted_line" ]]; then
  issues+=("summary output missing key program-summary lines")
fi
if [[ "${undefined_count:-0}" -gt 0 ]]; then
  issues+=("summary output contains undefined symbol warnings (count=$undefined_count)")
fi

cat <<REPORT
[CHECK 1] DFS2 feasible pruning / full path artifacts
  path files:   $path_count
  smt files:    $smt_count
  result files: $result_count
  feasible paths in results:   $result_feasible_paths
  infeasible paths in results: $result_infeasible_paths
  dfs2 time line: $(rg -n "\[DFS TIME COST\]" /tmp/eppather_dfs2.log | tail -n 1 || true)

[CHECK 2] VolCE range / model count / probabilities / weighted average
  range line: $volce_range_line
  total count: $volce_total_line
  weighted avg mems: $volce_weight_line
  probability sum: $prob_sum
  sample path prob lines:
$(rg -n "\[path [0-9]+\].*prob=" /tmp/eppather_volce.log | head -n 3 | sed 's/^/    /' || true)

[CHECK 3] Function summary / program-level worst + weighted average
  summary ready line: $summary_ready
  program summary line: $program_summary
  worst mems line: $worst_line
  weighted average line: $weighted_line
  undefined symbol warnings: ${undefined_count:-0}
REPORT

if [[ ${#issues[@]} -gt 0 ]]; then
  echo
  echo "[ISSUES DETECTED]"
  for issue in "${issues[@]}"; do
    echo "- $issue"
  done
  exit 2
fi

echo
echo "[ALL CHECKS PASSED]"
