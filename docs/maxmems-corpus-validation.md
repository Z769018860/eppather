# MaxMEMS normalized-C corpus validation

## Why the reporting scheme changed

The corpus is a fixed inventory of normalized C inputs, but the raw inventory
size is **not** used as the denominator for MaxMEMS correctness. A raw source
can fail GNU C syntax preflight, fall outside the current Eppather frontend
subset, time out before a DP/DFS comparison exists, hit the configured DFS
path cap, or be unsuitable for automatic concrete replay. Dividing every
outcome by the raw inventory conflates dataset quality, frontend coverage,
resource limits, and semantic correctness.

The maintained report therefore uses **staged cohorts**. The inventory size is
kept only for reproducibility and corpus-drift detection.

## Primary staged denominators

The aggregate report now presents these stages in order:

1. **Raw normalized-source inventory.** Descriptive only; never used as the
   MaxMEMS success-rate denominator.
2. **GNU C syntax-valid programs.** Separates normalization quality from the
   analyzer.
3. **DP-completed programs.** A tagged MaxMEMS result was produced.
4. **Static-comparison programs.** Both DP and DFS2 completed and at least one
   function-level comparison was available.
5. **Exhaustive-within-bounds static cohort.** Static-comparison programs for
   which DFS2 did not hit `maxpaths`. This is the denominator for the main
   DP-vs-DFS MaxMEMS agreement rate.
6. **Path-capped static cohort.** Reported separately; equality here is useful
   diagnostic evidence but is not called exhaustive validation.
7. **Replay-attempted functions.** Automatic concrete replay could be invoked.
8. **Defined concrete executions.** Replay completed without source-level
   undefined behavior. This is the denominator for the concrete branch-trace
   match rate.

Accordingly, the two principal correctness ratios are:

```text
static agreement =
  exhaustive_static_equal_programs / exhaustive_static_programs

concrete replay agreement =
  replay_match_functions / replay_defined_functions
```

Timeouts, parse errors, unsupported replay signatures, undefined executions,
and path-limit hits are retained as separate coverage/residual counts.

## Reproduction

The maintained workflow is still stored at
`.github/workflows/maxmems-266-corpus-validation.yml` for repository-history
compatibility, but its displayed name is now **MaxMEMS staged-corpus
validation** and it uses the denominator-neutral manifest
`docs/maxmems-corpus-manifest.txt`.

Local example:

```bash
cmake -S . -B build_maxmems_corpus -DANALYSIS_BACKEND=epat++
cmake --build build_maxmems_corpus --target cnip -j2
python3 tools/maxmems_corpus_experiment.py \
  --cnip build_maxmems_corpus/cnip \
  --corpus testcase/output_complete2 \
  --manifest docs/maxmems-corpus-manifest.txt \
  --output-dir maxmems-corpus-results \
  --max-loop 3 --max-paths 1000 --timeout 120 --retry-timeout 900

python3 tools/aggregate_maxmems_corpus.py \
  --input maxmems-corpus-results \
  --output maxmems-corpus-aggregate \
  --manifest docs/maxmems-corpus-manifest.txt
```

## Interpretation

DP/DFS agreement is a cross-implementation consistency check because both modes
share parts of the frontend and path encoding. The maintained 20-subject
MaxMEMS witness experiment remains the stronger independent semantic oracle:
it checks the selected witness by concrete execution and dynamic source-level
memory-access markers.

Loop handling is likewise reported separately from MaxMEMS correctness.
Eppather currently contains restricted, certified LoopSCC-inspired
accelerations with conservative fallback; this is not presented as a complete
implementation of LoopSCC.

## Related loop-summarization reference

K. Zhu, H. Li, K. Yan, R. Wang, J. Guo, H. Yang, J. Lu, L. Yu, X. Jia,
C. Guo, H. Du, Q. Huang, Y. Xie, and J. Tang,
“LoopSCC: Summarizing Complex Multi-branch Nested Loops via Periodic
Oscillation Interval,” *IEEE/ACM International Conference on Software
Engineering (ICSE), Research Track*, 2026.

The LoopSCC citation is used to position Eppather's loop-bound/summary
engineering in related work. The MaxMEMS contribution remains the bounded
feasible maximum-memory-access search and its validation methodology.
