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
