# Affine while-loop state summary: controlled validation

Date: 2026-09-18

## Change

The CFG now recovers a candidate induction initializer and one affine update
for a simple constant-bound `while` loop. It rejects a candidate if another
write to the induction variable follows the recovered initializer, or if the
body contains nested control flow. The existing EpatRunner checks the observed
iteration count against the predicted exact trip count. VolCE checks
entailment before binding a candidate to an SMT variable.

This extends the current LoopSCC-compatible affine adapter. It does not add
LoopSCC's SPath/CSG graph or multi-branch periodic summaries.

## CI evidence

- [VolCE loop state summaries #41](https://github.com/Z769018860/eppather/actions/runs/35394175339):
  all five VolCE unit tests, five prior summary equivalence checks, and four
  failure-mode checks passed.
- The 20-subject summaries-on/off A/B experiment passed for 20/20 subjects,
  with identical nonzero solution-space counts and weighted-average MEMS.
- Ground-validated subjects rose from 18/20 to 19/20. The simple
  constant-bound `while` subject 14 now validates one transition; the
  input-dependent `while` subject 13 remains a fallback.
- A separate symbolic reassignment subject (`i=0; i=n; while(i<5)`) correctly
  falls back instead of reusing the stale constant initializer.
- Subject 14: count 1/1 and weighted MEMS 10/10 with summaries enabled/disabled.
- Aggregated A/B elapsed time was 9479 ms versus 9649 ms (1.0179x).
  This single-run difference is too small to substantiate a speedup.
- [Hybrid loop validation #22](https://github.com/Z769018860/eppather/actions/runs/35394175445)
  passed both jobs.

## Interpretation and next gate

The new while case is ground-validated after epat++ constant folding.
No subject applied a loop equality to an SSA variable (0/20). A ground
identity checks the arithmetic of the recovered transition, but by itself
does not prove that a guessed source initializer matches a surviving SMT
symbol. The source-level restrictions and completed-path check therefore
remain necessary. No loop body is replaced with a closed form, and there is
no demonstrated model-counting acceleration.

For the next step, preserve source-to-SSA provenance and prove the
input-to-final-state relation over the path formula. Then build and validate
SPath/CSG summaries for data-dependent and multi-branch loops before
claiming LoopSCC-level coverage or performance.
