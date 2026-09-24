# Independent MaxMEMS witness validation

## Goal

This experiment addresses a correctness gap that DP-vs-DFS agreement alone cannot close: two static search implementations can share the same CFG or MEMS-accounting defect. The experiment therefore validates the concrete witness for the reported bounded MaxMEMS result.

The scope is deliberately limited to **MaxMEMS and Eppather**. It does not use path probabilities, wMEMS/ProbMEMS, or LoopSCC-specific claims.

## Validation chain

For each of 20 controlled C subjects:

1. run `cnip -g` and record the selected bounded MaxMEMS path and reported MEMS;
2. run `cnip -q` to obtain feasible path models and identify a model that realizes the DP-selected branch sequence;
3. execute that model on an instrumented copy of the original C function and compare ordered runtime branch outcomes with the DP path;
4. count source-level memory-access events dynamically under Eppather's current operational MEMS semantics for these subjects (array subscripts and pointer dereferences);
5. exhaustively replay the finite scalar-input domain `[-2,3]` and compute an independent bounded dynamic maximum;
6. require equality among the DP MEMS, feasible-DFS maximum, dynamic witness MEMS, and bounded dynamic-oracle maximum.

A subject passes only when all checks succeed.

## Controlled instrumentation

The source analyzed by Eppather is semantically unchanged. Counted accesses in this controlled suite are annotated with a C comment:

```c
/*EPP_MEM*/(a[i])
/*EPP_MEM*/(*p)
```

For concrete replay only, `tools/maxmems_witness_experiment.py` rewrites the annotated lvalue into an incrementing lvalue wrapper. Because the marker is a comment in the analysis input, it does not change Eppather's AST, CFG, path constraints, or MEMS value.

The controlled subjects use scalar `int` parameters and local fixed-size arrays/pointers, so the dynamic oracle can exhaustively enumerate inputs without guessing pointer ownership or external memory contents.

## Subject coverage

The 20 subjects cover branch-dependent array reads, nested branches, writes, fixed `for` and `while` loops, branch-containing loops, pointer reads/writes, pointer arithmetic/subscripts, mixed array-pointer accesses, two-array accesses, nested loops, input-bounded loops, memory accesses in conditions, sequential decisions, nested `else` branches, and tied maximum paths.

## Reproduction

```bash
cmake -S . -B build_maxmems_witness -DANALYSIS_BACKEND=epat++
cmake --build build_maxmems_witness --target cnip -j2

python3 tools/maxmems_witness_experiment.py \
  --cnip build_maxmems_witness/cnip \
  --output-dir maxmems-witness-results
```

The output directory contains the generated controlled C subjects, one JSON report per subject, and aggregate `summary.csv`, `summary.json`, and `summary.md`.

## Paper use

This experiment is intended for the MaxMEMS/Eppather SANER 2027 paper as independent witness-validity evidence. It complements rather than replaces the large DP-vs-DFS consistency experiment: the large experiment provides breadth/scalability evidence, while this controlled experiment provides a concrete semantic oracle for the selected worst-case witness and MEMS value.


## Final CI result

Final workflow run: `35936958085` (commit `d2ada75dd2172877d460bff46d023d709fada731`).

| Metric | Result |
|---|---:|
| Controlled subjects | 20 |
| Subjects passing all checks | **20/20** |
| Feasible static paths represented across the subjects | 42 |
| Defined bounded concrete-oracle executions | 210 |
| Undefined concrete-oracle executions | 0 |
| DP-vs-DFS MaxMEMS disagreements | 0 |
| Static-vs-dynamic witness MEMS disagreements | 0 |
| DP-vs-bounded-dynamic-oracle disagreements | 0 |
| Ordered witness branch-trace mismatches | 0 |

The final run therefore establishes, for this controlled suite, equality of the
four independently observed quantities used by the experiment:

```text
DP MaxMEMS = feasible-DFS maximum = concrete witness MEMS
           = bounded exhaustive dynamic maximum
```

The complete machine-readable table is stored in
`docs/maxmems-witness-validation-results-2026-09-24.csv`.  The CI artifact
`maxmems-witness-results` additionally contains every generated subject and
one JSON record per case.

### Defects exposed by the experiment

The experiment was intentionally run before treating its result as evidence.
The first executions exposed two real MaxMEMS-DP loop-state defects, which were
fixed and then re-evaluated with the same subjects and oracle:

1. **for-loop update ordering.** The DP engine appended the `for` update only
   after the recursively explored body returned. Because the CFG back-edge
   revisits the loop header before that return, the next feasibility query saw
   a stale induction variable and could report `MEMS=-1` for feasible fixed
   `for` loops. The fix executes/models `LoopUpdate` on re-entry to the loop
   header, matching DFS2's established ordering.
2. **nested-loop dynamic re-entry.** A completed inner lexical loop retained
   its unroll count when the enclosing loop began the next iteration. The
   second dynamic invocation of the inner loop was therefore treated as
   already exhausted. The fix resets counters of lexically deeper loops at an
   enclosing loop-header re-entry, again mirroring DFS2.

After both fixes, fixed `for`, loop-with-branch, array loop write, and nested
`for` subjects all pass the independent dynamic oracle. This history is
important for the paper: the experiment is not merely another internal
DP-vs-DFS cross-check; its external concrete oracle detected defects that the
existing static comparison did not isolate as clearly.

## Recommended SANER 2027 reporting

This result should be presented as a **controlled semantic validation**, not as
a claim that every C construct is fully supported.  A precise paper statement
is:

> On 20 controlled C subjects covering branches, short-circuit conditions,
> array reads/writes, fixed and input-bounded loops, and nested loops, the
> MaxMEMS path selected by Eppather agreed with feasible exhaustive DFS and
> with an independent bounded concrete-execution oracle in all 20 cases. Across
> 210 defined concrete oracle executions, the reported MaxMEMS value, the
> dynamically counted memory accesses of the selected witness, and the maximum
> dynamic value were identical.

The larger 266-program DP-vs-DFS experiment should remain the breadth/scalability
evaluation; this 20-subject experiment supplies independent semantic evidence.
