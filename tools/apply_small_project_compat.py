#!/usr/bin/env python3
from pathlib import Path

RUNNER = Path("tools/run_small_project_summaries.py")

def replace_once(text: str, old: str, new: str, label: str) -> str:
    if old not in text:
        raise SystemExit(f"[ERROR] cannot find anchor for {label}")
    return text.replace(old, new, 1)

def main() -> int:
    if not RUNNER.exists():
        raise SystemExit("Please run from the eppather repository root.")

    s = RUNNER.read_text(encoding="utf-8")

    if "def format_function_header" not in s:
        s = replace_once(
            s,
            '''def return_type_for_signature(signature: str, func_name: str) -> str:
    before = signature.split(func_name, 1)[0]
    if "*" in before or re.search(r"\\b(char|sds|FILE)\\b", before):
        return "int *"
    return "int"

def is_candidate_project_entry''',
            '''def return_type_for_signature(signature: str, func_name: str) -> str:
    before = signature.split(func_name, 1)[0]
    if "*" in before or re.search(r"\\b(char|sds|FILE)\\b", before):
        return "int *"
    return "int"

def format_function_header(ret: str, name: str, params: str) -> str:
    ret = ret.strip()
    if ret.endswith("*"):
        return f"{ret}{name}({params})"
    return f"{ret} {name}({params})"

def is_candidate_project_entry''',
            "format_function_header"
        )

    s = s.replace(
        '    return f"{ret}{func.name}({param_sig})\\\\n{{\\\\n{body}\\\\n}}\\\\n"',
        '    return format_function_header(ret, func.name, param_sig) + f"\\\\n{{\\\\n{body}\\\\n}}\\\\n"'
    )
    s = s.replace(
        '    return f"{ret}{func.name}({param_sig})\\n{{\\n{body}\\n}}\\n"',
        '    return format_function_header(ret, func.name, param_sig) + f"\\n{{\\n{body}\\n}}\\n"'
    )

    s = s.replace(
        '    return f"{ret}{func.name}({param_sig})\\\\n{{\\\\n" + "\\\\n".join(lines) + "\\\\n}}\\\\n"',
        '    return format_function_header(ret, func.name, param_sig) + "\\\\n{\\\\n" + "\\\\n".join(lines) + "\\\\n}\\\\n"'
    )
    s = s.replace(
        '    return f"{ret}{func.name}({param_sig})\\n{{\\n" + "\\n".join(lines) + "\\n}\\n"',
        '    return format_function_header(ret, func.name, param_sig) + "\\n{\\n" + "\\n".join(lines) + "\\n}\\n"'
    )

    old = '''    if (spec.name, entry) in COMPAT_FUNCTIONS:
        compat_path = slices_dir / f"{flat_path.stem}__{entry}__compat_entry.c"
        compat_path.write_text(make_compat_source(spec.name, entry), encoding="utf-8")
        result.append(("compat_entry", compat_path))
    elif spec.name == "sds" and entry in funcs:
        auto_compat_path = slices_dir / f"{flat_path.stem}__{entry}__auto_compat.c"
        auto_compat_path.write_text(make_auto_compat_source(funcs[entry], spec.name, entry), encoding="utf-8")
        result.append(("auto_compat", auto_compat_path))
    return result
'''
    new = '''    if (spec.name, entry) in COMPAT_FUNCTIONS:
        compat_path = slices_dir / f"{flat_path.stem}__{entry}__compat_entry.c"
        compat_path.write_text(make_compat_source(spec.name, entry), encoding="utf-8")
        result.append(("compat_entry", compat_path))
    if entry in funcs:
        auto_compat_path = slices_dir / f"{flat_path.stem}__{entry}__auto_compat.c"
        auto_compat_path.write_text(make_auto_compat_source(funcs[entry], spec.name, entry), encoding="utf-8")
        result.append(("auto_compat", auto_compat_path))
    return result
'''
    if old in s:
        s = s.replace(old, new, 1)
    elif 'elif spec.name == "sds" and entry in funcs:' in s:
        raise SystemExit("[ERROR] auto_compat block shape changed; inspect build_slice_files().")
    elif 'auto_compat_path = slices_dir' not in s:
        raise SystemExit("[ERROR] cannot locate auto_compat block.")

    s = s.replace(
        'priority = {"closure": 0, "entry_only": 1, "type_erased": 2, "compat_entry": 3}',
        'priority = {"closure": 0, "entry_only": 1, "type_erased": 2, "compat_entry": 3, "auto_compat": 4}'
    )

    RUNNER.write_text(s, encoding="utf-8")
    print("[OK] patched tools/run_small_project_summaries.py")
    print("[NEXT] Validate failed SDS entries:")
    print("  python3 tools/run_small_project_summaries.py --cnip build/cnip --projects sds --entries sds_free,sdsavail,sdsll2str,sdssetalloc,sdssetlen --modes summary --maxloop 2 --maxpaths 80 --timeout 120")
    print("[NEXT] Re-run all projects:")
    print("  python3 tools/run_small_project_summaries.py --cnip build/cnip --projects list,inih,sds --entry-set all --modes summary --maxloop 2 --maxpaths 80 --timeout 120")
    return 0

if __name__ == "__main__":
    raise SystemExit(main())
