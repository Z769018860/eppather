# LoopSCC-compatible integration effect evaluation

Date: 2026-09-16

## Scope and terminology

The current implementation is a **LoopSCC-compatible hybrid integration
layer**, not a complete reimplementation of LoopSCC. It provides:

- closed-form trip-count prediction for canonical affine `for` loops;
- exact induction-variable transition candidates;
- implication checking before a transition is passed to VolCE;
- automatic lifting of a too-small `maxloop` for proved affine loops;
- conservative fallback and explicit diagnostics for unsupported loops.

It does not yet construct LoopSCC SPaths/CSGs, detect oscillatory intervals or
determinate cycles, or summarize general multi-variable/multi-branch SCCs.

## Experiment

GitHub Actions run 35100441381 executes 20 loop subjects twice, with VolCE loop
summaries enabled and disabled. The domain is `[-8,8]`; each pair must have the
same nonzero solution-space count and the same weighted-average MEMS. The
experiment records SSA application, ground validation, rejection, fallback,
and end-to-end elapsed time.

| Metric | Result |
|---|---:|
| Completed A/B pairs | 20/20 |
| Equal solution-space counts | 20/20 |
| Equal weighted MEMS | 20/20 |
| SSA-applied cases | 0/20 |
| Ground-validated cases | 18/20 |
| Fallback cases | 2/20 |
| Rejected cases | 0/20 |
| Summary-enabled total time | 9533 ms |
| Baseline total time | 9630 ms |
| Aggregate ratio | 1.0102x |

The 1.0102x ratio is too small to distinguish from runner/process noise and
must not be reported as a performance improvement.

## Representative results

| Subject | Behavior | Count (summary/base) | wMEMS (summary/base) | Disposition |
|---|---|---:|---:|---|
| 01 | affine ascending | 1 / 1 | 8 / 8 | ground validated |
| 12 | nested affine loops | 1 / 1 | 8 / 8 | 2 ground validations |
| 13 | data-dependent while | 12 / 12 | 1 / 1 | fallback |
| 15 | multi-branch affine loop | 4 / 4 | 12 / 12 | ground validated |
| 16 | array, two loops | 1 / 1 | 8 / 8 | validation + diagnostic |
| 18 | early break | 17 / 17 | 11.7647 / 11.7647 | validation + 7 diagnostics |
| 20 | for plus while | 1 / 1 | 10 / 10 | validation + fallback diagnostic |

An earlier run used `[-1,1]` and produced zero models for subject 15 because
its feasible paths require `n=5` or `n=6`. The strict evaluator now rejects
zero counts and `N/A` weighted MEMS; the representative domain fixes the test.
This was a domain-coverage problem, not a loop-summary failure.

## Assessment

The integration has a confirmed **correctness and feasibility benefit**:
proved affine trip counts prevent low-`maxloop` truncation from eliminating
complete paths, and all tested summary constraints preserve VolCE counts and
wMEMS. It also makes unsupported cases observable instead of silently treating
bounded unfolding as exact.

It has **no demonstrated model-counting performance benefit yet**. epat++
constant-folds the local induction variable in every summarized test, leaving
no SSA variable for VolCE to constrain. Ground identities validate the source
transition but cannot reduce the formula or projection dimension.

## Next implementation priorities

1. Recover normalized initializer, condition, update, and modified-variable
   sets for `while` loops.
2. Build an SPath/CSG adapter and summarize multi-branch cycles, rather than
   only predicting a scalar trip count.
3. Preserve a source-to-SSA mapping through epat++ so accepted summaries can
   replace/unify loop-state constraints before constant folding.
4. Extend summaries to arrays and pointers with alias-aware write sets, then
   rerun the canonical memory-projection experiments.
5. Evaluate formula size, solver time, model-counting time, summary coverage,
   and probability-mass completeness separately; end-to-end time alone hides
   where a summary helps or adds overhead.

