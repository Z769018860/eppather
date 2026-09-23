# Bounded memory projection enumeration experiment (2026-09-20)

## Method

For a single canonical memory region of at most six cells, at least five projected cells, and at most two projected scalar declarations, enumerate distinct values for one projection term at a time using solver push/pop. A solver frame holds only sibling exclusions for the current term; complete-model blocking remains the default for other programs. The original projected-model semantics, bounds, SSA treatment and summary validation are unchanged.

Reproduce with the `ProbMEMS array and pointer projection` and `VolCE loop state summaries` workflows for PR #95. The new unit fixture has six memory cells, constrains cells zero and one to be equal, and expects 3^5 = 243 projected models.

## Observations

The first array/pointer workflow on commit `04cc79824b912d66ed53b79984bd436b4626ae23` completed: https://github.com/Z769018860/eppather/actions/runs/35478376307. Its 20-subject main manifest compiled in both modes, and 17/20 memory-projection runs completed within the existing 60-second per-subject limit, versus 16/20 in https://github.com/Z769018860/eppather/actions/runs/35441863861. The previously timed-out ap04 completed with 59,049 projected models and weighted MEMS 5; ap06, ap07 and ap15 still timed out. ap04 also completed at maxloop 2, 5 and 8 with the same 59,049 models and weighted MEMS 5. These are exact completed counts under the configured finite [-1,1] value bounds, not claims about unbounded C inputs.

The 20 loop-summary comparison cases passed with identical counts and weighted MEMS on the implementation run https://github.com/Z769018860/eppather/actions/runs/35478376281. The weighted-average regression passed as well. Project-level cJSON hit the original 180-second limit in several CI runs. A diagnostic 240-second run also timed out once. A paired rerun showed the previous implementation timing out at 180 seconds and the new implementation finishing in 179 seconds with 243 solutions and weighted MEMS 9.66667: https://github.com/Z769018860/eppather/actions/runs/35441861708 and https://github.com/Z769018860/eppather/actions/runs/35479718266. The final code's project workflow succeeded with the same cJSON result in 178 seconds: https://github.com/Z769018860/eppather/actions/runs/35480383532. The project workflow does not enable memory projection. These timings show a near-limit, unstable project test; they do not establish a performance gain from the new enumerator.

The final-code array/pointer workflow https://github.com/Z769018860/eppather/actions/runs/35480385768 confirms 17/20 memory runs complete, including ap04 with 59,049 models at maxloop 2, 5 and 8. ap06, ap07 and ap15 remain TIMEOUT under the unchanged 60-second per-case bound.

## Follow-up resolved on 2026-09-23

The proposed next step was implemented in PR #97 as a proved projection-component factorization. The dependency proof is performed on the semantics-preserving reduced counting formula after SSA elimination and solver reconstruction. Correlated memory cells remain connected; symbolic addresses that may alias are conservatively joined.

On workflow run 35883347768, memory projection completed on 20/20 subjects under the unchanged 60-second per-case limit. The three remaining timeouts from this report all completed: ap06 counted 1,948,617 projected models in about 2.96 seconds of model-count time, ap07 counted 531,441 in about 15.8 ms, and ap15 counted 1,948,617 in about 2.94 seconds. See `docs/loopscc-integration-status-2026-09-23.md` for the current integration boundary and next SPath/CSG gate.
