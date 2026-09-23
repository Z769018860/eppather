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
    bool apply_entailed_summaries = true);

std::optional<CountResult> countModelsFromSmt2File(
    const std::string& smt2_path,
    const std::unordered_map<std::string, Range>& ranges,
    const std::optional<Range>& default_range = std::nullopt,
    bool include_memory_terms = false);

}  // namespace volce
