#!/usr/bin/env python3
"""Collect public AOJ C solutions and official system tests for Eppather.

Only public submissions are downloaded.  The default profile accepts a removable
contest I/O wrapper (main/scanf/printf) while conservatively rejecting constructs
that Eppather cannot currently analyse.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import os
import re
import shutil
import subprocess
import sys
import tempfile
import time
from dataclasses import asdict, dataclass
from pathlib import Path
from typing import Any, Iterable
from urllib.error import HTTPError, URLError
from urllib.parse import quote
from urllib.request import Request, urlopen

API = "https://judgeapi.u-aizu.ac.jp"
DATA = "https://judgedat.u-aizu.ac.jp"

TOPIC_WORDS = {
    "array": 8, "matrix": 8, "sequence": 6, "vector": 5,
    "pointer": 10, "linked list": 9, "list": 5, "stack": 5,
    "queue": 5, "sort": 4, "search": 4, "string": 3, "table": 3,
}

# Full contest programs need these wrapper calls. Other calls are rejected unless
# they are functions declared in the same translation unit.
WRAPPER_CALLS = {
    "main", "scanf", "printf", "getchar", "putchar", "puts", "gets", "fgets",
    "strlen", "strcmp", "strcpy", "memset", "memcpy", "abs",
}

FORBIDDEN = [
    ("aggregate type", re.compile(r"\b(struct|union|enum)\b")),
    ("typedef", re.compile(r"\btypedef\b")),
    ("dynamic memory", re.compile(r"\b(malloc|calloc|realloc|free)\s*\(")),
    ("unsupported control flow", re.compile(r"\b(goto|switch|do)\b")),
    ("floating point", re.compile(r"\b(float|double|long\s+double)\b")),
    ("variadic", re.compile(r"\.\.\.")),
    ("function pointer", re.compile(r"\(\s*\*\s*[A-Za-z_]\w*\s*\)\s*\(")),
    ("C++ syntax", re.compile(r"\b(namespace|template|class|new|delete)\b|::|<iostream>")),
]


@dataclass
class Compatibility:
    accepted: bool
    reasons: list[str]
    features: list[str]


class Client:
    def __init__(self, delay: float, retries: int, cache: Path, user_agent: str):
        self.delay, self.retries, self.cache = delay, retries, cache
        self.user_agent, self.last_request = user_agent, 0.0
        cache.mkdir(parents=True, exist_ok=True)

    def get(self, url: str) -> Any:
        key = hashlib.sha256(url.encode()).hexdigest() + ".json"
        cached = self.cache / key
        if cached.exists():
            return json.loads(cached.read_text(encoding="utf-8"))
        error: Exception | None = None
        for attempt in range(self.retries + 1):
            wait = self.delay - (time.monotonic() - self.last_request)
            if wait > 0:
                time.sleep(wait)
            try:
                req = Request(url, headers={"User-Agent": self.user_agent, "Accept": "application/json"})
                self.last_request = time.monotonic()
                with urlopen(req, timeout=45) as response:
                    value = json.loads(response.read().decode("utf-8"))
                cached.write_text(json.dumps(value, ensure_ascii=False), encoding="utf-8")
                return value
            except (HTTPError, URLError, TimeoutError, json.JSONDecodeError) as exc:
                error = exc
                if isinstance(exc, HTTPError) and exc.code == 404:
                    raise
                time.sleep(min(30.0, 2.0 ** attempt))
        raise RuntimeError(f"request failed: {url}: {error}")


def strip_comments_strings(source: str) -> str:
    pattern = r'("(?:\\.|[^"\\])*")|(\'(?:\\.|[^\'\\])*\')|(/\*.*?\*/)|(//[^\n]*)'
    return re.sub(pattern, lambda m: " " * len(m.group(0)), source, flags=re.S)


def compatibility(source: str) -> Compatibility:
    clean = strip_comments_strings(source)
    reasons = [name for name, pattern in FORBIDDEN if pattern.search(clean)]
    if re.search(r"^\s*#\s*define\b", clean, re.M):
        reasons.append("macro")
    # Conservative VLA detector: an array dimension must be an integer literal or
    # a simple compile-time macro; macros are rejected above, so identifiers fail.
    if re.search(r"\b(?:char|short|int|long)\s+[A-Za-z_]\w*\s*\[\s*[A-Za-z_]\w*", clean):
        reasons.append("variable length array")
    declared = set(re.findall(
        r"(?:^|[;}])\s*(?:static\s+)?(?:const\s+)?(?:unsigned\s+|signed\s+)?"
        r"(?:void|char|short|int|long|size_t)\s+([A-Za-z_]\w*)\s*\([^;{}]*\)\s*\{",
        clean, re.M,
    ))
    calls = set(re.findall(r"\b([A-Za-z_]\w*)\s*\(", clean))
    keywords = {"if", "for", "while", "sizeof", "return"}
    unknown = sorted(calls - declared - WRAPPER_CALLS - keywords)
    if unknown:
        reasons.append("external calls: " + ", ".join(unknown))
    features = []
    if re.search(r"\[[^\]]+\]", clean): features.append("array")
    if re.search(r"(?:\*\s*[A-Za-z_]|[A-Za-z_]\w*\s*\*)", clean): features.append("pointer")
    if re.search(r"\bfor\s*\(|\bwhile\s*\(", clean): features.append("loop")
    return Compatibility(not reasons, reasons, features)


def candidate_ids() -> list[str]:
    ids: list[str] = []
    # AOJ educational courses predominantly use A-D tasks.  Probe those first;
    # broader families below provide enough candidates to reach 100 while
    # avoiding hundreds of guaranteed 404 requests.
    for prefix, max_chapter in (("ITP1", 11), ("ALDS1", 15)):
        for chapter in range(1, max_chapter + 1):
            for letter in "ABCD":
                ids.append(f"{prefix}_{chapter}_{letter}")
    for prefix, chapters, letters in (("DSL", 6, "ABCDEFGHI"), ("DPL", 5, "ABCDEFG"), ("GRL", 7, "ABCDEFG")):
        for chapter in range(1, chapters + 1):
            for letter in letters:
                ids.append(f"{prefix}_{chapter}_{letter}")
    return ids


def records(value: Any) -> list[dict[str, Any]]:
    if isinstance(value, list): return [x for x in value if isinstance(x, dict)]
    if isinstance(value, dict):
        for key in ("content", "solutions", "items", "data"):
            if isinstance(value.get(key), list): return records(value[key])
    return []


def source_from_review(value: Any) -> str:
    if isinstance(value, dict):
        for key in ("sourceCode", "source", "code"):
            if isinstance(value.get(key), str): return value[key]
        for nested in value.values():
            found = source_from_review(nested)
            if found: return found
    return ""


def test_count(header: Any) -> int:
    if isinstance(header, list): return len(header)
    if isinstance(header, dict):
        for key in ("count", "numberOfTestCases", "size", "total"):
            if isinstance(header.get(key), int): return header[key]
        for key in ("headers", "testcases", "items", "data"):
            if isinstance(header.get(key), list): return len(header[key])
    return 0


def test_io(value: Any) -> tuple[str, str]:
    if isinstance(value, dict):
        inp = next((value[k] for k in ("input", "in") if isinstance(value.get(k), str)), "")
        out = next((value[k] for k in ("output", "out") if isinstance(value.get(k), str)), "")
        if inp or out: return inp, out
        for nested in value.values():
            pair = test_io(nested)
            if pair != ("", ""): return pair
    return "", ""


def normalized_output(text: str) -> str:
    return "\n".join(line.rstrip() for line in text.rstrip().splitlines())


def compile_and_verify(source: Path, tests: list[tuple[Path, Path]], timeout: float) -> dict[str, Any]:
    compiler = shutil.which("cc") or shutil.which("gcc") or shutil.which("clang")
    if not compiler: return {"compiled": False, "error": "no C compiler", "passed": 0, "total": len(tests)}
    with tempfile.TemporaryDirectory() as td:
        binary = Path(td) / "solution"
        build = subprocess.run([compiler, "-std=c11", "-O0", str(source), "-o", str(binary)], text=True, capture_output=True)
        if build.returncode:
            return {"compiled": False, "error": build.stderr[-4000:], "passed": 0, "total": len(tests)}
        passed = 0
        for inp, expected in tests:
            try:
                run = subprocess.run([str(binary)], input=inp.read_text(), text=True, capture_output=True, timeout=timeout)
                if run.returncode == 0 and normalized_output(run.stdout) == normalized_output(expected.read_text()): passed += 1
            except subprocess.TimeoutExpired:
                pass
        return {"compiled": True, "passed": passed, "total": len(tests)}


def topic_score(description: Any) -> int:
    text = json.dumps(description, ensure_ascii=False).lower()
    return sum(weight for word, weight in TOPIC_WORDS.items() if word in text)


def collect(args: argparse.Namespace) -> int:
    root = args.output.resolve(); root.mkdir(parents=True, exist_ok=True)
    client = Client(args.delay, args.retries, root / ".cache", args.user_agent)
    selected: list[dict[str, Any]] = []
    ids = [x.strip() for x in args.problem_ids.split(",") if x.strip()] if args.problem_ids else candidate_ids()
    for problem_id in ids:
        if len(selected) >= args.problem_limit: break
        try:
            desc = client.get(f"{API}/resources/descriptions/en/{quote(problem_id)}")
        except Exception as exc:
            if args.verbose: print(f"skip {problem_id}: {exc}", file=sys.stderr)
            continue
        score = topic_score(desc)
        if score < args.min_topic_score: continue
        candidates: list[dict[str, Any]] = []
        for lang in args.languages.split(","):
            url = f"{API}/solutions/problems/{quote(problem_id)}/lang/{quote(lang.strip())}/rating?page=0&size={args.solution_scan}"
            try: candidates.extend(records(client.get(url)))
            except Exception: continue
        problem_dir = root / "problems" / problem_id
        solutions_dir = problem_dir / "solutions"; solutions_dir.mkdir(parents=True, exist_ok=True)
        kept, seen = [], set()
        for item in candidates:
            if len(kept) >= args.solutions_per_problem: break
            if str(item.get("policy", "public")).lower() == "private": continue
            judge_id = item.get("judgeId") or item.get("id") or item.get("submissionId")
            if judge_id is None: continue
            try: source = source_from_review(client.get(f"{API}/reviews/{quote(str(judge_id))}"))
            except Exception: continue
            digest = hashlib.sha256(re.sub(r"\s+", "", source).encode()).hexdigest()
            if not source or digest in seen: continue
            report = compatibility(source)
            if not report.accepted: continue
            seen.add(digest)
            path = solutions_dir / f"{judge_id}.c"; path.write_text(source, encoding="utf-8")
            kept.append({"judge_id": judge_id, "language": item.get("language"), "user_id": item.get("userId"),
                         "sha256": digest, "compatibility": asdict(report),
                         "source_url": f"https://onlinejudge.u-aizu.ac.jp/solutions/problem/{problem_id}/review/{judge_id}"})
        if len(kept) < args.solutions_per_problem:
            shutil.rmtree(problem_dir, ignore_errors=True); continue
        (problem_dir / "description.json").write_text(json.dumps(desc, ensure_ascii=False, indent=2), encoding="utf-8")
        header = client.get(f"{DATA}/testcases/{quote(problem_id)}/header")
        count = test_count(header)
        limit = count if args.max_system_tests == 0 else min(count, args.max_system_tests)
        tests_dir = problem_dir / "tests"; tests_dir.mkdir(exist_ok=True)
        tests: list[tuple[Path, Path]] = []
        for serial in range(1, limit + 1):
            value = client.get(f"{DATA}/testcases/{quote(problem_id)}/{serial}")
            inp, out = test_io(value)
            ip, op = tests_dir / f"{serial:03d}.in", tests_dir / f"{serial:03d}.out"
            ip.write_text(inp, encoding="utf-8"); op.write_text(out, encoding="utf-8"); tests.append((ip, op))
        if args.verify:
            for solution in kept:
                solution["verification"] = compile_and_verify(solutions_dir / f"{solution['judge_id']}.c", tests, args.timeout)
        metadata = {"problem_id": problem_id, "topic_score": score, "official_test_count": count,
                    "downloaded_test_count": limit, "solutions": kept,
                    "description_url": f"https://onlinejudge.u-aizu.ac.jp/problems/{problem_id}"}
        (problem_dir / "metadata.json").write_text(json.dumps(metadata, ensure_ascii=False, indent=2), encoding="utf-8")
        selected.append(metadata); print(f"[{len(selected)}/{args.problem_limit}] {problem_id}: {len(kept)} solutions, {limit}/{count} tests")
    summary = {"site": "Aizu Online Judge", "created_at": time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime()),
               "requested_problems": args.problem_limit, "collected_problems": len(selected), "problems": selected}
    (root / "manifest.json").write_text(json.dumps(summary, ensure_ascii=False, indent=2), encoding="utf-8")
    return 0 if len(selected) == args.problem_limit else 2


def parser() -> argparse.ArgumentParser:
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--output", type=Path, default=Path("testcase/aoj_eppather_dataset"))
    p.add_argument("--problem-limit", type=int, default=100)
    p.add_argument("--problem-ids", default="", help="comma-separated IDs; useful for a smoke test")
    p.add_argument("--solutions-per-problem", type=int, default=10)
    p.add_argument("--solution-scan", type=int, default=100)
    p.add_argument("--languages", default="C,C11,C99")
    p.add_argument("--min-topic-score", type=int, default=3)
    p.add_argument("--max-system-tests", type=int, default=20, help="0 downloads every official test")
    p.add_argument("--verify", action="store_true", help="compile and replay downloaded tests")
    p.add_argument("--timeout", type=float, default=3.0)
    p.add_argument("--delay", type=float, default=1.0)
    p.add_argument("--retries", type=int, default=4)
    p.add_argument("--user-agent", default="eppather-dataset-research/1.0 (public AOJ data; serial requests)")
    p.add_argument("--verbose", action="store_true")
    return p


if __name__ == "__main__":
    raise SystemExit(collect(parser().parse_args()))
