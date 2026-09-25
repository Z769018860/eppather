# Reviewer-facing method audit: memoization, loop summaries, and summary fidelity

This note separates measured results from proposed baselines. The 193 collected failures remain the failure-corpus denominator. The six-project source witnesses are a separate bounded validation set.

## 1. Prefix-keyed memoization

`MaxMemsDP` currently indexes `dpMemo` by `(CFGNode*, LoopMapKey(loopUnrollMap), pathPrefix)`. Because `pathPrefix` encodes complete decisions, a memo entry is reused only if exactly the same recorded prefix and loop state reach the same CFG node. It is **not justified** to claim merging of semantically equivalent states or asymptotic dynamic-programming acceleration. Exact bounded leaf scoring comes from `EpatRunner(...).solve(curDecisions)`; the bounded search explores CFG decisions and checks feasibility. The `-g` command name is retained for reproducibility, but paper prose should call it **prefix-keyed bounded search** until a sound state abstraction and actual reuse are demonstrated.

The new `tools/audit_dp_memo.py` logs per-case memo lookups, hits, stores, distinct entries, leaf solves, `-q` DFS2 versus `-g` bounded-search MEMS, and the core durations from each mode. It sets `--maxpaths 0`, identical loop bounds, and disables opt-in LoopSCC shortcuts. Workflow `Reviewer method audit` archives the raw logs and CSV. Timing is diagnostic only: four small cases, no repeated runs, no hardware normalization or speedup claim. The older three-project 66-entry experiment reported DP timeouts on two inih slices and does not establish general superiority. Insert the actual audit data below only after CI completes.

## 2. Loop-state summary ablation and baselines

The existing [VolCE A/B run 35883347664](https://github.com/Z769018860/eppather/actions/runs/35883347664) toggled `EPPATHER_DISABLE_VOLCE_LOOP_SUMMARIES` on 20 bounded loop subjects. The preserved `loopscc-effect-results/effect.csv` records exact model counts, weighted MEMS, summary application category, and counting assertions per subject. All 20/20 matched both model count and weighted MEMS; 16 applied scalar SSA, three passed the ground-validation route, one fell back and none were rejected. The aggregate number of counting assertions was 209 with summaries versus 563 without. This ablates **VolCE scalar loop-state summaries**, not the separate opt-in MaxMEMS DFS shortcut, and is not an ablation of LLM function summaries. It does not establish a general runtime improvement.

KLEE is a symbolic execution engine and WISE seeks high-complexity test inputs. The original implicit-path-enumeration (IPET) method bounds a different cost objective unless we explicitly assign one unit to each memory observation and enforce identical path feasibility and loop bounds. A table comparing their native time/instruction/test objectives directly to Eppather MEMS would be invalid. No numerical KLEE/WISE/IPET result has been obtained on these six source boundaries: **do not display invented baseline bars or state-of-the-art performance claims**. A future matched evaluation needs the same instrumented access contract, source boundary, input domain, loop limits, and proof/test status; KLEE/WISE test maxima are lower bounds, whereas a structural unit-cost IPET bound can be infeasible-path inflated.

## 3. RQ3: precise claim and negative findings

Historical [three-project summary experiment](small-project-summary-iteration-validation-2026-08-14.md) yielded 66/66 output slices, but 46/66 reported worst MEMS 0; only 30/66 selected closure or entry-only source-level slices, 11/66 used semantic approximations, and 25/66 used compatibility models. In its same-slice control, DFS2 finished 66/66 while `-g` finished 64/66 (two inih timeouts). Therefore slice-generation success does **not** measure source semantic fidelity. Some original-body source-level slices also yield zero despite concrete source accesses, so a zero should be recorded as unsupported/undercounted rather than presented as a precise maximum.

The independent [six-project source witness experiment](six-project-source-eppather-comparison.md) measures **36/36 fixed-input count agreements**: list 3, inih 9, SDSLib 2, cJSON direct-field fragment 4, tinyexpr constant evaluator fragment 2, Lua EOZ-reader domain 16. They are source-guided projections checked against original source instrumentation and output/state on the stated inputs, not unchanged full-function analyses or unbounded maximum proofs. In particular cJSON excludes accesses inside macros and callees, tinyexpr excludes recursion, and Lua excludes refill. The historical LLM summary's positive values must not be substituted for these counts.

Suggested RQ3 question: *Under explicitly stated source boundaries and finite input domains, when do generated or source-guided summaries preserve observed memory-access counts, and where do original-source and LLM approximations fail?* Report three distinct strata: original-body slices, rewritten/LLM compatibility summaries, and the 36 instrumented bounded source witnesses. Retain zero-count failures and negative controls in the main text.

### Paper-ready scoped prose

> We audited the prefix-keyed search by recording memo lookups and hits while comparing the same loop-bounded functions with exhaustive DFS2. The key includes the entire branch prefix, so reuse is not assumed; its measured hit rate and timing are reported in Table X. In a separate loop-state-summary ablation, all 20 finite-domain subjects retained the same model counts and weighted MEMS, while counting assertions fell from 563 to 209. The loop ablation does not evaluate the separate function-summary projection. For function summaries, historical generation success (66/66) concealed 46 zero-valued maximum counts and substantial model fallback. We therefore test fidelity directly: 36 bounded source-instrumented witnesses across six projects matched counts of their scoped Eppather projections. These are path-level validation observations, not proofs of full-library maxima.

### Checklist before submission

- Replace Table X with measured per-case lookup/hit/time output and state clearly if hits are zero.
- Cite the original KLEE, WISE, and IPET work; describe metric mismatch honestly until comparable experiments exist.
- Do not label the VolCE scalar-summary A/B test as MaxMEMS DFS shortcut or LLM-summary ablation.
- Never use the historical six-project models as original-source maxima; retain the corpus denominator 193.
