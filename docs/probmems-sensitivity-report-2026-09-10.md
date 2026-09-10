# ProbMEMS sensitivity experiment report (2026-09-10)

## Configuration

- Subjects: cJSON, inih, clibs-list, Lua, sds, tinyexpr
- Input domains: `d1=[-1,1]`, `d3=[-3,3]`
- Loop bounds: `maxloop={1,2,3,5}`
- Path cap: 40
- Timeout: 180 seconds per configuration
- Total configurations: 48

Raw data: [probmems-sensitivity-2026-09-10.csv](probmems-sensitivity-2026-09-10.csv). GitHub Actions run: [#34459636011](https://github.com/Z769018860/eppather/actions/runs/34459636011).

## Execution summary

| Outcome | Configurations |
|---|---:|
| PASS | 44 |
| TIMEOUT | 4 |
| Compile failure | 0 |
| Reported zero weighted sum | 0 |
| Path-cap hit | 4 |

All four timeouts are cJSON under `[-3,3]`. All four path-cap hits are cJSON under `[-1,1]`. A timeout has no valid denominator and must be recorded as missing/censored, never as zero.

## Sensitivity by subject

| Subject | Domain | EMEMS range over maxloop | MaxMEMS range | Interpretation |
|---|---|---:|---:|---|
| cJSON | [-1,1] | 9.66667–9.66667 | 15–17 | EMEMS stable; maximum changes; path-capped |
| cJSON | [-3,3] | N/A | N/A | all four configurations timed out |
| inih | [-1,1] | 1.33333–1.33333 | 2–2 | insensitive to maxloop |
| inih | [-3,3] | 1.71429–1.71429 | 2–2 | domain changes EMEMS |
| clibs-list | [-1,1] | 0.666667–0.666667 | 1–1 | insensitive to maxloop |
| clibs-list | [-3,3] | 0.857143–0.857143 | 1–1 | domain changes EMEMS |
| Lua | [-1,1] | 16.6154–16.6154 | 21–35 | EMEMS stable, maximum loop-sensitive |
| Lua | [-3,3] | 18.1718–20.1765 | 21–35 | domain and maxloop matter |
| sds | [-1,1] | 1.33333–1.33333 | 2–2 | insensitive to maxloop |
| sds | [-3,3] | 1.71429–1.71429 | 2–2 | domain changes EMEMS |
| tinyexpr | [-1,1] | 18.0000–20.9333 | 20–22 | maxloop matters until saturation at 3 |
| tinyexpr | [-3,3] | 19.1429–21.7838 | 20–22 | maxloop matters until saturation at 3 |

Lua and tinyexpr values at maxloop 3 and 5 are identical, suggesting saturation for these bounded subjects. This supports maxloop=3 as a cost-effective pilot default, while sensitivity checks remain necessary.

## Why previous values were zero

The results do **not** support the hypothesis that most previous zeros were caused by maxloop being too small:

1. No successful configuration in this matrix has a zero weighted sum.
2. In the independent 20-case pilot dataset, all five scalar-only cases have `weighted sum = EMEMS = MaxMEMS = 0`, while array, pointer, and mixed cases are nonzero.
3. Scalar-only zeros are expected under the current memory-access-only event definition; they are semantic zero-cost cases.
4. Timeout, empty solution space, unsupported construct, parse failure, and true zero-cost execution must remain separate classes.

## Threats and next experiments

- cJSON is censored by the 40-path cap on the small domain and timeout on the larger domain.
- These subjects include normalized summaries and function slices, not yet full original-project translation units.
- Add repetitions and report median/IQR runtime.
- Extend domains gradually and add a separate maxpaths sensitivity experiment.
- Fix the multi-function continuation crash in `gt20_function_call.c`, then rerun.
- Validate pointer-alias semantics against manual ground truth before accuracy claims.
