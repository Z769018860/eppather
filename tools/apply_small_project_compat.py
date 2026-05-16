#!/usr/bin/env python3
from pathlib import Path

RUNNER = Path("tools/run_small_project_summaries.py")

def replace_once(text, old, new, label):
    if old not in text:
        raise SystemExit("[ERROR] cannot find anchor for " + label)
    return text.replace(old, new, 1)

def main():
    if not RUNNER.exists():
        raise SystemExit("Please run from the eppather repository root.")

    s = RUNNER.read_text(encoding="utf-8")

    if "def normalize_semantic_expression" not in s:
        anchor = '''def make_typed_approx_source(funcs: Dict[str, FunctionDef], names: List[str], entry: str, project: str) -> str:
    known = set(funcs)
    out = [
        "/* Generated typed approximation for eppather summary mode. */\\n",
        f"/* project={project} EPPATHER_ENTRY={entry} slice=type_erased */\\n",
    ]
    for name in names:
        if name in funcs:
            out.append("\\n/* ===== TYPED APPROX FUNCTION " + name + " ===== */\\n")
            out.append(make_typed_approx_function(funcs[name], known))
            out.append("\\n")
    return "\\n".join(out)

def make_auto_compat_function'''
        insert = '''def make_typed_approx_source(funcs: Dict[str, FunctionDef], names: List[str], entry: str, project: str) -> str:
    known = set(funcs)
    out = [
        "/* Generated typed approximation for eppather summary mode. */\\n",
        f"/* project={project} EPPATHER_ENTRY={entry} slice=type_erased */\\n",
    ]
    for name in names:
        if name in funcs:
            out.append("\\n/* ===== TYPED APPROX FUNCTION " + name + " ===== */\\n")
            out.append(make_typed_approx_function(funcs[name], known))
            out.append("\\n")
    return "\\n".join(out)

def replace_balanced_call(text: str, name: str, repl_func) -> str:
    out = []
    i = 0
    needle = name + "("
    while i < len(text):
        j = text.find(needle, i)
        if j < 0:
            out.append(text[i:])
            break
        if j > 0 and (text[j - 1].isalnum() or text[j - 1] == "_"):
            out.append(text[i:j + len(name)])
            i = j + len(name)
            continue
        out.append(text[i:j])
        open_pos = j + len(name)
        depth = 0
        k = open_pos
        while k < len(text):
            if text[k] == "(":
                depth += 1
            elif text[k] == ")":
                depth -= 1
                if depth == 0:
                    args = text[open_pos + 1:k]
                    out.append(repl_func(args))
                    i = k + 1
                    break
            k += 1
        else:
            out.append(text[j:])
            break
    return "".join(out)

def first_arg(args: str) -> str:
    parts = split_top_level_commas(args)
    return parts[0].strip() if parts else "0"

def second_arg(args: str) -> str:
    parts = split_top_level_commas(args)
    return parts[1].strip() if len(parts) > 1 else "0"

def third_arg(args: str) -> str:
    parts = split_top_level_commas(args)
    return parts[2].strip() if len(parts) > 2 else "0"

def rewrite_sds_semantic_calls(expr: str) -> str:
    expr = re.sub(r"\\b([A-Za-z_][A-Za-z0-9_]*)\\s*\\[\\s*-\\s*1\\s*\\]", r"\\1[2]", expr)
    expr = replace_balanced_call(expr, "sdslen", lambda a: f"({first_arg(a)}[0])")
    expr = replace_balanced_call(expr, "sdsavail", lambda a: f"({first_arg(a)}[1] - {first_arg(a)}[0])")
    expr = replace_balanced_call(expr, "sdsalloc", lambda a: f"({first_arg(a)}[1])")
    expr = replace_balanced_call(expr, "sdsAllocSize", lambda a: f"({first_arg(a)}[1] + 3)")
    expr = replace_balanced_call(expr, "sdsAllocPtr", lambda a: f"({first_arg(a)})")
    expr = replace_balanced_call(expr, "sdsHdrSize", lambda a: "3")
    expr = replace_balanced_call(expr, "sdsReqType", lambda a: f"({first_arg(a)})")
    return expr

def rewrite_external_semantic_calls(expr: str) -> str:
    expr = replace_balanced_call(expr, "strlen", lambda a: f"({first_arg(a)}[0])")
    expr = replace_balanced_call(expr, "memcmp", lambda a: f"({third_arg(a)})")
    expr = replace_balanced_call(expr, "memcpy", lambda a: f"({third_arg(a)})")
    expr = replace_balanced_call(expr, "memmove", lambda a: f"({third_arg(a)})")
    expr = replace_balanced_call(expr, "memset", lambda a: f"({third_arg(a)})")
    expr = replace_balanced_call(expr, "strncpy", lambda a: f"({third_arg(a)})")
    expr = replace_balanced_call(expr, "snprintf", lambda a: f"({second_arg(a)})")
    expr = replace_balanced_call(expr, "vsnprintf", lambda a: f"({second_arg(a)})")
    expr = replace_balanced_call(expr, "s_malloc", lambda a: "0")
    expr = replace_balanced_call(expr, "s_calloc", lambda a: "0")
    expr = replace_balanced_call(expr, "malloc", lambda a: "0")
    expr = replace_balanced_call(expr, "calloc", lambda a: "0")
    expr = replace_balanced_call(expr, "s_realloc", lambda a: first_arg(a))
    expr = replace_balanced_call(expr, "realloc", lambda a: first_arg(a))
    expr = replace_balanced_call(expr, "s_free", lambda a: "0")
    expr = replace_balanced_call(expr, "free", lambda a: "0")
    return expr

def rewrite_semantic_assignment_line(line: str) -> str:
    line = re.sub(
        r"\\bsdssetlen\\s*\\(\\s*([^,]+?)\\s*,\\s*([^\\)]+?)\\s*\\)\\s*;",
        lambda m: f"{m.group(1).strip()}[0] = {m.group(2).strip()};",
        line,
    )
    line = re.sub(
        r"\\bsdsinclen\\s*\\(\\s*([^,]+?)\\s*,\\s*([^\\)]+?)\\s*\\)\\s*;",
        lambda m: f"{m.group(1).strip()}[0] = {m.group(1).strip()}[0] + {m.group(2).strip()};",
        line,
    )
    line = re.sub(
        r"\\bsdssetalloc\\s*\\(\\s*([^,]+?)\\s*,\\s*([^\\)]+?)\\s*\\)\\s*;",
        lambda m: f"{m.group(1).strip()}[1] = {m.group(2).strip()};",
        line,
    )
    return line

def normalize_semantic_expression(expr: str, known: Set[str], project: str) -> str:
    expr = replace_string_literals(expr)
    expr = re.sub(r"\\bNULL\\b", "0", expr)
    expr = re.sub(r"\\btrue\\b", "1", expr)
    expr = re.sub(r"\\bfalse\\b", "0", expr)
    expr = re.sub(r"sizeof\\s*\\([^)]*\\)", "1", expr)
    expr = re.sub(r"sizeof\\s+[A-Za-z_][A-Za-z0-9_]*", "1", expr)
    expr = remove_casts(expr)

    if project == "sds":
        expr = rewrite_sds_semantic_calls(expr)

    expr = rewrite_external_semantic_calls(expr)
    expr = rewrite_member_access_to_index(expr)
    expr = re.sub(r"&\\s*([A-Za-z_][A-Za-z0-9_]*)", r"\\1", expr)
    expr = replace_unsupported_calls(expr, known)
    return expr

def normalize_semantic_declaration_line(line: str, known: Set[str], project: str) -> str:
    return normalize_declaration_line(normalize_semantic_expression(line, known, project), known)

def normalize_semantic_body(body: str, known: Set[str], project: str) -> str:
    body = normalize_semantic_expression(body, known, project)
    out_lines: List[str] = []
    for line in body.splitlines():
        line = rewrite_semantic_assignment_line(line)
        out_lines.append(normalize_semantic_declaration_line(line, known, project))
    body = "\\n".join(out_lines)
    body = re.sub(r"\\breturn\\s*;", "return 0;", body)
    return body

def make_semantic_stubbed_function(func: FunctionDef, known: Set[str], project: str) -> str:
    params_text = extract_param_text(func.signature, func.name)
    params: List[str] = []
    param_names: List[str] = []
    if params_text.strip() and params_text.strip() != "void":
        for i, p in enumerate(split_top_level_commas(params_text)):
            name = param_name(p, i)
            if name not in param_names:
                param_names.append(name)
                params.append(typed_param(p, i))
    param_sig = ", ".join(params) if params else "void"
    ret = return_type_for_signature(func.signature, func.name)

    body = normalize_semantic_body(func.body, known, project)

    declared = collect_declared_names(body) | set(param_names)
    ids = collect_identifiers(body)
    extra = sorted(x for x in ids if x not in declared and x != func.name and x not in known)
    decls = "\\n".join(f"    int {x};" for x in extra)
    if decls:
        body = decls + "\\n" + body

    if ret == "int *":
        body = re.sub(r"\\breturn\\s+0\\s*;", "return 0;", body)
    return format_function_header(ret, func.name, param_sig) + f"\\n{{\\n{body}\\n}}\\n"

def make_semantic_stubbed_source(funcs: Dict[str, FunctionDef], names: List[str], entry: str, project: str) -> str:
    known = set(funcs)
    out = [
        "/* Generated semantic-stubbed approximation for eppather summary mode. */\\n",
        f"/* project={project} EPPATHER_ENTRY={entry} slice=semantic_stubbed */\\n",
    ]
    for name in names:
        if name in funcs:
            out.append("\\n/* ===== SEMANTIC STUBBED FUNCTION " + name + " ===== */\\n")
            out.append(make_semantic_stubbed_function(funcs[name], known, project))
            out.append("\\n")
    return "\\n".join(out)

def make_auto_compat_function'''
        s = replace_once(s, anchor, insert, "semantic_stubbed_functions")

    s = s.replace(
        'priority = {"closure": 0, "entry_only": 1, "type_erased": 2, "compat_entry": 3, "auto_compat": 4}',
        'priority = {"closure": 0, "entry_only": 1, "type_erased": 2, "semantic_stubbed": 3, "compat_entry": 4, "auto_compat": 5}'
    )
    s = s.replace(
        'priority = {"closure": 0, "entry_only": 1, "type_erased": 2, "compat_entry": 3}',
        'priority = {"closure": 0, "entry_only": 1, "type_erased": 2, "semantic_stubbed": 3, "compat_entry": 4, "auto_compat": 5}'
    )

    old = '''        typed_path = slices_dir / f"{flat_path.stem}__{entry}__type_erased.c"
        typed_path.write_text(make_typed_approx_source(funcs, closure, entry, spec.name), encoding="utf-8")
        result.append(("type_erased", typed_path))
    if (spec.name, entry) in COMPAT_FUNCTIONS:
'''
    new = '''        typed_path = slices_dir / f"{flat_path.stem}__{entry}__type_erased.c"
        typed_path.write_text(make_typed_approx_source(funcs, closure, entry, spec.name), encoding="utf-8")
        result.append(("type_erased", typed_path))

        semantic_path = slices_dir / f"{flat_path.stem}__{entry}__semantic_stubbed.c"
        semantic_path.write_text(make_semantic_stubbed_source(funcs, closure, entry, spec.name), encoding="utf-8")
        result.append(("semantic_stubbed", semantic_path))
    if (spec.name, entry) in COMPAT_FUNCTIONS:
'''
    if "__semantic_stubbed.c" not in s:
        s = replace_once(s, old, new, "build_slice_files semantic_stubbed")

    if "--no-semantic-stubbed" not in s:
        s = replace_once(
            s,
            '    ap.add_argument("--no-type-erased", action="store_true")\n',
            '    ap.add_argument("--no-type-erased", action="store_true")\n    ap.add_argument("--no-semantic-stubbed", action="store_true")\n',
            "arg no semantic stubbed"
        )
        s = replace_once(
            s,
            '''                if args.no_type_erased:
                    slice_files = [(m, p) for m, p in slice_files if m != "type_erased"]
                if args.no_compat_fallback:
''',
            '''                if args.no_type_erased:
                    slice_files = [(m, p) for m, p in slice_files if m != "type_erased"]
                if args.no_semantic_stubbed:
                    slice_files = [(m, p) for m, p in slice_files if m != "semantic_stubbed"]
                if args.no_compat_fallback:
''',
            "filter no semantic stubbed"
        )

    RUNNER.write_text(s, encoding="utf-8")
    print("[OK] Added semantic_stubbed slice to tools/run_small_project_summaries.py")
    print("[NEXT] Recommended validation:")
    print("  python3 tools/run_small_project_summaries.py --cnip build/cnip --projects sds --entries sdsavail,sdssetlen,sdssetalloc,sdsMakeRoomFor --modes summary --maxloop 2 --maxpaths 80 --timeout 120 --no-text-fallback")
    print("  python3 tools/run_small_project_summaries.py --cnip build/cnip --projects list,inih,sds --entry-set all --modes summary --maxloop 2 --maxpaths 80 --timeout 120 --no-text-fallback")
    return 0

if __name__ == "__main__":
    raise SystemExit(main())
