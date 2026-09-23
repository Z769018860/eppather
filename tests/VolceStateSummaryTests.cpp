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

    // LoopSCC periodic relations are accepted only when the complete SMT
    // path formula entails the relation between the materialized entry state
    // (#ssa0, created by local initialization) and the latest SSA state.
    // Two sign flips x' = -x - 1 compose to the identity.
    const std::string affineRelationSmt =
        "(declare-const |state@0#ssa0| (_ BitVec 32))\n"
        "(declare-const |state@0#ssa1| (_ BitVec 32))\n"
        "(declare-const |state@0#ssa2| (_ BitVec 32))\n"
        "(assert (= |state@0#ssa1| "
        "(bvsub (bvneg |state@0#ssa0|) (_ bv1 32))))\n"
        "(assert (= |state@0#ssa2| "
        "(bvsub (bvneg |state@0#ssa1|) (_ bv1 32))))\n";
    const auto affineAccepted = volce::countModelsFromSmt2WithSummaries(
        affineRelationSmt, {}, {}, volce::Range{-8, 8}, false, {}, true,
        {{"state", 1, 0}});
    const auto affineRejected = volce::countModelsFromSmt2WithSummaries(
        affineRelationSmt, {}, {}, volce::Range{-8, 8}, false, {}, true,
        {{"state", 1, 1}});
    const bool affineRelationOk = affineAccepted && affineRejected &&
        affineAccepted->count == affineRejected->count &&
        affineAccepted->applied_affine_relation_summaries.size() == 1 &&
        affineAccepted->rejected_affine_relation_summaries.empty() &&
        affineRejected->applied_affine_relation_summaries.empty() &&
        affineRejected->rejected_affine_relation_summaries.size() == 1;
    std::cout << "loopscc-affine-relation-entailment: "
              << (affineRelationOk ? "PASS" : "FAIL") << '\n';
    failures += !affineRelationOk;

    const std::string negativeScaleSmt =
        "(declare-const |flip@0#ssa0| (_ BitVec 32))\n"
        "(declare-const |flip@0#ssa1| (_ BitVec 32))\n"
        "(assert (= |flip@0#ssa1| "
        "(bvsub (bvneg |flip@0#ssa0|) (_ bv1 32))))\n";
    const auto negativeScale = volce::countModelsFromSmt2WithSummaries(
        negativeScaleSmt, {}, {}, volce::Range{-8, 8}, false, {}, true,
        {{"flip", -1, -1}});
    const bool negativeScaleOk = negativeScale &&
        negativeScale->applied_affine_relation_summaries.size() == 1 &&
        negativeScale->rejected_affine_relation_summaries.empty();
    std::cout << "loopscc-negative-scale-relation: "
              << (negativeScaleOk ? "PASS" : "FAIL") << '\n';
    failures += !negativeScaleOk;

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
              << (boundedEnumerationOk ? "PASS" : "FAIL")
              << " count=" << (manyCells ? std::to_string(manyCells->count) : "N/A")
              << " memory_terms=" << (manyCells ? std::to_string(manyCells->bounded_memory_terms.size()) : "N/A")
              << " components=" << (manyCells ? std::to_string(manyCells->factored_projection_components) : "N/A")
              << '\n';
    failures += !boundedEnumerationOk;

    // Two symbolic source regions are not independent unless the formula
    // proves their bases cannot alias. With three cells per region and bases
    // in {-1,0,1}, every relative offset 0, +/-1, +/-2 is feasible. The exact
    // projected count is 3*3^3 + 4*3^4 + 2*3^5 = 891, and the factorization
    // guard must keep the mutually aliasing base/cell terms in one component.
    const std::string aliasingSmt =
        "(declare-const p (_ BitVec 32))\n"
        "(declare-const q (_ BitVec 32))\n"
        "(declare-const %a (Array (_ BitVec 32) (_ BitVec 32)))\n";
    const auto aliasing = volce::countModelsFromSmt2(
        aliasingSmt, {}, volce::Range{-1, 1}, true,
        {{"p", 3, true}, {"q", 3, true}});
    const bool aliasingOk = aliasing &&
        aliasing->count == 891 &&
        aliasing->bounded_memory_terms.size() == 6 &&
        aliasing->factored_projection_components == 0;
    std::cout << "projection-factorization-alias-guard: "
              << (aliasingOk ? "PASS" : "FAIL")
              << " count=" << (aliasing ? std::to_string(aliasing->count) : "N/A")
              << " memory_terms=" << (aliasing ? std::to_string(aliasing->bounded_memory_terms.size()) : "N/A")
              << " components=" << (aliasing ? std::to_string(aliasing->factored_projection_components) : "N/A")
              << '\n';
    failures += !aliasingOk;

    // Six cells in one canonical region have distinct constant addresses.
    // With no cross-cell constraint, exact factorization should expose all six
    // independent projected dimensions and preserve 3^6 models.
    const std::string disjointSmt =
        "(declare-const %a (Array (_ BitVec 32) (_ BitVec 32)))\n"
        "(assert (= (select %a (_ bv0 32)) (select %a (_ bv0 32))))\n";
    const auto disjoint = volce::countModelsFromSmt2(
        disjointSmt, {}, volce::Range{-1, 1}, true,
        {{"region", 6, true}});
    const bool disjointOk = disjoint &&
        disjoint->count == 729 &&
        disjoint->bounded_memory_terms.size() == 6 &&
        disjoint->factored_projection_components == 6;
    std::cout << "projection-factorization-disjoint-regions: "
              << (disjointOk ? "PASS" : "FAIL")
              << " count=" << (disjoint ? std::to_string(disjoint->count) : "N/A")
              << " memory_terms=" << (disjoint ? std::to_string(disjoint->bounded_memory_terms.size()) : "N/A")
              << " components=" << (disjoint ? std::to_string(disjoint->factored_projection_components) : "N/A")
              << '\n';
    failures += !disjointOk;

    // Multiple canonical regions that have no surviving source base symbol are
    // already represented by non-overlapping fallback address ranges in the
    // existing memory-projection abstraction. Factorization may exploit that
    // canonical representation, but it must not change its exact count.
    const std::string canonicalMultiSmt =
        "(declare-const %a (Array (_ BitVec 32) (_ BitVec 32)))\n";
    const auto canonicalMulti = volce::countModelsFromSmt2(
        canonicalMultiSmt, {}, volce::Range{-1, 1}, true,
        {{"left", 3, true}, {"right", 3, true}});
    const bool canonicalMultiOk = canonicalMulti &&
        canonicalMulti->count == 729 &&
        canonicalMulti->bounded_memory_terms.size() == 6 &&
        canonicalMulti->factored_projection_components == 6;
    std::cout << "projection-factorization-canonical-multi-region: "
              << (canonicalMultiOk ? "PASS" : "FAIL")
              << " count=" << (canonicalMulti ? std::to_string(canonicalMulti->count) : "N/A")
              << " memory_terms=" << (canonicalMulti ? std::to_string(canonicalMulti->bounded_memory_terms.size()) : "N/A")
              << " components=" << (canonicalMulti ? std::to_string(canonicalMulti->factored_projection_components) : "N/A")
              << '\n';
    failures += !canonicalMultiOk;
    // A LoopSCC path relation is accepted only when the complete SMT path
    // formula entails the relation between the first and last materialized
    // SSA states. A wrong affine offset must be rejected.
    const std::string linearRelationSmt =
        "(declare-const |x@0#ssa0| (_ BitVec 32))\n"
        "(declare-const |x@0#ssa1| (_ BitVec 32))\n"
        "(declare-const |x@0#ssa2| (_ BitVec 32))\n"
        "(assert (= |x@0#ssa1| (bvadd |x@0#ssa0| (_ bv1 32))))\n"
        "(assert (= |x@0#ssa2| (bvadd |x@0#ssa1| (_ bv1 32))))\n";
    const auto linearAccepted = volce::countModelsFromSmt2WithSummaries(
        linearRelationSmt, {}, {}, volce::Range{-8, 8}, false, {}, true,
        {volce::AffineRelationSummary{"x", 1, 2}});
    const bool linearAcceptedOk = linearAccepted &&
        linearAccepted->applied_affine_relation_summaries.size() == 1 &&
        linearAccepted->rejected_affine_relation_summaries.empty();
    std::cout << "loopscc-linear-relation-entailed: "
              << (linearAcceptedOk ? "PASS" : "FAIL") << '\n';
    failures += !linearAcceptedOk;

    const auto linearRejected = volce::countModelsFromSmt2WithSummaries(
        linearRelationSmt, {}, {}, volce::Range{-8, 8}, false, {}, true,
        {volce::AffineRelationSummary{"x", 1, 3}});
    const bool linearRejectedOk = linearRejected &&
        linearRejected->applied_affine_relation_summaries.empty() &&
        linearRejected->rejected_affine_relation_summaries.size() == 1;
    std::cout << "loopscc-linear-relation-rejected: "
              << (linearRejectedOk ? "PASS" : "FAIL") << '\n';
    failures += !linearRejectedOk;

    return failures == 0 ? 0 : 1;
}
