// Implementation of CFG-aware epat++ invocation utilities.
#include "EpatRunner.h"
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <stdexcept>
#include <sstream>
#include <regex>
#include <map>
#include <optional>

#include <cctype>
#include <cstdint>
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
    std::unordered_set<std::string> ambiguous;
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
            const std::string name = match[1].str();
            if (ambiguous.find(name) != ambiguous.end()) {
                continue;
            }
            auto inserted = out.emplace(
                name, static_cast<std::size_t>(parsed));
            if (!inserted.second) {
                // vartemp may contain declarations from multiple functions.
                // A name-only region certificate is unsafe when source scopes
                // collide, even if both arrays happen to have the same size.
                out.erase(name);
                ambiguous.insert(name);
            }
        } catch (...) {
            continue;
        }
    }
    return out;
}


struct SignedScalarDeclarations {
    std::unordered_map<std::string, std::string> types;
    std::unordered_set<std::string> ambiguous;
};

std::string normalizeTypeSpelling(const std::string& raw) {
    std::stringstream in(raw);
    std::string word;
    std::string out;
    while (in >> word) {
        if (!out.empty()) out += " ";
        out += word;
    }
    return out;
}

void recordSignedScalarDeclaration(
    const std::string& raw,
    SignedScalarDeclarations& declarations) {
    // Deliberately exclude unsigned, char, _Bool, size_t, pointers, arrays,
    // multiple declarators and floating point. Runtime acceleration will later
    // need a separate no-overflow proof even for these signed integer types.
    static const std::regex scalar(
        "^[ \\t]*(?:(?:const|volatile)[ \\t]+)*"
        "((?:signed[ \\t]+)?"
        "(?:short(?:[ \\t]+int)?|int|"
        "long(?:[ \\t]+long)?(?:[ \\t]+int)?))"
        "[ \\t]+([A-Za-z_][A-Za-z0-9_]*)"
        "[ \\t]*(?:=[^,;]*)?[ \\t]*;?[ \\t]*$");

    std::smatch match;
    if (!std::regex_match(raw, match, scalar)) return;
    const std::string name = match[2].str();
    if (declarations.ambiguous.find(name) !=
        declarations.ambiguous.end()) {
        return;
    }
    const std::string type =
        normalizeTypeSpelling(match[1].str());
    auto inserted = declarations.types.emplace(name, type);
    if (!inserted.second) {
        declarations.types.erase(name);
        declarations.ambiguous.insert(name);
    }
}

SignedScalarDeclarations parseSignedScalarDeclarations(
    const std::string& sourcePrefix,
    CFGNode* loop) {
    SignedScalarDeclarations out;
    std::stringstream input(sourcePrefix);
    std::string line;
    while (std::getline(input, line)) {
        recordSignedScalarDeclaration(line, out);
    }
    if (loop && loop->isFor &&
        !loop->initstmt_str.empty()) {
        recordSignedScalarDeclaration(loop->initstmt_str, out);
    }
    return out;
}

bool certifyCoupledAffineTypes(
    CFGNode* loop,
    const LoopSccGraphInfo& graph,
    const LoopSccCoupledAffineCandidate& candidate,
    const std::string& sourcePrefix,
    std::unordered_map<std::string, std::string>& certifiedTypes,
    std::vector<std::string>& diagnostics) {
    auto reject = [&](const std::string& reason) {
        diagnostics.push_back(reason);
        return false;
    };

    if (!loop || !graph.complete ||
        candidate.cycleIndex >= graph.cycles.size()) {
        return reject("coupled affine graph/cycle is incomplete");
    }
    const auto& cycle = graph.cycles[candidate.cycleIndex];
    if (!candidate.exact ||
        candidate.totalIterations <= 0 ||
        graph.provedTripCount != candidate.totalIterations ||
        !cycle.determinate || !cycle.phaseGuardsProved ||
        cycle.period == 0 ||
        candidate.period != cycle.period ||
        candidate.entryPhase >= cycle.spathOrder.size()) {
        return reject("coupled affine trip/phase certificate is incomplete");
    }

    entryRangesCertified = true;
    diagnostics.push_back(
        "loop-entry ranges reconstructed from declarations and path prefix");

    const auto& state = candidate.closedForm;
    const std::size_t n = state.variables.size();
    if (n < 2 || n > 4 ||
        state.matrix.size() != n * n ||
        state.offset.size() != n) {
        return reject("coupled affine matrix dimensions are invalid");
    }
    for (long long coefficient : state.matrix) {
        if (coefficient == std::numeric_limits<long long>::min()) {
            return reject("matrix coefficient cannot be rendered safely");
        }
    }
    for (long long offset : state.offset) {
        if (offset == std::numeric_limits<long long>::min()) {
            return reject("matrix offset cannot be rendered safely");
        }
    }

    for (std::size_t pathId : cycle.spathOrder) {
        if (pathId >= graph.spaths.size()) {
            return reject("cycle references an absent SPath");
        }
        const auto& path = graph.spaths[pathId];
        if (!path.returnsToHeader || path.exitsLoop ||
            !path.guardModelComplete ||
            !path.coupledAffineEffectSafe ||
            path.writesMemory || path.observedMems != 0) {
            return reject(
                "SPath has memory/opaque/nonlinear effect outside coupled scalar certificate");
        }
    }

    const auto declarations =
        parseSignedScalarDeclarations(sourcePrefix, loop);
    for (const auto& variable : state.variables) {
        if (declarations.ambiguous.find(variable) !=
            declarations.ambiguous.end()) {
            return reject(
                "ambiguous signed integer scalar declaration for " +
                variable);
        }
        auto found = declarations.types.find(variable);
        if (found == declarations.types.end()) {
            return reject(
                "missing unique signed integer scalar declaration for " +
                variable);
        }
        certifiedTypes.emplace(variable, found->second);
    }

    diagnostics.push_back(
        "unique signed-integer scalar type certificate");
    diagnostics.push_back(
        "signed-scalar type certificate alone does not prove overflow safety");
    return true;
}

std::string coupledSnapshotStem(
    CFGNode* loop,
    std::size_t candidateIndex,
    const std::string& sourcePrefix) {
    const auto address =
        static_cast<unsigned long long>(
            reinterpret_cast<std::uintptr_t>(loop));
    const std::string base =
        "__eppather_loopscc_affine_" +
        std::to_string(address) + "_" +
        std::to_string(candidateIndex) + "_";
    if (sourcePrefix.find(base) == std::string::npos) {
        return base;
    }
    for (std::size_t salt = 1; salt <= 16; ++salt) {
        const std::string salted =
            base + std::to_string(salt) + "_";
        if (sourcePrefix.find(salted) == std::string::npos) {
            return salted;
        }
    }
    return {};
}

std::string renderCoupledAffineRow(
    const LoopSccCoupledAffineTransform& state,
    std::size_t row,
    const std::vector<std::string>& snapshots) {
    const std::size_t n = state.variables.size();
    if (row >= n || snapshots.size() != n ||
        state.matrix.size() != n * n ||
        state.offset.size() != n) {
        return {};
    }

    std::ostringstream os;
    os << state.variables[row] << " = 0";
    for (std::size_t col = 0; col < n; ++col) {
        const long long coefficient =
            state.matrix[row * n + col];
        if (coefficient == 0) continue;
        const long long magnitude =
            coefficient < 0 ? -coefficient : coefficient;
        os << (coefficient < 0 ? " - " : " + ");
        if (magnitude != 1) {
            os << magnitude << " * ";
        }
        os << snapshots[col];
    }
    const long long offset = state.offset[row];
    if (offset > 0) os << " + " << offset;
    else if (offset < 0) os << " - " << -offset;
    os << ";";
    return os.str();
}

bool isIdentityCoupledRow(
    const LoopSccCoupledAffineTransform& state,
    std::size_t row) {
    const std::size_t n = state.variables.size();
    if (row >= n || state.matrix.size() != n * n ||
        state.offset.size() != n || state.offset[row] != 0) {
        return false;
    }
    for (std::size_t col = 0; col < n; ++col) {
        const long long expected = row == col ? 1 : 0;
        if (state.matrix[row * n + col] != expected) {
            return false;
        }
    }
    return true;
}


struct ScalarInterval {
    long long lower{0};
    long long upper{0};
};

std::string trimScalarText(std::string text) {
    std::size_t begin = 0;
    while (begin < text.size() &&
           std::isspace(static_cast<unsigned char>(text[begin])) != 0) {
        ++begin;
    }
    std::size_t end = text.size();
    while (end > begin &&
           std::isspace(static_cast<unsigned char>(text[end - 1])) != 0) {
        --end;
    }
    text = text.substr(begin, end - begin);
    if (!text.empty() && text.back() == ';') {
        text.pop_back();
        while (!text.empty() &&
               std::isspace(
                   static_cast<unsigned char>(text.back())) != 0) {
            text.pop_back();
        }
    }
    return text;
}

std::optional<std::pair<long long, long long>>
signedScalarTypeBounds(const std::string& rawType) {
    const std::string type = normalizeTypeSpelling(rawType);
    if (type.find("long long") != std::string::npos) {
        return std::make_pair(
            std::numeric_limits<long long>::min(),
            std::numeric_limits<long long>::max());
    }
    if (type.find("long") != std::string::npos) {
        return std::make_pair(
            static_cast<long long>(
                std::numeric_limits<long>::min()),
            static_cast<long long>(
                std::numeric_limits<long>::max()));
    }
    if (type.find("short") != std::string::npos) {
        return std::make_pair(
            static_cast<long long>(
                std::numeric_limits<short>::min()),
            static_cast<long long>(
                std::numeric_limits<short>::max()));
    }
    if (type == "int" || type == "signed int" ||
        type == "signed") {
        return std::make_pair(
            static_cast<long long>(
                std::numeric_limits<int>::min()),
            static_cast<long long>(
                std::numeric_limits<int>::max()));
    }
    return std::nullopt;
}

bool intervalWithin(
    const ScalarInterval& value,
    const std::pair<long long, long long>& bounds) {
    return value.lower >= bounds.first &&
           value.upper <= bounds.second &&
           value.lower <= value.upper;
}

std::optional<ScalarInterval> intervalFrom128(
    __int128 lower, __int128 upper) {
    if (lower > upper ||
        lower < std::numeric_limits<long long>::min() ||
        upper > std::numeric_limits<long long>::max()) {
        return std::nullopt;
    }
    return ScalarInterval{
        static_cast<long long>(lower),
        static_cast<long long>(upper)};
}

std::optional<ScalarInterval> scaleInterval(
    const ScalarInterval& input,
    long long coefficient) {
    const __int128 a =
        static_cast<__int128>(coefficient) * input.lower;
    const __int128 b =
        static_cast<__int128>(coefficient) * input.upper;
    return intervalFrom128(std::min(a, b), std::max(a, b));
}

std::optional<ScalarInterval> addIntervals(
    const ScalarInterval& lhs,
    const ScalarInterval& rhs) {
    return intervalFrom128(
        static_cast<__int128>(lhs.lower) + rhs.lower,
        static_cast<__int128>(lhs.upper) + rhs.upper);
}

struct DetailedScalarDeclaration {
    std::string type;
    std::string name;
    std::optional<std::string> initializer;
};

std::optional<DetailedScalarDeclaration>
parseDetailedScalarDeclaration(const std::string& raw) {
    const std::string text = trimScalarText(raw);
    static const std::regex scalar(
        "^(?:(?:const|volatile)[ \\t]+)*"
        "((?:signed[ \\t]+)?"
        "(?:short(?:[ \\t]+int)?|int|"
        "long(?:[ \\t]+long)?(?:[ \\t]+int)?))"
        "[ \\t]+([A-Za-z_][A-Za-z0-9_]*)"
        "[ \\t]*(?:=[ \\t]*(.*))?$");
    std::smatch match;
    if (!std::regex_match(text, match, scalar)) {
        return std::nullopt;
    }
    DetailedScalarDeclaration out;
    out.type = normalizeTypeSpelling(match[1].str());
    out.name = match[2].str();
    if (match[3].matched) {
        const std::string init = trimScalarText(match[3].str());
        if (!init.empty()) out.initializer = init;
    }
    return out;
}

std::optional<ScalarInterval> evaluateLinearInterval(
    const std::string& raw,
    const std::unordered_map<std::string, ScalarInterval>& intervals,
    const std::unordered_set<std::string>& declaredNames,
    const ScalarInterval& externalInputRange) {
    std::string text;
    for (unsigned char ch : raw) {
        if (std::isspace(ch) == 0 && ch != ';') {
            text.push_back(static_cast<char>(ch));
        }
    }
    if (text.empty()) return std::nullopt;

    static const std::regex identifier(
        R"(^[A-Za-z_][A-Za-z0-9_]*$)");
    static const std::regex integer(
        R"(^[0-9]+$)");
    static const std::regex intTimesVar(
        R"(^([0-9]+)\*([A-Za-z_][A-Za-z0-9_]*)$)");
    static const std::regex varTimesInt(
        R"(^([A-Za-z_][A-Za-z0-9_]*)\*([0-9]+)$)");

    ScalarInterval total{0, 0};
    std::size_t pos = 0;
    while (pos < text.size()) {
        long long sign = 1;
        if (text[pos] == '+' || text[pos] == '-') {
            sign = text[pos] == '-' ? -1 : 1;
            ++pos;
        }
        if (pos >= text.size()) return std::nullopt;

        const std::size_t begin = pos;
        while (pos < text.size() &&
               text[pos] != '+' && text[pos] != '-') {
            ++pos;
        }
        const std::string term = text.substr(begin, pos - begin);
        if (term.empty()) return std::nullopt;

        long long coefficient = sign;
        std::optional<ScalarInterval> base;
        std::smatch match;
        try {
            if (std::regex_match(term, integer)) {
                const long long value = std::stoll(term);
                base = ScalarInterval{value, value};
            } else if (std::regex_match(term, identifier)) {
                auto found = intervals.find(term);
                if (found != intervals.end()) {
                    base = found->second;
                } else if (declaredNames.find(term) ==
                           declaredNames.end()) {
                    base = externalInputRange;
                } else {
                    return std::nullopt;
                }
            } else if (
                std::regex_match(term, match, intTimesVar)) {
                const long long factor =
                    std::stoll(match[1].str());
                coefficient =
                    static_cast<long long>(
                        static_cast<__int128>(coefficient) *
                        factor);
                const std::string name = match[2].str();
                auto found = intervals.find(name);
                if (found != intervals.end()) {
                    base = found->second;
                } else if (declaredNames.find(name) ==
                           declaredNames.end()) {
                    base = externalInputRange;
                } else {
                    return std::nullopt;
                }
            } else if (
                std::regex_match(term, match, varTimesInt)) {
                const long long factor =
                    std::stoll(match[2].str());
                coefficient =
                    static_cast<long long>(
                        static_cast<__int128>(coefficient) *
                        factor);
                const std::string name = match[1].str();
                auto found = intervals.find(name);
                if (found != intervals.end()) {
                    base = found->second;
                } else if (declaredNames.find(name) ==
                           declaredNames.end()) {
                    base = externalInputRange;
                } else {
                    return std::nullopt;
                }
            } else {
                return std::nullopt;
            }
        } catch (...) {
            return std::nullopt;
        }

        auto scaled = scaleInterval(*base, coefficient);
        if (!scaled) return std::nullopt;
        auto next = addIntervals(total, *scaled);
        if (!next) return std::nullopt;
        total = *next;
    }
    return total;
}

std::optional<std::pair<long long, long long>>
readCoupledBoundedRange(
    std::optional<long long> explicitLower,
    std::optional<long long> explicitUpper) {
    if (explicitLower || explicitUpper) {
        if (!explicitLower || !explicitUpper ||
            *explicitLower > *explicitUpper) {
            return std::nullopt;
        }
        return std::make_pair(*explicitLower, *explicitUpper);
    }

    const char* lowerRaw =
        std::getenv("EPPATHER_LOOP_SCC_COUPLED_RANGE_LOWER");
    const char* upperRaw =
        std::getenv("EPPATHER_LOOP_SCC_COUPLED_RANGE_UPPER");
    if (!lowerRaw || !*lowerRaw || !upperRaw || !*upperRaw) {
        return std::nullopt;
    }
    char* lowerEnd = nullptr;
    char* upperEnd = nullptr;
    const long long lower =
        std::strtoll(lowerRaw, &lowerEnd, 10);
    const long long upper =
        std::strtoll(upperRaw, &upperEnd, 10);
    if (lowerEnd == lowerRaw || *lowerEnd != '\0' ||
        upperEnd == upperRaw || *upperEnd != '\0' ||
        lower > upper) {
        return std::nullopt;
    }
    return std::make_pair(lower, upper);
}

bool applyIntervalAssignment(
    const std::string& raw,
    std::unordered_map<std::string, ScalarInterval>& intervals,
    const std::unordered_map<std::string, std::string>& knownTypes,
    const std::unordered_set<std::string>& declaredNames,
    const ScalarInterval& externalInputRange,
    const std::unordered_set<std::string>& candidateVariables) {
    const std::string text = trimScalarText(raw);
    if (text.empty()) return true;

    if (auto declaration =
            parseDetailedScalarDeclaration(text)) {
        if (!declaration->initializer) {
            intervals.erase(declaration->name);
            return candidateVariables.find(declaration->name) ==
                   candidateVariables.end();
        }
        auto value = evaluateLinearInterval(
            *declaration->initializer, intervals,
            declaredNames, externalInputRange);
        if (!value) {
            intervals.erase(declaration->name);
            return candidateVariables.find(declaration->name) ==
                   candidateVariables.end();
        }
        auto type = knownTypes.find(declaration->name);
        if (type != knownTypes.end()) {
            auto bounds = signedScalarTypeBounds(type->second);
            if (!bounds || !intervalWithin(*value, *bounds)) {
                intervals.erase(declaration->name);
                return candidateVariables.find(declaration->name) ==
                       candidateVariables.end();
            }
        }
        intervals[declaration->name] = *value;
        return true;
    }

    std::smatch match;
    static const std::regex postfix(
        R"(^([A-Za-z_][A-Za-z0-9_]*)\s*(\+\+|--)$)");
    static const std::regex prefix(
        R"(^(\+\+|--)\s*([A-Za-z_][A-Za-z0-9_]*)$)");
    static const std::regex compound(
        R"(^([A-Za-z_][A-Za-z0-9_]*)\s*(\+=|-=)\s*(-?[0-9]+)$)");
    static const std::regex assign(
        R"(^([A-Za-z_][A-Za-z0-9_]*)\s*=\s*(.+)$)");

    std::string lhs;
    std::optional<ScalarInterval> value;
    if (std::regex_match(text, match, postfix)) {
        lhs = match[1].str();
        auto current = intervals.find(lhs);
        if (current != intervals.end()) {
            const long long delta =
                match[2].str() == "++" ? 1 : -1;
            value = addIntervals(
                current->second, ScalarInterval{delta, delta});
        }
    } else if (std::regex_match(text, match, prefix)) {
        lhs = match[2].str();
        auto current = intervals.find(lhs);
        if (current != intervals.end()) {
            const long long delta =
                match[1].str() == "++" ? 1 : -1;
            value = addIntervals(
                current->second, ScalarInterval{delta, delta});
        }
    } else if (std::regex_match(text, match, compound)) {
        lhs = match[1].str();
        auto current = intervals.find(lhs);
        if (current != intervals.end()) {
            long long delta = 0;
            try {
                delta = std::stoll(match[3].str());
            } catch (...) {
                delta = 0;
                current = intervals.end();
            }
            if (current != intervals.end()) {
                if (match[2].str() == "-=") {
                    if (delta ==
                        std::numeric_limits<long long>::min()) {
                        current = intervals.end();
                    } else {
                        delta = -delta;
                    }
                }
                if (current != intervals.end()) {
                    value = addIntervals(
                        current->second,
                        ScalarInterval{delta, delta});
                }
            }
        }
    } else if (std::regex_match(text, match, assign)) {
        lhs = match[1].str();
        value = evaluateLinearInterval(
            match[2].str(), intervals,
            declaredNames, externalInputRange);
    } else {
        return true;
    }

    if (lhs.empty()) return true;
    if (!value) {
        intervals.erase(lhs);
        return candidateVariables.find(lhs) ==
               candidateVariables.end();
    }

    auto type = knownTypes.find(lhs);
    if (type != knownTypes.end()) {
        auto bounds = signedScalarTypeBounds(type->second);
        if (!bounds || !intervalWithin(*value, *bounds)) {
            intervals.erase(lhs);
            return candidateVariables.find(lhs) ==
                   candidateVariables.end();
        }
    }
    intervals[lhs] = *value;
    return true;
}

bool certifyCoupledPreexecutionRanges(
    const std::vector<PathDecision>& prefix,
    CFGNode* loop,
    const LoopSccCoupledAffineCandidate& candidate,
    const std::unordered_map<std::string, std::string>& certifiedTypes,
    const std::string& sourcePrefix,
    long long boundedLower,
    long long boundedUpper,
    bool& entryRangesCertified,
    std::vector<std::string>& diagnostics) {
    entryRangesCertified = false;
    auto reject = [&](const std::string& reason) {
        diagnostics.push_back(reason);
        return false;
    };
    if (boundedLower > boundedUpper) {
        return reject("invalid coupled bounded input domain");
    }
    const ScalarInterval externalInputRange{
        boundedLower, boundedUpper};

    std::vector<DetailedScalarDeclaration> declarations;
    std::unordered_set<std::string> declaredNames;
    std::unordered_set<std::string> ambiguousNames;
    std::unordered_map<std::string, std::string> knownTypes;

    auto collect = [&](const std::string& raw) {
        auto declaration = parseDetailedScalarDeclaration(raw);
        if (!declaration) return;
        if (!declaredNames.insert(declaration->name).second) {
            ambiguousNames.insert(declaration->name);
        }
        knownTypes[declaration->name] = declaration->type;
        declarations.push_back(std::move(*declaration));
    };

    std::stringstream input(sourcePrefix);
    std::string line;
    while (std::getline(input, line)) collect(line);
    if (loop && loop->isFor &&
        !loop->initstmt_str.empty()) {
        collect(loop->initstmt_str);
    }

    std::unordered_set<std::string> candidateVariables(
        candidate.closedForm.variables.begin(),
        candidate.closedForm.variables.end());
    for (const auto& variable : candidateVariables) {
        if (ambiguousNames.find(variable) != ambiguousNames.end()) {
            return reject(
                "ambiguous declaration prevents entry-range proof for " +
                variable);
        }
    }

    std::unordered_map<std::string, ScalarInterval> intervals;
    // Function parameters are represented in vartemp as ordinary
    // uninitialized scalar declarations. Treat every such signed scalar as an
    // unknown value in the configured finite domain; concrete prefix writes
    // below overwrite this conservative interval before the loop.
    for (const auto& declaration : declarations) {
        if (declaration.initializer ||
            ambiguousNames.find(declaration.name) !=
                ambiguousNames.end()) {
            continue;
        }
        auto bounds = signedScalarTypeBounds(declaration.type);
        if (!bounds ||
            !intervalWithin(externalInputRange, *bounds)) {
            continue;
        }
        intervals[declaration.name] = externalInputRange;
    }

    bool progress = true;
    for (std::size_t pass = 0;
         progress && pass <= declarations.size(); ++pass) {
        progress = false;
        for (const auto& declaration : declarations) {
            if (!declaration.initializer ||
                ambiguousNames.find(declaration.name) !=
                    ambiguousNames.end() ||
                intervals.find(declaration.name) != intervals.end()) {
                continue;
            }
            auto value = evaluateLinearInterval(
                *declaration.initializer, intervals,
                declaredNames, externalInputRange);
            if (!value) continue;
            auto bounds = signedScalarTypeBounds(declaration.type);
            if (!bounds || !intervalWithin(*value, *bounds)) {
                continue;
            }
            intervals[declaration.name] = *value;
            progress = true;
        }
    }

    for (const auto& decision : prefix) {
        if (!decision.node) continue;
        if (decision.node->hasCallExpr) {
            return reject(
                "prefix function call invalidates coupled entry ranges");
        }

        std::string text;
        switch (decision.kind) {
            case PathDecisionKind::Code:
                text = decision.node->getCode();
                break;
            case PathDecisionKind::SyntheticCode:
                text = decision.syntheticText;
                break;
            case PathDecisionKind::LoopInit:
                text = decision.node->initstmt_str;
                break;
            case PathDecisionKind::LoopUpdate:
                text = decision.node->expr_str;
                break;
            default:
                break;
        }
        if (text.empty()) continue;
        if (!applyIntervalAssignment(
                text, intervals, knownTypes,
                declaredNames, externalInputRange,
                candidateVariables)) {
            return reject(
                "prefix write is not interval-certifiable: " +
                trimScalarText(text));
        }
    }

    for (const auto& variable : candidate.closedForm.variables) {
        auto interval = intervals.find(variable);
        if (interval == intervals.end()) {
            return reject(
                "missing loop-entry interval for " + variable);
        }
        auto type = certifiedTypes.find(variable);
        if (type == certifiedTypes.end()) {
            return reject(
                "missing certified type for loop-entry interval " +
                variable);
        }
        auto bounds = signedScalarTypeBounds(type->second);
        if (!bounds || !intervalWithin(interval->second, *bounds)) {
            return reject(
                "loop-entry interval exceeds signed type range for " +
                variable);
        }
    }

    const auto& state = candidate.closedForm;
    const std::size_t n = state.variables.size();
    for (std::size_t row = 0; row < n; ++row) {
        if (isIdentityCoupledRow(state, row)) continue;

        auto targetType = certifiedTypes.find(state.variables[row]);
        if (targetType == certifiedTypes.end()) {
            return reject(
                "missing target type for coupled matrix row");
        }
        auto bounds = signedScalarTypeBounds(targetType->second);
        if (!bounds) {
            return reject(
                "unsupported signed target type for coupled matrix row");
        }

        ScalarInterval running{0, 0};
        for (std::size_t col = 0; col < n; ++col) {
            const long long coefficient =
                state.matrix[row * n + col];
            if (coefficient == 0) continue;
            const auto inputInterval =
                intervals.find(state.variables[col]);
            if (inputInterval == intervals.end()) {
                return reject(
                    "missing source entry interval for coupled matrix row");
            }
            auto term = scaleInterval(
                inputInterval->second, coefficient);
            if (!term || !intervalWithin(*term, *bounds)) {
                return reject(
                    "coupled matrix multiplication may overflow before execution");
            }
            auto sum = addIntervals(running, *term);
            if (!sum || !intervalWithin(*sum, *bounds)) {
                return reject(
                    "coupled matrix accumulated sum may overflow before execution");
            }
            running = *sum;
        }
        if (state.offset[row] != 0) {
            auto finalValue = addIntervals(
                running,
                ScalarInterval{
                    state.offset[row],
                    state.offset[row]});
            if (!finalValue ||
                !intervalWithin(*finalValue, *bounds)) {
                return reject(
                    "coupled matrix offset may overflow before execution");
            }
        }
    }

    diagnostics.push_back(
        "compressed coupled arithmetic preexecution overflow certificate");
    return true;
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


std::optional<LoopSccCoupledAffineDecisionPlan>
buildCoupledAffineValidationDecisions(
    CFGNode* loop,
    const LoopSccGraphInfo& graph,
    std::size_t candidateIndex,
    const std::vector<PathDecision>& decisions,
    const std::string& sourcePrefix) {
    if (!loop ||
        candidateIndex >= graph.coupledAffineCandidates.size()) {
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
        decisions.begin() +
            static_cast<std::ptrdiff_t>(firstTrue));
    auto plan =
        buildLoopSccCoupledAffineValidationDecisions(
            prefix, loop, graph, candidateIndex, sourcePrefix);
    if (!plan) return std::nullopt;
    if (!plan->typeCertified ||
        !plan->snapshotParallelized) {
        return plan;
    }

    plan->decisions.insert(
        plan->decisions.end(),
        decisions.begin() +
            static_cast<std::ptrdiff_t>(finalFalse + 1),
        decisions.end());
    return plan;
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

std::size_t fixedMemoryTransformMems(
    const LoopSccMemoryCellTransform& transform) {
    // epat++ MEMS counts the lvalue array subscript once for the write, plus
    // one source-cell read when the affine result depends on the old value.
    return transform.scale == 0 ? 1u : 2u;
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
        loop, PathDecisionKind::SyntheticMemoryCheckpoint, {}});
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
        compressedSummaryMems += fixedMemoryTransformMems(transform);
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


bool certifyFixedMemoryPreexecution(
    const LoopSccGraphInfo& graph,
    const LoopSccMemorySummaryCandidate& candidate,
    const LoopSccCycleInfo& cycle,
    const std::unordered_map<std::string, std::size_t>& extents,
    const std::vector<LoopSccConstantPointerAlias>& pointerAliases,
    std::vector<std::string>& diagnostics) {
    auto reject = [&](const std::string& reason) {
        diagnostics.push_back(reason);
        return false;
    };

    if (!graph.complete) {
        return reject("SPath graph is incomplete");
    }
    if (graph.provedTripCount < 0 ||
        candidate.totalIterations != graph.provedTripCount) {
        return reject("candidate trip count is not the proved graph trip count");
    }
    if (!cycle.determinate || !cycle.phaseGuardsProved ||
        cycle.period == 0 || cycle.spathOrder.size() != cycle.period) {
        return reject("cycle/phase certificate is incomplete");
    }
    if (!candidate.exact || candidate.closedFormTransforms.empty()) {
        return reject("fixed-cell closed form is not exact");
    }

    std::set<std::pair<std::string, long long>> candidateCells;
    for (const auto& transform : candidate.closedFormTransforms) {
        const auto extent = extents.find(transform.region);
        if (extent == extents.end()) {
            return reject(
                "summary region is not a unique fixed local array: " +
                transform.region);
        }
        if (transform.index < 0 ||
            static_cast<unsigned long long>(transform.index) >=
                static_cast<unsigned long long>(extent->second)) {
            return reject(
                "summary cell is outside fixed local array bounds: " +
                transform.region + "[" +
                std::to_string(transform.index) + "]");
        }
        candidateCells.emplace(transform.region, transform.index);
    }

    const long long fullPeriods =
        candidate.totalIterations /
        static_cast<long long>(cycle.period);
    const std::size_t residual =
        static_cast<std::size_t>(
            candidate.totalIterations %
            static_cast<long long>(cycle.period));

    std::set<std::size_t> participatingPaths;
    if (fullPeriods > 0) {
        participatingPaths.insert(
            cycle.spathOrder.begin(), cycle.spathOrder.end());
    }
    for (std::size_t r = 0; r < residual; ++r) {
        participatingPaths.insert(
            cycle.spathOrder[
                (candidate.entryPhase + r) % cycle.period]);
    }
    if (participatingPaths.empty()) {
        return reject("no SPath participates in the summarized execution");
    }

    static const std::regex fixedArrayAccess(
        R"(([A-Za-z_][A-Za-z0-9_]*)[[:space:]]*\[[[:space:]]*(-?[0-9]+)[[:space:]]*\])");
    static const std::regex compoundMemoryAssign(
        R"((\+=|-=|\*=|/=|%=|&=|\|=|\^=|<<=|>>=))");

    std::unordered_map<
        std::string, std::pair<std::string, long long>> aliasMap;
    for (const auto& alias : pointerAliases) {
        aliasMap.emplace(
            alias.pointer,
            std::make_pair(alias.region, alias.index));
    }
    static const std::regex pointerSelfAdd(
        R"(^[[:space:]]*\*[[:space:]]*([A-Za-z_][A-Za-z0-9_]*)[[:space:]]*=[[:space:]]*\*[[:space:]]*\1[[:space:]]*([+-])[[:space:]]*([0-9]+)[[:space:]]*;?[[:space:]]*$)");
    static const std::regex pointerCompound(
        R"(^[[:space:]]*\*[[:space:]]*([A-Za-z_][A-Za-z0-9_]*)[[:space:]]*(\+=|-=)[[:space:]]*(-?[0-9]+)[[:space:]]*;?[[:space:]]*$)");
    static const std::regex pointerConstant(
        R"(^[[:space:]]*\*[[:space:]]*([A-Za-z_][A-Za-z0-9_]*)[[:space:]]*=[[:space:]]*(-?[0-9]+)[[:space:]]*;?[[:space:]]*$)");

    auto certifiedPointerAccess =
        [&](const LoopSccMemoryAccessInfo& access) -> bool {
            std::smatch match;
            std::string pointer;
            std::size_t expectedPointerMems = 0;
            if (std::regex_match(
                    access.sourceText, match, pointerSelfAdd)) {
                pointer = match[1].str();
                expectedPointerMems = 2;
            } else if (std::regex_match(
                           access.sourceText, match,
                           pointerCompound)) {
                pointer = match[1].str();
                expectedPointerMems = 2;
            } else if (std::regex_match(
                           access.sourceText, match,
                           pointerConstant)) {
                pointer = match[1].str();
                expectedPointerMems = 1;
            } else {
                return false;
            }
            auto alias = aliasMap.find(pointer);
            if (alias == aliasMap.end() ||
                access.pointerDereferences != expectedPointerMems ||
                access.arraySubscripts != 0) {
                return false;
            }
            return candidateCells.find(alias->second) !=
                   candidateCells.end();
        };

    __int128 expectedMems = 0;
    auto addPathMems = [&](std::size_t pathId, long long multiplier) -> bool {
        if (pathId >= graph.spaths.size() || multiplier < 0) return false;
        expectedMems +=
            static_cast<__int128>(graph.spaths[pathId].observedMems) *
            multiplier;
        return expectedMems <=
            static_cast<__int128>(
                std::numeric_limits<std::size_t>::max());
    };
    if (fullPeriods > 0) {
        for (std::size_t pathId : cycle.spathOrder) {
            if (!addPathMems(pathId, fullPeriods)) {
                return reject("MEMS certificate overflow");
            }
        }
    }
    for (std::size_t r = 0; r < residual; ++r) {
        const std::size_t pathId =
            cycle.spathOrder[
                (candidate.entryPhase + r) % cycle.period];
        if (!addPathMems(pathId, 1)) {
            return reject("MEMS certificate overflow");
        }
    }
    if (static_cast<std::size_t>(expectedMems) !=
        candidate.observedMems) {
        return reject("candidate MEMS differs from exact SPath sum");
    }

    for (std::size_t pathId : participatingPaths) {
        if (pathId >= graph.spaths.size()) {
            return reject("cycle references an unknown SPath");
        }
        const auto& path = graph.spaths[pathId];
        if (!path.returnsToHeader || path.exitsLoop) {
            return reject("participating SPath is not an exact loop backedge");
        }
        if (!path.guardModelComplete ||
            !path.memoryAccessModelComplete ||
            !path.memoryTransitionModelComplete ||
            !path.memorySummaryEffectSafe) {
            return reject("participating SPath has incomplete guard/effect/memory model");
        }
        if (path.writesMemory && path.memoryCellTransforms.empty()) {
            return reject("memory write lacks fixed-cell transition");
        }

        __int128 explainedPathMems =
            static_cast<__int128>(
                path.certifiedNestedMemoryMems);
        for (const auto& access : path.memoryAccesses) {
            if (!access.precise) {
                return reject("memory access MEMS observation is imprecise");
            }
            if (access.pointerDereferences != 0) {
                if (!certifiedPointerAccess(access)) {
                    return reject(
                        "pointer dereference is not a unique constant fixed-array alias");
                }
                // This dereference has been fully localized to a candidate
                // fixed cell and its lexical/implicit MEMS count is exact.
                explainedPathMems += access.mems();
                continue;
            }

            std::size_t lexicalArrayAccesses = 0;
            for (std::sregex_iterator it(
                     access.sourceText.begin(),
                     access.sourceText.end(),
                     fixedArrayAccess),
                 end;
                 it != end; ++it) {
                ++lexicalArrayAccesses;
                const std::string region = (*it)[1].str();
                const long long index =
                    std::strtoll((*it)[2].str().c_str(), nullptr, 10);
                const auto extent = extents.find(region);
                if (extent == extents.end()) {
                    return reject(
                        "memory access region is not a unique fixed local array: " +
                        region);
                }
                if (index < 0 ||
                    static_cast<unsigned long long>(index) >=
                        static_cast<unsigned long long>(extent->second)) {
                    return reject(
                        "memory access is outside fixed local array bounds: " +
                        region + "[" + std::to_string(index) + "]");
                }
            }

            const bool compound =
                access.writesMemory &&
                std::regex_search(
                    access.sourceText, compoundMemoryAssign);
            const std::size_t expectedArrayMems =
                lexicalArrayAccesses + (compound ? 1u : 0u);
            if (expectedArrayMems != access.arraySubscripts) {
                return reject(
                    "array MEMS tokens are not fully explained by constant-index accesses");
            }
            if (access.arraySubscripts > 0 &&
                lexicalArrayAccesses == 0) {
                return reject("array access could not be structurally localized");
            }
            explainedPathMems += access.mems();
        }
        if (explainedPathMems < 0 ||
            explainedPathMems >
                static_cast<__int128>(
                    std::numeric_limits<std::size_t>::max()) ||
            static_cast<std::size_t>(explainedPathMems) !=
                path.observedMems) {
            return reject(
                "SPath MEMS are not fully explained by lexical accesses and certified nested summaries");
        }

        for (const auto& transform : path.memoryCellTransforms) {
            const auto extent = extents.find(transform.region);
            if (extent == extents.end() || transform.index < 0 ||
                static_cast<unsigned long long>(transform.index) >=
                    static_cast<unsigned long long>(extent->second)) {
                return reject("SPath fixed-cell transition is outside certified region");
            }
            if (candidateCells.find(
                    {transform.region, transform.index}) ==
                candidateCells.end()) {
                return reject("SPath memory write is absent from full-loop closed form");
            }
        }
    }

    diagnostics.push_back(
        "complete fixed-local-array frame/effect/MEMS certificate");
    return true;
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



std::optional<LoopSccCoupledAffineDecisionPlan>
buildLoopSccCoupledAffineValidationDecisions(
    const std::vector<PathDecision>& prefix,
    CFGNode* loop,
    const LoopSccGraphInfo& graph,
    std::size_t candidateIndex,
    const std::string& sourcePrefix,
    std::optional<long long> boundedLower,
    std::optional<long long> boundedUpper) {
    if (!loop ||
        candidateIndex >= graph.coupledAffineCandidates.size()) {
        return std::nullopt;
    }
    const auto& candidate =
        graph.coupledAffineCandidates[candidateIndex];
    if (!candidate.exact ||
        candidate.cycleIndex >= graph.cycles.size()) {
        return std::nullopt;
    }
    const auto& cycle = graph.cycles[candidate.cycleIndex];

    LoopSccCoupledAffineDecisionPlan plan;
    plan.coverageSlots = candidate.coverageSlots;

    std::unordered_map<std::string, std::string> certifiedTypes;
    plan.typeCertified =
        certifyCoupledAffineTypes(
            loop, graph, candidate, sourcePrefix,
            certifiedTypes, plan.certificateDiagnostics);
    if (!plan.typeCertified) {
        return plan;
    }

    if (const auto boundedRange =
            readCoupledBoundedRange(
                boundedLower, boundedUpper)) {
        plan.boundedRangeLower = boundedRange->first;
        plan.boundedRangeUpper = boundedRange->second;
        bool entryRangesCertified = false;
        plan.preexecutionOverflowCertified =
            certifyCoupledPreexecutionRanges(
                prefix, loop, candidate, certifiedTypes,
                sourcePrefix, boundedRange->first,
                boundedRange->second,
                entryRangesCertified,
                plan.certificateDiagnostics);
        plan.entryRangeCertified =
            entryRangesCertified;
    } else {
        plan.certificateDiagnostics.push_back(
            "bounded input domain unavailable for preexecution range proof");
    }

    const std::string stem =
        coupledSnapshotStem(loop, candidateIndex, sourcePrefix);
    if (stem.empty()) {
        plan.certificateDiagnostics.push_back(
            "unable to allocate collision-free snapshot namespace");
        return plan;
    }

    const auto& state = candidate.closedForm;
    std::vector<std::string> snapshots;
    snapshots.reserve(state.variables.size());

    plan.decisions = prefix;
    plan.decisions.push_back(PathDecision{
        loop, PathDecisionKind::TrueBranch, {}});

    const std::size_t entryPathId =
        cycle.spathOrder[candidate.entryPhase];
    if (entryPathId >= graph.spaths.size()) {
        plan.certificateDiagnostics.push_back(
            "entry phase references an absent SPath");
        return plan;
    }
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
            plan.certificateDiagnostics.push_back(
                "entry phase guard cannot be rendered");
            return plan;
        }
    }

    for (std::size_t i = 0; i < state.variables.size(); ++i) {
        const std::string& variable = state.variables[i];
        auto type = certifiedTypes.find(variable);
        if (type == certifiedTypes.end()) {
            plan.certificateDiagnostics.push_back(
                "missing certified snapshot type for " + variable);
            return plan;
        }
        const std::string snapshot =
            stem + std::to_string(i);
        snapshots.push_back(snapshot);
        plan.snapshotVariables.push_back(snapshot);
        plan.decisions.push_back(PathDecision{
            loop, PathDecisionKind::SyntheticCode,
            type->second + " " + snapshot + " = " +
                variable + ";", 0});
    }

    for (std::size_t row = 0;
         row < state.variables.size(); ++row) {
        if (isIdentityCoupledRow(state, row)) continue;
        const std::string assignment =
            renderCoupledAffineRow(state, row, snapshots);
        if (assignment.empty()) {
            plan.certificateDiagnostics.push_back(
                "coupled affine matrix row cannot be rendered");
            return plan;
        }
        plan.decisions.push_back(PathDecision{
            loop, PathDecisionKind::SyntheticCode,
            assignment, 0});
    }

    plan.decisions.push_back(PathDecision{
        loop, PathDecisionKind::FalseBranch, {}, 0});
    plan.snapshotParallelized = true;
    plan.runtimeShortcutEligible = false;
    plan.certificateDiagnostics.push_back(
        "entry state snapshotted before parallel matrix assignment");
    return plan;
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
    const auto pointerAliases =
        LoopSccAdapter::parseConstantPointerAliases(sourcePrefix);

    LoopSccMemoryAccelerationDecisionPlan plan;
    plan.preexecutionCertified =
        certifyFixedMemoryPreexecution(
            graph, candidate, cycle, extents, pointerAliases,
            plan.certificateDiagnostics);
    plan.unfoldedMems = candidate.observedMems;
    plan.decisions = prefix;
    plan.decisions.push_back(PathDecision{
        loop, PathDecisionKind::SyntheticMemoryCheckpoint, {}, 0});
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
        plan.compressedSummaryMems +=
            fixedMemoryTransformMems(transform);
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
            case PathDecisionKind::SyntheticMemoryCheckpoint: {
                // Reserved implementation marker. epat++ intercepts this
                // declaration and snapshots the current whole-memory state
                // without allocating a user-visible object.
                script += "int __eppather_loopscc_mem_checkpoint = 0;\n";
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
    CFGNode* memoryCheckpointLoop = nullptr;
    CFGNode* onlyMemorySummaryLoop = nullptr;
    CFGNode* onlyComposedMemorySummaryLoop = nullptr;
    std::size_t memorySummaryLoopCount = 0;
    std::size_t composedMemorySummaryLoopCount = 0;
    if (envEnabled("EPPATHER_LOOP_SCC_ANALYZE")) {
        for (CFGNode* loop : provenanceLoops) {
            auto graph =
                LoopSccAdapter::analyzeWithConstantPointerAliases(
                    loop, sourcePrefix_);
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
            for (const auto& candidate :
                 graph.coupledAffineCandidates) {
                if (!candidate.exact) continue;
                for (const auto& variable :
                     candidate.closedForm.variables) {
                    if (std::find(
                            provenanceVariables.begin(),
                            provenanceVariables.end(),
                            variable) == provenanceVariables.end()) {
                        provenanceVariables.push_back(variable);
                    }
                }
            }
            for (const auto& spath : graph.spaths) {
                if (!spath.memoryCellTransforms.empty()) {
                    memoryProvenanceNeeded = true;
                    break;
                }
            }
            if (!graph.memorySummaryCandidates.empty()) {
                ++memorySummaryLoopCount;
                onlyMemorySummaryLoop =
                    memorySummaryLoopCount == 1 ? loop : nullptr;
                if (graph.insideOutNestedMemorySummaryCount > 0) {
                    ++composedMemorySummaryLoopCount;
                    onlyComposedMemorySummaryLoop =
                        composedMemorySummaryLoopCount == 1
                            ? loop
                            : nullptr;
                }
            }
            loopSccAnalysis.emplace(loop, std::move(graph));
        }
    }

    // A nested fixed-memory outer loop intentionally coexists with the
    // inner loop's own candidate. Prefer the unique composed outer candidate:
    // it represents the complete inside-out effect and is the correct loop
    // entry for whole-memory provenance. If there is no unique composed
    // candidate, retain the legacy single-memory-loop requirement.
    if (composedMemorySummaryLoopCount == 1) {
        memoryCheckpointLoop = onlyComposedMemorySummaryLoop;
    } else if (memorySummaryLoopCount == 1) {
        memoryCheckpointLoop = onlyMemorySummaryLoop;
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
    auto solverDecisions = decisions;
    if (memoryProvenanceNeeded &&
        memoryCheckpointLoop) {
        bool alreadyCheckpointed = false;
        for (const auto& decision : solverDecisions) {
            if (decision.kind ==
                PathDecisionKind::SyntheticMemoryCheckpoint) {
                alreadyCheckpointed = true;
                break;
            }
        }
        if (!alreadyCheckpointed) {
            auto insertion = std::find_if(
                solverDecisions.begin(), solverDecisions.end(),
                [&](const PathDecision& decision) {
                    return decision.node == memoryCheckpointLoop &&
                           decision.kind ==
                               PathDecisionKind::TrueBranch;
                });
            if (insertion != solverDecisions.end()) {
                solverDecisions.insert(
                    insertion,
                    PathDecision{
                        memoryCheckpointLoop,
                        PathDecisionKind::SyntheticMemoryCheckpoint,
                        {}, 0});
            }
        }
    }
    epat::setSsaProvenanceVariables(provenanceVariables);
    epat::setMemorySsaProvenanceEnabled(memoryProvenanceNeeded);
    EpatResult result = solveScript(render(solverDecisions));
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
                for (const auto& candidate :
                     graph.coupledAffineCandidates) {
                    if (!candidate.exact ||
                        candidate.cycleIndex != trace.cycleIndex ||
                        candidate.entryPhase != trace.entryPhase ||
                        candidate.totalIterations !=
                            static_cast<long long>(
                                trace.observedIterations)) {
                        continue;
                    }
                    std::unordered_map<std::string, std::string>
                        certifiedTypes;
                    std::vector<std::string> certificateDiagnostics;
                    if (!certifyCoupledAffineTypes(
                            loop, graph, candidate, sourcePrefix_,
                            certifiedTypes, certificateDiagnostics)) {
                        for (const auto& diagnostic :
                             certificateDiagnostics) {
                            result.loopStateSummaryDiagnostics.push_back(
                                "loopscc coupled: " + diagnostic);
                        }
                        continue;
                    }
                    result.loopSccCoupledAffineStateSummaries.push_back(
                        LoopSccCoupledAffineStateSummary{
                            candidate.closedForm.variables,
                            candidate.closedForm.matrix,
                            candidate.closedForm.offset,
                            candidate.period,
                            trace.observedIterations});
                    result.loopStateSummaryDiagnostics.push_back(
                        "loopscc: type-certified coupled affine summary matched unfolded path");
                }
            }

            if (trace.complete && trace.matchedDeterminateCycle &&
                memoryCheckpointLoop == loop) {
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
                        if (extent == fixedArrayExtents.end()) {
                            fixedRegionBoundsOk = false;
                            result.loopStateSummaryDiagnostics.push_back(
                                "loopscc: rejected fixed-cell summary without unique fixed-array extent " +
                                relation.region);
                            break;
                        }
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
                                candidate.observedMems,
                                fixedArrayExtents.at(
                                    relation.region)});
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
                trace.complete && trace.matchedDeterminateCycle) {
                for (std::size_t candidateIndex = 0;
                     candidateIndex <
                         graph.coupledAffineCandidates.size();
                     ++candidateIndex) {
                    const auto& candidate =
                        graph.coupledAffineCandidates[candidateIndex];
                    if (!candidate.exact ||
                        candidate.cycleIndex != trace.cycleIndex ||
                        candidate.entryPhase != trace.entryPhase ||
                        candidate.totalIterations !=
                            static_cast<long long>(
                                trace.observedIterations)) {
                        continue;
                    }

                    LoopSccCoupledAffineValidation validation;
                    validation.loopCondition = loop->cond_str;
                    validation.attempted = true;
                    validation.originalDecisionCount =
                        decisions.size();
                    validation.baselineMem = result.mem;

                    auto compressed =
                        buildCoupledAffineValidationDecisions(
                            loop, graph, candidateIndex,
                            decisions, sourcePrefix_);
                    if (compressed) {
                        validation.typeCertified =
                            compressed->typeCertified;
                        validation.snapshotParallelized =
                            compressed->snapshotParallelized;
                        validation.entryRangeCertified =
                            compressed->entryRangeCertified;
                        validation.preexecutionOverflowCertified =
                            compressed->preexecutionOverflowCertified;
                        validation.certificateDiagnostics =
                            compressed->certificateDiagnostics;

                        if (validation.typeCertified &&
                            validation.snapshotParallelized) {
                            validation.compressedDecisionCount =
                                compressed->decisions.size();

                            epat::setSsaProvenanceVariables(
                                provenanceVariables);
                            EpatResult compressedResult =
                                solveScript(
                                    render(compressed->decisions));
                            epat::clearSsaProvenanceVariables();

                            validation.compressedMem =
                                compressedResult.mem;
                            validation.compressedSmt =
                                compressedResult.smt;
                            validation.statusMatched =
                                compressedResult.status ==
                                result.status;
                            validation.memMatched =
                                compressedResult.mem ==
                                result.mem;
                            validation.matched =
                                validation.statusMatched &&
                                validation.memMatched &&
                                validation.compressedDecisionCount <
                                    validation.originalDecisionCount;

                            result.loopStateSummaryDiagnostics.push_back(
                                validation.matched
                                    ? "loopscc: coupled affine compressed validation matched"
                                    : "loopscc: coupled affine compressed validation mismatch");
                        } else {
                            result.loopStateSummaryDiagnostics.push_back(
                                "loopscc: coupled affine validation rejected by type/snapshot certificate");
                        }
                    } else {
                        result.loopStateSummaryDiagnostics.push_back(
                            "loopscc: failed to construct coupled affine validation path");
                    }
                    result.loopSccCoupledAffineValidations.push_back(
                        std::move(validation));
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
