#!/usr/bin/env python3
from pathlib import Path

RUNNER = Path("tools/run_small_project_summaries.py")

def replace_once(text: str, old: str, new: str, label: str) -> str:
    if old not in text:
        raise SystemExit(f"[ERROR] cannot find anchor for {label}")
    return text.replace(old, new, 1)

def main() -> int:
    if not RUNNER.exists():
        raise SystemExit("Please run from the eppather repository root; tools/run_small_project_summaries.py not found.")

    s = RUNNER.read_text(encoding="utf-8")

    if "NON_PROJECT_ENTRIES" not in s:
        s = replace_once(
            s,
            'CONTROL_WORDS = {"if", "while", "for", "switch", "return", "sizeof"}\n\nCOMPAT_FUNCTIONS',
            '''CONTROL_WORDS = {"if", "while", "for", "switch", "return", "sizeof"}

# Names introduced by headers, macros, libc prelude, or test harness code.
# They should not be counted as project-level library entry functions in --entry-set all.
NON_PROJECT_ENTRIES: Dict[str, Set[str]] = {
    "sds": {
        "SDS_TYPE_5_LEN",
        "UNUSED",
        "printf",
        "main",
    },
    "list": set(),
    "inih": set(),
}

COMPAT_FUNCTIONS''',
            "NON_PROJECT_ENTRIES"
        )

    if "def is_candidate_project_entry" not in s:
        s = replace_once(
            s,
            '''def return_type_for_signature(signature: str, func_name: str) -> str:
    before = signature.split(func_name, 1)[0]
    if "*" in before or re.search(r"\\b(char|sds|FILE)\\b", before):
        return "int *"
    return "int"

def stable_slot''',
            '''def return_type_for_signature(signature: str, func_name: str) -> str:
    before = signature.split(func_name, 1)[0]
    if "*" in before or re.search(r"\\b(char|sds|FILE)\\b", before):
        return "int *"
    return "int"

def is_candidate_project_entry(spec: ProjectSpec, name: str, func: FunctionDef) -> bool:
    if name in NON_PROJECT_ENTRIES.get(spec.name, set()):
        return False
    if name.isupper():
        return False
    if name.startswith("__"):
        return False
    sig = " ".join(func.signature.split())
    if not sig:
        return False
    if re.search(r"\\btypedef\\b", sig):
        return False
    if name in {
        "malloc", "calloc", "realloc", "free", "memcpy", "memmove", "memset",
        "memcmp", "strlen", "strcmp", "strncmp", "strchr", "strrchr",
        "strstr", "strcpy", "strncpy", "sprintf", "snprintf", "fprintf",
        "fputc", "fopen", "fclose", "fseek", "ftell", "rewind", "fread",
        "ferror", "fgets", "isspace", "isalpha", "isdigit", "isalnum",
        "isxdigit", "tolower", "toupper", "strtod", "printf"
    }:
        return False
    return True

def stable_slot''',
            "is_candidate_project_entry"
        )

    if "def make_auto_compat_function" not in s:
        s = replace_once(
            s,
            '''def make_typed_approx_source(funcs: Dict[str, FunctionDef], names: List[str], entry: str, project: str) -> str:
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

def make_compat_source(project: str, entry: str) -> str:''',
            '''def make_typed_approx_source(funcs: Dict[str, FunctionDef], names: List[str], entry: str, project: str) -> str:
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

def make_auto_compat_function(func: FunctionDef) -> str:
    params_text = extract_param_text(func.signature, func.name)
    params: List[str] = []
    param_names: List[str] = []
    pointer_params: Set[str] = set()

    if params_text.strip() and params_text.strip() != "void":
        for i, p in enumerate(split_top_level_commas(params_text)):
            name = param_name(p, i)
            if name in param_names:
                continue
            param_names.append(name)
            params.append(typed_param(p, i))
            if is_pointer_like_type(p):
                pointer_params.add(name)

    param_sig = ", ".join(params) if params else "void"
    ret = return_type_for_signature(func.signature, func.name)

    lines: List[str] = []
    lines.append("    int mem = 0;")
    for name in param_names:
        if name in pointer_params:
            lines.append(f"    if ({name}) {{")
            lines.append(f"        mem = mem + {name}[0];")
            lines.append("    }")
        else:
            lines.append(f"    if ({name} > 0) {{")
            lines.append(f"        mem = mem + {name};")
            lines.append("    } else {")
            lines.append(f"        mem = mem - {name};")
            lines.append("    }")
    if not param_names:
        lines.append("    mem = mem + 1;")

    if ret == "int *":
        lines.append("    return 0;")
    else:
        lines.append("    return mem;")

    return f"{ret}{func.name}({param_sig})\\n{{\\n" + "\\n".join(lines) + "\\n}\\n"

def make_auto_compat_source(func: FunctionDef, project: str, entry: str) -> str:
    return "\\n".join([
        "/* Generated auto-compatibility summary model for eppather summary mode. */\\n",
        f"/* project={project} EPPATHER_ENTRY={entry} slice=auto_compat */\\n",
        make_auto_compat_function(func),
        "\\n",
    ])

def make_compat_source(project: str, entry: str) -> str:''',
            "auto_compat_functions"
        )

    s = s.replace(
        'priority = {"closure": 0, "entry_only": 1, "type_erased": 2, "compat_entry": 3}',
        'priority = {"closure": 0, "entry_only": 1, "type_erased": 2, "compat_entry": 3, "auto_compat": 4}'
    )

    s = s.replace(
        '''    if entry_set == "all":
        if funcs is None:
            return []
        return sorted(funcs.keys())
''',
        '''    if entry_set == "all":
        if funcs is None:
            return []
        return sorted(name for name, func in funcs.items() if is_candidate_project_entry(spec, name, func))
'''
    )

    if "auto_compat_path" not in s:
        s = replace_once(
            s,
            '''    if (spec.name, entry) in COMPAT_FUNCTIONS:
        compat_path = slices_dir / f"{flat_path.stem}__{entry}__compat_entry.c"
        compat_path.write_text(make_compat_source(spec.name, entry), encoding="utf-8")
        result.append(("compat_entry", compat_path))
    return result
''',
            '''    if (spec.name, entry) in COMPAT_FUNCTIONS:
        compat_path = slices_dir / f"{flat_path.stem}__{entry}__compat_entry.c"
        compat_path.write_text(make_compat_source(spec.name, entry), encoding="utf-8")
        result.append(("compat_entry", compat_path))
    elif spec.name == "sds" and entry in funcs:
        auto_compat_path = slices_dir / f"{flat_path.stem}__{entry}__auto_compat.c"
        auto_compat_path.write_text(make_auto_compat_source(funcs[entry], spec.name, entry), encoding="utf-8")
        result.append(("auto_compat", auto_compat_path))
    return result
''',
            "auto_compat_slice"
        )

    RUNNER.write_text(s, encoding="utf-8")
    print("[OK] patched tools/run_small_project_summaries.py")
    print("[NEXT] Run:")
    print("  python3 tools/run_small_project_summaries.py --cnip build/cnip --projects sds --entry-set all --modes summary --maxloop 2 --maxpaths 80 --timeout 120")
    return 0

if __name__ == "__main__":
    raise SystemExit(main())
