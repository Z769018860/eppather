# Source calibration for LLM function summaries (2026-09-25)

## Which experiment is which

The LLM-derived source files are in `testcase/llm_summaries/`; `tools/validate_llm_summaries.sh` compiles them and compares DFS2 (`-q`) with DP (`-g`) **on the same summary program**. Agreement is a useful analyzer regression check, but does not establish an access estimate for the original library function. `tools/auto_iterative_fix_with_llm.py` repairs parser compatibility in large C files; it stops at process return code 0 and does not test source equivalence. The separate `run_small_project_summaries.py` experiments for list/inih/sds do not use these three LLM summaries.

## Lua source-based correction

The old Lua model created and initialized two synthetic four-element arrays, scanned by copying bytes, and capped a transfer at four. Its reported 21 accesses therefore depended on initialization inside the generated function. The calibrated file is `testcase/llm_calibrated/lua_zread_summary.c`; the legacy `testcase/llm_summaries/lua_zread_summary.c` is retained only as an unvalidated historical baseline. The new bounded projection represents `ZIO.n` and the offset of `ZIO.p` as two integer slots supplied by the caller. Its loop follows the original `checkbuffer` and `luaZ_read` order and models `memcpy` as one source read and one destination write per copied byte.

`tools/validate_lua_projection.py` extracts the original function bodies directly from `testcase/lua/lzio.c`, builds separate original and instrumented versions, and checks a source-guided projection. It runs 16 defined inputs: initial available bytes 0–3 and requested bytes 0–3, a four-byte source and destination, and a reader returning EOZ when the initial buffer is exhausted. GCC undefined-behavior sanitizer is enabled. The projection matches the original's return, destination, ZIO state, and dynamic access count on all 16 inputs. The observed and projected counts are:

| Available bytes | Requested 0 | Requested 1 | Requested 2 | Requested 3 |
| --- | ---: | ---: | ---: | ---: |
| 0 | 0 | 1 | 1 | 1 |
| 1 | 0 | 9 | 11 | 11 |
| 2 | 0 | 9 | 11 | 13 |
| 3 | 0 | 9 | 11 | 13 |

Counting convention: each direct field or array element read/write counts one; a compound field update counts one read and one write; `memcpy` is **explicitly** modeled as one byte read plus one byte write. The 13 is the maximum observed **within these 16 cases**, not the unbounded function MaxMEMS. Array initialization in the caller and the internal work of a non-EOZ reader are excluded.

The CI workflow runs Eppather on this projection separately. An analyzer maximum over unconstrained pointer/size parameters is a property of the projection and its bounds; it cannot be compared directly with the 16-input observed maximum unless the same input contract and memcpy counting convention are enforced.

## Other two LLM models

The cJSON model replaces `parse_value` with an unconstrained `parse_success` parameter and changes the parser's pointer/global state into small arrays. The tinyexpr model scans a nine-element array, whereas the source wrapper calls `te_compile`, `te_eval`, and `te_free`. Existing values (15 and 20) are **model results**, not estimates validated against original-source instrumentation. They should not be presented as original cJSON/tinyexpr MaxMEMS, and DFS2/DP agreement on those files cannot supply the missing source check.

Any further LLM-generated summary must preserve the access-bearing operations, pointer aliases, branch conditions, and called-function contracts within a stated input domain. Require a behavior and access-count witness comparison against the original before using a generated file as a source-level estimate.

## First Eppather comparison

The unconstrained parameter experiment (Actions 36120332814, `maxloop=3`, `maxpaths=40`) timed out in both `-s` and `-q` after 120 seconds. Its partial paths included symbolic sizes far outside the validated 0–3 domain; the partial `[mem]` values are not usable final estimates.

A generated fixed-input entry for `available=2`, `requested=3` completed (`-q`, `maxloop=3`, `maxpaths=20`): Eppather reported `[DFS MAX MEMS]: 23`. Exactly ten array-element writes initialize caller-owned state in that entry, so the projected function body contributes `23 - 10 = 13` accesses. The separately instrumented original reports **13** for that same input, with equal return and final state. The next CI run gates four representative fixed inputs, covering empty buffer, full read, and partial read. This is path-level evidence in the stated domain, not a global maximum or evidence for the cJSON and tinyexpr models.

## Four Eppather path checks

The automated comparison from Actions 36142636220 passed all four selected input/branch classes, using the same maxloop 3 and maxpaths 20 for the fixed-input C entries:

| Available | Requested | Original-source witness | Eppather total | Caller initialization | Eppather function contribution |
| ---: | ---: | ---: | ---: | ---: | ---: |
| 0 | 1 | 1 | 11 | 10 | 1 |
| 1 | 1 | 9 | 19 | 10 | 9 |
| 2 | 3 | 13 | 23 | 10 | 13 |
| 3 | 3 | 13 | 23 | 10 | 13 |

The ten caller writes are two `z` slots, four `src` slots, and four `dst` slots. Each generated entry is a separate fixed-input program that copies the validated function body; the dynamic original is never initialized inside its measured function. This four-path match supports **bounded path-level accuracy** for the calibrated Lua projection under the stated byte-level memcpy model. The unbounded-parameter analyzer experiment timed out, so it supplies no whole-domain MaxMEMS value. The historical cJSON 15, Lua 21, and tinyexpr 20 results remain model-only numbers; none is upgraded into an original-source maximum by this test.

## Complete bounded Eppather comparison

Actions [36149816324](https://github.com/Z769018860/eppather/actions/runs/36149816324) passed the original-source instrumentation and **all 16** fixed-input Eppather checks. Each cell below is `original instrumented count / Eppather function count`; the latter subtracts exactly ten caller array initialization writes from the recorded analyzer total.

| Available bytes | Requested 0 | Requested 1 | Requested 2 | Requested 3 |
| --- | ---: | ---: | ---: | ---: |
| 0 | 0 / 0 | 1 / 1 | 1 / 1 | 1 / 1 |
| 1 | 0 / 0 | 9 / 9 | 11 / 11 | 11 / 11 |
| 2 | 0 / 0 | 9 / 9 | 11 / 11 | 13 / 13 |
| 3 | 0 / 0 | 9 / 9 | 11 / 11 | 13 / 13 |

The workflow artifact includes `lua_witness.csv`, `fixed_witness_comparison.csv`, generated fixed-input sources and per-case logs. This is exhaustive for the stated 4-by-4 **input grid**, not for Lua's full input space. In particular, `luaZ_fill`'s successful reader branch, callback memory accesses, and larger buffers remain outside the contract. A claim about those paths needs a separate reader/callback summary and an original-source witness under the same counting convention. These results do not alter the 193 collected failure records or establish a DP speed advantage.
