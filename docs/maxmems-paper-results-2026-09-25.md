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
