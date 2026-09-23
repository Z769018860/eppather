# LoopSCC / Eppather integration status (2026-09-23)

## Current scope

Eppather currently contains a **LoopSCC-compatible hybrid loop-summary pipeline**, not a complete implementation of the LoopSCC paper.

Implemented stages:

1. canonical affine `for` loops receive exact trip-count summaries and may automatically lift an insufficient `--maxloop` bound;
2. structurally simple constant-bound affine `while` loops recover initializer/update metadata with stale-initializer rejection;
3. completed paths produce affine state-transition candidates of the form
   `x_out = x_initial + step * iterations`;
4. VolCE accepts a transition only after an SMT entailment check;
5. epat++ preserves source-to-SSA provenance for selected scalar induction variables;
6. entailed SSA definitions are substituted away before model counting;
7. array/pointer/VLA inputs use bounded canonical memory projections;
8. the reduced counting formula is now decomposed into **proved-independent projection components** and exact component counts are multiplied;
9. an opt-in structural LoopSCC adapter enumerates one-iteration acyclic SPaths, records guards/write sets/simple affine updates, builds a conservative SPath transition graph, runs Tarjan SCC decomposition, and retains the contracted CSG structure for the next summarization stage.

Still not implemented from full LoopSCC:

- periodic oscillation interval discovery over SPath SCCs;
- determinate-cycle / multi-cycle closed forms;
- general multi-variable and data-dependent loop summarization;
- source-level alias summaries that can replace canonical memory abstraction.

Therefore the current integration should be described as **LoopSCC-compatible affine/state-summary integration with conservative fallback**, not full LoopSCC.

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

## SPath / CSG structural stage

PR #98 adds the first control-flow structure layer. With
`EPPATHER_LOOP_SCC_ANALYZE=1`, Eppather enumerates acyclic one-iteration
SPaths, retains branch guards, scalar/memory write sets and simple affine
updates, builds a conservative transition graph, computes Tarjan SCCs, and
retains both SCC membership and contracted CSG edges. This stage is
observational only: it does not replace unfolding or assert a new VolCE
constraint. Nested loops are marked incomplete until inside-out composition is
implemented.

See `docs/loopscc-spath-csg-adapter-2026-09-23.md` for the exact supported
forms, metrics and fallbacks.

## Next LoopSCC gate

The next step is now **restricted periodic/oscillation detection over the
retained SPath SCCs**:

1. identify SCC-local variables whose guards and updates are fully represented
   by the current interval/affine model;
2. detect a small proved periodic cycle (starting with reciprocal two-SPath
   oscillation) and derive its oscillation interval;
3. express the candidate as a guarded closed-form transition;
4. send that transition through the existing SMT entailment gate before it can
   influence VolCE or bypass unfolding;
5. keep general multi-variable, memory-writing, ambiguous-guard and incomplete
   SCCs on the existing bounded path;
6. validate exact solution-count and weighted-MEMS equality against the
   validation-only baseline before measuring performance.

Array/pointer state remains behind alias-aware write-set checks; no SPath/CSG
summary may bypass memory unfolding until the corresponding memory transition
is proved.
