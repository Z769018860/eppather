# LoopSCC SPath / CSG, acceleration, and memory certificates (2026-09-24)

## Current status

PR #98 now goes beyond structural SPath/CSG observation. The implementation
contains an opt-in certified DFS shortcut for a restricted class of determinate
scalar loops, while retaining bounded unfolding as the fallback.

The last completed green baseline before the newest nested/memory commits was
`VolCE loop state summaries #189` on head `8b355c7...`. It validated:

- period-2 symbolic acceleration with `--maxloop 1` and proved trip count 4;
- residual phase composition;
- symbolic entry phases;
- compressed-path feasibility and MEMS equivalence;
- VolCE solution-count and weighted-MEMS agreement;
- affine relation entailment and SSA-chain compression.

The newest head additionally contains inside-out scalar nesting, certified
`for` shortcuts, and array/pointer memory-access certificates. Those newest
changes remain subject to the current CI queue and should not be described as
green until the new runs finish.

## Certified scalar acceleration pipeline

With `EPPATHER_LOOP_SCC_ANALYZE=1`:

1. enumerate acyclic one-iteration SPaths;
2. record guards, writes, coverage slots, and scalar affine transforms;
3. build the SPath graph, Tarjan SCCs, and contracted CSG;
4. recognize determinate closed cycles conservatively;
5. prove phase transitions by interval inclusion;
6. prove an exact trip count when every returning SPath applies the same affine
   step to the loop-control variable;
7. derive one symbolic acceleration plan per possible entry phase;
8. compute `T^k` for complete periods and compose the proved residual phase;
9. compare the symbolic plan against the ordinary unfolded path in validation
   mode;
10. preserve selected scalar SSA provenance;
11. require VolCE to prove
    `path_formula => (x_exit = a*x_entry+b)`;
12. allow an entailed relation to participate in deterministic SSA-definition
    elimination;
13. build a compressed path containing the entry guard, entry-phase guard,
    closed-form assignments, and exit guard;
14. compare compressed vs unfolded feasibility, MEMS, solution-space count,
    weighted-MEMS contribution, and coverage;
15. only with `EPPATHER_LOOP_SCC_ACCELERATE=1` may a certified plan replace
    ordinary DFS unfolding.

Residual phases are supported; the shortcut is not restricted to a whole
number of periods.

## Safety certificates

A shortcut currently requires all of the following:

- complete SPath enumeration;
- a determinate cycle;
- proved phase guards;
- exact trip count;
- exact affine composition without overflow;
- all skipped SPaths represented by the supported scalar-effect model;
- no unresolved memory state or opaque call/effect;
- complete coverage union for skipped phases;
- a feasible compressed summary before DFS suppresses the unfolded fallback.

Ambiguous guards, unsupported scalar updates, opaque calls, unresolved memory
effects, incomplete SPath graphs, or failed SMT checks keep the original
unfolded execution.

## Inside-out nested loops

The newest branch code recursively analyzes a nested loop before the outer
SPath. A nested loop can be replaced inside the outer SPath only when every
possible nested acceleration plan has the same exact externally visible
transform and the same coverage certificate.

Implemented details include:

- scalar nested `while` summaries;
- canonical nested `for` summaries;
- constant `for` initializer folding;
- removal of C99 `for (int j=...)` local induction state from the outer
  summary;
- preservation of a pre-declared induction variable in `for (j=...)`;
- hiding raw inner-loop decisions when matching an outer phase trace;
- opt-in certified DFS shortcut for both `while` and `for` loops.

End-to-end A/B fixtures exist for both nested scalar while and nested scalar
for. The existing array-writing nested benchmark remains a required fallback.

## Array/pointer memory certificate substrate

The newest stage deliberately does **not** accelerate memory-dependent loops
yet. Instead each SPath records:

- source fragments containing memory accesses;
- array-subscript count;
- pointer-dereference count;
- whether memory is written;
- whether the restricted memory-access recognizer is complete;
- observed MEMS, using the same metric as epat++:
  one per ArraySubscript AST node and one per pointer dereference.

CI probes use the existing `16_array_scan.c` and `17_pointer_walk.c`
subjects. They must expose non-zero memory/MEMS certificates while producing
zero exact acceleration plans.

This separates two questions that were previously conflated:

1. can the skipped memory cost be accounted for exactly?
2. can the memory **state transition** be summarized without violating alias
   semantics?

Only (1) is now instrumented. Memory-dependent shortcuts remain disabled until
(2) has an alias-aware proof.

## What remains

The next LoopSCC work is:

1. finish CI validation of inside-out nested scalar shortcuts;
2. define canonical memory-region transitions for fixed cells/ranges;
3. connect those transitions to the existing VolCE canonical memory
   projections and alias checks;
4. prove read/write MEMS compensation against epat++ MemVisitor;
5. admit only alias-safe memory summaries into the DFS shortcut;
6. extend from independent scalar transforms to coupled multi-variable affine
   transforms;
7. evaluate the final implementation across the 20 loop cases plus the
   array/pointer/VLA suite at several `maxloop` settings.

Until memory-transition proofs are implemented, array/pointer loops remain
fallback cases even when their MEMS observations are precise.

### Fixed-memory shortcut safety gate (2026-09-24)

Fixed-cell local-array summaries support exact structural T^k composition, explicit MEMS compensation, VolCE memory-relation entailment, and untouched-region frame validation. Runtime replacement remains opt-in via `EPPATHER_LOOP_SCC_MEMORY_ACCELERATE=1` and is admitted only when a **pre-execution structural certificate** is available: the SPath graph/trip count/phase cycle are proved complete, every participating memory access is precisely accounted, pointer dereferences are absent, every array token is a constant in-bounds access to a uniquely named one-dimensional fixed local array, and every memory write is covered by the fixed-cell closed form. VolCE relation/frame entailment and model-count/wMEMS A/B remain independent post-hoc oracles for validating this certificate rule. Pointer, symbolic-index, cross-cell, ambiguous-region, VLA/unknown-region, and opaque effects continue to fall back to unfolding.
