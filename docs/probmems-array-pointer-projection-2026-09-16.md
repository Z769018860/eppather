# ProbMEMS array/pointer projection experiment (2026-09-16)

Workflow: [ProbMEMS array and pointer projection #4](https://github.com/Z769018860/eppather/actions/runs/35094788468)

## Goal

The established VolCE integration enumerates scalar bit-vector declarations.
Array-backed memory is existentially projected away. This experiment evaluates
an opt-in accessed-memory projection for programs containing arrays and
pointers, while retaining the scalar-only metric as the reproducible baseline.

Enable the experimental mode with:

```text
EPPATHER_VOLCE_PROJECT_MEMORY=1
```

Only `select` expressions with symbolic addresses are projected. Fixed-address
selects are epat++ local/SSA slots and must not be bounded by the source input
domain. Including them caused valid loop counters greater than one to make the
formula unsatisfiable; the final implementation excludes them.

## Dataset and completion

The dataset contains 16 subjects: seven array programs, six pointer programs,
and three mixed array/pointer programs. It covers fixed loops, symbolic indices,
reads, writes, pointer offsets, aliasing, copying, and branch-dependent loops.

| Measure | Result |
|---|---:|
| C syntax compilation | 16/16 |
| Scalar-projection analyses | 16/16 |
| Memory-projection analyses | 16/16 |
| Nonzero MaxMEMS | 16/16 |
| Unexpected zero-MEMS results | 0 |
| Comparable memory-projection aggregates | 15/16 |
| Explicitly censored inconsistent aggregate | 1/16 |

## Cases affected by memory projection

| Case | Feature | Scalar count | Memory-projected count | Memory terms | Weighted MEMS |
|---|---|---:|---:|---:|---:|
| ap08 | pointer dereference branch | 12 | 15 | 1 | 2 |
| ap10 | five-element pointer loop | 3 | 36 | 5 | 5 |
| ap11 | pointer offset read | 9 | 15 | 1 | 2 |
| ap13 | pointer loop with branches | 6 | N/A | 0–5 | censored |

The solution count changes demonstrate that scalar-only counting omits input
memory valuations for pointer reads. Weighted MEMS is unchanged for ap08,
ap10, and ap11 because all feasible paths in those examples have equal MEMS.

For ap13, different paths read different numbers of memory cells. Summing those
counts would mix spaces of different dimensions. Eppather therefore emits
`INCONSISTENT_ACROSS_PATHS` and reports aggregate count, probability, and
weighted MEMS as N/A. This is not a zero result or an analysis failure.

## Array representation result

The seven fixed-array cases expose no symbolic-address memory terms in the SMT
formula. epat++ scalarizes their accessed elements into bit-vector declarations,
so scalar and memory-projection results are identical. This means the current
prototype improves pointer-backed memory counting but does not yet reconstruct
the complete declared array input domain.

## maxloop sensitivity

Six loop-heavy subjects were repeated at `maxloop` 2, 5, and 8 in both modes.
Before the final fix, five constant-bound while loops produced no complete path
at U=2. Their CFG nodes lacked the initializer/update metadata required by the
exact for-loop predictor.

The new while policy recognizes only canonical variable-versus-integer
conditions and raises their exploration budget conservatively. Data-dependent
while loops still honor the requested bound. After the fix:

| Case | U=2 | U=5 | U=8 | Stability |
|---|---:|---:|---:|---|
| ap01 array loop | MEMS 3 | MEMS 3 | MEMS 3 | stable |
| ap04 array loop | MEMS 5 | MEMS 5 | MEMS 5 | stable |
| ap06 two-array loop | MEMS 8 | MEMS 8 | MEMS 8 | stable |
| ap10 pointer loop | wMEMS 5 | wMEMS 5 | wMEMS 5 | stable |
| ap13 pointer branch loop | censored | censored | censored | consistently diagnosed |
| ap15 pointer copy | MEMS 9 | MEMS 9 | MEMS 9 | stable |

Thus the earlier U=2 failures were caused by insufficient while-loop expansion,
not by zero-cost memory paths or a zero VolCE weight.

## Valid claims and limitations

The current results support these claims:

1. Pointer dereferences contribute nonzero MEMS after the dereference visitor
   fix; all 16 subjects now have nonzero MaxMEMS.
2. Scalar-only VolCE counts can underrepresent pointer input memory.
3. Constant-bound while-loop guessing recovers complete paths at a small user
   bound without changing results at U=5 or U=8.
4. Path counts with unequal memory-projection arity must not be normalized into
   probabilities.

The experimental projection is not yet a complete source-input probability
model. Equal arity does not prove that two paths project the same memory-cell
identities, and scalarized arrays require source-to-SMT input mapping. Before
using memory-projected wMEMS as the primary paper metric, Eppather must build a
single canonical input projection shared by every path, then count each path
over that identical projection.

## Next experiments

1. Record canonical source input cells (array parameter + index, pointer base +
   offset) during AST/CFG construction and pass the same projection to every
   path.
2. Compare accessed-cell projection with full declared arrays at sizes 2, 4,
   and 8 over domains of size 3 and 5.
3. Add alias pairs where two pointer expressions address the same cell and
   verify that the model counter does not double-count them.
4. Run cJSON/tinyexpr functions with bounded input buffers after canonical
   projection is available.
5. Measure enumeration time, model count, and peak memory as the number of
   projected cells increases.
