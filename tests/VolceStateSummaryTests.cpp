#include "volce/volce_api.h"

#include <iostream>
#include <optional>
#include <string>
#include <vector>

namespace {

bool check(const char* name,
           const std::string& smt,
           const volce::AffineStateSummary& summary,
           std::size_t applied,
           std::size_t ground,
           std::size_t rejected) {
    const auto result = volce::countModelsFromSmt2WithSummaries(
        smt, {summary}, {}, volce::Range{-8, 8});
    const bool ok = result &&
        result->applied_state_summaries.size() == applied &&
        result->validated_ground_state_summaries.size() == ground &&
        result->rejected_state_summaries.size() == rejected;
    std::cout << name << ": " << (ok ? "PASS" : "FAIL") << '\n';
    return ok;
}

}  // namespace

int main() {
    const volce::AffineStateSummary valid{"i", 0, 1, 4, 4};
    const volce::AffineStateSummary invalid{"i", 0, 1, 4, 5};
    int failures = 0;
    failures += !check(
        "ssa-bound",
        "(declare-const i (_ BitVec 32))\n(assert (= i (_ bv4 32)))\n",
        valid, 1, 0, 0);
    failures += !check("constant-folded", "(assert true)\n", valid, 0, 1, 0);
    failures += !check("invalid-closed-form", "(assert true)\n", invalid, 0, 0, 1);
    return failures == 0 ? 0 : 1;
}
