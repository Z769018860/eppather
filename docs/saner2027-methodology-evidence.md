# SANER 2027 methodology evidence: MaxMEMS search, loop summaries, and summary fidelity

Date: 2026-09-25

This note records the repository evidence used to address three likely methodology-review concerns in the MaxMEMS paper. It deliberately separates measured facts from claims that the current implementation does **not** support.

## 1. Path-sensitive memoization is measured, not assumed to accelerate

The MaxMEMS recurrence currently keys the memo table by

```text
(CFG node, loop-unroll counters, complete rendered path prefix)
```

The complete prefix is required by the present feasibility/MEMS semantics. It also means that two visits to the same CFG node reached by different branch histories do not share a memo entry. Therefore a low memo hit rate is expected on tree-like bounded explorations and the implementation must not claim a generic dynamic-programming speedup over exhaustive DFS.

The implementation now emits, per analyzed function:

- DP recursive calls;
- memo enabled/disabled status;
- memo lookups, hits, misses, hit rate, and stored states;
- terminal full-path evaluations and infeasible leaves;
- prefix-feasibility cache/solver/prune counts;
- the DP elapsed time.

Set `EPPATHER_DISABLE_DP_MEMO=1` to run the identical recurrence without memo lookup/store. This is the direct cache ablation.

`tools/maxmems_methodology_experiment.py` runs the 20 controlled witness subjects plus five correlation-focused subjects in four modes:

1. normal exact path-sensitive search;
2. the same search with memoization disabled;
3. exhaustive feasible DFS2;
4. `EPPATHER_MAXMEMS_FEASIBILITY_BLIND=1`, a feasibility-blind flow-only structural maximum.

Mode 4 is an experiment-only **IPET-style structural reference**: it keeps the same bounded CFG and MEMS objective but removes SMT feasibility from path selection. It is not a valid Eppather MaxMEMS result and should not be described as a full implementation of an external IPET tool.

The CI artifact `maxmems-methodology-results` contains `methodology.csv`, `methodology.json`, and `methodology.md`.

## 2. Loop-summary ablation already exists and should be reported as such

The maintained LoopSCC-compatible experiment executes 20 loop subjects with loop-state summaries enabled and disabled. The latest recorded semantic A/B gate reported:

| Metric | Summary mode | Baseline / result |
|---|---:|---:|
| Cases with exact count and weighted-MEMS agreement | 20/20 | 20/20 |
| SSA-applied cases | 16 | - |
| Ground-validated cases | 3 | - |
| Fallback cases | 1 | - |
| Counting assertions | 209 | 563 |
| Model-count time | 128,121 us | 132,271 us |

This result supports two claims and no more:

- the certified summary transformations preserved the measured bounded semantics on all 20 subjects;
- the reduced formulas used substantially fewer counting assertions.

The end-to-end/model-count timing difference is too small to support a general speedup claim. The paper should say so explicitly.

Reproduction:

```bash
bash tools/evaluate_loopscc_integration.sh
```

The current integration is restricted certified LoopSCC acceleration with conservative fallback, not a complete implementation of the LoopSCC paper.

## 3. Baseline policy

For the primary bounded MaxMEMS result, exhaustive feasible DFS2 is the direct semantic baseline because it uses the same parser, bounded CFG, feasibility semantics, and MEMS objective but enumerates feasible paths instead of selecting the maximum through the recurrence.

The flow-only structural mode added above supplies a second, feasibility-oblivious reference closely matching the question an IPET-style flow formulation asks after bounded unfolding. It isolates the value of path feasibility without pretending that KLEE, WISE, or a WCET IPET implementation optimizes the same metric.

KLEE and WISE should remain related-work systems unless a reproducible adapter is added that maps their outputs to the exact same bounded MEMS objective. Reporting wall-clock numbers from unmatched objectives/harnesses would be less informative than the paired DFS and flow-only comparisons.

## 4. RQ3 should be a fidelity-boundary result, not a positive accuracy result

The current 66-entry small-library evidence has a strong transformation dependency:

- direct/original-body slices with a positive estimate: **0/30**;
- simplified slices with a positive estimate: **2/11**;
- compatibility/model slices with a positive estimate: **18/25**.

Accordingly, the paper should rename/reframe RQ3 around **transformation sensitivity and fidelity boundaries**. The defensible conclusion is that the present summary recognizer can provide nonzero estimates after compatibility modeling, but the study does not establish faithful MaxMEMS estimation for unmodified source bodies.

Recommended reporting:

> RQ3 is a boundary study. All 30 analyzed slices that retained a direct source function body produced a zero estimate, whereas 20 transformed/modelled slices produced positive estimates. This prevents us from treating the positive values as source-level accuracy evidence; instead, it quantifies how strongly the current summary pipeline depends on compatibility transformations.

The large-project model values can remain as illustrative compatibility outputs, but they should not be presented as validated source-level MaxMEMS estimates.

## Paper implications

The SANER paper should use the following terminology consistently:

- **path-sensitive memoized search** for the current full-prefix recurrence;
- **exhaustive feasible DFS2** for the semantic enumeration baseline;
- **flow-only / IPET-style structural reference** for the feasibility-blind experiment;
- **restricted certified LoopSCC acceleration** for the loop-summary mechanism;
- **transformation-sensitivity / fidelity-boundary study** for RQ3.

Avoid statements that memoization necessarily yields a performance advantage, that LoopSCC currently gives a general runtime speedup, or that transformed RQ3 values validate unmodified source functions.
