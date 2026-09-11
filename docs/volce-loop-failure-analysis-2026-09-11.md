# VolCE loop-summary failure analysis (2026-09-11)

## Confirmed causes

1. **Constant folding was reported as application.** epat++ often removes a
   local induction variable from SMT. The previous fallback checked the ground
   identity `final = initial + step * iterations` and counted it as an applied
   summary. That identity is useful validation evidence, but it cannot reduce
   the VolCE model space because it binds no SMT variable.
2. **A small `maxloop` could eliminate every complete path.** For a provable
   loop such as `i < 4`, stopping at two iterations and then asserting the false
   condition produces an infeasible exit. Canonical affine loops are now lifted
   to their exact trip count up to a default hard cap of 64. Set
   `EPPATHER_EXACT_LOOP_AUTOLIFT_CAP` to override the cap; a non-positive or
   invalid value disables lifting.
3. **While-loop transition metadata is incomplete.** CFG nodes currently carry
   the condition but not a normalized initializer and update for while loops.
   They remain bounded by `maxloop` and are explicitly diagnosed rather than
   silently omitted.
4. **Break/return paths are not exact whole-loop transitions.** When the
   observed iteration count differs from the predicted canonical trip count,
   Eppather safely skips the affine summary and reports the mismatch.
5. **A zero MEMS value is not by itself a loop-bound failure.** It may represent
   a path containing only scalar/register operations, an unsupported memory
   construct in the backend, or text-fallback estimation. Dataset reports must
   distinguish these cases from “no feasible complete path”.

## New observable categories

- `VOLCE LOOP SUMMARIES APPLIED`: an entailed equality was bound to an actual
  SMT/SSA variable.
- `VOLCE LOOP SUMMARIES GROUND-VALIDATED`: the source transition arithmetic was
  validated after the induction variable had disappeared from SMT; no model
  reduction is claimed.
- `VOLCE LOOP SUMMARIES REJECTED`: the candidate relation was not sound.
- `VOLCE LOOP SUMMARY DIAGNOSTIC`: summary construction was skipped, with a
  reason such as missing while metadata or an early exit.

## Regression coverage

`tests/VolceStateSummaryTests.cpp` separates SSA application, ground validation,
and rejection. `tools/validate_volce_loop_failure_modes.sh` covers exact-bound
auto-lifting, an input-dependent while loop, and an early-break loop. The
existing five-case equivalence test still requires summarized and baseline
solution counts and weighted-average MEMS to match.

## Remaining research work

- Recover normalized initializer/update and modified-variable sets for while
  loops, preferably through a LoopSCC adapter.
- Map source variables to SSA definitions robustly. Ground-validated summaries
  provide correctness evidence but not a performance benefit.
- Separate full input-domain model counting from variables retained in the SMT
  path formula. An unused function parameter may currently disappear, so a
  count of one means one projected SMT model, not necessarily one source-input
  valuation.
- Label zero MEMS results using syntactic memory access, backend support, solver
  status, and fallback mode before including them in paper statistics.
