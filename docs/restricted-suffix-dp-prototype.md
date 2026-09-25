# Restricted suffix-DP prototype and limits

The [successful reviewer audit run 36177948529](https://github.com/Z769018860/eppather/actions/runs/36177948529) archives the generated C subjects, source instrumentation, analyzer logs and [three-row CSV](data/restricted_dp_prototype.csv). In its four-guard case, existing cnip DFS2 and prefix-keyed search both report MEMS=8; neither demonstrates memo reuse. The eight- and twelve-guard rows have not been executed by cnip, and their cnip columns remain blank.\n\nThis prototype is intentionally separate from the released `cnip -g` search. The latter still keys its memo by the full path prefix and recorded **0 hits / 1,701 queries** on the prior four-case audit. Do not cite this prototype as a measured speedup of `cnip -g`.

## Admissible C family and proof

`tools/restricted_dp_prototype.py` generates programs with `n` independent scalar guards `b_i`; both branches read only fixed cells of an initialized two-element array and add the values into a scalar accumulator. No guard reads the accumulator or array; no branch changes the array or subsequent input guards. Every combination of boolean guards is feasible and defined. The concrete instrumented copy increments a counter on each array read.

At layer `i`, the true branch costs two array reads and the false branch costs one; neither can alter future feasibility or future read counts. Thus for the **restricted family**, the suffix optimum satisfies `V(i)=max(2+V(i+1),1+V(i+1))` and `V(n)=0`. By backward induction, `V(0)=2n`; the witness takes all true branches. The initialized array's setup writes are outside the instrumented function's measured read subtotal. The prototype's read subtotal is distinct from any other memory-access counting convention that includes initialization writes.

The script validates this result against exhaustive enumeration of both the path choices and concrete C executions. An optional `--cnip` checks that DFS2 and existing prefix-keyed search agree on the generated 4-guard C subject. That check does not imply the prototype and cnip count identical operation boundaries; it only establishes that cnip's two modes agree on the same source.

| Independent branches | Suffix states, restricted DP | Prefix states, exhaustive DFS | Instrumented max reads |
| ---: | ---: | ---: | ---: |
| 4 | 5 | 31 | 8 |
| 8 | 9 | 511 | 16 |
| 12 | 13 | 8,191 | 24 |

These are **state counts**, not measured running times. The favorable complexity comes from a proven independence assumption, not from dropping `pathPrefix` in the general solver. General C programs can have correlated guards, conditionally feasible suffixes, aliasing, or branch-dependent memory states; this recurrence is invalid for them.

## Admission gate for future integration

A general Eppather optimization must prove (1) equal reachable live state for future memory observations, (2) equivalent projected constraints for future feasibility, (3) a separately accounted prefix cost, and (4) witness reconstruction. Reject a candidate merge if any proof is inconclusive; retain full-prefix search. Compare supported merged cases and unsupported fallback cases with the same-source DFS2 and concrete instrumentation before making a tool-level DP performance claim. No numerical KLEE, WISE, or IPET comparison is implied.
