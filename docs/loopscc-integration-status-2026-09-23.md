# LoopSCC / Eppather integration status (2026-09-23)

## Current scope

Eppather now contains a **restricted certified LoopSCC acceleration pipeline**,
not merely a structural adapter. It is still not a complete implementation of
the LoopSCC paper.

Implemented on PR #98:

1. canonical affine `for` and recoverable constant-bound `while` loops can
   obtain exact trip-count certificates and lift an insufficient requested
   `--maxloop`;
2. one-iteration SPaths, conservative transition graphs, Tarjan SCCs and the
   contracted CSG are built explicitly;
3. determinate cycles receive phase-guard proofs and machine-readable affine
   transforms;
4. symbolic `T^k` composition supports complete periods, residual phases and
   symbolic entry phases;
5. scalar SSA provenance is retained only for selected summarized variables;
6. VolCE accepts scalar affine relations only after SMT entailment and can then
   eliminate deterministic SSA definitions;
7. validation compares unfolded and compressed paths for feasibility, MEMS,
   coverage, solution-space count and weighted-MEMS contribution;
8. `EPPATHER_LOOP_SCC_ACCELERATE=1` enables the certified scalar DFS shortcut;
9. safe scalar nested loops are summarized inside-out before the outer SPath,
   including canonical nested `for` loops and C99 induction-variable scope;
10. array/pointer/VLA model counting uses bounded canonical memory projections
    with proved-independent projection factorization;
11. SPaths record memory accesses and exact epat++-compatible MEMS observations;
12. a restricted fixed-local-array memory summary composes constant-index cell
    transitions across the full loop;
13. VolCE validates fixed-cell entry-to-exit relations and proves the untouched
    frame over the declared fixed region;
14. compressed memory paths use `SyntheticMems` to restore skipped MEMS without
    adding source/SMT semantics;
15. `EPPATHER_LOOP_SCC_MEMORY_ACCELERATE=1` enables an opt-in fixed-cell DFS
    shortcut only after a conservative pre-execution structural certificate.

Still outside the certified shortcut:

- pointer dereference/alias summaries;
- symbolic array indices and ambiguous/cross-region aliases;
- VLA/unknown region extents;
- general multi-cycle/non-determinate oscillations;
- coupled multi-variable affine systems beyond independent scalar relations;
- nested memory summaries whose inner memory transition cannot be certified
  independently.

Therefore the accurate description is now **restricted certified LoopSCC
acceleration with conservative fallback**, not full LoopSCC.

The current head also contains a regression fix for a memory-observer regex
that previously threw on ordinary multiplication such as `i * 4`. The newest
full CI rerun is pending; do not treat the latest fixed-memory A/B matrix as
green until those runs complete.

## Latest semantic A/B gate

Workflow: `VolCE loop state summaries`, run 35883347664.

The 20 loop subjects were executed with summaries enabled and with the validation-only baseline.

| Metric | Result |
| --- | ---: |
| A/B cases passing exact count and weighted-MEMS agreement | 20/20 |
| SSA-applied cases | 16 |
| ground-validated cases | 3 |
| fallback cases | 1 |
| rejected cases | 0 |
| counting assertions, summary mode | 209 |
| counting assertions, baseline | 563 |
| model-count total, summary mode | 128,121 us |
| model-count total, baseline | 132,271 us |

The assertion reduction remains substantial, while the end-to-end timing difference is small enough that it should not be presented as a general LoopSCC speedup.

## Projection-factorization step

The previous bounded-memory enumerator left three real memory-projection subjects above the 60-second per-case limit:

- `ap06`: two-array dot product;
- `ap07`: six-cell reverse-pair reads;
- `ap15`: array-to-array copy.

The new factorization is applied **after semantics-preserving SSA elimination and solver reconstruction**. This is important: transient SSA/store structure can disappear from the exact reduced formula. Proving independence before that reduction was too conservative.

The dependency graph includes projected terms and hidden scalar state. Memory cells are separated only when the reduced formula does not connect them; symbolic addresses that may alias are joined after a Z3 satisfiability check. Stores, quantifiers, unsupported array-valued relations, ambiguous aliasing, or count overflow retain the exact fallback enumerator.

Unit regressions cover:

- correlated cells: 243 exact models, 5 components;
- symbolic alias guard: 891 exact models, factorization disabled;
- six disjoint cells: 729 exact models, 6 components;
- two canonical regions: 729 exact models, 6 components.

## 20 array/pointer/VLA subjects

Workflow: `ProbMEMS array and pointer projection`, run 35883347768.

Both modes completed on all subjects:

| Mode | Completed |
| --- | ---: |
| scalar | 20/20 |
| memory projection | 20/20 |

Previously, the final pre-factorization experiment completed memory projection on 17/20 subjects; `ap06`, `ap07`, and `ap15` timed out.

Representative final results:

| Subject | Projected models | Factor components | Model-count time | DFS time | Weighted MEMS |
| --- | ---: | ---: | ---: | ---: | ---: |
| ap04 | 59,049 | 10 | 12,100 us | 0.289 s | 5 |
| ap06 | 1,948,617 | 7 | 2,955,096 us | 3.214 s | 8 |
| ap07 | 531,441 | 12 | 15,839 us | 0.218 s | 6 |
| ap15 | 1,948,617 | 7 | 2,941,514 us | 3.193 s | 9 |

For comparison, the previous `ap04` memory run used about 14.6 seconds in model counting and the other three listed bottlenecks exceeded the 60-second case limit. The new result is an algorithmic scaling improvement for the finite projected model-count problem; it does not change the configured finite input domain.

The maxloop sensitivity runs at 2, 5, and 8 also completed for the selected array/pointer subjects, with the same completed counts for the previously problematic `ap06` and `ap15`.

## SPath / CSG, certified acceleration, nesting, and fixed memory

PR #98 now contains two separately gated runtime shortcuts.

**Scalar shortcut** (`EPPATHER_LOOP_SCC_ACCELERATE=1`):

- SPath/CSG analysis;
- exact trip count and phase guards;
- symbolic `T^k` plus residual phases;
- scalar SSA/VolCE entailment;
- inside-out scalar nesting;
- A/B equivalence for feasibility, MEMS, coverage, model count and wMEMS.

**Fixed-memory shortcut** (`EPPATHER_LOOP_SCC_MEMORY_ACCELERATE=1`):

- unique one-dimensional fixed local array only;
- constant in-bounds cell accesses only;
- exact full-loop fixed-cell affine transition;
- complete memory/effect and MEMS accounting;
- untouched-region frame proof;
- explicit MEMS compensation through `SyntheticMems`;
- pointer, symbolic-index, VLA, ambiguous-region and opaque cases rejected.

The array/pointer observer remains broader than the shortcut: it records MEMS
for pointer and symbolic-index subjects even when acceleration is forbidden.
That distinction is intentional and provides the substrate for the next alias
proof stage.

## Next LoopSCC gate

The next substantive gates are:

1. establish a **constant pointer-alias certificate** for narrowly resolvable
   forms such as `p = a` and `p = &a[k]`, while retaining fallback for pointer
   arithmetic and ambiguous aliases;
2. compose already-certified fixed-memory summaries inside-out for nested loops;
3. extend the state relation from independent scalar affine transforms to
   coupled multi-variable affine systems;
4. repeat the 20 loop and 20 array/pointer/VLA experiments under several
   requested `maxloop` values, reporting path equivalence, MEMS, count/wMEMS
   and runtime effects;
5. only after the current PR #98 CI matrix is green, merge the implementation
   into `main`.

PR #98 remains outside `main` until those current CI gates complete.


### Fixed-memory shortcut safety gate (2026-09-24)

Fixed-cell local-array summaries support exact structural T^k composition, explicit MEMS compensation, VolCE memory-relation entailment, and untouched-region frame validation. Runtime replacement remains opt-in via `EPPATHER_LOOP_SCC_MEMORY_ACCELERATE=1` and is admitted only when a **pre-execution structural certificate** is available: the SPath graph/trip count/phase cycle are proved complete, every participating memory access is precisely accounted, pointer dereferences are absent, every array token is a constant in-bounds access to a uniquely named one-dimensional fixed local array, and every memory write is covered by the fixed-cell closed form. VolCE relation/frame entailment and model-count/wMEMS A/B remain independent post-hoc oracles for validating this certificate rule. Pointer, symbolic-index, cross-cell, ambiguous-region, VLA/unknown-region, and opaque effects continue to fall back to unfolding.
