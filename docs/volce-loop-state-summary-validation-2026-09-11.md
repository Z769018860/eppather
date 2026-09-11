# VolCE loop state-summary validation report (2026-09-11)

## Implementation

For every completed symbolic path, Eppather derives an affine induction-state
summary only when:

1. the loop header has an exact closed-form trip count;
2. the observed path iteration count equals that trip count;
3. the loop was not truncated and did not take an early exit.

The summary is passed to VolCE. A source/SSA equality is asserted only after
`path_constraints AND NOT(summary)` is proved UNSAT. If Epat++ has completely
constant-folded the local induction variable, VolCE asserts the equivalent
ground 32-bit bit-vector closed form without adding a counted variable.

Use `EPPATHER_DISABLE_VOLCE_LOOP_SUMMARIES=1` to run the unchanged-formula
baseline.

## GitHub Actions result

Workflow: [VolCE loop state summaries #19](https://github.com/Z769018860/eppather/actions/runs/34588414514)

| Case | Summary | Models with summary | Baseline models | Applied | Rejected | wMEMS summary | wMEMS baseline |
|---:|---|---:|---:|---:|---:|---:|---:|
| 01 | ascending step 1 | 1 | 1 | 1 | 0 | 8 | 8 |
| 04 | ascending step 2 | 1 | 1 | 1 | 0 | 10 | 10 |
| 08 | reversed condition | 1 | 1 | 1 | 0 | 10 | 10 |
| 11 | negative initial value | 1 | 1 | 1 | 0 | 12 | 12 |
| 19 | descending step 2 | 1 | 1 | 1 | 0 | 10 | 10 |

Result: 5/5 summary integrations passed. Model counts and weighted-average
MEMS are identical to the no-summary baseline in every case.

## Current boundary

This iteration summarizes the induction-variable state transition. It does not
yet replace the loop body with a LoopSCC multi-variable summary, so its current
benefit is formula validation, explicit summary transport, and a sound
integration point for later LoopSCC output. Arrays and pointer access costs
continue to be accumulated by the existing path/MEMS analysis.
