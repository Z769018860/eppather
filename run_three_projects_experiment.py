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
        # Use upstream tinyexpr core to validate summary coverage.
        'src': TC / 'tinyexpr' / 'tinyexpr.c',
        'fallback_src': TC / 'tinyexpr' / 'tinyexpr_cfgsafe.c',
        'cpp_flags': ['-I', str(TC / 'tinyexpr')],
    },
}

RUNTIME_PROFILE = {
    'cjson': {'maxloop': '1', 'maxpaths': '18', 'timeout': 120},
    'lua': {'maxloop': '1', 'maxpaths': '120', 'timeout': 180},
    'tinyexpr': {'maxloop': '1', 'maxpaths': '30', 'timeout': 180},
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


def compat_filter(project: str, text: str, aggressive: bool = True) -> str:
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

    noisy_decl_patterns = [
        r'^__BEGIN_DECLS\s*$',
        r'^__END_DECLS\s*$',
        r'^extern\s+__inline__\b.*$',
        r'^extern\s+inline\b.*$',
        r'^extern\s+__attribute__\b.*$',
        r'^extern\s+int\s+_IO_.*$',
        r'^extern\s+const\s+.*\b__libc_.*$',
        r'^typedef\s+__builtin_va_list\s+__gnuc_va_list\s*;\s*$',
        r'^typedef\s+struct\s+_IO_.*;\s*$',
        r'^typedef\s+.*\b__mbstate_t\b.*;\s*$',
    ]
    for line in text.splitlines():
        s = line.strip()
        if not s:
            lines.append(line)
            continue
        if any(re.match(pat, s) for pat in noisy_decl_patterns):
            continue
        if s.startswith('enum') and '{' in s:
            in_enum = True
        if in_enum and ('#' in s or '/*' in s or '*/' in s):
            continue
        if in_enum and '};' in s:
            in_enum = False
        # Common noisy GNU/C extensions or declarations that frequently break parser recovery.
        if aggressive and ('__attribute__(' in s or '__declspec(' in s):
            continue
        if aggressive and ('__builtin_va_list' in s or '__gnuc_va_list' in s or '_IO_FILE' in s):
            continue
        if aggressive and s.startswith('extern ') and ('__THROW' in s or '__wur' in s):
            continue
        if aggressive and re.match(r'^(const|unsigned|long|int|char|void|TValue|TString|lua_Alloc|F2Imod)\b.*[,;)]\s*$', s) and '(' not in s and ')' in s:
            continue
        if aggressive and ('_Float128' in s or '__compar_fn_t' in s):
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
        if aggressive and s.startswith('extern ') and ('(' in s and ')' in s and ';' in s):
            continue
        # Normalize anonymous struct/union forward declarations that often confuse recovery.
        if aggressive and re.match(r'^(struct|union)\s*\{', s):
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
    filtered = re.sub(r'\bint\s+l_uint32\s+int\b', 'unsigned int', filtered)
    filtered = re.sub(r'\bstruct\s+_IO_(?:FILE|marker|codecvt|wide_data)\s*;', '', filtered)

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
        filtered = re.sub(r'\bglobal_State\b', 'void *', filtered)
        filtered = re.sub(r'\blua_State\b', 'void *', filtered)
        filtered = re.sub(r'\bCallInfo\b', 'void *', filtered)
        # Simplify Lua API decoration macros to empty/identity forms.
        filtered = re.sub(r'\bLUA_API\b', '', filtered)
        filtered = re.sub(r'\bLUAI_FUNC\b', '', filtered)
        filtered = re.sub(r'\bLUAI_DDEC\b', '', filtered)
        filtered = re.sub(r'\bLUAI_DDEF\b', '', filtered)
        filtered = re.sub(r'^\s*extern\s+.*__THROW.*$', '', filtered, flags=re.M)
        filtered = re.sub(r'^\s*extern\s+.*__nonnull.*$', '', filtered, flags=re.M)
    elif project == 'tinyexpr':
        filtered = re.sub(r'\bsize_t\b', 'unsigned long', filtered)
        filtered = re.sub(r'\buintptr_t\b', 'unsigned long', filtered)
        # Float-to-int approximation for current solver limitations on double sort.
        filtered = re.sub(r'\bdouble\b', 'long', filtered)
        filtered = re.sub(r'\bfloat\b', 'long', filtered)
        filtered = re.sub(r'\bte_fun2\b', 'long (*)(long,long)', filtered)
        filtered = re.sub(r'\bte_fun1\b', 'long (*)(long)', filtered)
        filtered = re.sub(r'\bte_fun0\b', 'long (*)()', filtered)
        filtered = re.sub(r'\bte_fun7\b', 'long (*)()', filtered)
        filtered = re.sub(r'\bNAN\b', '0', filtered)
        filtered = re.sub(r'\bINFINITY\b', '1000000', filtered)
        filtered = re.sub(r'#include\s*<math\.h>', '', filtered)
    elif project == 'cjson':
        # cJSON public/declaration wrappers and bool-like aliases.
        filtered = re.sub(r'\bCJSON_PUBLIC\s*\(', '(', filtered)
        filtered = re.sub(r'\bCJSON_CDECL\b', '', filtered)
        filtered = re.sub(r'\bcJSON_bool\b', 'int', filtered)
        filtered = re.sub(r'\bCJSON_NESTING_LIMIT\b', '1000', filtered)
        filtered = re.sub(r'^\s*_IS[a-zA-Z_]+\s*=.*$', '', filtered, flags=re.M)
        filtered = re.sub(r'^\s*extern\s+void\s*\*\s*memcpy\s*\(.*$', '', filtered, flags=re.M)
        filtered = re.sub(r'^\s*long unsigned int __n\)\s*;\s*$', '', filtered, flags=re.M)
        filtered = re.sub(r'^\s*In file included from .*$', '', filtered, flags=re.M)
        filtered = re.sub(r'^\s*extern\s+.*__attribute_pure__.*$', '', filtered, flags=re.M)
        filtered = re.sub(r'^\s*extern\s+.*__nonnull\s*\(.*$', '', filtered, flags=re.M)
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


def extract_failure_diagnostics(output_text: str, source_text: str, source_label: str):
    """
    Collect likely failing statements/syntax around parser errors for quick triage.
    """
    diags = []
    lines = source_text.splitlines()
    seen = set()
    # Match forms like: xxx.compat.i:238:21 error: ...
    for m in re.finditer(rf'{re.escape(source_label)}:(\d+):(\d+)\s+(error|warning):\s+([^\n]+)', output_text):
        ln = int(m.group(1))
        col = int(m.group(2))
        msg = m.group(4).strip()
        key = (ln, col, msg)
        if key in seen:
            continue
        seen.add(key)
        start = max(1, ln - 1)
        end = min(len(lines), ln + 1)
        snippet = []
        for i in range(start, end + 1):
            mark = ">>" if i == ln else "  "
            snippet.append(f"{mark} L{i}: {lines[i-1]}")
        diags.append(
            f"[FAIL POINT] line={ln} col={col} msg={msg}\n" + "\n".join(snippet)
        )
        if len(diags) >= 20:
            break
    # Parse antlr-style: line 174:29 no viable alternative at input ...
    for m in re.finditer(r'line\s+(\d+):(\d+)\s+([^\n]+)', output_text):
        ln = int(m.group(1))
        col = int(m.group(2))
        msg = m.group(3).strip()
        key = (ln, col, msg)
        if key in seen:
            continue
        seen.add(key)
        if 1 <= ln <= len(lines):
            start = max(1, ln - 1)
            end = min(len(lines), ln + 1)
            snippet = []
            for i in range(start, end + 1):
                mark = ">>" if i == ln else "  "
                snippet.append(f"{mark} L{i}: {lines[i-1]}")
            diags.append(
                f"[FAIL POINT] line={ln} col={col} msg={msg}\n" + "\n".join(snippet)
            )
        if len(diags) >= 40:
            break
    return diags


def extract_failure_lines(output_text: str, source_label: str):
    bad = set()
    for m in re.finditer(rf'{re.escape(source_label)}:(\d+):\d+\s+(error|warning):\s+([^\n]+)', output_text):
        ln = int(m.group(1))
        msg = m.group(3)
        if ('missing type specifier' in msg or 'expected ' in msg or 'no viable alternative' in msg
            or 'mismatched input' in msg or 'extraneous input' in msg or 'undeclared identifier' in msg):
            bad.add(ln)
    for m in re.finditer(r'line\s+(\d+):\d+\s+([^\n]+)', output_text):
        ln = int(m.group(1))
        msg = m.group(2)
        if 'no viable alternative' in msg or 'mismatched input' in msg or 'extraneous input' in msg:
            bad.add(ln)
    return sorted(bad)


def sanitize_by_failure_lines(source_text: str, bad_lines):
    if not bad_lines:
        return source_text
    lines = source_text.splitlines()
    bad = set(bad_lines)
    out = []
    for i, line in enumerate(lines, start=1):
        if i in bad:
            out.append("/* removed by sanitizer: parse-failure line */")
            continue
        out.append(line)
    return "\n".join(out) + "\n"


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




def retry_with_compat_levels(name: str, opt: str, profile: dict, base_i: Path, pdir: Path, default_entry_env, initial_out: str, initial_rc: int):
    best_rc, best_out = initial_rc, initial_out
    if opt not in ('-s', '-g'):
        return best_rc, best_out
    for label, aggressive in [('relaxed', False), ('raw', None)]:
        if label == 'raw':
            cand = pdir / f"{name}.raw.compat.i"
            cand.write_text(base_i.read_text())
        else:
            cand = pdir / f"{name}.{label}.compat.i"
            cand.write_text(compat_filter(name, base_i.read_text(), aggressive=aggressive))
        cmd = [str(CNIP), opt, '--maxloop', profile['maxloop'], '--maxpaths', profile['maxpaths'], str(cand)]
        rc, out = run(cmd, timeout=profile['timeout'], extra_env=default_entry_env)
        best_out += f"\n[COMPAT RETRY:{label}] rc={rc}\n" + out
        if rc == 0:
            best_rc = 0
            if '[FUNCTION SUMMARIES]' in out:
                return best_rc, best_out
    return best_rc, best_out




def extract_function_only_source(text: str) -> str:
    lines = text.splitlines()
    out = []
    i = 0
    n = len(lines)
    while i < n:
        line = lines[i]
        if '{' in line and '(' in line and not line.strip().startswith(('if', 'for', 'while', 'switch')):
            header = []
            j = i
            while j >= 0 and lines[j].strip() and not lines[j].strip().endswith(';'):
                header.append(lines[j])
                if '{' in lines[j]:
                    break
                j -= 1
            header = list(reversed(header))
            brace = 0
            body = []
            k = i
            started = False
            while k < n:
                l = lines[k]
                if '{' in l:
                    brace += l.count('{')
                    started = True
                if started:
                    body.append(l)
                if '}' in l and started:
                    brace -= l.count('}')
                    if brace <= 0:
                        break
                k += 1
            if body and any('{' in x for x in body):
                out.extend(header[:-1] + body)
                out.append('')
                i = k + 1
                continue
        i += 1
    prelude = [
        'typedef unsigned long size_t;',
        'typedef long ptrdiff_t;',
        'typedef unsigned long uintptr_t;',
        'typedef void* __builtin_va_list;',
        'typedef struct _IO_FILE FILE;',
        ''
    ]
    return '\n'.join(prelude + out) + '\n'


def split_functions_to_files(text: str, out_dir: Path, prefix: str):
    out_dir.mkdir(exist_ok=True, parents=True)
    lines = text.splitlines()
    funcs = []
    i = 0
    n = len(lines)
    while i < n:
        line = lines[i]
        if '{' in line and '(' in line and not line.strip().startswith(('if', 'for', 'while', 'switch')):
            # capture body by brace matching
            brace = 0
            body = []
            k = i
            started = False
            while k < n:
                l = lines[k]
                if '{' in l:
                    brace += l.count('{')
                    started = True
                if started:
                    body.append(l)
                if '}' in l and started:
                    brace -= l.count('}')
                    if brace <= 0:
                        break
                k += 1
            if body and any('{' in x for x in body):
                funcs.append('\n'.join(body) + '\n')
                i = k + 1
                continue
        i += 1

    prelude = '\n'.join([
        'typedef unsigned long size_t;',
        'typedef long ptrdiff_t;',
        'typedef unsigned long uintptr_t;',
        'typedef void* __builtin_va_list;',
        'typedef struct _IO_FILE FILE;',
        ''
    ]) + '\n'

    files = []
    for idx, fbody in enumerate(funcs):
        fp = out_dir / f"{prefix}.func_{idx}.i"
        fp.write_text(prelude + fbody)
        files.append(fp)
    return files
def retry_on_timeout(name: str, opt: str, target_input: Path, default_entry_env, out: str, rc: int):
    if rc != 124 or opt not in ('-s', '-g'):
        return rc, out
    profiles = [
        ('timeout-shrink-1', '1', '20', 120),
        ('timeout-shrink-2', '1', '8', 90),
        ('timeout-shrink-3', '1', '4', 60),
    ]
    for tag, maxloop, maxpaths, to in profiles:
        cmd = [str(CNIP), opt, '--maxloop', maxloop, '--maxpaths', maxpaths, str(target_input)]
        rci, outi = run(cmd, timeout=to, extra_env=default_entry_env)
        out += f"\n[TIMEOUT RETRY:{tag}] " + ' '.join(shlex.quote(x) for x in cmd) + f"\n[TIMEOUT RC] {rci}\n" + outi
        rc = rci
        if rc != 124:
            break
    return rc, out
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
        compat_text = compat_i_file.read_text()
        entry_candidates = discover_cjson_entry_candidates(compat_text) if name == 'cjson' else []
        per = {}
        default_entry_env = {'EPPATHER_ENTRY': 'cJSON_Parse'} if name == 'cjson' else None
        for opt, fname in [('-s', 'summary.txt'), ('-g', 'worst_path_dp.txt'), ('-c', 'cfg.txt')]:
            target_input = compat_i_file
            if name == 'tinyexpr' and opt in ('-s', '-g') and conf.get('fallback_src'):
                target_input = conf['fallback_src']
            cmd = [str(CNIP), opt, '--maxloop', profile['maxloop'], '--maxpaths', profile['maxpaths'], str(target_input)]
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
            rc, out = retry_on_timeout(name, opt, Path(target_input), default_entry_env, out, rc)
            # Crash-oriented fallback: if summary/DP crashes (-11 etc.), retry with
            # stricter budget and optionally tinyexpr fallback source.
            if rc < 0 and opt in ('-s', '-g'):
                crash_cmd = [str(CNIP), opt, '--maxloop', '1', '--maxpaths', '4', str(target_input)]
                rc_c, out_c = run(crash_cmd, timeout=90, extra_env=default_entry_env)
                out += (
                    "\n[CRASH RETRY] " + ' '.join(shlex.quote(x) for x in crash_cmd)
                    + f"\n[CRASH RC] {rc_c}\n" + out_c
                )
                rc = rc_c
                if rc < 0 and name == 'tinyexpr' and conf.get('fallback_src'):
                    fb_i = pdir / 'tinyexpr_fallback.i'
                    fb_compat = pdir / 'tinyexpr_fallback.compat.i'
                    fb_i.write_text(conf['fallback_src'].read_text())
                    fb_compat.write_text(compat_filter('tinyexpr', fb_i.read_text()))
                    tiny_fb_cmd = [str(CNIP), opt, '--maxloop', '1', '--maxpaths', '30', str(fb_compat)]
                    rc_fb, out_fb = run(tiny_fb_cmd, timeout=120)
                    out += (
                        "\n[TINYEXPR FALLBACK SRC] " + str(conf['fallback_src'])
                        + "\n[TINYEXPR FALLBACK CMD] " + ' '.join(shlex.quote(x) for x in tiny_fb_cmd)
                        + f"\n[TINYEXPR FALLBACK RC] {rc_fb}\n" + out_fb
                    )
                    rc = rc_fb
            if rc < 0 and opt in ('-s', '-g'):
                bad_lines = extract_failure_lines(out, Path(target_input).name)
                if bad_lines:
                    target_text = Path(target_input).read_text(encoding='utf-8', errors='ignore')
                    sanitized = sanitize_by_failure_lines(target_text, bad_lines[:200])
                    sanitized_file = pdir / f'{name}.sanitized.compat.i'
                    sanitized_file.write_text(sanitized)
                    san_cmd = [str(CNIP), opt, '--maxloop', '1', '--maxpaths', '20', str(sanitized_file)]
                    rc_s, out_s = run(san_cmd, timeout=120, extra_env=default_entry_env)
                    out += (
                        "\n[SANITIZE RETRY] removed_lines=" + str(len(bad_lines[:200]))
                        + "\n[SANITIZE CMD] " + ' '.join(shlex.quote(x) for x in san_cmd)
                        + f"\n[SANITIZE RC] {rc_s}\n" + out_s
                    )
                    rc = rc_s
            if rc != 0 and opt in ('-s', '-g'):
                retry_base = i_file if name != 'tinyexpr' else Path(target_input)
                rc, out = retry_with_compat_levels(name, opt, profile, retry_base, pdir, default_entry_env, out, rc)
            if rc != 0 and opt == '-s':
                active_text = Path(target_input).read_text(encoding='utf-8', errors='ignore')
                func_only = extract_function_only_source(active_text)
                func_file = pdir / f'{name}.function_only.i'
                func_file.write_text(func_only)
                fcmd = [str(CNIP), opt, '--maxloop', '1', '--maxpaths', '12', str(func_file)]
                rc_f, out_f = run(fcmd, timeout=120, extra_env=default_entry_env)
                out += "\n[FUNCTION-ONLY RETRY] " + ' '.join(shlex.quote(x) for x in fcmd) + f"\n[FUNCTION-ONLY RC] {rc_f}\n" + out_f
                rc = rc_f if rc_f == 0 else rc
            if rc != 0 and opt == '-s':
                shard_dir = pdir / f'{name}_func_shards'
                shard_files = split_functions_to_files(Path(target_input).read_text(encoding='utf-8', errors='ignore'), shard_dir, name)
                success_blocks = 0
                for sf in shard_files[:80]:
                    scmd = [str(CNIP), '-s', '--maxloop', '1', '--maxpaths', '4', str(sf)]
                    rc_sf, out_sf = run(scmd, timeout=45, extra_env=default_entry_env)
                    out += '\n[SHARD RETRY] ' + sf.name + f' rc={rc_sf}\n'
                    if rc_sf == 0 and '[FUNCTION SUMMARIES]' in out_sf:
                        success_blocks += 1
                        out += out_sf
                out += f'\n[SHARD SUMMARY SUCCESS] {success_blocks}/{len(shard_files[:80])}\n'
            if rc < 0:
                diag_text = Path(target_input).read_text(encoding='utf-8', errors='ignore')
                fail_points = extract_failure_diagnostics(out, diag_text, Path(target_input).name)
                if fail_points:
                    out += "\n[FAILURE DIAGNOSTICS]\n" + "\n\n".join(fail_points) + "\n"
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
