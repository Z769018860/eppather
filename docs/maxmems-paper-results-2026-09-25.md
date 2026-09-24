# MaxMEMS paper-ready experiment results — 2026-09-25

This note records **MaxMEMS/Eppather-only** results that have already been
validated by GitHub Actions artifacts. It intentionally excludes wMEMS claims.
The frozen 266-program final rerun is tracked separately below.

## 1. Independent controlled witness validation

Source artifact: `maxmems-prefix-witness-results`, Run `35955952039`.

- Controlled subjects: **20**
- Subjects passing all checks: **20 / 20**
- Feasible symbolic paths represented by the controlled suite: **43**
- Defined bounded concrete-oracle executions: **210**
- Undefined concrete-oracle executions: **0**
- Errors: **0**

For every subject, the following four quantities agree:

1. Eppather MaxMEMS DP result,
2. bounded feasible DFS oracle maximum,
3. dynamic memory-access count of the selected witness, and
4. maximum dynamic memory-access count over the bounded concrete input oracle.

The suite covers branches, nested branches, short-circuit conditions, fixed
arrays, array reads/writes, fixed loops, input-bounded loops, and nested loops.

**Paper-safe interpretation:** this is an independent bounded semantic
validation on a controlled C subset. It is not a claim of full ISO C
correctness.

## 2. Exact complete-path ranking on the historical mismatch set

Source artifact: `historical32-results`, Run `35943605541`.

- Historical mismatch subjects: **32**
- Subjects for which the uncapped bounded DFS comparison completed: **23**
- DP=DFS after exact complete-path ranking: **23 / 23 comparable cases**
- Remaining unavailable/timeout cases: **9**
- New static mismatches among comparable cases: **0**

This gives **71.9% (23/32)** resolved directly within the selected historical
mismatch set, while the remaining 9 cases are availability/timeout cases rather
than observed DP-vs-DFS disagreements.

**Paper-safe interpretation:** exact complete-path MEMS ranking eliminated every
previous DP/DFS disagreement that could be recomputed to completion in this
targeted regression set. Because the set was selected from prior failures, it
must not be presented as a random-sample accuracy percentage.

## 3. Timeout-rescue search optimization

Source artifact: `maxmems-prefix-ab-results`, Run `35955952039`.

Under the same **120 s per-program budget** on the 9 historical timeout
subjects:

- Baseline static passes: **3 / 9 (33.3%)**
- Optimized static passes: **7 / 9 (77.8%)**
- Absolute improvement: **+44.4 percentage points**
- Relative pass-count increase: **2.33x**
- Previously failing subjects rescued: **4 / 6 (66.7%)**
- Regressions: **0**

The four newly rescued programs are:

- `averages-median-2.c`
- `combinations-1.c`
- `number-names.c`
- `search-a-list.c`

The optimized configuration used bounded prefix feasibility, decision-only path
representation, lightweight leaf solving, a bounded prefix-query budget,
certified exact-loop guard pruning, and related search-cost reductions.

**Paper-safe interpretation:** the optimization improves robustness on a
deliberately hard timeout set without changing the 20-subject controlled
correctness result.

## 4. DFS max-only oracle for validation-side timeout

Source artifacts: `dfs-max-only-equivalence` and
`soundex-dfs-max-only-ab`, Run `35965035896`.

Controlled equivalence gate:

- Ordinary DFS maximum vs max-only DFS maximum: **20 / 20 equal**
- Objective mismatches: **0**

On `soundex.c`:

- Eppather DP: **MEMS = 22**, **15.0146 s**
- Ordinary DFS oracle: **timed out at 120 s**
- Max-only DFS oracle: **MEMS = 22**, **22.0736 s**
- DP = max-only DFS: **yes**

Thus the max-only oracle finished within 22.1 s where ordinary DFS exceeded the
120 s cutoff, i.e. more than **5.4x below the ordinary-DFS timeout budget** for
this case. This is an oracle-side optimization: it preserves the maximum-MEMS
objective but intentionally does not preserve the count of lower-value feasible
paths.

## 5. Historical 266-program baseline

The saved 2026-05-09 266-program result reported:

- DP=DFS programs: **145 / 266 (54.5%)**

This value is the fixed historical baseline for measuring the final rerun gain.

## 6. Frozen final 266-program rerun

Frozen branch:

`experiment/maxmems-266-final-20260925`

Frozen experiment commit:

`f8940bfe60468f14bcaa3f4ea5f35e18bf8fc344`

Workflow:

`MaxMEMS 266 final validation`

Run:

`36028035523`

Configuration:

- corpus denominator: **266 frozen programs**
- `maxloop=3`
- ordinary DFS `maxpaths=1000`
- primary timeout: **120 s**
- retry timeout: **300 s**
- 12 shards
- exact complete-path DP ranking
- core-only MaxMEMS reporting
- validated timeout-search optimizations
- ordinary DFS first; max-only DFS is used only as a timeout fallback
- independent 20-case witness gate runs in the same workflow

### Interim snapshot while the 266 rerun is still running

Artifacts currently available from shards 2, 4, 6, 7, 8, 9, and 11 cover
**154 / 266** programs. This is an interim progress snapshot, not the final
corpus result.

- Programs collected so far: **154**
- GNU C syntax-valid / invalid: **149 / 5**
- Programs reaching DP/DFS comparison: **140**
- Programs with DP=DFS: **140 / 140 analyzed (100%)**
- Functions with DP=DFS: **188 / 188 (100%)**
- True static mismatch programs: **0**
- DFS path-limit hits: **0 programs / 0 functions**
- DP timeouts after retry: **5**
- DFS timeouts after fallback: **0**
- Retry attempted / rescued: **8 / 3**
- DFS max-only fallback programs: **1** (`soundex.c`)
- Concrete replay matches: **76 functions**
- Concrete replay mismatches: **3 functions**; all three remain static
  **DP=DFS** and are therefore tracked as replay-oracle residuals rather than
  MaxMEMS static disagreements.

Among the current DP-timeout rows, at least two are dominated by repeated
`unsupported type: int[5]` diagnostics from epat++ (`amb.c` and
`walk-a-directory-recursively-2.c`), so they are solver/subset-coverage
residuals rather than observed DP-vs-DFS disagreements. The main search-timeout
cases currently include `arithmetic-geometric-mean-1.c`,
`non-continuous-subsequences-2.c`, and `ludic-numbers.c`; targeted BnB
rescues are running for AGM and ludic.

The interrupted original shard 10 job is an infrastructure failure: the GitHub
runner received a shutdown signal after completing 9/22 programs. A dedicated
shard-10 retry is running with the same experimental parameters.

**Paper-safe interim interpretation:** across the first 140 programs for which
both MaxMEMS DP and the bounded DFS/max-only oracle produced comparable
results, every static maximum agrees. This number must be replaced by the
complete 266-program aggregate before submission.

### Interim residual classification

The current non-comparable residuals should not be merged into the MaxMEMS
correctness count without qualification:

- `call-an-object-method.c`: recursion plus function-pointer invocation; the
  process exits with `-11` after already printing MaxMEMS diagnostics.
- `cut-a-rectangle-1.c`: recursive helper plus two-dimensional arrays and
  wider integer types.
- `first-class-functions-2.c`: two-dimensional arrays and a normalized
  first-class-function encoding outside the supported scalar/fixed-array
  subset.
- `sutherland-hodgman-polygon-clipping.c`: heavy two-dimensional-array
  interface and indexing.
- `inverted-index-1.c`: recursion, callback/function pointer, and
  two-dimensional arrays.

These are front-end / supported-subset coverage residuals. They remain in the
frozen **266-program denominator**, but they should be reported separately from
`true_static_mismatch_programs`. The only confirmed search timeout in the
current 88-program snapshot is `ludic-numbers.c`; a separate BnB rescue run is
tracking it.

When the run completes, report at least:

1. programs collected / 266,
2. syntax-valid vs invalid normalized programs,
3. programs reaching DP/DFS comparison,
4. DP=DFS rate over all 266 and over analyzed programs,
5. uncapped/static-equal programs and functions,
6. path-limit-hit programs/functions,
7. true static mismatches,
8. DP timeout and DFS timeout counts after retry/fallback,
9. retry attempted/rescued counts,
10. max-only fallback count,
11. concrete replay match/undefined/unsupported/mismatch counts,
12. gain over the historical **145/266** baseline.

Do **not** call a `maxpaths=1000` DFS comparison exhaustive. Only the uncapped
historical-32 regression and explicitly uncapped/max-only runs should use
"exhaustive bounded" wording.
