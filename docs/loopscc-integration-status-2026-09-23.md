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
9. an opt-in LoopSCC adapter enumerates one-iteration acyclic SPaths, records guards/write sets/simple affine updates, builds a conservative SPath transition graph, runs Tarjan SCC decomposition, and retains the contracted CSG;
10. determinate closed SPath cycles are recognized conservatively and their machine-readable period transforms `x' = a*x+b` are composed;
11. concrete paths are mapped to SPath phase sequences and path-specific affine relations;
12. periodic state variables receive scalar SSA provenance before epat++ solving;
13. VolCE accepts a periodic affine relation only after an SMT entailment check over the complete path formula;
14. an entailed periodic relation can feed the existing SSA definition-elimination pass, while the validation-only baseline performs the same checks without assertion/elimination.

Still not implemented from full LoopSCC:

- symbolic period-count derivation that can safely skip repeated loop bodies;
- general multi-cycle / non-determinate oscillation closed forms;
- inside-out nested SCC composition;
- general coupled multi-variable and data-dependent loop summarization;
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

## SPath / CSG and guarded relation stage

PR #98 extends the control-flow layer beyond structural observation. With
`EPPATHER_LOOP_SCC_ANALYZE=1`, Eppather enumerates acyclic one-iteration
SPaths, builds SCC/CSG structure, recognizes restricted determinate cycles,
composes exact scalar period transforms including sign-flip scale `-1`, and
maps a concrete unfolded path to its phase sequence.

For a complete matched cycle, Eppather transports a machine-readable
`x_exit = a*x_entry+b` candidate to VolCE. epat++ materializes the relevant
local scalar states as `#ssaN`. VolCE then checks the candidate by asserting
its negation; only UNSAT relations are accepted. Applied relations are kept
separate from the older constant-final-state summaries and may participate in
deterministic SSA definition elimination. SAT/UNKNOWN, missing provenance,
ambiguous SSA scopes, unsupported writes, memory writes, nested loops, and
incomplete graphs all fall back conservatively.

This changes the status of PR #98 from “structural-only” to **guarded affine
relation integration**. It still does not bypass loop unfolding: the current
phase relation is derived after observing the concrete bounded path.

See `docs/loopscc-spath-csg-adapter-2026-09-23.md` for supported transforms,
validation gates and fallbacks.

## Next LoopSCC gate

The next step is **safe symbolic period acceleration**, not another structural
adapter:

1. derive the number of complete cycle periods symbolically from loop guards
   and cycle-entry state;
2. prove the period-count/exit relation and residual phase, not just the state
   transform for an already-unfolded path;
3. replace repeated period bodies only after the closed form and exit semantics
   are both SMT-validated;
4. preserve bounded unfolding for ambiguous, non-determinate, nested,
   multi-variable-unsupported, and memory-writing SCCs;
5. implement inside-out SCC composition before accelerating nested loops;
6. evaluate maxloop sensitivity directly: a successful acceleration should
   preserve counts/wMEMS while reducing dependence on the configured unroll
   bound.

Array/pointer state remains behind alias-aware write-set checks; no SPath/CSG
summary may bypass memory unfolding until the corresponding memory transition
is proved.

The new PR #98 relation/SSA-compression work is not yet part of `main` until
its CI gates pass and the PR is merged.
