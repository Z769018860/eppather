# ProbMEMS adaptive maxloop optimization report (2026-09-10)

Workflow: [run 34514739706](https://github.com/Z769018860/eppather/actions/runs/34514739706)

## Final outcome

| Measure | Before while fix | After while fix, naive retries | Optimized guessing |
|---|---:|---:|---:|
| Complete analyses | 35/40 | 39/40 | 39/40 |
| Completed memory-access cases with nonzero EMEMS | 29/30 | 34/34 | 34/34 |
| Dataset analysis time (sum of per-case elapsed seconds) | 6 s | 2,559 s | 25 s |
| Unexpected zero-memory results | 1 | 0 | 0 |
| Remaining failures | 5 | 1 | 1 |

The optimized policy preserves all recovered results while reducing measured analysis time by 99.0% relative to naive adaptive retries.

## Root causes and fixes

1. Pointer dereferences were not counted. `MemVisitor` now counts `UnaryOperator::Uop::Deref`.
2. Every while-loop silently used `min(maxloop,3)`. While loops now honor the configured safety cap.
3. Empty feasible-path matrices were indexed at row zero. Empty matrices now return safely.
4. Blindly trying larger bounds first caused nested-loop state explosion. Bounds now start from a tighter static guess and retry nearest smaller before nearest larger.

## Bound-selection results

| Case | Structure | Guessed/selected bound | EMEMS | MaxMEMS | Time |
|---|---|---:|---:|---:|---:|
| gt19 | nested 2x2 array loop | 3 | 4 | 4 | 0 s |
| gt22 | fixed 5 array loop | 5 | 5 | 5 | 0 s |
| gt24 | nested 2x3 array loop | 4 | 6 | 6 | 10 s |
| gt27 | fixed 4 two-array loop | 4 | 8 | 8 | 0 s |
| gt31 | fixed 5 pointer loop | 5 | 5 | 5 | 0 s |
| gt38 | fixed 4 pointer copy | 4 | 9 | 9 | 0 s |
| gt40 | nested 2x3 pointer loop | 4 | 6 | 6 | 10 s |

No successful case required an adaptive retry in the optimized run. The only retried case was gt20, which failed at 1,2,3,4,5,12 due to the independent multi-function crash (#77).

## Recommended maxloop policy

- Use exact affine prediction for canonical for-loops.
- For while-loops with visible constant bounds, use the smallest safe structural bound.
- For nested loops, assign per-loop bounds rather than multiplying them into one global value.
- On failure, try candidates in the order U, U-1, U+1, U-2, U+2, up to a safety ceiling.
- Stop at the first complete non-empty result.
- Treat timeout, empty solution space, crash, and true zero cost as separate outcomes.
- Do not increase maxloop after metrics and path count have stabilized.

Raw data: [probmems-adaptive-maxloop-optimized-2026-09-10.csv](probmems-adaptive-maxloop-optimized-2026-09-10.csv).
