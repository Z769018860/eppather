# ProbMEMS 20-case pilot results (2026-09-10)

Workflow run: https://github.com/Z769018860/eppather/actions/runs/34460037622

## Configuration

- Input domain: [-1,1]
- maxpaths: 100
- Per-case maxloop: 1 or 5, as specified by the manifest
- Per-case timeout: 120 seconds
- Subjects: 20 new C functions in testcase/probmems_ground_truth

## Outcome

- C syntax compilation: 20/20 PASS
- Complete Eppather process exit: 19/20 PASS
- Path-limit hits: 0/20
- Scalar zero-cost cases: 5/5
- Array cases with non-zero EMEMS: 7/7
- Pointer cases with non-zero EMEMS: 6/6
- Mixed array/pointer cases with non-zero EMEMS: 1/1
- Multi-function call case: 0/1 complete

The five scalar cases report weighted sum and EMEMS equal to zero while MaxMEMS is also zero. Under the current MEMS definition, which counts memory accesses rather than scalar arithmetic, these are expected zero-cost cases and are not evidence of an insufficient loop bound.

All array, pointer, and mixed cases produced non-zero weighted sums. Their observed EMEMS values range from 0.333333 to 5.14706. No case reached maxpaths=100.

## Multi-function failure

gt20_function_call.c produced valid metrics for the helper function and then terminated with a core dump:

```text
[VOLCE WEIGHTED AVERAGE MEMS]: 1
[DFS MAX MEMS]: 1
timeout: the monitored command dumped core
```

The partial metrics must not be used as the result of the whole source file. This case exposes a multi-function DFS2/function-summary stability defect and should remain in the dataset as a negative capability case.

## Interpretation limits

These results establish compilation and analysis feasibility only. They do not yet establish probability accuracy because exhaustive dynamic ground truth has not been generated. Pointer alias semantics in gt16 must be validated separately even though the analyzer exits successfully. A successful process exit is not proof that the counted input space matches C pointer semantics.

Raw results: [probmems-pilot-dataset-2026-09-10.csv](probmems-pilot-dataset-2026-09-10.csv)
