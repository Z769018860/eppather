#!/usr/bin/env python3
import json, os, re, shlex, shutil, subprocess
from pathlib import Path

ROOT = Path(__file__).resolve().parent
TC = ROOT / 'testcase'
OUT = ROOT / 'experiment_results'
CNIP = ROOT / 'build' / 'cnip'
PROJECTS = {
    'cjson': {
        'src': TC / 'cJSON' / 'cJSON.c',
        'cpp_flags': ['-I', str(TC / 'cJSON'), '-DCJSON_PUBLIC(x)=x', '-DCJSON_CDECL='],
    },
    'lua': {
        # onelua.c is a bundled amalgamation that currently triggers weaker CFG extraction.
        # Use lapi.c as the stable representative for Lua project CFG/summarization experiments.
        'src': TC / 'lua' / 'lapi.c',
        'cpp_flags': ['-I', str(TC / 'lua'), '-DLUA_USE_POSIX', '-DLUA_COMPAT_5_3'],
    },
    'tinyexpr': {
        # Use compatibility-reduced tinyexpr source for summary/DP stability.
        'src': TC / 'tinyexpr' / 'tinyexpr_cfgsafe.c',
        'cpp_flags': ['-I', str(TC / 'tinyexpr')],
    },
}

RUNTIME_PROFILE = {
    'cjson': {'maxloop': '1', 'maxpaths': '18', 'timeout': 120},
    'lua': {'maxloop': '1', 'maxpaths': '120', 'timeout': 180},
    'tinyexpr': {'maxloop': '1', 'maxpaths': '120', 'timeout': 180},
}

FALLBACK_PROFILE = {
    'cjson': [
        {'maxloop': '1', 'maxpaths': '15', 'timeout': 180},
        {'maxloop': '1', 'maxpaths': '8', 'timeout': 120},
    ],
}


def run(cmd, cwd=ROOT, timeout=None, extra_env=None):
    env = dict(os.environ)
    env['LD_LIBRARY_PATH'] = f"{ROOT/'build'}:{ROOT/'build'/'C'}:{ROOT/'build'/'common'}:{ROOT/'C'}:" + env.get('LD_LIBRARY_PATH', '')
    if extra_env:
        env.update(extra_env)
    try:
        p = subprocess.run(cmd, cwd=cwd, text=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, env=env, timeout=timeout)
        return p.returncode, p.stdout
    except subprocess.TimeoutExpired as e:
        out = e.stdout or b""
        if isinstance(out, bytes):
            out = out.decode('utf-8', errors='ignore')
        return 124, out + "\n[TIMEOUT]"


def collect_stats(text: str):
    out = {}
    for k in ('function_count', 'summary_case_count', 'call_edge_count'):
        m = re.search(rf'{k}=(\d+)', text)
        out[k] = int(m.group(1)) if m else None
    return out


def preprocess(src: Path, dst_i: Path, cpp_flags):
    cmd = ['gcc', '-E', '-P', '-std=c11', *cpp_flags, str(src)]
    rc, out = run(cmd)
    if rc == 0:
        dst_i.write_text(out)
    return rc, out


def compat_filter(project: str, text: str) -> str:
    """
    Convert preprocessed sources into a parser-friendlier subset for eppather.
    Goal: keep control-flow/function bodies for CFG while removing hard-to-parse declarations.
    """
    prelude = [
        "/* eppather compatibility prelude */",
        "#ifndef __attribute__",
        "#define __attribute__(x)",
        "#endif",
        "#ifndef __extension__",
        "#define __extension__",
        "#endif",
        "#ifndef __inline__",
        "#define __inline__ inline",
        "#endif",
        "#ifndef __THROW",
        "#define __THROW",
        "#endif",
        "#ifndef __wur",
        "#define __wur",
        "#endif",
        "#ifndef __nonnull",
        "#define __nonnull(x)",
        "#endif",
        "#ifndef __attribute_malloc__",
        "#define __attribute_malloc__",
        "#endif",
        "typedef unsigned long size_t;",
        "typedef long ptrdiff_t;",
        "typedef unsigned long uintptr_t;",
        "typedef void* __builtin_va_list;",
        "typedef struct _IO_FILE FILE;",
        "",
    ]
    lines = prelude[:]
    typedef_aliases = {}
    in_enum = False
    for line in text.splitlines():
        s = line.strip()
        if not s:
            lines.append(line)
            continue
        if s.startswith('enum') and '{' in s:
            in_enum = True
        if in_enum and ('#' in s or '/*' in s or '*/' in s):
            continue
        if in_enum and '};' in s:
            in_enum = False
        # Common noisy GNU/C extensions or declarations that frequently break parser recovery.
        if '__attribute__(' in s or '__declspec(' in s:
            continue
        if '__builtin_va_list' in s or '__gnuc_va_list' in s or '_IO_FILE' in s:
            continue
        if s.startswith('extern ') and ('__THROW' in s or '__wur' in s):
            continue
        if '__restrict' in s or 'restrict ' in s:
            line = line.replace('__restrict', '').replace('restrict ', '')
        if s.startswith('typedef '):
            # Handle simple alias typedef by converting it into macro-style expansion.
            # Example: typedef unsigned long lu_mem; -> #define lu_mem unsigned long
            m_simple = re.match(r'^typedef\s+([A-Za-z_][\w\s\*]+?)\s+([A-Za-z_]\w*)\s*;\s*$', s)
            if m_simple and '(*' not in s:
                base = re.sub(r'\s+', ' ', m_simple.group(1)).strip()
                alias = m_simple.group(2).strip()
                typedef_aliases[alias] = base
                continue
            if '(*' in s or s.count('(') > 2:
                continue
        # Skip GCC extension typedefs with typeof/alignof patterns (parser-unfriendly).
        if s.startswith('typedef ') and ('typeof' in s or '__typeof__' in s or '__alignof__' in s):
            continue
        if s.startswith('extern ') and ('(' in s and ')' in s and ';' in s):
            continue
        # Normalize anonymous struct/union forward declarations that often confuse recovery.
        if re.match(r'^(struct|union)\s*\{', s):
            continue
        if s.startswith('#pragma') or s.startswith('#line'):
            continue
        if s.startswith('register '):
            line = line.replace('register ', '')
        lines.append(line)

    macro_lines = []
    for alias, base in sorted(typedef_aliases.items()):
        macro_lines.append(f"#ifndef {alias}")
        macro_lines.append(f"#define {alias} {base}")
        macro_lines.append("#endif")
    if macro_lines:
        lines = prelude[:] + macro_lines + [""] + lines[len(prelude):]

    filtered = "\n".join(lines) + "\n"

    # Project-specific compatibility rewrites.
    if project == 'lua':
        # Keep CFG-focused analysis by softening some alias types frequently seen in declarations.
        filtered = re.sub(r'\bptrdiff_t\b', 'long', filtered)
        filtered = re.sub(r'\bsize_t\b', 'unsigned long', filtered)
        filtered = re.sub(r'\blu_byte\b', 'unsigned char', filtered)
        filtered = re.sub(r'\bl_mem\b', 'unsigned long', filtered)
        filtered = re.sub(r'\blu_mem\b', 'unsigned long', filtered)
        filtered = re.sub(r'\bInstruction\b', 'unsigned int', filtered)
        filtered = re.sub(r'\bStkId\b', 'void *', filtered)
        filtered = re.sub(r'\bPfunc\b', 'void *', filtered)
        # Simplify Lua API decoration macros to empty/identity forms.
        filtered = re.sub(r'\bLUA_API\b', '', filtered)
        filtered = re.sub(r'\bLUAI_FUNC\b', '', filtered)
        filtered = re.sub(r'\bLUAI_DDEC\b', '', filtered)
        filtered = re.sub(r'\bLUAI_DDEF\b', '', filtered)
    elif project == 'tinyexpr':
        filtered = re.sub(r'\bsize_t\b', 'unsigned long', filtered)
        filtered = re.sub(r'\buintptr_t\b', 'unsigned long', filtered)
        filtered = re.sub(r'\bte_fun2\b', 'double (*)(double,double)', filtered)
        filtered = re.sub(r'\bte_fun1\b', 'double (*)(double)', filtered)
        filtered = re.sub(r'\bte_fun0\b', 'double (*)()', filtered)
        filtered = re.sub(r'\bte_fun7\b', 'double (*)()', filtered)
    elif project == 'cjson':
        # cJSON public/declaration wrappers and bool-like aliases.
        filtered = re.sub(r'\bCJSON_PUBLIC\s*\(', '(', filtered)
        filtered = re.sub(r'\bCJSON_CDECL\b', '', filtered)
        filtered = re.sub(r'\bcJSON_bool\b', 'int', filtered)
        filtered = re.sub(r'\bCJSON_NESTING_LIMIT\b', '1000', filtered)
        filtered = re.sub(r'^\s*_IS[a-zA-Z_]+\s*=.*$', '', filtered, flags=re.M)
        filtered = re.sub(r'^\s*extern\s+void\s*\*\s*memcpy\s*\(.*$', '', filtered, flags=re.M)
        filtered = re.sub(r'^\s*long unsigned int __n\)\s*;\s*$', '', filtered, flags=re.M)
        filtered = re.sub(r'^\s*In file included from .*$' , '', filtered, flags=re.M)
    elif project == 'lua':
        filtered = re.sub(r'^\s*extern\s+.*__THROW.*$', '', filtered, flags=re.M)
        filtered = re.sub(r'^\s*extern\s+.*__nonnull.*$', '', filtered, flags=re.M)
    return filtered


def parse_cfg_quality(dot_path: Path):
    text = dot_path.read_text(encoding='utf-8', errors='ignore')
    node_count = len(re.findall(r'^\s*\d+\s*\[', text, flags=re.M))
    edge_count = len(re.findall(r'^\s*\d+\s*->\s*\d+', text, flags=re.M))
    return node_count, edge_count


def parse_mems(summary_text: str):
    worst = re.search(r'worst_mems=([^\n]+)', summary_text)
    avg = re.search(r'weighted_avg_mems=([^\n]+)', summary_text)
    return {
        'worst_mems': worst.group(1).strip() if worst else None,
        'weighted_avg_mems': avg.group(1).strip() if avg else None,
    }


def parse_function_names(summary_text: str):
    return re.findall(r'^Function\s+([A-Za-z_]\w*)\s*:', summary_text, flags=re.M)


def discover_entry_candidates(compat_source: str):
    names = re.findall(r'^(?:static\s+)?[A-Za-z_][\w\s\*]*\s+([A-Za-z_]\w*)\s*\([^;{}]*\)\s*\{', compat_source, flags=re.M)
    deny = {'if', 'while', 'for', 'switch'}
    uniq = []
    for n in names:
        if n not in deny and n not in uniq:
            uniq.append(n)
    return uniq[:6]


def discover_cjson_entry_candidates(compat_source: str):
    preferred = [
        'cJSON_Parse',
        'cJSON_ParseWithOpts',
        'cJSON_ParseWithLength',
        'cJSON_ParseWithLengthOpts',
        'cJSON_Print',
        'cJSON_PrintUnformatted',
    ]
    dynamic = discover_entry_candidates(compat_source)
    ordered = []
    for n in preferred + dynamic:
        if n not in ordered:
            ordered.append(n)
    return ordered[:10]


def main():
    OUT.mkdir(exist_ok=True)
    results = {}
    for name, conf in PROJECTS.items():
        pdir = OUT / name
        pdir.mkdir(exist_ok=True)
        for stale in pdir.glob('cfg_func_*.dot'):
            stale.unlink()
        use_direct_source = (name == 'tinyexpr' and conf['src'].name == 'tinyexpr_cfgsafe.c')
        i_file = pdir / f'{name}.i'
        if use_direct_source:
            i_file.write_text(conf['src'].read_text())
            rc = 0
        else:
            rc, pp = preprocess(conf['src'], i_file, conf['cpp_flags'])
            if rc != 0:
                results[name] = {'error': pp[:3000]}
                continue
        compat_i_file = pdir / f'{name}.compat.i'
        if use_direct_source:
            compat_i_file.write_text(i_file.read_text())
        else:
            compat_i_file.write_text(compat_filter(name, i_file.read_text()))

        profile = RUNTIME_PROFILE.get(name, {'maxloop': '1', 'maxpaths': '120', 'timeout': 180})
        entry_candidates = discover_cjson_entry_candidates(compat_i_file.read_text()) if name == 'cjson' else []
        per = {}
        default_entry_env = {'EPPATHER_ENTRY': 'cJSON_Parse'} if name == 'cjson' else None
        for opt, fname in [('-s', 'summary.txt'), ('-g', 'worst_path_dp.txt'), ('-c', 'cfg.txt')]:
            cmd = [str(CNIP), opt, '--maxloop', profile['maxloop'], '--maxpaths', profile['maxpaths'], str(compat_i_file)]
            rc, out = run(cmd, timeout=profile['timeout'], extra_env=default_entry_env)
            if rc == 124 and name in FALLBACK_PROFILE:
                for fb in FALLBACK_PROFILE[name]:
                    fb_cmd = [str(CNIP), opt, '--maxloop', fb['maxloop'], '--maxpaths', fb['maxpaths'], str(compat_i_file)]
                    rc, out_fb = run(fb_cmd, timeout=fb['timeout'], extra_env=default_entry_env)
                    out = (
                        out
                        + "\n[FALLBACK RETRY] " + ' '.join(shlex.quote(x) for x in fb_cmd)
                        + f"\n[FALLBACK RC] {rc}\n"
                        + out_fb
                    )
                    if rc != 124:
                        break
            if rc == 124 and entry_candidates:
                for entry in entry_candidates:
                    rc_e, out_e = run(cmd, timeout=90, extra_env={'EPPATHER_ENTRY': entry})
                    out += f"\n[ENTRY RETRY] {entry}\n[ENTRY RC] {rc_e}\n" + out_e
                    rc = rc_e
                    if rc != 124:
                        break
            (pdir / fname).write_text(out)
            per[fname] = rc
            if opt == '-c':
                for dot in ROOT.glob('cfg_func_*.dot'):
                    shutil.move(str(dot), pdir / dot.name)
        summary_text = (pdir / 'summary.txt').read_text()
        st = collect_stats(summary_text)
        st.update(parse_mems(summary_text))
        st['function_blocks'] = len(parse_function_names(summary_text))

        # Retry with a discovered entry function to get program-level mems if default entry is missing.
        if st.get('worst_mems') in (None, 'N/A') and per.get('summary.txt') == 0:
            fnames = entry_candidates + [f for f in parse_function_names(summary_text) if f not in entry_candidates]
            if fnames:
                rc_retry, out_retry = run(
                    [str(CNIP), '-s', '--maxloop', profile['maxloop'], '--maxpaths', profile['maxpaths'], str(compat_i_file)],
                    timeout=profile['timeout'],
                    extra_env={'EPPATHER_ENTRY': fnames[0]},
                )
                (pdir / 'summary_entry_retry.txt').write_text(out_retry)
                st['entry_retry'] = {'entry': fnames[0], 'rc': rc_retry}
                retry_mems = parse_mems(out_retry)
                st['worst_mems_retry'] = retry_mems['worst_mems']
                st['weighted_avg_mems_retry'] = retry_mems['weighted_avg_mems']
                st['summary_success'] = (retry_mems['worst_mems'] not in (None, 'N/A'))
        else:
            st['summary_success'] = (st.get('worst_mems') not in (None, 'N/A'))
        if 'summary_success' not in st:
            st['summary_success'] = False
        dot_files = sorted(pdir.glob('cfg_func_*.dot'))
        st['cfg_graph_count'] = len(dot_files)
        cfg_quality = []
        for dot in dot_files[:30]:
            n, e = parse_cfg_quality(dot)
            cfg_quality.append({'file': dot.name, 'nodes': n, 'edges': e})
        st['cfg_quality_sample'] = cfg_quality
        st['rcodes'] = per
        results[name] = st

    (OUT / 'report.json').write_text(json.dumps(results, indent=2, ensure_ascii=False))
    success_count = sum(1 for x in results.values() if x.get('summary_success'))
    results['_aggregate'] = {
        'project_count': len(PROJECTS),
        'summary_success_count': success_count,
        'summary_success_rate': round(success_count / max(len(PROJECTS), 1), 4),
    }
    (OUT / 'report.json').write_text(json.dumps(results, indent=2, ensure_ascii=False))
    print(json.dumps(results, indent=2, ensure_ascii=False))


if __name__ == '__main__':
    main()
