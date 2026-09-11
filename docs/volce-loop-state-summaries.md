# VolCE state-transition summary integration

For an affine loop whose concrete symbolic path executes the exact closed-form
trip count, Eppather derives:

```text
induction_out = induction_initial + step * iterations
```

The summary is passed with the path SMT formula to VolCE. VolCE searches the
path's bit-vector declarations for a source/SSA candidate and performs an
entailment check:

```text
path_constraints AND NOT(candidate_summary)
```

Only an UNSAT result permits the summary to be asserted. SAT/UNKNOWN summaries
are rejected and model counting continues with the original path formula. This
makes the optimization semantics-preserving and prevents truncated paths,
early exits, unsupported pointer updates, or ambiguous SSA names from changing
solution counts.

Diagnostics:

```text
[VOLCE LOOP SUMMARIES APPLIED]: N
[VOLCE LOOP SUMMARIES REJECTED]: M
```

The initial integration test runs five affine array-loop programs with VolCE
and requires a numeric solution-space count, a weighted average, and at least
one entailed summary per program.
