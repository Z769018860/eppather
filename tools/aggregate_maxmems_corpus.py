#!/usr/bin/env python3
"""Aggregate sharded MaxMEMS corpus validation with staged denominators."""
from __future__ import annotations

import argparse
import csv
import json
from pathlib import Path


FAIL_STATUSES = {"dp_failed", "dfs_failed", "dp_parse_error", "harness_error"}


def read_csvs(root: Path, pattern: str):
    rows = []
    for path in sorted(root.rglob(pattern)):
        with path.open(encoding="utf-8") as fh:
            rows.extend(csv.DictReader(fh))
    return rows


def manifest_sources(path: Path | None) -> set[str]:
    if path is None:
        return set()
    repo_root = Path(__file__).resolve().parents[1]
    out = set()
    for raw in path.read_text(encoding="utf-8").splitlines():
        line = raw.strip()
        if not line or line.startswith("#"):
            continue
        p = Path(line)
        if not p.is_absolute():
            p = (repo_root / p).resolve()
        out.add(str(p))
    return out


def rate(num: int, den: int) -> float | None:
    return num / den if den else None


def pct(value: float | None) -> str:
    return "N/A" if value is None else f"{value:.1%}"


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--input", type=Path, required=True)
    ap.add_argument("--output", type=Path, required=True)
    ap.add_argument("--manifest", type=Path)
    ap.add_argument("--strict", action="store_true")
    args = ap.parse_args()

    out = args.output.resolve()
    out.mkdir(parents=True, exist_ok=True)
    programs = read_csvs(args.input.resolve(), "programs-shard*.csv")
    functions = read_csvs(args.input.resolve(), "functions-shard*.csv")

    collected_sources = {str(Path(r["source"]).resolve()) for r in programs}
    inventory_sources = manifest_sources(args.manifest.resolve() if args.manifest else None)
    inventory_count = len(inventory_sources) if inventory_sources else len(collected_sources)
    duplicate_program_rows = len(programs) - len(collected_sources)

    syntax_valid = [r for r in programs if r.get("c_syntax_status") == "valid"]
    syntax_invalid = [r for r in programs if r.get("c_syntax_status") == "invalid"]
    syntax_timeout = [r for r in programs if r.get("c_syntax_status") == "timeout"]

    dp_completed = [
        r for r in programs
        if r.get("dp_status") == "0" and int(r.get("dp_blocks") or 0) > 0
    ]
    static_comparable = [
        r for r in programs
        if r.get("status") not in FAIL_STATUSES
        and int(r.get("functions_checked") or 0) > 0
    ]
    exhaustive_static = [
        r for r in static_comparable
        if int(r.get("path_limit_functions") or 0) == 0
    ]
    capped_static = [
        r for r in static_comparable
        if int(r.get("path_limit_functions") or 0) > 0
    ]
    exhaustive_equal = [
        r for r in exhaustive_static
        if int(r.get("static_mismatch_functions") or 0) == 0
    ]
    exhaustive_mismatch = [
        r for r in exhaustive_static
        if int(r.get("static_mismatch_functions") or 0) > 0
    ]
    capped_equal = [
        r for r in capped_static
        if int(r.get("static_mismatch_functions") or 0) == 0
    ]
    capped_mismatch = [
        r for r in capped_static
        if int(r.get("static_mismatch_functions") or 0) > 0
    ]

    replay_match = [r for r in functions if r.get("replay_status") == "match"]
    replay_mismatch = [r for r in functions if r.get("replay_status") == "mismatch"]
    replay_undefined = [r for r in functions if r.get("replay_status") == "undefined"]
    replay_error = [r for r in functions if r.get("replay_status") == "error"]
    replay_unsupported = [
        r for r in functions if r.get("replay_status", "").startswith("unsupported")
    ]
    replay_attempted = replay_match + replay_mismatch + replay_undefined + replay_error
    replay_defined = replay_match + replay_mismatch
    replay_eligible_programs = {
        r.get("source") for r in replay_attempted if r.get("source")
    }
    replay_defined_programs = {
        r.get("source") for r in replay_defined if r.get("source")
    }

    path_limit_functions = sum(r.get("path_limit_hit") == "1" for r in functions)
    static_equal_functions = sum(r.get("static_equal") == "1" for r in functions)
    uncapped_static_equal_functions = sum(
        r.get("static_equal") == "1" and r.get("path_limit_hit") != "1"
        for r in functions
    )

    hard = [r for r in programs if r.get("hard_failure") == "1"]
    dp_timeout = [
        r for r in programs
        if r.get("status") == "dp_failed" and r.get("dp_status") == "timeout"
    ]
    dfs_timeout = [
        r for r in programs
        if r.get("status") == "dfs_failed" and r.get("dfs_status") == "timeout"
    ]
    dp_parse_error = [r for r in programs if r.get("status") == "dp_parse_error"]
    retry_attempted = [
        r for r in programs
        if r.get("dp_retried") == "1" or r.get("dfs_retried") == "1"
    ]
    retry_rescued = [
        r for r in retry_attempted if r.get("status") not in {"dp_failed", "dfs_failed"}
    ]

    delta_known = [r for r in functions if str(r.get("dp_score_delta", "")).strip()]
    delta_nonzero = sum(int(r.get("dp_score_delta") or 0) != 0 for r in delta_known)

    replay_status_counts = {}
    for r in functions:
        st = r.get("replay_status") or "missing"
        replay_status_counts[st] = replay_status_counts.get(st, 0) + 1

    summary = {
        # Inventory is descriptive only; it is not used as the algorithm-success denominator.
        "inventory_programs": inventory_count,
        "programs_collected": len(programs),
        "unique_programs_collected": len(collected_sources),
        "duplicate_program_rows": duplicate_program_rows,
        "syntax_valid_programs": len(syntax_valid),
        "syntax_invalid_programs": len(syntax_invalid),
        "syntax_timeout_programs": len(syntax_timeout),
        "dp_completed_programs": len(dp_completed),
        "static_comparison_programs": len(static_comparable),
        "exhaustive_static_programs": len(exhaustive_static),
        "exhaustive_static_equal_programs": len(exhaustive_equal),
        "exhaustive_static_mismatch_programs": len(exhaustive_mismatch),
        "exhaustive_static_agreement_rate": rate(len(exhaustive_equal), len(exhaustive_static)),
        "capped_static_programs": len(capped_static),
        "capped_static_equal_programs": len(capped_equal),
        "capped_static_mismatch_programs": len(capped_mismatch),
        "functions_checked": len(functions),
        "static_equal_functions": static_equal_functions,
        "uncapped_static_equal_functions": uncapped_static_equal_functions,
        "path_limit_functions": path_limit_functions,
        "replay_eligible_programs": len(replay_eligible_programs),
        "replay_defined_programs": len(replay_defined_programs),
        "replay_attempted_functions": len(replay_attempted),
        "replay_defined_functions": len(replay_defined),
        "replay_match_functions": len(replay_match),
        "replay_mismatch_functions": len(replay_mismatch),
        "replay_defined_match_rate": rate(len(replay_match), len(replay_defined)),
        "replay_undefined_functions": len(replay_undefined),
        "replay_error_functions": len(replay_error),
        "replay_unsupported_functions": len(replay_unsupported),
        "dp_timeout_programs": len(dp_timeout),
        "dfs_timeout_programs": len(dfs_timeout),
        "dp_parse_error_programs": len(dp_parse_error),
        "retry_attempted_programs": len(retry_attempted),
        "retry_rescued_programs": len(retry_rescued),
        "hard_failure_programs": len(hard),
        "dp_score_delta_known_functions": len(delta_known),
        "dp_score_delta_nonzero_functions": delta_nonzero,
        "replay_status_counts": replay_status_counts,
    }

    if inventory_sources:
        summary["inventory_missing_programs"] = len(inventory_sources - collected_sources)
        summary["inventory_extra_programs"] = len(collected_sources - inventory_sources)

    for name, rows in (("programs.csv", programs), ("functions.csv", functions)):
        if rows:
            with (out / name).open("w", newline="", encoding="utf-8") as fh:
                w = csv.DictWriter(fh, fieldnames=list(rows[0].keys()))
                w.writeheader()
                w.writerows(rows)

    failures = [
        r for r in programs
        if r.get("hard_failure") == "1" or r.get("status") == "mismatch"
    ]
    path_limited = [r for r in functions if r.get("path_limit_hit") == "1"]
    replay_residual = [
        r for r in functions
        if r.get("replay_status") in ("error", "mismatch", "witness_not_found")
    ]
    for name, rows in (
        ("failures.csv", failures),
        ("path-limit-functions.csv", path_limited),
        ("replay-residual-functions.csv", replay_residual),
    ):
        if rows:
            with (out / name).open("w", newline="", encoding="utf-8") as fh:
                w = csv.DictWriter(fh, fieldnames=list(rows[0].keys()))
                w.writeheader()
                w.writerows(rows)

    (out / "summary.json").write_text(
        json.dumps(summary, indent=2) + "\n", encoding="utf-8"
    )

    md = [
        "# MaxMEMS corpus validation: staged cohorts",
        "",
        "The raw inventory size is reported for reproducibility only. It is not the denominator for algorithm correctness.",
        "",
        "## Cohort flow",
        "",
        f"- Raw normalized-source inventory: **{summary['inventory_programs']} programs**",
        f"- GNU C syntax-valid: **{summary['syntax_valid_programs']}**",
        f"- DP result produced: **{summary['dp_completed_programs']}**",
        f"- DP/DFS statically comparable: **{summary['static_comparison_programs']}**",
        f"- Exhaustive-within-bounds static cohort (no maxpaths hit): **{summary['exhaustive_static_programs']}**",
        f"- DP/DFS MaxMEMS agreement in exhaustive cohort: **{summary['exhaustive_static_equal_programs']} / {summary['exhaustive_static_programs']} ({pct(summary['exhaustive_static_agreement_rate'])})**",
        f"- Exhaustive-cohort static mismatches: **{summary['exhaustive_static_mismatch_programs']}**",
        f"- Path-capped static cohort, reported separately: **{summary['capped_static_programs']}**",
        "",
        "## Independent concrete replay cohort",
        "",
        f"- Replay-attempted functions: **{summary['replay_attempted_functions']}**",
        f"- Defined concrete executions: **{summary['replay_defined_functions']}**",
        f"- Defined branch-trace matches: **{summary['replay_match_functions']} / {summary['replay_defined_functions']} ({pct(summary['replay_defined_match_rate'])})**",
        f"- Undefined concrete executions: **{summary['replay_undefined_functions']}**",
        f"- Replay-unsupported functions: **{summary['replay_unsupported_functions']}**",
        f"- Replay errors: **{summary['replay_error_functions']}**",
        "",
        "## Coverage / residual diagnostics",
        "",
        f"- DP timeouts after retry: **{summary['dp_timeout_programs']}**",
        f"- DFS timeouts after retry: **{summary['dfs_timeout_programs']}**",
        f"- DP parse errors: **{summary['dp_parse_error_programs']}**",
        f"- Retry attempted/rescued: **{summary['retry_attempted_programs']} / {summary['retry_rescued_programs']}**",
        f"- Functions hitting maxpaths: **{summary['path_limit_functions']}**",
        f"- Non-zero DP score-delta diagnostics: **{summary['dp_score_delta_nonzero_functions']} / {summary['dp_score_delta_known_functions']}**",
        "",
    ]
    (out / "summary.md").write_text("\n".join(md), encoding="utf-8")
    print("MAXMEMS_CORPUS_SUMMARY " + json.dumps(summary, sort_keys=True))

    integrity_bad = (
        duplicate_program_rows != 0
        or (inventory_sources and collected_sources != inventory_sources)
    )
    semantic_bad = (
        summary["exhaustive_static_mismatch_programs"] != 0
        or summary["replay_mismatch_functions"] != 0
    )
    return 1 if args.strict and (integrity_bad or semantic_bad) else 0


if __name__ == "__main__":
    raise SystemExit(main())
