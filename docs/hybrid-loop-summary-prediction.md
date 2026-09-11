# Hybrid loop summary and prediction

Eppather now uses one loop-analysis contract for DFS, DFS2, MaxMemsDP and
GreedyDFS.

## Policy

1. Canonical affine `for` loops receive an exact closed-form trip-count
   summary. Direct and reversed comparisons, positive/negative constant steps,
   prefix/postfix increments and compound updates are recognized.
2. If the proved count is larger than `--maxloop`, the result is explicitly
   classified as `ConservativeUnroll`; it is not reported as exact.
3. Data-dependent or unsupported loops use `AdaptiveFallback`. Existing
   dataset runners may retry nearby bounds and must report that the result
   remains maxloop-dependent.
4. The contract intentionally leaves room for a LoopSCC backend. LoopSCC may
   provide a state-transition summary later, but memory/pointer semantics must
   be validated before such a summary can bypass unfolding.

This first integration does **not** claim full LoopSCC state summarization. It
adds the safe hybrid decision layer and exact affine trip-count summaries that
can be used today without changing MEMS or VolCE semantics.

## Validation

Run:

```bash
bash tools/validate_hybrid_loops.sh
```

The suite contains exactly 20 loop programs, including ascending, descending,
reversed-condition, non-unit-step, zero-trip, nested, multi-branch, array,
pointer, early-exit, data-dependent `while`, and mixed loops. It performs:

- 20 predictor oracle checks;
- ISO C syntax compilation for all 20 programs;
- optional Eppather DFS2 execution for all 20 when `build/cnip` exists;
- CSV output under `loop-hybrid-results/`.

The predictor CSV reports mode 0 as exact summary, mode 1 as conservative
unrolling and mode 2 as adaptive fallback.
