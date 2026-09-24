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
#include <stdexcept>
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

struct LinearExpr {
    std::map<std::string, long long> coefficients;
    long long constant{0};
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
    // Entry-state expressions for sequential scalar linear assignments.
    std::map<std::string, LinearExpr> coupledState;
    std::set<std::string> coupledVariables;
    std::set<std::string> unknownWrites;
};

using ConstantPointerAliasMap =
    std::unordered_map<std::string, std::pair<std::string, long long>>;

// Alias-aware analysis is opt-in and thread-local so recursive inside-out
// analyses inherit the same immutable source-prefix alias certificate.
thread_local const ConstantPointerAliasMap* activeConstantPointerAliases =
    nullptr;

const std::pair<std::string, long long>* constantPointerAlias(
    const std::string& pointer) {
    if (!activeConstantPointerAliases) return nullptr;
    auto it = activeConstantPointerAliases->find(pointer);
    return it == activeConstantPointerAliases->end() ? nullptr : &it->second;
}

void invalidateConstantPointerAliasWrite(
    BuiltPath& path, const std::string& variable) {
    if (!constantPointerAlias(variable)) return;
    path.info.memorySummaryEffectSafe = false;
    path.info.memoryTransitionModelComplete = false;
    path.info.coupledAffineEffectSafe = false;
}

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
        // Keep '-' at the end of the ECMAScript character class.
        // Placing it between '+' and '*' forms an invalid range ("+-*") in
        // libstdc++ regex and used to throw on ordinary expressions like i*4.
        static const std::regex multiplicationOnly(
            R"(^[A-Za-z0-9_[:space:]()+*/%<>=!&|-]+$)");
        if (!std::regex_match(text, multiplicationOnly)) {
            access.precise = false;
        }
    }

    if (!conditionContext) {
        const auto eq = text.find('=');
        if (eq != std::string::npos) {
            const std::string lhs = trim(text.substr(0, eq));
            const bool lhsArray =
                lhs.find('[') != std::string::npos;
            const bool lhsPointer =
                !lhs.empty() && lhs.front() == '*';
            access.writesMemory = lhsArray || lhsPointer;

            // Compound assignment performs an implicit read of the lvalue
            // before writing it. Lexically there is only one a[i] / *p token,
            // so add the missing read to match epat++ MEMS semantics.
            std::size_t op = eq;
            while (op > 0 &&
                   std::isspace(static_cast<unsigned char>(
                       text[op - 1])) != 0) {
                --op;
            }
            const bool compoundAssignment =
                op > 0 &&
                (text[op - 1] == '+' || text[op - 1] == '-' ||
                 text[op - 1] == '*' || text[op - 1] == '/' ||
                 text[op - 1] == '%' || text[op - 1] == '&' ||
                 text[op - 1] == '|' || text[op - 1] == '^' ||
                 text[op - 1] == '<' || text[op - 1] == '>');
            if (compoundAssignment && access.writesMemory) {
                if (lhsArray) {
                    ++access.arraySubscripts;
                } else if (lhsPointer) {
                    ++access.pointerDereferences;
                }
            }
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


bool checkedLinearAccumulate(long long& target, __int128 delta) {
    const __int128 value =
        static_cast<__int128>(target) + delta;
    if (value < std::numeric_limits<long long>::min() ||
        value > std::numeric_limits<long long>::max()) {
        return false;
    }
    target = static_cast<long long>(value);
    return true;
}

bool parseLinearRhs(
    const std::string& raw,
    std::map<std::string, long long>& coefficients,
    long long& constant) {
    std::string text;
    text.reserve(raw.size());
    for (unsigned char ch : raw) {
        if (std::isspace(ch) == 0) text.push_back(static_cast<char>(ch));
    }
    if (text.empty()) return false;

    static const std::regex identifier(
        R"(^[A-Za-z_][A-Za-z0-9_]*$)");
    static const std::regex integer(
        R"(^[0-9]+$)");
    static const std::regex intTimesVar(
        R"(^([0-9]+)\*([A-Za-z_][A-Za-z0-9_]*)$)");
    static const std::regex varTimesInt(
        R"(^([A-Za-z_][A-Za-z0-9_]*)\*([0-9]+)$)");

    std::size_t pos = 0;
    while (pos < text.size()) {
        int sign = 1;
        if (text[pos] == '+' || text[pos] == '-') {
            sign = text[pos] == '-' ? -1 : 1;
            ++pos;
        }
        if (pos >= text.size()) return false;

        const std::size_t begin = pos;
        while (pos < text.size() &&
               text[pos] != '+' && text[pos] != '-') {
            ++pos;
        }
        const std::string term = text.substr(begin, pos - begin);
        if (term.empty()) return false;

        std::smatch match;
        try {
            if (std::regex_match(term, identifier)) {
                auto& coeff = coefficients[term];
                if (!checkedLinearAccumulate(coeff, sign)) return false;
            } else if (std::regex_match(term, integer)) {
                const long long value = std::stoll(term);
                if (!checkedLinearAccumulate(
                        constant,
                        static_cast<__int128>(sign) * value)) {
                    return false;
                }
            } else if (std::regex_match(term, match, intTimesVar)) {
                const long long value = std::stoll(match[1].str());
                auto& coeff = coefficients[match[2].str()];
                if (!checkedLinearAccumulate(
                        coeff,
                        static_cast<__int128>(sign) * value)) {
                    return false;
                }
            } else if (std::regex_match(term, match, varTimesInt)) {
                const long long value = std::stoll(match[2].str());
                auto& coeff = coefficients[match[1].str()];
                if (!checkedLinearAccumulate(
                        coeff,
                        static_cast<__int128>(sign) * value)) {
                    return false;
                }
            } else {
                return false;
            }
        } catch (const std::out_of_range&) {
            return false;
        }
    }

    for (auto it = coefficients.begin();
         it != coefficients.end();) {
        if (it->second == 0) it = coefficients.erase(it);
        else ++it;
    }
    return true;
}

LinearExpr identityLinearExpr(const std::string& variable) {
    LinearExpr out;
    out.coefficients[variable] = 1;
    return out;
}

bool addScaledLinearExpr(
    LinearExpr& target,
    const LinearExpr& source,
    long long scale) {
    if (!source.exact) return false;
    if (!checkedLinearAccumulate(
            target.constant,
            static_cast<__int128>(scale) * source.constant)) {
        return false;
    }
    for (const auto& entry : source.coefficients) {
        auto& coeff = target.coefficients[entry.first];
        if (!checkedLinearAccumulate(
                coeff,
                static_cast<__int128>(scale) * entry.second)) {
            return false;
        }
        if (coeff == 0) target.coefficients.erase(entry.first);
    }
    return true;
}

bool composeCoupledAssignment(
    BuiltPath& path,
    const std::string& lhs,
    const std::string& rhs) {
    std::map<std::string, long long> rawCoefficients;
    long long rawConstant = 0;
    if (!parseLinearRhs(rhs, rawCoefficients, rawConstant)) {
        return false;
    }

    LinearExpr result;
    result.constant = rawConstant;
    for (const auto& entry : rawCoefficients) {
        const auto current = path.coupledState.find(entry.first);
        const LinearExpr source =
            current == path.coupledState.end()
                ? identityLinearExpr(entry.first)
                : current->second;
        if (!addScaledLinearExpr(result, source, entry.second)) {
            return false;
        }
        path.coupledVariables.insert(entry.first);
    }
    path.coupledVariables.insert(lhs);
    path.coupledState[lhs] = std::move(result);
    return true;
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
    static const std::regex scalarAssignCapture(
        R"(^([A-Za-z_][A-Za-z0-9_]*)[[:space:]]*=[[:space:]]*(.+)$)");

    bool coupledAssignmentSeen = false;
    bool coupledAssignmentExact = false;
    std::smatch coupledMatch;
    if (std::regex_match(text, coupledMatch, scalarAssignCapture)) {
        coupledAssignmentSeen = true;
        coupledAssignmentExact = composeCoupledAssignment(
            path, coupledMatch[1].str(), coupledMatch[2].str());
        if (!coupledAssignmentExact) {
            path.info.coupledAffineEffectSafe = false;
        }
    }

    if (std::regex_match(text, m, postfix)) {
        const long long delta = m[2].str() == "++" ? 1 : -1;
        if (!composeCoupledAssignment(
                path, m[1].str(),
                m[1].str() + (delta > 0 ? "+" : "-") + "1")) {
            path.info.coupledAffineEffectSafe = false;
        }
        composeUpdate(path, m[1].str(), 1, delta, raw);
        invalidateConstantPointerAliasWrite(path, m[1].str());
        return true;
    }
    if (std::regex_match(text, m, prefix)) {
        const long long delta = m[1].str() == "++" ? 1 : -1;
        if (!composeCoupledAssignment(
                path, m[2].str(),
                m[2].str() + (delta > 0 ? "+" : "-") + "1")) {
            path.info.coupledAffineEffectSafe = false;
        }
        composeUpdate(path, m[2].str(), 1, delta, raw);
        invalidateConstantPointerAliasWrite(path, m[2].str());
        return true;
    }
    if (std::regex_match(text, m, compound)) {
        long long value = std::stoll(m[3].str());
        if (m[2].str() == "-=") value = -value;
        if (!composeCoupledAssignment(
                path, m[1].str(),
                m[1].str() + (value >= 0 ? "+" : "") +
                    std::to_string(value))) {
            path.info.coupledAffineEffectSafe = false;
        }
        composeUpdate(path, m[1].str(), 1, value, raw);
        invalidateConstantPointerAliasWrite(path, m[1].str());
        return true;
    }
    if (std::regex_match(text, m, selfAdd)) {
        long long value = std::stoll(m[3].str());
        if (m[2].str() == "-") value = -value;
        composeUpdate(path, m[1].str(), 1, value, raw);
        invalidateConstantPointerAliasWrite(path, m[1].str());
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
        invalidateConstantPointerAliasWrite(path, m[1].str());
        return true;
    }
    if (std::regex_match(text, m, constantAssign)) {
        composeUpdate(path, m[1].str(), 0, std::stoll(m[2].str()), raw);
        invalidateConstantPointerAliasWrite(path, m[1].str());
        return true;
    }

    // Narrow constant-pointer aliases are normalized to the same fixed-cell
    // transition representation used by direct array syntax. The alias map is
    // recovered outside the loop from declarations such as "int *p = a;" or
    // "int *p = &a[2];". Any in-loop reassignment of p is handled by the
    // ordinary unknown-scalar-write path and invalidates memorySummaryEffectSafe.
    static const std::regex pointerSelfAdd(
        R"(^\*[[:space:]]*([A-Za-z_][A-Za-z0-9_]*)[[:space:]]*=[[:space:]]*\*[[:space:]]*\1[[:space:]]*([+-])[[:space:]]*([0-9]+)$)");
    static const std::regex pointerCompound(
        R"(^\*[[:space:]]*([A-Za-z_][A-Za-z0-9_]*)[[:space:]]*(\+=|-=)[[:space:]]*(-?[0-9]+)$)");
    static const std::regex pointerConstant(
        R"(^\*[[:space:]]*([A-Za-z_][A-Za-z0-9_]*)[[:space:]]*=[[:space:]]*(-?[0-9]+)$)");

    auto applyPointerCell = [&](const std::string& pointer,
                                long long scale,
                                long long offset) {
        const auto* alias = constantPointerAlias(pointer);
        if (!alias) return false;
        if (!composeMemoryCellUpdate(
                path, alias->first, alias->second, scale, offset)) {
            path.info.memoryTransitionModelComplete = false;
            path.info.memorySummaryEffectSafe = false;
        }
        recordWrite(path, "*memory*");
        path.unknownWrites.insert("*memory*");
        path.info.accelerationEffectSafe = false;
        path.info.coupledAffineEffectSafe = false;
        return true;
    };

    if (std::regex_match(text, m, pointerSelfAdd)) {
        long long value = std::stoll(m[3].str());
        if (m[2].str() == "-") value = -value;
        if (applyPointerCell(m[1].str(), 1, value)) return false;
    }
    if (std::regex_match(text, m, pointerCompound)) {
        long long value = std::stoll(m[3].str());
        if (m[2].str() == "-=") value = -value;
        if (applyPointerCell(m[1].str(), 1, value)) return false;
    }
    if (std::regex_match(text, m, pointerConstant)) {
        if (applyPointerCell(
                m[1].str(), 0, std::stoll(m[2].str()))) {
            return false;
        }
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
        path.info.coupledAffineEffectSafe = false;
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
        path.info.coupledAffineEffectSafe = false;
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
        path.info.coupledAffineEffectSafe = false;
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
        path.info.coupledAffineEffectSafe = false;
        return false;
    }

    if (std::regex_match(text, m, simpleAssign)) {
        markUnknownWrite(path, m[1].str(), raw);
        path.info.accelerationEffectSafe = false;
        path.info.memorySummaryEffectSafe = false;
        if (!coupledAssignmentSeen || !coupledAssignmentExact) {
            path.info.coupledAffineEffectSafe = false;
        }
        return false;
    }

    // Any remaining executable statement is outside the restricted scalar
    // affine semantics (for example a call, declaration with initializer,
    // pointer read, multiplication, or other side effect). Keep structural
    // SPath information, but never use such a path for acceleration.
    path.info.accelerationEffectSafe = false;
    path.info.memorySummaryEffectSafe = false;
    path.info.coupledAffineEffectSafe = false;
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


struct DenseAffine {
    std::size_t n{0};
    std::vector<long long> matrix;
    std::vector<long long> offset;
    bool exact{true};
};

DenseAffine denseIdentity(std::size_t n) {
    DenseAffine out;
    out.n = n;
    out.matrix.assign(n * n, 0);
    out.offset.assign(n, 0);
    for (std::size_t i = 0; i < n; ++i) {
        out.matrix[i * n + i] = 1;
    }
    return out;
}

bool checkedDenseAccumulate(long long& total, __int128 term) {
    const __int128 value =
        static_cast<__int128>(total) + term;
    if (value < std::numeric_limits<long long>::min() ||
        value > std::numeric_limits<long long>::max()) {
        return false;
    }
    total = static_cast<long long>(value);
    return true;
}

bool checkedDenseCompose(
    const DenseAffine& after,
    const DenseAffine& before,
    DenseAffine& out) {
    if (!after.exact || !before.exact ||
        after.n == 0 || after.n != before.n) {
        return false;
    }
    const std::size_t n = after.n;
    DenseAffine result = denseIdentity(n);
    std::fill(result.matrix.begin(), result.matrix.end(), 0);
    std::fill(result.offset.begin(), result.offset.end(), 0);

    for (std::size_t i = 0; i < n; ++i) {
        for (std::size_t j = 0; j < n; ++j) {
            long long value = 0;
            for (std::size_t k = 0; k < n; ++k) {
                const __int128 term =
                    static_cast<__int128>(
                        after.matrix[i * n + k]) *
                    before.matrix[k * n + j];
                if (!checkedDenseAccumulate(value, term)) {
                    return false;
                }
            }
            result.matrix[i * n + j] = value;
        }

        long long bias = after.offset[i];
        for (std::size_t k = 0; k < n; ++k) {
            const __int128 term =
                static_cast<__int128>(
                    after.matrix[i * n + k]) *
                before.offset[k];
            if (!checkedDenseAccumulate(bias, term)) {
                return false;
            }
        }
        result.offset[i] = bias;
    }

    out = std::move(result);
    return true;
}

bool densePower(
    DenseAffine base,
    long long exponent,
    DenseAffine& out) {
    if (exponent < 0 || !base.exact || base.n == 0) return false;
    DenseAffine result = denseIdentity(base.n);
    while (exponent > 0) {
        if ((exponent & 1LL) != 0) {
            DenseAffine next;
            if (!checkedDenseCompose(base, result, next)) {
                return false;
            }
            result = std::move(next);
        }
        exponent >>= 1;
        if (exponent == 0) break;
        DenseAffine squared;
        if (!checkedDenseCompose(base, base, squared)) {
            return false;
        }
        base = std::move(squared);
    }
    out = std::move(result);
    return true;
}

bool denseFromPath(
    const BuiltPath& path,
    const std::vector<std::string>& variables,
    DenseAffine& out) {
    if (variables.empty()) return false;
    std::unordered_map<std::string, std::size_t> index;
    for (std::size_t i = 0; i < variables.size(); ++i) {
        index.emplace(variables[i], i);
    }

    DenseAffine result = denseIdentity(variables.size());
    for (std::size_t row = 0; row < variables.size(); ++row) {
        const auto state = path.coupledState.find(variables[row]);
        if (state == path.coupledState.end()) continue;
        if (!state->second.exact) return false;

        for (std::size_t col = 0; col < variables.size(); ++col) {
            result.matrix[row * variables.size() + col] = 0;
        }
        for (const auto& coefficient :
             state->second.coefficients) {
            const auto col = index.find(coefficient.first);
            if (col == index.end()) return false;
            result.matrix[
                row * variables.size() + col->second] =
                    coefficient.second;
        }
        result.offset[row] = state->second.constant;
    }
    out = std::move(result);
    return true;
}

bool hasCrossVariableCoefficient(const DenseAffine& transform) {
    for (std::size_t row = 0; row < transform.n; ++row) {
        for (std::size_t col = 0; col < transform.n; ++col) {
            if (row != col &&
                transform.matrix[row * transform.n + col] != 0) {
                return true;
            }
        }
    }
    return false;
}

void deriveCoupledAffineCandidates(
    const std::vector<BuiltPath>& built,
    LoopSccGraphInfo& result) {
    if (!result.complete || result.provedTripCount < 0) return;

    constexpr std::size_t kMaxCoupledVariables = 4;
    for (std::size_t cycleIndex = 0;
         cycleIndex < result.cycles.size(); ++cycleIndex) {
        const auto& cycle = result.cycles[cycleIndex];
        if (!cycle.determinate || !cycle.phaseGuardsProved ||
            cycle.period == 0 ||
            cycle.spathOrder.size() != cycle.period) {
            continue;
        }

        std::set<std::string> variableSet;
        bool safe = true;
        for (std::size_t pathId : cycle.spathOrder) {
            if (pathId >= built.size()) {
                safe = false;
                break;
            }
            const auto& path = built[pathId];
            if (!path.info.coupledAffineEffectSafe ||
                !path.info.guardModelComplete ||
                path.info.writesMemory ||
                path.info.observedMems != 0) {
                safe = false;
                break;
            }
            variableSet.insert(
                path.coupledVariables.begin(),
                path.coupledVariables.end());
        }
        if (!safe ||
            variableSet.size() < 2 ||
            variableSet.size() > kMaxCoupledVariables) {
            continue;
        }

        std::vector<std::string> variables(
            variableSet.begin(), variableSet.end());
        std::unordered_map<std::size_t, DenseAffine> pathTransforms;
        for (std::size_t pathId : cycle.spathOrder) {
            DenseAffine transform;
            if (!denseFromPath(
                    built[pathId], variables, transform)) {
                safe = false;
                break;
            }
            pathTransforms.emplace(
                pathId, std::move(transform));
        }
        if (!safe) continue;

        const long long fullPeriods =
            result.provedTripCount /
            static_cast<long long>(cycle.period);
        const std::size_t residual =
            static_cast<std::size_t>(
                result.provedTripCount %
                static_cast<long long>(cycle.period));

        for (std::size_t entryPhase = 0;
             entryPhase < cycle.period; ++entryPhase) {
            DenseAffine onePeriod =
                denseIdentity(variables.size());
            bool exact = true;
            for (std::size_t step = 0;
                 step < cycle.period; ++step) {
                const std::size_t pathId =
                    cycle.spathOrder[
                        (entryPhase + step) % cycle.period];
                auto it = pathTransforms.find(pathId);
                if (it == pathTransforms.end()) {
                    exact = false;
                    break;
                }
                DenseAffine next;
                if (!checkedDenseCompose(
                        it->second, onePeriod, next)) {
                    exact = false;
                    break;
                }
                onePeriod = std::move(next);
            }
            if (!exact ||
                !hasCrossVariableCoefficient(onePeriod)) {
                continue;
            }

            DenseAffine accumulated;
            if (!densePower(
                    onePeriod, fullPeriods, accumulated)) {
                continue;
            }
            for (std::size_t r = 0; r < residual; ++r) {
                const std::size_t pathId =
                    cycle.spathOrder[
                        (entryPhase + r) % cycle.period];
                auto it = pathTransforms.find(pathId);
                if (it == pathTransforms.end()) {
                    exact = false;
                    break;
                }
                DenseAffine next;
                if (!checkedDenseCompose(
                        it->second, accumulated, next)) {
                    exact = false;
                    break;
                }
                accumulated = std::move(next);
            }
            if (!exact) continue;

            LoopSccCoupledAffineCandidate candidate;
            candidate.cycleIndex = cycleIndex;
            candidate.entryPhase = entryPhase;
            candidate.period = cycle.period;
            candidate.totalIterations = result.provedTripCount;
            candidate.completePeriods = fullPeriods;
            candidate.residualPhases = residual;
            candidate.closedForm.variables = variables;
            candidate.closedForm.matrix =
                accumulated.matrix;
            candidate.closedForm.offset =
                accumulated.offset;

            std::set<int> coverage;
            if (fullPeriods > 0) {
                for (std::size_t pathId : cycle.spathOrder) {
                    coverage.insert(
                        built[pathId].info.coverageSlots.begin(),
                        built[pathId].info.coverageSlots.end());
                }
            }
            for (std::size_t r = 0; r < residual; ++r) {
                const std::size_t pathId =
                    cycle.spathOrder[
                        (entryPhase + r) % cycle.period];
                coverage.insert(
                    built[pathId].info.coverageSlots.begin(),
                    built[pathId].info.coverageSlots.end());
            }
            candidate.coverageSlots.assign(
                coverage.begin(), coverage.end());
            candidate.exact = true;
            candidate.diagnostics.push_back(
                "structural-only coupled affine matrix; runtime shortcut disabled");
            result.coupledAffineCandidates.push_back(
                std::move(candidate));
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

struct InsideOutMemorySummary {
    std::vector<LoopSccMemoryCellTransform> memoryTransforms;
    std::vector<LoopSccAffineTransform> scalarTransforms;
    std::vector<int> coverageSlots;
    std::size_t observedMems{0};
};

std::optional<InsideOutMemorySummary>
uniformInsideOutMemorySummary(
    const LoopSccGraphInfo& nested, CFGNode* nestedLoop) {
    if (!nested.complete || nested.provedTripCount <= 0 ||
        nested.cycles.size() != 1 ||
        nested.memorySummaryCandidates.empty()) {
        return std::nullopt;
    }

    const auto& cycle = nested.cycles.front();
    if (!cycle.determinate || !cycle.phaseGuardsProved ||
        cycle.period == 0 ||
        cycle.spathOrder.size() != cycle.period ||
        nested.memorySummaryCandidates.size() != cycle.period) {
        return std::nullopt;
    }

    // The inner candidate is allowed to become an outer structural fact only
    // when every participating SPath already has exact memory observation,
    // transition and non-memory effect models.
    for (std::size_t pathId : cycle.spathOrder) {
        if (pathId >= nested.spaths.size()) return std::nullopt;
        const auto& path = nested.spaths[pathId];
        if (!path.returnsToHeader || path.exitsLoop ||
            !path.guardModelComplete ||
            !path.memoryAccessModelComplete ||
            !path.memoryTransitionModelComplete ||
            !path.memorySummaryEffectSafe ||
            (path.writesMemory && path.memoryCellTransforms.empty())) {
            return std::nullopt;
        }

        __int128 explainedMems =
            static_cast<__int128>(
                path.certifiedNestedMemoryMems);
        for (const auto& access : path.memoryAccesses) {
            if (!access.precise) return std::nullopt;
            explainedMems += access.mems();
        }
        if (explainedMems < 0 ||
            explainedMems >
                static_cast<__int128>(
                    std::numeric_limits<std::size_t>::max()) ||
            static_cast<std::size_t>(explainedMems) !=
                path.observedMems) {
            return std::nullopt;
        }
    }

    using CellKey = std::pair<std::string, long long>;
    using TransformValue = std::pair<long long, long long>;
    auto normalizeMemory =
        [](const LoopSccMemorySummaryCandidate& candidate) {
            std::map<CellKey, TransformValue> out;
            for (const auto& transform :
                 candidate.closedFormTransforms) {
                out[{transform.region, transform.index}] =
                    {transform.scale, transform.offset};
            }
            return out;
        };
    auto normalizeScalar =
        [](const LoopSccMemorySummaryCandidate& candidate) {
            std::map<std::string, TransformValue> out;
            for (const auto& transform :
                 candidate.scalarClosedFormTransforms) {
                out[transform.variable] =
                    {transform.scale, transform.offset};
            }
            return out;
        };
    auto coverageFor =
        [&](const LoopSccMemorySummaryCandidate& candidate)
            -> std::optional<std::vector<int>> {
            if (candidate.cycleIndex != 0 ||
                candidate.entryPhase >= cycle.period ||
                candidate.totalIterations != nested.provedTripCount) {
                return std::nullopt;
            }

            const long long fullPeriods =
                candidate.totalIterations /
                static_cast<long long>(cycle.period);
            const std::size_t residual =
                static_cast<std::size_t>(
                    candidate.totalIterations %
                    static_cast<long long>(cycle.period));
            std::set<int> coverage;
            if (fullPeriods > 0) {
                for (std::size_t pathId : cycle.spathOrder) {
                    if (pathId >= nested.spaths.size()) {
                        return std::nullopt;
                    }
                    coverage.insert(
                        nested.spaths[pathId].coverageSlots.begin(),
                        nested.spaths[pathId].coverageSlots.end());
                }
            }
            for (std::size_t r = 0; r < residual; ++r) {
                const std::size_t pathId =
                    cycle.spathOrder[
                        (candidate.entryPhase + r) % cycle.period];
                if (pathId >= nested.spaths.size()) {
                    return std::nullopt;
                }
                coverage.insert(
                    nested.spaths[pathId].coverageSlots.begin(),
                    nested.spaths[pathId].coverageSlots.end());
            }
            if (nestedLoop && nestedLoop->depth >= 0) {
                coverage.insert(2 * nestedLoop->depth + 1);
            }
            return std::vector<int>(
                coverage.begin(), coverage.end());
        };

    const LoopSccMemorySummaryCandidate* representative = nullptr;
    std::map<CellKey, TransformValue> referenceMemory;
    std::map<std::string, TransformValue> referenceScalar;
    std::vector<int> referenceCoverage;
    std::size_t referenceMems = 0;

    for (const auto& candidate :
         nested.memorySummaryCandidates) {
        if (!candidate.exact ||
            candidate.totalIterations != nested.provedTripCount ||
            candidate.closedFormTransforms.empty()) {
            return std::nullopt;
        }
        const auto coverage = coverageFor(candidate);
        if (!coverage) return std::nullopt;

        auto memory = normalizeMemory(candidate);
        auto scalar = normalizeScalar(candidate);
        if (!representative) {
            representative = &candidate;
            referenceMemory = std::move(memory);
            referenceScalar = std::move(scalar);
            referenceCoverage = *coverage;
            referenceMems = candidate.observedMems;
            continue;
        }
        if (memory != referenceMemory ||
            scalar != referenceScalar ||
            *coverage != referenceCoverage ||
            candidate.observedMems != referenceMems) {
            return std::nullopt;
        }
    }
    if (!representative || referenceMemory.empty()) {
        return std::nullopt;
    }

    InsideOutMemorySummary folded;
    folded.memoryTransforms =
        representative->closedFormTransforms;
    folded.scalarTransforms =
        representative->scalarClosedFormTransforms;
    folded.coverageSlots = std::move(referenceCoverage);
    folded.observedMems = referenceMems;

    // Match scalar inside-out semantics for a nested for initializer. A C99
    // declaration is scoped to the inner loop and must not leak into the outer
    // SPath. A predeclared induction variable remains externally visible as a
    // constant final value after the initializer is folded.
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
        for (auto& transform : folded.scalarTransforms) {
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

        static const std::regex declaredInitRe(
            R"(^[[:space:]]*(?:const[[:space:]]+|volatile[[:space:]]+|signed[[:space:]]+|unsigned[[:space:]]+)*(?:char|short|int|long|float|double|_Bool|size_t)[[:space:]]+)");
        if (std::regex_search(
                nestedLoop->initstmt_str, declaredInitRe)) {
            folded.scalarTransforms.erase(
                std::remove_if(
                    folded.scalarTransforms.begin(),
                    folded.scalarTransforms.end(),
                    [&](const LoopSccAffineTransform& transform) {
                        return transform.variable == initVar;
                    }),
                folded.scalarTransforms.end());
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
            const auto nestedMemory =
                nestedPlan
                    ? std::optional<InsideOutMemorySummary>{}
                    : uniformInsideOutMemorySummary(
                          nested, current.get());
            if (!nestedPlan && !nestedMemory) {
                unsupported = true;
                result.diagnostics.push_back(
                    "nested loop requires inside-out LoopSCC summary");
                return;
            }

            if (nestedPlan) {
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
            } else {
                if (nestedMemory->observedMems >
                    std::numeric_limits<std::size_t>::max() -
                        path.info.observedMems) {
                    unsupported = true;
                    result.diagnostics.push_back(
                        "inside-out nested memory MEMS overflow");
                    return;
                }
                for (const auto& transform :
                     nestedMemory->scalarTransforms) {
                    composeUpdate(
                        path, transform.variable,
                        transform.scale, transform.offset,
                        "inside-out nested fixed-memory summary");
                }
                for (const auto& transform :
                     nestedMemory->memoryTransforms) {
                    if (!composeMemoryCellUpdate(
                            path, transform.region,
                            transform.index,
                            transform.scale,
                            transform.offset)) {
                        unsupported = true;
                        result.diagnostics.push_back(
                            "inside-out nested memory transform overflow");
                        return;
                    }
                }
                path.info.observedMems +=
                    nestedMemory->observedMems;
                path.info.certifiedNestedMemoryMems +=
                    nestedMemory->observedMems;
                path.info.writesMemory = true;
                path.info.accelerationEffectSafe = false;
                recordWrite(path, "*memory*");
                path.unknownWrites.insert("*memory*");
                for (int slot : nestedMemory->coverageSlots) {
                    recordCoverageSlot(path, slot);
                }
            }
            if (summarizedNestedLoops.insert(current.get()).second) {
                ++result.insideOutNestedSummaryCount;
                if (nestedMemory) {
                    ++result.insideOutNestedMemorySummaryCount;
                    result.diagnostics.push_back(
                        "inside-out summarized nested fixed-memory loop: " +
                        current->cond_str);
                } else {
                    result.diagnostics.push_back(
                        "inside-out summarized nested loop: " +
                        current->cond_str);
                }
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
    deriveCoupledAffineCandidates(built, result);
    deriveMemorySummaryCandidates(built, result);
    deriveAccelerationPlans(loop, built, result);
    return result;
}


std::vector<LoopSccConstantPointerAlias>
LoopSccAdapter::parseConstantPointerAliases(
    const std::string& sourcePrefix) {
    std::vector<LoopSccConstantPointerAlias> out;
    std::unordered_map<std::string, LoopSccConstantPointerAlias> unique;
    std::unordered_set<std::string> ambiguous;

    // First stage intentionally accepts declarations only. General assignments
    // require dominance/lifetime reasoning and remain fallback cases.
    static const std::regex decayDecl(
        R"((?:^|[;{}\n])[[:space:]]*(?:const[[:space:]]+)?(?:(?:unsigned|signed)[[:space:]]+)?(?:int|long|short|char)[[:space:]]*\*[[:space:]]*([A-Za-z_][A-Za-z0-9_]*)[[:space:]]*=[[:space:]]*([A-Za-z_][A-Za-z0-9_]*)[[:space:]]*;)");
    static const std::regex addressDecl(
        R"((?:^|[;{}\n])[[:space:]]*(?:const[[:space:]]+)?(?:(?:unsigned|signed)[[:space:]]+)?(?:int|long|short|char)[[:space:]]*\*[[:space:]]*([A-Za-z_][A-Za-z0-9_]*)[[:space:]]*=[[:space:]]*&[[:space:]]*([A-Za-z_][A-Za-z0-9_]*)[[:space:]]*\[[[:space:]]*([0-9]+)[[:space:]]*\][[:space:]]*;)");

    auto add = [&](const std::string& pointer,
                   const std::string& region,
                   long long index) {
        if (ambiguous.count(pointer)) return;
        LoopSccConstantPointerAlias alias{pointer, region, index};
        auto it = unique.find(pointer);
        if (it == unique.end()) {
            unique.emplace(pointer, std::move(alias));
            return;
        }
        if (it->second.region != region || it->second.index != index) {
            unique.erase(it);
            ambiguous.insert(pointer);
        } else {
            // Multiple textual declarations of the same pointer name are
            // scope-ambiguous for a name-only certificate.
            unique.erase(it);
            ambiguous.insert(pointer);
        }
    };

    for (std::sregex_iterator it(
             sourcePrefix.begin(), sourcePrefix.end(), addressDecl), end;
         it != end; ++it) {
        const std::string pointer = (*it)[1].str();
        try {
            add(pointer, (*it)[2].str(),
                std::stoll((*it)[3].str()));
        } catch (const std::out_of_range&) {
            // An index that cannot be represented by the certificate's
            // signed 64-bit cell index is not a constant alias we can prove.
            // Treat it exactly like any other ambiguous/unsupported alias
            // instead of aborting loop analysis.
            unique.erase(pointer);
            ambiguous.insert(pointer);
        }
    }
    for (std::sregex_iterator it(
             sourcePrefix.begin(), sourcePrefix.end(), decayDecl), end;
         it != end; ++it) {
        // Do not reinterpret the "&a[k]" declaration as an array-decay alias;
        // decayDecl cannot consume '&', but keep this loop separate for clarity.
        add((*it)[1].str(), (*it)[2].str(), 0);
    }

    out.reserve(unique.size());
    for (const auto& entry : unique) out.push_back(entry.second);
    std::sort(
        out.begin(), out.end(),
        [](const LoopSccConstantPointerAlias& lhs,
           const LoopSccConstantPointerAlias& rhs) {
            return lhs.pointer < rhs.pointer;
        });
    return out;
}

LoopSccGraphInfo LoopSccAdapter::analyzeWithConstantPointerAliases(
    CFGNode* loop,
    const std::string& sourcePrefix,
    std::size_t maxPaths,
    std::size_t maxNodesPerPath) {
    ConstantPointerAliasMap aliases;
    for (const auto& alias : parseConstantPointerAliases(sourcePrefix)) {
        aliases.emplace(
            alias.pointer,
            std::make_pair(alias.region, alias.index));
    }

    const ConstantPointerAliasMap* previous =
        activeConstantPointerAliases;
    activeConstantPointerAliases = aliases.empty() ? nullptr : &aliases;
    LoopSccGraphInfo result;
    try {
        result = analyze(loop, maxPaths, maxNodesPerPath);
    } catch (...) {
        activeConstantPointerAliases = previous;
        throw;
    }
    activeConstantPointerAliases = previous;

    for (const auto& alias :
         parseConstantPointerAliases(sourcePrefix)) {
        result.diagnostics.push_back(
            "constant pointer alias: " + alias.pointer + " -> " +
            alias.region + "[" + std::to_string(alias.index) + "]");
    }
    return result;
}

}  // namespace C
}  // namespace psy
