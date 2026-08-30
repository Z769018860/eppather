# SANER 2027 research-track manuscript

This directory contains the full-length, double-anonymous SANER 2027 version
of the Eppather worst-case path exploration paper. The current build is a
10-page research-track manuscript, expanded from the original long paper
rather than a shortened summary.

## Build

```bash
pdflatex -interaction=nonstopmode -halt-on-error main.tex
pdflatex -interaction=nonstopmode -halt-on-error main.tex
```

## Submission checks

- IEEE conference class: `\\documentclass[10pt,conference]{IEEEtran}`
- Anonymous author block and no acknowledgments
- Main text limit: 10 pages; references may use up to 2 additional pages
- English PDF
- `Data Availability` section after the conclusion body, as requested by the
  SANER 2027 open-science policy
- Public repository URL omitted from the anonymous manuscript

Official research-track requirements:
https://conf.researchr.org/track/saner-2027/saner-2027-papers

- Mandatory abstract deadline: 2026-09-21 (AoE)
- Paper deadline: 2026-09-25 (AoE)
- Notification: 2026-12-01
- Conference: 2027-03-09 to 2027-03-12, Richmond, Virginia, USA

The manuscript's project-summary numbers come from
`docs/small-project-summary-iteration-validation-2026-08-14.md` and
`testcase/_eppather_runs/20260814_173835/`. The cJSON/tinyexpr/Lua results are
reported only as stress-case limitations because the stored program summaries
do not contain valid worst-path results.


## Full-paper content

The ten-page version retains and expands the original manuscript's substantive
material:

- analysis scope and detailed MEMS counting rules;
- bounded-DP recurrence, state-merging example, correctness argument, and
  complexity/bound sensitivity;
- compositional summaries, recursive SCC fixed points, and an interprocedural
  worked example;
- concrete path-witness replay under the same loop bound;
- full RQ1/RQ2/RQ3 protocol and evidence interpretation;
- per-project list/inih/SDS analysis and compatibility provenance;
- the condensed Zephyr work-queue path case study;
- expanded related work, threats, artifact instructions, and research-question
  answers.

The manuscript deliberately preserves the revised evidence boundaries: it does
not restore unsupported cJSON/tinyexpr/Lua success claims or interpret MEMS as
cycle-accurate WCET.
