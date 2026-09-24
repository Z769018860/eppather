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
