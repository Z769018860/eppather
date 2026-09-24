# MaxMEMS 266 corpus — shard10 completion (2026-09-25)

This note records the completed 22-program shard10 rerun from the frozen 266-program corpus.

## Runs

- Main 22-way independent-program matrix: Actions run `36037037292`, head `53acfcdded30aa013f549ebb00b66b211e99f2ca`.
- Hailstone runner-safe diagnostic: Actions run `36038544162`, head `07d9e5f400fc29034d19bcde323a91368d835010`.
- Earlier serial retry `36029406038` was interrupted by runner shutdown after 9/22 programs and is superseded by the independent-program matrix.

## Result

All **22/22 shard10 programs now have a recorded outcome**.

- Passing programs: **17/22**
  - full replay: **11**
  - partial replay: **1**
  - static-only: **5**
- Analyzed functions: **18**
- DP=DFS static-equal functions: **18/18**
- True DP/DFS static mismatches: **0**
- Replay mismatches: **0**
- Valid C programs: **21/22**
- Invalid C programs: **1/22** (`n-queens-problem-3.c`)
- Standard-budget DP timeouts with completed records: **4**
- Additional hailstone diagnostic timeout: **1**, with both standard-budget attempts interrupted by runner shutdown before the 120 s primary timeout completed.

The 21-artifact aggregate from the main matrix reported 17 analyzed/static-equal programs and 18/18 static-equal functions. The missing 22nd row was `hailstone-sequence-2.c`; the separate 90 s runner-safe diagnostic recorded it as `dp_failed / timeout`.

## Residual programs

| Program | Classification | Detail |
|---|---|---|
| `combinations-1.c` | valid-C DP timeout | 120 s primary + 300 s retry exhausted |
| `hailstone-sequence-2.c` | valid-C unresolved/timeout diagnostic | 90 s diagnostic timed out; two standard-budget attempts were terminated by runner shutdown around 103 s |
| `n-queens-problem-3.c` | corpus/front-end invalid | source fails C syntax checks and epat++ reports unsupported `int[33]` |
| `unix-ls.c` | valid-C DP timeout | 120 s primary + 300 s retry exhausted |
| `window-management.c` | valid-C DP timeout / unsupported-array evidence | 120 s primary + 300 s retry exhausted; epat++ also reports unsupported `int[100]` |

## Interpretation

Among every shard10 program for which both DP and bounded DFS completed, static MaxMEMS agrees exactly: **18/18 functions, 0 mismatches**. The remaining failures are timeout/front-end support cases rather than observed MaxMEMS ranking disagreements.

The hailstone result must not be reported as a standard 120+300 s timeout: the standard run was attempted twice, but the GitHub runner itself was shut down at roughly 103 s on both attempts. The 90 s diagnostic exists only to ensure shard10 has a durable 22nd program row.
