# LoopSCC SPath / CSG and guarded affine relations (2026-09-23)

## Purpose

This stage extends Eppather beyond scalar trip-count prediction into the
control-flow/state-transition part of LoopSCC. It remains conservative: every
new closed-form relation must be justified by the SPath/CSG structure and then
proved entailed by the complete path SMT formula before it can affect VolCE.

It is still **not a full LoopSCC implementation**. In particular, the branch
does not yet skip arbitrary loop unfolding or summarize memory-writing SCCs.

## Implemented pipeline

With `EPPATHER_LOOP_SCC_ANALYZE=1`:

1. enumerate acyclic one-iteration SPaths from the loop body edge to the loop
   header/exit;
2. record loop and branch guards, scalar writes, memory-write markers, and
   simple affine state transforms;
3. build a conservative SPath transition graph using recognized guard
   intervals and exact affine transforms;
4. compute Tarjan SCCs and the contracted CSG;
5. recognize a determinate closed cycle only when every SPath in the SCC has
   one unique internal successor and predecessor and no escape edge;
6. compose exact machine-readable transforms `x' = a*x+b` across each SPath
   and complete period;
7. map the concrete Eppather path back to its SPath phase sequence, recording
   entry phase, observed iterations, complete periods and residual phases;
8. compose a path-specific affine relation across the observed phase sequence;
9. preserve SSA provenance for variables in a proved guarded periodic
   candidate;
10. ask VolCE to prove `path_formula => (x_exit = a*x_entry+b)` by checking
    `path_formula AND NOT(relation)` for UNSAT;
11. only an entailed relation is marked applied. Rejected/ambiguous relations
    leave the existing bounded formula unchanged;
12. an applied relation may participate in the existing deterministic SSA
    definition-elimination pass. The validation-only baseline performs the same
    relation checks but does not assert the relation or eliminate the chain.

The current affine parser supports scale `-1`, `0`, and `1`, including
increment/decrement, constant `+=/-=`, `x=x+K`, `x=x-K`, constant
assignment, and sign flips such as `x=-x-1` / `x=0-x-1`.

## Safety boundaries and fallbacks

The graph or relation is not used when:

- SPath/node budgets are exceeded;
- a nested loop requires inside-out summarization;
- an unexpected internal CFG cycle is encountered;
- guards or writes make the transition ambiguous;
- a memory/dereference/array write participates in the candidate;
- a scalar write is not represented by the supported affine model;
- the concrete phase sequence does not match a proved determinate cycle;
- SSA entry/exit provenance is missing or ambiguous;
- the proposed affine relation is SAT/UNKNOWN under its negation rather than
  proven entailed.

These cases retain bounded unfolding and the existing VolCE semantics.

## Validation gates

Direct adapter tests cover:

1. one SPath/self-cycle;
2. an ambiguous oscillating SCC that must not be classified determinate;
3. a proved period-2 cycle;
4. contracted CSG edges;
5. nested-loop fallback.

VolCE unit regressions cover:

- an entailed periodic identity relation;
- a deliberately wrong relation that must be rejected;
- negative-scale relation `x'=-x-1`;
- equal model counts between optimized and validation-only modes;
- fewer counting assertions after an entailed periodic SSA chain is compressed.

The end-to-end periodic fixture uses a local initialized SSA state and a
four-iteration sign-flip loop. Its required chain is:

`CFG -> SPaths -> determinate period-2 cycle -> concrete phase trace -> SSA
provenance -> VolCE entailment -> optional SSA compression`.

The current PR head is still subject to the repository CI gates; do not report
the branch as merged or the new end-to-end gate as passing until those workflow
runs complete successfully.

## What remains

The next substantive LoopSCC step is no longer SPath/CSG construction or
relation validation. It is **safe loop acceleration**:

1. derive a symbolic number of complete periods rather than relying on the
   already-unfolded concrete phase sequence;
2. preserve the cycle-entry guard and residual-phase semantics;
3. replace repeated period bodies with the proved closed form only when the
   period count and exit condition are also proved;
4. handle nested SCCs inside-out;
5. extend multi-variable transforms beyond independent scalar relations;
6. keep array/pointer state behind alias-aware memory-transition proofs;
7. rerun exact solution-count, weighted-MEMS and maxloop-sensitivity A/B gates
   before claiming that LoopSCC removes the fixed-unroll limitation.
