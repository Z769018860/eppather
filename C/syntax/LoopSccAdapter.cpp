#include "LoopSccAdapter.h"

#include <algorithm>
#include <cctype>
#include <climits>
#include <cstdlib>
#include <functional>
#include <limits>
#include <map>
#include <regex>
#include <set>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#include "SyntaxNamePrinter.h"
#include "LoopBoundPredictor.h"

namespace psy {
namespace C {
namespace {

constexpr long long kNegInf = LLONG_MIN / 4;
constexpr long long kPosInf = LLONG_MAX / 4;

std::string trim(std::string text) {
    auto notSpace = [](unsigned char c) { return std::isspace(c) == 0; };
    auto first = std::find_if(text.begin(), text.end(), notSpace);
    auto last = std::find_if(text.rbegin(), text.rend(), notSpace).base();
    if (first >= last) return {};
    return std::string(first, last);
}

struct Interval {
    long long lower{kNegInf};
    long long upper{kPosInf};

    bool empty() const { return lower > upper; }
};

struct AffineTransform {
    // x' = scale * x + offset. The structural adapter currently supports
    // scale -1, 0, or 1. Scale -1 is needed for sign-flipping periodic
    // oscillations such as x' = -x - 1.
    long long scale{1};
    long long offset{0};
    bool exact{true};
};

struct GuardConstraint {
    std::string variable;
    Interval interval;
    bool recognized{false};
};

struct BuiltPath {
    LoopSccSPathInfo info;
    std::map<std::string, Interval> guardIntervals;
    std::map<std::string, AffineTransform> transforms;
    std::map<std::pair<std::string, long long>, AffineTransform>
        memoryTransforms;
    std::set<std::string> unknownWrites;
};

void observeMemoryAccess(BuiltPath& path,
                         const std::string& raw,
                         bool conditionContext = false) {
    const std::string text = trim(raw);
    if (text.empty()) return;

    LoopSccMemoryAccessInfo access;
    access.sourceText = text;
    access.arraySubscripts = static_cast<std::size_t>(
        std::count(text.begin(), text.end(), '['));

    // Count only conservative unary-dereference forms. Multiplication such as
    // i * 4 is intentionally excluded.
    static const std::regex derefRe(
        R"((^|[ \t=(:,!~?;+&|/-])[ \t]*\*[ \t]*([A-Za-z_]|\())");
    for (std::sregex_iterator it(text.begin(), text.end(), derefRe), end;
         it != end; ++it) {
        ++access.pointerDereferences;
    }

    // A star outside the recognized unary forms is either multiplication or a
    // pointer expression outside this restricted observer. Pure arithmetic is
    // safe to ignore; otherwise retain the observation as imprecise.
    if (text.find('*') != std::string::npos &&
        access.pointerDereferences == 0) {
        static const std::regex multiplicationOnly(
            R"(^[A-Za-z0-9_[:space:]()+-*/%<>=!&|]+$)");
        if (!std::regex_match(text, multiplicationOnly)) {
            access.precise = false;
        }
    }

    if (!conditionContext) {
        const auto eq = text.find('=');
        if (eq != std::string::npos) {
            const std::string lhs = trim(text.substr(0, eq));
            access.writesMemory =
                lhs.find('[') != std::string::npos ||
                (!lhs.empty() && lhs.front() == '*');
        }
    }

    if (access.mems() == 0 && !access.writesMemory && access.precise) {
        return;
    }
    path.info.observedMems += access.mems();
    path.info.memoryAccessModelComplete =
        path.info.memoryAccessModelComplete && access.precise;
    path.info.writesMemory =
        path.info.writesMemory || access.writesMemory;
    path.info.memoryAccesses.push_back(std::move(access));
}

long long clampAdd(long long value, long long delta) {
    if (value <= kNegInf / 2 || value >= kPosInf / 2) return value;
    if (delta > 0 && value > kPosInf - delta) return kPosInf;
    if (delta < 0 && value < kNegInf - delta) return kNegInf;
    return value + delta;
}

std::string invertComparator(const std::string& op) {
    if (op == "<") return ">=";
    if (op == "<=") return ">";
    if (op == ">") return "<=";
    if (op == ">=") return "<";
    if (op == "==") return "!=";
    if (op == "!=") return "==";
    return {};
}

std::string reverseComparator(const std::string& op) {
    if (op == "<") return ">";
    if (op == "<=") return ">=";
    if (op == ">") return "<";
    if (op == ">=") return "<=";
    return op;
}

GuardConstraint parseGuard(const std::string& raw, bool truth) {
    std::string text = trim(raw);
    while (text.size() >= 2 && text.front() == '(' && text.back() == ')') {
        text = trim(text.substr(1, text.size() - 2));
    }

    static const std::regex direct(
        R"(^([A-Za-z_][A-Za-z0-9_]*)[[:space:]]*(<=|>=|==|!=|<|>)[[:space:]]*(-?[0-9]+)$)");
    static const std::regex reversed(
        R"(^(-?[0-9]+)[[:space:]]*(<=|>=|==|!=|<|>)[[:space:]]*([A-Za-z_][A-Za-z0-9_]*)$)");

    std::smatch match;
    std::string variable;
    std::string op;
    long long constant = 0;
    if (std::regex_match(text, match, direct)) {
        variable = match[1].str();
        op = match[2].str();
        constant = std::stoll(match[3].str());
    } else if (std::regex_match(text, match, reversed)) {
        constant = std::stoll(match[1].str());
        op = reverseComparator(match[2].str());
        variable = match[3].str();
    } else {
        return {};
    }

    if (!truth) op = invertComparator(op);
    GuardConstraint out;
    out.variable = variable;
    out.recognized = true;
    if (op == "<") {
        out.interval.upper = constant == LLONG_MIN ? kNegInf
                                                   : constant - 1;
    } else if (op == "<=") {
        out.interval.upper = constant;
    } else if (op == ">") {
        out.interval.lower = constant == LLONG_MAX ? kPosInf
                                                   : constant + 1;
    } else if (op == ">=") {
        out.interval.lower = constant;
    } else if (op == "==") {
        out.interval.lower = constant;
        out.interval.upper = constant;
    } else {
        // != cannot be represented by one interval. Keep the guard text, but
        // do not use it to remove SPath transitions.
        out.recognized = false;
    }
    return out;
}

void recordCoverageSlot(BuiltPath& path, int slot) {
    if (slot < 0) return;
    if (std::find(
            path.info.coverageSlots.begin(),
            path.info.coverageSlots.end(),
            slot) == path.info.coverageSlots.end()) {
        path.info.coverageSlots.push_back(slot);
    }
}

void addGuard(BuiltPath& path, const std::string& expr, bool truth,
              int depth = -1) {
    observeMemoryAccess(path, expr, true);
    path.info.guards.push_back(std::string(truth ? "T: " : "F: ") + expr);
    if (depth >= 0) {
        recordCoverageSlot(path, 2 * depth + (truth ? 0 : 1));
    }
    const auto parsed = parseGuard(expr, truth);
    if (!parsed.recognized) {
        path.info.guardModelComplete = false;
        return;
    }
    auto it = path.guardIntervals.find(parsed.variable);
    if (it == path.guardIntervals.end()) {
        path.guardIntervals.emplace(parsed.variable, parsed.interval);
        return;
    }
    it->second.lower = std::max(it->second.lower, parsed.interval.lower);
    it->second.upper = std::min(it->second.upper, parsed.interval.upper);
}

void recordWrite(BuiltPath& path, const std::string& variable) {
    if (variable.empty()) return;
    if (std::find(path.info.writes.begin(), path.info.writes.end(), variable) ==
        path.info.writes.end()) {
        path.info.writes.push_back(variable);
    }
}

void composeUpdate(BuiltPath& path,
                   const std::string& variable,
                   long long scale,
                   long long offset,
                   const std::string& sourceText) {
    recordWrite(path, variable);
    auto& current = path.transforms[variable];
    if (!current.exact) return;
    // new = scale * old_current + offset
    current.offset = scale * current.offset + offset;
    current.scale = scale * current.scale;
    std::ostringstream os;
    os << variable << "'=";
    if (current.scale == 0) {
        os << current.offset;
    } else {
        if (current.scale == -1) os << "-";
        os << variable;
        if (current.offset > 0) os << "+" << current.offset;
        else if (current.offset < 0) os << current.offset;
    }
    if (!sourceText.empty()) os << " [" << trim(sourceText) << "]";
    path.info.affineUpdates.push_back(os.str());
}

bool composeMemoryCellUpdate(
    BuiltPath& path,
    const std::string& region,
    long long index,
    long long scale,
    long long offset) {
    auto& current = path.memoryTransforms[{region, index}];
    if (!current.exact) return false;
    const __int128 nextScale =
        static_cast<__int128>(scale) * current.scale;
    const __int128 nextOffset =
        static_cast<__int128>(scale) * current.offset + offset;
    if (nextScale < std::numeric_limits<long long>::min() ||
        nextScale > std::numeric_limits<long long>::max() ||
        nextOffset < std::numeric_limits<long long>::min() ||
        nextOffset > std::numeric_limits<long long>::max()) {
        current.exact = false;
        return false;
    }
    current.scale = static_cast<long long>(nextScale);
    current.offset = static_cast<long long>(nextOffset);
    return true;
}

void markUnknownWrite(BuiltPath& path,
                      const std::string& variable,
                      const std::string& sourceText) {
    recordWrite(path, variable);
    path.unknownWrites.insert(variable);
    path.transforms.erase(variable);
    if (!sourceText.empty()) {
        path.info.affineUpdates.push_back(
            variable + "'=? [" + trim(sourceText) + "]");
    }
}

bool parseUpdate(BuiltPath& path, const std::string& raw) {
    observeMemoryAccess(path, raw, false);
    std::string text = trim(raw);
    if (text.empty()) return true;
    if (!text.empty() && text.back() == ';') text.pop_back();
    text = trim(text);

    std::smatch m;
    static const std::regex postfix(
        R"(^([A-Za-z_][A-Za-z0-9_]*)[[:space:]]*(\+\+|--)$)");
    static const std::regex prefix(
        R"(^(\+\+|--)[[:space:]]*([A-Za-z_][A-Za-z0-9_]*)$)");
    static const std::regex compound(
        R"(^([A-Za-z_][A-Za-z0-9_]*)[[:space:]]*(\+=|-=)[[:space:]]*(-?[0-9]+)$)");
    static const std::regex selfAdd(
        R"(^([A-Za-z_][A-Za-z0-9_]*)[[:space:]]*=[[:space:]]*\1[[:space:]]*([+-])[[:space:]]*([0-9]+)$)");
    static const std::regex selfNegate(
        R"(^([A-Za-z_][A-Za-z0-9_]*)[[:space:]]*=[[:space:]]*-[[:space:]]*\1(?:[[:space:]]*([+-])[[:space:]]*([0-9]+))?$)");
    static const std::regex zeroMinusSelf(
        R"(^([A-Za-z_][A-Za-z0-9_]*)[[:space:]]*=[[:space:]]*0[[:space:]]*-[[:space:]]*\1(?:[[:space:]]*([+-])[[:space:]]*([0-9]+))?$)");
    static const std::regex constantAssign(
        R"(^([A-Za-z_][A-Za-z0-9_]*)[[:space:]]*=[[:space:]]*(-?[0-9]+)$)");
    static const std::regex simpleAssign(
        R"(^([A-Za-z_][A-Za-z0-9_]*)[[:space:]]*=.*$)");

    if (std::regex_match(text, m, postfix)) {
        composeUpdate(path, m[1].str(), 1, m[2].str() == "++" ? 1 : -1, raw);
        return true;
    }
    if (std::regex_match(text, m, prefix)) {
        composeUpdate(path, m[2].str(), 1, m[1].str() == "++" ? 1 : -1, raw);
        return true;
    }
    if (std::regex_match(text, m, compound)) {
        long long value = std::stoll(m[3].str());
        if (m[2].str() == "-=") value = -value;
        composeUpdate(path, m[1].str(), 1, value, raw);
        return true;
    }
    if (std::regex_match(text, m, selfAdd)) {
        long long value = std::stoll(m[3].str());
        if (m[2].str() == "-") value = -value;
        composeUpdate(path, m[1].str(), 1, value, raw);
        return true;
    }
    if (std::regex_match(text, m, selfNegate) ||
        std::regex_match(text, m, zeroMinusSelf)) {
        long long value = 0;
        if (m[3].matched) {
            value = std::stoll(m[3].str());
            if (m[2].str() == "-") value = -value;
        }
        composeUpdate(path, m[1].str(), -1, value, raw);
        return true;
    }
    if (std::regex_match(text, m, constantAssign)) {
        composeUpdate(path, m[1].str(), 0, std::stoll(m[2].str()), raw);
        return true;
    }

    // Recognize a restricted constant-index memory transition. This only
    // records a candidate; the path remains acceleration-unsafe until an
    // alias-aware memory proof validates the source cell against canonical
    // VolCE memory regions.
    static const std::regex cellSelfAdd(
        R"(^([A-Za-z_][A-Za-z0-9_]*)[[:space:]]*\[[[:space:]]*(-?[0-9]+)[[:space:]]*\][[:space:]]*=[[:space:]]*([A-Za-z_][A-Za-z0-9_]*)[[:space:]]*\[[[:space:]]*(-?[0-9]+)[[:space:]]*\][[:space:]]*([+-])[[:space:]]*([0-9]+)$)");
    static const std::regex cellCompound(
        R"(^([A-Za-z_][A-Za-z0-9_]*)[[:space:]]*\[[[:space:]]*(-?[0-9]+)[[:space:]]*\][[:space:]]*(\+=|-=)[[:space:]]*(-?[0-9]+)$)");
    static const std::regex cellConstant(
        R"(^([A-Za-z_][A-Za-z0-9_]*)[[:space:]]*\[[[:space:]]*(-?[0-9]+)[[:space:]]*\][[:space:]]*=[[:space:]]*(-?[0-9]+)$)");

    if (std::regex_match(text, m, cellSelfAdd)) {
        const std::string lhsRegion = m[1].str();
        const long long lhsIndex = std::stoll(m[2].str());
        const std::string rhsRegion = m[3].str();
        const long long rhsIndex = std::stoll(m[4].str());
        if (lhsRegion == rhsRegion && lhsIndex == rhsIndex) {
            long long value = std::stoll(m[6].str());
            if (m[5].str() == "-") value = -value;
            if (!composeMemoryCellUpdate(
                    path, lhsRegion, lhsIndex, 1, value)) {
                path.info.memoryTransitionModelComplete = false;
            }
        } else {
            path.info.memoryTransitionModelComplete = false;
            path.info.memorySummaryEffectSafe = false;
        }
        recordWrite(path, "*memory*");
        path.unknownWrites.insert("*memory*");
        path.info.accelerationEffectSafe = false;
        return false;
    }
    if (std::regex_match(text, m, cellCompound)) {
        long long value = std::stoll(m[4].str());
        if (m[3].str() == "-=") value = -value;
        if (!composeMemoryCellUpdate(
                path, m[1].str(), std::stoll(m[2].str()), 1, value)) {
            path.info.memoryTransitionModelComplete = false;
        }
        recordWrite(path, "*memory*");
        path.unknownWrites.insert("*memory*");
        path.info.accelerationEffectSafe = false;
        return false;
    }
    if (std::regex_match(text, m, cellConstant)) {
        if (!composeMemoryCellUpdate(
                path, m[1].str(), std::stoll(m[2].str()),
                0, std::stoll(m[3].str()))) {
            path.info.memoryTransitionModelComplete = false;
        }
        recordWrite(path, "*memory*");
        path.unknownWrites.insert("*memory*");
        path.info.accelerationEffectSafe = false;
        return false;
    }

    // Other array/dereference writes are kept as an explicit unresolved
    // memory marker.
    if (text.find('=') != std::string::npos &&
        (text.find('[') != std::string::npos ||
         (!text.empty() && text.front() == '*'))) {
        path.info.memoryTransitionModelComplete = false;
        path.info.memorySummaryEffectSafe = false;
        recordWrite(path, "*memory*");
        path.unknownWrites.insert("*memory*");
        path.info.accelerationEffectSafe = false;
        return false;
    }

    if (std::regex_match(text, m, simpleAssign)) {
        markUnknownWrite(path, m[1].str(), raw);
        path.info.accelerationEffectSafe = false;
        path.info.memorySummaryEffectSafe = false;
        return false;
    }

    // Any remaining executable statement is outside the restricted scalar
    // affine semantics (for example a call, declaration with initializer,
    // pointer read, multiplication, or other side effect). Keep structural
    // SPath information, but never use such a path for acceleration.
    path.info.accelerationEffectSafe = false;
    path.info.memorySummaryEffectSafe = false;
    return false;
}

Interval applyTransform(const Interval& input, const AffineTransform& transform) {
    if (!transform.exact) return Interval{};
    if (transform.scale == 0) {
        return Interval{transform.offset, transform.offset};
    }
    if (transform.scale == 1) {
        return Interval{
            clampAdd(input.lower, transform.offset),
            clampAdd(input.upper, transform.offset)};
    }
    if (transform.scale == -1) {
        auto negateBound = [](long long value) {
            if (value <= kNegInf / 2) return kPosInf;
            if (value >= kPosInf / 2) return kNegInf;
            return -value;
        };
        return Interval{
            clampAdd(negateBound(input.upper), transform.offset),
            clampAdd(negateBound(input.lower), transform.offset)};
    }
    return Interval{};
}

bool disjoint(const Interval& lhs, const Interval& rhs) {
    return lhs.empty() || rhs.empty() ||
           lhs.upper < rhs.lower || rhs.upper < lhs.lower;
}

bool intervalSubset(const Interval& inner, const Interval& outer) {
    return !inner.empty() &&
           inner.lower >= outer.lower &&
           inner.upper <= outer.upper;
}

bool transitionGuaranteed(const BuiltPath& source,
                          const BuiltPath& target,
                          const std::string& loopControlVariable) {
    if (!source.info.guardModelComplete ||
        !target.info.guardModelComplete) {
        return false;
    }

    for (const auto& targetGuard : target.guardIntervals) {
        const std::string& variable = targetGuard.first;
        if (!loopControlVariable.empty() &&
            variable == loopControlVariable) {
            continue;
        }

        Interval after;
        auto sourceGuard = source.guardIntervals.find(variable);
        if (sourceGuard != source.guardIntervals.end()) {
            after = sourceGuard->second;
        }
        if (source.unknownWrites.count(variable) != 0) {
            return false;
        }
        auto transform = source.transforms.find(variable);
        if (transform != source.transforms.end()) {
            after = applyTransform(after, transform->second);
        }
        if (!intervalSubset(after, targetGuard.second)) {
            return false;
        }
    }
    return true;
}

bool transitionPossible(const BuiltPath& source, const BuiltPath& target) {
    if (!source.info.returnsToHeader) return false;
    for (const auto& targetGuard : target.guardIntervals) {
        const std::string& variable = targetGuard.first;
        auto sourceGuard = source.guardIntervals.find(variable);
        if (sourceGuard == source.guardIntervals.end()) continue;
        if (source.unknownWrites.count(variable) != 0) continue;

        Interval after = sourceGuard->second;
        auto transform = source.transforms.find(variable);
        if (transform != source.transforms.end()) {
            after = applyTransform(after, transform->second);
        }
        if (disjoint(after, targetGuard.second)) return false;
    }
    return true;
}

struct TarjanState {
    std::vector<int> index;
    std::vector<int> low;
    std::vector<int> stack;
    std::vector<bool> onStack;
    int nextIndex{0};
    std::vector<std::vector<int>> components;
};

void strongConnect(int v,
                   const std::vector<std::vector<int>>& graph,
                   TarjanState& state) {
    state.index[v] = state.low[v] = state.nextIndex++;
    state.stack.push_back(v);
    state.onStack[v] = true;

    for (int w : graph[v]) {
        if (state.index[w] == -1) {
            strongConnect(w, graph, state);
            state.low[v] = std::min(state.low[v], state.low[w]);
        } else if (state.onStack[w]) {
            state.low[v] = std::min(state.low[v], state.index[w]);
        }
    }

    if (state.low[v] != state.index[v]) return;
    std::vector<int> component;
    while (!state.stack.empty()) {
        int w = state.stack.back();
        state.stack.pop_back();
        state.onStack[w] = false;
        component.push_back(w);
        if (w == v) break;
    }
    state.components.push_back(std::move(component));
}

std::string renderPeriodTransform(const std::string& variable,
                                  const AffineTransform& transform) {
    std::ostringstream os;
    os << variable << "_after_period=";
    if (transform.scale == 0) {
        os << transform.offset;
    } else {
        if (transform.scale == -1) os << "-";
        os << variable;
        if (transform.offset > 0) os << "+" << transform.offset;
        else if (transform.offset < 0) os << transform.offset;
    }
    return os.str();
}

void detectDeterminateCycles(const std::vector<BuiltPath>& built,
                             const std::vector<std::vector<int>>& graph,
                             const std::vector<std::vector<int>>& components,
                             const std::vector<int>& componentOf,
                             LoopSccGraphInfo& result) {
    for (std::size_t cid = 0; cid < components.size(); ++cid) {
        const auto& component = components[cid];
        if (component.empty()) continue;

        bool cyclic = component.size() > 1;
        if (!cyclic && component.size() == 1) {
            const int node = component.front();
            cyclic = std::find(graph[node].begin(), graph[node].end(), node) !=
                     graph[node].end();
        }
        if (!cyclic) continue;

        bool determinate = result.complete;
        std::unordered_map<int, int> successor;
        std::unordered_map<int, int> predecessorCount;
        for (int node : component) predecessorCount[node] = 0;

        for (int node : component) {
            int internalSuccessor = -1;
            int internalCount = 0;
            for (int to : graph[node]) {
                if (componentOf[to] != static_cast<int>(cid)) {
                    // A periodic closed component may not have an escape edge.
                    determinate = false;
                    continue;
                }
                internalSuccessor = to;
                ++internalCount;
            }
            if (internalCount != 1) {
                determinate = false;
            } else {
                successor[node] = internalSuccessor;
                ++predecessorCount[internalSuccessor];
            }
        }
        for (const auto& entry : predecessorCount) {
            if (entry.second != 1) determinate = false;
        }
        if (!determinate) continue;

        const int start = *std::min_element(component.begin(), component.end());
        std::vector<std::size_t> order;
        std::unordered_set<int> visited;
        int current = start;
        for (std::size_t step = 0; step < component.size(); ++step) {
            if (!visited.insert(current).second) {
                determinate = false;
                break;
            }
            order.push_back(static_cast<std::size_t>(current));
            auto it = successor.find(current);
            if (it == successor.end()) {
                determinate = false;
                break;
            }
            current = it->second;
        }
        if (!determinate || current != start ||
            order.size() != component.size()) {
            continue;
        }

        LoopSccCycleInfo cycle;
        cycle.sccId = cid;
        cycle.spathOrder = order;
        cycle.period = order.size();
        cycle.determinate = true;

        std::set<std::string> touched;
        bool exact = true;
        for (std::size_t pathId : order) {
            if (!built[pathId].info.returnsToHeader) exact = false;
            if (!built[pathId].info.accelerationEffectSafe) {
                exact = false;
                cycle.diagnostics.push_back(
                    "opaque or memory effect prevents acceleration");
            }
            for (const auto& write : built[pathId].info.writes) {
                if (write == "*memory*") {
                    exact = false;
                    cycle.diagnostics.push_back(
                        "memory write prevents guarded closed form");
                } else {
                    touched.insert(write);
                }
            }
            if (!built[pathId].unknownWrites.empty()) {
                for (const auto& write : built[pathId].unknownWrites) {
                    if (write != "*memory*") {
                        cycle.diagnostics.push_back(
                            "non-affine write to " + write +
                            " prevents guarded closed form");
                    }
                }
                exact = false;
            }
        }

        for (const auto& variable : touched) {
            AffineTransform combined;
            for (std::size_t pathId : order) {
                auto it = built[pathId].transforms.find(variable);
                if (it == built[pathId].transforms.end()) continue;
                const auto& next = it->second;
                if (!next.exact) {
                    exact = false;
                    break;
                }
                combined.offset = next.scale * combined.offset + next.offset;
                combined.scale = next.scale * combined.scale;
            }
            if (exact) {
                cycle.periodAffineUpdates.push_back(
                    renderPeriodTransform(variable, combined));
                cycle.periodAffineTransforms.push_back(
                    LoopSccAffineTransform{
                        variable, combined.scale, combined.offset});
            }
        }

        cycle.guardedClosedFormCandidate =
            exact && !touched.empty() && result.complete;
        ++result.determinateCycleCount;
        if (cycle.period > 1) ++result.oscillatingCycleCount;
        if (cycle.guardedClosedFormCandidate) {
            ++result.guardedClosedFormCandidateCount;
        }
        result.cycles.push_back(std::move(cycle));
    }
}


bool checkedAffineCompose(const AffineTransform& after,
                          const AffineTransform& before,
                          AffineTransform& out) {
    if (!after.exact || !before.exact) return false;
    const __int128 scale =
        static_cast<__int128>(after.scale) * before.scale;
    const __int128 offset =
        static_cast<__int128>(after.scale) * before.offset +
        after.offset;
    if (scale < std::numeric_limits<long long>::min() ||
        scale > std::numeric_limits<long long>::max() ||
        offset < std::numeric_limits<long long>::min() ||
        offset > std::numeric_limits<long long>::max()) {
        return false;
    }
    out.scale = static_cast<long long>(scale);
    out.offset = static_cast<long long>(offset);
    out.exact = true;
    return true;
}

bool affinePower(AffineTransform base,
                 long long exponent,
                 AffineTransform& out) {
    if (exponent < 0 || !base.exact) return false;
    AffineTransform result;
    while (exponent > 0) {
        if ((exponent & 1LL) != 0) {
            AffineTransform next;
            if (!checkedAffineCompose(base, result, next)) return false;
            result = next;
        }
        exponent >>= 1;
        if (exponent == 0) break;
        AffineTransform squared;
        if (!checkedAffineCompose(base, base, squared)) return false;
        base = squared;
    }
    out = result;
    return true;
}

void provePhaseGuards(const std::vector<BuiltPath>& built,
                      LoopSccGraphInfo& result) {
    if (!result.complete || result.provedTripCount < 0 ||
        result.tripCountVariable.empty()) {
        return;
    }

    for (auto& cycle : result.cycles) {
        if (!cycle.determinate || cycle.spathOrder.empty()) {
            continue;
        }
        bool proved = true;
        for (std::size_t i = 0; i < cycle.spathOrder.size(); ++i) {
            const std::size_t from = cycle.spathOrder[i];
            const std::size_t to =
                cycle.spathOrder[(i + 1) % cycle.spathOrder.size()];
            if (from >= built.size() || to >= built.size() ||
                !transitionGuaranteed(
                    built[from], built[to],
                    result.tripCountVariable)) {
                proved = false;
                break;
            }
        }
        cycle.phaseGuardsProved = proved;
        if (!proved) {
            cycle.diagnostics.push_back(
                "phase guard inclusion proof failed; shortcut disabled");
        }
    }
}

void deriveMemorySummaryCandidates(
    const std::vector<BuiltPath>& built,
    LoopSccGraphInfo& result) {
    if (!result.complete || result.provedTripCount < 0) return;

    for (std::size_t cycleIndex = 0;
         cycleIndex < result.cycles.size(); ++cycleIndex) {
        const auto& cycle = result.cycles[cycleIndex];
        if (!cycle.determinate || !cycle.phaseGuardsProved ||
            cycle.period == 0 ||
            cycle.spathOrder.size() != cycle.period) {
            continue;
        }

        bool memoryModelComplete = true;
        std::set<std::pair<std::string, long long>> cells;
        std::set<std::string> scalarVariables;
        for (std::size_t pathId : cycle.spathOrder) {
            if (pathId >= built.size()) {
                memoryModelComplete = false;
                break;
            }
            const auto& path = built[pathId];
            if (!path.info.memoryTransitionModelComplete ||
                !path.info.memorySummaryEffectSafe) {
                memoryModelComplete = false;
                break;
            }
            if (path.info.writesMemory && path.memoryTransforms.empty()) {
                memoryModelComplete = false;
                break;
            }
            for (const auto& entry : path.memoryTransforms) {
                if (!entry.second.exact) {
                    memoryModelComplete = false;
                    break;
                }
                cells.insert(entry.first);
            }
            for (const auto& entry : path.transforms) {
                if (entry.second.exact) {
                    scalarVariables.insert(entry.first);
                }
            }
            if (!memoryModelComplete) break;
        }
        if (!memoryModelComplete || cells.empty()) continue;

        const long long fullPeriods =
            result.provedTripCount /
            static_cast<long long>(cycle.period);
        const std::size_t residual =
            static_cast<std::size_t>(
                result.provedTripCount %
                static_cast<long long>(cycle.period));

        for (std::size_t entryPhase = 0;
             entryPhase < cycle.period; ++entryPhase) {
            LoopSccMemorySummaryCandidate candidate;
            candidate.cycleIndex = cycleIndex;
            candidate.entryPhase = entryPhase;
            candidate.period = cycle.period;
            candidate.totalIterations = result.provedTripCount;
            bool exact = true;

            __int128 mems = 0;
            if (fullPeriods > 0) {
                std::size_t onePeriodMems = 0;
                for (std::size_t pathId : cycle.spathOrder) {
                    onePeriodMems += built[pathId].info.observedMems;
                }
                mems += static_cast<__int128>(onePeriodMems) *
                        fullPeriods;
            }
            for (std::size_t r = 0; r < residual; ++r) {
                const std::size_t pathId =
                    cycle.spathOrder[
                        (entryPhase + r) % cycle.period];
                mems += built[pathId].info.observedMems;
            }
            if (mems < 0 ||
                mems > std::numeric_limits<std::size_t>::max()) {
                exact = false;
            } else {
                candidate.observedMems =
                    static_cast<std::size_t>(mems);
            }

            for (const auto& cell : cells) {
                AffineTransform onePeriod;
                for (std::size_t step = 0;
                     step < cycle.period; ++step) {
                    const std::size_t pathId =
                        cycle.spathOrder[
                            (entryPhase + step) % cycle.period];
                    auto it = built[pathId].memoryTransforms.find(cell);
                    if (it == built[pathId].memoryTransforms.end()) {
                        continue;
                    }
                    AffineTransform next;
                    if (!checkedAffineCompose(
                            it->second, onePeriod, next)) {
                        exact = false;
                        break;
                    }
                    onePeriod = next;
                }
                if (!exact) break;

                AffineTransform accumulated;
                if (!affinePower(
                        onePeriod, fullPeriods, accumulated)) {
                    exact = false;
                    break;
                }
                for (std::size_t r = 0; r < residual; ++r) {
                    const std::size_t pathId =
                        cycle.spathOrder[
                            (entryPhase + r) % cycle.period];
                    auto it = built[pathId].memoryTransforms.find(cell);
                    if (it == built[pathId].memoryTransforms.end()) {
                        continue;
                    }
                    AffineTransform next;
                    if (!checkedAffineCompose(
                            it->second, accumulated, next)) {
                        exact = false;
                        break;
                    }
                    accumulated = next;
                }
                if (!exact) break;

                candidate.closedFormTransforms.push_back(
                    LoopSccMemoryCellTransform{
                        cell.first, cell.second,
                        accumulated.scale, accumulated.offset});
            }

            for (const auto& variable : scalarVariables) {
                AffineTransform onePeriod;
                for (std::size_t step = 0;
                     step < cycle.period; ++step) {
                    const std::size_t pathId =
                        cycle.spathOrder[
                            (entryPhase + step) % cycle.period];
                    auto it = built[pathId].transforms.find(variable);
                    if (it == built[pathId].transforms.end()) continue;
                    AffineTransform next;
                    if (!checkedAffineCompose(
                            it->second, onePeriod, next)) {
                        exact = false;
                        break;
                    }
                    onePeriod = next;
                }
                if (!exact) break;

                AffineTransform accumulated;
                if (!affinePower(
                        onePeriod, fullPeriods, accumulated)) {
                    exact = false;
                    break;
                }
                for (std::size_t r = 0; r < residual; ++r) {
                    const std::size_t pathId =
                        cycle.spathOrder[
                            (entryPhase + r) % cycle.period];
                    auto it = built[pathId].transforms.find(variable);
                    if (it == built[pathId].transforms.end()) continue;
                    AffineTransform next;
                    if (!checkedAffineCompose(
                            it->second, accumulated, next)) {
                        exact = false;
                        break;
                    }
                    accumulated = next;
                }
                if (!exact) break;
                candidate.scalarClosedFormTransforms.push_back(
                    LoopSccAffineTransform{
                        variable,
                        accumulated.scale,
                        accumulated.offset});
            }

            candidate.exact =
                exact && !candidate.closedFormTransforms.empty();
            if (!candidate.exact) {
                candidate.diagnostics.push_back(
                    "fixed-cell T^k composition failed");
            }
            result.memorySummaryCandidates.push_back(
                std::move(candidate));
        }
    }
}

void deriveAccelerationPlans(CFGNode* loop,
                             const std::vector<BuiltPath>& built,
                             LoopSccGraphInfo& result) {
    if (!result.complete || result.provedTripCount < 0) return;

    for (std::size_t cycleIndex = 0;
         cycleIndex < result.cycles.size(); ++cycleIndex) {
        const auto& cycle = result.cycles[cycleIndex];
        if (!cycle.determinate || !cycle.guardedClosedFormCandidate ||
            !cycle.phaseGuardsProved ||
            cycle.period == 0 ||
            cycle.spathOrder.size() != cycle.period) {
            continue;
        }

        const long long fullPeriods =
            result.provedTripCount /
            static_cast<long long>(cycle.period);
        const std::size_t residual =
            static_cast<std::size_t>(
                result.provedTripCount %
                static_cast<long long>(cycle.period));

        std::set<std::string> variables;
        bool memsPreserving = true;
        for (std::size_t pathId : cycle.spathOrder) {
            if (pathId >= built.size()) {
                variables.clear();
                memsPreserving = false;
                break;
            }
            memsPreserving =
                memsPreserving &&
                built[pathId].info.accelerationEffectSafe;
            for (const auto& entry : built[pathId].transforms)
                variables.insert(entry.first);
        }
        if (variables.empty()) continue;

        for (std::size_t entryPhase = 0;
             entryPhase < cycle.period; ++entryPhase) {
            LoopSccAccelerationPlan plan;
            plan.cycleIndex = cycleIndex;
            plan.entryPhase = entryPhase;
            plan.period = cycle.period;
            plan.totalIterations = result.provedTripCount;
            plan.completePeriods = fullPeriods;
            plan.residualPhases = residual;
            plan.memsPreserving = memsPreserving;
            // The closed form already composes complete periods plus the
            // proved residual phase sequence. When every participating SPath
            // is effect/MEMS-safe, the entire exact trip count is skippable.
            plan.skippableIterations = memsPreserving
                ? result.provedTripCount
                : 0;
            bool exact = true;

            for (std::size_t r = 0; r < residual; ++r) {
                plan.residualSPaths.push_back(
                    cycle.spathOrder[(entryPhase + r) % cycle.period]);
            }

            std::set<int> coverageSlots;
            if (fullPeriods > 0) {
                for (std::size_t pathId : cycle.spathOrder) {
                    if (pathId >= built.size()) {
                        exact = false;
                        break;
                    }
                    coverageSlots.insert(
                        built[pathId].info.coverageSlots.begin(),
                        built[pathId].info.coverageSlots.end());
                }
            }
            for (std::size_t pathId : plan.residualSPaths) {
                if (pathId >= built.size()) {
                    exact = false;
                    break;
                }
                coverageSlots.insert(
                    built[pathId].info.coverageSlots.begin(),
                    built[pathId].info.coverageSlots.end());
            }
            if (loop && loop->depth >= 0) {
                coverageSlots.insert(2 * loop->depth + 1);
            }
            plan.coverageSlots.assign(
                coverageSlots.begin(), coverageSlots.end());

            for (const auto& variable : variables) {
                AffineTransform onePeriod;
                for (std::size_t step = 0; step < cycle.period; ++step) {
                    const std::size_t pathId =
                        cycle.spathOrder[
                            (entryPhase + step) % cycle.period];
                    auto it = built[pathId].transforms.find(variable);
                    if (it == built[pathId].transforms.end()) continue;
                    AffineTransform next;
                    if (!checkedAffineCompose(
                            it->second, onePeriod, next)) {
                        exact = false;
                        break;
                    }
                    onePeriod = next;
                }
                if (!exact) break;

                AffineTransform accumulated;
                if (!affinePower(
                        onePeriod, fullPeriods, accumulated)) {
                    exact = false;
                    break;
                }

                for (std::size_t r = 0; r < residual; ++r) {
                    const std::size_t pathId =
                        cycle.spathOrder[
                            (entryPhase + r) % cycle.period];
                    auto it = built[pathId].transforms.find(variable);
                    if (it == built[pathId].transforms.end()) continue;
                    AffineTransform next;
                    if (!checkedAffineCompose(
                            it->second, accumulated, next)) {
                        exact = false;
                        break;
                    }
                    accumulated = next;
                }
                if (!exact) break;

                plan.closedFormTransforms.push_back(
                    LoopSccAffineTransform{
                        variable,
                        accumulated.scale,
                        accumulated.offset});
            }

            plan.exact = exact &&
                plan.memsPreserving &&
                !plan.closedFormTransforms.empty();
            if (!plan.exact) {
                plan.diagnostics.push_back(
                    "affine acceleration composition overflow/unsupported");
            }
            result.accelerationPlans.push_back(std::move(plan));
        }
    }
}

std::optional<LoopSccAccelerationPlan>
uniformInsideOutPlan(const LoopSccGraphInfo& nested, CFGNode* nestedLoop) {
    if (!nested.complete || nested.provedTripCount < 0 ||
        nested.accelerationPlans.empty()) {
        return std::nullopt;
    }

    auto normalizedTransforms = [](const LoopSccAccelerationPlan& plan) {
        std::map<std::string, std::pair<long long, long long>> out;
        for (const auto& transform : plan.closedFormTransforms) {
            out[transform.variable] =
                std::make_pair(transform.scale, transform.offset);
        }
        return out;
    };

    const LoopSccAccelerationPlan* representative = nullptr;
    std::map<std::string, std::pair<long long, long long>> reference;
    std::vector<int> referenceCoverage;
    for (const auto& plan : nested.accelerationPlans) {
        if (!plan.exact || !plan.memsPreserving ||
            plan.skippableIterations != plan.totalIterations ||
            plan.totalIterations != nested.provedTripCount) {
            return std::nullopt;
        }
        auto transforms = normalizedTransforms(plan);
        auto coverage = plan.coverageSlots;
        std::sort(coverage.begin(), coverage.end());
        if (!representative) {
            representative = &plan;
            reference = std::move(transforms);
            referenceCoverage = std::move(coverage);
            continue;
        }
        if (transforms != reference || coverage != referenceCoverage) {
            return std::nullopt;
        }
    }
    if (!representative || reference.empty()) return std::nullopt;

    LoopSccAccelerationPlan folded = *representative;

    // A for-loop initializer is executed each time the nested loop is entered.
    // The per-iteration SPath transform intentionally starts at the loop body,
    // so fold a constant induction initializer into the closed form before the
    // nested summary is composed into the outer SPath. Without this, a nested
    // "for (int j = 0; ...)" would incorrectly export j_out=j_entry+N.
    if (nestedLoop && nestedLoop->isFor &&
        !nestedLoop->initstmt_str.empty()) {
        std::smatch initMatch;
        static const std::regex initRe(
            R"((?:^|[;[:space:]])(?:[A-Za-z_][A-Za-z0-9_]*[[:space:]]+)*([A-Za-z_][A-Za-z0-9_]*)[[:space:]]*=[[:space:]]*(-?[0-9]+)[[:space:]]*;?$)");
        if (!std::regex_search(
                nestedLoop->initstmt_str, initMatch, initRe)) {
            return std::nullopt;
        }
        const std::string initVar = initMatch[1].str();
        const long long initValue =
            std::strtoll(initMatch[2].str().c_str(), nullptr, 10);
        bool sawInitVar = false;
        for (auto& transform : folded.closedFormTransforms) {
            if (transform.variable != initVar) continue;
            const __int128 value =
                static_cast<__int128>(transform.scale) * initValue +
                transform.offset;
            if (value < std::numeric_limits<long long>::min() ||
                value > std::numeric_limits<long long>::max()) {
                return std::nullopt;
            }
            transform.scale = 0;
            transform.offset = static_cast<long long>(value);
            sawInitVar = true;
            break;
        }
        if (!sawInitVar) return std::nullopt;

        // C99 for-init declarations are scoped to the nested for statement.
        // Their final value is not visible to the outer SPath and must not be
        // emitted as synthetic code after the nested loop has been removed.
        // A pre-declared induction variable (for (j=0; ...)) remains live and
        // therefore keeps the folded constant transform.
        static const std::regex declaredInitRe(
            R"(^[[:space:]]*(?:const[[:space:]]+|volatile[[:space:]]+|signed[[:space:]]+|unsigned[[:space:]]+)*(?:char|short|int|long|float|double|_Bool|size_t)[[:space:]]+)");
        if (std::regex_search(
                nestedLoop->initstmt_str, declaredInitRe)) {
            folded.closedFormTransforms.erase(
                std::remove_if(
                    folded.closedFormTransforms.begin(),
                    folded.closedFormTransforms.end(),
                    [&](const LoopSccAffineTransform& transform) {
                        return transform.variable == initVar;
                    }),
                folded.closedFormTransforms.end());
        }
    }

    return folded;
}

void deriveUniformTripCount(CFGNode* loop,
                            const std::vector<BuiltPath>& built,
                            LoopSccGraphInfo& result) {
    if (!loop || !loop->isLoop || !result.complete ||
        loop->initstmt_str.empty() || built.empty()) {
        return;
    }

    std::smatch initMatch;
    static const std::regex initRe(
        R"((?:^|[;[:space:]])(?:[A-Za-z_][A-Za-z0-9_]*[[:space:]]+)*([A-Za-z_][A-Za-z0-9_]*)[[:space:]]*=[[:space:]]*(-?[0-9]+)[[:space:]]*;?$)");
    if (!std::regex_search(loop->initstmt_str, initMatch, initRe)) {
        return;
    }
    const std::string variable = initMatch[1].str();

    bool haveStep = false;
    long long uniformStep = 0;
    for (const auto& path : built) {
        if (!path.info.returnsToHeader || path.info.exitsLoop ||
            path.unknownWrites.count(variable) != 0) {
            return;
        }
        auto transform = path.transforms.find(variable);
        if (transform == path.transforms.end() ||
            !transform->second.exact ||
            transform->second.scale != 1 ||
            transform->second.offset == 0) {
            return;
        }
        if (!haveStep) {
            uniformStep = transform->second.offset;
            haveStep = true;
        } else if (uniformStep != transform->second.offset) {
            return;
        }
    }
    if (!haveStep) return;

    const std::string update =
        variable + " = " + variable +
        (uniformStep > 0 ? " + " : " - ") +
        std::to_string(std::llabs(uniformStep)) + ";";

    // Use the total SPath transform rather than trusting the syntactic for-post
    // expression alone. This rejects bodies that also mutate the induction
    // variable, while allowing canonical for-loops and recovered while-loops
    // to share the same exact trip-count certificate.
    const auto prediction = LoopBoundPredictor::predict(
        loop->initstmt_str, loop->cond_str, update,
        std::numeric_limits<int>::max(), 0);
    if (!prediction.exact() ||
        prediction.inductionVariable != variable ||
        prediction.step != uniformStep) {
        return;
    }

    result.provedTripCount = prediction.iterations;
    result.tripCountVariable = variable;
    result.tripCountStep = uniformStep;
    result.diagnostics.push_back(
        "proved uniform SPath trip count: " + variable + "=" +
        std::to_string(prediction.iterations) +
        " step=" + std::to_string(uniformStep));
}

}  // namespace

LoopSccGraphInfo LoopSccAdapter::analyze(CFGNode* loop,
                                         std::size_t maxPaths,
                                         std::size_t maxNodesPerPath) {
    LoopSccGraphInfo result;
    if (!loop || !loop->isLoop) {
        result.diagnostics.push_back("not a loop CFG node");
        return result;
    }

    result.loopCondition = loop->cond_str;
    auto start = loop->getNextNode();
    auto exit = loop->getNextFalseNode();
    if (!start) {
        result.diagnostics.push_back("loop has no true/body edge");
        return result;
    }

    std::vector<BuiltPath> built;
    bool truncated = false;
    bool unsupported = false;
    std::unordered_set<CFGNode*> summarizedNestedLoops;

    std::function<void(std::shared_ptr<CFGNode>, BuiltPath,
                       std::unordered_set<CFGNode*>, std::size_t)> visit;
    visit = [&](std::shared_ptr<CFGNode> current,
                BuiltPath path,
                std::unordered_set<CFGNode*> seen,
                std::size_t depth) {
        if (built.size() >= maxPaths) {
            truncated = true;
            return;
        }
        if (depth > maxNodesPerPath) {
            truncated = true;
            return;
        }
        if (!current) {
            path.info.exitsLoop = true;
            built.push_back(std::move(path));
            return;
        }
        if (current.get() == loop) {
            if (loop->isFor && !loop->expr_str.empty() &&
                !parseUpdate(path, loop->expr_str)) {
                path.info.accelerationEffectSafe = false;
            }
            path.info.returnsToHeader = true;
            built.push_back(std::move(path));
            return;
        }
        if (exit && current.get() == exit.get()) {
            path.info.exitsLoop = true;
            built.push_back(std::move(path));
            return;
        }
        if (current->isReturn) {
            path.info.exitsLoop = true;
            built.push_back(std::move(path));
            return;
        }
        if (current->isLoop) {
            const auto nested = LoopSccAdapter::analyze(
                current.get(), maxPaths, maxNodesPerPath);
            const auto nestedPlan =
                uniformInsideOutPlan(nested, current.get());
            if (!nestedPlan) {
                unsupported = true;
                result.diagnostics.push_back(
                    "nested loop requires inside-out LoopSCC summary");
                return;
            }

            for (const auto& transform :
                 nestedPlan->closedFormTransforms) {
                composeUpdate(
                    path, transform.variable,
                    transform.scale, transform.offset,
                    "inside-out nested LoopSCC summary");
            }
            for (int slot : nestedPlan->coverageSlots) {
                recordCoverageSlot(path, slot);
            }
            if (summarizedNestedLoops.insert(current.get()).second) {
                ++result.insideOutNestedSummaryCount;
                result.diagnostics.push_back(
                    "inside-out summarized nested loop: " +
                    current->cond_str);
            }

            auto afterNested = current->getNextFalseNode();
            if (!afterNested) {
                unsupported = true;
                result.diagnostics.push_back(
                    "inside-out nested loop has no exit edge");
                return;
            }
            visit(
                afterNested, std::move(path),
                std::move(seen), depth + 1);
            return;
        }
        if (!seen.insert(current.get()).second) {
            unsupported = true;
            result.diagnostics.push_back(
                "internal cycle encountered before loop backedge");
            return;
        }

        if (current->isIf ||
            (current->isCondition && current->getNextFalseNode())) {
            auto truePath = path;
            addGuard(truePath, current->cond_str, true, current->depth);
            visit(current->getNextNode(), std::move(truePath), seen, depth + 1);

            auto falsePath = std::move(path);
            addGuard(falsePath, current->cond_str, false, current->depth);
            visit(current->getNextFalseNode(), std::move(falsePath),
                  std::move(seen), depth + 1);
            return;
        }

        if (current->depth >= 0 && !current->isCondition) {
            recordCoverageSlot(path, 2 * current->depth);
            recordCoverageSlot(path, 2 * current->depth + 1);
        }
        const std::string code = current->getCode();
        if (!code.empty() && code != "Code has not been set yet" &&
            !parseUpdate(path, code)) {
            path.info.accelerationEffectSafe = false;
        }
        if (current->getNextFalseNode()) {
            unsupported = true;
            result.diagnostics.push_back(
                "non-condition CFG node has a false edge");
            return;
        }
        visit(current->getNextNode(), std::move(path), std::move(seen),
              depth + 1);
    };

    BuiltPath initial;
    addGuard(initial, loop->cond_str, true, loop->depth);
    visit(start, std::move(initial), {}, 0);

    for (std::size_t i = 0; i < built.size(); ++i) {
        built[i].info.id = i;
        built[i].info.affineTransforms.clear();
        for (const auto& entry : built[i].transforms) {
            if (!entry.second.exact ||
                built[i].unknownWrites.count(entry.first) != 0) {
                continue;
            }
            built[i].info.affineTransforms.push_back(
                LoopSccAffineTransform{
                    entry.first, entry.second.scale, entry.second.offset});
        }
        built[i].info.memoryCellTransforms.clear();
        for (const auto& entry : built[i].memoryTransforms) {
            if (!entry.second.exact) continue;
            built[i].info.memoryCellTransforms.push_back(
                LoopSccMemoryCellTransform{
                    entry.first.first,
                    entry.first.second,
                    entry.second.scale,
                    entry.second.offset});
        }
        result.spaths.push_back(built[i].info);
    }
    if (truncated) {
        result.diagnostics.push_back("SPath enumeration hit configured budget");
    }
    result.complete = !truncated && !unsupported && !built.empty();
    if (built.empty()) return result;

    std::vector<std::vector<int>> graph(built.size());
    for (std::size_t i = 0; i < built.size(); ++i) {
        for (std::size_t j = 0; j < built.size(); ++j) {
            if (!transitionPossible(built[i], built[j])) continue;
            graph[i].push_back(static_cast<int>(j));
            result.transitions.emplace_back(i, j);
            ++result.transitionCount;
        }
    }

    TarjanState tarjan;
    tarjan.index.assign(built.size(), -1);
    tarjan.low.assign(built.size(), -1);
    tarjan.onStack.assign(built.size(), false);
    for (std::size_t i = 0; i < built.size(); ++i) {
        if (tarjan.index[i] == -1) {
            strongConnect(static_cast<int>(i), graph, tarjan);
        }
    }

    result.sccCount = tarjan.components.size();
    result.sccs.reserve(tarjan.components.size());
    for (const auto& component : tarjan.components) {
        std::vector<std::size_t> converted;
        converted.reserve(component.size());
        for (int node : component)
            converted.push_back(static_cast<std::size_t>(node));
        result.sccs.push_back(std::move(converted));
    }
    std::vector<int> componentOf(built.size(), -1);
    for (std::size_t cid = 0; cid < tarjan.components.size(); ++cid) {
        const auto& component = tarjan.components[cid];
        result.maxSccSize = std::max(result.maxSccSize, component.size());
        if (component.size() > 1) ++result.multiNodeSccCount;

        bool cyclic = component.size() > 1;
        for (int node : component) {
            componentOf[node] = static_cast<int>(cid);
            if (!cyclic &&
                std::find(graph[node].begin(), graph[node].end(), node) !=
                    graph[node].end()) {
                cyclic = true;
            }
        }
        if (cyclic) ++result.cyclicSccCount;
    }

    std::set<std::pair<int, int>> contractedEdges;
    for (std::size_t from = 0; from < graph.size(); ++from) {
        for (int to : graph[from]) {
            const int lhs = componentOf[from];
            const int rhs = componentOf[to];
            if (lhs != rhs) contractedEdges.emplace(lhs, rhs);
        }
    }
    result.contractedEdgeCount = contractedEdges.size();
    for (const auto& edge : contractedEdges) {
        result.contractedEdges.emplace_back(
            static_cast<std::size_t>(edge.first),
            static_cast<std::size_t>(edge.second));
    }

    detectDeterminateCycles(
        built, graph, tarjan.components, componentOf, result);
    deriveUniformTripCount(loop, built, result);
    provePhaseGuards(built, result);
    deriveMemorySummaryCandidates(built, result);
    deriveAccelerationPlans(loop, built, result);
    return result;
}

}  // namespace C
}  // namespace psy
