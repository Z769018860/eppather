#!/usr/bin/env bash
set -u

ROOT=$(cd "$(dirname "$0")/.." && pwd)
CNIP=${CNIP:-"$ROOT/cnip"}
MAXLOOP=${MAXLOOP:-1}
MAXPATHS=${MAXPATHS:-80}
RUN_TIMEOUT=${RUN_TIMEOUT:-120}
OUTDIR=${OUTDIR:-"/tmp/eppather-llm-summary-validation"}
mkdir -p "$OUTDIR"

export LD_LIBRARY_PATH="$ROOT/C:$ROOT:$ROOT/common:$ROOT/libParser/z3/bin:$ROOT/lpsolve${LD_LIBRARY_PATH:+:$LD_LIBRARY_PATH}"

failures=0
for source in "$ROOT"/testcase/llm_summaries/*.c; do
    name=$(basename "$source" .c)
    cc -std=c11 -Wall -Wextra -Wpedantic -c "$source" -o "$OUTDIR/$name.o" \
        >"$OUTDIR/$name.compile.log" 2>&1
    compile_rc=$?

    timeout "$RUN_TIMEOUT" "$CNIP" -q --maxloop "$MAXLOOP" --maxpaths "$MAXPATHS" "$source" \
        >"$OUTDIR/$name.dfs.log" 2>&1
    dfs_rc=$?
    timeout "$RUN_TIMEOUT" "$CNIP" -g --maxloop "$MAXLOOP" --maxpaths "$MAXPATHS" "$source" \
        >"$OUTDIR/$name.dp.log" 2>&1
    dp_rc=$?

    dfs_mem=$(sed -n 's/^\[DFS MAX MEMS\]: //p' "$OUTDIR/$name.dfs.log" | tail -1)
    dp_mem=$(sed -n 's/^MEMS: //p' "$OUTDIR/$name.dp.log" | tail -1)
    status=PASS
    if [ "$compile_rc" -ne 0 ] || [ "$dfs_rc" -ne 0 ] || [ "$dp_rc" -ne 0 ] || \
       [ -z "$dfs_mem" ] || [ -z "$dp_mem" ] || [ "$dfs_mem" != "$dp_mem" ]; then
        status=FAIL
        failures=$((failures + 1))
    fi
    printf '%s compile=%s dfs=%s dp=%s dfs_mems=%s dp_mems=%s %s\n' \
        "$name" "$compile_rc" "$dfs_rc" "$dp_rc" "${dfs_mem:-N/A}" "${dp_mem:-N/A}" "$status"
done

exit "$failures"
