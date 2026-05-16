#!/usr/bin/env python3
from pathlib import Path

ROOT = Path.cwd()
EPAT = ROOT / "C" / "syntax" / "EpatRunner.cpp"

def read(path: Path) -> str:
    return path.read_text(encoding="utf-8", errors="ignore")

def write(path: Path, text: str) -> None:
    path.write_text(text, encoding="utf-8")

def ensure_include(s: str, include: str) -> str:
    if include in s:
        return s
    return s.replace('#include "EpatRunner.h"\n', '#include "EpatRunner.h"\n' + include + "\n", 1)

def main() -> int:
    if not (ROOT / "CMakeLists.txt").exists():
        raise SystemExit("Please run from the eppather repository root.")

    s = read(EPAT)

    s = ensure_include(s, "#include <sstream>")
    s = ensure_include(s, "#include <stdexcept>")

    helper = """
bool isSafePrefixLine(const std::string& line) {
    if (line.empty()) {
        return false;
    }
    if (line.find("typedef") != std::string::npos ||
        line.find("struct ") != std::string::npos ||
        line.find("union ") != std::string::npos ||
        line.find("enum ") != std::string::npos ||
        line.find("*") != std::string::npos ||
        line.find("[") != std::string::npos ||
        line.find("]") != std::string::npos ||
        line.find("->") != std::string::npos ||
        line.find(".") != std::string::npos ||
        line.find("(") != std::string::npos ||
        line.find(")") != std::string::npos) {
        return false;
    }
    if (line.find("int ") != std::string::npos ||
        line.find("long ") != std::string::npos ||
        line.find("char ") != std::string::npos ||
        line.find("size_t ") != std::string::npos ||
        line.find("unsigned ") != std::string::npos) {
        return true;
    }
    return false;
}

std::string sanitizePrefixForEpat(const std::string& prefix) {
    if (!envEnabled("EPPATHER_EPAT_SAFE_PREFIX")) {
        return prefix;
    }
    std::stringstream in(prefix);
    std::string out;
    std::string line;
    while (std::getline(in, line)) {
        if (isSafePrefixLine(line)) {
            out += line;
            if (!line.empty() && line.back() != ';') {
                out += ";";
            }
            out += "\\n";
        } else if (envEnabled("EPPATHER_DEBUG_CRASH_TRACE") && !line.empty()) {
            std::cerr << "[EPAT_SAFE_PREFIX] skip unsupported prefix line: " << line << std::endl;
        }
    }
    return out;
}
"""

    if "std::string sanitizePrefixForEpat" not in s:
        anchor = """void appendSafeLine(std::string& script, const std::string& line, bool addSemicolon) {
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
        if anchor not in s:
            raise SystemExit("Could not find appendSafeLine() anchor. Check EpatRunner.cpp manually.")
        s = s.replace(anchor, anchor + helper, 1)

    old_ctor = """EpatRunner::EpatRunner(std::string prefix) : prefix_(std::move(prefix)) {
    if (!prefix_.empty() && prefix_.back() != '\\n') prefix_.push_back('\\n');
}
"""
    new_ctor = """EpatRunner::EpatRunner(std::string prefix) : prefix_(sanitizePrefixForEpat(prefix)) {
    if (!prefix_.empty() && prefix_.back() != '\\n') prefix_.push_back('\\n');
}
"""
    if old_ctor in s:
        s = s.replace(old_ctor, new_ctor, 1)

    old_solve = """EpatResult EpatRunner::solveScript(const std::string& script) const {
    if (envEnabled("EPPATHER_DEBUG_EPAT_SCRIPT")) {
        std::cerr << "[EPAT_SCRIPT_BEGIN]\\n" << script << "\\n[EPAT_SCRIPT_END]" << std::endl;
    }
    auto root = epat::Root::fromString(script);
    auto solver = epat::Solver::create(std::move(root));

    EpatResult result;
    result.status = solver->feasible();
    result.mem = solver->getMem();
    result.smt = solver->getSMT2();
    result.model = solver->getModel();
    return result;
}
"""
    new_solve = """EpatResult EpatRunner::solveScript(const std::string& script) const {
    if (envEnabled("EPPATHER_DEBUG_EPAT_SCRIPT")) {
        std::cerr << "[EPAT_SCRIPT_BEGIN]\\n" << script << "\\n[EPAT_SCRIPT_END]" << std::endl;
    }

    EpatResult result;
    try {
        auto root = epat::Root::fromString(script);
        auto solver = epat::Solver::create(std::move(root));
        result.status = solver->feasible();
        result.mem = solver->getMem();
        result.smt = solver->getSMT2();
        result.model = solver->getModel();
    } catch (const std::exception& ex) {
        result.status = epat::result::unknown;
        result.mem = 0;
        if (envEnabled("EPPATHER_DEBUG_CRASH_TRACE")) {
            std::cerr << "[EPAT_SAFE_RENDER] solver exception: " << ex.what() << std::endl;
        }
    } catch (...) {
        result.status = epat::result::unknown;
        result.mem = 0;
        if (envEnabled("EPPATHER_DEBUG_CRASH_TRACE")) {
            std::cerr << "[EPAT_SAFE_RENDER] solver unknown exception" << std::endl;
        }
    }
    return result;
}
"""
    if old_solve in s:
        s = s.replace(old_solve, new_solve, 1)
    else:
        section_start = s.find("EpatResult EpatRunner::solveScript")
        section_end = s.find("EpatResult EpatRunner::solve(const")
        section = s[section_start:section_end] if section_start >= 0 and section_end > section_start else ""
        if "try {" not in section:
            raise SystemExit("Could not replace solveScript(); check EpatRunner.cpp manually.")

    write(EPAT, s)
    print("[OK] updated C/syntax/EpatRunner.cpp")
    print("[NEXT] cmake --build build -j")
    return 0

if __name__ == "__main__":
    raise SystemExit(main())
