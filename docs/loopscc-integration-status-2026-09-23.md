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

## SPath / CSG, certified acceleration, and nesting stage

PR #98 now contains the complete restricted scalar path from SPath analysis to
an opt-in DFS shortcut:

- acyclic one-iteration SPath enumeration;
- conservative transition graph, Tarjan SCCs and contracted CSG;
- determinate-cycle and phase-guard proofs;
- exact uniform trip-count recovery for canonical `while` and `for` loops;
- symbolic `T^k` composition plus residual phases;
- symbolic entry-phase alternatives;
- SSA provenance and VolCE affine-relation entailment;
- deterministic SSA-chain compression after entailment;
- validation-only compressed path generation;
- A/B checks for feasibility, MEMS, solution-space count, weighted-MEMS and
  coverage;
- opt-in certified DFS shortcut under
  `EPPATHER_LOOP_SCC_ACCELERATE=1`.

The last completed green scalar-acceleration baseline is workflow
`VolCE loop state summaries #189` on head `8b355c7...`. Its unit and
end-to-end gates include period-2 acceleration with requested `--maxloop 1`,
residual-phase composition and symbolic entry phases.

The newest branch commits additionally implement inside-out scalar nesting:
safe nested loops are summarized before the outer SPath, C99 nested-for local
induction variables do not escape their scope, and the same certified shortcut
can be used for both `while` and `for` loops. Real nested-while and nested-for
A/B fixtures are now part of the validation script. These newest commits are
still waiting on the current CI queue.

Array/pointer work has entered a certificate stage. SPaths now record array
subscripts, pointer dereferences, memory writes, observer completeness and the
corresponding MEMS count. Existing array/pointer subjects must expose these
metrics while still producing zero exact acceleration plans. Memory-dependent
shortcuts remain disabled until a canonical alias-aware memory-state transition
is proved.

See `docs/loopscc-spath-csg-adapter-2026-09-23.md` for the detailed safety
contract.

## Next LoopSCC gate

The next substantive gate is **alias-aware memory transition acceleration**:

1. represent fixed/canonical memory-region transforms in the LoopSCC plan;
2. connect source memory regions to the canonical projections already used by
   VolCE;
3. prove that projected regions do not alias other written/read regions;
4. validate summarized memory state against the unfolded SMT formula;
5. compensate skipped array/pointer MEMS exactly and A/B it against epat++
   MemVisitor;
6. only then admit memory-dependent loops to the DFS shortcut;
7. retain the existing fallback for symbolic aliases, opaque calls,
   unsupported memory writes and incomplete projections.

After that, the main remaining LoopSCC gap is coupled multi-variable affine
state rather than independent scalar relations.

The PR #98 work is not part of `main` until its current CI gates complete and
the PR is merged.

### Fixed-memory shortcut safety gate (2026-09-24)

Fixed-cell local-array summaries now support exact structural T^k composition, explicit MEMS compensation, VolCE memory-relation entailment, and untouched-region frame validation. These memory summaries remain **validation-only** in DFS: requesting `EPPATHER_LOOP_SCC_MEMORY_ACCELERATE=1` is conservatively blocked until the relation and frame certificates can be established independently before loop replacement. Pointer, symbolic-index, cross-cell, ambiguous-region, VLA/unknown-region, and opaque effects continue to fall back to unfolding.
