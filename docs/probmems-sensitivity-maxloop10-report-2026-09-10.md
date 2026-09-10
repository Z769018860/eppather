# ProbMEMS maxloop 1–10 sensitivity report (2026-09-10)

Workflow: [run 34462238842](https://github.com/Z769018860/eppather/actions/runs/34462238842)

## Design

- 6 subjects: cJSON, inih, clibs-list, Lua, sds, tinyexpr
- 2 input domains: [-1,1] and [-3,3]
- maxloop: 1, 2, 3, 5, 8, 10
- maxpaths: 80
- 72 configurations total

## Outcomes

| Outcome | Count |
|---|---:|
| PASS | 66 |
| TIMEOUT | 6 |
| Zero weighted sum among completed configurations | 0 |
| Path-cap hit | 5 |

All six timeouts are cJSON with domain [-3,3]. They are censored and excluded from metric comparisons.

## Saturation findings

- inih, clibs-list, and sds are invariant across maxloop 1–10 for a fixed input domain.
- Lua reaches stable path count, EMEMS, and MaxMEMS at maxloop=3. Runtime rises sharply from 1–2 to 3 and then remains approximately stable.
- tinyexpr reaches stable path count, EMEMS, and MaxMEMS at maxloop=3.
- cJSON under [-1,1] reaches EMEMS 9.66667 by maxloop=2 and remains identical through 10. MaxMEMS reaches 17 by maxloop=3. Runs from maxloop=2 onward hit maxpaths=80, so the apparent stability is censored by the path cap.
- Raising maxloop above 3 provides no additional metric value for the successful subjects in this experiment.
- Increasing the cJSON input domain to [-3,3] causes timeout at every tested loop bound, including maxloop=1. The dominant factor is counting/domain complexity, not loop depth.

## Recommended policy

Use maxloop=3 as the default pilot bound for these large-project subjects, then apply adaptive retry only when:

1. no feasible path is produced;
2. the predicted bound is known to be below a constant loop requirement;
3. metrics have not stabilized between adjacent bounds.

Do not globally force maxloop=8 or 10. Record timeout and path-cap censoring separately.
