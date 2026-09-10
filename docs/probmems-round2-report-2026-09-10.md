# ProbMEMS round-2 dataset report (pre-dereference fix)

Date: 2026-09-10  
Workflow: [run 34462238835](https://github.com/Z769018860/eppather/actions/runs/34462238835)  
Configuration: 40 cases, input domain [-1,1], maxpaths=100, maxloop forced to 8.

## Aggregate results

| Measure | Result |
|---|---:|
| C syntax compilation | 40/40 |
| Complete Eppather analyses | 35/40 |
| Cases with memory-access syntax | 35 |
| Complete memory-access analyses | 30/35 |
| Nonzero EMEMS among complete memory-access cases | 29/30 (96.7%) |
| Path-limit hits | 0 |
| Legitimate scalar-only zero cases | 5 |
| Unexpected memory-access zero cases | 1 |
| Analysis failures | 5 |

## Category results

| Category | Cases | Complete | Nonzero among complete | Mean EMEMS among complete |
|---|---:|---:|---:|---:|
| array | 15 | 13 | 13 | 2.707692 |
| pointer | 14 | 13 | 12 | 1.783962 |
| mixed | 5 | 4 | 4 | 3.416667 |
| scalar | 5 | 5 | 0 | 0 |
| call | 1 | 0 | 0 | N/A |

## Zero-value diagnosis

The five scalar cases are classified as `ZERO_NO_MEMORY_ACCESS`; they have nonempty solution spaces but no array subscript or pointer dereference and are valid zeros.

The only unexpected zero is `gt34_pointer_swap.c`. It contains unary pointer dereferences but reports solution count 1, weighted sum 0, EMEMS 0, and MaxMEMS 0. Source inspection found the root cause: `MemVisitor` counted only `ArraySubscript` and did not count `UnaryOperator::Uop::Deref`. The fix was merged in [PR #79](https://github.com/Z769018860/eppather/pull/79).

## Failure diagnosis

- `gt20_function_call.c`: reproduces the previously reported multi-function core dump (#77). Partial metrics are now correctly censored to N/A.
- `gt22_array_fixed_five_loop.c`, `gt27_two_array_dot.c`, `gt31_pointer_fixed_five_loop.c`, and `gt38_array_pointer_copy.c`: no feasible path was emitted under the globally forced maxloop=8, followed by an empty-matrix core dump.
- The four fixed-loop failures are not weighted-zero results. They are analysis failures and must not enter EMEMS aggregates.
- Their manifests have been changed to semantic bounds 5, 4, 5, and 4 respectively. The follow-up workflow uses per-case bounds.

## Reproducibility notes

Raw data is stored in [probmems-round2-dataset-pre-deref-fix-2026-09-10.csv](probmems-round2-dataset-pre-deref-fix-2026-09-10.csv). A post-fix rerun is required before using these figures as final paper results.
