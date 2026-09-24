# MaxMEMS validation on the 266-program normalized Rosetta corpus

## Scope

This experiment extends the independent MaxMEMS witness-validation work from the
20 controlled subjects to every C file in `testcase/output_complete2/`.
That directory contains exactly 266 normalized Rosetta Code programs and is the
corpus reported by the SANER 2027 MaxMEMS/Eppather paper.

The experiment remains strictly about MaxMEMS and Eppather. It does not use
wMEMS/ProbMEMS and does not make LoopSCC-specific claims.

## Validation levels

The corpus experiment deliberately distinguishes two evidence levels.

1. **Static maximum validation (all analyzable programs).** Eppather runs
   `-g` and exhaustive bounded `-q` with the same loop/path bounds. For every
   tagged function, the reported DP MaxMEMS must equal the largest feasible DFS2
   MEMS value. The DP-selected branch sequence must also have a feasible DFS2
   model.
2. **Concrete witness replay (eligible functions).** When a normalized function
   has a scalar-`int` signature that the replay harness can invoke safely, the
   DFS model realizing the DP-selected MaxMEMS witness is executed on the
   original normalized C source. Ordered concrete branch outcomes must equal the
   DP witness. Pointer/array parameters, original `main` entry points, undefined
   executions, compile failures, and unsupported signatures are reported
   explicitly rather than silently removed.

The earlier 20-subject controlled experiment remains the stronger independent
MEMS-count oracle because its source-level access markers permit dynamic MEMS
counting and finite-domain exhaustive execution. The 266-program extension is
intended to add breadth: static DP/DFS equality for the whole reported corpus and
concrete witness feasibility wherever automatic replay is sound.

## Reproduction

The GitHub Actions workflow is
`.github/workflows/maxmems-266-corpus-validation.yml`. It shards the 266 files
across six workers, then aggregates per-program and per-function CSV/JSON data.

Local example:

```bash
cmake -S . -B build_maxmems266 -DANALYSIS_BACKEND=epat++
cmake --build build_maxmems266 --target cnip -j2
python3 tools/maxmems_corpus_experiment.py \
  --cnip build_maxmems266/cnip \
  --corpus testcase/output_complete2 \
  --output-dir maxmems-266-results \
  --max-loop 3 --max-paths 1000 --timeout 120
```

The `-g` output now emits a stable `[FUNCTION TAG]` before every MaxMEMS
block. This makes multi-function corpus files unambiguous and also allows the
batch experiment to match each DP result to the corresponding DFS2 artifacts.

## Reporting rule

For the SANER paper, do not describe unsupported concrete replays as failures of
the MaxMEMS algorithm. Report separately: corpus size, DP/DFS agreement,
replay-eligible functions/programs, branch-trace matches, undefined executions,
unsupported signatures, timeouts/errors, and any true mismatches.


## 2026-09-24 corpus-hardening update

To improve the 266-program result without changing the evaluated denominator or
the MaxMEMS semantics, the batch experiment now reads the frozen
`docs/maxmems-266-corpus-manifest.txt` and rejects corpus drift. The workflow
uses 12 shards instead of six so isolated expensive subjects do not prevent
unrelated programs from completing. Concrete witness replay also accepts common
scalar integer C signatures while continuing to reject pointer/array parameters
that require ownership or extent assumptions.

The aggregate artifact preserves three residual worklists:
`failures.csv`, `path-limit-functions.csv`, and
`replay-residual-functions.csv`. These files support targeted follow-up while
keeping every failed or timed-out subject in the frozen 266-program denominator.
