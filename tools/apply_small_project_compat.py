#!/usr/bin/env python3
from pathlib import Path

ROOT = Path.cwd()

def read(path):
    return path.read_text(encoding="utf-8", errors="ignore")

def write(path, text):
    path.write_text(text, encoding="utf-8")

def fix_runner():
    p = ROOT / "tools" / "run_small_project_summaries.py"
    s = read(p)

    if "def to_text(value)" not in s:
        insert = """


def to_text(value) -> str:
    if value is None:
        return ""
    if isinstance(value, bytes):
        return value.decode("utf-8", errors="replace")
    return str(value)
"""
        if "def run_gcc_preprocess(" in s:
            s = s.replace("\ndef run_gcc_preprocess(", insert + "\n\ndef run_gcc_preprocess(", 1)
        elif "def run_cnip(" in s:
            s = s.replace("\ndef run_cnip(", insert + "\n\ndef run_cnip(", 1)
        else:
            raise RuntimeError("cannot find insertion point for to_text()")

    s = s.replace('(exc.stdout or "") + (exc.stderr or "")', 'to_text(exc.stdout) + to_text(exc.stderr)')
    s = s.replace("proc.stdout + proc.stderr", "to_text(proc.stdout) + to_text(proc.stderr)")
    s = s.replace("proc.stdout+proc.stderr", "to_text(proc.stdout) + to_text(proc.stderr)")

    if 'env.setdefault("EPPATHER_EPAT_SAFE_RENDER", "1")' not in s:
        s = s.replace(
            'env["EPPATHER_ENTRY"] = entry',
            'env["EPPATHER_ENTRY"] = entry\n    env.setdefault("EPPATHER_EPAT_SAFE_RENDER", "1")',
            1
        )

    write(p, s)
    print(f"[OK] fixed {p}")

def fix_epat_runner():
    p = ROOT / "C" / "syntax" / "EpatRunner.cpp"
    s = read(p)

    if '#include <cstdlib>' not in s:
        s = s.replace('#include "EpatRunner.h"\n\n', '#include "EpatRunner.h"\n\n#include <cctype>\n#include <cstdlib>\n#include <iostream>\n', 1)

    helper = """
bool envEnabled(const char* name) {
    const char* v = std::getenv(name);
    return v && *v && std::string(v) != "0";
}

bool containsAny(const std::string& s, std::initializer_list<const char*> needles) {
    for (const char* needle : needles) {
        if (s.find(needle) != std::string::npos) {
            return true;
        }
    }
    return false;
}

bool probablyUnsafeForEpat(const std::string& line) {
    if (line.empty()) {
        return false;
    }
    if (containsAny(line, {"->", "(*", "?", "[", "]"})) {
        return true;
    }
    if (containsAny(line, {"sizeof", "offsetof", "__attribute__", "__asm"})) {
        return true;
    }
    return false;
}

void appendSafeLine(std::string& script, const std::string& line, bool addSemicolon) {
    if (line.empty()) {
        return;
    }
    if (envEnabled("EPPATHER_EPAT_SAFE_RENDER") && probablyUnsafeForEpat(line)) {
        if (envEnabled("EPPATHER_DEBUG_CRASH_TRACE")) {
            std::cerr << "[EPAT_SAFE_RENDER] skip unsupported script line: " << line << std::endl;
        }
        return;
    }
    script += line;
    if (addSemicolon && !endsWithSemicolon(line)) {
        script += ";";
    }
    script += "\\n";
}
"""
    if "bool envEnabled(const char* name)" not in s:
        anchor = "bool endsWithSemicolon(const std::string& s) {\n    return !s.empty() && s.back() == ';';\n}\n"
        if anchor not in s:
            raise RuntimeError("cannot find endsWithSemicolon() anchor in EpatRunner.cpp")
        s = s.replace(anchor, anchor + helper, 1)

    s = s.replace(
        'script += init;\n                    if (!endsWithSemicolon(init)) script += ";";\n                    script += "\\n";',
        'appendSafeLine(script, init, true);'
    )
    s = s.replace(
        'script += step.node->expr_str;\n                    if (!endsWithSemicolon(step.node->expr_str)) script += ";";\n                    script += "\\n";',
        'appendSafeLine(script, step.node->expr_str, true);'
    )
    s = s.replace(
        'script += code;\n                    if (!endsWithSemicolon(code)) script += "\\n";',
        'appendSafeLine(script, code, false);'
    )

    s = s.replace(
        'script += "@(" + step.node->cond_str + ");\\n";',
        'if (!envEnabled("EPPATHER_EPAT_SAFE_RENDER") || !probablyUnsafeForEpat(step.node->cond_str)) {\n                        script += "@(" + step.node->cond_str + ");\\n";\n                    }'
    )
    s = s.replace(
        'script += "@(!(" + step.node->cond_str + "));\\n";',
        'if (!envEnabled("EPPATHER_EPAT_SAFE_RENDER") || !probablyUnsafeForEpat(step.node->cond_str)) {\n                        script += "@(!(" + step.node->cond_str + "));\\n";\n                    }'
    )

    if "[EPAT_SCRIPT_BEGIN]" not in s:
        s = s.replace(
            "EpatResult EpatRunner::solveScript(const std::string& script) const {\n",
            'EpatResult EpatRunner::solveScript(const std::string& script) const {\n'
            '    if (envEnabled("EPPATHER_DEBUG_EPAT_SCRIPT")) {\n'
            '        std::cerr << "[EPAT_SCRIPT_BEGIN]\\n" << script << "\\n[EPAT_SCRIPT_END]" << std::endl;\n'
            '    }\n',
            1
        )

    write(p, s)
    print(f"[OK] fixed {p}")

def main():
    if not (ROOT / "CMakeLists.txt").exists():
        raise SystemExit("Please run this script from /home/zhangliwei/eppather")
    fix_runner()
    fix_epat_runner()
    print("[DONE] Now rebuild: cmake --build build -j")

if __name__ == "__main__":
    main()
