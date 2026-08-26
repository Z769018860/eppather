# Adaptive loop-unrolling bound prediction

Eppather now computes a per-loop unfolding budget before DFS, DFS2, DP, and
greedy traversal. `--maxloop` is a safety cap (default: 64), rather than the
number blindly assigned to every loop. Unsupported loops conservatively retain
the historical fallback of three iterations.

## Algorithm

For each CFG loop header, the predictor extracts the tuple
`(induction variable, initial value, comparison, limit, step)` from the CFG's
normalized `initstmt_str`, `cond_str`, and `expr_str`.

1. Recognize a constant initializer such as `i = 0` or `int i = 0`.
2. Require a condition `i < C`, `i <= C`, `i > C`, or `i >= C` with constant C.
3. Recognize a non-zero affine update (`i++`, `i--`, `i = i +/- k`,
   `i += k`, or `i -= k`) and verify that it moves toward the exit.
4. Compute the trip count without enumerating paths:
   - strict comparison: `ceil(distance / abs(step))`;
   - inclusive comparison: `ceil((distance + 1) / abs(step))`.
5. Clamp the result to `--maxloop`. A clamped proof is marked conservative;
   an unclamped proof is exact.
6. If any proof obligation fails (input-dependent limit, non-affine update,
   pointer mutation, `while`, or inconsistent direction), use `min(3, cap)`.

The analysis is O(length of the three loop expressions), has no solver calls,
and is performed independently for nested loops. The safety cap is still
required because constant loops can legitimately contain millions of
iterations and path exploration grows exponentially with nested branches.

## Examples

| Loop | Predicted unfolding |
|---|---:|
| `for (i=0; i<10; i++)` | 10 |
| `for (i=2; i<=10; i=i+2)` | 5 |
| `for (i=100; i>0; i--)` with `--maxloop 64` | 64 (clamped) |
| `for (i=0; i<n; i++)` | 3 (fallback) |

Run the focused regression test with `bash tools/test_loop_bound_predictor.sh`.
