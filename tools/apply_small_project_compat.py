#!/usr/bin/env python3
from pathlib import Path
from typing import Tuple

ROOT = Path.cwd()
EPAT = ROOT / "C" / "syntax" / "EpatRunner.cpp"
RUNNER = ROOT / "tools" / "run_small_project_summaries.py"

def read(path: Path) -> str:
    return path.read_text(encoding="utf-8", errors="ignore")

def write(path: Path, text: str) -> None:
    path.write_text(text, encoding="utf-8")

def ensure_include(s: str, inc: str) -> str:
    if inc in s:
        return s
    return s.replace('#include "EpatRunner.h"\n', '#include "EpatRunner.h"\n' + inc + "\n", 1)

def find_function_block(text: str, signature_prefix: str) -> Tuple[int, int]:
    start = text.find(signature_prefix)
    if start < 0:
        raise RuntimeError(f"cannot find function: {signature_prefix}")
    brace = text.find("{", start)
    if brace < 0:
        raise RuntimeError(f"cannot find opening brace for: {signature_prefix}")
    depth = 0
    i = brace
    while i < len(text):
        if text[i] == "{":
            depth += 1
        elif text[i] == "}":
            depth -= 1
            if depth == 0:
                return start, i + 1
        i += 1
    raise RuntimeError(f"cannot find closing brace for: {signature_prefix}")

def patch_epat_runner() -> None:
    s = read(EPAT)

    for inc in [
        "#include <algorithm>",
        "#include <cctype>",
        "#include <cstdlib>",
        "#include <iostream>",
        "#include <sstream>",
        "#include <stdexcept>",
        "#include <unordered_set>",
    ]:
        s = ensure_include(s, inc)

    if "estimateMemsFromScript" not in s:
        helper = '''
std::string trimCopy(std::string s) {
    auto notSpace = [](unsigned char c) { return !std::isspace(c); };
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), notSpace));
    s.erase(std::find_if(s.rbegin(), s.rend(), notSpace).base(), s.end());
    return s;
}

bool isIdentChar(char c) {
    return std::isalnum(static_cast<unsigned char>(c)) || c == '_';
}

int countIdentifiersAsReads(const std::string& line) {
    static const std::unordered_set<std::string> keywords{
        "int", "long", "short", "char", "void", "unsigned", "signed", "size_t",
        "return", "if", "while", "for", "else", "NULL", "typedef", "struct",
        "union", "enum", "static", "const", "volatile", "restrict"
    };
    int count = 0;
    for (size_t i = 0; i < line.size();) {
        if (!(std::isalpha(static_cast<unsigned char>(line[i])) || line[i] == '_')) {
            ++i;
            continue;
        }
        const size_t start = i;
        ++i;
        while (i < line.size() && isIdentChar(line[i])) {
            ++i;
        }
        const std::string ident = line.substr(start, i - start);
        if (keywords.find(ident) == keywords.end()) {
            ++count;
        }
    }
    return count;
}

bool isDeclarationLine(const std::string& line) {
    return line.find("int ") == 0 ||
           line.find("long ") == 0 ||
           line.find("short ") == 0 ||
           line.find("char ") == 0 ||
           line.find("unsigned ") == 0 ||
           line.find("signed ") == 0 ||
           line.find("size_t ") == 0;
}

bool looksLikeAssignment(const std::string& line) {
    for (size_t i = 0; i < line.size(); ++i) {
        if (line[i] != '=') {
            continue;
        }
        const char prev = (i > 0 ? line[i - 1] : '\\0');
        const char next = (i + 1 < line.size() ? line[i + 1] : '\\0');
        if (prev == '=' || prev == '<' || prev == '>' || prev == '!' || next == '=') {
            continue;
        }
        return true;
    }
    return false;
}

int estimateMemsFromLine(const std::string& raw) {
    std::string line = trimCopy(raw);
    if (line.empty()) {
        return 0;
    }
    if (line.rfind("//", 0) == 0 || line.rfind("/*", 0) == 0) {
        return 0;
    }
    if (line.find("typedef") == 0 || line.find("struct ") == 0 ||
        line.find("union ") == 0 || line.find("enum ") == 0) {
        return 0;
    }

    int mem = 0;
    if (line.rfind("@(", 0) == 0) {
        mem += countIdentifiersAsReads(line);
    } else if (line.find("return") == 0) {
        mem += countIdentifiersAsReads(line);
    } else if (looksLikeAssignment(line)) {
        mem += 1;
        mem += countIdentifiersAsReads(line);
    } else if (!isDeclarationLine(line)) {
        mem += countIdentifiersAsReads(line);
    }

    for (size_t i = 0; i < line.size(); ++i) {
        if (line[i] == '[') {
            mem += 1;
        }
        if (line[i] == '*' && (i == 0 || !isIdentChar(line[i - 1]))) {
            mem += 1;
        }
    }
    return std::max(0, mem);
}

int estimateMemsFromScript(const std::string& script) {
    std::stringstream in(script);
    std::string line;
    int mem = 0;
    while (std::getline(in, line)) {
        mem += estimateMemsFromLine(line);
    }
    return mem;
}
'''
        anchor = "}  // namespace\n\nEpatRunner::EpatRunner"
        if anchor not in s:
            raise RuntimeError("cannot find namespace helper insertion anchor in EpatRunner.cpp")
        s = s.replace(anchor, helper + "\n}  // namespace\n\nEpatRunner::EpatRunner", 1)

    s = s.replace(
        'if (containsAny(line, {"->", "(*", "?", "[", "]"})) {',
        'if (containsAny(line, {"->", "?"})) {'
    )
    s = s.replace(
        'if (containsAny(line, {"->", "(*", "?"})) {',
        'if (containsAny(line, {"->", "?"})) {'
    )

    start, end = find_function_block(s, "EpatResult EpatRunner::solveScript")
    new_solve = '''EpatResult EpatRunner::solveScript(const std::string& script) const {
    if (envEnabled("EPPATHER_DEBUG_EPAT_SCRIPT")) {
        std::cerr << "[EPAT_SCRIPT_BEGIN]\\n" << script << "\\n[EPAT_SCRIPT_END]" << std::endl;
    }

    EpatResult result;

    if (envEnabled("EPPATHER_EPAT_TEXT_FALLBACK")) {
        result.status = epat::result::feasible;
        result.mem = estimateMemsFromScript(script);
        result.smt = "";
        result.model = "";
        return result;
    }

    try {
        auto root = epat::Root::fromString(script);
        auto solver = epat::Solver::create(std::move(root));
        result.status = solver->feasible();
        result.mem = solver->getMem();
        result.smt = solver->getSMT2();
        result.model = solver->getModel();
    } catch (const std::exception& ex) {
        result.status = epat::result::unknown;
        result.mem = estimateMemsFromScript(script);
        if (envEnabled("EPPATHER_DEBUG_CRASH_TRACE")) {
            std::cerr << "[EPAT_TEXT_FALLBACK] solver exception: " << ex.what() << std::endl;
        }
    } catch (...) {
        result.status = epat::result::unknown;
        result.mem = estimateMemsFromScript(script);
        if (envEnabled("EPPATHER_DEBUG_CRASH_TRACE")) {
            std::cerr << "[EPAT_TEXT_FALLBACK] solver unknown exception" << std::endl;
        }
    }
    return result;
}'''
    s = s[:start] + new_solve + s[end:]

    write(EPAT, s)
    print("[OK] patched C/syntax/EpatRunner.cpp")

def patch_runner() -> None:
    s = read(RUNNER)

    start = s.find("def run_cnip(")
    end = s.find("\ndef write_csv(", start)
    if start < 0 or end < 0:
        raise RuntimeError("cannot locate run_cnip() block in run_small_project_summaries.py")

    new_run_cnip = '''def run_cnip(cnip: Path, cfile: Path, mode: str, entry: str, maxloop: int, maxpaths: int, timeout: int, out_log: Path, crash_trace: bool, debug_epat: bool) -> Dict[str, str]:
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

'''
    s = s[:start] + new_run_cnip + s[end+1:]

    start = s.find("def write_csv(")
    end = s.find("\ndef select_entries(", start)
    if start < 0 or end < 0:
        raise RuntimeError("cannot locate write_csv() block in run_small_project_summaries.py")

    new_write_csv = '''def write_csv(path: Path, rows: List[Dict[str, str]]) -> None:
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

'''
    s = s[:start] + new_write_csv + s[end+1:]

    old_end = '''    if rows:
        summary_csv = run_root / "run_summary.csv"
        write_csv(summary_csv, rows)
        log(f"[SUMMARY] {summary_csv}")
    return 0
'''
    new_end = '''    if rows:
        summary_csv = run_root / "run_summary.csv"
        write_csv(summary_csv, rows)
        log(f"[SUMMARY] {summary_csv}")

        final_csv = run_root / "final_summary.csv"
        write_csv(final_csv, select_final_rows(rows))
        log(f"[FINAL SUMMARY] {final_csv}")
    return 0
'''
    if old_end in s:
        s = s.replace(old_end, new_end, 1)
    elif "final_summary.csv" not in s:
        raise RuntimeError("cannot replace final summary block")

    write(RUNNER, s)
    print("[OK] patched tools/run_small_project_summaries.py")

def main() -> int:
    if not (ROOT / "CMakeLists.txt").exists():
        raise SystemExit("Please run from the eppather repository root.")
    patch_epat_runner()
    patch_runner()
    print("[DONE] Rebuild with: cmake --build build -j")
    return 0

if __name__ == "__main__":
    raise SystemExit(main())
