#!/usr/bin/env bash
set -euo pipefail

CNIP_BIN="${1:-build2/cnip}"
REPEAT="${2:-3}"

if [[ ! -x "$CNIP_BIN" ]]; then
  echo "[ERROR] cnip binary not found or not executable: $CNIP_BIN" >&2
  exit 1
fi

if ! [[ "$REPEAT" =~ ^[0-9]+$ ]] || [[ "$REPEAT" -lt 1 ]]; then
  echo "[ERROR] repeat count must be a positive integer, got: $REPEAT" >&2
  exit 1
fi

TMP_DIR=$(mktemp -d)
trap 'rm -rf "$TMP_DIR"' EXIT

DP_CASES=(
  "testcase/dp_maxmem_single.c:4:80"
  "testcase/dp_maxmem_branch.c:2:20"
  "testcase/dp_maxmem_nested.c:3:80"
)

for round in $(seq 1 "$REPEAT"); do
  echo "[ROUND $round/$REPEAT]"

  for case_item in "${DP_CASES[@]}"; do
    IFS=':' read -r cfile expected maxpaths <<< "$case_item"

    if [[ ! -f "$cfile" ]]; then
      echo "[ERROR] missing testcase: $cfile" >&2
      exit 1
    fi

    dp_out="$TMP_DIR/dp_$(basename "$cfile")_$round.txt"
    dfs_out="$TMP_DIR/dfs_$(basename "$cfile")_$round.txt"

    "$CNIP_BIN" -g "$cfile" > "$dp_out"
    "$CNIP_BIN" -q --maxpaths "$maxpaths" "$cfile" > "$dfs_out"

    dp_mem=$(sed -n 's/^MEMS: //p' "$dp_out" | tail -n 1)
    dfs_max_mem=$(sed -n 's/^\[DFS MAX MEMS\]: //p' "$dfs_out" | tail -n 1)

    if [[ "$dp_mem" != "$expected" ]]; then
      echo "[ERROR] $cfile DP MEMS expected $expected, got: ${dp_mem:-<empty>}" >&2
      exit 1
    fi

    if [[ "$dfs_max_mem" != "$expected" ]]; then
      echo "[ERROR] $cfile DFS2 MAX MEMS expected $expected, got: ${dfs_max_mem:-<empty>}" >&2
      exit 1
    fi

    if [[ "$dp_mem" != "$dfs_max_mem" ]]; then
      echo "[ERROR] $cfile DP/DFS mismatch: DP=$dp_mem DFS=$dfs_max_mem" >&2
      exit 1
    fi

    echo "[OK] $cfile DP=$dp_mem DFS=$dfs_max_mem"
  done

  sum_out="$TMP_DIR/summary_$round.txt"
  "$CNIP_BIN" -s testcase/summary_global_multi.c > "$sum_out"

  sum_worst=$(sed -n 's/^worst_mems=//p' "$sum_out" | tail -n 1)
  if [[ "$sum_worst" != "3" ]]; then
    echo "[ERROR] summary worst_mems expected 3, got: ${sum_worst:-<empty>}" >&2
    exit 1
  fi

  if ! grep -q 'worst_path=main#0' "$sum_out" || ! grep -q 'helper#0' "$sum_out"; then
    echo "[ERROR] summary worst_path does not include both main and helper expansion." >&2
    exit 1
  fi

  echo "[OK] summary worst_mems=$sum_worst"
done

echo "[DONE] all $REPEAT round(s) passed"
