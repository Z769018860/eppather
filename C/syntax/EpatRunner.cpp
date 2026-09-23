// Implementation of CFG-aware epat++ invocation utilities.
#include "EpatRunner.h"
#include <unordered_set>
#include <algorithm>
#include <stdexcept>
#include <sstream>
#include <regex>
#include <map>
#include <optional>

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

std::size_t boundedVlaCap() {
    constexpr std::size_t kDefault = 5;
    constexpr std::size_t kMaximum = 64;
    const char* raw = std::getenv("EPPATHER_VLA_MAX_ELEMENTS");
    if (!raw || !*raw) return kDefault;
    char* end = nullptr;
    const unsigned long parsed = std::strtoul(raw, &end, 10);
    if (end == raw || *end != '\0' || parsed == 0) return kDefault;
    return std::min<std::size_t>(parsed, kMaximum);
}

std::string normalizeBoundedVlaDeclaration(const std::string& line) {
    if (envEnabled("EPPATHER_DISABLE_BOUNDED_VLA")) return line;
    static const std::regex declarationPrefix(
        "^[[:space:]]*(?:const[[:space:]]+)?"
        "(?:unsigned[[:space:]]+|signed[[:space:]]+)?"
        "(?:int|long|short|char)[[:space:]]+");
    if (!std::regex_search(line, declarationPrefix)) return line;
    static const std::regex variableExtent(
        "\\[[[:space:]]*(?:[A-Za-z_][A-Za-z0-9_]*)?[[:space:]]*\\]");
    return std::regex_replace(
        line, variableExtent,
        "[" + std::to_string(boundedVlaCap()) + "]");
}

std::string normalizeBoundedVlaPrefix(const std::string& prefix) {
    std::stringstream input(prefix);
    std::string output;
    std::string line;
    while (std::getline(input, line)) {
        output += normalizeBoundedVlaDeclaration(line) + "\n";
    }
    return output;
}

std::unordered_map<std::string, std::size_t>
parseFixedOneDimensionalArrayExtents(const std::string& prefix) {
    std::unordered_map<std::string, std::size_t> out;
    std::stringstream input(prefix);
    std::string line;
    // Deliberately accept only simple one-dimensional fixed arrays from the
    // original source prefix. VLA, pointer, multi-dimensional and macro-sized
    // declarations remain unknown and are left to the later frame/alias proof.
    static const std::regex fixedArray(
        "^[ \\t]*(?:const[ \\t]+)?"
        "(?:(?:unsigned|signed)[ \\t]+)?"
        "(?:int|long|short|char)[ \\t]+"
        "([A-Za-z_][A-Za-z0-9_]*)[ \\t]*"
        "\\[[ \\t]*([0-9]+)[ \\t]*\\]"
        "[ \\t]*(?:;|=)");
    while (std::getline(input, line)) {
        std::smatch match;
        if (!std::regex_search(line, match, fixedArray)) continue;
        if (line.find('[', static_cast<std::size_t>(match.position(2) +
                                                    match.length(2))) !=
            std::string::npos) {
            continue;
        }
        try {
            const unsigned long long parsed =
                std::stoull(match[2].str());
            if (parsed == 0 ||
                parsed > std::numeric_limits<std::size_t>::max()) {
                continue;
            }
            out.emplace(
                match[1].str(), static_cast<std::size_t>(parsed));
        } catch (...) {
            continue;
        }
    }
    return out;
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
    script += normalizeBoundedVlaDeclaration(line);
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


std::map<std::string, std::pair<long long, long long>>
affineTransformMap(const std::vector<LoopSccAffineTransform>& transforms) {
    std::map<std::string, std::pair<long long, long long>> out;
    for (const auto& transform : transforms) {
        out[transform.variable] =
            std::make_pair(transform.scale, transform.offset);
    }
    return out;
}

bool sameAffineTransforms(
    const std::vector<LoopSccAffineTransform>& lhs,
    const std::vector<LoopSccAffineTransform>& rhs) {
    return affineTransformMap(lhs) == affineTransformMap(rhs);
}

LoopSccPhaseTrace buildLoopSccPhaseTrace(
    CFGNode* loop,
    const LoopSccGraphInfo& graph,
    const std::vector<PathDecision>& decisions) {
    LoopSccPhaseTrace trace;
    if (!loop) {
        trace.diagnostics.push_back("missing loop for phase trace");
        return trace;
    }
    trace.loopCondition = loop->cond_str;
    if (!graph.complete) {
        trace.diagnostics.push_back(
            "SPath graph incomplete; phase trace is not trusted");
        return trace;
    }

    std::vector<std::vector<std::string>> iterationGuards;
    std::vector<std::string> currentGuards;
    std::vector<CFGNode*> nestedLoopStack;
    bool active = false;
    bool closedAtLoopHead = true;

    auto finishIteration = [&]() {
        if (!active) return;
        iterationGuards.push_back(currentGuards);
        currentGuards.clear();
        active = false;
    };

    for (const auto& decision : decisions) {
        if (!decision.node) continue;
        if (decision.node == loop) {
            if (decision.kind == PathDecisionKind::TrueBranch) {
                if (active) finishIteration();
                active = true;
                closedAtLoopHead = true;
                currentGuards.push_back("T: " + loop->cond_str);
            } else if (decision.kind == PathDecisionKind::FalseBranch) {
                if (active) finishIteration();
                closedAtLoopHead = true;
            }
            continue;
        }

        if (!active) continue;

        // The structural adapter may have summarized a nested loop inside-out.
        // While matching the outer concrete path, hide every decision made
        // inside that nested loop so the observed guard sequence corresponds
        // to the summarized outer SPath rather than the raw nested expansion.
        if (!nestedLoopStack.empty()) {
            if (decision.node->isLoop &&
                decision.node != loop &&
                decision.kind == PathDecisionKind::TrueBranch &&
                decision.node != nestedLoopStack.back()) {
                nestedLoopStack.push_back(decision.node);
                continue;
            }
            if (decision.node == nestedLoopStack.back() &&
                decision.kind == PathDecisionKind::FalseBranch) {
                nestedLoopStack.pop_back();
                continue;
            }
            continue;
        }
        if (decision.node->isLoop && decision.node != loop) {
            if (decision.kind == PathDecisionKind::TrueBranch) {
                nestedLoopStack.push_back(decision.node);
            }
            continue;
        }

        if ((decision.kind == PathDecisionKind::TrueBranch ||
             decision.kind == PathDecisionKind::FalseBranch) &&
            decision.node->isCondition) {
            currentGuards.push_back(
                std::string(
                    decision.kind == PathDecisionKind::TrueBranch
                        ? "T: " : "F: ") +
                decision.node->cond_str);
        }
        closedAtLoopHead = false;
    }

    // A path ending inside the loop (return/break/truncation) has no following
    // loop-head decision proving completion of the last iteration.
    if (active) {
        finishIteration();
        closedAtLoopHead = false;
    }

    for (const auto& guards : iterationGuards) {
        std::size_t matched = graph.spaths.size();
        std::size_t matches = 0;
        for (std::size_t i = 0; i < graph.spaths.size(); ++i) {
            if (graph.spaths[i].guards == guards) {
                matched = i;
                ++matches;
            }
        }
        if (matches != 1) {
            trace.diagnostics.push_back(
                matches == 0
                    ? "observed iteration did not match any SPath"
                    : "observed iteration matched multiple SPaths");
            return trace;
        }
        trace.spathSequence.push_back(matched);
    }

    trace.observedIterations = trace.spathSequence.size();
    trace.complete = closedAtLoopHead;
    if (!trace.complete || trace.spathSequence.empty()) {
        if (trace.spathSequence.empty())
            trace.diagnostics.push_back("no completed loop iteration observed");
        return trace;
    }

    for (std::size_t cycleIndex = 0;
         cycleIndex < graph.cycles.size(); ++cycleIndex) {
        const auto& cycle = graph.cycles[cycleIndex];
        if (!cycle.determinate || cycle.spathOrder.empty()) continue;

        auto first = std::find(
            cycle.spathOrder.begin(), cycle.spathOrder.end(),
            trace.spathSequence.front());
        if (first == cycle.spathOrder.end()) continue;
        const std::size_t entry = static_cast<std::size_t>(
            std::distance(cycle.spathOrder.begin(), first));

        bool matchesCycle = true;
        for (std::size_t i = 0; i < trace.spathSequence.size(); ++i) {
            const std::size_t expected =
                cycle.spathOrder[(entry + i) % cycle.spathOrder.size()];
            if (trace.spathSequence[i] != expected) {
                matchesCycle = false;
                break;
            }
        }
        if (!matchesCycle) continue;

        trace.matchedDeterminateCycle = true;
        trace.cycleIndex = cycleIndex;
        trace.period = cycle.period;
        trace.entryPhase = entry;
        trace.completePeriods =
            trace.period == 0 ? 0 : trace.observedIterations / trace.period;
        trace.residualPhases =
            trace.period == 0 ? trace.observedIterations
                              : trace.observedIterations % trace.period;

        // Compose the exact machine-readable SPath transforms in the concrete
        // phase order. Missing entries are identity transforms for that SPath.
        // The cycle-level candidate gate already excludes unknown/memory writes.
        std::map<std::string, std::pair<long long, long long>> composed;
        for (std::size_t pathId : trace.spathSequence) {
            if (pathId >= graph.spaths.size()) {
                trace.diagnostics.push_back(
                    "phase trace refers to an out-of-range SPath");
                trace.pathAffineTransforms.clear();
                return trace;
            }
            for (const auto& relation : graph.spaths[pathId].affineTransforms) {
                auto inserted = composed.emplace(
                    relation.variable, std::make_pair(1LL, 0LL));
                auto& current = inserted.first->second;
                current.second =
                    relation.scale * current.second + relation.offset;
                current.first = relation.scale * current.first;
            }
        }
        for (const auto& entry : composed) {
            trace.pathAffineTransforms.push_back(
                LoopSccAffineTransform{
                    entry.first, entry.second.first, entry.second.second});
        }

        // The acceleration plan is derived independently from the proved trip
        // count and T^k composition. Accept it only if the concrete unfolded
        // path reaches the same entry phase, consumes the same exact number of
        // iterations, and yields the same scalar relation. This is the A/B
        // gate before any future DFS shortcut is allowed to use the plan.
        for (std::size_t planIndex = 0;
             planIndex < graph.accelerationPlans.size(); ++planIndex) {
            const auto& plan = graph.accelerationPlans[planIndex];
            if (!plan.exact ||
                plan.cycleIndex != cycleIndex ||
                plan.entryPhase != entry ||
                plan.totalIterations !=
                    static_cast<long long>(trace.observedIterations)) {
                continue;
            }
            if (!sameAffineTransforms(
                    plan.closedFormTransforms,
                    trace.pathAffineTransforms)) {
                trace.diagnostics.push_back(
                    "symbolic acceleration plan disagrees with unfolded path");
                continue;
            }
            trace.matchedAccelerationPlan = true;
            trace.accelerationPlanIndex = planIndex;
            trace.accelerationTransforms =
                plan.closedFormTransforms;
            break;
        }
        if (!graph.accelerationPlans.empty() &&
            !trace.matchedAccelerationPlan) {
            trace.diagnostics.push_back(
                "no symbolic acceleration plan matched the unfolded path");
        }
        return trace;
    }

    trace.diagnostics.push_back(
        "observed SPath sequence does not follow a determinate cycle");
    return trace;
}

std::string renderAccelerationAssignment(
    const LoopSccAffineTransform& transform) {
    std::ostringstream os;
    os << transform.variable << " = ";
    if (transform.scale == 0) {
        os << transform.offset;
    } else if (transform.scale == 1) {
        os << transform.variable;
        if (transform.offset > 0) os << " + " << transform.offset;
        else if (transform.offset < 0) os << " - " << -transform.offset;
    } else if (transform.scale == -1) {
        os << "0 - " << transform.variable;
        if (transform.offset > 0) os << " + " << transform.offset;
        else if (transform.offset < 0) os << " - " << -transform.offset;
    } else {
        os << transform.scale << " * " << transform.variable;
        if (transform.offset > 0) os << " + " << transform.offset;
        else if (transform.offset < 0) os << " - " << -transform.offset;
    }
    os << ";";
    return os.str();
}

std::optional<std::vector<PathDecision>>
buildAccelerationValidationDecisions(
    CFGNode* loop,
    const LoopSccGraphInfo& graph,
    const LoopSccPhaseTrace& trace,
    const std::vector<PathDecision>& decisions) {
    if (!loop || !trace.matchedAccelerationPlan ||
        trace.accelerationPlanIndex >= graph.accelerationPlans.size()) {
        return std::nullopt;
    }

    std::size_t firstTrue = decisions.size();
    std::size_t finalFalse = decisions.size();
    for (std::size_t i = 0; i < decisions.size(); ++i) {
        if (decisions[i].node != loop) continue;
        if (decisions[i].kind == PathDecisionKind::TrueBranch &&
            firstTrue == decisions.size()) {
            firstTrue = i;
        } else if (firstTrue != decisions.size() &&
                   decisions[i].kind == PathDecisionKind::FalseBranch) {
            finalFalse = i;
        }
    }
    if (firstTrue == decisions.size() ||
        finalFalse == decisions.size() ||
        finalFalse <= firstTrue) {
        return std::nullopt;
    }

    std::vector<PathDecision> prefix(
        decisions.begin(),
        decisions.begin() + static_cast<std::ptrdiff_t>(firstTrue));
    auto compressed = buildLoopSccAccelerationDecisions(
        prefix, loop, graph, trace.accelerationPlanIndex);
    if (!compressed) return std::nullopt;

    compressed->insert(
        compressed->end(),
        decisions.begin() + static_cast<std::ptrdiff_t>(finalFalse + 1),
        decisions.end());
    return compressed;
}

std::string renderMemoryCellAssignment(
    const LoopSccMemoryCellTransform& transform) {
    std::ostringstream os;
    const std::string cell =
        transform.region + "[" + std::to_string(transform.index) + "]";
    os << cell << " = ";
    if (transform.scale == 0) {
        os << transform.offset;
    } else if (transform.scale == 1) {
        os << cell;
        if (transform.offset > 0) os << " + " << transform.offset;
        else if (transform.offset < 0) os << " - " << -transform.offset;
    } else if (transform.scale == -1) {
        os << "0 - " << cell;
        if (transform.offset > 0) os << " + " << transform.offset;
        else if (transform.offset < 0) os << " - " << -transform.offset;
    } else {
        os << transform.scale << " * " << cell;
        if (transform.offset > 0) os << " + " << transform.offset;
        else if (transform.offset < 0) os << " - " << -transform.offset;
    }
    os << ";";
    return os.str();
}

std::optional<std::vector<PathDecision>>
buildMemorySummaryValidationDecisions(
    CFGNode* loop,
    const LoopSccGraphInfo& graph,
    const LoopSccMemorySummaryCandidate& candidate,
    const std::vector<PathDecision>& decisions,
    std::size_t& compressedSummaryMems) {
    compressedSummaryMems = 0;
    if (!loop || !candidate.exact ||
        candidate.cycleIndex >= graph.cycles.size()) {
        return std::nullopt;
    }
    const auto& cycle = graph.cycles[candidate.cycleIndex];
    if (!cycle.phaseGuardsProved ||
        candidate.entryPhase >= cycle.spathOrder.size()) {
        return std::nullopt;
    }

    std::size_t firstTrue = decisions.size();
    std::size_t finalFalse = decisions.size();
    for (std::size_t i = 0; i < decisions.size(); ++i) {
        if (decisions[i].node != loop) continue;
        if (decisions[i].kind == PathDecisionKind::TrueBranch &&
            firstTrue == decisions.size()) {
            firstTrue = i;
        } else if (firstTrue != decisions.size() &&
                   decisions[i].kind == PathDecisionKind::FalseBranch) {
            finalFalse = i;
        }
    }
    if (firstTrue == decisions.size() ||
        finalFalse == decisions.size() ||
        finalFalse <= firstTrue) {
        return std::nullopt;
    }

    std::vector<PathDecision> out(
        decisions.begin(),
        decisions.begin() + static_cast<std::ptrdiff_t>(firstTrue));
    out.push_back(PathDecision{
        loop, PathDecisionKind::TrueBranch, {}});

    const std::size_t entryPathId =
        cycle.spathOrder[candidate.entryPhase];
    if (entryPathId >= graph.spaths.size()) return std::nullopt;
    const auto& entryPath = graph.spaths[entryPathId];
    const std::string loopTrue = "T: " + loop->cond_str;
    for (const auto& guard : entryPath.guards) {
        if (guard == loopTrue) continue;
        if (guard.rfind("T: ", 0) == 0) {
            out.push_back(PathDecision{
                loop, PathDecisionKind::SyntheticAssume,
                guard.substr(3)});
        } else if (guard.rfind("F: ", 0) == 0) {
            out.push_back(PathDecision{
                loop, PathDecisionKind::SyntheticAssume,
                "!(" + guard.substr(3) + ")"});
        } else {
            return std::nullopt;
        }
    }

    for (const auto& transform :
         candidate.scalarClosedFormTransforms) {
        out.push_back(PathDecision{
            loop, PathDecisionKind::SyntheticCode,
            renderAccelerationAssignment(transform)});
    }
    for (const auto& transform :
         candidate.closedFormTransforms) {
        const auto code = renderMemoryCellAssignment(transform);
        compressedSummaryMems += static_cast<std::size_t>(
            estimateMemsFromLine(code));
        out.push_back(PathDecision{
            loop, PathDecisionKind::SyntheticCode, code});
    }

    out.push_back(PathDecision{
        loop, PathDecisionKind::FalseBranch, {}});
    out.insert(
        out.end(),
        decisions.begin() + static_cast<std::ptrdiff_t>(finalFalse + 1),
        decisions.end());
    return out;
}

}  // namespace

std::optional<std::vector<PathDecision>>
buildLoopSccAccelerationDecisions(
    const std::vector<PathDecision>& prefix,
    CFGNode* loop,
    const LoopSccGraphInfo& graph,
    std::size_t planIndex) {
    if (!loop || planIndex >= graph.accelerationPlans.size()) {
        return std::nullopt;
    }
    const auto& plan = graph.accelerationPlans[planIndex];
    if (!plan.exact || !plan.memsPreserving ||
        plan.skippableIterations != plan.totalIterations ||
        plan.cycleIndex >= graph.cycles.size()) {
        return std::nullopt;
    }
    const auto& cycle = graph.cycles[plan.cycleIndex];
    if (!cycle.phaseGuardsProved ||
        plan.entryPhase >= cycle.spathOrder.size()) {
        return std::nullopt;
    }

    std::vector<PathDecision> out = prefix;
    out.push_back(PathDecision{
        loop, PathDecisionKind::TrueBranch, {}});

    const std::size_t entryPathId =
        cycle.spathOrder[plan.entryPhase];
    if (entryPathId >= graph.spaths.size()) {
        return std::nullopt;
    }
    const auto& entryPath = graph.spaths[entryPathId];
    const std::string loopTrue = "T: " + loop->cond_str;
    for (const auto& guard : entryPath.guards) {
        if (guard == loopTrue) continue;
        if (guard.rfind("T: ", 0) == 0) {
            out.push_back(PathDecision{
                loop, PathDecisionKind::SyntheticAssume,
                guard.substr(3)});
        } else if (guard.rfind("F: ", 0) == 0) {
            out.push_back(PathDecision{
                loop, PathDecisionKind::SyntheticAssume,
                "!(" + guard.substr(3) + ")"});
        } else {
            return std::nullopt;
        }
    }

    for (const auto& transform : plan.closedFormTransforms) {
        out.push_back(PathDecision{
            loop, PathDecisionKind::SyntheticCode,
            renderAccelerationAssignment(transform)});
    }

    out.push_back(PathDecision{
        loop, PathDecisionKind::FalseBranch, {}});
    return out;
}


std::optional<LoopSccMemoryAccelerationDecisionPlan>
buildLoopSccMemoryAccelerationDecisions(
    const std::vector<PathDecision>& prefix,
    CFGNode* loop,
    const LoopSccGraphInfo& graph,
    std::size_t candidateIndex,
    const std::string& sourcePrefix) {
    if (!loop ||
        candidateIndex >= graph.memorySummaryCandidates.size()) {
        return std::nullopt;
    }
    const auto& candidate =
        graph.memorySummaryCandidates[candidateIndex];
    if (!candidate.exact || candidate.totalIterations <= 0 ||
        candidate.cycleIndex >= graph.cycles.size() ||
        candidate.closedFormTransforms.empty()) {
        return std::nullopt;
    }
    const auto& cycle = graph.cycles[candidate.cycleIndex];
    if (!cycle.determinate || !cycle.phaseGuardsProved ||
        cycle.period == 0 ||
        candidate.entryPhase >= cycle.spathOrder.size()) {
        return std::nullopt;
    }

    const auto extents =
        parseFixedOneDimensionalArrayExtents(sourcePrefix);
    for (const auto& transform : candidate.closedFormTransforms) {
        const auto extent = extents.find(transform.region);
        if (extent == extents.end() || transform.index < 0 ||
            static_cast<unsigned long long>(transform.index) >=
                static_cast<unsigned long long>(extent->second)) {
            return std::nullopt;
        }
    }

    LoopSccMemoryAccelerationDecisionPlan plan;
    plan.unfoldedMems = candidate.observedMems;
    plan.decisions = prefix;
    plan.decisions.push_back(PathDecision{
        loop, PathDecisionKind::TrueBranch, {}, 0});

    const std::size_t entryPathId =
        cycle.spathOrder[candidate.entryPhase];
    if (entryPathId >= graph.spaths.size()) return std::nullopt;
    const auto& entryPath = graph.spaths[entryPathId];
    const std::string loopTrue = "T: " + loop->cond_str;
    for (const auto& guard : entryPath.guards) {
        if (guard == loopTrue) continue;
        if (guard.rfind("T: ", 0) == 0) {
            plan.decisions.push_back(PathDecision{
                loop, PathDecisionKind::SyntheticAssume,
                guard.substr(3), 0});
        } else if (guard.rfind("F: ", 0) == 0) {
            plan.decisions.push_back(PathDecision{
                loop, PathDecisionKind::SyntheticAssume,
                "!(" + guard.substr(3) + ")", 0});
        } else {
            return std::nullopt;
        }
    }

    for (const auto& transform :
         candidate.scalarClosedFormTransforms) {
        plan.decisions.push_back(PathDecision{
            loop, PathDecisionKind::SyntheticCode,
            renderAccelerationAssignment(transform), 0});
    }
    for (const auto& transform :
         candidate.closedFormTransforms) {
        const std::string code =
            renderMemoryCellAssignment(transform);
        const int mems = estimateMemsFromLine(code);
        if (mems < 0) return std::nullopt;
        plan.compressedSummaryMems +=
            static_cast<std::size_t>(mems);
        plan.decisions.push_back(PathDecision{
            loop, PathDecisionKind::SyntheticCode, code, 0});
    }
    if (candidate.observedMems < plan.compressedSummaryMems) {
        return std::nullopt;
    }
    plan.compensationMems =
        candidate.observedMems - plan.compressedSummaryMems;
    if (plan.compensationMems >
        static_cast<std::size_t>(
            std::numeric_limits<long long>::max())) {
        return std::nullopt;
    }
    if (plan.compensationMems > 0) {
        plan.decisions.push_back(PathDecision{
            loop, PathDecisionKind::SyntheticMems, {},
            static_cast<long long>(plan.compensationMems)});
    }
    plan.decisions.push_back(PathDecision{
        loop, PathDecisionKind::FalseBranch, {}, 0});

    std::set<int> coverage;
    const long long fullPeriods =
        candidate.totalIterations /
        static_cast<long long>(cycle.period);
    const std::size_t residual =
        static_cast<std::size_t>(
            candidate.totalIterations %
            static_cast<long long>(cycle.period));
    if (fullPeriods > 0) {
        for (std::size_t pathId : cycle.spathOrder) {
            if (pathId >= graph.spaths.size()) return std::nullopt;
            coverage.insert(
                graph.spaths[pathId].coverageSlots.begin(),
                graph.spaths[pathId].coverageSlots.end());
        }
    }
    for (std::size_t r = 0; r < residual; ++r) {
        const std::size_t pathId =
            cycle.spathOrder[
                (candidate.entryPhase + r) % cycle.period];
        if (pathId >= graph.spaths.size()) return std::nullopt;
        coverage.insert(
            graph.spaths[pathId].coverageSlots.begin(),
            graph.spaths[pathId].coverageSlots.end());
    }
    if (loop->depth >= 0) {
        coverage.insert(2 * loop->depth + 1);
    }
    plan.coverageSlots.assign(coverage.begin(), coverage.end());
    return plan;
}

EpatRunner::EpatRunner(std::string prefix)
    : sourcePrefix_(prefix),
      prefix_(sanitizePrefixForEpat(normalizeBoundedVlaPrefix(prefix))) {
    if (!prefix_.empty() && prefix_.back() != '\n') prefix_.push_back('\n');
}

std::string EpatRunner::render(const std::vector<PathDecision>& decisions) const {
    std::string script = prefix_;

    for (const auto& step : decisions) {
        if (!step.node) continue;
        switch (step.kind) {
            case PathDecisionKind::SyntheticAssume: {
                if (!step.syntheticText.empty()) {
                    script += "@(" + step.syntheticText + ");\n";
                }
                break;
            }
            case PathDecisionKind::SyntheticCode: {
                if (!step.syntheticText.empty()) {
                    appendSafeLine(script, step.syntheticText, true);
                }
                break;
            }
            case PathDecisionKind::SyntheticMems: {
                // Cost-only compensation for a structurally certified
                // fixed-memory shortcut. It deliberately adds no SMT/source
                // semantics; solve() restores the exact skipped MEMS cost.
                break;
            }
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
    // Select only induction variables for SSA materialization.  This filter is
    // installed before epat++ evaluates the path, then cleared immediately;
    // ordinary scalar assignments retain the compact legacy representation.
    std::vector<std::string> provenanceVariables;
    std::unordered_set<CFGNode*> provenanceLoops;
    for (const auto& decision : decisions) {
        CFGNode* loop = decision.node;
        if (!loop || !loop->isLoop ||
            !provenanceLoops.insert(loop).second) {
            continue;
        }
        const auto prediction = LoopBoundPredictor::predict(
            loop->initstmt_str, loop->cond_str, loop->expr_str,
            std::numeric_limits<int>::max());
        if (prediction.exact() &&
            !prediction.inductionVariable.empty()) {
            provenanceVariables.push_back(prediction.inductionVariable);
        }
    }
    // Analyze the structural LoopSCC graph before invoking epat++ so state
    // variables participating in a proved scalar periodic candidate are also
    // materialized as SSA states. The relation is still only a candidate here;
    // VolCE performs the semantic entailment proof after solving the full path.
    std::unordered_map<CFGNode*, LoopSccGraphInfo> loopSccAnalysis;
    bool memoryProvenanceNeeded = false;
    if (envEnabled("EPPATHER_LOOP_SCC_ANALYZE")) {
        for (CFGNode* loop : provenanceLoops) {
            auto graph = LoopSccAdapter::analyze(loop);
            for (const auto& cycle : graph.cycles) {
                if (!cycle.guardedClosedFormCandidate) continue;
                for (const auto& relation : cycle.periodAffineTransforms) {
                    if (std::find(
                            provenanceVariables.begin(),
                            provenanceVariables.end(),
                            relation.variable) == provenanceVariables.end()) {
                        provenanceVariables.push_back(relation.variable);
                    }
                }
            }
            for (const auto& spath : graph.spaths) {
                if (!spath.memoryCellTransforms.empty()) {
                    memoryProvenanceNeeded = true;
                    break;
                }
            }
            loopSccAnalysis.emplace(loop, std::move(graph));
        }
    }

    // Array-indexed paths with multiple loops can create a large chain of
    // symbolic memory expressions.  Materializing every induction write on
    // those paths exceeded the bounded integration budget.  Keep their
    // existing compact encoding until memory-state provenance is available.
    if (provenanceLoops.size() > 1) {
        bool indexedMemory = false;
        for (const auto& decision : decisions) {
            if (!decision.node) continue;
            if (decision.node->getCode().find('[') != std::string::npos ||
                decision.node->cond_str.find('[') != std::string::npos) {
                indexedMemory = true;
                break;
            }
        }
        if (indexedMemory) provenanceVariables.clear();
    }
    epat::setSsaProvenanceVariables(provenanceVariables);
    epat::setMemorySsaProvenanceEnabled(memoryProvenanceNeeded);
    EpatResult result = solveScript(render(decisions));
    epat::setMemorySsaProvenanceEnabled(false);
    epat::clearSsaProvenanceVariables();

    long long syntheticMems = 0;
    bool syntheticMemsOverflow = false;
    for (const auto& decision : decisions) {
        if (decision.kind != PathDecisionKind::SyntheticMems) continue;
        if (decision.syntheticMems < 0 ||
            syntheticMems >
                std::numeric_limits<long long>::max() -
                    decision.syntheticMems) {
            syntheticMemsOverflow = true;
            break;
        }
        syntheticMems += decision.syntheticMems;
    }
    if (!syntheticMemsOverflow) {
        const long long compensated =
            static_cast<long long>(result.mem) + syntheticMems;
        if (compensated >= std::numeric_limits<int>::min() &&
            compensated <= std::numeric_limits<int>::max()) {
            result.mem = static_cast<int>(compensated);
        } else {
            syntheticMemsOverflow = true;
        }
    }
    if (syntheticMemsOverflow) {
        result.status = epat::result::unknown;
        result.loopStateSummaryDiagnostics.push_back(
            "loopscc: synthetic MEMS compensation overflow");
    }

    // Structural LoopSCC analysis remains opt-in. At this stage it also
    // exports a path-specific affine relation only for a concrete phase trace
    // that matches a proved guarded closed-form cycle. The relation is not
    // trusted by itself: it is transported to VolCE for SMT entailment.
    if (envEnabled("EPPATHER_LOOP_SCC_ANALYZE")) {
        for (CFGNode* loop : provenanceLoops) {
            auto found = loopSccAnalysis.find(loop);
            LoopSccGraphInfo graph =
                found != loopSccAnalysis.end()
                    ? std::move(found->second)
                    : LoopSccAdapter::analyze(loop);
            for (const auto& diagnostic : graph.diagnostics) {
                result.loopStateSummaryDiagnostics.push_back(
                    "loopscc: " + diagnostic);
            }
            auto trace = buildLoopSccPhaseTrace(loop, graph, decisions);
            if (trace.complete && trace.matchedDeterminateCycle &&
                trace.cycleIndex < graph.cycles.size() &&
                graph.cycles[trace.cycleIndex].guardedClosedFormCandidate) {
                const auto& relations =
                    trace.matchedAccelerationPlan
                        ? trace.accelerationTransforms
                        : trace.pathAffineTransforms;
                for (const auto& relation : relations) {
                    result.loopSccAffineStateSummaries.push_back(
                        LoopSccAffineStateSummary{
                            relation.variable,
                            relation.scale,
                            relation.offset,
                            trace.period,
                            trace.observedIterations});
                }
                if (trace.matchedAccelerationPlan) {
                    result.loopStateSummaryDiagnostics.push_back(
                        "loopscc: symbolic acceleration plan matched unfolded path");
                }
            }

            if (trace.complete && trace.matchedDeterminateCycle) {
                const auto fixedArrayExtents =
                    parseFixedOneDimensionalArrayExtents(sourcePrefix_);
                for (const auto& candidate :
                     graph.memorySummaryCandidates) {
                    if (!candidate.exact ||
                        candidate.cycleIndex != trace.cycleIndex ||
                        candidate.entryPhase != trace.entryPhase ||
                        candidate.totalIterations !=
                            static_cast<long long>(
                                trace.observedIterations)) {
                        continue;
                    }

                    bool fixedRegionBoundsOk = true;
                    for (const auto& relation :
                         candidate.closedFormTransforms) {
                        auto extent = fixedArrayExtents.find(
                            relation.region);
                        if (extent == fixedArrayExtents.end()) continue;
                        if (relation.index < 0 ||
                            static_cast<unsigned long long>(
                                relation.index) >=
                                static_cast<unsigned long long>(
                                    extent->second)) {
                            fixedRegionBoundsOk = false;
                            result.loopStateSummaryDiagnostics.push_back(
                                "loopscc: rejected fixed-cell summary outside declared local array region " +
                                relation.region + "[" +
                                std::to_string(relation.index) + "]");
                            break;
                        }
                    }
                    if (!fixedRegionBoundsOk) continue;

                    for (const auto& relation :
                         candidate.closedFormTransforms) {
                        result.loopSccMemoryCellStateSummaries.push_back(
                            LoopSccMemoryCellStateSummary{
                                relation.region,
                                relation.index,
                                relation.scale,
                                relation.offset,
                                candidate.period,
                                trace.observedIterations,
                                candidate.observedMems});
                    }
                    result.loopStateSummaryDiagnostics.push_back(
                        "loopscc: fixed-cell memory summary matched unfolded path");

                    if (envEnabled(
                            "EPPATHER_LOOP_SCC_ACCEL_VALIDATE")) {
                        LoopSccMemoryAccelerationValidation validation;
                        validation.loopCondition = loop->cond_str;
                        validation.attempted = true;
                        validation.originalDecisionCount =
                            decisions.size();
                        validation.unfoldedLoopMems =
                            candidate.observedMems;

                        std::size_t compressedSummaryMems = 0;
                        auto compressed =
                            buildMemorySummaryValidationDecisions(
                                loop, graph, candidate, decisions,
                                compressedSummaryMems);
                        if (compressed) {
                            validation.compressedDecisionCount =
                                compressed->size();
                            validation.compressedSummaryMems =
                                compressedSummaryMems;

                            epat::setSsaProvenanceVariables(
                                provenanceVariables);
                            epat::setMemorySsaProvenanceEnabled(true);
                            EpatResult compressedResult =
                                solveScript(render(*compressed));
                            epat::setMemorySsaProvenanceEnabled(false);
                            epat::clearSsaProvenanceVariables();

                            validation.baselineMem = result.mem;
                            validation.compressedMem =
                                compressedResult.mem;
                            validation.compressedSmt =
                                compressedResult.smt;
                            validation.statusMatched =
                                compressedResult.status == result.status;

                            if (candidate.observedMems >=
                                compressedSummaryMems) {
                                const long long compensated =
                                    static_cast<long long>(
                                        compressedResult.mem) +
                                    static_cast<long long>(
                                        candidate.observedMems -
                                        compressedSummaryMems);
                                if (compensated >=
                                        std::numeric_limits<int>::min() &&
                                    compensated <=
                                        std::numeric_limits<int>::max()) {
                                    validation.compensatedMem =
                                        static_cast<int>(compensated);
                                    validation.compensatedMemMatched =
                                        validation.compensatedMem ==
                                        result.mem;
                                }
                            }
                            validation.matched =
                                validation.statusMatched &&
                                validation.compensatedMemMatched &&
                                validation.compressedDecisionCount <
                                    validation.originalDecisionCount;
                            result.loopStateSummaryDiagnostics.push_back(
                                validation.matched
                                    ? "loopscc: compressed fixed-memory validation matched"
                                    : "loopscc: compressed fixed-memory validation mismatch");
                        } else {
                            result.loopStateSummaryDiagnostics.push_back(
                                "loopscc: failed to construct compressed fixed-memory path");
                        }
                        result.loopSccMemoryAccelerationValidations.push_back(
                            std::move(validation));
                    }
                }
            }

            if (envEnabled("EPPATHER_LOOP_SCC_ACCEL_VALIDATE") &&
                trace.matchedAccelerationPlan) {
                LoopSccAccelerationValidation validation;
                validation.loopCondition = loop->cond_str;
                validation.attempted = true;
                validation.originalDecisionCount = decisions.size();

                auto compressed =
                    buildAccelerationValidationDecisions(
                        loop, graph, trace, decisions);
                if (compressed) {
                    validation.compressedDecisionCount =
                        compressed->size();
                    epat::setSsaProvenanceVariables(
                        provenanceVariables);
                    EpatResult compressedResult =
                        solveScript(render(*compressed));
                    epat::clearSsaProvenanceVariables();

                    validation.baselineMem = result.mem;
                    validation.compressedMem =
                        compressedResult.mem;
                    validation.compressedSmt =
                        compressedResult.smt;
                    validation.statusMatched =
                        compressedResult.status == result.status;
                    validation.memMatched =
                        compressedResult.mem == result.mem;
                    validation.matched =
                        validation.statusMatched &&
                        validation.memMatched &&
                        validation.compressedDecisionCount <
                            validation.originalDecisionCount;
                    if (!validation.matched) {
                        result.loopStateSummaryDiagnostics.push_back(
                            "loopscc: compressed acceleration validation mismatch");
                    } else {
                        result.loopStateSummaryDiagnostics.push_back(
                            "loopscc: compressed acceleration validation matched");
                    }
                } else {
                    result.loopStateSummaryDiagnostics.push_back(
                        "loopscc: failed to construct compressed validation path");
                }
                result.loopSccAccelerationValidations.push_back(
                    std::move(validation));
            }

            result.loopSccPhaseTraces.push_back(std::move(trace));
            result.loopSccGraphs.push_back(std::move(graph));
        }
    }

    // Build exact source-level state transitions only after the concrete path
    // has been rendered. Early exits and truncated paths are rejected because
    // their observed iteration count differs from the closed-form trip count.
    std::unordered_map<CFGNode*, long long> observedIterations;
    std::unordered_map<CFGNode*, bool> observedExitCondition;
    std::vector<CFGNode*> order;
    for (const auto& decision : decisions) {
        if (!decision.node || !decision.node->isLoop) {
            continue;
        }
        if (observedIterations.emplace(decision.node, 0).second) {
            order.push_back(decision.node);
        }
        if (decision.kind == PathDecisionKind::TrueBranch) {
            ++observedIterations[decision.node];
        } else if (decision.kind == PathDecisionKind::FalseBranch) {
            observedExitCondition[decision.node] = true;
        }
    }
    for (CFGNode* loop : order) {
        if (!loop->isFor &&
            (loop->initstmt_str.empty() || loop->expr_str.empty())) {
            result.loopStateSummaryDiagnostics.push_back(
                "skipped: while-loop lacks initializer/update metadata");
            continue;
        }
        const auto prediction = LoopBoundPredictor::predict(
            loop->initstmt_str, loop->cond_str, loop->expr_str,
            std::numeric_limits<int>::max());
        const long long observed = observedIterations[loop];
        if (!prediction.exact()) {
            result.loopStateSummaryDiagnostics.push_back(
                "skipped " + loop->cond_str + ": " + prediction.reason);
            continue;
        }
        if (observed != prediction.iterations) {
            const bool sawExit = observedExitCondition[loop];
            result.loopStateSummaryDiagnostics.push_back(
                "skipped " + prediction.inductionVariable + ": observed " +
                std::to_string(observed) + " of " +
                std::to_string(prediction.iterations) +
                (sawExit ? " iterations (condition exited early)"
                         : " iterations (break/return or truncated path)"));
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
