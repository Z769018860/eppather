#ifndef PSYCHE_C_LOOP_BOUND_PREDICTOR_H__
#define PSYCHE_C_LOOP_BOUND_PREDICTOR_H__

#include <algorithm>
#include <cstdlib>
#include <limits>
#include <regex>
#include <string>

namespace psy { namespace C {

enum class LoopBoundConfidence { Exact, Conservative, Fallback };

// The selected handling mode is intentionally independent from the callers.
// DFS, DFS2, MaxMemsDP and GreedyDFS can therefore share exactly the same
// decision and cannot silently analyse different bounded programs.
enum class LoopHandlingMode {
    ExactSummary,       // a closed-form affine trip-count was proved
    ConservativeUnroll,// the proof exists but maxloop truncates it
    AdaptiveFallback   // unsupported/data-dependent loop; use the safe budget
};

struct LoopBoundPrediction {
    int iterations{0};
    LoopBoundConfidence confidence{LoopBoundConfidence::Fallback};
    std::string reason;
    LoopHandlingMode mode{LoopHandlingMode::AdaptiveFallback};
    std::string inductionVariable;
    long long start{0};
    long long step{0};
    long long limit{0};
    std::string relation;

    bool exact() const {
        return confidence == LoopBoundConfidence::Exact &&
               mode == LoopHandlingMode::ExactSummary;
    }
};

// Hybrid loop pre-analysis.
//
// For canonical affine loops it computes a closed-form trip-count summary.  This
// is an exact loop summary for the induction variable and avoids guessing an
// arbitrary small maxloop.  If the exact count exceeds safetyCap, callers use a
// conservative bounded unfolding.  Unsupported/data-dependent loops retain the
// adaptive fallback budget.  A future LoopSCC adapter can return the same
// LoopBoundPrediction contract without changing DFS/DP call sites.
class LoopBoundPredictor {
public:
    static LoopBoundPrediction predict(const std::string& init,
                                       const std::string& condition,
                                       const std::string& update,
                                       int safetyCap,
                                       int fallbackIterations = 3) {
        const int cap = std::max(0, safetyCap);
        const int fallback = std::min(cap, std::max(0, fallbackIterations));

        auto unsupported = [&](const std::string& why) {
            LoopBoundPrediction p;
            p.iterations = fallback;
            p.confidence = LoopBoundConfidence::Fallback;
            p.reason = why;
            p.mode = LoopHandlingMode::AdaptiveFallback;
            return p;
        };

        std::smatch m;
        static const std::regex initRe(
            "(?:^|[;[:space:]])(?:[A-Za-z_][A-Za-z0-9_]*[[:space:]]+)*"
            "([A-Za-z_][A-Za-z0-9_]*)[[:space:]]*=[[:space:]]*"
            "(-?[0-9]+)[[:space:]]*;?$");
        if (!std::regex_search(init, m, initRe))
            return unsupported("non-constant or missing induction initializer");

        const std::string variable = m[1].str();
        const long long start = std::strtoll(m[2].str().c_str(), nullptr, 10);
        const std::string id = "\\b" + variable + "\\b";
        const std::string integer = "(-?[0-9]+)";

        std::string op;
        long long limit = 0;
        const std::regex directRe(
            id + "[[:space:]]*(<=|<|>=|>)[[:space:]]*" + integer);
        const std::regex reversedRe(
            integer + "[[:space:]]*(<=|<|>=|>)[[:space:]]*" + id);
        if (std::regex_search(condition, m, directRe)) {
            op = m[1].str();
            limit = std::strtoll(m[2].str().c_str(), nullptr, 10);
        } else if (std::regex_search(condition, m, reversedRe)) {
            limit = std::strtoll(m[1].str().c_str(), nullptr, 10);
            const std::string reversed = m[2].str();
            if (reversed == "<") op = ">";
            else if (reversed == "<=") op = ">=";
            else if (reversed == ">") op = "<";
            else op = "<=";
        } else {
            return unsupported("condition is not an affine constant bound");
        }

        long long step = 0;
        const std::regex postfixRe(id + "[[:space:]]*(\\+\\+|--)");
        const std::regex prefixRe("(\\+\\+|--)[[:space:]]*" + id);
        const std::regex compoundRe(
            id + "[[:space:]]*(\\+=|-=)[[:space:]]*([0-9]+)");
        const std::regex assignRe(
            id + "[[:space:]]*=[[:space:]]*" + id +
            "[[:space:]]*([+-])[[:space:]]*([0-9]+)");
        if (std::regex_search(update, m, postfixRe) ||
            std::regex_search(update, m, prefixRe)) {
            step = m[1].str() == "++" ? 1 : -1;
        } else if (std::regex_search(update, m, compoundRe)) {
            const long long magnitude =
                std::strtoll(m[2].str().c_str(), nullptr, 10);
            step = m[1].str() == "-=" ? -magnitude : magnitude;
        } else if (std::regex_search(update, m, assignRe)) {
            const long long magnitude =
                std::strtoll(m[2].str().c_str(), nullptr, 10);
            step = m[1].str() == "-" ? -magnitude : magnitude;
        }
        if (step == 0)
            return unsupported("update is not a non-zero affine step");

        const bool ascending = op == "<" || op == "<=";
        if ((ascending && step < 0) || (!ascending && step > 0))
            return unsupported("step does not progress toward loop exit");

        long long iterations = 0;
        const long long magnitude = std::llabs(step);
        if (ascending) {
            if ((op == "<" && start < limit) || (op == "<=" && start <= limit)) {
                const long long distance = limit - start;
                iterations = op == "<"
                    ? (distance + magnitude - 1) / magnitude
                    : distance / magnitude + 1;
            }
        } else {
            if ((op == ">" && start > limit) || (op == ">=" && start >= limit)) {
                const long long distance = start - limit;
                iterations = op == ">"
                    ? (distance + magnitude - 1) / magnitude
                    : distance / magnitude + 1;
            }
        }

        LoopBoundPrediction p;
        p.iterations = static_cast<int>(
            std::min<long long>(cap, std::max<long long>(0, iterations)));
        p.confidence = iterations <= cap
            ? LoopBoundConfidence::Exact
            : LoopBoundConfidence::Conservative;
        p.reason = iterations <= cap
            ? "proved affine trip-count summary"
            : "proved affine trip count clamped by safety cap";
        p.mode = iterations <= cap
            ? LoopHandlingMode::ExactSummary
            : LoopHandlingMode::ConservativeUnroll;
        p.inductionVariable = variable;
        p.start = start;
        p.step = step;
        p.limit = limit;
        p.relation = op;
        return p;
    }
};

}} // namespace psy::C

#endif
