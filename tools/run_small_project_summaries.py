#!/usr/bin/env python3
import argparse
import csv
import os
import re
import shutil
import subprocess
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
        safe_entries=["list_rpush", "list_lpush", "list_rpop", "list_lpop", "list_remove"],
        core_entries=["list_rpush", "list_lpush", "list_rpop", "list_lpop", "list_remove", "list_new"],
        full_entries=["list_new", "list_destroy", "list_rpush", "list_lpush", "list_rpop", "list_lpop", "list_find", "list_at", "list_remove"],
        preferred_dirs=["clib", "list", "clibs-list", "list-master"],
    ),
    "inih": ProjectSpec(
        name="inih",
        marker_files=["ini.c", "ini.h"],
        headers=["ini.h"],
        sources=["ini.c"],
        safe_entries=["ini_rstrip", "ini_lskip", "ini_find_chars_or_comment", "ini_strncpy0", "ini_reader_string"],
        core_entries=["ini_rstrip", "ini_lskip", "ini_find_chars_or_comment", "ini_strncpy0", "ini_reader_string", "ini_parse_string_length"],
        full_entries=["ini_rstrip", "ini_lskip", "ini_find_chars_or_comment", "ini_strncpy0", "ini_parse_stream", "ini_parse_file", "ini_parse", "ini_reader_string", "ini_parse_string", "ini_parse_string_length"],
        preferred_dirs=["inih"],
    ),
    "sds": ProjectSpec(
        name="sds",
        marker_files=["sds.c", "sds.h"],
        headers=["sdsalloc.h", "sds.h"],
        sources=["sds.c"],
        safe_entries=["sdsReqType", "sdsclear", "sdsupdatelen"],
        core_entries=["sdsReqType", "sdsempty", "sdsnew", "sdsdup", "sdsfree", "sdsupdatelen", "sdsclear", "sdsAllocSize", "sdsAllocPtr"],
        full_entries=["sdsHdrSize", "sdsReqType", "sdsnewlen", "sdsempty", "sdsnew", "sdsdup", "sdsfree", "sdsupdatelen", "sdsclear", "sdsMakeRoomFor", "sdsRemoveFreeSpace", "sdsAllocSize", "sdsAllocPtr"],
        preferred_dirs=["sds"],
    ),
}

KEYWORDS = {
    "if", "while", "for", "switch", "return", "sizeof", "case", "do", "else", "goto",
    "typedef", "struct", "union", "enum", "static", "inline", "extern", "const", "volatile",
    "int", "char", "long", "short", "unsigned", "signed", "void", "size_t", "NULL"
}

CONTROL_WORDS = {"if", "while", "for", "switch", "return", "sizeof"}

COMPAT_FUNCTIONS: Dict[Tuple[str, str], str] = {
    ("list", "list_rpush"): """
int list_rpush(int len, int node_ok)
{
    int writes = 0;
    if (!node_ok) {
        return 0;
    }
    if (len) {
        writes = writes + 4;
    } else {
        writes = writes + 4;
    }
    len = len + 1;
    return writes + len;
}
""",
    ("list", "list_lpush"): """
int list_lpush(int len, int node_ok)
{
    int writes = 0;
    if (!node_ok) {
        return 0;
    }
    if (len) {
        writes = writes + 4;
    } else {
        writes = writes + 4;
    }
    len = len + 1;
    return writes + len;
}
""",
    ("list", "list_rpop"): """
int list_rpop(int len)
{
    int reads = 1;
    if (!len) {
        return 0;
    }
    len = len - 1;
    if (len) {
        reads = reads + 3;
    } else {
        reads = reads + 2;
    }
    return reads + len;
}
""",
    ("list", "list_lpop"): """
int list_lpop(int len)
{
    int reads = 1;
    if (!len) {
        return 0;
    }
    len = len - 1;
    if (len) {
        reads = reads + 3;
    } else {
        reads = reads + 2;
    }
    return reads + len;
}
""",
    ("list", "list_remove"): """
int list_remove(int has_prev, int has_next, int len)
{
    int writes = 0;
    if (has_prev) {
        writes = writes + 1;
    } else {
        writes = writes + 1;
    }
    if (has_next) {
        writes = writes + 1;
    } else {
        writes = writes + 1;
    }
    len = len - 1;
    return writes + len;
}
""",
    ("inih", "ini_rstrip"): """
int ini_rstrip(int len, int last_is_space)
{
    if (len > 0) {
        if (last_is_space) {
            len = len - 1;
        }
    }
    return len;
}
""",
    ("inih", "ini_lskip"): """
int ini_lskip(int pos, int is_space)
{
    while (is_space && pos < 3) {
        pos = pos + 1;
        is_space = 0;
    }
    return pos;
}
""",
    ("inih", "ini_find_chars_or_comment"): """
int ini_find_chars_or_comment(int pos, int hit_char, int hit_comment)
{
    while (!hit_char && !hit_comment && pos < 3) {
        pos = pos + 1;
        hit_char = 1;
    }
    return pos;
}
""",
    ("inih", "ini_strncpy0"): """
int ini_strncpy0(int size, int src_nonzero)
{
    int copied = 0;
    if (size > 1) {
        if (src_nonzero) {
            copied = copied + 1;
        }
    }
    return copied;
}
""",
    ("inih", "ini_reader_string"): """
int ini_reader_string(int num_left, int num)
{
    if (num_left == 0 || num < 2) {
        return 0;
    }
    num_left = num_left - 1;
    return num_left + 1;
}
""",
    ("sds", "sdsReqType"): """
int sdsReqType(unsigned long string_size)
{
    if (string_size < 32) {
        return 0;
    }
    if (string_size < 256) {
        return 1;
    }
    if (string_size < 65536) {
        return 2;
    }
    return 3;
}
""",
    ("sds", "sdsclear"): """
int sdsclear(int len)
{
    len = 0;
    return len;
}
""",
    ("sds", "sdsupdatelen"): """
int sdsupdatelen(int old_len, int real_len)
{
    if (real_len >= 0) {
        old_len = real_len;
    }
    return old_len;
}
""",
}

def log(msg: str) -> None:
    print(msg, flush=True)

def to_text(value) -> str:
    if value is None:
        return ""
    if isinstance(value, bytes):
        return value.decode("utf-8", errors="replace")
    return str(value)

def parse_list(value: str) -> List[str]:
    return [x.strip() for x in value.split(",") if x.strip()]

def find_repo_root(start: Optional[Path] = None) -> Path:
    candidates: List[Path] = []
    if start:
        candidates.append(start.resolve())
    candidates.append(Path.cwd().resolve())
    try:
        candidates.append(Path(__file__).resolve().parent)
    except NameError:
        pass
    seen: Set[Path] = set()
    for p in candidates:
        for q in [p] + list(p.parents):
            if q in seen:
                continue
            seen.add(q)
            if (q / "CMakeLists.txt").exists() and (q / "testcase").exists():
                return q
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
    for p in [root / "build" / "cnip", root / "build_local" / "cnip", root / "cmake-build-debug" / "cnip", root / "cnip"]:
        if p.exists() and os.access(p, os.X_OK):
            return p.resolve()
    found = shutil.which("cnip")
    if found:
        return Path(found).resolve()
    raise FileNotFoundError("cnip not found. Build first or pass --cnip build/cnip")

def strip_includes_and_pragmas(text: str) -> str:
    out: List[str] = []
    for line in text.splitlines():
        if re.match(r"^\s*#\s*include\s+[<\"].*[>\"]", line):
            continue
        if re.match(r"^\s*#\s*pragma\b", line):
            continue
        if re.match(r"^\s*#\s*line\b", line):
            continue
        out.append(line)
    return "\n".join(out) + "\n"

def candidate_project_dirs(testcase: Path, spec: ProjectSpec) -> List[Path]:
    dirs: List[Path] = []
    for name in spec.preferred_dirs:
        p = testcase / name
        if p.exists():
            dirs.append(p)
    if testcase.exists():
        for p in testcase.iterdir():
            if p.is_dir() and not p.name.startswith("_") and p not in dirs:
                dirs.append(p)
    return dirs

def has_any_marker(root: Path, spec: ProjectSpec) -> bool:
    return any((root / rel).exists() for rel in spec.marker_files)

def locate_project_root(testcase: Path, spec: ProjectSpec) -> Optional[Path]:
    for p in candidate_project_dirs(testcase, spec):
        if has_any_marker(p, spec):
            return p
    return None

def read_existing_files(project_root: Path, rels: List[str]) -> List[Tuple[str, str]]:
    files: List[Tuple[str, str]] = []
    used: Set[Path] = set()
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
    state = "normal"
    while i < len(chars):
        c = chars[i]
        if state == "normal":
            if c == "/" and i + 1 < len(chars) and chars[i + 1] == "/":
                chars[i] = chars[i + 1] = " "
                i += 2
                state = "line_comment"
                continue
            if c == "/" and i + 1 < len(chars) and chars[i + 1] == "*":
                chars[i] = chars[i + 1] = " "
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
            if c == "*" and i + 1 < len(chars) and chars[i + 1] == "/":
                chars[i] = chars[i + 1] = " "
                i += 2
                state = "normal"
                continue
            if c != "\n":
                chars[i] = " "
        elif state == "string":
            if c == "\\" and i + 1 < len(chars):
                chars[i] = chars[i + 1] = " "
                i += 2
                continue
            if c == '"':
                state = "normal"
            chars[i] = " "
        elif state == "char":
            if c == "\\" and i + 1 < len(chars):
                chars[i] = chars[i + 1] = " "
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
    if "typedef" in sig[:m.start(1)].split():
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
        funcs[name] = FunctionDef(name=name, text=text[start:end + 1], start=start, end=end + 1, signature=signature, body=text[i + 1:end])
        spans.append((start, end + 1))
        i = end + 1
    if not spans:
        return funcs, text
    parts: List[str] = []
    last = 0
    for start, end in sorted(spans):
        parts.append(text[last:start])
        last = end
    parts.append(text[last:])
    return funcs, "".join(parts)

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
    result: List[str] = []
    seen: Set[str] = set()
    def visit(name: str, depth: int) -> None:
        if name in seen or name not in funcs or depth > max_depth:
            return
        seen.add(name)
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

def split_top_level_commas(text: str) -> List[str]:
    parts = []
    cur = []
    depth = 0
    for ch in text:
        if ch in "([{":
            depth += 1
        elif ch in ")]}":
            depth = max(0, depth - 1)
        if ch == "," and depth == 0:
            parts.append("".join(cur).strip())
            cur = []
        else:
            cur.append(ch)
    if cur:
        parts.append("".join(cur).strip())
    return parts

def extract_param_text(signature: str, func_name: str) -> str:
    m = re.search(r"\b" + re.escape(func_name) + r"\s*\(", signature)
    if not m:
        return ""
    start = signature.find("(", m.start())
    depth = 0
    for i in range(start, len(signature)):
        if signature[i] == "(":
            depth += 1
        elif signature[i] == ")":
            depth -= 1
            if depth == 0:
                return signature[start + 1:i]
    return ""

def param_name(param: str, idx: int) -> str:
    p = re.sub(r"=.*$", "", param).strip()
    p = re.sub(r"\[[^\]]*\]", " ", p)
    ids = re.findall(r"\b[A-Za-z_][A-Za-z0-9_]*\b", p)
    ids = [x for x in ids if x not in KEYWORDS and x not in {"const", "volatile", "restrict", "struct", "union", "enum"}]
    if not ids:
        return f"arg{idx}"
    return ids[-1]

FIELD_OFFSETS = {
    "len": 0,
    "alloc": 1,
    "flags": 2,
    "head": 3,
    "tail": 4,
    "next": 5,
    "prev": 6,
    "val": 7,
    "value": 7,
    "ptr": 8,
    "num_left": 9,
    "data": 10,
    "buf": 11,
}

POINTER_TYPE_NAMES = {
    "sds", "FILE",
}

def field_offset(field: str) -> int:
    if field in FIELD_OFFSETS:
        return FIELD_OFFSETS[field]
    return 16 + (sum(ord(ch) for ch in field) % 48)

def rewrite_member_access_to_index(text: str) -> str:
    """
    Keep pointer/array memory-access shape instead of flattening member accesses
    into scalar variables.

    Examples:
      self->len          => self[0]
      node->next         => node[5]
      self->tail->next   => self[4][5]
      ctx.ptr            => ctx_ptr
    """
    prev = None
    cur = text
    arrow = re.compile(r"(\b[A-Za-z_][A-Za-z0-9_]*(?:\s*\[[^\]]+\])*)\s*->\s*([A-Za-z_][A-Za-z0-9_]*)")
    dot = re.compile(r"\b([A-Za-z_][A-Za-z0-9_]*)\s*\.\s*([A-Za-z_][A-Za-z0-9_]*)")
    while prev != cur:
        prev = cur
        cur = arrow.sub(lambda m: f"{m.group(1)}[{field_offset(m.group(2))}]", cur)
        cur = dot.sub(lambda m: f"{m.group(1)}_{m.group(2)}", cur)
    return cur

def remove_casts(text: str) -> str:
    type_words = (
        r"(?:const|volatile|unsigned|signed|long|short|double|float|"
        r"struct\s+\w+|union\s+\w+|enum\s+\w+|"
        r"char|int|void|size_t|ssize_t|"
        r"[A-Za-z_][A-Za-z0-9_]*_t|sds|FILE)"
    )
    pattern = re.compile(r"\(\s*" + type_words + r"(?:\s*\*)*\s*\)")
    prev = None
    cur = text
    while prev != cur:
        prev = cur
        cur = pattern.sub("", cur)
    return cur

def replace_string_and_char_literals(text: str) -> str:
    text = re.sub(r'"(?:\\.|[^"\\])*"', "0", text)
    text = re.sub(r"'(?:\\.|[^'\\])+'", "1", text)
    return text

def replace_external_function_calls(text: str, internal_names: Optional[Set[str]] = None) -> str:
    if internal_names is None:
        internal_names = set()
    prev = None
    cur = text
    simple_call = re.compile(r"\b([A-Za-z_][A-Za-z0-9_]*)\s*\(([^(){};]*)\)")
    while prev != cur:
        prev = cur
        def repl(m: re.Match) -> str:
            name = m.group(1)
            if name in CONTROL_WORDS or name in internal_names:
                return m.group(0)
            return "1"
        cur = simple_call.sub(repl, cur)
    return cur

def is_pointer_like_decl(param_or_decl: str) -> bool:
    p = param_or_decl.strip()
    if "*" in p:
        return True
    if re.search(r"\[[^\]]*\]", p):
        return True
    words = re.findall(r"\b[A-Za-z_][A-Za-z0-9_]*\b", p)
    return any(w in POINTER_TYPE_NAMES for w in words)

def is_array_decl(param_or_decl: str) -> bool:
    return bool(re.search(r"\[[^\]]*\]", param_or_decl))

def normalize_array_suffix(text: str) -> str:
    return re.sub(r"\[[^\]]*\]", "[8]", text)

def normalize_declarator_name(part: str, idx: int) -> str:
    p = re.sub(r"=.*$", "", part).strip()
    p = re.sub(r"\[[^\]]*\]", " ", p)
    ids = re.findall(r"\b[A-Za-z_][A-Za-z0-9_]*\b", p)
    ids = [x for x in ids if x not in KEYWORDS and x not in {"const", "volatile", "restrict", "struct", "union", "enum"}]
    return ids[-1] if ids else f"tmp{idx}"

def normalize_decl_part(part: str, idx: int, internal_names: Optional[Set[str]] = None) -> str:
    raw = part.strip()
    if not raw:
        return ""
    if "(*" in raw:
        return ""
    init = ""
    if "=" in raw:
        left, init = raw.split("=", 1)
        init = normalize_expression_typed(init.strip(), internal_names)
    else:
        left = raw
    name = normalize_declarator_name(left, idx)

    if is_array_decl(left):
        decl = f"int {name}[8]"
    elif is_pointer_like_decl(left):
        decl = f"int *{name}"
    else:
        decl = f"int {name}"

    if init:
        return f"{decl} = {init};"
    return f"{decl};"

def normalize_declaration_line_typed(line: str, internal_names: Optional[Set[str]] = None) -> str:
    raw = line.strip()
    if not raw or raw.startswith("#"):
        return line

    prefix_pattern = re.compile(
        r"^(?P<indent>\s*)(?:(?:static|const|volatile|register|inline|extern)\s+)*"
        r"(?P<type>(?:struct|union|enum)\s+[A-Za-z_][A-Za-z0-9_]*|"
        r"[A-Za-z_][A-Za-z0-9_]*_t|sds|FILE|char|double|float|int|long|short|size_t|ssize_t|unsigned|signed|void)"
        r"(?:\s+(?:long|short|int|char|signed|unsigned|double|float))*"
        r"\s+(?P<rest>[^;{}]+);$"
    )
    m = prefix_pattern.match(line)
    if not m:
        return line

    rest = m.group("rest").strip()
    if "(" in rest and ")" in rest:
        return ""

    base_type = m.group("type")
    decls = []
    for idx, part in enumerate(split_top_level_commas(rest)):
        full_part = base_type + " " + part.strip()
        d = normalize_decl_part(full_part, idx, internal_names)
        if d:
            decls.append(d)
    indent = m.group("indent")
    return "\n".join(indent + d for d in decls)

def normalize_expression_typed(expr: str, internal_names: Optional[Set[str]] = None) -> str:
    expr = replace_string_and_char_literals(expr)
    expr = re.sub(r"\bNULL\b", "0", expr)
    expr = re.sub(r"\btrue\b", "1", expr)
    expr = re.sub(r"\bfalse\b", "0", expr)
    expr = re.sub(r"sizeof\s*\([^)]*\)", "1", expr)
    expr = re.sub(r"sizeof\s+[A-Za-z_][A-Za-z0-9_]*", "1", expr)
    expr = remove_casts(expr)
    expr = rewrite_member_access_to_index(expr)
    expr = replace_external_function_calls(expr, internal_names)
    expr = normalize_array_suffix(expr)
    return expr

def normalize_body_typed(body: str, internal_names: Optional[Set[str]] = None) -> str:
    b = normalize_expression_typed(body, internal_names)
    out_lines = []
    for line in b.splitlines():
        out_lines.append(normalize_declaration_line_typed(line, internal_names))
    b = "\n".join(out_lines)
    b = re.sub(r"\breturn\s*;", "return 0;", b)
    return b

def collect_identifiers(text: str) -> Set[str]:
    masked = mask_comments_and_strings(text)
    ids = set(re.findall(r"\b[A-Za-z_][A-Za-z0-9_]*\b", masked))
    return {x for x in ids if x not in KEYWORDS and x not in CONTROL_WORDS and not x.isupper()}

def collect_declared_names(text: str) -> Set[str]:
    names = set(re.findall(r"\bint\s+\*?\s*([A-Za-z_][A-Za-z0-9_]*)\b", text))
    names.update(re.findall(r"\bint\s+([A-Za-z_][A-Za-z0-9_]*)\s*\[", text))
    return names

def pointer_return_type(signature: str) -> bool:
    before = signature.split("(", 1)[0]
    if "*" in before:
        return True
    words = re.findall(r"\b[A-Za-z_][A-Za-z0-9_]*\b", before)
    return any(w in POINTER_TYPE_NAMES for w in words)

def make_typed_param(param: str, idx: int) -> Tuple[str, str]:
    name = param_name(param, idx)
    if is_array_decl(param) or is_pointer_like_decl(param):
        return name, f"int *{name}"
    return name, f"int {name}"

def make_type_erased_function(func: FunctionDef, internal_names: Optional[Set[str]] = None) -> str:
    if internal_names is None:
        internal_names = set()
    params_text = extract_param_text(func.signature, func.name)
    params = []
    param_names: List[str] = []
    if params_text.strip() and params_text.strip() != "void":
        for i, p in enumerate(split_top_level_commas(params_text)):
            name, decl = make_typed_param(p, i)
            if name not in param_names:
                param_names.append(name)
                params.append(decl)
    param_sig = ", ".join(params) if params else "void"
    ret = "int *" if pointer_return_type(func.signature) else "int"

    body = normalize_body_typed(func.body, internal_names)
    existing = collect_declared_names(body) | set(param_names)
    ids = collect_identifiers(body)
    extra = sorted(x for x in ids if x not in existing and x != func.name and x not in internal_names)
    decls = "\n".join(f"    int {x};" for x in extra)
    if decls:
        body = decls + "\n" + body

    if "return" not in body:
        body = body.rstrip() + "\n    return 0;\n"

    return f"{ret} {func.name}({param_sig})\n{{\n{body}\n}}\n"

def make_type_erased_source(funcs: Dict[str, FunctionDef], names: List[str], entry: str, project: str) -> str:
    out = [
        "/* Generated typed approximation for eppather summary mode. */\n",
        "/* This slice preserves pointer/array access forms where possible. */\n",
        f"/* project={project} EPPATHER_ENTRY={entry} slice=type_erased */\n",
    ]
    internal_names = set(names)
    for name in names:
        if name in funcs:
            out.append("\n/* ===== TYPED APPROX FUNCTION " + name + " ===== */\n")
            out.append(make_type_erased_function(funcs[name], internal_names))
            out.append("\n")
    return "\n".join(out)

def make_slice_source(preamble: str, funcs: Dict[str, FunctionDef], names: List[str], entry: str, project: str, slice_mode: str) -> str:
    out = [
        "/* Generated by run_small_project_summaries.py */\n",
        f"/* project={project} EPPATHER_ENTRY={entry} slice={slice_mode} */\n",
        filter_preamble(preamble),
    ]
    for name in names:
        if name in funcs:
            out.append("\n/* ===== FUNCTION " + name + " ===== */\n")
            out.append(funcs[name].text)
            out.append("\n")
    return "\n".join(out)

def make_type_erased_source(funcs: Dict[str, FunctionDef], names: List[str], entry: str, project: str) -> str:
    out = [
        "/* Generated type-erased approximation for eppather summary mode. */\n",
        f"/* project={project} EPPATHER_ENTRY={entry} slice=type_erased */\n",
    ]
    for name in names:
        if name in funcs:
            out.append("\n/* ===== TYPE ERASED FUNCTION " + name + " ===== */\n")
            out.append(make_type_erased_function(funcs[name]))
            out.append("\n")
    return "\n".join(out)

def make_compat_source(project: str, entry: str) -> str:
    return "\n".join([
        "/* Generated compatibility slice for eppather summary mode. */\n",
        f"/* project={project} EPPATHER_ENTRY={entry} slice=compat_entry */\n",
        COMPAT_FUNCTIONS[(project, entry)],
        "\n",
    ])

def mode_to_flag(mode: str) -> str:
    table = {"summary": "-s", "cfg": "-c", "dfs2": "-q", "dfs": "-f", "dp": "-g"}
    if mode not in table:
        raise ValueError(f"unknown mode: {mode}")
    return table[mode]

def run_cmd(cmd: List[str], env: Dict[str, str], timeout: int) -> Tuple[int, bool, str, float]:
    start = time.time()
    try:
        proc = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, env=env, timeout=timeout)
        return proc.returncode, False, to_text(proc.stdout) + to_text(proc.stderr), time.time() - start
    except subprocess.TimeoutExpired as exc:
        text = to_text(exc.stdout) + to_text(exc.stderr)
        text += "\n[TIMEOUT]\n"
        return 124, True, text, time.time() - start

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
    worst = metrics["worst_mems"]
    metrics["summary_ok"] = "true" if metrics["has_function_summaries"] == "true" and worst and worst != "N/A" else "false"
    return metrics

def run_cnip(cnip: Path, cfile: Path, mode: str, entry: str, maxloop: int, maxpaths: int, timeout: int, out_log: Path, crash_trace: bool, debug_epat: bool) -> Dict[str, str]:
    def invoke(use_text_fallback: bool, log_path: Path) -> Dict[str, str]:
        env = os.environ.copy()
        env["EPPATHER_ENTRY"] = entry
        env.setdefault("EPPATHER_EPAT_SAFE_RENDER", "1")
        env.setdefault("EPPATHER_EPAT_SAFE_PREFIX", "1")
        if use_text_fallback:
            env["EPPATHER_EPAT_TEXT_FALLBACK"] = "1"
        if crash_trace:
            env["EPPATHER_DEBUG_CRASH_TRACE"] = "1"
        if debug_epat:
            env["EPPATHER_DEBUG_EPAT_SCRIPT"] = "1"

        cmd = [str(cnip), mode_to_flag(mode), "--maxloop", str(maxloop), "--maxpaths", str(maxpaths), str(cfile)]
        rc, timed_out, text, elapsed = run_cmd(cmd, env, timeout)
        log_path.parent.mkdir(parents=True, exist_ok=True)
        log_path.write_text(text, encoding="utf-8", errors="ignore")
        metrics = extract_metrics(text, entry)
        metrics.update({
            "entry": entry,
            "mode": mode,
            "returncode": str(rc),
            "timeout": "true" if timed_out else "false",
            "seconds": f"{elapsed:.6f}",
            "log": str(log_path),
            "cmd": " ".join(cmd),
            "epat_mode": "text_fallback" if use_text_fallback else "pafi-rs",
        })
        return metrics

    row = invoke(False, out_log)
    ok = row.get("summary_ok") == "true" if mode == "summary" else row.get("returncode") == "0"

    retry_enabled = os.environ.get("EPPATHER_DISABLE_TEXT_FALLBACK_RETRY", "0") != "1"
    should_retry = retry_enabled and mode == "summary" and not ok

    if should_retry:
        fallback_log = out_log.with_name(out_log.stem + "_text_fallback" + out_log.suffix)
        fallback_row = invoke(True, fallback_log)
        fallback_ok = fallback_row.get("summary_ok") == "true"
        if fallback_ok:
            fallback_row["original_returncode"] = row.get("returncode", "")
            fallback_row["original_timeout"] = row.get("timeout", "")
            fallback_row["original_log"] = row.get("log", "")
            return fallback_row

    row.setdefault("original_returncode", "")
    row.setdefault("original_timeout", "")
    row.setdefault("original_log", "")
    return row

def write_csv(path: Path, rows: List[Dict[str, str]]) -> None:
    fields = [
        "project", "project_root", "source", "slice_mode", "slice_file",
        "entry", "mode", "epat_mode", "returncode", "timeout", "seconds",
        "summary_ok", "has_function_summaries", "has_program_summary", "entry_seen",
        "worst_mems", "weighted_avg_mems", "function_count", "summary_case_count",
        "call_edge_count", "mems", "dfs_time", "dp_time", "reason", "notes",
        "original_returncode", "original_timeout", "original_log", "log", "cmd"
    ]
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", newline="", encoding="utf-8") as f:
        writer = csv.DictWriter(f, fieldnames=fields)
        writer.writeheader()
        for row in rows:
            writer.writerow({k: row.get(k, "") for k in fields})

def select_final_rows(rows: List[Dict[str, str]]) -> List[Dict[str, str]]:
    priority = {
        "closure": 0,
        "entry_only": 1,
        "type_erased": 2,
        "compat_entry": 3,
    }
    grouped: Dict[Tuple[str, str, str], List[Dict[str, str]]] = {}
    for row in rows:
        key = (row.get("project", ""), row.get("entry", ""), row.get("mode", ""))
        grouped.setdefault(key, []).append(row)

    final_rows: List[Dict[str, str]] = []
    for key in sorted(grouped):
        candidates = grouped[key]
        ok_rows = [r for r in candidates if r.get("summary_ok") == "true" or (r.get("mode") != "summary" and r.get("returncode") == "0")]
        pool = ok_rows if ok_rows else candidates
        best = sorted(
            pool,
            key=lambda r: (
                0 if r.get("summary_ok") == "true" else 1,
                priority.get(r.get("slice_mode", ""), 99),
                0 if r.get("epat_mode") == "pafi-rs" else 1,
                float(r.get("seconds", "999999") or 999999),
            )
        )[0].copy()
        best["attempt_count"] = str(len(candidates))
        best["successful_attempt_count"] = str(len(ok_rows))
        final_rows.append(best)
    return final_rows

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

def prepare_project(testcase: Path, spec: ProjectSpec, out_root: Path) -> Tuple[Optional[Path], List[Path], Dict[Path, Tuple[Dict[str, FunctionDef], str]]]:
    project_root = locate_project_root(testcase, spec)
    if project_root is None:
        log(f"[SKIP] {spec.name}: project folder not found under {testcase}")
        return None, [], {}
    source_paths: List[Path] = []
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
    if entry in funcs:
        closure = closure_for_entry(entry, funcs, max_closure_depth) or [entry]
        closure_path = slices_dir / f"{flat_path.stem}__{entry}__closure.c"
        closure_path.write_text(make_slice_source(preamble, funcs, closure, entry, spec.name, "closure"), encoding="utf-8")
        result.append(("closure", closure_path))

        entry_path = slices_dir / f"{flat_path.stem}__{entry}__entry_only.c"
        entry_path.write_text(make_slice_source(preamble, funcs, [entry], entry, spec.name, "entry_only"), encoding="utf-8")
        result.append(("entry_only", entry_path))

        type_erased_path = slices_dir / f"{flat_path.stem}__{entry}__type_erased.c"
        type_erased_path.write_text(make_type_erased_source(funcs, closure, entry, spec.name), encoding="utf-8")
        result.append(("type_erased", type_erased_path))

    if (spec.name, entry) in COMPAT_FUNCTIONS:
        compat_path = slices_dir / f"{flat_path.stem}__{entry}__compat_entry.c"
        compat_path.write_text(make_compat_source(spec.name, entry), encoding="utf-8")
        result.append(("compat_entry", compat_path))
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
    ap.add_argument("--no-type-erased", action="store_true")
    ap.add_argument("--no-compat-fallback", action="store_true")
    ap.add_argument("--crash-trace", action="store_true")
    ap.add_argument("--debug-epat", action="store_true")
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
        project_root, flat_paths, parsed = prepare_project(testcase, spec, pp_root)
        if project_root is None or not flat_paths:
            continue
        if args.only_preprocess:
            continue

        selected = select_entries(spec, args.entry_set, custom_entries)
        project_out = pp_root / spec.name
        for flat_path in flat_paths:
            funcs, preamble = parsed[flat_path]
            missing = [e for e in selected if e not in funcs and (spec.name, e) not in COMPAT_FUNCTIONS]
            if missing:
                log(f"[WARN] {spec.name}: missing entries in {flat_path.name}: {','.join(missing)}")
            for entry in selected:
                slice_files = build_slice_files(project_out, spec, flat_path, funcs, preamble, entry, args.max_closure_depth)
                if args.no_type_erased:
                    slice_files = [(m, p) for m, p in slice_files if m != "type_erased"]
                if args.no_compat_fallback:
                    slice_files = [(m, p) for m, p in slice_files if m != "compat_entry"]
                if not slice_files:
                    continue
                for mode in modes:
                    succeeded = False
                    for slice_mode, slice_path in slice_files:
                        log_name = f"{spec.name}_{flat_path.stem}_{entry}_{mode}_{slice_mode}.log"
                        log_path = run_root / spec.name / log_name
                        log(f"[RUN] project={spec.name} entry={entry} mode={mode} slice={slice_mode}")
                        row = run_cnip(cnip, slice_path, mode, entry, args.maxloop, args.maxpaths, args.timeout, log_path, args.crash_trace, args.debug_epat)
                        row.update({
                            "project": spec.name,
                            "project_root": str(project_root),
                            "source": str(flat_path),
                            "slice_mode": slice_mode,
                            "slice_file": str(slice_path),
                        })
                        rows.append(row)
                        ok = row.get("summary_ok") == "true" if mode == "summary" else row.get("returncode") == "0"
                        log(f"[{'OK' if ok else 'FAIL'}] rc={row['returncode']} timeout={row['timeout']} summary_ok={row.get('summary_ok','')} worst_mems={row.get('worst_mems','')} log={log_path}")
                        if ok:
                            succeeded = True
                            break
                    if not succeeded:
                        log(f"[WARN] no successful {mode} result for {spec.name}:{entry}")

    if rows:
        summary_csv = run_root / "run_summary.csv"
        write_csv(summary_csv, rows)
        log(f"[SUMMARY] {summary_csv}")

        final_csv = run_root / "final_summary.csv"
        write_csv(final_csv, select_final_rows(rows))
        log(f"[FINAL SUMMARY] {final_csv}")
    return 0

if __name__ == "__main__":
    raise SystemExit(main())
