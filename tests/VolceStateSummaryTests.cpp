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

    // Eliminating a derived SSA chain must preserve the projected input
    // models, including a later assertion that reads the exit state.
    const std::string chainSmt =
        "(declare-const x (_ BitVec 32))\n"
        "(declare-const |i@0#ssa0| (_ BitVec 32))\n"
        "(declare-const |i@0#ssa1| (_ BitVec 32))\n"
        "(declare-const |i@0#ssa2| (_ BitVec 32))\n"
        "(assert (= |i@0#ssa0| (_ bv0 32)))\n"
        "(assert (= |i@0#ssa1| (bvadd |i@0#ssa0| (_ bv1 32))))\n"
        "(assert (= |i@0#ssa2| (bvadd |i@0#ssa1| (_ bv1 32))))\n"
        "(assert (= x |i@0#ssa2|))\n";
    const volce::AffineStateSummary chainSummary{"i", 0, 1, 2, 2};
    const auto optimized = volce::countModelsFromSmt2WithSummaries(
        chainSmt, {chainSummary}, {}, volce::Range{-8, 8});
    const auto reference = volce::countModelsFromSmt2WithSummaries(
        chainSmt, {chainSummary}, {}, volce::Range{-8, 8}, false, {}, false);
    const bool eliminationOk = optimized && reference &&
        optimized->count == 1 && reference->count == 1 &&
        optimized->projection_terms == reference->projection_terms &&
        optimized->counting_assertions < reference->counting_assertions &&
        optimized->applied_state_summaries.size() == 1;
    std::cout << "ssa-definition-elimination: "
              << (eliminationOk ? "PASS" : "FAIL") << '\n';
    failures += !eliminationOk;

    const std::string memorySmt =
        "(declare-const x (_ BitVec 32))\n"
        "(declare-const mem (Array (_ BitVec 32) (_ BitVec 32)))\n"
        "(assert (= x x))\n"
        "(assert (= (select mem x) (select mem x)))\n";
    const auto memoryResult = volce::countModelsFromSmt2(
        memorySmt, {}, volce::Range{-1, 1}, true);
    const bool memoryOk = memoryResult && memoryResult->count == 9 &&
        memoryResult->bounded_vars.size() == 1 &&
        memoryResult->bounded_memory_terms.size() == 1;
    std::cout << "array-memory-projection: "
              << (memoryOk ? "PASS" : "FAIL") << '\n';
    failures += !memoryOk;

    const std::string canonicalSmt =
        "(declare-const p (_ BitVec 32))\n"
        "(declare-const %a (Array (_ BitVec 32) (_ BitVec 32)))\n"
        "(assert (= p (_ bv0 32)))\n";
    const std::vector<volce::MemoryRegionProjection> regions{
        {"p", 2, true}};
    const auto canonicalResult = volce::countModelsFromSmt2(
        canonicalSmt, {}, volce::Range{-1, 1}, true, regions);
    const bool canonicalOk = canonicalResult &&
        canonicalResult->count == 9 &&
        canonicalResult->bounded_memory_terms.size() == 2;
    std::cout << "canonical-memory-region: "
              << (canonicalOk ? "PASS" : "FAIL") << '\n';
    failures += !canonicalOk;
    return failures == 0 ? 0 : 1;
}
