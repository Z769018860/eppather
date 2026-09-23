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
    // Six bounded memory cells have 3^6 valuations. The array equality
    // correlates the first pair, leaving exactly 3^5 projected models.
    const std::string manyCellsSmt =
        "(declare-const %a (Array (_ BitVec 32) (_ BitVec 32)))\n"
        "(assert (= (select %a (_ bv0 32)) (select %a (_ bv1 32))))\n";
    const auto manyCells = volce::countModelsFromSmt2(
        manyCellsSmt, {}, volce::Range{-1, 1}, true,
        {{"region", 6, true}});
    const bool boundedEnumerationOk = manyCells &&
        manyCells->count == 243 &&
        manyCells->bounded_memory_terms.size() == 6 &&
        manyCells->factored_projection_components == 5;
    std::cout << "bounded-memory-enumeration: "
              << (boundedEnumerationOk ? "PASS" : "FAIL") << '\n';
    failures += !boundedEnumerationOk;

    // Two symbolic source regions are not independent unless the formula
    // proves their bases cannot alias. p==q is feasible here, so the exact
    // count must preserve the shared-cell case and factorization must be
    // rejected. 3 equal-base pairs contribute 3 values each; six distinct-
    // base pairs contribute 3^2 values each: 3*3 + 6*9 = 63.
    const std::string aliasingSmt =
        "(declare-const p (_ BitVec 32))\n"
        "(declare-const q (_ BitVec 32))\n"
        "(declare-const %a (Array (_ BitVec 32) (_ BitVec 32)))\n";
    const auto aliasing = volce::countModelsFromSmt2(
        aliasingSmt, {}, volce::Range{-1, 1}, true,
        {{"p", 1, true}, {"q", 1, true}});
    const bool aliasingOk = aliasing &&
        aliasing->count == 63 &&
        aliasing->factored_projection_components == 0;
    std::cout << "projection-factorization-alias-guard: "
              << (aliasingOk ? "PASS" : "FAIL") << '\n';
    failures += !aliasingOk;

    // Once bases are fixed apart, six canonical cells are provably disjoint
    // and can be counted as independent components without changing the exact
    // finite projection count.
    const std::string disjointSmt =
        "(declare-const p (_ BitVec 32))\n"
        "(declare-const q (_ BitVec 32))\n"
        "(declare-const %a (Array (_ BitVec 32) (_ BitVec 32)))\n"
        "(assert (= p (_ bv0 32)))\n"
        "(assert (= q (_ bv4 32)))\n";
    const std::unordered_map<std::string, volce::Range> disjointRanges{
        {"p", {-8, 8}}, {"q", {-8, 8}}, {"%memory", {-1, 1}}};
    const auto disjoint = volce::countModelsFromSmt2(
        disjointSmt, disjointRanges, std::nullopt, true,
        {{"p", 3, true}, {"q", 3, true}});
    const bool disjointOk = disjoint &&
        disjoint->count == 729 &&
        disjoint->bounded_memory_terms.size() == 6 &&
        disjoint->factored_projection_components >= 6;
    std::cout << "projection-factorization-disjoint-regions: "
              << (disjointOk ? "PASS" : "FAIL") << '\n';
    failures += !disjointOk;
    return failures == 0 ? 0 : 1;
}
