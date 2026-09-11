// Implementation of CFG-aware epat++ invocation utilities.
#include "EpatRunner.h"
#include <unordered_set>
#include <algorithm>
#include <stdexcept>
#include <sstream>
#include <regex>

#include <cctype>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <utility>

#include "SyntaxNamePrinter.h"
#include "LoopBoundPredictor.h"

namespace psy {
namespace C {

namespace {
bool endsWithSemicolon(const std::string& s) {
    return !s.empty() && s.back() == ';';
}

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
    if (containsAny(line, {"->", "?"})) {
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
    script += "\n";
}

std::string trimCopy(std::string s);
bool isIdentChar(char c);

// epat++'s path language has no function-call expression. Feeding a C call to
// its parser can abort the process before an exception can be reported. Keep
// the caller's assignment/write in the direct summary and let the existing
// function-summary composition add the callee cost.
std::string abstractCallForEpat(const std::string& line) {
    const size_t assign = line.find('=');
    if (assign != std::string::npos) {
        size_t name = assign + 1;
        while (name < line.size() && std::isspace(static_cast<unsigned char>(line[name]))) ++name;
        if (name < line.size() &&
            (std::isalpha(static_cast<unsigned char>(line[name])) || line[name] == '_')) {
            size_t end = name + 1;
            while (end < line.size() && isIdentChar(line[end])) ++end;
            size_t open = end;
            while (open < line.size() && std::isspace(static_cast<unsigned char>(line[open]))) ++open;
            if (open < line.size() && line[open] == '(') {
                return line.substr(0, assign + 1) + " 0;";
            }
        }
    }
    const std::string trimmed = trimCopy(line);
    if (trimmed.rfind("return ", 0) == 0 && trimmed.find('(') != std::string::npos) {
        return "return 0;";
    }
    return "";
}

bool isSafePrefixLine(const std::string& line) {
    if (line.empty()) {
        return false;
    }
    if (line.find("typedef") != std::string::npos ||
        line.find("struct ") != std::string::npos ||
        line.find("union ") != std::string::npos ||
        line.find("enum ") != std::string::npos ||
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
            out += "\n";
        } else if (envEnabled("EPPATHER_DEBUG_CRASH_TRACE") && !line.empty()) {
            std::cerr << "[EPAT_SAFE_PREFIX] skip unsupported prefix line: " << line << std::endl;
        }
    }
    return out;
}

std::string trimCopy(std::string s) {
    auto notSpace = [](unsigned char c) { return !std::isspace(c); };
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), notSpace));
    s.erase(std::find_if(s.rbegin(), s.rend(), notSpace).base(), s.end());
    return s;
}

bool isIdentChar(char c) {
    return std::isalnum(static_cast<unsigned char>(c)) || c == '_';
}

// Normalize standard C increment/compound updates to the small assignment
// language accepted by epat++. This keeps the source CFG unchanged while making
// loop-summary and path-feasibility handling agree for i++, ++i, i += k, etc.
std::string normalizeLoopUpdateForEpat(const std::string& raw) {
    const std::string line = trimCopy(raw);
    std::smatch m;
    static const std::regex postfix(
        "^([A-Za-z_][A-Za-z0-9_]*)[[:space:]]*(\\+\\+|--)[[:space:]]*;?$");
    static const std::regex prefix(
        "^(\\+\\+|--)[[:space:]]*([A-Za-z_][A-Za-z0-9_]*)[[:space:]]*;?$");
    static const std::regex compound(
        "^([A-Za-z_][A-Za-z0-9_]*)[[:space:]]*(\\+=|-=)[[:space:]]*"
        "([0-9]+)[[:space:]]*;?$");
    if (std::regex_match(line, m, postfix)) {
        const std::string op = m[2].str() == "++" ? " + 1" : " - 1";
        return m[1].str() + " = " + m[1].str() + op;
    }
    if (std::regex_match(line, m, prefix)) {
        const std::string op = m[1].str() == "++" ? " + 1" : " - 1";
        return m[2].str() + " = " + m[2].str() + op;
    }
    if (std::regex_match(line, m, compound)) {
        const std::string op = m[2].str() == "+=" ? " + " : " - ";
        return m[1].str() + " = " + m[1].str() + op + m[3].str();
    }
    return line;
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
        const char prev = (i > 0 ? line[i - 1] : '\0');
        const char next = (i + 1 < line.size() ? line[i + 1] : '\0');
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

}  // namespace

EpatRunner::EpatRunner(std::string prefix) : prefix_(sanitizePrefixForEpat(prefix)) {
    if (!prefix_.empty() && prefix_.back() != '\n') prefix_.push_back('\n');
}

std::string EpatRunner::render(const std::vector<PathDecision>& decisions) const {
    std::string script = prefix_;

    for (const auto& step : decisions) {
        if (!step.node) continue;
        switch (step.kind) {
            case PathDecisionKind::LoopInit: {
                const auto& init = step.node->initstmt_str;
                if (!init.empty() && init != ";") {
                    appendSafeLine(script, init, true);
                }
                break;
            }
            case PathDecisionKind::TrueBranch: {
                if (!step.node->cond_str.empty()) {
                    if (!envEnabled("EPPATHER_EPAT_SAFE_RENDER") || !probablyUnsafeForEpat(step.node->cond_str)) {
                        script += "@(" + step.node->cond_str + ");\n";
                    }
                }
                break;
            }
            case PathDecisionKind::FalseBranch: {
                if (!step.node->cond_str.empty()) {
                    if (!envEnabled("EPPATHER_EPAT_SAFE_RENDER") || !probablyUnsafeForEpat(step.node->cond_str)) {
                        script += "@(!(" + step.node->cond_str + "));\n";
                    }
                }
                break;
            }
            case PathDecisionKind::LoopUpdate: {
                if (!step.node->expr_str.empty()) {
                    appendSafeLine(script, normalizeLoopUpdateForEpat(step.node->expr_str), true);
                }
                break;
            }
            case PathDecisionKind::Code:
            default: {
                auto code = step.node->getCode();
                if (!code.empty()) {
                    if (step.node->hasCallExpr) {
                        code = abstractCallForEpat(code);
                    }
                    if (!code.empty()) {
                        appendSafeLine(script, code, false);
                    }
                }
                break;
            }
        }
    }

    return script;
}

EpatResult EpatRunner::solveScript(const std::string& script) const {
    if (envEnabled("EPPATHER_DEBUG_EPAT_SCRIPT")) {
        std::cerr << "[EPAT_SCRIPT_BEGIN]\n" << script << "\n[EPAT_SCRIPT_END]" << std::endl;
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
}

EpatResult EpatRunner::solve(const std::vector<PathDecision>& decisions) const {
    EpatResult result = solveScript(render(decisions));

    // Build exact source-level state transitions only after the concrete path
    // has been rendered. Early exits and truncated paths are rejected because
    // their observed iteration count differs from the closed-form trip count.
    std::unordered_map<CFGNode*, long long> observedIterations;
    std::vector<CFGNode*> order;
    for (const auto& decision : decisions) {
        if (!decision.node || !decision.node->isFor) {
            continue;
        }
        if (observedIterations.emplace(decision.node, 0).second) {
            order.push_back(decision.node);
        }
        if (decision.kind == PathDecisionKind::TrueBranch) {
            ++observedIterations[decision.node];
        }
    }
    for (CFGNode* loop : order) {
        const auto prediction = LoopBoundPredictor::predict(
            loop->initstmt_str, loop->cond_str, loop->expr_str,
            std::numeric_limits<int>::max());
        const long long observed = observedIterations[loop];
        if (!prediction.exact() || observed != prediction.iterations) {
            continue;
        }
        AffineLoopStateSummary summary;
        summary.variable = prediction.inductionVariable;
        summary.initialValue = prediction.start;
        summary.step = prediction.step;
        summary.iterations = observed;
        summary.finalValue = prediction.start + prediction.step * observed;
        summary.sourceRelation = summary.variable + "_out = " +
            std::to_string(summary.initialValue) + " + (" +
            std::to_string(summary.step) + " * " +
            std::to_string(summary.iterations) + ")";
        result.loopStateSummaries.push_back(std::move(summary));
    }
    return result;
}

}  // namespace C
}  // namespace psy
