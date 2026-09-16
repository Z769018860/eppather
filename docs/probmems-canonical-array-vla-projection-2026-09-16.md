# Canonical array, pointer, and bounded-VLA projection

Date: 2026-09-16

## Goal

This experiment replaces path-local memory terms with a canonical source-level
projection. Every feasible path is counted over the same named array/pointer
regions and the same number of cells. This makes the per-path solution counts
comparable when computing weighted-average MEMS.

## VLA policy

- Fixed-size array parameters retain their declared extent.
- `a[n]`, `a[]`, and pointer parameters use a bounded projection (five cells by
  default, configurable with `EPPATHER_VLA_MAX_ELEMENTS`, hard-capped at 64).
- When a function has multiple variable-length regions, they share a six-cell
  budget. For example, two pointer parameters receive three cells each. This
  prevents the model space from growing exponentially with every unknown
  region while keeping all paths on the same projection.
- Local VLAs are normalized to the configured finite bound so the current
  epat++ frontend can analyze them. They are not treated as external input
  memory regions.
- Set `EPPATHER_DISABLE_BOUNDED_VLA` to disable the declaration rewrite.

This is a bounded analysis approximation, not an exact representation of an
unbounded C VLA.

## Validation

GitHub Actions run 35098821517 compiled the project, passed all five VolCE
state-summary tests, and completed both scalar and memory modes for all 20
array/pointer/VLA subjects. Run 35098821620 passed the loop-state-summary
integration suite.

| Subject | Construct | Scalar count | Memory count | Projected cells | Weighted MEMS (scalar / memory) |
|---|---|---:|---:|---:|---:|
| ap06 | two fixed arrays | 1 | 6561 | 8 | 8 / 8 |
| ap12 | two pointers, swap | 1 | 729 | 6 | 6 / 6 |
| ap13 | pointer + loop branch | 6 | 1215 | 5 | 1.33333 / 1.2 |
| ap17 | `a[n]` parameter | 3 | 729 | 5 | 0.333333 / 0.333333 |
| ap18 | `a[]` parameter | 3 | 729 | 5 | 0.333333 / 0.333333 |
| ap19 | local bounded VLA | 3 | 3 | 0 | 0.666667 / 0.666667 |
| ap20 | pointer + runtime extent | 5 | 1215 | 5 | 0.6 / 0.6 |

All 40 main experiment rows report `PASS`, `CONSISTENT_ARITY`, and `NONZERO`.
The six loop-heavy sensitivity subjects also pass unchanged at maxloop 2, 5,
and 8. Therefore the prior `ap12` timeout was caused by projection cardinality
(two five-cell unknown regions plus addresses), rather than an insufficient
maxloop bound.

## Interpretation and limitations

The `ap13` result demonstrates why memory-aware weighting matters: feasible
paths have different memory-conditioned solution counts, changing weighted
MEMS from 1.33333 to 1.2.

The canonical projection gives every path the same source-region identity and
arity. However, when the backend scalarizes a fixed array, projected raw-array
cells can remain unconstrained and multiply every path count by the same
factor. Thus weighted probabilities remain comparable, but the absolute total
may exceed the number of distinct concrete source inputs. A future refinement
should connect canonical source cells directly to scalarized SSA values and
exclude pointer addresses from the input valuation when alias identity is not
part of the experiment.

