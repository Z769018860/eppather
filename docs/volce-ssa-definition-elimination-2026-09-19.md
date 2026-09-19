# VolCE SSA definition elimination: validation (2026-09-19)

## Change

After a LoopSCC-compatible scalar induction summary is proved entailed by the complete SMT formula, VolCE substitutes deterministic, unprojected SSA definitions in that source variable's scope and removes their defining equalities before enumeration. Projection terms are substituted as well. The validation-only baseline retains its original constraints. Both modes rebuild and warm their solvers before enumeration. The original formula assertion count is still reported separately from the counting-stage assertion count.

## Reproduction

Run the `VolCE loop state summaries` GitHub Actions workflow for PR #94; it compiles `volce-summary-tests` and `cnip`, runs `tools/validate_volce_loop_summaries.sh` and `tools/validate_volce_loop_failure_modes.sh`, then runs `tools/evaluate_loopscc_integration.sh`. The artifact `loopscc-effect-results/` contains the per-case CSV. Reference run: https://github.com/Z769018860/eppather/actions/runs/35441863818 (commit `dc3d5bf16b18af4a33789a919077260730482f22`).

## Results (one CI run)

| Measure | Summary enabled | Validation-only baseline |
| --- | ---: | ---: |
| Cases passing count and weighted MEMS agreement | 20/20 | 20/20 |
| SSA-applied / ground-validated / fallback cases | 16 / 3 / 1 | same input set |
| Counting-stage assertions, summed across cases | 209 | 563 |
| Model-enumeration duration, summed (μs) | 126,053 | 129,304 |
| Whole-case wall duration, summed (ms) | 11,196 | 11,220 |

The counting-stage formula has 354 fewer assertions in this run (62.9%). The enumeration duration ratio is 1.0258× baseline/summary, and whole-case wall ratio is 1.0021×. These are single-run observations, not a statistically established speedup. Some single-solution paths simplify entirely to true, so they report zero counting assertions. Multi-branch and early-exit cases retain constraints (e.g. case 18: 181 versus 215); fallback and ground-only summaries do not have a corresponding SSA definition to eliminate.

The six `volce-summary-tests` checks passed, including equal projected model counts for a synthetic SSA chain and fewer counting-stage assertions. The loop summary and diagnosed failure-mode scripts passed.

## Next measurement

Repeat the paired comparison on multiple runners and report per-case median and dispersion. Add larger arrays, symbolic pointer indices and nonconstant loops where the projected model count is greater than one; profile summary validation, substitution, warmup and enumeration separately. Retain the strict count and weighted MEMS equality gates.
