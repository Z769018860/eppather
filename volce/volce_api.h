#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

namespace volce {

struct Range {
    std::int64_t lower;
    std::int64_t upper;
};

struct AffineStateSummary {
    std::string variable;
    std::int64_t initial_value;
    std::int64_t step;
    std::int64_t iterations;
    std::int64_t final_value;
};

struct AffineRelationSummary {
    std::string variable;
    // exit = scale * entry + offset
    std::int64_t scale{1};
    std::int64_t offset{0};
};

struct CoupledAffineRelationSummary {
    // Row/column order for matrix. Each row proves:
    // variables[row]_exit = sum_j matrix[row,j] *
    //                       variables[j]_entry + offset[row].
    std::vector<std::string> variables;
    std::vector<std::int64_t> matrix;
    std::vector<std::int64_t> offset;
};

struct CoupledAffineValidationResult {
    std::vector<std::string> applied;
    std::vector<std::string> rejected;
    std::size_t required_rows{0};
    std::size_t applied_rows{0};
    bool all_rows_entailed{false};
};

struct CoupledAffineOverflowValidationResult {
    std::vector<std::string> certified;
    std::vector<std::string> rejected;
    std::size_t required_rows{0};
    std::size_t certified_rows{0};
    bool all_rows_safe{false};
};

struct MemoryCellAffineRelationSummary {
    std::string source_name;
    std::int64_t cell_index{0};
    // final_cell = scale * loop_entry_cell + offset
    std::int64_t scale{1};
    std::int64_t offset{0};
    // Exact fixed local-array extent supplied by Eppather.
    std::size_t region_cells{0};
};

struct MemoryRelationValidationResult {
    std::vector<std::string> applied;
    std::vector<std::string> rejected;
    // Frame validation proves every declared region cell not written by the
    // summary is unchanged from %a#ssa_loop_entry to %a#ssa_final.
    std::vector<std::string> frame_applied;
    std::vector<std::string> frame_rejected;
};

struct MemoryRegionProjection {
    std::string source_name;
    std::size_t cells;
    bool variable_length{false};
};

struct CountResult {
    std::uint64_t count;
    std::vector<std::string> bounded_vars;
    // Finite projections of array-backed memory reads that occur in the path
    // formula. Without these terms, pointer/array contents are existentially
    // ignored and path probabilities are computed over scalar variables only.
    std::vector<std::string> bounded_memory_terms;
    std::vector<std::string> applied_state_summaries;
    // The affine identity is valid, but the source variable was constant-folded
    // out of the SMT formula.  These summaries document the transition; they do
    // not constrain the model space and must not be reported as "applied".
    std::vector<std::string> validated_ground_state_summaries;
    std::vector<std::string> rejected_state_summaries;
    std::vector<std::string> applied_affine_relation_summaries;
    std::vector<std::string> rejected_affine_relation_summaries;
    // Profiling fields separate formula/projection size from the two expensive
    // phases. They are observational and do not change counting semantics.
    std::size_t formula_assertions{0};
    std::size_t smt_declarations{0};
    std::size_t projection_terms{0};
    std::size_t counting_assertions{0};
    // Number of independent projected components actually counted separately.
    // Zero means factorization was not used for this formula.
    std::size_t factored_projection_components{0};
    std::uint64_t solver_warmup_microseconds{0};
    std::uint64_t summary_check_microseconds{0};
    std::uint64_t model_count_microseconds{0};
};

std::optional<CountResult> countModelsFromSmt2(
    const std::string& smt2,
    const std::unordered_map<std::string, Range>& ranges,
    const std::optional<Range>& default_range = std::nullopt,
    bool include_memory_terms = false,
    const std::vector<MemoryRegionProjection>& memory_regions = {});

std::optional<CountResult> countModelsFromSmt2WithSummaries(
    const std::string& smt2,
    const std::vector<AffineStateSummary>& summaries,
    const std::unordered_map<std::string, Range>& ranges,
    const std::optional<Range>& default_range = std::nullopt,
    bool include_memory_terms = false,
    const std::vector<MemoryRegionProjection>& memory_regions = {},
    bool apply_entailed_summaries = true,
    const std::vector<AffineRelationSummary>& affine_relations = {});


std::optional<CoupledAffineValidationResult>
validateCoupledAffineRelationsFromSmt2(
    const std::string& smt2,
    const std::vector<CoupledAffineRelationSummary>& summaries);


std::optional<CoupledAffineOverflowValidationResult>
validateCoupledAffineOverflowFromSmt2(
    const std::string& smt2,
    const std::vector<CoupledAffineRelationSummary>& summaries,
    const Range& input_range);

std::optional<MemoryRelationValidationResult>
validateMemoryCellRelationsFromSmt2(
    const std::string& smt2,
    const std::vector<MemoryCellAffineRelationSummary>& summaries);

std::optional<CountResult> countModelsFromSmt2File(
    const std::string& smt2_path,
    const std::unordered_map<std::string, Range>& ranges,
    const std::optional<Range>& default_range = std::nullopt,
    bool include_memory_terms = false);

}  // namespace volce
