# Legacy MaxMEMS corpus-report filename

This file is retained only so old links remain valid. The earlier report used
the raw normalized-source inventory as a fixed success-rate denominator. That
reporting convention has been retired because it conflated source
normalization, frontend support, timeouts, path caps, static agreement, and
concrete replay eligibility.

Use the current staged-cohort report instead:

- `docs/maxmems-corpus-validation.md`
- `docs/maxmems-corpus-manifest.txt`
- `tools/aggregate_maxmems_corpus.py`

The raw inventory size is now descriptive only. The primary static correctness
rate uses the no-path-cap DP/DFS comparison cohort; the primary concrete rate
uses defined replay executions.
