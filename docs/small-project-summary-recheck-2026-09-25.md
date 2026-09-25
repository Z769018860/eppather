# Small-project summary recheck (2026-09-25)

## Why some estimates are too low

The old final CSV selected the first analyzer success, even when the input was a type-erased rewrite, a semantic stub, or a signature-only compatibility model. Those numbers count accesses in the rewritten model and are not MaxMEMS estimates for the original function.

A reproducible preprocessing defect also changed `i < size - 1 && src[i]` into `i < size - 1 &src[i]` in the `ini_strncpy0` type-erased slice. The regular expression that removed address-of operators matched the second ampersand of `&&`. A separate rewrite maps `self->tail->next` to one hashed array slot, losing the intermediate member access and potentially aliasing unrelated fields. These approximations cannot justify an original-source access estimate. The patch preserves logical AND and emits an empty `worst_mems` for final rows selected from approximate slices; the old model number is retained explicitly in `model_worst_mems`. A native analyzer success on an original `closure` or `entry_only` slice has `estimate_scope=original_slice` and `validated_worst_mems`.

## Repeated original-source dynamic check

We compiled separate original and instrumented upstream C implementations with GCC and undefined-behavior sanitizer. The harness compared functional output on each input before recording accesses. The instrumented function bodies count array subscripts and member accesses, including both steps of a nested member chain. Results from the repeated local run:

| Original function | Tested witness | Observed accesses | Archived model worst_mems |
| --- | --- | ---: | ---: |
| list_new | successful allocation | 5 | 5 |
| list_rpush | one-node list and nonnull node | 9 | 0 |
| list_lpush | one-node list and nonnull node | 9 | 0 |
| ini_strncpy0 | size 3, source length 2 | 7 | 2 |

The list harness also checks empty lists (7 accesses) and null nodes (0 accesses); the inih harness checks sizes 1–3 and source lengths 0–2. These are observed test-path counts, **not** global maxima or a proof that the analyzer should output precisely these values. A lower original-source MaxMEMS bound would require investigating the analyzer's access definition and path bounds. No execution-time comparison is claimed.

## Recompute procedure

Run `python3 -m unittest tools/test_summary_estimate_provenance.py`. The CI workflow `recheck-small-project-summaries.yml` builds cnip and recomputes native summaries for original slices of list_new, list_rpush, list_lpush, and ini_strncpy0. It uploads run and final CSV files; any blank validated estimate is an unavailable result, not zero. This narrow check makes no claim about the separate 193 collected cases and does not add failed cases to that corpus.

## First CI recheck outcome

The first run (GitHub Actions 36116854797) exposed a remaining fallback: disabling `compat_entry` did not disable `auto_compat`. For original slices, `list_new` produced `entry function not found` on both closure and entry-only; `list_rpush` and `list_lpush` returned -11 on both; `ini_strncpy0` produced `entry function has no available summary path` on both. The fallback's model counts were 0, 2, 2, 2 respectively and did not match original-source witnesses 5, 9, 9, 7. These are counts on different programs. The revised CI command explicitly disables `auto_compat` too. Until native original slices yield valid summaries, there is no comparable static estimate for these four functions.
