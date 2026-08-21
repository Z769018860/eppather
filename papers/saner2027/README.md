# SANER 2027 research-track manuscript

This directory contains the double-anonymous SANER 2027 version of the
Eppather worst-case path exploration paper.

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
