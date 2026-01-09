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

struct CountResult {
    std::uint64_t count;
    std::vector<std::string> bounded_vars;
};

std::optional<CountResult> countModelsFromSmt2(
    const std::string& smt2,
    const std::unordered_map<std::string, Range>& ranges,
    const std::optional<Range>& default_range = std::nullopt);

std::optional<CountResult> countModelsFromSmt2File(
    const std::string& smt2_path,
    const std::unordered_map<std::string, Range>& ranges,
    const std::optional<Range>& default_range = std::nullopt);

}  // namespace volce
