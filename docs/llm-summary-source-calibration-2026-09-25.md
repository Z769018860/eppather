# Source calibration for LLM function summaries (2026-09-25)

## Which experiment is which

The LLM-derived source files are in `testcase/llm_summaries/`; `tools/validate_llm_summaries.sh` compiles them and compares DFS2 (`-q`) with DP (`-g`) **on the same summary program**. Agreement is a useful analyzer regression check, but does not establish an access estimate for the original library function. `tools/auto_iterative_fix_with_llm.py` repairs parser compatibility in large C files; it stops at process return code 0 and does not test source equivalence. The separate `run_small_project_summaries.py` experiments for list/inih/sds do not use these three LLM summaries.

## Lua source-based correction

The old Lua model created and initialized two synthetic four-element arrays, scanned by copying bytes, and capped a transfer at four. Its reported 21 accesses therefore depended on initialization inside the generated function. The new bounded projection represents `ZIO.n` and the offset of `ZIO.p` as two integer slots supplied by the caller. Its loop follows the original `checkbuffer` and `luaZ_read` order and models `memcpy` as one source read and one destination write per copied byte.

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
