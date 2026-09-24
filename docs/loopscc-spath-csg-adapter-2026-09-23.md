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

## Array/pointer and fixed-memory acceleration stage

The memory work is now split into three explicitly different classes.

### 1. Fixed local-array cells: opt-in shortcut implemented

For a restricted class of one-dimensional fixed local arrays, PR #98 now
constructs full-loop fixed-cell memory summaries and an independently guarded
DFS shortcut.

The admitted case requires all of the following before replacement:

- complete SPath graph and exact trip count;
- determinate cycle with proved phase guards;
- a unique fixed local-array declaration with a statically known extent;
- constant, in-bounds array indices only;
- every memory write represented by an exact fixed-cell affine transition;
- every memory access lexically accounted for with the same MEMS convention
  as epat++ MemVisitor;
- no pointer dereference, symbolic index, VLA/unknown extent, opaque call or
  unresolved memory effect;
- exact coverage union for skipped SPaths.

The compressed decision stream contains a loop-entry whole-memory checkpoint,
the scalar closed form, fixed-cell assignments and a cost-only
`SyntheticMems` decision. `SyntheticMems` emits no source/SMT semantics; it
restores the exact MEMS skipped by compression after epat++ solves the
compressed path.

VolCE remains an independent oracle. On the unfolded path it proves:

- the summarized fixed-cell entry-to-exit affine relation;
- the untouched frame for every other cell in the declared fixed region;
- model-count and weighted-MEMS equivalence between unfolded and compressed
  paths.

Runtime replacement is separately opt-in through
`EPPATHER_LOOP_SCC_MEMORY_ACCELERATE=1`. Positive A/B fixtures cover a single
updated cell and a two-cell frame where the untouched second cell remains
symbolic.

### 2. General array accesses: certificate/observation only

SPaths record source memory fragments, array-subscript counts, write status,
observer completeness and observed MEMS. Symbolic-index or otherwise
unresolved array transitions are still fallback cases and are never promoted
to the fixed-cell shortcut.

### 3. Pointer dereferences: fallback

Pointer reads/writes are counted for MEMS diagnostics, but the fixed-memory
pre-execution certificate deliberately rejects pointer dereferences. The next
pointer milestone is a narrow alias proof for pointers that can be bound
statically to a unique fixed local-array cell/range. General pointer arithmetic
and ambiguous aliasing remain out of scope for shortcut admission.

## What remains

The next LoopSCC work is:

1. finish the current CI rerun after the memory-observer regex fix and record
   the exact green run IDs;
2. add a conservative constant pointer-alias certificate
   (`p = a`, `p = &a[k]`) before admitting any dereference shortcut;
3. retain fallback for pointer arithmetic, symbolic aliases, symbolic array
   indices, VLA/unknown extents and cross-region ambiguity;
4. compose safe fixed-memory summaries inside-out for nested loops only after
   the flat fixed-cell A/B gate is stable;
5. extend independent scalar relations to coupled multi-variable affine
   transforms;
6. re-run the 20 loop subjects plus the 20 array/pointer/VLA subjects at
   multiple requested maxloop values and report path/MEMS/count/runtime deltas.


### Fixed-memory shortcut safety gate (2026-09-24)

Fixed-cell local-array summaries support exact structural T^k composition, explicit MEMS compensation, VolCE memory-relation entailment, and untouched-region frame validation. Runtime replacement remains opt-in via `EPPATHER_LOOP_SCC_MEMORY_ACCELERATE=1` and is admitted only when a **pre-execution structural certificate** is available: the SPath graph/trip count/phase cycle are proved complete, every participating memory access is precisely accounted, pointer dereferences are absent, every array token is a constant in-bounds access to a uniquely named one-dimensional fixed local array, and every memory write is covered by the fixed-cell closed form. VolCE relation/frame entailment and model-count/wMEMS A/B remain independent post-hoc oracles for validating this certificate rule. Pointer, symbolic-index, cross-cell, ambiguous-region, VLA/unknown-region, and opaque effects continue to fall back to unfolding.
