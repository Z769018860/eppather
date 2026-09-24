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


## MaxMEMS loop-branch maximization fix

During the 266-program follow-up, the DP implementation was found to differ
from DFS2 at loop headers: DFS2 enumerated both continuing and exiting a loop,
whereas MaxMemsDP returned the continuing branch as soon as it was feasible.
That policy is not a valid global maximization rule because an additional loop
iteration can change program state and steer execution away from a more
expensive post-loop branch.

MaxMemsDP now evaluates both bounded successors at each `for` and `while`
header and selects the feasible result with larger whole-path MEMS. Conditional
branches also use independent loop-state snapshots so exploration of one branch
cannot contaminate its sibling. The controlled MaxMEMS witness workflow and the
frozen 266-program workflow are both triggered by this change.


## Decision-level MEMS scoring

The corpus audit also found that the previous DP ranking score used one cached
`CFGNode::getMem()` value per CFG node. For a `for` header that value bundled
loop initialization, the true guard, and the update, even though DFS2 renders
those decisions at different dynamic visits. The selected path was then
re-evaluated with epat++ before printing, so path ranking and the reported MEMS
could use different accounting.

MaxMemsDP now accumulates cached MEMS costs per `PathDecisionKind`:
`LoopInit`, true/false guard, `LoopUpdate`, and ordinary code. This matches
the same decision sequence rendered by DFS2. The `-g` output additionally
reports `[DP INTERNAL MEMS]` and `[DP SCORE DELTA]`; a non-zero delta is
retained as a diagnostic rather than silently hiding a scoring discrepancy.


## Replay loop-bound synchronization

Concrete replay previously applied the raw `--max-loop` value to every loop.
That no longer matches Eppather: canonical constant affine `for` loops can be
auto-lifted to their proved trip count, and simple constant-bound `while`
loops can receive a larger conservative budget. A fixed loop such as
`for(i=0;i<5;i++)` could therefore be analyzed for five iterations but
replayed for only three, creating a false branch-trace mismatch.

The replay instrumenter now computes a per-loop bound using the same supported
affine forms and the same default 64-iteration autolift ceiling. Unsupported or
data-dependent loops continue to use the requested safety bound. This change
affects only the independent concrete oracle; it does not alter Eppather's
static DP or DFS2 analysis.


## 2026-09-24 validation-quality update

The frozen denominator remains 266 programs.  The experiment now separates
normalization/front-end quality from MaxMEMS correctness instead of treating
every unsuccessful case as a DP mismatch.  Each source first receives a GNU C
syntax preflight, but Eppather is still attempted so malformed normalization
outputs remain visible in the corpus.  Timeout cases are retried once with a
300-second budget while preserving `maxloop=3` and `maxpaths=1000`.

The aggregate report now distinguishes: syntax-invalid normalized programs,
DP/DFS timeouts, DP parse failures, true static DP/DFS mismatches, replay-only
mismatches, unsupported concrete replay, path-limit hits, and non-zero
`[DP SCORE DELTA]` diagnostics.  Concrete replay additionally records the
witness input and expected/actual ordered branch traces.  `switch/case`
subjects are explicitly marked replay-unsupported because the current concrete
tracer instruments `if`, `for`, and `while` decisions, not switch cases.

For reference, the saved 2026-05-09 all-stage result on the same 266-file
`output_complete2` corpus reported 202 DFS successes, 206 DP successes, and
145 files with DP=DFS MaxMEMS (54.5%).  New results should be compared against
that 145/266 static-agreement baseline, not against the 391-row multi-stage
summary that concatenated the 5/20/100/266 runs.
