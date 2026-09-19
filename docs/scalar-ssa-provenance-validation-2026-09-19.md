# Scalar SSA provenance for LoopSCC state summaries

Date: 2026-09-19  
PR: https://github.com/Z769018860/eppather/pull/93

## Implementation

Eppather selects exact affine induction variables from the concrete path before invoking epat++. The selection is scoped to one solver invocation. epat++ materializes direct scalar initialization and assignments as named, constrained SSA states (`source@scope#ssaN`). VolCE recognizes the source-name prefix, proves that the candidate equality is entailed by the path formula, then applies it in summary mode. The validation-only baseline performs the same checks without asserting the equality.

Derived SSA states remain in the solver but are excluded from input projection. Projecting them independently would incorrectly change the solution-space count. Array, pointer, and indirect writes continue through the existing memory model. On paths with multiple loops and indexed memory access, SSA materialization falls back to the compact encoding to bound the symbolic memory cost.

## Results and interpretation

| Experiment | Result |
|---|---:|
| 20 loop-containing cases, semantic A/B | 20/20 PASS |
| Cases with SSA summary applied | 16/20 |
| Cases with ground validation | 3/20 |
| Fallback cases | 1/20 |
| Rejected cases | 0/20 |
| Summary count time | 49,627 us |
| Validation-only baseline count time | 48,521 us |
| Baseline / summary count-time ratio | 0.9777x |
| End-to-end aggregate speedup | 0.9953x |
| Ten-case weighted average regression | 10/10 PASS; all CSV counts and averages match main |
| Multi-function and exact oracle regression | PASS |

The 20-case loop results come from https://github.com/Z769018860/eppather/actions/runs/35439857939 and the weighted regression from https://github.com/Z769018860/eppather/actions/runs/35439897604. The earlier fully passing array/pointer/VLA run on the branch is https://github.com/Z769018860/eppather/actions/runs/35411382893; a final run for this revision is tracked in the PR.

The source-to-SSA link now works for many scalar induction variables, but the validated equalities are already entailed by the fully unrolled formula. Formula assertion and input-projection counts stay equal across A/B configurations. This implementation demonstrates a sound binding; it does **not** demonstrate faster model counting. To obtain a speedup, the next stage must replace or avoid expansion of a validated transition while preserving the original path and memory semantics. The 20-case suite alone cannot establish a speedup.

## Limits and next step

The provenance filter uses source variable names; shadowed variables with the same name in different scopes, indirect writes through aliases, and variable-length memory cells still require explicit declaration and memory-region identity. The multi-loop indexed-memory fallback deliberately retains ground validation. Future work should carry a stable declaration ID through CFG, epat++, and VolCE, record the exact loop exit state, and test summary substitution against an independent execution oracle on pointer/array paths.
