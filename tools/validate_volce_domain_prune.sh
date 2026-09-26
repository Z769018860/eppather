#!/usr/bin/env bash
set -euo pipefail
IFS=$'\n\t'

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
CNIP="${CNIP:-$ROOT/build_ci_array_pointer/cnip}"
OUT_DIR="${OUT_DIR:-$ROOT/volce-domain-prune-results}"
MANIFEST="$ROOT/testcase/probmems_array_pointer/domain_prune.csv"

rm -rf "$OUT_DIR"
mkdir -p "$OUT_DIR"

EPPATHER_VOLCE_DOMAIN_PRUNE=1 \
MANIFEST="$MANIFEST" \
OUT_DIR="$OUT_DIR" \
LOWER=-1 UPPER=1 \
MAXPATHS=100 TIMEOUT_SECONDS=60 \
CNIP="$CNIP" \
  bash "$ROOT/tools/run_array_pointer_projection_experiment.sh"

summary="$OUT_DIR/summary.csv"
if [[ ! -f "$summary" ]]; then
  echo "domain-prune: missing summary.csv" >&2
  exit 1
fi

for id in ap13 ap16; do
  for mode in scalar memory; do
    log="$OUT_DIR/logs/$id.$mode.log"
    row="$(awk -F, -v id="$id" -v mode="$mode" '
      NR > 1 && $1 == id && $5 == mode { print; exit }
    ' "$summary")"
    if [[ -z "$row" ]]; then
      echo "$id/$mode: missing summary row" >&2
      exit 1
    fi
    status="$(printf '%s\n' "$row" | awk -F, '{print $7}')"
    paths="$(printf '%s\n' "$row" | awk -F, '{print $8}')"
    count="$(printf '%s\n' "$row" | awk -F, '{print $9}')"
    avg="$(printf '%s\n' "$row" | awk -F, '{print $10}')"
    maxmem="$(printf '%s\n' "$row" | awk -F, '{print $11}')"

    if [[ "$status" != PASS ]]; then
      echo "$id/$mode: expected PASS, got $status" >&2
      cat "$log" >&2
      exit 1
    fi
    if [[ ! "$paths" =~ ^[0-9]+$ || "$paths" -lt 1 || "$paths" -gt 4 ]]; then
      echo "$id/$mode: expected a small domain-reachable path set, got $paths" >&2
      cat "$log" >&2
      exit 1
    fi
    if [[ "$count" == N/A* || "$avg" == N/A* || "$maxmem" == N/A* ]]; then
      echo "$id/$mode: missing completed VolCE/MEMS metrics" >&2
      cat "$log" >&2
      exit 1
    fi

    checks="$(sed -n 's/^\[VOLCE DOMAIN PREFIX CHECKS\]: //p' "$log" | tail -1)"
    pruned="$(sed -n 's/^\[VOLCE DOMAIN PREFIX PRUNED\]: //p' "$log" | tail -1)"
    if [[ ! "$checks" =~ ^[0-9]+$ || "$checks" -lt 1 ||
          ! "$pruned" =~ ^[0-9]+$ || "$pruned" -lt 1 ]]; then
      echo "$id/$mode: domain pruning did not prove/prune any prefix" >&2
      cat "$log" >&2
      exit 1
    fi
  done
done

echo "id,mode,path_count,solution_space_count,weighted_average_mems,dfs_max_mems,prefix_checks,prefix_pruned"
for id in ap13 ap16; do
  for mode in scalar memory; do
    row="$(awk -F, -v id="$id" -v mode="$mode" '
      NR > 1 && $1 == id && $5 == mode { print; exit }
    ' "$summary")"
    log="$OUT_DIR/logs/$id.$mode.log"
    echo "$id,$mode,$(printf '%s\n' "$row" | awk -F, '{print $8","$9","$10","$11}'),$(sed -n 's/^\[VOLCE DOMAIN PREFIX CHECKS\]: //p' "$log" | tail -1),$(sed -n 's/^\[VOLCE DOMAIN PREFIX PRUNED\]: //p' "$log" | tail -1)"
  done
done


# Semantic A/B oracle on a subject that already completed before pruning.
# Count and wMEMS must be identical because both modes describe the same
# configured VolCE population. DFS path count / max MEMS may decrease because
# zero-weight paths outside that finite population are no longer explored.
AB_MANIFEST="$ROOT/testcase/probmems_array_pointer/domain_prune_ab.csv"
AB_BASE="$OUT_DIR/ab-baseline"
AB_PRUNED="$OUT_DIR/ab-pruned"

MANIFEST="$AB_MANIFEST" OUT_DIR="$AB_BASE" LOWER=-1 UPPER=1 \
MAXPATHS=100 TIMEOUT_SECONDS=60 CNIP="$CNIP" \
  bash "$ROOT/tools/run_array_pointer_projection_experiment.sh" >/dev/null

EPPATHER_VOLCE_DOMAIN_PRUNE=1 \
MANIFEST="$AB_MANIFEST" OUT_DIR="$AB_PRUNED" LOWER=-1 UPPER=1 \
MAXPATHS=100 TIMEOUT_SECONDS=60 CNIP="$CNIP" \
  bash "$ROOT/tools/run_array_pointer_projection_experiment.sh" >/dev/null

for mode in scalar memory; do
  base_row="$(awk -F, -v mode="$mode" '
    NR > 1 && $1 == "ap17" && $5 == mode { print; exit }
  ' "$AB_BASE/summary.csv")"
  prune_row="$(awk -F, -v mode="$mode" '
    NR > 1 && $1 == "ap17" && $5 == mode { print; exit }
  ' "$AB_PRUNED/summary.csv")"

  base_status="$(printf '%s\n' "$base_row" | awk -F, '{print $7}')"
  prune_status="$(printf '%s\n' "$prune_row" | awk -F, '{print $7}')"
  base_paths="$(printf '%s\n' "$base_row" | awk -F, '{print $8}')"
  prune_paths="$(printf '%s\n' "$prune_row" | awk -F, '{print $8}')"
  base_count="$(printf '%s\n' "$base_row" | awk -F, '{print $9}')"
  prune_count="$(printf '%s\n' "$prune_row" | awk -F, '{print $9}')"
  base_avg="$(printf '%s\n' "$base_row" | awk -F, '{print $10}')"
  prune_avg="$(printf '%s\n' "$prune_row" | awk -F, '{print $10}')"
  base_max="$(printf '%s\n' "$base_row" | awk -F, '{print $11}')"
  prune_max="$(printf '%s\n' "$prune_row" | awk -F, '{print $11}')"

  if [[ "$base_status" != PASS || "$prune_status" != PASS ]]; then
    echo "ap17/$mode: A/B run did not complete" >&2
    exit 1
  fi
  if [[ "$base_count" != "$prune_count" || "$base_avg" != "$prune_avg" ]]; then
    echo "ap17/$mode: finite-domain count/wMEMS changed under pruning" >&2
    echo "baseline count=$base_count avg=$base_avg" >&2
    echo "pruned   count=$prune_count avg=$prune_avg" >&2
    exit 1
  fi
  if (( prune_paths > base_paths )); then
    echo "ap17/$mode: pruning increased DFS path count" >&2
    exit 1
  fi
  if [[ "$base_max" =~ ^[0-9]+$ && "$prune_max" =~ ^[0-9]+$ ]] &&
     (( prune_max > base_max )); then
    echo "ap17/$mode: pruning increased finite-domain max MEMS" >&2
    exit 1
  fi
  echo "AB,ap17,$mode,baseline_paths=$base_paths,pruned_paths=$prune_paths,count=$base_count,wmems=$base_avg,baseline_max=$base_max,pruned_max=$prune_max"
done
