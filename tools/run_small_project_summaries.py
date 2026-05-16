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
from typing import Dict, List, Optional, Set, Tuple

@dataclass
class ProjectSpec:
    name: str
    source_markers: List[str]
    header_markers: List[str]
    headers: List[str]
    sources: List[str]
    core_entries: List[str]
    full_entries: List[str]
    risky_entries: Set[str]

C_PRELUDE = r'''
#ifndef NULL
#define NULL ((void*)0)
#endif
#ifndef EOF
#define EOF (-1)
#endif
#ifndef SIZE_MAX
#define SIZE_MAX ((size_t)-1)
#endif
#ifndef LONG_MAX
#define LONG_MAX 9223372036854775807L
#endif
#ifndef LLONG_MAX
#define LLONG_MAX 9223372036854775807LL
#endif
#ifndef LLONG_MIN
#define LLONG_MIN (-9223372036854775807LL - 1LL)
#endif
#ifndef ULLONG_MAX
#define ULLONG_MAX 18446744073709551615ULL
#endif
#ifndef CHAR_BIT
#define CHAR_BIT 8
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
#define _Static_assert(x, y)
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
typedef struct _IO_FILE FILE;
typedef long ptrdiff_t;
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
char *fgets(char *str, int num, FILE *stream);
int isspace(int c);
int isalpha(int c);
int isdigit(int c);
int isalnum(int c);
int isxdigit(int c);
int tolower(int c);
int toupper(int c);
double strtod(const char *nptr, char **endptr);
int vsnprintf(char *str, size_t size, const char *format, void *ap);
'''

PROJECTS: Dict[str, ProjectSpec] = {
    "list": ProjectSpec(
        name="list",
        source_markers=["src/list.c"],
        header_markers=["src/list.h"],
        headers=["src/list.h"],
        sources=["src/list.c"],
        core_entries=["list_new", "list_rpush", "list_lpush", "list_rpop", "list_lpop", "list_at", "list_remove"],
        full_entries=["list_new", "list_destroy", "list_rpush", "list_lpush", "list_rpop", "list_lpop", "list_find", "list_at", "list_remove"],
        risky_entries={"list_destroy", "list_find"}
    ),
    "inih": ProjectSpec(
        name="inih",
        source_markers=["ini.c"],
        header_markers=["ini.h"],
        headers=["ini.h"],
        sources=["ini.c"],
        core_entries=["ini_rstrip", "ini_lskip", "ini_find_chars_or_comment", "ini_strncpy0", "ini_reader_string"],
        full_entries=["ini_rstrip", "ini_lskip", "ini_find_chars_or_comment", "ini_strncpy0", "ini_reader_string", "ini_parse_string_length", "ini_parse_string", "ini_parse", "ini_parse_file", "ini_parse_stream"],
        risky_entries={"ini_parse_stream", "ini_parse_file", "ini_parse", "ini_parse_string", "ini_parse_string_length"}
    ),
    "sds": ProjectSpec(
        name="sds",
        source_markers=["sds.c"],
        header_markers=["sds.h"],
        headers=["sdsalloc.h", "sds.h"],
        sources=["sds.c"],
        core_entries=["sdsHdrSize", "sdsReqType", "sdsnewlen", "sdsempty", "sdsnew", "sdsdup", "sdsfree", "sdsupdatelen", "sdsclear", "sdsAllocSize", "sdsAllocPtr"],
        full_entries=["sdsHdrSize", "sdsReqType", "sdsnewlen", "sdsempty", "sdsnew", "sdsdup", "sdsfree", "sdsupdatelen", "sdsclear", "sdsMakeRoomFor", "sdsRemoveFreeSpace", "sdsAllocSize", "sdsAllocPtr"],
        risky_entries={"sdsMakeRoomFor", "sdsRemoveFreeSpace"}
    )
}

KEYWORDS = {
    "if", "for", "while", "switch", "return", "sizeof", "case", "do", "else", "goto",
    "typedef", "struct", "union", "enum", "static", "extern", "inline", "const", "volatile"
}

EXTERNAL_NAMES = {
    "malloc", "free", "realloc", "calloc", "memcpy", "memmove", "memset", "memcmp", "strlen",
    "strcmp", "strncmp", "strchr", "strrchr", "strstr", "strncpy", "strcpy", "sprintf", "snprintf",
    "printf", "fprintf", "fputc", "fopen", "fclose", "fseek", "ftell", "rewind", "fread", "ferror",
    "fgets", "isspace", "isalpha", "isdigit", "isalnum", "isxdigit", "tolower", "toupper", "strtod",
    "assert", "vsnprintf"
}

@dataclass
class FunctionDef:
    name: str
    start: int
    end: int
    text: str
    signature: str
    body: str


def find_repo_root() -> Path:
    p = Path.cwd().resolve()
    for cand in [p] + list(p.parents):
        if (cand / "CMakeLists.txt").exists() and (cand / "testcase").exists():
            return cand
    return p


def find_cnip(root: Path, explicit: str) -> Path:
    if explicit:
        p = Path(explicit).expanduser().resolve()
        if p.exists():
            return p
        raise FileNotFoundError(str(p))
    for rel in ["build/cnip", "build_local/cnip", "build-release/cnip", "cnip"]:
        p = root / rel
        if p.exists() and os.access(p, os.X_OK):
            return p
    found = shutil.which("cnip")
    if found:
        return Path(found)
    raise FileNotFoundError("cnip not found; pass --cnip /path/to/cnip")


def normalize_rel(path: Path) -> str:
    return str(path).replace(os.sep, "/")


def locate_project_root(testcase: Path, spec: ProjectSpec) -> Optional[Path]:
    direct = testcase / spec.name
    if direct.exists():
        return direct
    for c in testcase.iterdir() if testcase.exists() else []:
        if not c.is_dir() or c.name.startswith("_"):
            continue
        ok = True
        for marker in spec.source_markers + spec.header_markers:
            if not (c / marker).exists():
                ok = False
                break
        if ok:
            return c
    for marker in spec.source_markers:
        hits = list(testcase.rglob(Path(marker).name)) if testcase.exists() else []
        for hit in hits:
            rel = normalize_rel(hit.relative_to(hit.parents[len(Path(marker).parts) - 1])) if len(hit.parents) else hit.name
            parts = Path(marker).parts
            candidate = hit
            for _ in parts:
                candidate = candidate.parent
            if all((candidate / m).exists() for m in spec.source_markers + spec.header_markers):
                return candidate
    return None


def read_text(path: Path) -> str:
    return path.read_text(encoding="utf-8", errors="ignore")


def strip_includes_pragmas_and_line_directives(text: str) -> str:
    out = []
    for line in text.splitlines():
        if re.match(r"^\s*#\s*include\s+[<\"].*[>\"]", line):
            continue
        if re.match(r"^\s*#\s*pragma\b", line):
            continue
        if re.match(r"^\s*#\s*line\b", line):
            continue
        out.append(line)
    return "\n".join(out) + "\n"


def strip_comments(text: str) -> str:
    res = []
    i = 0
    n = len(text)
    state = "code"
    while i < n:
        c = text[i]
        d = text[i + 1] if i + 1 < n else ""
        if state == "code":
            if c == '"':
                state = "str"
                res.append(c)
                i += 1
            elif c == "'":
                state = "char"
                res.append(c)
                i += 1
            elif c == "/" and d == "/":
                while i < n and text[i] != "\n":
                    i += 1
                res.append("\n")
            elif c == "/" and d == "*":
                i += 2
                while i + 1 < n and not (text[i] == "*" and text[i + 1] == "/"):
                    res.append("\n" if text[i] == "\n" else " ")
                    i += 1
                i += 2
            else:
                res.append(c)
                i += 1
        elif state == "str":
            res.append(c)
            if c == "\\" and i + 1 < n:
                res.append(text[i + 1])
                i += 2
            elif c == '"':
                state = "code"
                i += 1
            else:
                i += 1
        elif state == "char":
            res.append(c)
            if c == "\\" and i + 1 < n:
                res.append(text[i + 1])
                i += 2
            elif c == "'":
                state = "code"
                i += 1
            else:
                i += 1
    return "".join(res)


def find_matching(text: str, open_pos: int, open_ch: str, close_ch: str) -> int:
    depth = 0
    i = open_pos
    n = len(text)
    state = "code"
    while i < n:
        c = text[i]
        if state == "code":
            if c == '"':
                state = "str"
            elif c == "'":
                state = "char"
            elif c == open_ch:
                depth += 1
            elif c == close_ch:
                depth -= 1
                if depth == 0:
                    return i
        elif state == "str":
            if c == "\\":
                i += 1
            elif c == '"':
                state = "code"
        elif state == "char":
            if c == "\\":
                i += 1
            elif c == "'":
                state = "code"
        i += 1
    return -1


def previous_top_level_boundary(text: str, pos: int) -> int:
    i = pos - 1
    while i >= 0:
        if text[i] in ";}":
            return i + 1
        i -= 1
    return 0


def extract_function_name(signature: str) -> Optional[str]:
    sig = re.sub(r"\s+", " ", signature.strip())
    if ";" in sig or "=" in sig:
        return None
    m = re.search(r"([A-Za-z_]\w*)\s*\([^;{}]*\)\s*$", sig)
    if not m:
        return None
    name = m.group(1)
    if name in KEYWORDS:
        return None
    prefix = sig[:m.start(1)]
    if re.search(r"\b(if|for|while|switch|return|sizeof)\b", prefix):
        return None
    return name


def extract_functions(text: str) -> Tuple[str, Dict[str, FunctionDef]]:
    clean = strip_comments(text)
    funcs: Dict[str, FunctionDef] = {}
    spans: List[Tuple[int, int]] = []
    i = 0
    n = len(clean)
    depth = 0
    state = "code"
    while i < n:
        c = clean[i]
        if state == "code":
            if c == '"':
                state = "str"
            elif c == "'":
                state = "char"
            elif c == "{":
                if depth == 0:
                    start = previous_top_level_boundary(clean, i)
                    signature = clean[start:i].strip()
                    name = extract_function_name(signature)
                    end_brace = find_matching(clean, i, "{", "}")
                    if name and end_brace != -1:
                        text_def = clean[start:end_brace + 1]
                        body = clean[i + 1:end_brace]
                        funcs[name] = FunctionDef(name, start, end_brace + 1, text_def, signature, body)
                        spans.append((start, end_brace + 1))
                        i = end_brace
                    else:
                        depth += 1
                else:
                    depth += 1
            elif c == "}":
                if depth > 0:
                    depth -= 1
        elif state == "str":
            if c == "\\":
                i += 1
            elif c == '"':
                state = "code"
        elif state == "char":
            if c == "\\":
                i += 1
            elif c == "'":
                state = "code"
        i += 1
    preamble_parts = []
    last = 0
    for a, b in sorted(spans):
        preamble_parts.append(clean[last:a])
        last = b
    preamble_parts.append(clean[last:])
    preamble = "\n".join(preamble_parts)
    return preamble, funcs


def call_names(body: str) -> Set[str]:
    names = set()
    for m in re.finditer(r"\b([A-Za-z_]\w*)\s*\(", body):
        name = m.group(1)
        if name not in KEYWORDS and name not in EXTERNAL_NAMES:
            names.add(name)
    return names


def dependency_closure(entry: str, funcs: Dict[str, FunctionDef], max_depth: int = 8) -> List[str]:
    order: List[str] = []
    seen: Set[str] = set()
    def visit(name: str, depth: int) -> None:
        if name in seen or name not in funcs or depth > max_depth:
            return
        seen.add(name)
        for callee in sorted(call_names(funcs[name].body)):
            if callee in funcs:
                visit(callee, depth + 1)
        order.append(name)
    visit(entry, 0)
    return order


def parse_switch_cases(body: str) -> List[Tuple[List[str], str, bool]]:
    labels: List[Tuple[int, int, str, bool]] = []
    i = 0
    n = len(body)
    depth = 0
    while i < n:
        c = body[i]
        if c in "{([":
            depth += 1
            i += 1
            continue
        if c in "})]":
            depth = max(0, depth - 1)
            i += 1
            continue
        if depth == 0 and re.match(r"case\b", body[i:]):
            m = re.match(r"case\s+", body[i:])
            j = i + m.end()
            colon = body.find(":", j)
            if colon == -1:
                break
            labels.append((i, colon + 1, body[j:colon].strip(), False))
            i = colon + 1
            continue
        if depth == 0 and re.match(r"default\s*:", body[i:]):
            m = re.match(r"default\s*:", body[i:])
            labels.append((i, i + m.end(), "", True))
            i += m.end()
            continue
        i += 1
    if not labels:
        return []
    cases: List[Tuple[List[str], str, bool]] = []
    current_labels: List[str] = []
    current_default = False
    for idx, (label_start, label_end, expr, is_default) in enumerate(labels):
        if idx > 0:
            prev_end = labels[idx - 1][1]
            code = body[prev_end:label_start]
            if code.strip():
                cases.append((current_labels, code, current_default))
                current_labels = []
                current_default = False
        if is_default:
            current_default = True
        else:
            current_labels.append(expr)
    last_code_start = labels[-1][1]
    code = body[last_code_start:]
    cases.append((current_labels, code, current_default))
    return cases


def remove_top_level_breaks(code: str) -> str:
    return re.sub(r"\bbreak\s*;", "", code)


def rewrite_switches_once(text: str, counter_start: int = 0) -> Tuple[str, bool, int]:
    m = re.search(r"\bswitch\s*\(", text)
    if not m:
        return text, False, counter_start
    paren_open = text.find("(", m.start())
    paren_close = find_matching(text, paren_open, "(", ")")
    if paren_close == -1:
        return text, False, counter_start
    brace_open = text.find("{", paren_close)
    if brace_open == -1:
        return text, False, counter_start
    brace_close = find_matching(text, brace_open, "{", "}")
    if brace_close == -1:
        return text, False, counter_start
    expr = text[paren_open + 1:paren_close].strip()
    body = text[brace_open + 1:brace_close]
    cases = parse_switch_cases(body)
    if not cases:
        return text, False, counter_start
    var = f"__epp_sw_{counter_start}"
    counter_start += 1
    parts = ["{\n", f"int {var} = ({expr});\n"]
    first = True
    default_code = ""
    for labels, code, is_default in cases:
        code = remove_top_level_breaks(code)
        if is_default:
            default_code += code + "\n"
            continue
        if not labels:
            continue
        cond = " || ".join([f"({var} == ({lab}))" for lab in labels])
        parts.append(("if" if first else "else if") + f" ({cond}) {{\n{code}\n}}\n")
        first = False
    if default_code.strip():
        parts.append(f"else {{\n{default_code}\n}}\n")
    parts.append("}\n")
    repl = "".join(parts)
    return text[:m.start()] + repl + text[brace_close + 1:], True, counter_start


def rewrite_switches(text: str) -> str:
    changed = True
    count = 0
    out = text
    guard = 0
    while changed and guard < 200:
        out, changed, count = rewrite_switches_once(out, count)
        guard += 1
    return out


def apply_sanitizers(text: str, rewrite_switch: bool) -> str:
    text = re.sub(r"__attribute__\s*\(\([^)]*\)\)", "", text)
    text = re.sub(r"__declspec\s*\([^)]*\)", "", text)
    text = re.sub(r"\b__extension__\b", "", text)
    text = re.sub(r"\bregister\b", "", text)
    text = re.sub(r"\bvolatile\b", "", text)
    if rewrite_switch:
        text = rewrite_switches(text)
    return text


def make_flat_source(project_root: Path, spec: ProjectSpec, source_rel: str, out_dir: Path, defines: List[str]) -> Path:
    pieces = [C_PRELUDE]
    for h in spec.headers:
        hp = project_root / h
        if hp.exists():
            pieces.append(strip_includes_pragmas_and_line_directives(read_text(hp)))
    sp = project_root / source_rel
    pieces.append(strip_includes_pragmas_and_line_directives(read_text(sp)))
    flat = "\n".join(defines + pieces)
    out_dir.mkdir(parents=True, exist_ok=True)
    out = out_dir / f"{spec.name}_{Path(source_rel).stem}_flat.c"
    out.write_text(flat, encoding="utf-8")
    return out


def run_gcc_preprocess(flat: Path, pp: Path, timeout: int) -> Tuple[bool, str]:
    cmd = ["gcc", "-E", "-P", "-x", "c", str(flat), "-o", str(pp)]
    try:
        proc = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, timeout=timeout)
        return proc.returncode == 0, proc.stdout + proc.stderr
    except subprocess.TimeoutExpired as exc:
        return False, (exc.stdout or "") + (exc.stderr or "") + "\n[TIMEOUT] gcc -E\n"


def preprocess_project(testcase: Path, spec: ProjectSpec, pp_timeout: int, no_gcc_pp: bool, defines: List[str], rewrite_switch: bool) -> List[Path]:
    root = locate_project_root(testcase, spec)
    if root is None:
        print(f"[SKIP] {spec.name}: project folder not found under {testcase}; searched markers={spec.source_markers + spec.header_markers}")
        return []
    print(f"[FOUND] {spec.name}: {root}")
    out_dir = testcase / "_eppather_preprocessed" / spec.name
    outputs = []
    for source_rel in spec.sources:
        flat = make_flat_source(root, spec, source_rel, out_dir, defines)
        pp = out_dir / f"{spec.name}_{Path(source_rel).stem}_pp.c"
        if no_gcc_pp:
            pp.write_text(flat.read_text(encoding="utf-8", errors="ignore"), encoding="utf-8")
            ok = True
            log = ""
        else:
            ok, log = run_gcc_preprocess(flat, pp, pp_timeout)
            (out_dir / f"{spec.name}_{Path(source_rel).stem}_gcc_preprocess.log").write_text(log, encoding="utf-8")
            if not ok:
                pp.write_text(flat.read_text(encoding="utf-8", errors="ignore"), encoding="utf-8")
                print(f"[WARN] gcc preprocessing failed for {spec.name}/{source_rel}; fallback to flat source")
        original = pp.read_text(encoding="utf-8", errors="ignore")
        sanitized = apply_sanitizers(original, rewrite_switch)
        pp.write_text(sanitized, encoding="utf-8")
        print(f"[OK] preprocessed: {pp}")
        outputs.append(pp)
    return outputs


def make_entry_slice(pp_file: Path, spec: ProjectSpec, entry: str, mode: str, slice_mode: str, rewrite_switch: bool) -> Tuple[Optional[Path], str]:
    text = pp_file.read_text(encoding="utf-8", errors="ignore")
    preamble, funcs = extract_functions(text)
    if entry not in funcs:
        return None, f"entry not found in preprocessed file: {entry}"
    if slice_mode == "entry":
        names = [entry]
    elif slice_mode == "closure":
        names = dependency_closure(entry, funcs)
    else:
        names = list(funcs.keys())
    if entry not in names:
        names.append(entry)
    selected = []
    for name in names:
        if name in funcs:
            selected.append(funcs[name].text)
    sliced_text = preamble + "\n\n" + "\n\n".join(selected) + "\n"
    sliced_text = apply_sanitizers(sliced_text, rewrite_switch)
    out_dir = pp_file.parent / "slices"
    out_dir.mkdir(parents=True, exist_ok=True)
    out = out_dir / f"{pp_file.stem}__{entry}__{slice_mode}.c"
    out.write_text(sliced_text, encoding="utf-8")
    return out, f"functions={','.join(names)}"


def mode_flag(mode: str) -> str:
    return {"summary": "-s", "cfg": "-c", "dfs2": "-q", "dp": "-g"}[mode]


def extract_metric(pattern: str, text: str) -> str:
    m = re.search(pattern, text, re.MULTILINE)
    return m.group(1).strip() if m else ""


def extract_metrics(text: str) -> Dict[str, str]:
    return {
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
        "has_function_summaries": "true" if "[FUNCTION SUMMARIES]" in text else "false",
        "has_program_summary": "true" if "[PROGRAM SUMMARY]" in text else "false",
        "has_cfg": "true" if "CFG TABLE" in text or "CFG DOT" in text else "false",
        "has_parse_error": "true" if "unsuccessful parsing" in text or "invalid syntax tree" in text else "false"
    }


def run_cnip(cnip: Path, cfile: Path, mode: str, entry: str, maxloop: int, maxpaths: int, timeout: int, log_path: Path, crash_trace: bool) -> Dict[str, str]:
    env = os.environ.copy()
    env["EPPATHER_ENTRY"] = entry
    if crash_trace:
        env["EPPATHER_DEBUG_CRASH_TRACE"] = "1"
    cmd = [str(cnip), mode_flag(mode), "--maxloop", str(maxloop), "--maxpaths", str(maxpaths), str(cfile)]
    start = time.time()
    timed_out = False
    try:
        proc = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, env=env, timeout=timeout)
        rc = proc.returncode
        text = proc.stdout + proc.stderr
    except subprocess.TimeoutExpired as exc:
        rc = 124
        timed_out = True
        text = (exc.stdout or "") + (exc.stderr or "") + "\n[TIMEOUT] cnip execution timeout\n"
    elapsed = time.time() - start
    log_path.parent.mkdir(parents=True, exist_ok=True)
    log_path.write_text(text, encoding="utf-8", errors="ignore")
    metrics = extract_metrics(text)
    metrics.update({
        "entry": entry,
        "mode": mode,
        "returncode": str(rc),
        "timeout": "true" if timed_out else "false",
        "seconds": f"{elapsed:.6f}",
        "log": str(log_path),
        "source": str(cfile)
    })
    return metrics


def parse_list(value: str) -> List[str]:
    return [x.strip() for x in value.split(",") if x.strip()]


def write_csv(path: Path, rows: List[Dict[str, str]]) -> None:
    fields = [
        "project", "entry", "mode", "slice_mode", "risk", "returncode", "timeout", "seconds",
        "worst_mems", "weighted_avg_mems", "function_count", "summary_case_count", "call_edge_count",
        "mems", "dfs_time", "dp_time", "reason", "notes", "has_function_summaries", "has_program_summary",
        "has_cfg", "has_parse_error", "slice_info", "source", "log"
    ]
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", newline="", encoding="utf-8") as f:
        w = csv.DictWriter(f, fieldnames=fields)
        w.writeheader()
        for row in rows:
            w.writerow({k: row.get(k, "") for k in fields})


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--cnip", default="")
    ap.add_argument("--projects", default="list,inih,sds")
    ap.add_argument("--modes", default="summary")
    ap.add_argument("--entry-set", choices=["core", "full"], default="core")
    ap.add_argument("--entries", default="")
    ap.add_argument("--slice-mode", choices=["entry", "closure", "full"], default="closure")
    ap.add_argument("--retry-entry-slice", action="store_true", default=True)
    ap.add_argument("--no-retry-entry-slice", dest="retry_entry_slice", action="store_false")
    ap.add_argument("--include-risky", action="store_true")
    ap.add_argument("--rewrite-switch", action="store_true", default=True)
    ap.add_argument("--no-rewrite-switch", dest="rewrite_switch", action="store_false")
    ap.add_argument("--no-gcc-pp", action="store_true")
    ap.add_argument("--maxloop", type=int, default=2)
    ap.add_argument("--maxpaths", type=int, default=80)
    ap.add_argument("--timeout", type=int, default=90)
    ap.add_argument("--pp-timeout", type=int, default=60)
    ap.add_argument("--crash-trace", action="store_true")
    ap.add_argument("--only-preprocess", action="store_true")
    args = ap.parse_args()

    root = find_repo_root()
    testcase = root / "testcase"
    cnip = None if args.only_preprocess else find_cnip(root, args.cnip)
    print(f"[ROOT] {root}")
    if cnip:
        print(f"[CNIP] {cnip}")

    define_lines = [
        "#define INI_USE_STACK 1",
        "#define INI_ALLOW_REALLOC 0",
        "#define INI_CUSTOM_ALLOCATOR 0",
        "#define INI_HANDLER_LINENO 0",
        "#define SDS_ABORT_ON_OOM 0"
    ]

    selected_projects = [PROJECTS[p] for p in parse_list(args.projects)]
    modes = parse_list(args.modes)
    timestamp = time.strftime("%Y%m%d_%H%M%S")
    run_root = testcase / "_eppather_runs" / timestamp
    rows: List[Dict[str, str]] = []

    for spec in selected_projects:
        pp_files = preprocess_project(testcase, spec, args.pp_timeout, args.no_gcc_pp, define_lines, args.rewrite_switch)
        if args.only_preprocess:
            continue
        if args.entries:
            entries = parse_list(args.entries)
        else:
            entries = spec.core_entries if args.entry_set == "core" else spec.full_entries
        if not args.include_risky:
            entries = [e for e in entries if e not in spec.risky_entries]
        for pp in pp_files:
            for entry in entries:
                slice_file, slice_info = make_entry_slice(pp, spec, entry, args.slice_mode, args.rewrite_switch)
                if slice_file is None:
                    print(f"[MISS] project={spec.name} entry={entry}: {slice_info}")
                    rows.append({"project": spec.name, "entry": entry, "mode": "", "slice_mode": args.slice_mode, "risk": "missing_entry", "returncode": "", "slice_info": slice_info, "source": str(pp)})
                    continue
                for mode in modes:
                    log_name = f"{spec.name}_{entry}_{mode}_{args.slice_mode}.log"
                    log = run_root / spec.name / log_name
                    print(f"[RUN] project={spec.name} entry={entry} mode={mode} slice={args.slice_mode}")
                    row = run_cnip(cnip, slice_file, mode, entry, args.maxloop, args.maxpaths, args.timeout, log, args.crash_trace)
                    row["project"] = spec.name
                    row["slice_mode"] = args.slice_mode
                    row["slice_info"] = slice_info
                    row["risk"] = "risky" if entry in spec.risky_entries else "core"
                    rows.append(row)
                    ok = row["returncode"] == "0"
                    print(f"[{'OK' if ok else 'FAIL'}] rc={row['returncode']} worst_mems={row.get('worst_mems','')} summaries={row.get('has_function_summaries','')} log={log}")
                    if (not ok) and args.retry_entry_slice and args.slice_mode != "entry" and mode == "summary":
                        entry_slice, entry_info = make_entry_slice(pp, spec, entry, "entry", args.rewrite_switch)
                        if entry_slice:
                            retry_log = run_root / spec.name / f"{spec.name}_{entry}_{mode}_entry_retry.log"
                            print(f"[RETRY] project={spec.name} entry={entry} mode={mode} slice=entry")
                            retry = run_cnip(cnip, entry_slice, mode, entry, args.maxloop, args.maxpaths, args.timeout, retry_log, args.crash_trace)
                            retry["project"] = spec.name
                            retry["slice_mode"] = "entry"
                            retry["slice_info"] = entry_info + "; retry_after_failure"
                            retry["risk"] = "risky" if entry in spec.risky_entries else "core"
                            rows.append(retry)
                            print(f"[{'OK' if retry['returncode']=='0' else 'FAIL'}] retry rc={retry['returncode']} worst_mems={retry.get('worst_mems','')} summaries={retry.get('has_function_summaries','')} log={retry_log}")

    if rows:
        summary = run_root / "run_summary.csv"
        write_csv(summary, rows)
        print(f"[SUMMARY] {summary}")
    return 0

if __name__ == "__main__":
    raise SystemExit(main())
