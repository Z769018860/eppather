# LoopSCC SPath / CSG structural adapter (2026-09-23)

## Purpose

This stage begins the control-flow part of LoopSCC integration after Eppather's
existing affine trip-count, source-to-SSA, VolCE entailment, SSA elimination,
and canonical memory-projection pipeline.

It is deliberately **structural-only**. The adapter does not replace a loop
body, change `--maxloop`, or add a new constraint to VolCE. Unsupported or
incomplete graphs therefore cannot change MEMS, feasibility, or model counts.

## Pipeline

For each loop selected by `EPPATHER_LOOP_SCC_ANALYZE=1`:

1. start from the loop true/body edge;
2. enumerate acyclic paths until the loop header is reached again or the path
   exits/returns;
3. record the loop guard and internal branch guards;
4. record scalar writes, simple affine self-updates, and a conservative memory
   write marker;
5. build the SPath transition graph. A candidate edge is removed only when
   recognized integer guard intervals plus an exact affine update prove the
   next SPath guard cannot hold;
6. run Tarjan SCC decomposition;
7. report SCC and contracted-graph (CSG) metrics.

The current affine parser recognizes increment/decrement, constant `+=/-=`,
`x=x+K`, `x=x-K`, and constant assignment. Unknown scalar writes and memory
writes remain conservative and cannot be used to remove an edge.

## Conservative fallbacks

The graph is marked incomplete when:

- a nested loop is encountered before an inside-out summary exists;
- an unexpected internal cycle occurs;
- SPath or per-path node budgets are exhausted;
- unsupported CFG structure prevents an acyclic one-iteration path.

An incomplete graph is diagnostic only. Existing bounded unfolding remains the
execution semantics.

## Metrics

When enabled, DFS2 result output includes:

- `[LOOPSCC SPATHS]`
- `[LOOPSCC TRANSITIONS]`
- `[LOOPSCC SCCS]`
- `[LOOPSCC CYCLIC SCCS]`
- `[LOOPSCC MULTI-NODE SCCS]`
- `[LOOPSCC MAX SCC SIZE]`
- `[LOOPSCC CSG EDGES]`
- `[LOOPSCC GRAPH COMPLETE]`

## Validation

`tests/LoopSccAdapterTests.cpp` covers:

1. one SPath with a self-cycle;
2. two oscillating branch SPaths forming one two-node SCC;
3. two SPaths whose graph contracts to two SCCs with one CSG edge;
4. nested-loop conservative fallback.

`tools/validate_loopscc_spath_adapter.sh` additionally runs the real Eppather
CFG/DFS2 pipeline on an oscillating branch loop and the existing nested-loop
subject.

## Next gate

The next implementation must use SCC-local transition structure to recognize a
restricted periodic/oscillating cycle pattern. A candidate closed form should
be exported only as a guarded transition and must pass the existing SMT
entailment check before it can influence VolCE. Memory-writing SPaths remain
excluded from summary replacement until an alias-aware memory transition is
proved.
