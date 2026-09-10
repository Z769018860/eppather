# ProbMEMS while-maxloop fix validation (2026-09-10)

Workflow: [run 34465346860](https://github.com/Z769018860/eppather/actions/runs/34465346860)

## Results

- 40/40 cases compile.
- 39/40 cases complete Eppather analysis.
- 34/34 completed memory-access cases have nonzero weighted sum and EMEMS.
- The only remaining failure is the independent multi-function crash in gt20 (#77).
- gt22 (fixed five), gt27 (fixed four), gt31 (pointer fixed five), and gt38 (pointer copy four) all recover immediately at bounds 5, 4, 5, and 4.
- gt34 pointer swap reports weighted sum=6, EMEMS=6, MaxMEMS=6 after unary dereference counting was fixed.

## Confirmed maxloop root cause

The loop traversal helper silently returned min(maxloop,3) for every while-loop. Values above three were never honored. After removing this clamp, all four previously failing fixed 4/5-iteration loops pass.

## Adaptive behavior and performance issue

Three nested-loop cases recovered at a lower bound:

| Case | Requested | Selected | Attempts | Elapsed |
|---|---:|---:|---|---:|
| gt19 | 5 | 4 | 5,6,7,8,9,4 | 610 s |
| gt24 | 8 | 4 | 8,9,10,11,12,7,6,5,4 | 970 s |
| gt40 | 8 | 4 | 8,9,10,11,12,7,6,5,4 | 972 s |

This validates bidirectional recovery but shows that increasing first is inefficient for nested loops. PR #82 tightens static guesses, tries the nearest smaller bound before the larger bound, and reduces micro-case attempt timeout from 120 to 30 seconds.

Raw data: [probmems-while-maxloop-fix-2026-09-10.csv](probmems-while-maxloop-fix-2026-09-10.csv).
