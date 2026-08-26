#ifndef PSYCHE_C_LOOP_BOUND_PREDICTOR_H__
#define PSYCHE_C_LOOP_BOUND_PREDICTOR_H__

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <limits>
#include <regex>
#include <string>

namespace psy { namespace C {

enum class LoopBoundConfidence { Exact, Conservative, Fallback };

struct LoopBoundPrediction {
    int iterations;
    LoopBoundConfidence confidence;
    std::string reason;
};

// A deliberately small, side-effect-free pre-analysis for canonical C loops.
// It proves affine induction-variable bounds.  Unsupported/data-dependent loops
// use fallbackIterations; every result is clamped by safetyCap.
class LoopBoundPredictor {
public:
    static LoopBoundPrediction predict(const std::string& init,
                                       const std::string& condition,
                                       const std::string& update,
                                       int safetyCap,
                                       int fallbackIterations = 3) {
        const int cap = std::max(0, safetyCap);
        const int fallback = std::min(cap, std::max(0, fallbackIterations));
        std::smatch m;
        static const std::regex initRe(
            "(?:^|[;[:space:]])(?:[A-Za-z_][A-Za-z0-9_]*[[:space:]]+)*([A-Za-z_][A-Za-z0-9_]*)[[:space:]]*=[[:space:]]*(-?[0-9]+)[[:space:]]*;?$");
        if (!std::regex_search(init, m, initRe))
            return {fallback, LoopBoundConfidence::Fallback, "non-constant or missing induction initializer"};

        const std::string variable = m[1].str();
        const long long start = std::strtoll(m[2].str().c_str(), nullptr, 10);
        const std::string id = "\\b" + variable + "\\b";
        const std::regex condRe(id + "[[:space:]]*(<=|<|>=|>)[[:space:]]*(-?[0-9]+)");
        if (!std::regex_search(condition, m, condRe))
            return {fallback, LoopBoundConfidence::Fallback, "condition is not an affine constant bound"};
        const std::string op = m[1].str();
        const long long limit = std::strtoll(m[2].str().c_str(), nullptr, 10);

        long long step = 0;
        const std::regex incRe(id + "[[:space:]]*(\\+\\+|--)");
        const std::regex compoundRe(id + "[[:space:]]*(\\+=|-=)[[:space:]]*([0-9]+)");
        const std::regex assignRe(id + "[[:space:]]*=[[:space:]]*" + id + "[[:space:]]*([+-])[[:space:]]*([0-9]+)");
        if (std::regex_search(update, m, incRe)) {
            step = m[1].str() == "++" ? 1 : -1;
        } else if (std::regex_search(update, m, compoundRe)) {
            const long long magnitude = std::strtoll(m[2].str().c_str(), nullptr, 10);
            step = m[1].str() == "-=" ? -magnitude : magnitude;
        } else if (std::regex_search(update, m, assignRe)) {
            const long long magnitude = std::strtoll(m[2].str().c_str(), nullptr, 10);
            step = m[1].str() == "-" ? -magnitude : magnitude;
        }
        if (step == 0)
            return {fallback, LoopBoundConfidence::Fallback, "update is not a non-zero affine step"};

        const bool ascending = op == "<" || op == "<=";
        if ((ascending && step < 0) || (!ascending && step > 0))
            return {fallback, LoopBoundConfidence::Fallback, "step does not progress toward loop exit"};

        long long distance = ascending ? limit - start : start - limit;
        if ((ascending && ((op == "<" && start >= limit) || (op == "<=" && start > limit))) ||
            (!ascending && ((op == ">" && start <= limit) || (op == ">=" && start < limit))))
            return {0, LoopBoundConfidence::Exact, "loop condition is initially false"};
        if (op == "<=" || op == ">=") ++distance;
        const long long magnitude = std::llabs(step);
        const long long iterations = (distance + magnitude - 1) / magnitude;
        return {static_cast<int>(std::min<long long>(cap, iterations)),
                iterations <= cap ? LoopBoundConfidence::Exact : LoopBoundConfidence::Conservative,
                iterations <= cap ? "proved affine induction bound" : "proved bound clamped by safety cap"};
    }
};

}} // namespace psy::C

#endif
