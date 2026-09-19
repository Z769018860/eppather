# VolCE Loop-Summary Phase Profiling

Date: 2026-09-19  
Branch: `feature/volce-summary-profiling`  
Evaluation set: 20 loop-containing C programs used by `tools/evaluate_loopscc_integration.sh`

## Objective

Measure whether the current LoopSCC-derived state summaries reduce VolCE model-counting cost, while separating solver initialization, summary validation, and model counting. The experiment also checks that enabling summaries preserves weighted-counting semantics.

## Instrumentation

The VolCE API and Eppather result printer now report:

- formula assertion count;
- SMT declaration count;
- projection-term count;
- solver warm-up time;
- summary-check time;
- model-counting time.

The evaluation script records these values for both configurations and writes their totals to `aggregate.csv`.

## Fair A/B methodology

The first instrumented run compared summary mode against a cold baseline. It reported 40,982 us for summary model counting and 105,643 us for the baseline, apparently a 2.58x speedup. This result was invalid: summary entailment checks had already warmed the Z3 solver.

The corrected experiment therefore uses the same work in both configurations:

1. construct the same SMT formula and projection set;
2. perform one symmetric solver warm-up check;
3. discover and validate the same summary candidates;
4. in summary mode only, assert validated equalities;
5. execute the same model-counting procedure.

Thus, the baseline is validation-only rather than cold. This isolates the effect of adding summary constraints from solver warm-up and candidate-validation overhead.

## Results

| Metric | Summary enabled | Validation-only baseline |
|---|---:|---:|
| Programs | 20 | 20 |
| Formula assertions, total | 483 | 483 |
| Projection terms, total | 15 | 15 |
| Solver warm-up, us | 125,176 | 124,077 |
| Summary validation, us | 3,909 | same validation work |
| Model counting, us | 48,831 | 48,234 |
| Baseline / summary count-time ratio | 0.988x | 1.000x |
| Semantic equivalence | 20/20 | reference |
| Ground summaries validated | 19 | 19 candidates checked |
| SSA summaries applied | 0 | 0 |
| Fallbacks | 1 | 1 |

Relevant successful CI runs:

- VolCE loop-summary evaluation: https://github.com/Z769018860/eppather/actions/runs/35409550615
- Array/pointer/VLA regression: https://github.com/Z769018860/eppather/actions/runs/35409550804

## Interpretation

The current ground summaries preserve semantics but do not accelerate model counting. The measured count-time ratio is 0.988x, meaning summary mode is slightly slower within run-to-run noise. The earlier 2.58x observation was entirely a solver-state/warm-up artifact and must not be reported as a performance improvement.

This outcome is expected from the structural counters: both configurations retain 483 assertions and 15 projection terms. Nineteen summaries are validated, but all are ground facts and zero are attached to the SSA variables that dominate the counting formula. Consequently, the constraints do not shrink the formula or reduce the counted state space.

## Next experiment

The next implementation should establish explicit source-to-SSA provenance before constant folding destroys the relation between source loop variables and SMT symbols.

Recommended sequence:

1. emit a stable source-variable identifier and loop identifier while building the Eppather path/state representation;
2. propagate those identifiers through SSA renaming and into the SMT declaration metadata;
3. translate LoopSCC affine postconditions onto the corresponding SSA exit variables;
4. reject summaries when aliasing, pointer writes, or unsupported VLA bounds make the mapping ambiguous;
5. repeat the same 20-program semantic A/B test and phase profiling;
6. expand to array, pointer, and VLA loops only after nonzero SSA application is observed.

Success criteria for the next stage are: nonzero SSA summaries applied, unchanged weighted counts on every supported program, reduced assertion/term complexity or counted search space, and performance reported with the fair validation-only baseline defined above.
