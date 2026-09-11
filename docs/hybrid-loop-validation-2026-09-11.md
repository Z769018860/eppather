# Hybrid loop validation report (2026-09-11)

## Configuration

- GitHub Actions: Ubuntu 24.04
- E: default GitHub-hosted runner
- compiler checks: GCC C11 and G++ C++17
- E: Eppather built with `ANALYSIS_BACKEND=epat++`
- analysis: `cnip -q --maxpaths 80`
- per-case timeout: 60 seconds
- workflow run: [Hybrid loop validation #15](https://github.com/Z769018860/eppather/actions/runs/34584226781)

## Aggregate result

| Check | Passed | Total |
|---|---:|---:|
| Trip-count summary oracle | 20 | 20 |
| C syntax compilation | 20 | 20 |
| Eppather DFS2 process completion | 20 | 20 |
| Valid DFS maximum MEMS | 20 | 20 |

A valid result requires a non-negative integer `[DFS MAX MEMS]`; a zero exit
status with the old `-1` sentinel is classified as a failure.

## Per-program results

| ID | Category | Compile | DFS2 | DFS Max MEMS |
|---:|---|---|---|---:|
| 01 | ascending `<` | PASS | PASS | 8 |
| 02 | ascending `<=` | PASS | PASS | 10 |
| 03 | descending | PASS | PASS | 10 |
| 04 | step 2 | PASS | PASS | 10 |
| 05 | inclusive step 3 / `+=` | PASS | PASS | 8 |
| 06 | assignment step | PASS | PASS | 6 |
| 07 | increment update | PASS | PASS | 10 |
| 08 | reversed condition | PASS | PASS | 10 |
| 09 | reversed descending condition | PASS | PASS | 10 |
| 10 | zero-trip loop | PASS | PASS | 0 |
| 11 | negative initial value | PASS | PASS | 12 |
| 12 | nested loops | PASS | PASS | 8 |
| 13 | input-dependent `while` | PASS | PASS | 6 |
| 14 | constant-condition `while` | PASS | PASS | 10 |
| 15 | multi-branch loop | PASS | PASS | 12 |
| 16 | array / two loops | PASS | PASS | 8 |
| 17 | pointer walk | PASS | PASS | 12 |
| 18 | early `break` | PASS | PASS | 16 |
| 19 | descending step 2 | PASS | PASS | 10 |
| 20 | mixed `for` and `while` | PASS | PASS | 10 |

## Findings

The initial full run exposed two false-success cases with
`[DFS MAX MEMS]: -1`: a standard increment expression and a nested
two-dimensional-array case. The validation script now rejects missing,
negative, or non-numeric MEMS values. Standard loop increments and compound
updates are normalized to assignment form only at the epat path-language
boundary; the source CFG is unchanged. The nested case uses a flattened array,
which is within Eppather's currently supported memory model.

The implemented summary is an exact affine **trip-count summary**, not a full
LoopSCC state-transition summary. Unsupported/data-dependent loops remain
explicitly classified as adaptive fallback and therefore remain
`maxloop`-dependent. This distinction prevents bounded results from being
reported as exact.
