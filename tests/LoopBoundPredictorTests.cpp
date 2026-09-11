#include "C/syntax/LoopBoundPredictor.h"
#include <iostream>
#include <string>
#include <vector>

using psy::C::LoopBoundConfidence;
using psy::C::LoopBoundPredictor;
using psy::C::LoopHandlingMode;

struct Case {
    const char* id;
    const char* init;
    const char* cond;
    const char* update;
    int cap;
    int expected;
    LoopHandlingMode mode;
};

int main() {
    const std::vector<Case> cases = {
        {"01_lt", "int i = 0;", "i < 4", "i = i + 1", 64, 4, LoopHandlingMode::ExactSummary},
        {"02_le", "int i = 0;", "i <= 4", "i = i + 1", 64, 5, LoopHandlingMode::ExactSummary},
        {"03_desc", "int i = 5;", "i > 0", "i = i - 1", 64, 5, LoopHandlingMode::ExactSummary},
        {"04_step2", "int i = 0;", "i < 9", "i = i + 2", 64, 5, LoopHandlingMode::ExactSummary},
        {"05_step3_le", "int i = 1;", "i <= 10", "i += 3", 64, 4, LoopHandlingMode::ExactSummary},
        {"06_assign_step", "int i = 1;", "i < 8", "i = i + 3", 64, 3, LoopHandlingMode::ExactSummary},
        {"07_prefix", "int i = 0;", "i < 5", "++i", 64, 5, LoopHandlingMode::ExactSummary},
        {"08_reversed", "int i = 0;", "5 > i", "i = i + 1", 64, 5, LoopHandlingMode::ExactSummary},
        {"09_reversed_desc", "int i = 5;", "0 < i", "i = i - 1", 64, 5, LoopHandlingMode::ExactSummary},
        {"10_zero_trip", "int i = 4;", "i < 2", "i = i + 1", 64, 0, LoopHandlingMode::ExactSummary},
        {"11_negative", "int i = -3;", "i < 3", "i = i + 1", 64, 6, LoopHandlingMode::ExactSummary},
        {"12_clamped", "int i = 0;", "i < 100", "i = i + 1", 4, 4, LoopHandlingMode::ConservativeUnroll},
        {"13_variable_limit", "int i = 0;", "i < n", "i = i + 1", 64, 3, LoopHandlingMode::AdaptiveFallback},
        {"14_wrong_direction", "int i = 0;", "i < 5", "i = i - 1", 64, 3, LoopHandlingMode::AdaptiveFallback},
        {"15_zero_update", "int i = 0;", "i < 5", "i = i + 0", 64, 3, LoopHandlingMode::AdaptiveFallback},
        {"16_missing_init", ";", "i < 5", "i = i + 1", 64, 3, LoopHandlingMode::AdaptiveFallback},
        {"17_equality", "int i = 0;", "i != 5", "i = i + 1", 64, 3, LoopHandlingMode::AdaptiveFallback},
        {"18_desc_step2", "int i = 9;", "i >= 1", "i -= 2", 64, 5, LoopHandlingMode::ExactSummary},
        {"19_reversed_inclusive", "int i = 3;", "0 <= i", "i = i - 1", 64, 4, LoopHandlingMode::ExactSummary},
        {"20_fallback_cap", "int i = 0;", "i < n", "i = i + 1", 2, 2, LoopHandlingMode::AdaptiveFallback}
    };

    int failures = 0;
    std::cout << "id,iterations,mode,reason\n";
    for (const auto& tc : cases) {
        const auto got = LoopBoundPredictor::predict(
            tc.init, tc.cond, tc.update, tc.cap);
        std::cout << tc.id << "," << got.iterations << ","
                  << static_cast<int>(got.mode) << "," << got.reason << "\n";
        if (got.iterations != tc.expected || got.mode != tc.mode) {
            std::cerr << "FAIL " << tc.id << ": expected " << tc.expected
                      << "/" << static_cast<int>(tc.mode) << ", got "
                      << got.iterations << "/" << static_cast<int>(got.mode)
                      << "\n";
            ++failures;
        }
    }
    if (cases.size() != 20) {
        std::cerr << "FAIL: regression suite must contain exactly 20 cases\n";
        ++failures;
    }
    return failures == 0 ? 0 : 1;
}
