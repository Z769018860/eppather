#!/usr/bin/env python3
import argparse
import csv
import os
import re
import shutil
import subprocess
import sys
import time
from dataclasses import dataclass
from pathlib import Path
from typing import Dict, Iterable, List, Optional, Set, Tuple

C_PRELUDE = r"""
#ifndef NULL
#define NULL ((void*)0)
#endif

#ifndef EOF
#define EOF (-1)
#endif

#ifndef SIZE_MAX
#define SIZE_MAX ((size_t)-1)
#endif

#ifndef CHAR_BIT
#define CHAR_BIT 8
#endif

#ifndef LONG_MAX
#define LONG_MAX 9223372036854775807L
#endif

#ifndef LLONG_MAX
#define LLONG_MAX 9223372036854775807LL
#endif

#define __attribute__(x)
#define __declspec(x)
#define __cdecl
#define __stdcall
#define __inline
#define __inline__
#define __restrict
#define __restrict__
#define restrict
#define _Noreturn
#define _Static_assert(cond,msg)
#define static_assert(cond,msg)
#define assert(x) ((void)0)

typedef unsigned long size_t;
typedef long ssize_t;
typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef int int32_t;
typedef unsigned int uint32_t;
typedef long long int64_t;
typedef unsigned long long uint64_t;
typedef long intptr_t;
typedef unsigned long uintptr_t;

typedef struct _EPPATHER_FILE FILE;

void *malloc(size_t size);
void free(void *ptr);
void *realloc(void *ptr, size_t size);
void *calloc(size_t n, size_t size);

void *memcpy(void *dest, const void *src, size_t n);
void *memmove(void *dest, const void *src, size_t n);
void *memset(void *s, int c, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);

size_t strlen(const char *s);
int strcmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2, size_t n);
char *strchr(const char *s, int c);
char *strrchr(const char *s, int c);
char *strstr(const char *haystack, const char *needle);
char *strncpy(char *dest, const char *src, size_t n);
char *strcpy(char *dest, const char *src);

int sprintf(char *str, const char *format, ...);
int snprintf(char *str, size_t size, const char *format, ...);
int printf(const char *format, ...);
int fprintf(FILE *stream, const char *format, ...);
int fputc(int c, FILE *stream);
FILE *fopen(const char *filename, const char *mode);
int fclose(FILE *stream);
int fseek(FILE *stream, long offset, int whence);
long ftell(FILE *stream);
void rewind(FILE *stream);
size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
int ferror(FILE *stream);
char *fgets(char *str, int num, void *stream);

int isspace(int c);
int isalpha(int c);
int isdigit(int c);
int isalnum(int c);
int isxdigit(int c);
int tolower(int c);
int toupper(int c);

double strtod(const char *nptr, char **endptr);
"""

@dataclass
class ProjectSpec:
    name: str
    marker_files: List[str]
    headers: List[str]
    sources: List[str]
    safe_entries: List[str]
    core_entries: List[str]
    full_entries: List[str]
    preferred_dirs: List[str]

@dataclass
class FunctionDef:
    name: str
    text: str
    start: int
    end: int
    signature: str
    body: str

PROJECTS: Dict[str, ProjectSpec] = {
    "list": ProjectSpec(
        name="list",
        marker_files=["src/list.c", "src/list.h", "list.c", "list.h"],
        headers=["src/list.h", "list.h"],
        sources=["src/list.c", "list.c"],
        safe_entries=[
            "list_rpush",
            "list_lpush",
            "list_rpop",
            "list_lpop",
            "list_remove"
        ],
        core_entries=[
            "list_rpush",
            "list_lpush",
            "list_rpop",
            "list_lpop",
            "list_remove",
            "list_new"
        ],
        full_entries=[
            "list_new",
            "list_destroy",
            "list_rpush",
            "list_lpush",
            "list_rpop",
            "list_lpop",
            "list_find",
            "list_at",
            "list_remove"
        ],
        preferred_dirs=["clib", "list", "clibs-list", "list-master"]
    ),
    "inih": ProjectSpec(
        name="inih",
        marker_files=["ini.c", "ini.h"],
        headers=["ini.h"],
        sources=["ini.c"],
        safe_entries=[
            "ini_rstrip",
            "ini_lskip",
            "ini_find_chars_or_comment",
            "ini_strncpy0",
            "ini_reader_string"
        ],
        core_entries=[
            "ini_rstrip",
            "ini_lskip",
            "ini_find_chars_or_comment",
            "ini_strncpy0",
            "ini_reader_string",
            "ini_parse_string_length"
        ],
        full_entries=[
            "ini_rstrip",
            "ini_lskip",
            "ini_find_chars_or_comment",
            "ini_strncpy0",
            "ini_parse_stream",
            "ini_parse_file",
            "ini_parse",
            "ini_reader_string",
            "ini_parse_string",
            "ini_parse_string_length"
        ],
        preferred_dirs=["inih"]
    ),
    "sds": ProjectSpec(
        name="sds",
        marker_files=["sds.c", "sds.h"],
        headers=["sdsalloc.h", "sds.h"],
        sources=["sds.c"],
        safe_entries=[
            "sdsReqType",
            "sdsclear",
            "sdsupdatelen"
        ],
        core_entries=[
            "sdsReqType",
            "sdsempty",
            "sdsnew",
            "sdsdup",
            "sdsfree",
            "sdsupdatelen",
            "sdsclear",
            "sdsAllocSize",
            "sdsAllocPtr"
        ],
        full_entries=[
            "sdsHdrSize",
            "sdsReqType",
            "sdsnewlen",
            "sdsempty",
            "sdsnew",
            "sdsdup",
            "sdsfree",
            "sdsupdatelen",
            "sdsclear",
            "sdsMakeRoomFor",
            "sdsRemoveFreeSpace",
            "sdsAllocSize",
            "sdsAllocPtr"
        ],
        preferred_dirs=["sds"]
    )
}

KEYWORDS = {
    "if", "while", "for", "switch", "return", "sizeof", "case", "do",
    "else", "goto", "typedef", "struct", "union", "enum", "static",
    "inline", "extern"
}

def log(msg: str) -> None:
    print(msg, flush=True)

def find_repo_root(start: Optional[Path] = None) -> Path:
    candidates = []
    if start:
        candidates.append(start.resolve())
    candidates.append(Path.cwd().resolve())
    try:
        candidates.append(Path(__file__).resolve().parent)
    except NameError:
        pass
    seen = set()
    expanded = []
    for p in candidates:
        for q in [p] + list(p.parents):
            if q not in seen:
                seen.add(q)
                expanded.append(q)
    for p in expanded:
        if (p / "CMakeLists.txt").exists() and (p / "testcase").exists():
            return p
    return Path.cwd().resolve()

def find_cnip(root: Path, explicit: Optional[str]) -> Path:
    if explicit:
        p = Path(explicit).expanduser()
        if not p.is_absolute():
            p = root / p
        p = p.resolve()
        if p.exists():
            return p
        raise FileNotFoundError(f"cnip not found: {p}")
    candidates = [
        root / "build" / "cnip",
        root / "build_local" / "cnip",
        root / "cmake-build-debug" / "cnip",
        root / "cnip"
    ]
    for p in candidates:
        if p.exists() and os.access(p, os.X_OK):
            return p.resolve()
    found = shutil.which("cnip")
    if found:
        return Path(found).resolve()
    raise FileNotFoundError("cnip not found. Build first or pass --cnip build/cnip")

def strip_includes_and_pragmas(text: str) -> str:
    out = []
    for line in text.splitlines():
        if re.match(r"^\s*#\s*include\s+[<\"].*[>\"]", line):
            continue
        if re.match(r"^\s*pragma\b", line):
            continue
        if re.match(r"^\s*#\s*pragma\b", line):
            continue
        out.append(line)
    return "\n".join(out) + "\n"

def candidate_project_dirs(testcase: Path, spec: ProjectSpec) -> List[Path]:
    dirs = []
    for name in spec.preferred_dirs:
        p = testcase / name
        if p.exists():
            dirs.append(p)
    for p in testcase.iterdir() if testcase.exists() else []:
        if p.is_dir() and not p.name.startswith("_") and p not in dirs:
            dirs.append(p)
    return dirs

def has_any_marker(root: Path, spec: ProjectSpec) -> bool:
    for rel in spec.marker_files:
        if (root / rel).exists():
            return True
    return False

def locate_project_root(testcase: Path, spec: ProjectSpec) -> Optional[Path]:
    for p in candidate_project_dirs(testcase, spec):
        if has_any_marker(p, spec):
            return p
    return None

def first_existing(root: Path, rels: Iterable[str]) -> Optional[Path]:
    for rel in rels:
        p = root / rel
        if p.exists():
            return p
    return None

def read_existing_files(project_root: Path, rels: List[str]) -> List[Tuple[str, str]]:
    files = []
    used = set()
    for rel in rels:
        p = project_root / rel
        if p.exists() and p not in used:
            used.add(p)
            files.append((rel, p.read_text(encoding="utf-8", errors="ignore")))
    return files

def build_flat_source(project_root: Path, spec: ProjectSpec, source_rel: str) -> str:
    pieces = [C_PRELUDE]
    for rel, text in read_existing_files(project_root, spec.headers):
        pieces.append(f"\n/* ===== BEGIN HEADER {rel} ===== */\n")
        pieces.append(strip_includes_and_pragmas(text))
        pieces.append(f"\n/* ===== END HEADER {rel} ===== */\n")
    src_path = project_root / source_rel
    source_text = src_path.read_text(encoding="utf-8", errors="ignore")
    pieces.append(f"\n/* ===== BEGIN SOURCE {source_rel} ===== */\n")
    pieces.append(strip_includes_and_pragmas(source_text))
    pieces.append(f"\n/* ===== END SOURCE {source_rel} ===== */\n")
    return "\n".join(pieces)

def mask_comments_and_strings(text: str) -> str:
    chars = list(text)
    i = 0
    n = len(chars)
    state = "normal"
    while i < n:
        c = chars[i]
        if state == "normal":
            if c == "/" and i + 1 < n and chars[i + 1] == "/":
                chars[i] = " "
                chars[i + 1] = " "
                i += 2
                state = "line_comment"
                continue
            if c == "/" and i + 1 < n and chars[i + 1] == "*":
                chars[i] = " "
                chars[i + 1] = " "
                i += 2
                state = "block_comment"
                continue
            if c == '"':
                chars[i] = " "
                i += 1
                state = "string"
                continue
            if c == "'":
                chars[i] = " "
                i += 1
                state = "char"
                continue
        elif state == "line_comment":
            if c == "\n":
                state = "normal"
            else:
                chars[i] = " "
        elif state == "block_comment":
            if c == "*" and i + 1 < n and chars[i + 1] == "/":
                chars[i] = " "
                chars[i + 1] = " "
                i += 2
                state = "normal"
                continue
            if c != "\n":
                chars[i] = " "
        elif state == "string":
            if c == "\\" and i + 1 < n:
                chars[i] = " "
                chars[i + 1] = " "
                i += 2
                continue
            if c == '"':
                state = "normal"
            chars[i] = " "
        elif state == "char":
            if c == "\\" and i + 1 < n:
                chars[i] = " "
                chars[i + 1] = " "
                i += 2
                continue
            if c == "'":
                state = "normal"
            chars[i] = " "
        i += 1
    return "".join(chars)

def matching_brace(masked: str, open_pos: int) -> int:
    depth = 0
    for i in range(open_pos, len(masked)):
        if masked[i] == "{":
            depth += 1
        elif masked[i] == "}":
            depth -= 1
            if depth == 0:
                return i
    return -1

def find_signature_start(text: str, brace_pos: int) -> int:
    i = brace_pos - 1
    paren = 0
    while i >= 0:
        c = text[i]
        if c == ")":
            paren += 1
        elif c == "(":
            paren -= 1
        if paren < 0:
            break
        i -= 1
    line_start = text.rfind("\n", 0, i + 1) + 1
    semi = text.rfind(";", 0, brace_pos)
    close = text.rfind("}", 0, brace_pos)
    hash_line = text.rfind("\n#", 0, brace_pos)
    start = max(line_start, semi + 1, close + 1, hash_line + 2)
    while start < brace_pos and text[start].isspace():
        start += 1
    return start

def function_name_from_signature(signature: str) -> Optional[str]:
    sig = re.sub(r"/\*.*?\*/", " ", signature, flags=re.S)
    sig = re.sub(r"//.*", " ", sig)
    sig = " ".join(sig.split())
    if not sig or sig.startswith("#"):
        return None
    m = re.search(r"([A-Za-z_][A-Za-z0-9_]*)\s*\([^;{}]*\)\s*$", sig)
    if not m:
        return None
    name = m.group(1)
    if name in KEYWORDS:
        return None
    before = sig[:m.start(1)]
    if "typedef" in before.split():
        return None
    return name

def extract_functions(text: str) -> Tuple[Dict[str, FunctionDef], str]:
    masked = mask_comments_and_strings(text)
    funcs: Dict[str, FunctionDef] = {}
    spans: List[Tuple[int, int]] = []
    i = 0
    while i < len(masked):
        if masked[i] != "{":
            i += 1
            continue
        start = find_signature_start(text, i)
        signature = text[start:i].strip()
        name = function_name_from_signature(signature)
        if not name:
            i += 1
            continue
        end = matching_brace(masked, i)
        if end < 0:
            i += 1
            continue
        full = text[start:end + 1]
        body = text[i + 1:end]
        funcs[name] = FunctionDef(name=name, text=full, start=start, end=end + 1, signature=signature, body=body)
        spans.append((start, end + 1))
        i = end + 1
    if not spans:
        return funcs, text
    parts = []
    last = 0
    for start, end in sorted(spans):
        parts.append(text[last:start])
        last = end
    parts.append(text[last:])
    preamble = "".join(parts)
    return funcs, preamble

def extract_direct_calls(body: str, known: Set[str]) -> Set[str]:
    masked = mask_comments_and_strings(body)
    calls = set()
    for m in re.finditer(r"\b([A-Za-z_][A-Za-z0-9_]*)\s*\(", masked):
        name = m.group(1)
        if name in known and name not in KEYWORDS:
            calls.add(name)
    return calls

def closure_for_entry(entry: str, funcs: Dict[str, FunctionDef], max_depth: int) -> List[str]:
    if entry not in funcs:
        return []
    known = set(funcs)
    result = []
    seen = set()
    def visit(name: str, depth: int) -> None:
        if name in seen or name not in funcs:
            return
        seen.add(name)
        if depth > max_depth:
            return
        result.append(name)
        for callee in sorted(extract_direct_calls(funcs[name].body, known)):
            if callee != name:
                visit(callee, depth + 1)
    visit(entry, 0)
    return result

def filter_preamble(preamble: str) -> str:
    lines = []
    for line in preamble.splitlines():
        if re.match(r"^\s*#\s*line\b", line):
            continue
        if "__BEGIN_DECLS" in line or "__END_DECLS" in line:
            continue
        lines.append(line)
    return "\n".join(lines) + "\n"

def make_slice_source(preamble: str, funcs: Dict[str, FunctionDef], names: List[str], entry: str) -> str:
    out = []
    out.append("/* Generated by run_small_project_summaries.py */\n")
    out.append(f"/* EPPATHER_ENTRY={entry} */\n")
    out.append(filter_preamble(preamble))
    for name in names:
        if name in funcs:
            out.append("\n/* ===== FUNCTION " + name + " ===== */\n")
            out.append(funcs[name].text)
            out.append("\n")
    return "\n".join(out)

def mode_to_flag(mode: str) -> str:
    table = {
        "summary": "-s",
        "cfg": "-c",
        "dfs2": "-q",
        "dfs": "-f",
        "dp": "-g"
    }
    if mode not in table:
        raise ValueError(f"unknown mode: {mode}")
    return table[mode]

def run_cmd(cmd: List[str], env: Dict[str, str], timeout: int) -> Tuple[int, bool, str, float]:
    start = time.time()
    try:
        proc = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, env=env, timeout=timeout)
        elapsed = time.time() - start
        return proc.returncode, False, proc.stdout + proc.stderr, elapsed
    except subprocess.TimeoutExpired as exc:
        elapsed = time.time() - start
        text = (exc.stdout or "") + (exc.stderr or "")
        text += "\n[TIMEOUT]\n"
        return 124, True, text, elapsed

def extract_metric(pattern: str, text: str) -> str:
    m = re.search(pattern, text, re.MULTILINE)
    return m.group(1).strip() if m else ""

def extract_metrics(text: str, entry: str) -> Dict[str, str]:
    metrics = {
        "has_function_summaries": "true" if "[FUNCTION SUMMARIES]" in text else "false",
        "has_program_summary": "true" if "[PROGRAM SUMMARY]" in text else "false",
        "entry_seen": "true" if f"Function {entry}:" in text else "false",
        "worst_mems": extract_metric(r"^worst_mems=(.*)$", text),
        "weighted_avg_mems": extract_metric(r"^weighted_avg_mems=(.*)$", text),
        "function_count": extract_metric(r"^function_count=(.*)$", text),
        "summary_case_count": extract_metric(r"^summary_case_count=(.*)$", text),
        "call_edge_count": extract_metric(r"^call_edge_count=(.*)$", text),
        "reason": extract_metric(r"^reason=(.*)$", text),
        "notes": extract_metric(r"^notes=(.*)$", text),
        "dfs_time": extract_metric(r"^\[DFS TIME COST\]:\s*(.*)$", text),
        "dp_time": extract_metric(r"^\[DP TIME COST\]:\s*(.*)$", text),
        "mems": extract_metric(r"^MEMS:\s*(.*)$", text),
    }
    worst = metrics.get("worst_mems", "")
    metrics["summary_ok"] = "true" if metrics["has_function_summaries"] == "true" and worst and worst != "N/A" else "false"
    return metrics

def run_cnip(cnip: Path, cfile: Path, mode: str, entry: str, maxloop: int, maxpaths: int, timeout: int, out_log: Path, crash_trace: bool) -> Dict[str, str]:
    env = os.environ.copy()
    env["EPPATHER_ENTRY"] = entry
    if crash_trace:
        env["EPPATHER_DEBUG_CRASH_TRACE"] = "1"
    cmd = [
        str(cnip),
        mode_to_flag(mode),
        "--maxloop",
        str(maxloop),
        "--maxpaths",
        str(maxpaths),
        str(cfile)
    ]
    rc, timed_out, text, elapsed = run_cmd(cmd, env, timeout)
    out_log.parent.mkdir(parents=True, exist_ok=True)
    out_log.write_text(text, encoding="utf-8", errors="ignore")
    metrics = extract_metrics(text, entry)
    metrics.update({
        "entry": entry,
        "mode": mode,
        "returncode": str(rc),
        "timeout": "true" if timed_out else "false",
        "seconds": f"{elapsed:.6f}",
        "log": str(out_log),
        "cmd": " ".join(cmd)
    })
    return metrics

def write_csv(path: Path, rows: List[Dict[str, str]]) -> None:
    fields = [
        "project", "project_root", "source", "slice_mode", "slice_file",
        "entry", "mode", "returncode", "timeout", "seconds",
        "summary_ok", "has_function_summaries", "has_program_summary", "entry_seen",
        "worst_mems", "weighted_avg_mems", "function_count", "summary_case_count",
        "call_edge_count", "mems", "dfs_time", "dp_time", "reason", "notes", "log", "cmd"
    ]
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", newline="", encoding="utf-8") as f:
        writer = csv.DictWriter(f, fieldnames=fields)
        writer.writeheader()
        for row in rows:
            writer.writerow({k: row.get(k, "") for k in fields})

def parse_list(value: str) -> List[str]:
    return [x.strip() for x in value.split(",") if x.strip()]

def select_entries(spec: ProjectSpec, entry_set: str, custom_entries: Optional[List[str]]) -> List[str]:
    if custom_entries:
        return custom_entries
    if entry_set == "safe":
        return spec.safe_entries
    if entry_set == "core":
        return spec.core_entries
    if entry_set == "full":
        return spec.full_entries
    raise ValueError(entry_set)

def prepare_project(root: Path, testcase: Path, spec: ProjectSpec, out_root: Path, max_closure_depth: int) -> Tuple[Optional[Path], List[Path], Dict[Path, Tuple[Dict[str, FunctionDef], str]]]:
    project_root = locate_project_root(testcase, spec)
    if project_root is None:
        log(f"[SKIP] {spec.name}: project folder not found under {testcase}")
        return None, [], {}
    source_paths = []
    for rel in spec.sources:
        p = project_root / rel
        if p.exists():
            source_paths.append(p)
    if not source_paths:
        log(f"[SKIP] {spec.name}: source not found")
        return project_root, [], {}
    parsed: Dict[Path, Tuple[Dict[str, FunctionDef], str]] = {}
    project_out = out_root / spec.name
    project_out.mkdir(parents=True, exist_ok=True)
    for src_path in source_paths:
        rel = str(src_path.relative_to(project_root))
        flat = build_flat_source(project_root, spec, rel)
        flat_path = project_out / f"{spec.name}_{src_path.stem}_flat.c"
        flat_path.write_text(flat, encoding="utf-8")
        funcs, preamble = extract_functions(flat)
        parsed[flat_path] = (funcs, preamble)
        log(f"[OK] flattened: {flat_path} functions={len(funcs)}")
    return project_root, list(parsed.keys()), parsed

def build_slice_files(project_out: Path, spec: ProjectSpec, flat_path: Path, funcs: Dict[str, FunctionDef], preamble: str, entry: str, max_closure_depth: int) -> List[Tuple[str, Path]]:
    slices_dir = project_out / "slices"
    slices_dir.mkdir(parents=True, exist_ok=True)
    result: List[Tuple[str, Path]] = []
    if entry not in funcs:
        return result
    closure = closure_for_entry(entry, funcs, max_closure_depth)
    if not closure:
        closure = [entry]
    closure_path = slices_dir / f"{flat_path.stem}__{entry}__closure.c"
    closure_path.write_text(make_slice_source(preamble, funcs, closure, entry), encoding="utf-8")
    result.append(("closure", closure_path))
    if closure != [entry]:
        entry_path = slices_dir / f"{flat_path.stem}__{entry}__entry_only.c"
        entry_path.write_text(make_slice_source(preamble, funcs, [entry], entry), encoding="utf-8")
        result.append(("entry_only", entry_path))
    return result

def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--root", default="")
    ap.add_argument("--testcase", default="")
    ap.add_argument("--cnip", default="")
    ap.add_argument("--projects", default="list,inih,sds")
    ap.add_argument("--entries", default="")
    ap.add_argument("--entry-set", choices=["safe", "core", "full"], default="safe")
    ap.add_argument("--modes", default="summary")
    ap.add_argument("--maxloop", type=int, default=2)
    ap.add_argument("--maxpaths", type=int, default=80)
    ap.add_argument("--timeout", type=int, default=120)
    ap.add_argument("--max-closure-depth", type=int, default=2)
    ap.add_argument("--only-preprocess", action="store_true")
    ap.add_argument("--try-entry-only-on-fail", action="store_true", default=True)
    ap.add_argument("--no-entry-only-on-fail", dest="try_entry_only_on_fail", action="store_false")
    ap.add_argument("--crash-trace", action="store_true")
    args = ap.parse_args()

    root = find_repo_root(Path(args.root) if args.root else None)
    testcase = Path(args.testcase).expanduser().resolve() if args.testcase else (root / "testcase")
    cnip = None if args.only_preprocess else find_cnip(root, args.cnip or None)
    project_names = parse_list(args.projects)
    modes = parse_list(args.modes)
    custom_entries = parse_list(args.entries) if args.entries else None

    timestamp = time.strftime("%Y%m%d_%H%M%S")
    pp_root = testcase / "_eppather_preprocessed"
    run_root = testcase / "_eppather_runs" / timestamp
    rows: List[Dict[str, str]] = []

    log(f"[ROOT] {root}")
    log(f"[TESTCASE] {testcase}")
    if cnip:
        log(f"[CNIP] {cnip}")

    for project_name in project_names:
        if project_name not in PROJECTS:
            log(f"[SKIP] unknown project: {project_name}")
            continue
        spec = PROJECTS[project_name]
        project_root, flat_paths, parsed = prepare_project(root, testcase, spec, pp_root, args.max_closure_depth)
        if project_root is None or not flat_paths:
            continue
        if args.only_preprocess:
            continue

        selected = select_entries(spec, args.entry_set, custom_entries)
        project_out = pp_root / spec.name
        for flat_path in flat_paths:
            funcs, preamble = parsed[flat_path]
            available = [e for e in selected if e in funcs]
            missing = [e for e in selected if e not in funcs]
            if missing:
                log(f"[WARN] {spec.name}: missing entries in {flat_path.name}: {','.join(missing)}")
            for entry in available:
                slice_files = build_slice_files(project_out, spec, flat_path, funcs, preamble, entry, args.max_closure_depth)
                if not slice_files:
                    continue
                for mode in modes:
                    tried_entry_only = False
                    for idx, (slice_mode, slice_path) in enumerate(slice_files):
                        if idx > 0 and not tried_entry_only:
                            break
                        log_name = f"{spec.name}_{flat_path.stem}_{entry}_{mode}_{slice_mode}.log"
                        log_path = run_root / spec.name / log_name
                        log(f"[RUN] project={spec.name} entry={entry} mode={mode} slice={slice_mode}")
                        row = run_cnip(cnip, slice_path, mode, entry, args.maxloop, args.maxpaths, args.timeout, log_path, args.crash_trace)
                        row.update({
                            "project": spec.name,
                            "project_root": str(project_root),
                            "source": str(flat_path),
                            "slice_mode": slice_mode,
                            "slice_file": str(slice_path)
                        })
                        rows.append(row)
                        ok = row.get("summary_ok") == "true" if mode == "summary" else row.get("returncode") == "0"
                        log(f"[{'OK' if ok else 'FAIL'}] rc={row['returncode']} summary_ok={row.get('summary_ok','')} worst_mems={row.get('worst_mems','')} log={log_path}")
                        if ok:
                            break
                        if idx == 0 and args.try_entry_only_on_fail and len(slice_files) > 1:
                            tried_entry_only = True
                            continue
                        break

    if rows:
        summary_csv = run_root / "run_summary.csv"
        write_csv(summary_csv, rows)
        log(f"[SUMMARY] {summary_csv}")
    return 0

if __name__ == "__main__":
    raise SystemExit(main())
