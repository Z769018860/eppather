# MaxMEMS methodology audit for SANER 2027

Date: 2026-09-26  
PR: #110  
Primary performance run: https://github.com/Z769018860/eppather/actions/runs/36170356461

## Why this audit was added

The MaxMEMS recurrence memoizes a state keyed by the CFG node, loop counters,
and the complete serialized event prefix.  This key is deliberately
path-sensitive: two histories that reach the same control location are not
merged unless their complete prefixes are identical.  The design protects
feasibility and witness correctness, but it also raises a performance question:
does the memo table actually reuse states, or does the implementation behave
like a recursively implemented exhaustive search with pruning?

The instrumentation in this PR reports memo lookups, hits, misses, stores,
entries, and hit rate without changing the search semantics.

## Controlled DP/DFS performance audit

Configuration:

- subjects: the 20 controlled MaxMEMS witness programs;
- backend: Backend A (CMake `ANALYSIS_BACKEND=epat++`);
- repetitions: 3;
- `maxloop`: 4 for 18 subjects and 5 for two subjects;
- `maxpaths`: 1000;
- optional prefix feasibility: disabled;
- per analyzer process timeout: 120 s;
- reported search times: the analyzer's existing `[DP TIME COST]` and
  `[DFS TIME COST]` timers.

The first successful CI run produced:

| Metric | Result |
|---|---:|
| DP/DFS MaxMEMS equality | all 20 subjects in all 3 repetitions |
| Memo lookups | 1,767 |
| Memo hits | 0 |
| Memo misses | 1,767 |
| Memo hit rate | 0.0000 |
| Median summed DP search time per 20-subject repetition | 2.5063011 s |
| Median summed DFS search time per 20-subject repetition | 2.5196372 s |
| Median DFS/DP time ratio | 1.0016318x |

Per-repetition summed search times were:

| Repetition | DP (s) | DFS (s) | DFS/DP |
|---|---:|---:|---:|
| 1 | 2.5038011 | 2.4892473 | 0.9941873x |
| 2 | 2.5367022 | 2.5408416 | 1.0016318x |
| 3 | 2.5063011 | 2.5196372 | 1.0053210x |

## Interpretation

On this controlled suite the complete-prefix memo key yields no state reuse.
Therefore the memo table should be interpreted as a correctness-preserving
path-sensitive cache, not as evidence of dynamic-programming state
compression.  The measured DP and DFS search times are essentially the same on
this suite; no general MaxMEMS speedup claim is justified by these results.

This does not invalidate the bounded-optimality argument: the full-prefix key
still prevents unsound reuse across different path conditions.  It does mean
that memo-key fidelity is a correctness condition rather than an observed
performance mechanism.  Future optimization should only remove prefix
information after proving that the forgotten history cannot affect suffix
feasibility or cost.

## Loop-summary ablation

The current LoopSCC-derived/SSA-linked summary path has a separate fair A/B
evaluation (commit `bf9c9571d71f3d26ae94fb299e5a6363730ad1d9`,
`docs/scalar-ssa-provenance-validation-2026-09-19.md`):

- semantic A/B: 20/20 PASS;
- SSA-linked summary applied: 16/20 cases;
- ground validation only: 3/20;
- fallback: 1/20;
- rejected: 0;
- summary model-count time: 49,627 us;
- validation-only baseline model-count time: 48,521 us;
- baseline/summary count-time ratio: 0.9777x;
- end-to-end aggregate ratio: 0.9953x.

Thus the current summaries preserve the measured semantics on this suite but
do not improve model-counting performance.  The audit treats this as a
negative/neutral ablation result rather than as a speedup.

## Reproducible analysis parameters

| Study | Backend | maxloop | maxpaths | budget | prefix check |
|---|---|---:|---:|---:|---|
| Controlled witness | A | 4 (18), 5 (2) | 1000 | 120 s | off |
| Collected corpus | A | 3 | 1000 | 120 s | off |
| Historical regression | A | 3 | 1000 | 120 s | off |
| Timeout rescue | A | 3 | 1000 | 900 s | off |
| Small-library slices | B | 2 | 80 | 120 s | off |
| Selected cJSON/Lua/tinyexpr functions | B | 1 | 40 | 120 s | off |

The bundled Z3 version is 4.12.2.  MaxMEMS has a defensive recursion/search
depth guard of 1000.  Interprocedural function-summary composition uses at most
32 synchronous fixpoint iterations; this value is not a call-stack expansion
depth.
