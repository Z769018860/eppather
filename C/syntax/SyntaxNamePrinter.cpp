// Copyright (c) 2020/21/22 Leandro T. C. Melo <ltcmelo@gmail.com>

//

// Permission is hereby granted, free of charge, to any person obtaining a copy

// of this software and associated documentation files (the "Software"), to deal

// in the Software without restriction, including without limitation the rights

// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell

// copies of the Software, and to permit persons to whom the Software is

// furnished to do so, subject to the following conditions:

//

// The above copyright notice and this permission notice shall be included in

// all copies or substantial portions of the Software.

//

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR

// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,

// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE

// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER

// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,

// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN

// THE SOFTWARE.



#include "SyntaxNamePrinter.h"
#include "LoopBoundPredictor.h"



#include <algorithm>
#include <chrono>
#include <cmath>
#include <cctype>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <limits>
#include <optional>
#include <regex>
#include <stdlib.h>
#include <string>
#include <unordered_map>
#include <unordered_set>

namespace {
int exactLoopAutoliftCap(int requestedCap) {
    const char* raw = std::getenv("EPPATHER_EXACT_LOOP_AUTOLIFT_CAP");
    if (!raw || !*raw) {
        return std::max(requestedCap, 64);
    }
    char* end = nullptr;
    const long parsed = std::strtol(raw, &end, 10);
    if (end == raw || *end != '\0' || parsed <= 0) {
        return requestedCap;
    }
    return static_cast<int>(std::min<long>(
        parsed, std::numeric_limits<int>::max()));
}

int predictedLoopBound(const psy::C::CFGNode* node, int safetyCap) {
    if (!node) return 0;
    // The affine predictor currently has initializer/update metadata only for
    // for-loops. A while-loop must therefore honor the configured safety cap;
    // the old hard-coded fallback of 3 silently ignored --maxloop values > 3.
    if (!node->isFor) {
        const int requested = std::max(0, safetyCap);
        if (!node->isWhile) return requested;

        // A complete LoopSCC SPath graph can recover an exact trip count even
        // when nested branches prevented the legacy while-update metadata
        // from being classified as a simple affine loop. Enable this only with
        // the LoopSCC analysis flag until the A/B gates promote it by default.
        const char* loopSccAnalyze = std::getenv("EPPATHER_LOOP_SCC_ANALYZE");
        if (loopSccAnalyze && *loopSccAnalyze &&
            std::string(loopSccAnalyze) != "0" &&
            !node->initstmt_str.empty()) {
            static std::unordered_map<const psy::C::CFGNode*, long long>
                provedTripCounts;
            auto it = provedTripCounts.find(node);
            if (it == provedTripCounts.end()) {
                auto graph = psy::C::LoopSccAdapter::analyze(
                    const_cast<psy::C::CFGNode*>(node));
                it = provedTripCounts.emplace(
                    node, graph.provedTripCount).first;
            }
            if (it->second >= 0) {
                const long long hardBudget = std::max<long long>(
                    requested, exactLoopAutoliftCap(requested));
                const int bound = static_cast<int>(std::min<long long>(
                    it->second, hardBudget));
                const char* trace =
                    std::getenv("EPPATHER_LOOP_SCC_BOUND_TRACE");
                if (trace && *trace && std::string(trace) != "0") {
                    std::cerr << "[LOOPSCC BOUND]: cond="
                              << node->cond_str
                              << " source=spath"
                              << " requested=" << requested
                              << " proved=" << it->second
                              << " bound=" << bound
                              << std::endl;
                }
                return bound;
            }
        }

        // Without a LoopSCC proof, retain the legacy conservative budget for a
        // canonical variable-vs-integer condition. Data-dependent conditions
        // continue to honor the requested maxloop without guessing.
        static const std::regex direct(
            "\\b[A-Za-z_][A-Za-z0-9_]*\\b[[:space:]]*"
            "(?:<=|<|>=|>)[[:space:]]*(-?[0-9]+)");
        static const std::regex reversed(
            "(-?[0-9]+)[[:space:]]*(?:<=|<|>=|>)[[:space:]]*"
            "\\b[A-Za-z_][A-Za-z0-9_]*\\b");
        std::smatch match;
        long long limit = 0;
        if (std::regex_search(node->cond_str, match, direct) ||
            std::regex_search(node->cond_str, match, reversed)) {
            limit = std::strtoll(match[1].str().c_str(), nullptr, 10);
            const long long guessed = std::min<long long>(
                exactLoopAutoliftCap(requested),
                std::max<long long>(requested, 2 * std::llabs(limit) + 2));
            const char* trace =
                std::getenv("EPPATHER_LOOP_SCC_BOUND_TRACE");
            if (trace && *trace && std::string(trace) != "0") {
                std::cerr << "[LOOPSCC BOUND]: cond="
                          << node->cond_str
                          << " source=heuristic"
                          << " requested=" << requested
                          << " bound=" << guessed
                          << std::endl;
            }
            return static_cast<int>(guessed);
        }
        return requested;
    }
    // A small user-supplied maxloop used to make a provably finite loop end in
    // an infeasible synthetic exit (for example, i < 4 with --maxloop 2).
    // Lift only canonical affine loops, and only to a modest configurable hard
    // cap. Data-dependent/unsupported loops still honor maxloop exactly.
    const auto lifted = psy::C::LoopBoundPredictor::predict(
        node->initstmt_str, node->cond_str, node->expr_str,
        exactLoopAutoliftCap(std::max(0, safetyCap)));
    if (lifted.exact()) return lifted.iterations;
    return psy::C::LoopBoundPredictor::predict(
        node->initstmt_str, node->cond_str, node->expr_str,
        safetyCap).iterations;
}
}


#include "lp_lib.h"
#include "SyntaxNode.h"
#include "SyntaxUtilities.h"
#include "volce/volce_api.h"

//#include "stmt.h"

//#include "driver.h"

#include <string>


using namespace std;

using namespace psy;

using namespace C;

namespace DEBUG {
bool globalDebugEnabled = false;
}

namespace {
struct VolceResult {
    std::string output;
    std::optional<std::string> count;
    std::size_t boundedMemoryTerms{0};
    std::size_t canonicalMemoryRegions{0};
    std::vector<std::string> appliedStateSummaries;
    std::vector<std::string> validatedGroundStateSummaries;
    std::vector<std::string> rejectedStateSummaries;
    std::vector<std::string> appliedAffineRelationSummaries;
    std::vector<std::string> rejectedAffineRelationSummaries;
    std::vector<std::string> appliedCoupledAffineRows;
    std::vector<std::string> rejectedCoupledAffineRows;
    std::size_t requiredCoupledAffineRows{0};
    std::size_t appliedCoupledAffineRowsCount{0};
    bool allCoupledAffineRowsEntailed{false};
    std::vector<std::string> certifiedCoupledOverflowRows;
    std::vector<std::string> rejectedCoupledOverflowRows;
    std::size_t requiredCoupledOverflowRows{0};
    std::size_t certifiedCoupledOverflowRowsCount{0};
    bool allCoupledOverflowRowsSafe{false};
    std::vector<std::string> appliedMemoryRelationSummaries;
    std::vector<std::string> rejectedMemoryRelationSummaries;
    std::vector<std::string> appliedMemoryFrameSummaries;
    std::vector<std::string> rejectedMemoryFrameSummaries;
    std::size_t formulaAssertions{0};
    std::size_t smtDeclarations{0};
    std::size_t projectionTerms{0};
    std::size_t countingAssertions{0};
    std::size_t factoredProjectionComponents{0};
    std::uint64_t solverWarmupMicroseconds{0};
    std::uint64_t summaryCheckMicroseconds{0};
    std::uint64_t modelCountMicroseconds{0};
};

std::vector<std::string> extractDirectCalleesFromCallExprSnippet(const std::string& snippet);
std::string extractFunctionName(const std::string& signature);
std::optional<std::string> extractFunctionIdentifierFromDeclarator(const DeclaratorSyntax* declarator);
std::optional<std::string> extractCallIdentifierFromExpression(const ExpressionSyntax* expression);
std::string sanitizeFunctionTag(const std::string& rawTag);

bool shouldEmitDebugWarning() {
    return DEBUG::globalDebugEnabled;
}

std::string normalizeIdentifier(std::string ident) {
    size_t start = 0;
    while (start < ident.size() && std::isspace(static_cast<unsigned char>(ident[start]))) {
        ++start;
    }
    size_t end = ident.size();
    while (end > start && std::isspace(static_cast<unsigned char>(ident[end - 1]))) {
        --end;
    }
    return ident.substr(start, end - start);
}

std::size_t configuredVlaCellCap() {
    constexpr std::size_t kDefault = 5;
    constexpr std::size_t kHardMaximum = 64;
    const char* raw = std::getenv("EPPATHER_VLA_MAX_ELEMENTS");
    if (!raw || !*raw) return kDefault;
    char* end = nullptr;
    const unsigned long parsed = std::strtoul(raw, &end, 10);
    if (end == raw || *end != '\0' || parsed == 0) return kDefault;
    return std::min<std::size_t>(parsed, kHardMaximum);
}

std::optional<psy::C::SourceMemoryRegion> parseSourceMemoryRegion(
    const std::string& declaration) {
    std::smatch match;
    static const std::regex arrayPattern(
        "\\b([A-Za-z_][A-Za-z0-9_]*)[[:space:]]*\\["
        "[[:space:]]*([^\\]]*)[[:space:]]*\\]");
    if (std::regex_search(declaration, match, arrayPattern)) {
        const std::string extent = normalizeIdentifier(match[2].str());
        const bool fixed = !extent.empty() &&
            std::all_of(extent.begin(), extent.end(), [](unsigned char c) {
                return std::isdigit(c) != 0;
            });
        std::size_t cells = configuredVlaCellCap();
        if (fixed) {
            cells = std::min<std::size_t>(
                std::strtoul(extent.c_str(), nullptr, 10), 64);
        }
        if (cells == 0) return std::nullopt;
        return psy::C::SourceMemoryRegion{
            match[1].str(), cells, !fixed};
    }

    static const std::regex pointerPattern(
        "\\*+[[:space:]]*([A-Za-z_][A-Za-z0-9_]*)\\b");
    if (std::regex_search(declaration, match, pointerPattern)) {
        return psy::C::SourceMemoryRegion{
            match[1].str(), configuredVlaCellCap(), true};
    }
    return std::nullopt;
}

std::vector<psy::C::SourceMemoryRegion> parseSignatureMemoryRegions(
    const std::string& signature) {
    std::vector<psy::C::SourceMemoryRegion> regions;
    const size_t open = signature.find('(');
    const size_t close = signature.rfind(')');
    if (open == std::string::npos || close == std::string::npos ||
        close <= open) {
        return regions;
    }
    std::stringstream parameters(signature.substr(open + 1, close - open - 1));
    std::string parameter;
    while (std::getline(parameters, parameter, ',')) {
        if (auto region = parseSourceMemoryRegion(parameter)) {
            regions.push_back(*region);
        }
    }
    return regions;
}

std::optional<std::string> extractFunctionIdentifierFromDeclarator(const DeclaratorSyntax* declarator) {
    if (!declarator) {
        return std::nullopt;
    }
    const auto* inner = SyntaxUtilities::innermostDeclaratorOrSelf(declarator);
    if (!inner || inner->kind() != SyntaxKind::IdentifierDeclarator) {
        return std::nullopt;
    }
    auto token = inner->asIdentifierDeclarator()->identifierToken();
    if (!token.isValid()) {
        return std::nullopt;
    }
    std::string name = normalizeIdentifier(token.valueText());
    if (name.empty()) {
        return std::nullopt;
    }
    return name;
}

std::optional<std::string> extractCallIdentifierFromExpression(const ExpressionSyntax* expression) {
    if (!expression) {
        return std::nullopt;
    }
    const auto kind = expression->kind();
    if (kind == SyntaxKind::IdentifierName) {
        auto token = expression->asIdentifierName()->identifierToken();
        if (!token.isValid()) {
            return std::nullopt;
        }
        std::string name = normalizeIdentifier(token.valueText());
        if (name.empty()) {
            return std::nullopt;
        }
        return name;
    }
    if (kind == SyntaxKind::ParenthesizedExpression) {
        return extractCallIdentifierFromExpression(expression->asParenthesizedExpression()->expression());
    }
    return std::nullopt;
}

std::optional<std::uint64_t> parseVolceCount(const std::optional<VolceResult>& result) {
    if (!result || !result->count) {
        return std::nullopt;
    }
    const std::string& text = *result->count;
    if (text.empty()) {
        return std::nullopt;
    }
    std::uint64_t value = 0;
    for (char ch : text) {
        if (ch < '0' || ch > '9') {
            return std::nullopt;
        }
        const std::uint64_t digit = static_cast<std::uint64_t>(ch - '0');
        if (value > (std::numeric_limits<std::uint64_t>::max() - digit) / 10) {
            return std::nullopt;
        }
        value = value * 10 + digit;
    }
    return value;
}

std::optional<VolceResult> runVolce(
    const std::string& smt2,
    int lowerBound,
    int upperBound,
    const std::vector<psy::C::AffineLoopStateSummary>& loopSummaries = {},
    const std::vector<psy::C::SourceMemoryRegion>& sourceMemoryRegions = {},
    const std::vector<psy::C::LoopSccAffineStateSummary>& loopSccSummaries = {},
    const std::vector<psy::C::LoopSccMemoryCellStateSummary>&
        loopSccMemorySummaries = {},
    const std::vector<psy::C::LoopSccCoupledAffineStateSummary>&
        loopSccCoupledSummaries = {}) {
    if (smt2.empty()) {
        return std::nullopt;
    }

    const volce::Range range{lowerBound, upperBound};
    std::vector<volce::AffineStateSummary> summaries;
    summaries.reserve(loopSummaries.size());
    for (const auto& summary : loopSummaries) {
        summaries.push_back(volce::AffineStateSummary{
            summary.variable,
            summary.initialValue,
            summary.step,
            summary.iterations,
            summary.finalValue});
    }
    std::vector<volce::AffineRelationSummary> affineRelations;
    affineRelations.reserve(loopSccSummaries.size());
    for (const auto& summary : loopSccSummaries) {
        affineRelations.push_back(volce::AffineRelationSummary{
            summary.variable, summary.scale, summary.offset});
    }
    std::vector<volce::CoupledAffineRelationSummary> coupledRelations;
    coupledRelations.reserve(loopSccCoupledSummaries.size());
    for (const auto& summary : loopSccCoupledSummaries) {
        volce::CoupledAffineRelationSummary relation;
        relation.variables = summary.variables;
        relation.matrix.assign(
            summary.matrix.begin(), summary.matrix.end());
        relation.offset.assign(
            summary.offset.begin(), summary.offset.end());
        coupledRelations.push_back(std::move(relation));
    }
    std::vector<volce::MemoryCellAffineRelationSummary> memoryRelations;
    memoryRelations.reserve(loopSccMemorySummaries.size());
    for (const auto& summary : loopSccMemorySummaries) {
        memoryRelations.push_back(
            volce::MemoryCellAffineRelationSummary{
                summary.region,
                summary.index,
                summary.scale,
                summary.offset,
                summary.regionCells});
    }
    const char* disableSummaries =
        std::getenv("EPPATHER_DISABLE_VOLCE_LOOP_SUMMARIES");
    const bool summariesDisabled =
        disableSummaries && *disableSummaries &&
        std::string(disableSummaries) != "0";
    const char* projectMemory =
        std::getenv("EPPATHER_VOLCE_PROJECT_MEMORY");
    const bool includeMemoryTerms =
        projectMemory && *projectMemory &&
        std::string(projectMemory) != "0";
    std::vector<volce::MemoryRegionProjection> memoryRegions;
    memoryRegions.reserve(sourceMemoryRegions.size());
    for (const auto& region : sourceMemoryRegions) {
        memoryRegions.push_back(volce::MemoryRegionProjection{
            region.name, region.cells, region.variableLength});
    }
    const auto countResult = summaries.empty() && affineRelations.empty()
        ? volce::countModelsFromSmt2(
              smt2, {}, range, includeMemoryTerms, memoryRegions)
        : volce::countModelsFromSmt2WithSummaries(
              smt2, summaries, {}, range, includeMemoryTerms, memoryRegions,
              !summariesDisabled, affineRelations);
    if (!countResult) {
        return std::nullopt;
    }

    VolceResult result;
    const std::string countString = std::to_string(countResult->count);
    result.output = "the total count (LattE): " + countString;
    result.count = countString;
    result.boundedMemoryTerms = countResult->bounded_memory_terms.size();
    result.canonicalMemoryRegions = memoryRegions.size();
    result.appliedStateSummaries = countResult->applied_state_summaries;
    result.validatedGroundStateSummaries =
        countResult->validated_ground_state_summaries;
    result.rejectedStateSummaries = countResult->rejected_state_summaries;
    result.appliedAffineRelationSummaries =
        countResult->applied_affine_relation_summaries;
    result.rejectedAffineRelationSummaries =
        countResult->rejected_affine_relation_summaries;
    if (!coupledRelations.empty()) {
        if (const auto coupledValidation =
                volce::validateCoupledAffineRelationsFromSmt2(
                    smt2, coupledRelations)) {
            result.appliedCoupledAffineRows =
                coupledValidation->applied;
            result.rejectedCoupledAffineRows =
                coupledValidation->rejected;
            result.requiredCoupledAffineRows =
                coupledValidation->required_rows;
            result.appliedCoupledAffineRowsCount =
                coupledValidation->applied_rows;
            result.allCoupledAffineRowsEntailed =
                coupledValidation->all_rows_entailed;
        } else {
            result.rejectedCoupledAffineRows.push_back(
                "coupled affine relation validation unavailable");
        }
    }
    if (!coupledRelations.empty()) {
        if (const auto overflowValidation =
                volce::validateCoupledAffineOverflowFromSmt2(
                    smt2, coupledRelations, range)) {
            result.certifiedCoupledOverflowRows =
                overflowValidation->certified;
            result.rejectedCoupledOverflowRows =
                overflowValidation->rejected;
            result.requiredCoupledOverflowRows =
                overflowValidation->required_rows;
            result.certifiedCoupledOverflowRowsCount =
                overflowValidation->certified_rows;
            result.allCoupledOverflowRowsSafe =
                overflowValidation->all_rows_safe;
        } else {
            result.rejectedCoupledOverflowRows.push_back(
                "coupled affine bounded-overflow validation unavailable");
        }
    }
    if (!memoryRelations.empty()) {
        if (const auto memoryValidation =
                volce::validateMemoryCellRelationsFromSmt2(
                    smt2, memoryRelations)) {
            result.appliedMemoryRelationSummaries =
                memoryValidation->applied;
            result.rejectedMemoryRelationSummaries =
                memoryValidation->rejected;
            result.appliedMemoryFrameSummaries =
                memoryValidation->frame_applied;
            result.rejectedMemoryFrameSummaries =
                memoryValidation->frame_rejected;
        } else {
            for (const auto& relation : memoryRelations) {
                result.rejectedMemoryRelationSummaries.push_back(
                    relation.source_name + "[" +
                    std::to_string(relation.cell_index) +
                    "]: memory relation validation unavailable");
            }
        }
    }
    result.formulaAssertions = countResult->formula_assertions;
    result.smtDeclarations = countResult->smt_declarations;
    result.projectionTerms = countResult->projection_terms;
    result.countingAssertions = countResult->counting_assertions;
    result.factoredProjectionComponents =
        countResult->factored_projection_components;
    result.solverWarmupMicroseconds =
        countResult->solver_warmup_microseconds;
    result.summaryCheckMicroseconds =
        countResult->summary_check_microseconds;
    result.modelCountMicroseconds =
        countResult->model_count_microseconds;
    return result;
}

std::string sanitizeFunctionTag(const std::string& rawTag) {
    if (rawTag.empty()) {
        return "unknown";
    }

    std::string sanitized;
    sanitized.reserve(rawTag.size());
    for (char ch : rawTag) {
        if (std::isalnum(static_cast<unsigned char>(ch)) || ch == '_') {
            sanitized.push_back(ch);
        } else {
            sanitized.push_back('_');
        }
    }
    return sanitized.empty() ? "unknown" : sanitized;
}

bool shouldEmitCrashTrace() {
    const char* env = std::getenv("EPPATHER_DEBUG_CRASH_TRACE");
    return env && *env && std::string(env) != "0";
}

void emitCrashTrace(const char* stage, const std::shared_ptr<CFGNode>& node, int depth) {
    if (!shouldEmitCrashTrace()) return;
    std::cerr << "[CRASH_TRACE] stage=" << stage
              << " depth=" << depth;
    if (!node) {
        std::cerr << " node=null" << std::endl;
        return;
    }
    std::cerr << " nodeDepth=" << node->depth
              << " nodeLevel=" << node->nodeLevel
              << " kind(loop=" << node->isLoop
              << ",if=" << node->isIf
              << ",ret=" << node->isReturn
              << ",func=" << node->isFuncDef << ")"
              << " next=" << (node->getNextNode() ? "1" : "0")
              << " nextFalse=" << (node->getNextFalseNode() ? "1" : "0")
              << std::endl;
}
}  // namespace



//using namespace tool;

//using namespace epat;



namespace {



int CUR_LEVEL;



std::string formatSnippet(std::string& snippet, bool maxLimit = true) {

    std::replace_if(

        snippet.begin(), snippet.end(), [](char c) { return c == '\n' || c == '\t'; }, ' ');



    while (true) {

        auto pos = snippet.find("  ");

        if (pos == std::string::npos) break;

        snippet = snippet.replace(pos, 2, " ");

    }



    if (maxLimit) {

        static const auto MAX_LEN = 200;

        if (snippet.length() > MAX_LEN) {

            snippet = snippet.substr(0, MAX_LEN);

            snippet += "...";

        }

    }



    return snippet;

}



}  // namespace



void SyntaxNamePrinter::print(const SyntaxNode* node, Style style) { print(node, style, std::cout); }



void SyntaxNamePrinter::print(const SyntaxNode* node, Style style, std::ostream& os) {

    CUR_LEVEL = 0;



    nonterminal(node);



    auto source = node->syntaxTree()->text().rawText();



    os << std::endl;

    for (auto i = 0U; i < dump_.size(); ++i) {

        auto node = std::get<0>(dump_[i]);

        auto nodeLevel = std::get<1>(dump_[i]);



        if (style == Style::Plain) {

            os << std::string(nodeLevel * 4, ' ');

            os << to_string(node->kind()) << std::endl;

            continue;

        }



        auto levelCnt = 0;

        while (nodeLevel > levelCnt) {

            if (nodeLevel == levelCnt + 1) {

                os << '|';

                os << std::string(2, '-');

            } else {

                int nextLevelBelow;

                for (auto j = i + 1; j < dump_.size(); ++j) {

                    nextLevelBelow = std::get<1>(dump_[j]);

                    if (nextLevelBelow <= levelCnt + 1) break;

                }

                if (nextLevelBelow == levelCnt + 1)

                    os << '|';

                else

                    os << ' ';

                os << std::string(2, ' ');

            }

            ++levelCnt;

        }



        os << to_string(node->kind()) << " [" << nodeLevel << "]  ";



        if (node->kind() == TranslationUnit) {

            os << std::endl;

            continue;

        }



        os << " <";

        auto firstTk = node->firstToken();

        auto lastTk = node->lastToken();

        if (firstTk.isValid()) os << firstTk.location().lineSpan().span().start();

        os << "..";

        if (lastTk.isValid()) os << lastTk.location().lineSpan().span().end();

        os << "> ";



        if (firstTk.isValid() && lastTk.isValid()) {

            auto firstTkStart = source.c_str() + firstTk.span().start();

            auto lastTkEnd = source.c_str() + lastTk.span().end();

            std::string snippet(firstTkStart, lastTkEnd - firstTkStart);

            os << " `" << formatSnippet(snippet) << "`";

        }



        os << std::endl;

    }

}



void SyntaxNamePrinter::nonterminal(const SyntaxNode* node) {

    if (!node) return;



    dump_.push_back(std::make_tuple(node, CUR_LEVEL));



    ++CUR_LEVEL;

    visit(node);

    --CUR_LEVEL;

}



// CFGNode related

// 获取第一个括号相匹配的内容

std::string getMatchContent(std::string input) {

    int index = input.find("(");

    int count;

    count = (index == -1) ? 0 : 1;

    index++;

    while (count > 0 && index < (int)input.size()) {

        if (input[index] == '(') count += 1;

        if (input[index] == ')') count -= 1;

        index++;

    }

    if (count == 0) return input.substr(0, index);

    return "";

}



void CFGNode::setCode(std::string codeSnippet) {

    // compound -> simple

    if (isCondition) {

        cfgCode_ = getMatchContent(codeSnippet);

        if (cfgCode_.empty()) {

            std::cout << "Invalid Conditional Statement" << std::endl;

        }

    } else

        cfgCode_ = codeSnippet;

}

std::string CFGNode::getCode() {

    if (cfgCode_.empty() && kind_==SyntaxKind::UnknownSyntax)

        return "Code has not been set yet";

    else

        return cfgCode_;

}

int CFGNode::getMem(const std::string& vartemp) {
    if (setmem) return memUsage;

    EpatRunner runner(vartemp);
    std::vector<PathDecision> decisions;

    if (isFor) {
        decisions.push_back(PathDecision{this, PathDecisionKind::LoopInit});
        decisions.push_back(PathDecision{this, PathDecisionKind::TrueBranch});
        decisions.push_back(PathDecision{this, PathDecisionKind::LoopUpdate});
    } else if (isIf || isWhile) {
        decisions.push_back(PathDecision{this, PathDecisionKind::TrueBranch});
    } else if (!isFuncDef) {
        decisions.push_back(PathDecision{this, PathDecisionKind::Code});
    }

    auto eval = runner.solve(decisions);
    memUsage = eval.mem;
    setmem = true;
    return memUsage;
}



std::string CFGNode::ExpressionToString2(ExpressionSyntax* node) {

    if (!node) return "";



    // 获取语法树的原始文本

    auto sourceText = node->syntaxTree()->text().rawText();



    // 定位表达式在源代码中的位置

    auto firstTk = node->firstToken();

    auto lastTk = node->lastToken();

    

    if (!firstTk.isValid() || !lastTk.isValid()) return "";



    auto firstTkStart = firstTk.span().start();

    auto lastTkEnd = lastTk.span().end();



    // 提取表达式文本

    std::string expressionText = sourceText.substr(firstTkStart, lastTkEnd - firstTkStart);



    // 格式化表达式文本

    return formatSnippet(expressionText);

}



std::string CFGNode::StatementToString2(StatementSyntax* node) {

    if (!node) return "";



    // 获取语法树的原始文本

    auto sourceText = node->syntaxTree()->text().rawText();



    // 定位语句在源代码中的位置

    auto firstTk = node->firstToken();

    auto lastTk = node->lastToken();

    

    if (!firstTk.isValid() || !lastTk.isValid()) return "";



    auto firstTkStart = firstTk.span().start();

    auto lastTkEnd = lastTk.span().end();



    // 提取语句文本

    std::string statementText = sourceText.substr(firstTkStart, lastTkEnd - firstTkStart);



    // 格式化语句文本

    return formatSnippet(statementText);

}



std::string CFGNode::ExpressionToString(const ExpressionSyntax* node) {

    if (!node) return "";



    // 获取语法树的原始文本

    auto sourceText = node->syntaxTree()->text().rawText();



    // 定位表达式在源代码中的位置

    auto firstTk = node->firstToken();

    auto lastTk = node->lastToken();

    

    if (!firstTk.isValid() || !lastTk.isValid()) return "";



    auto firstTkStart = firstTk.span().start();

    auto lastTkEnd = lastTk.span().end();



    // 提取表达式文本

    std::string expressionText = sourceText.substr(firstTkStart, lastTkEnd - firstTkStart);



    // 格式化表达式文本

    return formatSnippet(expressionText);

}



std::string CFGNode::StatementToString(const StatementSyntax* node) {

    if (!node) return "";



    // 获取语法树的原始文本

    auto sourceText = node->syntaxTree()->text().rawText();



    // 定位语句在源代码中的位置

    auto firstTk = node->firstToken();

    auto lastTk = node->lastToken();

    

    if (!firstTk.isValid() || !lastTk.isValid()) return "";



    auto firstTkStart = firstTk.span().start();

    auto lastTkEnd = lastTk.span().end();



    // 提取语句文本

    std::string statementText = sourceText.substr(firstTkStart, lastTkEnd - firstTkStart);



    // 格式化语句文本

    return formatSnippet(statementText);

}



void CFGNode::setNextNode(std::shared_ptr<CFGNode> nextNode) { nextNode_ = nextNode; }

std::shared_ptr<CFGNode> CFGNode::getNextNode() { return nextNode_; }



void CFGNode::setNextFalseNode(std::shared_ptr<CFGNode> nextFalseNode) { nextFalseNode_ = nextFalseNode; }

std::shared_ptr<CFGNode> CFGNode::getNextFalseNode() { return nextFalseNode_; }



void CFGNode::setSyntaxNode(const SyntaxNode* syntaxNode) { syntaxNode_ = syntaxNode; }

const SyntaxNode* CFGNode::getSyntaxNode() { return syntaxNode_; }


void SyntaxNamePrinter::getCFG(const SyntaxNode* root) {
    CUR_LEVEL = 0;
    nonterminal(root);

    CFGNode cfgnode;
    auto source = root->syntaxTree()->text().rawText();

    funcDefStack_.clear();
    globalVarDefs.clear();
    VarDefStack_.clear();
    vartemp.clear();
    inputMemoryRegions_.clear();

    bool callExprFlag = false;
    int  depth_count  = 0;

    // 获取语句块第一条“可执行语句”，空块返回 nullptr
    auto firstExecutable = [](const StatementSyntax* s) -> const StatementSyntax* {
        if (!s) return nullptr;
        if (s->kind() == SyntaxKind::CompoundStatement) {
            auto comp = s->asCompoundStatement();
            auto list = comp->statements();
            return list ? list->value : nullptr;
        }
        return s;
    };

    struct IfFrame {
        std::shared_ptr<CFGNode> cond;
        const StatementSyntax*   thenFirst;
        const StatementSyntax*   elseFirst;
        std::shared_ptr<CFGNode> join;
        int                      level;
        bool                     inElse;
    };
    std::vector<IfFrame> ifStack;

    struct LoopFrame {
        std::shared_ptr<CFGNode> cond;
        std::shared_ptr<CFGNode> bodyEnd;
        std::shared_ptr<CFGNode> join;
        int                      level;
        std::vector<std::shared_ptr<CFGNode>> breaks;
        std::shared_ptr<CFGNode> lastInBody;
        bool                     isFor;
    };
    std::vector<LoopFrame> loopStack;

    struct PendingEdge { std::shared_ptr<CFGNode> from; const SyntaxNode* toSyn; bool isFalse; };
    std::unordered_map<const SyntaxNode*, std::vector<PendingEdge>> pendingEdges;

    std::unordered_map<const StatementSyntax*, std::shared_ptr<CFGNode>> forInitToCond;
    std::unordered_map<const SyntaxNode*, std::shared_ptr<CFGNode>> syn2cfg;

    edgeCoverageMatrix.clear();
    edgeCoverageMatrix.resize(dump_.size(), std::vector<bool>(dump_.size(), false));

    for (size_t i = 0; i < dump_.size(); ++i) {
        auto* syn       = std::get<0>(dump_[i]);
        auto  nodeLevel = std::get<1>(dump_[i]);

        auto firstTk = syn->firstToken();
        auto lastTk  = syn->lastToken();
        if (!firstTk.isValid() || !lastTk.isValid())
            continue;

        const auto srcSize = source.size();
        const auto firstPos = static_cast<size_t>(firstTk.span().start());
        const auto lastPos = static_cast<size_t>(lastTk.span().end());
        if (firstPos > srcSize || lastPos > srcSize || firstPos >= lastPos) {
            emitCrashTrace("getCFG.skip_invalid_span", nullptr, static_cast<int>(i));
            continue;
        }
        auto firstTkStart = source.c_str() + firstPos;
        auto lastTkEnd    = source.c_str() + lastPos;
        std::string snippet(firstTkStart, lastTkEnd - firstTkStart);

        // 全局变量（层级=1 的 VariableAndOrFunctionDeclaration）
        if (nodeLevel == 1 && syn->kind() == SyntaxKind::VariableAndOrFunctionDeclaration) {
            auto g = std::make_shared<CFGNode>();
            g->isVarDef = true;
            g->setSyntaxNode(syn);
            g->setCode(snippet);
            globalVarDefs.push_back(g);
        }

        // 函数定义
        if (syn->kind() == SyntaxKind::FunctionDefinition) {
            auto f = std::make_shared<CFGNode>();
            f->isFuncDef = true;
            f->depth = depth_count++;
            f->setSyntaxNode(syn);
            f->nodeLevel = nodeLevel;
            f->memUsage = 0;

            const DeclaratorSyntax* declarator = syn->asFunctionDefinition()->declarator();
            auto fstart = source.c_str() + firstPos;
            std::string signature;
            if (declarator) {
                auto declLast = declarator->lastToken();
                if (declLast.isValid()) {
                    const auto dendPos = static_cast<size_t>(declLast.span().end());
                    if (dendPos > firstPos && dendPos <= srcSize) {
                        auto dend = source.c_str() + dendPos;
                        signature = std::string(fstart, dend - fstart);
                    }
                }
                if (auto name = extractFunctionIdentifierFromDeclarator(declarator)) {
                    f->functionName = *name;
                }
            } else {
                signature = std::string(fstart, source.c_str() + lastPos - fstart);
            }
            if (f->functionName.empty()) {
                f->functionName = extractFunctionName(formatSnippet(signature, false));
                if (shouldEmitDebugWarning()) {
                    std::cerr << "[DEBUG][summary] fallback extractFunctionName() used for function definition signature: "
                              << formatSnippet(signature, false) << std::endl;
                }
            }
            f->setCode(formatSnippet(signature, false));
            funcDefStack_.push_back(f);
            for (const auto& region : parseSignatureMemoryRegions(signature)) {
                const bool duplicate = std::any_of(
                    inputMemoryRegions_.begin(), inputMemoryRegions_.end(),
                    [&](const SourceMemoryRegion& existing) {
                        return existing.name == region.name;
                    });
                if (!duplicate) inputMemoryRegions_.push_back(region);
            }

            // 形参收集
            FunctionParameterExtractor extractor(syn->syntaxTree());
            syn->acceptVisitor(&extractor);
            for (const auto& p : extractor.parameters) {
                auto v = std::make_shared<CFGNode>();
                v->isVarDef = true;
                v->setSyntaxNode(p);
                auto pf = p->firstToken(), pl = p->lastToken();
                auto ps = source.c_str() + pf.span().start();
                auto pe = source.c_str() + pl.span().end();
                std::string sn(ps, pe - ps);
                v->setCode(formatSnippet(sn, false));
                VarDefStack_.push_back(v);
                if (auto region = parseSourceMemoryRegion(sn)) {
                    const bool duplicate = std::any_of(
                        inputMemoryRegions_.begin(), inputMemoryRegions_.end(),
                        [&](const SourceMemoryRegion& existing) {
                            return existing.name == region->name;
                        });
                    if (!duplicate) inputMemoryRegions_.push_back(*region);
                }
            }
        }

        // 仅为“非 CompoundStatement”建 CFG 结点
        if (syn->kind() > SyntaxKind::CompoundStatement && syn->kind() < SyntaxKind::TypeName) {

            // A) 进入某 if 的 else 首句：阻断 then→else 落入，并把 then 尾接到 join
            bool enteringElse = false;
            int  enteringElseIdx = -1;
            for (int k = (int)ifStack.size() - 1; k >= 0; --k) {
                auto& fr = ifStack[k];
                if (fr.elseFirst && syn == fr.elseFirst && !fr.inElse) {
                    enteringElse    = true;
                    enteringElseIdx = k;
                    break;
                }
            }
            if (enteringElse) {
                // Finish any ifs nested in the then arm before entering the
                // outer else arm.  Leaving them on ifStack lets B1 treat their
                // join nodes as predecessors of elseFirst, which incorrectly
                // creates a then -> else fall-through edge.
                while (static_cast<int>(ifStack.size()) - 1 > enteringElseIdx) {
                    auto nested = ifStack.back();
                    if (lastNode && lastNode != nested.join) {
                        lastNode->setNextNode(nested.join);
                    }
                    lastNode = nested.join;
                    ifStack.pop_back();
                }
                auto& fr = ifStack[enteringElseIdx];
                // Loops wholly contained in the then arm must likewise finish
                // at the outer if join.  Otherwise B2 later resolves their
                // false edge to elseFirst and executes both arms.
                while (!loopStack.empty() && loopStack.back().level > fr.level) {
                    auto lf = loopStack.back();
                    if (lf.lastInBody && lf.lastInBody->nodeLevel > lf.level &&
                        lf.lastInBody != lf.bodyEnd) {
                        lf.lastInBody->setNextNode(lf.bodyEnd);
                    }
                    if (lastNode && lastNode->nodeLevel > lf.level &&
                        lastNode != lf.bodyEnd) {
                        lastNode->setNextNode(lf.bodyEnd);
                    }
                    lf.bodyEnd->setNextNode(lf.cond);
                    for (auto& br : lf.breaks) br->setNextNode(lf.join);
                    lf.join->setNextNode(fr.join);
                    loopStack.pop_back();
                    lastNode = fr.join;
                }
                if (lastNode && lastNode != fr.join) {
                    lastNode->setNextNode(fr.join);
                }
                fr.inElse = true;
            }

            // B) 创建当前结点前：收束“已结束的 if/loop”
            bool closedSomething = false;

            // 这些 join 要在“当前结点 n 创建之后”再连出去
            std::vector<std::shared_ptr<CFGNode>> pendingIfJoinsToOutside;
            std::vector<std::shared_ptr<CFGNode>> pendingLoopJoinsToOutside;

            // B1) 收束 if：遇到 nodeLevel <= if.level 表示离开该 if
            while (!ifStack.empty() && nodeLevel <= ifStack.back().level) {
                auto fr = ifStack.back();

                // 把 then/else 的尾（当前 lastNode）并到 if.join
                if (lastNode && lastNode != fr.join) {
                    lastNode->setNextNode(fr.join);
                }

                // ★ 修正点：是否把 if.join 直接接到 bodyEnd？
                // 只有当“正在离开循环体”（nodeLevel <= loop.level）时，才 join→bodyEnd；
                // 如果下一条语句与该 if 同级（nodeLevel == if.level）或仍在循环体内更深层，
                // 则应该让 join→当前即将创建的语句 n（pending 方式回填）。
                bool joinToBodyEnd = false;
                if (!loopStack.empty()) {
                    auto& L = loopStack.back();
                    // 只有 if 位于该循环内部且正在离开循环体时才回环。
                    // 外层 if 包含内层循环时，不能把 if.join 接到内层 bodyEnd，
                    // 否则 false 分支会错误地进入循环。
                    joinToBodyEnd = (fr.level > L.level && nodeLevel <= L.level);
                }

                if (joinToBodyEnd) {
                    auto& L = loopStack.back();
                    fr.join->setNextNode(L.bodyEnd);
                    // 更新路径尾为 bodyEnd，避免顺序边误连
                    lastNode = L.bodyEnd;
                } else {
                    pendingIfJoinsToOutside.push_back(fr.join);
                    lastNode = fr.join;
                }

                ifStack.pop_back();
                closedSomething = true;
            }

            // B2) 收束 loop：遇到 nodeLevel <= loop.level 表示离开该循环
            while (!loopStack.empty() && nodeLevel <= loopStack.back().level) {
                auto lf = loopStack.back();

                if (lf.lastInBody && lf.lastInBody->nodeLevel > lf.level && lf.lastInBody != lf.bodyEnd)
                    lf.lastInBody->setNextNode(lf.bodyEnd);
                if (lastNode && lastNode->nodeLevel > lf.level && lastNode != lf.bodyEnd)
                    lastNode->setNextNode(lf.bodyEnd);

                // bodyEnd → cond（统一回环）
                lf.bodyEnd->setNextNode(lf.cond);

                // break → join
                for (auto& br : lf.breaks) br->setNextNode(lf.join);

                loopStack.pop_back();
                closedSomething = true;

                // If this loop is nested in another loop that is also being
                // closed, its false/join edge finishes one outer iteration;
                // it must not jump directly to the statement outside both
                // loops (which would skip the outer update/back edge).
                if (!loopStack.empty() && nodeLevel <= loopStack.back().level) {
                    lf.join->setNextNode(loopStack.back().bodyEnd);
                    loopStack.back().lastInBody = loopStack.back().bodyEnd;
                    lastNode = loopStack.back().bodyEnd;
                } else {
                    // Outermost join is resolved once the current node exists.
                    pendingLoopJoinsToOutside.push_back(lf.join);
                    lastNode = nullptr;
                }
            }

            // C) 创建当前 CFG 结点 n
            auto n = std::make_shared<CFGNode>();
            n->setSyntaxNode(syn);
            n->nodeLevel = nodeLevel;
            n->depth = depth_count++;

            // 声明语句：保留原保护，不再“吞并下一条语句”
            if (syn->kind() == SyntaxKind::DeclarationStatement) {
                n->isVarDef = true;
                n->setCode(formatSnippet(snippet, false));
                if (n->nodeLevel == 3) VarDefStack_.push_back(n);
            } else {
                n->setCode(formatSnippet(snippet, false));
            }
            syn2cfg[syn] = n;

            // 回填 if.join / loop.join → n
            for (auto& jn : pendingIfJoinsToOutside)  jn->setNextNode(n);
            for (auto& jn : pendingLoopJoinsToOutside) jn->setNextNode(n);

            // 默认顺序边（未收束且未进入 else 首句时才连接）
            if (callExprFlag && lastNode) {
                lastNode->hasCallExpr = true;
                callExprFlag = false;
            }
            if (!funcDefStack_.empty()) {
                auto head = funcDefStack_.back();
                if (head && !head->getNextNode()) {
                    head->setNextNode(n);
                } else if (!closedSomething && !enteringElse && lastNode &&
                           lastNode->getSyntaxNode() &&
                           lastNode->getSyntaxNode()->kind() != SyntaxKind::ReturnStatement &&
                           lastNode->getSyntaxNode()->kind() != SyntaxKind::ContinueStatement) {
                    lastNode->setNextNode(n);
                }
            }

            // D) 识别 If / For / While
            if (syn->kind() == SyntaxKind::IfStatement) {
                n->isCondition = true; n->isIf = true;
                n->cond_    = syn->asIfStatement()->condition();
                n->cond_str = cfgnode.ExpressionToString(n->cond_);

                const IfStatementSyntax* ifSyn = syn->asIfStatement();
                const StatementSyntax* thenFirst = firstExecutable(ifSyn->statement());
                const StatementSyntax* elseFirst = firstExecutable(ifSyn->elseStatement());

                auto join = createEndNode();
                join->nodeLevel = nodeLevel;

                if (thenFirst) pendingEdges[thenFirst].push_back({ n, thenFirst, false });
                else           n->setNextNode(join);

                if (elseFirst) pendingEdges[elseFirst].push_back({ n, elseFirst, true });
                else           n->setNextFalseNode(join);

                ifStack.push_back(IfFrame{ n, thenFirst, elseFirst, join, nodeLevel, false });
            }
            else if (syn->kind() == SyntaxKind::ForStatement) {
                n->isCondition = true; n->isFor = true; n->isLoop = true; n->loopCount = 0;

                n->initstmt_    = syn->asForStatement()->initializer();
                n->initstmt_str = cfgnode.StatementToString(n->initstmt_);
                n->cond_        = syn->asForStatement()->condition();
                n->cond_str     = cfgnode.ExpressionToString(n->cond_);
                n->expr_        = syn->asForStatement()->expression();
                n->expr_str     = cfgnode.ExpressionToString(n->expr_);

                const StatementSyntax* initFirst = firstExecutable(n->initstmt_);
                const StatementSyntax* bodyFirst = firstExecutable(syn->asForStatement()->statement());

                auto join    = createEndNode(); join->nodeLevel    = nodeLevel;
                auto bodyEnd = createEndNode(); bodyEnd->nodeLevel = nodeLevel + 1;

                // false → join（跳出循环）
                n->setNextFalseNode(join);

                // true → body 首句；体空则 true → bodyEnd
                if (bodyFirst) pendingEdges[bodyFirst].push_back({ n, bodyFirst, false });
                else           n->setNextNode(bodyEnd);

                // 体末端统一回到 cond
                bodyEnd->setNextNode(n);

                if (initFirst) forInitToCond[initFirst] = n;

                loopStack.push_back(LoopFrame{ n, bodyEnd, join, nodeLevel, {}, nullptr, /*isFor*/true });
            }
            else if (syn->kind() == SyntaxKind::WhileStatement) {
                n->isCondition = true; n->isWhile = true; n->isLoop = true; n->loopCount = 0;

                n->cond_    = syn->asWhileStatement()->condition();
                n->cond_str = cfgnode.ExpressionToString(n->cond_);

                // Recover a conservative affine transition contract for a
                // structurally simple while-loop.  The candidate is still
                // implication-checked by VolCE before it can constrain model
                // counting.  Loops containing nested control flow keep the
                // existing bounded fallback.
                std::smatch inductionMatch;
                static const std::regex whileDirect(
                    "\\b([A-Za-z_][A-Za-z0-9_]*)\\b[[:space:]]*"
                    "(?:<=|<|>=|>)[[:space:]]*-?[0-9]+");
                static const std::regex whileReversed(
                    "-?[0-9]+[[:space:]]*(?:<=|<|>=|>)[[:space:]]*"
                    "\\b([A-Za-z_][A-Za-z0-9_]*)\\b");
                if (std::regex_search(n->cond_str, inductionMatch, whileDirect) ||
                    std::regex_search(n->cond_str, inductionMatch, whileReversed)) {
                    const std::string variable = inductionMatch[1].str();
                    const std::string prefix = source.substr(0, firstPos);
                    const std::regex initializer(
                        "(?:\\b[A-Za-z_][A-Za-z0-9_]*[[:space:]]+)*\\b" +
                        variable +
                        "\\b[[:space:]]*=[[:space:]]*(-?[0-9]+)[[:space:]]*;");
                    std::size_t initializerEnd = std::string::npos;
                    for (std::sregex_iterator it(prefix.begin(), prefix.end(), initializer),
                             end; it != end; ++it) {
                        n->initstmt_str = variable + " = " + (*it)[1].str() + ";";
                        initializerEnd = static_cast<std::size_t>(
                            it->position() + it->length());
                    }
                    if (initializerEnd != std::string::npos) {
                        const std::string between = prefix.substr(initializerEnd);
                        const std::regex laterWrite(
                            "\\b" + variable +
                            "\\b[[:space:]]*(?:=(?!=)|\\+\\+|--|\\+=|-=)");
                        if (std::regex_search(between, laterWrite) ||
                            between.find('}') != std::string::npos) {
                            n->initstmt_str.clear();
                        }
                    }

                    const std::size_t bodyStart = snippet.find('{');
                    const std::string bodySnippet = bodyStart == std::string::npos
                        ? snippet.substr(snippet.find(')') + 1)
                        : snippet.substr(bodyStart + 1);
                    const bool hasNestedControl = std::regex_search(
                        bodySnippet,
                        std::regex("\\b(if|for|while|switch|break|continue|return)\\b"));
                    const std::regex update(
                        "\\b" + variable +
                        "\\b[[:space:]]*(?:\\+\\+|--|\\+=?[[:space:]]*[0-9]+|"
                        "-=?[[:space:]]*[0-9]+|=[[:space:]]*" + variable +
                        "[[:space:]]*[+-][[:space:]]*[0-9]+)[[:space:]]*;");
                    std::vector<std::string> updates;
                    for (std::sregex_iterator it(bodySnippet.begin(), bodySnippet.end(), update),
                             end; it != end; ++it) {
                        updates.push_back(it->str());
                    }
                    if (!hasNestedControl && !n->initstmt_str.empty() &&
                        updates.size() == 1) {
                        n->expr_str = updates.front();
                    } else {
                        // Keep a proved, non-stale constant initializer even
                        // when nested control prevents the legacy single-update
                        // while summary. LoopSCC may still prove that every
                        // one-iteration SPath applies the same affine control
                        // step. Keeping only the initializer cannot make the
                        // older predictor exact because expr_str stays empty.
                        n->expr_str.clear();
                    }
                }

                const StatementSyntax* bodyFirst = firstExecutable(syn->asWhileStatement()->statement());

                auto join    = createEndNode(); join->nodeLevel    = nodeLevel;
                auto bodyEnd = createEndNode(); bodyEnd->nodeLevel = nodeLevel + 1;

                n->setNextFalseNode(join);
                if (bodyFirst) pendingEdges[bodyFirst].push_back({ n, bodyFirst, false });
                else           n->setNextNode(bodyEnd);

                bodyEnd->setNextNode(n);

                loopStack.push_back(LoopFrame{ n, bodyEnd, join, nodeLevel, {}, nullptr, /*isFor*/false });
            }

            // 回填 True/False 延迟边
            if (auto it = pendingEdges.find(syn); it != pendingEdges.end()) {
                for (const auto& pe : it->second) {
                    if (pe.isFalse) pe.from->setNextFalseNode(n);
                    else            pe.from->setNextNode(n);
                }
                pendingEdges.erase(it);
            }

            // 回填 for init → cond
            if (auto it2 = forInitToCond.find(static_cast<const StatementSyntax*>(syn)); it2 != forInitToCond.end()) {
                n->setNextNode(it2->second);
                forInitToCond.erase(it2);
            }

            // break / continue
            if (syn->kind() == SyntaxKind::BreakStatement) {
                if (!loopStack.empty()) loopStack.back().breaks.push_back(n);
            }
            if (syn->kind() == SyntaxKind::ContinueStatement) {
                if (!loopStack.empty()) {
                    auto& L = loopStack.back();
                    if (L.isFor) n->setNextNode(L.bodyEnd); // for: continue → bodyEnd（再 bodyEnd→cond）
                    else         n->setNextNode(L.cond);    // while: continue → cond
                }
            }

            // 更新“体内最后观测到的结点”（凡是比循环层级更深的都算体内）
            if (!loopStack.empty()) {
                auto& L = loopStack.back();
                if (n->nodeLevel > L.level) L.lastInBody = n;
            }

            if (syn->kind() == SyntaxKind::ReturnStatement) n->isReturn = true;

            lastNode = n;
        }

        if (syn->kind() == SyntaxKind::CallExpression) {
            callExprFlag = true;
            if (lastNode) {
                lastNode->hasCallExpr = true;
                const auto* callExpr = syn->asCallExpression();
                bool usedFallback = false;
                if (callExpr) {
                    if (auto calleeName = extractCallIdentifierFromExpression(callExpr->expression())) {
                        if (std::find(lastNode->calleeNames.begin(), lastNode->calleeNames.end(), *calleeName)
                            == lastNode->calleeNames.end()) {
                            lastNode->calleeNames.push_back(*calleeName);
                        }
                    } else {
                        usedFallback = true;
                    }
                } else {
                    usedFallback = true;
                }

                if (usedFallback) {
                    auto callCallees = extractDirectCalleesFromCallExprSnippet(snippet);
                    if (shouldEmitDebugWarning()) {
                        std::cerr << "[DEBUG][summary] fallback extractFunctionName/call-snippet used for call expression: "
                                  << formatSnippet(snippet) << std::endl;
                    }
                    for (const auto& callee : callCallees) {
                        if (std::find(lastNode->calleeNames.begin(), lastNode->calleeNames.end(), callee)
                            == lastNode->calleeNames.end()) {
                            lastNode->calleeNames.push_back(callee);
                        }
                    }
                }
            }
        }
    }

    // 文件尾兜底：收束未关闭的 if / loop
    while (!ifStack.empty()) {
        auto fr = ifStack.back();
        if (!loopStack.empty()) {
            auto& L = loopStack.back();
            if (lastNode && lastNode != L.bodyEnd) lastNode->setNextNode(L.bodyEnd);
            fr.join->setNextNode(L.bodyEnd);
            lastNode = L.bodyEnd;
        } else {
            if (lastNode && lastNode != fr.join) lastNode->setNextNode(fr.join);
            lastNode = fr.join;
        }
        ifStack.pop_back();
    }

    while (!loopStack.empty()) {
        auto lf = loopStack.back();
        if (lf.lastInBody && lf.lastInBody->nodeLevel > lf.level && lf.lastInBody != lf.bodyEnd)
            lf.lastInBody->setNextNode(lf.bodyEnd);
        if (lastNode && lastNode->nodeLevel > lf.level && lastNode != lf.bodyEnd)
            lastNode->setNextNode(lf.bodyEnd);
        lf.bodyEnd->setNextNode(lf.cond);
        for (auto& br : lf.breaks) br->setNextNode(lf.join);
        loopStack.pop_back();
        lastNode = lf.join;
    }

    // Keep exact fixed-array extents. For multiple pointer/VLA parameters,
    // share a finite unknown-memory budget to avoid exponential 3^N model
    // enumeration (two default five-cell pointers would already add 59,049
    // memory/address combinations over [-1,1]).
    const std::size_t variableRegionCount = static_cast<std::size_t>(
        std::count_if(inputMemoryRegions_.begin(), inputMemoryRegions_.end(),
            [](const SourceMemoryRegion& region) {
                return region.variableLength;
            }));
    if (variableRegionCount > 1) {
        constexpr std::size_t kSharedVariableCellBudget = 6;
        const std::size_t perRegion = std::max<std::size_t>(
            1, kSharedVariableCellBudget / variableRegionCount);
        for (auto& region : inputMemoryRegions_) {
            if (region.variableLength) {
                region.cells = std::min(region.cells, perRegion);
            }
        }
    }

    maxdepth = depth_count;
    temp_loopCount.assign(static_cast<size_t>(std::max(1, maxdepth + 2)), {});

    // 变量文本输出
    for (auto& n : globalVarDefs) {
        std::string code = n->getCode();
        if (!code.empty() && code.back() != ';') code += ";";
        vartemp += code + "\n";
    }
    for (auto& n : VarDefStack_) {
        std::string code = n->getCode();
        if (!code.empty() && code.back() != ';') code += ";";
        vartemp += code + "\n";
    }
}


void SyntaxNamePrinter::printCFG() {
    using std::cout;
    using std::endl;

    auto getKindName = [&](const std::shared_ptr<CFGNode>& n) -> std::string {
        if (!n) return "null";
        if (n->getKind() != SyntaxKind::UnknownSyntax) return to_string(n->getKind());
        if (n->getSyntaxNode()) return to_string(n->getSyntaxNode()->kind());
        return "UnknownSyntax";
    };

    auto sanitize = [&](std::string s, size_t maxlen = 80) -> std::string {
        for (char& c : s) {
            if (c == '\n' || c == '\r' || c == '\t') c = ' ';
        }
        while (!s.empty() && (s.back() == ' ')) s.pop_back();
        if (s.size() > maxlen) s = s.substr(0, maxlen - 3) + "...";
        return s;
    };

    auto nodeLabel = [&](const std::shared_ptr<CFGNode>& n) -> std::string {
        if (!n) return "";
        std::string base = sanitize(n->getCode());
        if (n->isIf)    base = "if(" + sanitize(n->cond_str, 40) + ")";
        if (n->isWhile) base = "while(" + sanitize(n->cond_str, 40) + ")";
        if (n->isFor)   base = "for(" + sanitize(n->initstmt_str, 20) + "; " + sanitize(n->cond_str, 20) + "; " + sanitize(n->expr_str, 20) + ")";
        if (base.empty()) base = getKindName(n);
        return base;
    };

    auto shapeOf = [&](const std::shared_ptr<CFGNode>& n) -> const char* {
        if (!n) return "box";
        if (n->isIf || n->isWhile || n->isFor) return "diamond";
        if (n->getKind() == SyntaxKind::UnknownSyntax && !n->getSyntaxNode()) return "circle"; // end/empty node
        return "box";
    };

    for (size_t fi = 0; fi < funcDefStack_.size(); ++fi) {
        std::shared_ptr<CFGNode> entry = funcDefStack_[fi];
        if (!entry) continue;

        // 1) Collect reachable nodes (true/next and false edges), assign stable ids
        std::unordered_map<CFGNode*, int> id;
        std::vector<std::shared_ptr<CFGNode>> ordered;
        std::deque<std::shared_ptr<CFGNode>> q;

        auto enqueue = [&](const std::shared_ptr<CFGNode>& n) {
            if (!n) return;
            CFGNode* key = n.get();
            if (id.find(key) == id.end()) {
                int nid = static_cast<int>(ordered.size());
                id[key] = nid;
                ordered.push_back(n);
                q.push_back(n);
            }
        };

        enqueue(entry);
        while (!q.empty()) {
            auto cur = q.front(); q.pop_front();
            auto t = cur->getNextNode();
            auto f = cur->getNextFalseNode();
            if (t) enqueue(t);
            if (f) enqueue(f);
        }

        // 2) Print human-readable table (adjacency with labels)
        cout << "======== CFG TABLE: FunctionDefinition #" << fi << " ========" << endl;
        cout << "Total nodes: " << ordered.size() << endl;
        cout << "Idx | Level | Kind                | Flags        | Next  | False | Code/Label" << endl;
        cout << "----+-------+---------------------+--------------+-------+-------+----------------------------------------" << endl;

        for (size_t idx = 0; idx < ordered.size(); ++idx) {
            auto n = ordered[idx];
            auto t = n->getNextNode();
            auto f = n->getNextFalseNode();
            int tid = (t ? id[t.get()] : -1);
            int fid = (f ? id[f.get()] : -1);

            std::string flags;
            if (n->isFuncDef) flags += "F";
            if (n->isVarDef)  { if (!flags.empty()) flags += ","; flags += "V"; }
            if (n->isIf)      { if (!flags.empty()) flags += ","; flags += "IF"; }
            if (n->isWhile)   { if (!flags.empty()) flags += ","; flags += "WH"; }
            if (n->isFor)     { if (!flags.empty()) flags += ","; flags += "FOR"; }
            if (n->isLoop)    { if (!flags.empty()) flags += ","; flags += "LOOP"; }
            if (n->hasCallExpr){ if (!flags.empty()) flags += ","; flags += "CALL"; }
            if (flags.empty()) flags = "-";

            std::string kind = getKindName(n);
            if (kind.size() > 21) kind = kind.substr(0, 21) + "...";

            cout << std::setw(3) << idx << " | "
                 << std::setw(5) << n->nodeLevel << " | "
                 << std::setw(21) << kind << " | "
                 << std::setw(12) << flags << " | "
                 << std::setw(5) << tid << " | "
                 << std::setw(5) << fid << " | "
                 << sanitize(nodeLabel(n), 60)
                 << endl;
        }
        cout << endl;

        // 3) Also emit Graphviz DOT so you can render a real graph
        std::ostringstream dot;
        dot << "digraph CFG_" << fi << " {\n";
        dot << "  rankdir=LR;\n";
        dot << "  node [fontname=\"Helvetica\"];\n";

        for (size_t idx = 0; idx < ordered.size(); ++idx) {
            auto n = ordered[idx];
            std::string label = std::to_string(idx) + ": " + nodeLabel(n);
            // escape quotes
            for (char& c : label) if (c == '\"') c = '\'';
            dot << "  " << idx << " [shape=" << shapeOf(n) << ", label=\"" << label << "\"];\n";
        }
        for (size_t idx = 0; idx < ordered.size(); ++idx) {
            auto n = ordered[idx];
            auto t = n->getNextNode();
            auto f = n->getNextFalseNode();
            if (t) {
                int tid = id[t.get()];
                dot << "  " << idx << " -> " << tid << " [label=\"next\"];\n";
            }
            if (f) {
                int fid = id[f.get()];
                dot << "  " << idx << " -> " << fid << " [style=dashed, label=\"false\"];\n";
            }
        }
        dot << "}\n";

        // 4) Print DOT to stdout and also save to file
        cout << "======== CFG DOT (Function #" << fi << ") ========" << endl;
        cout << dot.str() << endl;

        char filename[256];
        std::snprintf(filename, sizeof(filename), "cfg_func_%zu.dot", fi);
        std::ofstream ofs(filename, std::ios::out | std::ios::trunc);
        if (ofs.is_open()) {
            ofs << dot.str();
            ofs.close();
            cout << "[INFO] DOT written to: " << filename << endl;
            cout << "       Render with: dot -Tpng " << filename << " -o cfg_func_" << fi << ".png" << endl;
        } else {
            cout << "[WARN] Unable to open file for DOT output: " << filename << endl;
        }

        cout << endl;
    }
}

void printMatrixFileContent(const std::string& filename) {

    std::ifstream file(filename);

    if (file.is_open()) {

        std::string line;

        while (std::getline(file, line)) {

            std::cout << line << std::endl;

        }

        file.close();

    } else {

        std::cerr << "无法打开文件：" << filename << std::endl;

    }

}



void SyntaxNamePrinter::printCFG_DFS(int maxloop, int maxpaths) {
    int pathCount = 0;
    std::string matrixFileName = "matrix.txt";   

    loopCount.clear();
    loopCount.resize(maxdepth, 0);

    for (auto& funcNode : funcDefStack_) {
        std::vector<bool> pathCoverage(maxdepth, false);
        std::vector<PathDecision> decisions;

        std::ofstream ofs(matrixFileName, std::ios::out | std::ios::trunc);
        ofs.close();

        int maxMems = -1;
        int minMems = std::numeric_limits<int>::max();

        auto start = std::chrono::high_resolution_clock::now();

        DFS(funcNode, pathCoverage, decisions, 0, pathCount, maxloop, maxpaths, maxMems, minMems);

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - start;
        std::cout << "[DFS TIME COST]: " << diff.count() << " seconds" << std::endl;

        std::cout << "[MATRIX]:" << std::endl;
        printMatrixFileContent(matrixFileName);

        std::cout << "[DFS MAX MEMS]: " << maxMems << std::endl;
        std::cout << "[DFS MIN MEMS]: " << (minMems == std::numeric_limits<int>::max() ? 0 : minMems) << std::endl;

        auto coverageMatrix = ReadCoverageMatrix(matrixFileName);
        SolveLinearProgram(coverageMatrix);
    }
}
// ===== printCFG_DFS2：可按需把 pathCount 挪到函数内重置 =====
void SyntaxNamePrinter::printCFG_DFS2(int maxloop, int maxpaths, bool enableVolce, int volceLower, int volceUpper) {
    std::string matrixFileName = "matrix2.txt";

    for (size_t funcIndex = 0; funcIndex < funcDefStack_.size(); ++funcIndex) {
        auto& funcNode = funcDefStack_[funcIndex];
        const std::string functionTag = sanitizeFunctionTag(
            funcNode->functionName.empty() ? ("func_" + std::to_string(funcIndex)) : funcNode->functionName);
        int pathCount = 0; // 建议每个函数单独计数，避免跨函数累加
        loopCount.clear();
        loopCount.resize(maxdepth, 0);

        std::vector<bool> pathCoverage(maxdepth, false);
        std::vector<PathDecision> decisions;

        std::ofstream ofs(matrixFileName, std::ios::out | std::ios::trunc);
        ofs.close();

        feasiblePaths_.clear();
        totalVolceCount_ = 0;
        feasCache.clear();

        maxmem = -1;
        minmem = std::numeric_limits<int>::max();

        auto start = std::chrono::high_resolution_clock::now();
        currentPathCallees_.clear();
        DFS2(funcNode, pathCoverage, decisions, 0, pathCount, maxloop, maxpaths, enableVolce, volceLower, volceUpper, functionTag);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - start;

        std::cout << "[DFS TIME COST]: " << diff.count() << " seconds" << std::endl;
        printFeasiblePathSummary(enableVolce, volceLower, volceUpper);
        std::cout << "[MATRIX]:" << std::endl;
        printMatrixFileContent(matrixFileName);
        std::cout << "[DFS MAX MEMS]: " << maxmem << std::endl;
        std::cout << "[DFS MIN MEMS]: "
                  << (minmem == std::numeric_limits<int>::max() ? 0 : minmem) << std::endl;

        auto coverageMatrix = ReadCoverageMatrix(matrixFileName);
        SolveLinearProgram(coverageMatrix);
    }
}

void SyntaxNamePrinter::recordFeasiblePath(int pathIndex,
                                           int mem,
                                           const std::string& path,
                                           const std::vector<std::string>& callees,
                                           const std::optional<std::uint64_t>& volceCount,
                                           const std::optional<std::size_t>& volceMemoryTerms) {
    feasiblePaths_.push_back(FeasiblePathSummary{
        pathIndex, mem, path, callees, volceCount, volceMemoryTerms});
    if (volceCount) {
        totalVolceCount_ += *volceCount;
    }
}

void SyntaxNamePrinter::printFeasiblePathSummary(bool enableVolce, int volceLower, int volceUpper) const {
    std::cout << "[FEASIBLE PATHS]:" << std::endl;
    if (enableVolce) {
        std::cout << "[VOLCE RANGE]: [" << volceLower << ", " << volceUpper << "]" << std::endl;
    }
    std::ofstream csvFile;
    if (enableVolce) {
        csvFile.open("volce_paths.csv", std::ios::out | std::ios::trunc);
        if (csvFile.is_open()) {
            csvFile << "path_index,path,mems,volce,probability,range\n";
        }
    }

    if (feasiblePaths_.empty()) {
        std::cout << "  (none)" << std::endl;
    }

    // Model counts are the weights.  Accumulate the numerator directly instead
    // of converting every count to double probability and normalizing again.
    std::uint64_t countedSolutionSpace = 0;
    long double weightedMemsSum = 0.0L;
    bool countOverflow = false;
    std::optional<std::size_t> memoryProjectionArity;
    bool inconsistentMemoryProjection = false;

    for (const auto& info : feasiblePaths_) {
        if (!info.volceCount) {
            continue;
        }
        if (info.volceMemoryTerms) {
            if (!memoryProjectionArity) {
                memoryProjectionArity = info.volceMemoryTerms;
            } else if (*memoryProjectionArity != *info.volceMemoryTerms) {
                inconsistentMemoryProjection = true;
            }
        }
        if (countedSolutionSpace >
            std::numeric_limits<std::uint64_t>::max() - *info.volceCount) {
            countOverflow = true;
            break;
        }
        countedSolutionSpace += *info.volceCount;
        weightedMemsSum += static_cast<long double>(info.mem)
                           * static_cast<long double>(*info.volceCount);
    }

    for (const auto& info : feasiblePaths_) {
        std::cout << "  [path " << info.pathIndex << "] mem=" << info.mem;
        std::optional<double> prob;
        if (enableVolce) {
            if (info.volceCount) {
                std::cout << " volce=" << *info.volceCount;
                if (!inconsistentMemoryProjection && countedSolutionSpace > 0 &&
                    !countOverflow) {
                    const double probValue =
                        static_cast<double>(*info.volceCount) /
                        static_cast<double>(countedSolutionSpace);
                    prob = probValue;
                    std::cout << " prob=" << probValue;
                } else {
                    std::cout << " prob=N/A";
                }
            } else {
                std::cout << " volce=N/A prob=N/A";
            }
        }
        std::cout << std::endl;
        std::cout << "    path=" << info.path << std::endl;

        if (enableVolce && csvFile.is_open()) {
            std::string escapedPath = info.path;
            size_t pos = 0;
            while ((pos = escapedPath.find('"', pos)) != std::string::npos) {
                escapedPath.replace(pos, 1, "\"\"");
                pos += 2;
            }
            csvFile << info.pathIndex << ",\"" << escapedPath << "\"," << info.mem << ",";
            if (info.volceCount) {
                csvFile << *info.volceCount;
            }
            csvFile << ",";
            if (prob) {
                csvFile << *prob;
            }
            csvFile << ",\"[" << volceLower << "," << volceUpper << "]\"\n";
        }
    }

    if (enableVolce) {
        if (memoryProjectionArity) {
            std::cout << "[VOLCE MEMORY PROJECTION ARITY]: "
                      << *memoryProjectionArity << std::endl;
        }
        if (inconsistentMemoryProjection) {
            std::cout << "[VOLCE MEMORY PROJECTION STATUS]: "
                      << "INCONSISTENT_ACROSS_PATHS" << std::endl;
            std::cout << "[VOLCE MEMORY PROJECTION WARNING]: path counts "
                         "use different accessed-memory dimensions; do not "
                         "interpret their normalized weights as probabilities"
                      << std::endl;
        } else if (memoryProjectionArity) {
            std::cout << "[VOLCE MEMORY PROJECTION STATUS]: CONSISTENT_ARITY"
                      << std::endl;
        }
        if (inconsistentMemoryProjection) {
            std::cout << "[VOLCE SOLUTION SPACE COUNT]: "
                      << "N/A_INCONSISTENT_MEMORY_PROJECTION" << std::endl;
            std::cout << "[VOLCE TOTAL COUNT (LattE)]: "
                      << "N/A_INCONSISTENT_MEMORY_PROJECTION" << std::endl;
        } else if (countOverflow) {
            std::cout << "[VOLCE SOLUTION SPACE COUNT]: OVERFLOW" << std::endl;
            std::cout << "[VOLCE TOTAL COUNT (LattE)]: OVERFLOW" << std::endl;
        } else {
            std::cout << "[VOLCE SOLUTION SPACE COUNT]: " << countedSolutionSpace << std::endl;
            // Preserve the legacy label for existing experiment parsers.
            std::cout << "[VOLCE TOTAL COUNT (LattE)]: " << countedSolutionSpace << std::endl;
        }
    }

    if (enableVolce && countedSolutionSpace > 0 && !countOverflow &&
        !inconsistentMemoryProjection) {
        const long double weightedAverage =
            weightedMemsSum / static_cast<long double>(countedSolutionSpace);
        std::cout << "[VOLCE WEIGHTED MEMS SUM]: " << weightedMemsSum << std::endl;
        std::cout << "[VOLCE WEIGHTED AVERAGE MEMS]: " << weightedAverage << std::endl;
        // Preserve the legacy label for existing experiment parsers.
        std::cout << "[WEIGHTED AVG MEMS BY PROB]: " << weightedAverage << std::endl;
    } else if (enableVolce) {
        std::cout << "[VOLCE WEIGHTED MEMS SUM]: N/A" << std::endl;
        std::cout << "[VOLCE WEIGHTED AVERAGE MEMS]: N/A" << std::endl;
        std::cout << "[WEIGHTED AVG MEMS BY PROB]: N/A" << std::endl;
    }
}

namespace {
std::string extractFunctionName(const std::string& signature) {
    auto lparen = signature.find('(');
    if (lparen == std::string::npos) {
        return signature;
    }
    auto before = signature.substr(0, lparen);
    size_t end = before.find_last_not_of(" \t\n\r");
    if (end == std::string::npos) {
        return signature;
    }
    size_t start = end;
    while (start > 0) {
        char c = before[start - 1];
        if (!(std::isalnum(static_cast<unsigned char>(c)) || c == '_')) {
            break;
        }
        --start;
    }
    auto name = before.substr(start, end - start + 1);
    return name.empty() ? signature : name;
}

std::vector<std::string> extractDirectCalleesFromCallExprSnippet(const std::string& snippet) {
    std::vector<std::string> callees;
    const std::unordered_set<std::string> excludedKeywords{
        "if", "while", "for", "switch", "return", "sizeof"
    };
    const size_t n = snippet.size();
    size_t i = 0;
    while (i < n) {
        if (!(std::isalpha(static_cast<unsigned char>(snippet[i])) || snippet[i] == '_')) {
            ++i;
            continue;
        }
        const size_t start = i;
        ++i;
        while (i < n && (std::isalnum(static_cast<unsigned char>(snippet[i])) || snippet[i] == '_')) {
            ++i;
        }
        const std::string ident = snippet.substr(start, i - start);

        size_t j = i;
        while (j < n && std::isspace(static_cast<unsigned char>(snippet[j]))) {
            ++j;
        }
        if (j < n && snippet[j] == '(') {
            if (excludedKeywords.find(ident) == excludedKeywords.end()
                && std::find(callees.begin(), callees.end(), ident) == callees.end()) {
                callees.push_back(ident);
            }
        }
    }
    return callees;
}
}  // namespace

void SyntaxNamePrinter::dumpFunctionSummaries(int maxloop, int maxpaths, bool enableVolce, int volceLower, int volceUpper) {
    const char* entryEnv = std::getenv("EPPATHER_ENTRY");
    const std::string entryName = (entryEnv && *entryEnv) ? std::string(entryEnv) : std::string("main");

    std::vector<FunctionSummary> summaries;
    summaries.reserve(funcDefStack_.size());

    std::unordered_set<std::string> knownFunctions;
    for (const auto& funcNode : funcDefStack_) {
        if (!funcNode->functionName.empty()) {
            knownFunctions.insert(funcNode->functionName);
        }
    }

    std::unordered_map<std::string, FunctionSummary> directSummaries;
    std::unordered_map<std::string, std::vector<SummaryCase>> functionPathTable;
    std::unordered_map<std::string, std::unordered_set<std::string>> callGraph;

    for (size_t funcIndex = 0; funcIndex < funcDefStack_.size(); ++funcIndex) {
        const auto& funcNode = funcDefStack_[funcIndex];
        const std::string functionTag = sanitizeFunctionTag(
            funcNode->functionName.empty() ? ("func_" + std::to_string(funcIndex)) : funcNode->functionName);
        int pathCount = 0;
        loopCount.clear();
        loopCount.resize(maxdepth, 0);

        std::vector<bool> pathCoverage(maxdepth, false);
        std::vector<PathDecision> decisions;

        feasiblePaths_.clear();
        totalVolceCount_ = 0;
        feasCache.clear();
        maxmem = -1;
        minmem = std::numeric_limits<int>::max();

        currentPathCallees_.clear();
        DFS2(funcNode, pathCoverage, decisions, 0, pathCount, maxloop, maxpaths, enableVolce, volceLower, volceUpper, functionTag);

        FunctionSummary summary;
        const std::string signature = funcNode->getCode();
        summary.name = funcNode->functionName.empty() ? "unknown" : funcNode->functionName;
        summary.signature = signature.empty() ? "unknown" : signature;

        int worst = -1;
        double avg = -1.0;
        double sum = 0.0;
        double weightedSum = 0.0;
        std::uint64_t totalCount = totalVolceCount_;
        size_t probCases = 0;

        summary.cases.reserve(feasiblePaths_.size());
        for (const auto& info : feasiblePaths_) {
            SummaryCase caseSummary;
            caseSummary.guardHash = std::hash<std::string>{}(info.path);
            caseSummary.path = info.path;
            caseSummary.mems = info.mem;
            caseSummary.composedMems = info.mem;
            caseSummary.callees = info.callees;
            caseSummary.volceCount = info.volceCount;
            if (enableVolce && info.volceCount && totalCount > 0) {
                caseSummary.prob = static_cast<double>(*info.volceCount)
                                   / static_cast<double>(totalCount);
                weightedSum += static_cast<double>(info.mem) * *caseSummary.prob;
                ++probCases;
            }
            sum += static_cast<double>(info.mem);
            if (info.mem > worst) {
                worst = info.mem;
            }
            summary.cases.push_back(caseSummary);
        }

        if (!summary.cases.empty()) {
            if (enableVolce && totalCount > 0 && probCases == summary.cases.size()) {
                avg = weightedSum;
            } else {
                avg = sum / static_cast<double>(summary.cases.size());
            }
        }

        summary.worstMems = worst;
        summary.avgMems = avg;

        directSummaries[summary.name] = summary;
        functionPathTable[summary.name] = summary.cases;

        std::unordered_set<std::string> calleeSet;
        for (const auto& caseSummary : summary.cases) {
            for (const auto& callee : caseSummary.callees) {
                if (knownFunctions.find(callee) == knownFunctions.end()) {
                    continue;
                }
                calleeSet.insert(callee);
            }
        }
        callGraph[summary.name] = std::move(calleeSet);
        summaries.push_back(summary);
    }

    std::unordered_map<std::string, int> index;
    std::unordered_map<std::string, int> lowlink;
    std::unordered_map<std::string, bool> onStack;
    std::unordered_map<std::string, int> nodeToScc;
    std::vector<std::vector<std::string>> sccs;
    std::vector<std::string> tarjanStack;
    int tarjanIndex = 0;

    std::function<void(const std::string&)> strongConnect = [&](const std::string& v) {
        index[v] = tarjanIndex;
        lowlink[v] = tarjanIndex;
        ++tarjanIndex;
        tarjanStack.push_back(v);
        onStack[v] = true;

        auto it = callGraph.find(v);
        if (it != callGraph.end()) {
            for (const auto& w : it->second) {
                if (index.find(w) == index.end()) {
                    strongConnect(w);
                    lowlink[v] = std::min(lowlink[v], lowlink[w]);
                } else if (onStack[w]) {
                    lowlink[v] = std::min(lowlink[v], index[w]);
                }
            }
        }

        if (lowlink[v] == index[v]) {
            std::vector<std::string> component;
            while (!tarjanStack.empty()) {
                const std::string w = tarjanStack.back();
                tarjanStack.pop_back();
                onStack[w] = false;
                nodeToScc[w] = static_cast<int>(sccs.size());
                component.push_back(w);
                if (w == v) {
                    break;
                }
            }
            sccs.push_back(component);
        }
    };

    for (const auto& [name, _] : callGraph) {
        if (index.find(name) == index.end()) {
            strongConnect(name);
        }
    }

    auto isRecursiveScc = [&](const std::string& name) {
        auto sccIt = nodeToScc.find(name);
        if (sccIt == nodeToScc.end()) {
            return false;
        }
        const int sccId = sccIt->second;
        if (sccId < 0 || static_cast<size_t>(sccId) >= sccs.size()) {
            return false;
        }
        if (sccs[sccId].size() > 1) {
            return true;
        }
        auto cgIt = callGraph.find(name);
        return cgIt != callGraph.end() && cgIt->second.find(name) != cgIt->second.end();
    };

    std::unordered_map<std::string, int> approxWorst;
    std::unordered_map<std::string, double> approxAvg;
    std::unordered_map<std::string, size_t> approxBestCase;
    std::unordered_set<std::string> reasonSet;
    constexpr int kFixpointMaxIters = 32;

    for (const auto& [name, summary] : directSummaries) {
        approxWorst[name] = std::max(0, summary.worstMems);
        approxAvg[name] = summary.avgMems >= 0.0 ? summary.avgMems : 0.0;
        approxBestCase[name] = 0;
    }

    int iterationsUsed = 0;
    bool converged = false;
    for (int iter = 0; iter < kFixpointMaxIters; ++iter) {
        iterationsUsed = iter + 1;
        const auto prevWorst = approxWorst;
        const auto prevAvg = approxAvg;
        bool changed = false;

        for (const auto& [name, cases] : functionPathTable) {
            if (cases.empty()) {
                continue;
            }

            int newWorst = std::numeric_limits<int>::min();
            size_t bestIdx = 0;
            double newAvg = 0.0;
            bool hasProbWeight = enableVolce;
            double probSum = 0.0;

            for (size_t i = 0; i < cases.size(); ++i) {
                const auto& caseSummary = cases[i];
                int composedWorst = caseSummary.mems;
                double composedAvg = static_cast<double>(caseSummary.mems);

                for (const auto& callee : caseSummary.callees) {
                    if (knownFunctions.find(callee) == knownFunctions.end()) {
                        reasonSet.insert("external callee omitted=" + callee);
                        continue;
                    }
                    auto worstIt = prevWorst.find(callee);
                    auto avgIt = prevAvg.find(callee);
                    if (worstIt != prevWorst.end()) {
                        composedWorst += worstIt->second;
                    }
                    if (avgIt != prevAvg.end()) {
                        composedAvg += avgIt->second;
                    }
                }

                if (composedWorst > newWorst) {
                    newWorst = composedWorst;
                    bestIdx = i;
                }

                if (enableVolce) {
                    if (caseSummary.prob) {
                        newAvg += composedAvg * *caseSummary.prob;
                        probSum += *caseSummary.prob;
                    } else {
                        hasProbWeight = false;
                    }
                } else {
                    newAvg += composedAvg;
                }
            }

            if (!enableVolce) {
                newAvg /= static_cast<double>(cases.size());
            } else if (!hasProbWeight || probSum <= 0.0) {
                newAvg = 0.0;
                for (const auto& caseSummary : cases) {
                    double composedAvg = static_cast<double>(caseSummary.mems);
                    for (const auto& callee : caseSummary.callees) {
                        auto avgIt = prevAvg.find(callee);
                        if (avgIt != prevAvg.end()) {
                            composedAvg += avgIt->second;
                        }
                    }
                    newAvg += composedAvg;
                }
                newAvg /= static_cast<double>(cases.size());
                reasonSet.insert("missing volce probability during fixpoint composition for " + name);
            }

            if (newWorst != approxWorst[name]) {
                approxWorst[name] = newWorst;
                changed = true;
            }
            if (std::abs(newAvg - approxAvg[name]) > 1e-9) {
                approxAvg[name] = newAvg;
                changed = true;
            }
            approxBestCase[name] = bestIdx;
        }

        if (!changed) {
            converged = true;
            break;
        }
    }

    for (auto& summary : summaries) {
        auto tableIt = functionPathTable.find(summary.name);
        if (tableIt != functionPathTable.end()) {
            for (size_t i = 0; i < summary.cases.size() && i < tableIt->second.size(); ++i) {
                int composed = tableIt->second[i].mems;
                for (const auto& callee : tableIt->second[i].callees) {
                    auto it = approxWorst.find(callee);
                    if (it != approxWorst.end()) {
                        composed += it->second;
                    }
                }
                summary.cases[i].composedMems = composed;
            }
        }
        if (approxWorst.find(summary.name) != approxWorst.end()) {
            summary.worstMems = approxWorst[summary.name];
            summary.avgMems = approxAvg[summary.name];
        }
    }

    std::vector<std::string> worstSeq;
    if (knownFunctions.find(entryName) != knownFunctions.end()) {
        std::unordered_map<std::string, int> visitDepth;
        std::function<void(const std::string&)> buildWorstPath = [&](const std::string& functionName) {
            auto tableIt = functionPathTable.find(functionName);
            if (tableIt == functionPathTable.end() || tableIt->second.empty()) {
                reasonSet.insert("missing path summary for function=" + functionName);
                return;
            }
            const size_t caseIdx = std::min(approxBestCase[functionName], tableIt->second.size() - 1);
            const auto& pathCase = tableIt->second[caseIdx];
            worstSeq.push_back(functionName + "#" + std::to_string(caseIdx) + "{" + pathCase.path + "}");

            if (++visitDepth[functionName] > 1 && isRecursiveScc(functionName)) {
                worstSeq.push_back(functionName + "{FIXPOINT_APPROX}");
                reasonSet.insert("recursive SCC summarized by fixpoint at " + functionName);
                --visitDepth[functionName];
                return;
            }

            for (const auto& callee : pathCase.callees) {
                if (knownFunctions.find(callee) == knownFunctions.end()) {
                    continue;
                }
                buildWorstPath(callee);
            }
            --visitDepth[functionName];
        };
        buildWorstPath(entryName);
    }

    std::cout << "[FUNCTION SUMMARIES]" << std::endl;
    for (const auto& summary : summaries) {
        std::cout << "Function " << summary.name << ":" << std::endl;
        std::cout << "signature: " << summary.signature << std::endl;
        std::cout << "#cases: " << summary.cases.size() << std::endl;
        const auto directIt = directSummaries.find(summary.name);
        const int directWorst = (directIt != directSummaries.end() ? directIt->second.worstMems : -1);
        const double directAvg = (directIt != directSummaries.end() ? directIt->second.avgMems : -1.0);
        std::cout << "DIRECT worst_mems: " << directWorst << std::endl;
        if (directAvg < 0) {
            std::cout << "DIRECT avg_mems: N/A" << std::endl;
        } else if (enableVolce) {
            std::cout << "DIRECT weighted_avg_mems: " << directAvg << std::endl;
        } else {
            std::cout << "DIRECT avg_mems(equal-weight): " << directAvg << std::endl;
        }

        std::cout << "APPROX worst_mems: " << summary.worstMems << std::endl;
        if (summary.avgMems < 0) {
            std::cout << "APPROX avg_mems: N/A" << std::endl;
        } else if (enableVolce) {
            std::cout << "APPROX weighted_avg_mems: " << summary.avgMems << std::endl;
        } else {
            std::cout << "APPROX avg_mems(equal-weight): " << summary.avgMems << std::endl;
        }

        for (size_t i = 0; i < summary.cases.size(); ++i) {
            const auto& caseSummary = summary.cases[i];
            std::cout << "  [case " << i << "] guard_hash=" << caseSummary.guardHash
                      << " path=\"" << caseSummary.path << "\""
                      << " mems=" << caseSummary.mems
                      << " composed_mems=" << caseSummary.composedMems;
            if (caseSummary.volceCount) {
                std::cout << " volce=" << *caseSummary.volceCount;
            } else {
                std::cout << " volce=N/A";
            }
            if (caseSummary.prob) {
                std::cout << " prob=" << *caseSummary.prob;
            } else {
                std::cout << " prob=N/A";
            }
            std::cout << " callees=[";
            for (size_t calleeIdx = 0; calleeIdx < caseSummary.callees.size(); ++calleeIdx) {
                if (calleeIdx > 0) {
                    std::cout << ",";
                }
                std::cout << caseSummary.callees[calleeIdx];
            }
            std::cout << "]" << std::endl;
        }
    }

    std::cout << "[CALL GRAPH]" << std::endl;
    size_t callEdgeCount = 0;
    for (const auto& [caller, callees] : callGraph) {
        if (callees.empty()) {
            std::cout << caller << " -> []" << std::endl;
            continue;
        }
        std::cout << caller << " -> [";
        size_t idx = 0;
        for (const auto& callee : callees) {
            if (idx++ > 0) {
                std::cout << ",";
            }
            std::cout << callee;
            ++callEdgeCount;
        }
        std::cout << "]" << std::endl;
    }

    std::cout << "[SUMMARY STATS]" << std::endl;
    std::cout << "function_count=" << summaries.size() << std::endl;
    std::cout << "summary_case_count=";
    size_t totalCases = 0;
    for (const auto& summary : summaries) {
        totalCases += summary.cases.size();
    }
    std::cout << totalCases << std::endl;
    std::cout << "call_edge_count=" << callEdgeCount << std::endl;

    std::cout << "[PROGRAM SUMMARY]" << std::endl;
    std::cout << "entry=" << entryName << std::endl;
    std::cout << "recursion_policy=FUNCTION_SUMMARY_FIXPOINT_APPROX(max_iters=" << kFixpointMaxIters
              << ", used_iters=" << iterationsUsed
              << ", converged=" << (converged ? "true" : "false") << ")" << std::endl;

    if (knownFunctions.find(entryName) == knownFunctions.end()) {
        std::cout << "worst_mems=N/A" << std::endl;
        std::cout << "worst_path=N/A" << std::endl;
        std::cout << "weighted_avg_mems=N/A" << std::endl;
        std::cout << "reason=entry function not found" << std::endl;
        return;
    }

    if (worstSeq.empty()) {
        std::cout << "worst_mems=N/A" << std::endl;
        std::cout << "worst_path=N/A" << std::endl;
        std::cout << "weighted_avg_mems=N/A" << std::endl;
        std::cout << "reason=entry function has no available summary path" << std::endl;
        return;
    }

    const int worstMem = approxWorst[entryName];

    std::cout << "worst_mems=" << worstMem << std::endl;
    std::cout << "worst_path=";
    for (size_t i = 0; i < worstSeq.size(); ++i) {
        if (i > 0) {
            std::cout << " -> ";
        }
        std::cout << worstSeq[i];
    }
    std::cout << std::endl;

    std::cout << "weighted_avg_mems=" << approxAvg[entryName];
    if (!enableVolce) {
        std::cout << " (equal-weight; volce disabled)";
    }
    std::cout << std::endl;

    // Machine-readable program-level metrics.  For multi-function inputs these
    // deliberately follow the same labels as DFS2, so experiment runners do
    // not accidentally report the caller's direct (uncomposed) zero cost.
    std::uint64_t entryCount = 0;
    const auto entryIt = directSummaries.find(entryName);
    if (entryIt != directSummaries.end()) {
        for (const auto& pathCase : entryIt->second.cases) {
            if (pathCase.volceCount) entryCount += *pathCase.volceCount;
        }
    }
    if (enableVolce && entryCount > 0) {
        const long double programWeightedSum =
            static_cast<long double>(approxAvg[entryName]) * entryCount;
        std::cout << "[VOLCE SOLUTION SPACE COUNT]: " << entryCount << std::endl;
        std::cout << "[VOLCE WEIGHTED MEMS SUM]: " << programWeightedSum << std::endl;
        std::cout << "[VOLCE WEIGHTED AVERAGE MEMS]: " << approxAvg[entryName] << std::endl;
    }
    const size_t programPathCount =
        entryIt == directSummaries.end() ? 0 : entryIt->second.cases.size();
    std::cout << "[PROGRAM PATH COUNT]: " << programPathCount << std::endl;
    std::cout << "[DFS MAX MEMS]: " << worstMem << std::endl;

    if (!reasonSet.empty()) {
        std::cout << "notes=";
        size_t idx = 0;
        for (const auto& reason : reasonSet) {
            if (idx++ > 0) {
                std::cout << " | ";
            }
            std::cout << reason;
        }
        std::cout << std::endl;
    }
}



void SyntaxNamePrinter::DFS(
    std::shared_ptr<CFGNode> node,
    std::vector<bool>& pathCoverage,
    std::vector<PathDecision>& decisions,
    int depth,
    int& pathCount,
    int maxloop,
    int maxpaths,
    int& maxMems,
    int& minMems
) {
    if (maxpaths > 0 && pathCount >= maxpaths) return;
    if (!node) return;

    // 标记当前节点已访问
    if (node->depth >= 0)
        if (node->depth >= 0 && node->depth < static_cast<int>(pathCoverage.size())) pathCoverage[node->depth] = true;

    auto appendAndEvalLeaf = [&](bool includeCode) {
        bool pushed = false;
        if (includeCode && !node->isLoop && !node->isIf &&
            !node->isFuncDef && !(node->isVarDef && node->nodeLevel == 3)) {
            decisions.push_back(PathDecision{node.get(), PathDecisionKind::Code});
            pushed = true;
        }

        EpatRunner runner(vartemp);
        auto eval = runner.solve(decisions);
        const bool feasible = eval.status == result::feasible;
        if (feasible) {
            if (eval.mem > maxMems) maxMems = eval.mem;
            if (eval.mem < minMems) minMems = eval.mem;
        }

        auto script = runner.render(decisions);
        processPathResult(eval, script, pathCoverage, pathCount, depth);
        ++pathCount;

        if (pushed) decisions.pop_back();
    };

    // 叶子节点处理
    if (node->isReturn || !node->getNextNode()) {
        appendAndEvalLeaf(true);
        return;
    }

    if (node->isLoop) {
        if (node->isFor) {
            // False分支（循环终止）
            if (node->depth < 0 || node->depth >= static_cast<int>(loopCount.size())) return;
            if (node->depth < 0 || node->depth >= static_cast<int>(loopCount.size())) return;
            if (node->depth < 0 || node->depth >= static_cast<int>(loopCount.size())) return;
            if (node->depth < 0 || node->depth >= static_cast<int>(loopCount.size())) return;
            if (loopCount[node->depth] >= predictedLoopBound(node.get(), maxloop)) {
                decisions.push_back(PathDecision{node.get(), PathDecisionKind::FalseBranch});
                loopCount[node->depth] = 0;
                auto falseNode = node->getNextFalseNode();
                auto afterFalse = falseNode ? falseNode->getNextNode() : nullptr;
                DFS(afterFalse, pathCoverage, decisions, depth + 1, pathCount, maxloop, maxpaths, maxMems, minMems);
                decisions.pop_back();
                return;
            }
            // 第一次进入时补初始化
            bool pushedInit = false;
            if (node->depth < 0 || node->depth >= static_cast<int>(loopCount.size())) return;
            if (loopCount[node->depth] == 0 && node->initstmt_str != ";") {
                decisions.push_back(PathDecision{node.get(), PathDecisionKind::LoopInit});
                pushedInit = true;
            }

            // True分支（进入循环体）
            decisions.push_back(PathDecision{node.get(), PathDecisionKind::TrueBranch});
            decisions.push_back(PathDecision{node.get(), PathDecisionKind::LoopUpdate});
            const int savedLoopCount = loopCount[node->depth];
            loopCount[node->depth]++;
            DFS(node->getNextNode(), pathCoverage, decisions, depth + 1, pathCount, maxloop, maxpaths, maxMems, minMems);
            loopCount[node->depth] = savedLoopCount;
            decisions.pop_back();
            decisions.pop_back();
            if (pushedInit) decisions.pop_back();

        }

        if (node->isWhile) {
            // False分支（循环终止）
            if (node->depth < 0 || node->depth >= static_cast<int>(loopCount.size())) return;
            if (node->depth < 0 || node->depth >= static_cast<int>(loopCount.size())) return;
            if (loopCount[node->depth] >= predictedLoopBound(node.get(), maxloop)) {
                decisions.push_back(PathDecision{node.get(), PathDecisionKind::FalseBranch});
                loopCount[node->depth] = 0;
                DFS(node->getNextFalseNode(), pathCoverage, decisions, depth + 1, pathCount, maxloop, maxpaths, maxMems, minMems);
                decisions.pop_back();
                return;
            }
            // True分支（进入循环体）
            decisions.push_back(PathDecision{node.get(), PathDecisionKind::TrueBranch});
            const int savedLoopCount = loopCount[node->depth];
            loopCount[node->depth]++;
            DFS(node->getNextNode(), pathCoverage, decisions, depth + 1, pathCount, maxloop, maxpaths, maxMems, minMems);
            loopCount[node->depth] = savedLoopCount;
            decisions.pop_back();
        }
    }

    if (node->isIf) {
        // True分支

        if (depth >= static_cast<int>(temp_loopCount.size())) {
            temp_loopCount.resize(static_cast<size_t>(depth + 1));
        }
        temp_loopCount[depth]=loopCount;
        auto temp_pathcoverage = pathCoverage;
        decisions.push_back(PathDecision{node.get(), PathDecisionKind::TrueBranch});
        DFS(node->getNextNode(), pathCoverage, decisions, depth + 1, pathCount, maxloop, maxpaths, maxMems, minMems);
        decisions.pop_back();

        // False分支
        for (int i=node->depth+1;i<maxdepth;i++)
            pathCoverage[i]=false;//对于之前下面的覆盖率清零；

        pathCoverage = temp_pathcoverage;
        if (depth >= 0 && depth < static_cast<int>(temp_loopCount.size())) {
            loopCount=temp_loopCount[depth];
        }
        decisions.push_back(PathDecision{node.get(), PathDecisionKind::FalseBranch});
        DFS(node->getNextFalseNode(), pathCoverage, decisions, depth + 1, pathCount, maxloop, maxpaths, maxMems, minMems);
        decisions.pop_back();
        return;
    }

    if (node->isFuncDef || (node->isVarDef && node->nodeLevel == 3)) {
        DFS(node->getNextNode(), pathCoverage, decisions, depth + 1, pathCount, maxloop, maxpaths, maxMems, minMems);
        return;
    }

    decisions.push_back(PathDecision{node.get(), PathDecisionKind::Code});
    DFS(node->getNextNode(), pathCoverage, decisions, depth + 1, pathCount, maxloop, maxpaths, maxMems, minMems);
    decisions.pop_back();
}

#include <iomanip>  // 注意：用于 setw 对齐

// 开始前清空矩阵
void SyntaxNamePrinter::startBranchMatrix() {
    branchCovMatrix_.clear();
}

// 在 DFS 叶子时把一条路径写入矩阵（自动填充到 2*maxdepth 列）
void SyntaxNamePrinter::pushBranchRow(const std::vector<bool>& row) {
    const int COLS = std::max(0, 2 * maxdepth);   // 每个 depth 两列：T/F
    std::vector<int> r(COLS, 0);
    const int n = std::min<int>(COLS, row.size());
    for (int i = 0; i < n; ++i) r[i] = row[i] ? 1 : 0;
    branchCovMatrix_.push_back(std::move(r));
}

// 统一对齐打印矩阵
void SyntaxNamePrinter::printBranchMatrix() {
    const int COLS = std::max(0, 2 * maxdepth);
    std::cout << "[MATRIX]:\n";
    for (const auto& r : branchCovMatrix_) {
        for (int c = 0; c < COLS; ++c) {
            std::cout << std::setw(2) << r[c] << ' ';
        }
        std::cout << '\n';
    }
}
void SyntaxNamePrinter::DFS2(std::shared_ptr<CFGNode> node,
                             std::vector<bool>& pathCoverage,
                             std::vector<PathDecision>& decisions,
                             int depth,
                             int& pathCount,
                             int maxloop,
                             int maxpaths,
                             bool enableVolce,
                             int volceLower,
                             int volceUpper,
                             const std::string& functionTag)
{
    if (maxpaths > 0 && pathCount >= maxpaths) return;
    if (!node) return;
    emitCrashTrace("DFS2.enter", node, depth);

    struct CalleeRestore {
        std::vector<std::string>& ref;
        std::vector<std::string> old;
        explicit CalleeRestore(std::vector<std::string>& r) : ref(r), old(r) {}
        ~CalleeRestore() { ref = std::move(old); }
    } restore(currentPathCallees_);

    for (const auto& callee : node->calleeNames) {
        if (std::find(currentPathCallees_.begin(), currentPathCallees_.end(), callee) == currentPathCallees_.end()) {
            currentPathCallees_.push_back(callee);
        }
    }
    const auto baseCallees = currentPathCallees_;

    // 原有：按当前 pathCoverage 扩容
    auto ensure_cov = [&](int d){
        int need = 2 * d + 2;
        if ((int)pathCoverage.size() < need) pathCoverage.resize(need, false);
    };
    // 新增：对任意向量 vec 扩容（关键修复点：用于 cov_t/cov_f 等分支副本）
    auto ensure_cov_vec = [&](std::vector<bool>& vec, int d){
        int need = 2 * d + 2;
        if ((int)vec.size() < need) vec.resize(need, false);
    };
    // 原有：循环计数扩容
    auto ensure_loop = [&](int d){
        if (d < 0) return;
        if ((int)loopCount.size() <= d) loopCount.resize(d + 1, 0);
    };
    // 新增：叶子统一对齐（把该行补到 2*maxdepth 列）
    auto pad_to_full_cols = [&](std::vector<bool>& vec){
        int want = 2 * std::max(0, maxdepth);
        if ((int)vec.size() < want) vec.resize(want, false);
    };
    auto is_decision_feasible = [&](const std::vector<PathDecision>& nextDecisions) {
        // Prefix scripts are not complete C paths.  In particular, a prefix
        // ending at a negated loop guard can underflow epat++'s expression
        // stack.  Solve complete leaf paths by default; keep prefix pruning as
        // an explicit experimental opt-in.
        const char* prefixCheck = std::getenv("EPPATHER_PREFIX_FEASIBILITY");
        if (!prefixCheck || !*prefixCheck || std::string(prefixCheck) == "0") {
            return true;
        }
        static const EpatRunner rawRunner("");
        const std::string rawPath = rawRunner.render(nextDecisions);
        return isPathFeasible(nextDecisions, rawPath);
    };
    // 非条件普通语句：同时打 T/F 覆盖位
    if (node->depth >= 0 && !node->isCondition) {
        ensure_cov(node->depth);
        const int trueIdx = 2 * node->depth;
        const int falseIdx = trueIdx + 1;
        if (trueIdx >= 0 && trueIdx < static_cast<int>(pathCoverage.size())) {
            pathCoverage[trueIdx] = true;
        }
        if (falseIdx >= 0 && falseIdx < static_cast<int>(pathCoverage.size())) {
            pathCoverage[falseIdx] = true;
        }
    }

    // 叶子：return 或 无后继（将当前节点代码补入，再判可行）
    if (node->isReturn || !node->getNextNode()) {
        bool pushed = false;
        if (!node->isLoop && !node->isIf && !node->isFuncDef && !(node->isVarDef && node->nodeLevel == 3)) {
            const std::string code = node->getCode();
            if (!code.empty()) {
                decisions.push_back(PathDecision{node.get(), PathDecisionKind::Code});
                pushed = true;
            }
        }
        EpatRunner runner(vartemp);
        auto eval = runner.solve(decisions);
        const bool feasible = eval.status == result::feasible;
        if (!feasible) {
            if (pushed) decisions.pop_back();
            return;
        }
        if (eval.mem > maxmem) maxmem = eval.mem;
        if (eval.mem < minmem) minmem = eval.mem;

        // 关键修复：叶子处将覆盖向量统一补齐到 2*maxdepth 列，保证输出矩阵行对齐
        pad_to_full_cols(pathCoverage);

        auto script = runner.render(decisions);
        processPathResult2(eval, script, pathCoverage, pathCount, depth, functionTag, enableVolce, volceLower, volceUpper, currentPathCallees_);
        ++pathCount;
        if (pushed) decisions.pop_back();
        return;
    }

    // ===================== FOR =====================
    if (node->isLoop && node->isFor) {
        const int d = node->depth;
        ensure_loop(d);

        // 清理更深层的展开计数，避免跨层污染
        if (!loopCount.empty()) {
            for (int k = d + 1, sz = (int)loopCount.size(); k < sz; ++k) loopCount[k] = 0;
        }

        // 为 T/F 分支分别保存快照
        const std::vector<bool>  snap_cov  = pathCoverage;
        const std::vector<int>   snap_lc   = loopCount;

        // Fixed-cell memory shortcut. This is separately opt-in and stricter
        // than scalar acceleration: every memory relation must be a fixed cell
        // of a one-dimensional local fixed array, with structurally complete
        // effects and exact MEMS compensation.
        const char* memoryAccelRaw =
            std::getenv("EPPATHER_LOOP_SCC_MEMORY_ACCELERATE");
        const bool memoryAccelRequested =
            memoryAccelRaw && *memoryAccelRaw &&
            std::string(memoryAccelRaw) != "0";
        // Runtime replacement is allowed only after the memory-plan builder
        // establishes a pre-execution structural certificate. VolCE relation
        // and untouched-frame proofs remain independent A/B oracles.
        const bool memoryAccelEnabled = memoryAccelRequested;
        if (memoryAccelEnabled && snap_lc[d] == 0) {
            const auto graph =
                LoopSccAdapter::analyzeWithConstantPointerAliases(
                    node.get(), vartemp);
            bool usedMemoryShortcut = false;
            for (std::size_t candidateIndex = 0;
                 candidateIndex < graph.memorySummaryCandidates.size();
                 ++candidateIndex) {
                auto prefix = decisions;
                if (!node->initstmt_str.empty() &&
                    node->initstmt_str != ";") {
                    prefix.push_back(PathDecision{
                        node.get(), PathDecisionKind::LoopInit});
                }
                auto memoryPlan =
                    buildLoopSccMemoryAccelerationDecisions(
                        prefix, node.get(), graph, candidateIndex,
                        vartemp);
                if (!memoryPlan) continue;
                if (!memoryPlan->preexecutionCertified) {
                    std::cout
                        << "[LOOPSCC MEMORY DFS SHORTCUT BLOCKED]: reason="
                        << "preexecution_structural_certificate_failed"
                        << std::endl;
                    for (const auto& diagnostic :
                         memoryPlan->certificateDiagnostics) {
                        std::cout
                            << "[LOOPSCC MEMORY PREEXEC DIAGNOSTIC]: "
                            << diagnostic << std::endl;
                    }
                    continue;
                }
                std::cout
                    << "[LOOPSCC MEMORY PREEXEC CERTIFICATE]: certified=1"
                    << " unfolded_mems=" << memoryPlan->unfoldedMems
                    << " compensation=" << memoryPlan->compensationMems
                    << std::endl;

                auto cov_a = snap_cov;
                for (int slot : memoryPlan->coverageSlots) {
                    if (slot < 0) continue;
                    if (slot >= static_cast<int>(cov_a.size())) {
                        cov_a.resize(
                            static_cast<std::size_t>(slot + 1), false);
                    }
                    cov_a[static_cast<std::size_t>(slot)] = true;
                }

                auto saved = loopCount;
                loopCount = snap_lc;
                if (static_cast<int>(loopCount.size()) <= d) {
                    loopCount.resize(d + 1, 0);
                }
                loopCount[d] = 0;

                EpatRunner shortcutRunner(vartemp);
                const auto shortcutEval =
                    shortcutRunner.solve(memoryPlan->decisions);
                if (shortcutEval.status == result::feasible) {
                    const auto& candidate =
                        graph.memorySummaryCandidates[candidateIndex];
                    std::cout
                        << "[LOOPSCC MEMORY DFS SHORTCUT USED]: kind=for period="
                        << candidate.period
                        << " iterations=" << candidate.totalIterations
                        << " entry_phase=" << candidate.entryPhase
                        << " unfolded_mems=" << memoryPlan->unfoldedMems
                        << " summary_mems="
                        << memoryPlan->compressedSummaryMems
                        << " compensation="
                        << memoryPlan->compensationMems
                        << " decisions=" << memoryPlan->decisions.size()
                        << std::endl;
                    currentPathCallees_ = baseCallees;
                    DFS2(node->getNextFalseNode(), cov_a,
                         memoryPlan->decisions, depth + 1, pathCount,
                         maxloop, maxpaths, enableVolce,
                         volceLower, volceUpper, functionTag);
                    usedMemoryShortcut = true;
                }
                loopCount = saved;
            }
            if (usedMemoryShortcut) {
                loopCount = snap_lc;
                pathCoverage = snap_cov;
                return;
            }
        }

        // The same certified LoopSCC shortcut used for while-loops also applies
        // to canonical for-loops once the adapter has proved the total SPath
        // transform and exact trip count. The for initializer is part of the
        // entry semantics and must execute exactly once before the closed form;
        // the repeated post expression is already included in T^k.
        const char* accelRaw =
            std::getenv("EPPATHER_LOOP_SCC_ACCELERATE");
        const bool accelEnabled =
            accelRaw && *accelRaw && std::string(accelRaw) != "0";
        if (accelEnabled && snap_lc[d] == 0) {
            const auto graph = LoopSccAdapter::analyze(node.get());
            bool usedShortcut = false;
            for (std::size_t planIndex = 0;
                 planIndex < graph.accelerationPlans.size();
                 ++planIndex) {
                const auto& plan = graph.accelerationPlans[planIndex];
                if (!plan.exact || !plan.memsPreserving ||
                    plan.totalIterations <= 0 ||
                    plan.skippableIterations != plan.totalIterations) {
                    continue;
                }

                auto prefix = decisions;
                if (!node->initstmt_str.empty() &&
                    node->initstmt_str != ";") {
                    prefix.push_back(PathDecision{
                        node.get(), PathDecisionKind::LoopInit});
                }
                auto accelerated =
                    buildLoopSccAccelerationDecisions(
                        prefix, node.get(), graph, planIndex);
                if (!accelerated) continue;

                auto cov_a = snap_cov;
                for (int slot : plan.coverageSlots) {
                    if (slot < 0) continue;
                    if (slot >= static_cast<int>(cov_a.size())) {
                        cov_a.resize(
                            static_cast<std::size_t>(slot + 1), false);
                    }
                    cov_a[static_cast<std::size_t>(slot)] = true;
                }

                auto saved = loopCount;
                loopCount = snap_lc;
                if (static_cast<int>(loopCount.size()) <= d) {
                    loopCount.resize(d + 1, 0);
                }
                loopCount[d] = 0;

                EpatRunner shortcutRunner(vartemp);
                const auto shortcutEval =
                    shortcutRunner.solve(*accelerated);
                if (shortcutEval.status == result::feasible) {
                    std::cout
                        << "[LOOPSCC DFS SHORTCUT USED]: kind=for period="
                        << plan.period
                        << " iterations=" << plan.totalIterations
                        << " entry_phase=" << plan.entryPhase
                        << " decisions=" << accelerated->size()
                        << std::endl;
                    currentPathCallees_ = baseCallees;
                    DFS2(node->getNextFalseNode(), cov_a,
                         *accelerated, depth + 1, pathCount,
                         maxloop, maxpaths, enableVolce,
                         volceLower, volceUpper, functionTag);
                    usedShortcut = true;
                }
                loopCount = saved;
            }
            if (usedShortcut) {
                loopCount = snap_lc;
                pathCoverage = snap_cov;
                return;
            }
        }

        // True：@(cond) → 体（顺着 CFG 的 next 走）
        if (loopCount[d] < predictedLoopBound(node.get(), maxloop)) {
            auto        cov_t = snap_cov;
            auto        lc_t  = snap_lc;

            // 关键修复：对 cov_t 本身扩容后再写位
            ensure_cov_vec(cov_t, d);
            cov_t[2 * d] = true;

            // 本层展开+1，只影响 True 这条路径
            if ((int)lc_t.size() <= d) lc_t.resize(d + 1, 0);
            lc_t[d] += 1;

            // 下钻（用 True 的 loop 计数）
            auto saved = loopCount;
            loopCount  = lc_t;
            const bool firstCheck = loopCount[d] == 1;
            if (firstCheck && !node->initstmt_str.empty() && node->initstmt_str != ";") {
                decisions.push_back(PathDecision{node.get(), PathDecisionKind::LoopInit});
            }
            if (!firstCheck && !node->expr_str.empty()) {
                decisions.push_back(PathDecision{node.get(), PathDecisionKind::LoopUpdate});
            }
            decisions.push_back(PathDecision{node.get(), PathDecisionKind::TrueBranch});
            if (is_decision_feasible(decisions)) {
                currentPathCallees_ = baseCallees;
                DFS2(node->getNextNode(), cov_t, decisions, depth + 1, pathCount, maxloop, maxpaths, enableVolce, volceLower, volceUpper, functionTag);
            }
            decisions.pop_back();
            if (!firstCheck && !node->expr_str.empty()) {
                decisions.pop_back();
            }
            if (firstCheck && !node->initstmt_str.empty() && node->initstmt_str != ";") {
                decisions.pop_back();
            }
            loopCount = saved;
        }

        // False：@(!(cond)) → 走 CFG 的 false 边（join/end）
        {
            auto        cov_f = snap_cov;
            ensure_cov_vec(cov_f, d);
            cov_f[2 * d + 1] = true;

            const bool firstCheck = snap_lc[d] == 0;
            if (firstCheck && !node->initstmt_str.empty() && node->initstmt_str != ";") {
                decisions.push_back(PathDecision{node.get(), PathDecisionKind::LoopInit});
            }
            if (!firstCheck && !node->expr_str.empty()) {
                decisions.push_back(PathDecision{node.get(), PathDecisionKind::LoopUpdate});
            }
            decisions.push_back(PathDecision{node.get(), PathDecisionKind::FalseBranch});
            if (is_decision_feasible(decisions)) {
                currentPathCallees_ = baseCallees;
                DFS2(node->getNextFalseNode(), cov_f, decisions, depth + 1, pathCount, maxloop, maxpaths, enableVolce, volceLower, volceUpper, functionTag);
            }
            decisions.pop_back();
            if (!firstCheck && !node->expr_str.empty()) {
                decisions.pop_back();
            }
            if (firstCheck && !node->initstmt_str.empty() && node->initstmt_str != ";") {
                decisions.pop_back();
            }
        }
        return;
    }

    // ===================== WHILE =====================
    if (node->isLoop && node->isWhile) {
        const int d = node->depth;
        ensure_loop(d);

        // 清理更深层展开计数
        if (!loopCount.empty()) {
            for (int k = d + 1, sz = (int)loopCount.size(); k < sz; ++k) loopCount[k] = 0;
        }

        // 为 T/F 分支保存快照
        const std::vector<bool>  snap_cov  = pathCoverage;
        const std::vector<int>   snap_lc   = loopCount;

        // Fixed-cell local-array shortcut with exact MEMS compensation.
        // Pointer, symbolic-index, cross-cell, VLA/unknown-region and opaque
        // effects cannot construct this plan and therefore fall back.
        const char* memoryAccelRaw =
            std::getenv("EPPATHER_LOOP_SCC_MEMORY_ACCELERATE");
        const bool memoryAccelRequested =
            memoryAccelRaw && *memoryAccelRaw &&
            std::string(memoryAccelRaw) != "0";
        // Runtime replacement is allowed only after the memory-plan builder
        // establishes a pre-execution structural certificate. VolCE relation
        // and untouched-frame proofs remain independent A/B oracles.
        const bool memoryAccelEnabled = memoryAccelRequested;
        if (memoryAccelEnabled && snap_lc[d] == 0) {
            const auto graph =
                LoopSccAdapter::analyzeWithConstantPointerAliases(
                    node.get(), vartemp);
            bool usedMemoryShortcut = false;
            for (std::size_t candidateIndex = 0;
                 candidateIndex < graph.memorySummaryCandidates.size();
                 ++candidateIndex) {
                auto memoryPlan =
                    buildLoopSccMemoryAccelerationDecisions(
                        decisions, node.get(), graph, candidateIndex,
                        vartemp);
                if (!memoryPlan) continue;
                if (!memoryPlan->preexecutionCertified) {
                    std::cout
                        << "[LOOPSCC MEMORY DFS SHORTCUT BLOCKED]: reason="
                        << "preexecution_structural_certificate_failed"
                        << std::endl;
                    for (const auto& diagnostic :
                         memoryPlan->certificateDiagnostics) {
                        std::cout
                            << "[LOOPSCC MEMORY PREEXEC DIAGNOSTIC]: "
                            << diagnostic << std::endl;
                    }
                    continue;
                }
                std::cout
                    << "[LOOPSCC MEMORY PREEXEC CERTIFICATE]: certified=1"
                    << " unfolded_mems=" << memoryPlan->unfoldedMems
                    << " compensation=" << memoryPlan->compensationMems
                    << std::endl;

                auto cov_a = snap_cov;
                for (int slot : memoryPlan->coverageSlots) {
                    if (slot < 0) continue;
                    if (slot >= static_cast<int>(cov_a.size())) {
                        cov_a.resize(
                            static_cast<std::size_t>(slot + 1), false);
                    }
                    cov_a[static_cast<std::size_t>(slot)] = true;
                }

                auto saved = loopCount;
                loopCount = snap_lc;
                if (static_cast<int>(loopCount.size()) <= d) {
                    loopCount.resize(d + 1, 0);
                }
                loopCount[d] = 0;

                EpatRunner shortcutRunner(vartemp);
                const auto shortcutEval =
                    shortcutRunner.solve(memoryPlan->decisions);
                if (shortcutEval.status == result::feasible) {
                    const auto& candidate =
                        graph.memorySummaryCandidates[candidateIndex];
                    std::cout
                        << "[LOOPSCC MEMORY DFS SHORTCUT USED]: kind=while period="
                        << candidate.period
                        << " iterations=" << candidate.totalIterations
                        << " entry_phase=" << candidate.entryPhase
                        << " unfolded_mems=" << memoryPlan->unfoldedMems
                        << " summary_mems="
                        << memoryPlan->compressedSummaryMems
                        << " compensation="
                        << memoryPlan->compensationMems
                        << " decisions=" << memoryPlan->decisions.size()
                        << std::endl;
                    currentPathCallees_ = baseCallees;
                    DFS2(node->getNextFalseNode(), cov_a,
                         memoryPlan->decisions, depth + 1, pathCount,
                         maxloop, maxpaths, enableVolce,
                         volceLower, volceUpper, functionTag);
                    usedMemoryShortcut = true;
                }
                loopCount = saved;
            }
            if (usedMemoryShortcut) {
                loopCount = snap_lc;
                pathCoverage = snap_cov;
                return;
            }
        }

        // Experimental certified LoopSCC shortcut. It is deliberately
        // opt-in and restricted to plans that already proved:
        // - exact trip count and determinate phase cycle;
        // - phase-guard inclusion;
        // - scalar affine T^k relation;
        // - MEMS preservation (no array/dereference/opaque effect);
        // - zero residual phase.
        const char* accelRaw =
            std::getenv("EPPATHER_LOOP_SCC_ACCELERATE");
        const bool accelEnabled =
            accelRaw && *accelRaw && std::string(accelRaw) != "0";
        if (accelEnabled && snap_lc[d] == 0) {
            const auto graph = LoopSccAdapter::analyze(node.get());
            bool usedShortcut = false;
            for (std::size_t planIndex = 0;
                 planIndex < graph.accelerationPlans.size();
                 ++planIndex) {
                const auto& plan =
                    graph.accelerationPlans[planIndex];
                if (!plan.exact || !plan.memsPreserving ||
                    plan.totalIterations <= 0 ||
                    plan.skippableIterations !=
                        plan.totalIterations) {
                    continue;
                }

                auto accelerated =
                    buildLoopSccAccelerationDecisions(
                        decisions, node.get(), graph, planIndex);
                if (!accelerated) continue;

                auto cov_a = snap_cov;
                for (int slot : plan.coverageSlots) {
                    if (slot < 0) continue;
                    if (slot >= static_cast<int>(cov_a.size())) {
                        cov_a.resize(
                            static_cast<std::size_t>(slot + 1), false);
                    }
                    cov_a[static_cast<std::size_t>(slot)] = true;
                }

                auto saved = loopCount;
                loopCount = snap_lc;
                if (static_cast<int>(loopCount.size()) <= d) {
                    loopCount.resize(d + 1, 0);
                }
                loopCount[d] = 0;

                // Unlike ordinary prefix pruning, shortcut admission
                // must prove that at least one summarized entry phase is
                // feasible at the loop exit. Otherwise suppressing the
                // unfolded fallback could lose all valid paths.
                EpatRunner shortcutRunner(vartemp);
                const auto shortcutEval =
                    shortcutRunner.solve(*accelerated);
                if (shortcutEval.status == result::feasible) {
                    std::cout
                        << "[LOOPSCC DFS SHORTCUT USED]: period="
                        << plan.period
                        << " iterations=" << plan.totalIterations
                        << " entry_phase=" << plan.entryPhase
                        << " decisions=" << accelerated->size()
                        << std::endl;
                    currentPathCallees_ = baseCallees;
                    DFS2(node->getNextFalseNode(), cov_a,
                         *accelerated, depth + 1, pathCount,
                         maxloop, maxpaths, enableVolce,
                         volceLower, volceUpper, functionTag);
                    usedShortcut = true;
                }
                loopCount = saved;
            }
            if (usedShortcut) {
                loopCount = snap_lc;
                pathCoverage = snap_cov;
                return;
            }
        }

        // True：@(cond) → 体（顺着 CFG 的 next 走）
        if (loopCount[d] < predictedLoopBound(node.get(), maxloop)) {
            auto        cov_t = snap_cov;
            auto        lc_t  = snap_lc;

            ensure_cov_vec(cov_t, d);
            cov_t[2 * d] = true;

            if ((int)lc_t.size() <= d) lc_t.resize(d + 1, 0);
            lc_t[d] += 1;

            auto saved = loopCount;
            loopCount  = lc_t;
            decisions.push_back(PathDecision{node.get(), PathDecisionKind::TrueBranch});
            if (is_decision_feasible(decisions)) {
                currentPathCallees_ = baseCallees;
                DFS2(node->getNextNode(), cov_t, decisions, depth + 1, pathCount, maxloop, maxpaths, enableVolce, volceLower, volceUpper, functionTag);
            }
            decisions.pop_back();
            loopCount = saved;
        }

        // False：@(!(cond)) → 走 CFG 的 false 边（join/end）
        {
            auto        cov_f = snap_cov;
            ensure_cov_vec(cov_f, d);
            cov_f[2 * d + 1] = true;

            decisions.push_back(PathDecision{node.get(), PathDecisionKind::FalseBranch});
            if (is_decision_feasible(decisions)) {
                currentPathCallees_ = baseCallees;
                DFS2(node->getNextFalseNode(), cov_f, decisions, depth + 1, pathCount, maxloop, maxpaths, enableVolce, volceLower, volceUpper, functionTag);
            }
            decisions.pop_back();
        }
        return;
    }

    // ===================== IF =====================
    if (node->isIf) {
        const int d = node->depth;

        // Branch state must be stack-local.  A CFG node can be revisited on
        // successive loop iterations, so indexing member scratch storage by
        // node->depth is not re-entrant: a recursive visit to the same IF
        // overwrites the outer snapshot before its false branch is explored.
        // That used to drop valid alternating paths such as T,F,T,F.
        const std::vector<bool> snap_cov = pathCoverage;
        const std::vector<int> snap_lc = loopCount;

        // True
        {
            auto cov_t = snap_cov;
            ensure_cov_vec(cov_t, d);
            cov_t[2 * d] = true;
            loopCount = snap_lc;

            decisions.push_back(PathDecision{
                node.get(), PathDecisionKind::TrueBranch});
            if (is_decision_feasible(decisions)) {
                currentPathCallees_ = baseCallees;
                DFS2(node->getNextNode(), cov_t, decisions, depth + 1,
                     pathCount, maxloop, maxpaths, enableVolce,
                     volceLower, volceUpper, functionTag);
            }
            decisions.pop_back();
        }

        // False starts from the exact same caller state, independent of any
        // recursive visits performed by the true branch.
        {
            auto cov_f = snap_cov;
            ensure_cov_vec(cov_f, d);
            cov_f[2 * d + 1] = true;
            loopCount = snap_lc;

            decisions.push_back(PathDecision{
                node.get(), PathDecisionKind::FalseBranch});
            if (is_decision_feasible(decisions)) {
                currentPathCallees_ = baseCallees;
                DFS2(node->getNextFalseNode(), cov_f, decisions, depth + 1,
                     pathCount, maxloop, maxpaths, enableVolce,
                     volceLower, volceUpper, functionTag);
            }
            decisions.pop_back();
        }

        loopCount = snap_lc;
        pathCoverage = snap_cov;
        return;
    }

    // ===================== 其它顺序节点 =====================
    if (node->isFuncDef || (node->isVarDef && node->nodeLevel == 3)) {
        currentPathCallees_ = baseCallees;
        DFS2(node->getNextNode(), pathCoverage, decisions, depth + 1, pathCount, maxloop, maxpaths, enableVolce, volceLower, volceUpper, functionTag);
        return;
    }

    decisions.push_back(PathDecision{node.get(), PathDecisionKind::Code});
    currentPathCallees_ = baseCallees;
    DFS2(node->getNextNode(), pathCoverage, decisions, depth + 1, pathCount, maxloop, maxpaths, enableVolce, volceLower, volceUpper, functionTag);
    decisions.pop_back();
}


// Helper: LoopMap简化key
// ========== 辅助：循环计数序列化（与 DFS2 统一用“按节点指针计数”） ==========
static std::string LoopMapKey(const std::unordered_map<CFGNode*, int>& mp) {
    std::vector<std::pair<uintptr_t,int>> v;
    v.reserve(mp.size());
    for (const auto& kv : mp) v.push_back({reinterpret_cast<uintptr_t>(kv.first), kv.second});
    std::sort(v.begin(), v.end());
    std::string res;
    for (auto &p : v) {
        res += std::to_string(p.first);
        res += ":";
        res += std::to_string(p.second);
        res += "|";
    }
    return res;
}


// ========== 可行性缓存，避免重复求解 ==========
namespace psy {
namespace C {
std::unordered_map<std::string, bool> feasCache;

// 仅在可行性判定时拼接 vartemp；其他地方一律使用 raw path
inline bool feasibleWithVartemp(
    SyntaxNamePrinter* self,
    const std::vector<PathDecision>& decisions,
    const std::string& rawPath) {
    return self->isPathFeasible(decisions, rawPath);
}

inline bool isPathFeasibleCached(
    SyntaxNamePrinter* self,
    const std::vector<PathDecision>& decisions,
    const std::string& fullExpr) {
    // An incomplete prefix can leave epat++'s expression stack in an invalid
    // state and is not a sound feasibility query.  Match DFS2: prune prefixes
    // only when explicitly requested, and always solve complete leaf paths.
    const char* prefixCheck = std::getenv("EPPATHER_PREFIX_FEASIBILITY");
    if (!prefixCheck || !*prefixCheck || std::string(prefixCheck) == "0") {
        return true;
    }
    auto it = feasCache.find(fullExpr);
    if (it != feasCache.end()) return it->second;

    bool ok = feasibleWithVartemp(self, decisions, fullExpr.substr(self->vartemp.size()));
    feasCache.emplace(fullExpr, ok);
    return ok;
}
}  // namespace C
}  // namespace psy

// ========== 核心：与新 CFG 对齐的 DP ==========
// 说明：依赖以下已存在成员/类型：
// - struct PathInfo { int mems; std::string path; bool feasible; ... };
// - std::unordered_map<std::tuple<CFGNode*, std::string, std::string>, PathInfo> dpMemo;
// - std::string LoopMapKey(const std::unordered_map<CFGNode*, int>&);
// - bool feasibleWithVartemp(SyntaxNamePrinter*, const std::string&);
// - bool isPathFeasible(const std::string&);
// - std::string vartemp;
// - CFGNode 的接口：isFuncDef/isVarDef/isIf/isLoop/isWhile/isFor/isReturn/cond_str/initstmt_str/expr_str
//                    getCode()/getMem(vartemp)/getNextNode()/getNextFalseNode()

static std::unordered_map<std::string, int> decisionMemCache;

static int decisionMemCached(SyntaxNamePrinter* self,
                             CFGNode* node,
                             PathDecisionKind kind) {
    if (!node) return 0;
    const std::string key =
        std::to_string(reinterpret_cast<std::uintptr_t>(node)) + ":" +
        std::to_string(static_cast<int>(kind)) + ":" +
        std::to_string(std::hash<std::string>{}(self->vartemp));
    auto it = decisionMemCache.find(key);
    if (it != decisionMemCache.end()) return it->second;

    EpatRunner runner(self->vartemp);
    std::vector<PathDecision> one{
        PathDecision{node, kind}
    };
    const auto eval = runner.solve(one);
    const int mem = std::max(0, eval.mem);
    decisionMemCache.emplace(key, mem);
    return mem;
}


PathInfo SyntaxNamePrinter::MaxMemsDP(
    const std::shared_ptr<CFGNode>& entry,
    int maxloop,
    std::string pathPrefix,
    int depth,
    std::unordered_map<CFGNode*, int>& loopUnrollMap,
    std::vector<PathDecision> decisions
) {
    if (depth > 1000) return PathInfo(0, pathPrefix, false);
    if (!entry)        return PathInfo(0, pathPrefix, true);

    // Match DFS2's lexical-loop backtracking before constructing the DP key.
    // A deeper loop is a fresh dynamic invocation after an enclosing loop
    // starts another iteration.
    if (entry->isLoop) {
        for (auto& [loopNode, count] : loopUnrollMap) {
            if (loopNode && loopNode != entry.get() &&
                loopNode->depth > entry->depth) {
                count = 0;
            }
        }
    }

    const auto stateKey = std::make_tuple(
        entry.get(), LoopMapKey(loopUnrollMap), pathPrefix);
    if (auto it = dpMemo.find(stateKey); it != dpMemo.end()) {
        return it->second;
    }
    auto store = [&](PathInfo result) {
        dpMemo[stateKey] = result;
        return result;
    };
    // Because the memo key includes the complete path prefix, each leaf is
    // path-specific. Rank candidates with the exact EpatRunner MEMS of the
    // complete feasible decision sequence instead of summing context-free
    // per-decision estimates.
    // A complete leaf is the semantic scoring boundary. EpatRunner already
    // returns both feasibility and MEMS for the whole decision sequence, so
    // keep that exact value as the DP objective. This makes DP ranking use the
    // same complete-path MEMS semantics as DFS2.
    if (entry->isReturn || !(entry->getNextNode())) {
        std::string curPath = pathPrefix;
        auto curDecisions = decisions;
        if (!entry->isLoop && !entry->isIf && !entry->isFuncDef &&
            !(entry->isVarDef && entry->nodeLevel == 3)) {
            const std::string code = entry->getCode();
            if (!code.empty()) {
                curPath += code + "\n";
                curDecisions.push_back(
                    PathDecision{entry.get(), PathDecisionKind::Code});
            }
        }
        EpatRunner runner(vartemp);
        const auto eval = runner.solve(curDecisions);
        if (eval.status != result::feasible) {
            return store(PathInfo(0, curPath, false));
        }
        return store(PathInfo(std::max(0, eval.mem), curPath, true));
    }

    // Function-definition and level-3 local-definition nodes are not rendered
    // by DFS2 and therefore contribute no path MEMS decision here.
    if (entry->isFuncDef ||
        (entry->isVarDef && entry->nodeLevel == 3)) {
        auto child = MaxMemsDP(entry->getNextNode(), maxloop, pathPrefix,
                               depth + 1, loopUnrollMap, decisions);
        return store(child);
    }

    if (entry->isIf) {
        std::string curPath = pathPrefix;

        auto tLoopMap = loopUnrollMap;
        std::string tPath = curPath + "@(" + entry->cond_str + ");\n";
        auto tDecisions = decisions;
        tDecisions.push_back(
            PathDecision{entry.get(), PathDecisionKind::TrueBranch});
        PathInfo tInfo(0, tPath, false);
        if (entry->getNextNode() &&
            isPathFeasibleCached(this, tDecisions, vartemp + tPath)) {
            tInfo = MaxMemsDP(entry->getNextNode(), maxloop, tPath,
                              depth + 1, tLoopMap, tDecisions);
        }

        auto fLoopMap = loopUnrollMap;
        std::string fPath =
            curPath + "@(!(" + entry->cond_str + "));\n";
        auto fDecisions = decisions;
        fDecisions.push_back(
            PathDecision{entry.get(), PathDecisionKind::FalseBranch});
        PathInfo fInfo(0, fPath, false);
        if (entry->getNextFalseNode() &&
            isPathFeasibleCached(this, fDecisions, vartemp + fPath)) {
            fInfo = MaxMemsDP(entry->getNextFalseNode(), maxloop, fPath,
                              depth + 1, fLoopMap, fDecisions);
        }

        if (!tInfo.feasible && !fInfo.feasible)
            return store(PathInfo(0, curPath, false));
        return store(
            (tInfo.feasible &&
             (!fInfo.feasible || tInfo.mems >= fInfo.mems))
                ? tInfo : fInfo);
    }

    if (entry->isLoop) {
        const int unroll = loopUnrollMap[entry.get()];
        const int bound = predictedLoopBound(entry.get(), maxloop);
        std::string curPath = pathPrefix;
        auto curDecisions = decisions;

        if (entry->isFor) {
            if (unroll == 0 && !entry->initstmt_str.empty() &&
                entry->initstmt_str != ";") {
                curPath += entry->initstmt_str + "\n";
                curDecisions.push_back(
                    PathDecision{entry.get(), PathDecisionKind::LoopInit});
                if (!isPathFeasibleCached(
                        this, curDecisions, vartemp + curPath)) {
                    return store(PathInfo(0, curPath, false));
                }
            }
            if (unroll > 0 && !entry->expr_str.empty()) {
                curPath += entry->expr_str + ";\n";
                curDecisions.push_back(
                    PathDecision{entry.get(), PathDecisionKind::LoopUpdate});
                if (!isPathFeasibleCached(
                        this, curDecisions, vartemp + curPath)) {
                    return store(PathInfo(0, curPath, false));
                }
            }
        }

        PathInfo tInfo(0, curPath, false);
        PathInfo fInfo(0, curPath, false);

        if (unroll < bound && entry->getNextNode()) {
            std::string tPath =
                curPath + "@(" + entry->cond_str + ");\n";
            auto tDecisions = curDecisions;
            tDecisions.push_back(
                PathDecision{entry.get(), PathDecisionKind::TrueBranch});
            if (isPathFeasibleCached(
                    this, tDecisions, vartemp + tPath)) {
                auto tLoopMap = loopUnrollMap;
                tLoopMap[entry.get()] = unroll + 1;
                tInfo = MaxMemsDP(entry->getNextNode(), maxloop, tPath,
                                  depth + 1, tLoopMap, tDecisions);
            }
        }

        if (entry->getNextFalseNode()) {
            std::string fPath =
                curPath + "@(!(" + entry->cond_str + "));\n";
            auto fDecisions = curDecisions;
            fDecisions.push_back(
                PathDecision{entry.get(), PathDecisionKind::FalseBranch});
            if (isPathFeasibleCached(
                    this, fDecisions, vartemp + fPath)) {
                auto fLoopMap = loopUnrollMap;
                fInfo = MaxMemsDP(entry->getNextFalseNode(), maxloop, fPath,
                                  depth + 1, fLoopMap, fDecisions);
            }
        }

        if (!tInfo.feasible && !fInfo.feasible)
            return store(PathInfo(0, curPath, false));
        return store(
            (tInfo.feasible &&
             (!fInfo.feasible || tInfo.mems >= fInfo.mems))
                ? tInfo : fInfo);
    }

    // Ordinary sequential code node.
    std::string curPath = pathPrefix;
    auto nextDecisions = decisions;
    const std::string code = entry->getCode();
    if (!code.empty()) {
        curPath += code + "\n";
        nextDecisions.push_back(
            PathDecision{entry.get(), PathDecisionKind::Code});
    }
    if (!isPathFeasibleCached(
            this, nextDecisions, vartemp + curPath)) {
        return store(PathInfo(0, curPath, false));
    }
    auto child = MaxMemsDP(entry->getNextNode(), maxloop, curPath,
                           depth + 1, loopUnrollMap, nextDecisions);
    if (!child.feasible)
        return store(PathInfo(0, curPath, false));
    return store(child);
}


// ========== 驱动：与 DFS2 保持同样的 maxloop 和输出 ==========
// 改动：无可行路径时输出 "MEMS: -1"
void SyntaxNamePrinter::printCFG_greedyDFS(int maxloop, int maxpaths, bool enableVolce) {
    for (size_t funcIndex = 0; funcIndex < funcDefStack_.size(); ++funcIndex) {
        const auto& funcNode = funcDefStack_[funcIndex];
        const std::string functionTag = sanitizeFunctionTag(
            funcNode->functionName.empty() ? ("func_" + std::to_string(funcIndex)) : funcNode->functionName);
        dpMemo.clear();  // 每个函数入口前清空 memo
        decisionMemCache.clear();
        feasCache.clear();

        std::unordered_map<CFGNode*, int> loopUnrollMap;

        auto start = std::chrono::high_resolution_clock::now();
        PathInfo result = MaxMemsDP(funcNode, maxloop, "", 0, loopUnrollMap, {}); // raw path
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - start;

        std::cout << "[FUNCTION TAG]: " << functionTag << std::endl;
        std::cout << "[MAX MEMS PATH]:\n";
        const std::string fullPath = vartemp + result.path; // 只在这里拼接一次
        if (!result.feasible) {
            // 按要求：没有可行路径也输出 MEMS=-1
            // 如需查看组合出的路径，可取消下一行注释
            // std::cout << fullPath << "\n";
            std::cout << "MEMS: -1" << std::endl;
            std::cout << "[VolCE] N/A" << std::endl;
        } else {
            std::cout << fullPath << std::endl;
            // The DP score is already accumulated from the exact PathDecision
            // sequence (LoopInit/guard/LoopUpdate/Code).  A second whole-script
            // solve is useful as a diagnostic, but it is not required to select
            // or report the MaxMEMS witness and some unsupported expressions can
            // crash that optional post-processing path.  Keep the core MaxMEMS
            // result independent from the diagnostic verifier.
            int reportedMems = result.mems;
            bool verified = false;
            const char* coreOnlyRaw =
                std::getenv("EPPATHER_MAXMEMS_CORE_ONLY");
            const bool coreOnly =
                coreOnlyRaw && *coreOnlyRaw &&
                std::string(coreOnlyRaw) != "0";
            const char* verifyRaw =
                std::getenv("EPPATHER_VERIFY_SELECTED_PATH");
            const bool verifySelected =
                !coreOnly && verifyRaw && *verifyRaw &&
                std::string(verifyRaw) != "0";
            if (verifySelected) {
                const auto verifiedEval =
                    EpatRunner("").solveScript(fullPath);
                if (verifiedEval.status == result::feasible) {
                    reportedMems = verifiedEval.mem;
                    verified = true;
                }
            }
            std::cout << "[DP INTERNAL MEMS]: " << result.mems << std::endl;
            if (verified) {
                std::cout << "[DP SCORE DELTA]: "
                          << (reportedMems - result.mems) << std::endl;
            } else {
                std::cout << "[DP SCORE DELTA]: N/A" << std::endl;
            }
            std::cout << "MEMS: " << reportedMems << std::endl;

            // VolCE is orthogonal to the MaxMEMS validation corpus.  In
            // core-only mode skip it as well, so an optional model-counting
            // post-pass cannot turn a completed MaxMEMS analysis into a crash.
            if (enableVolce && !coreOnly) {
                const auto eval = EpatRunner("").solveScript(fullPath);
                const auto volceResult = runVolce(
                    eval.smt, -8, 8, {}, inputMemoryRegions_);
                if (volceResult) {
                    std::cout << "[VolCE]" << std::endl;
                    std::cout << volceResult->output << std::endl;
                } else {
                    std::cout << "[VolCE] N/A" << std::endl;
                }
            } else {
                std::cout << "[VolCE] N/A" << std::endl;
            }
        }
        std::cout << "[DP TIME COST]: " << diff.count() << " seconds" << std::endl;
    }
}




// 贪心+剪枝 DFS（只走可行路径，分支贪心选mems最大，循环最大展开）
void SyntaxNamePrinter::GreedyDFS(
    std::shared_ptr<CFGNode> node,
    std::vector<bool>& pathCoverage,
    std::vector<PathDecision> decisions,
    int depth,
    int& pathCount,
    int maxloop,
    int maxpaths,
    int currentMem,
    std::string& bestPath,
    int& bestMem)
{
    if (!node || (maxpaths > 0 && pathCount >= maxpaths)) return;
    if (node->depth >= 0 && node->depth < static_cast<int>(pathCoverage.size())) pathCoverage[node->depth] = true;
    currentMem += node->getMem(vartemp);

    auto leafEval = [&](bool includeCode) {
        bool pushed = false;
        if (includeCode && !node->isLoop && !node->isIf && !node->isFuncDef && !(node->isVarDef && node->nodeLevel == 3)) {
            decisions.push_back(PathDecision{node.get(), PathDecisionKind::Code});
            pushed = true;
        }
        EpatRunner runner(vartemp);
        auto eval = runner.solve(decisions);
        if (eval.status == result::feasible && currentMem > bestMem) {
            bestMem = currentMem;
            bestPath = runner.render(decisions);
            processPathResult(eval, bestPath, pathCoverage, pathCount, depth);
        }
        ++pathCount;
        if (pushed) decisions.pop_back();
    };

    // 终结节点
    if (node->isReturn || !node->getNextNode()) {
        leafEval(true);
        return;
    }

    // If分支
    if (node->isIf) {
        auto temp_pathcoverage = pathCoverage;
        if (depth >= static_cast<int>(temp_loopCount.size())) {
            temp_loopCount.resize(static_cast<size_t>(depth + 1));
        }
        temp_loopCount[depth] = loopCount;

        decisions.push_back(PathDecision{node.get(), PathDecisionKind::TrueBranch});
        GreedyDFS(node->getNextNode(), pathCoverage, decisions, depth + 1, pathCount, maxloop, maxpaths, currentMem, bestPath, bestMem);
        decisions.pop_back();

        for (int i = node->depth + 1; i < maxdepth; i++)
            pathCoverage[i] = false;
        pathCoverage = temp_pathcoverage;
        if (depth >= 0 && depth < static_cast<int>(temp_loopCount.size())) {
            loopCount = temp_loopCount[depth];
        }
        decisions.push_back(PathDecision{node.get(), PathDecisionKind::FalseBranch});
        GreedyDFS(node->getNextFalseNode(), pathCoverage, decisions, depth + 1, pathCount, maxloop, maxpaths, currentMem, bestPath, bestMem);
        decisions.pop_back();
        return;
    }

    // Loop循环
    else if (node->isLoop) {
        if (node->isFor) {
            if (node->depth + 1 >= 0 && node->depth + 1 < static_cast<int>(pathCoverage.size())) {
                pathCoverage[node->depth + 1] = true;
            }
            if (node->depth < 0 || node->depth >= static_cast<int>(loopCount.size())) return;
            if (node->depth < 0 || node->depth >= static_cast<int>(loopCount.size())) return;
            if (loopCount[node->depth] >= predictedLoopBound(node.get(), maxloop)) {
                decisions.push_back(PathDecision{node.get(), PathDecisionKind::FalseBranch});
                loopCount[node->depth] = 0;
                auto falseNode = node->getNextFalseNode();
                auto afterFalse = falseNode ? falseNode->getNextNode() : nullptr;
                GreedyDFS(afterFalse, pathCoverage, decisions, depth + 1, pathCount, maxloop, maxpaths, currentMem, bestPath, bestMem);
                decisions.pop_back();
            } else {
                if (node->depth < 0 || node->depth >= static_cast<int>(loopCount.size())) return;
            if (loopCount[node->depth] == 0 && node->initstmt_str != ";") {
                    decisions.push_back(PathDecision{node.get(), PathDecisionKind::LoopInit});
                }
                decisions.push_back(PathDecision{node.get(), PathDecisionKind::TrueBranch});
                if (!node->expr_str.empty()) decisions.push_back(PathDecision{node.get(), PathDecisionKind::LoopUpdate});
                auto epatDecisions = decisions;
                loopCount[node->depth]++;
                auto loopBody = node->getNextNode();
                auto loopBodyNext = loopBody ? loopBody->getNextNode() : nullptr;
                GreedyDFS(loopBodyNext, pathCoverage, epatDecisions, depth + 1, pathCount, maxloop, maxpaths, currentMem, bestPath, bestMem);
                if (!node->expr_str.empty()) decisions.pop_back();
                decisions.pop_back();
                if (loopCount[node->depth] == 1 && node->initstmt_str != ";") decisions.pop_back();
            }
            return;
        } else if (node->isWhile) {
            if (node->depth < 0 || node->depth >= static_cast<int>(loopCount.size())) return;
            if (node->depth < 0 || node->depth >= static_cast<int>(loopCount.size())) return;
            if (loopCount[node->depth] >= predictedLoopBound(node.get(), maxloop)) {
                decisions.push_back(PathDecision{node.get(), PathDecisionKind::FalseBranch});
                loopCount[node->depth] = 0;
                GreedyDFS(node->getNextFalseNode(), pathCoverage, decisions, depth + 1, pathCount, maxloop, maxpaths, currentMem, bestPath, bestMem);
                decisions.pop_back();
            } else {
                loopCount[node->depth]++;
                decisions.push_back(PathDecision{node.get(), PathDecisionKind::TrueBranch});
                GreedyDFS(node->getNextNode(), pathCoverage, decisions, depth + 1, pathCount, maxloop, maxpaths, currentMem, bestPath, bestMem);
                decisions.pop_back();
            }
            return;
        }
    }

    // 变量定义/函数定义节点：只递归，不加内容到path
    else if (node->isFuncDef || (node->isVarDef && node->nodeLevel == 3)) {
        GreedyDFS(node->getNextNode(), pathCoverage, decisions, depth + 1, pathCount, maxloop, maxpaths, currentMem, bestPath, bestMem);
        return;
    }

    // 其它普通节点：把内容加入path
    else {
        decisions.push_back(PathDecision{node.get(), PathDecisionKind::Code});
        GreedyDFS(node->getNextNode(), pathCoverage, decisions, depth + 1, pathCount, maxloop, maxpaths, currentMem, bestPath, bestMem);
        decisions.pop_back();
        return;
    }
}

// 估算指定分支或循环下最大mems（仅贪心用，不检查可行性！）
int SyntaxNamePrinter::EvaluateBranchMem(std::shared_ptr<CFGNode> node, int maxloop, int nodelevel) {
    emitCrashTrace("EvalBranch.enter", node, nodelevel);
    if (!node) return 0;
    if (node->isReturn || node->nodeLevel < nodelevel) return 0;
    int mem = node->getMem(vartemp);
    if (node->isLoop) {
        std::shared_ptr<CFGNode> loopBody = node->getNextNode();
        if (loopBody) {
            int loopBodyMem = EvaluateBranchMem(loopBody, maxloop, loopBody->nodeLevel);
            mem += loopBodyMem * maxloop;
        }
        std::shared_ptr<CFGNode> afterLoop = node->getNextFalseNode();
        if (afterLoop) {
            mem += EvaluateBranchMem(afterLoop, maxloop, afterLoop->nodeLevel);
        }
    } else if (node->isIf) {
        auto trueNode = node->getNextNode();
        auto falseNode = node->getNextFalseNode();
        int trueMem = trueNode ? EvaluateBranchMem(trueNode, maxloop, trueNode->nodeLevel) : std::numeric_limits<int>::min();
        int falseMem = falseNode ? EvaluateBranchMem(falseNode, maxloop, falseNode->nodeLevel) : std::numeric_limits<int>::min();
        mem += std::max(trueMem, falseMem);
    } else {
        std::shared_ptr<CFGNode> nextNode = node->getNextNode();
        if (nextNode) {
            mem += EvaluateBranchMem(nextNode, maxloop, nodelevel);
        }
    }
    return mem;
}


//包含剪枝的宽度优先搜索

void SyntaxNamePrinter::printCFG_BFS() {
    std::cout << "[INFO] BFS traversal is temporarily disabled for node-based epat integration." << std::endl;
}

void SyntaxNamePrinter::BFS(std::shared_ptr<CFGNode> /*startNode*/,
                            std::vector<bool>& /*pathCoverage*/,
                            std::vector<PathDecision> /*decisions*/,
                            int& /*pathCount*/) {
    // Intentionally left blank.
}

//输出结果用的函数

void SyntaxNamePrinter::processPathResult(const EpatResult& eval,
                                          const std::string& path,
                                          std::vector<bool>& pathCoverage,
                                          int pathCount,
                                          int depth) {

    std::string pathFileName = "path" + std::to_string(pathCount) + ".txt";
    std::string resultFileName = "result" + std::to_string(pathCount) + ".txt";
    std::string smtFileName = "smt" + std::to_string(pathCount) + ".txt";
    std::string matrixFileName = "matrix.txt";

    std::ofstream pathFile(pathFileName);
    std::ofstream resultFile(resultFileName);
    std::ofstream smtFile(smtFileName);
    std::ofstream matrixFile(matrixFileName, std::ios::app);

    // 写入路径
    pathFile << path;
    cout<<"Path:"<<path<<endl;

    const bool feasible = eval.status == result::feasible;
    resultFile << (feasible ? "feasible" : (eval.status == result::infeasible ? "infeasible" : "unknown")) << "\n";

    if (!feasible) {
        std::fill(pathCoverage.begin(), pathCoverage.end(), false);  // 将路径覆盖矩阵元素全部置为0
    }
    resultFile << (feasible ? "feasible" : "infeasible") << "\n";

    // 写入 SMT 表达式和内存使用情况
    const std::string& smt2 = eval.smt;
    const int mem = eval.mem;

    if (feasible)
    {
        cout<<"feasible!!!"<<endl;
        const std::string& model= eval.model;
        std::optional<std::uint64_t> volceCount;

        smtFile << smt2 << "\n";
        resultFile << "[testcase]:" << "\n" << model << "\n"
                   << "[mem]:" << mem << "\n";

        cout<<"[mem]:"<<mem<<endl;
        cout<<"[averagemem]:"<<mem/depth<<endl;
        cout<<"[testcase]:"<<endl<<model<<endl;

        // 写入覆盖矩阵
        for (bool covered : pathCoverage) {
            matrixFile << (covered ? "1" : "0") << " ";
        }
        matrixFile << "\n";

        // 关闭文件
        pathFile.close();
        resultFile.close();
        smtFile.close();
        matrixFile.close();

        // 将路径覆盖信息添加到总覆盖矩阵中
        allPathsCoverage.push_back(pathCoverage);        

    }
    else
    {
        cout<<"infeasible!!!"<<endl;

        smtFile << smt2 << "\n";
        resultFile <<"\n"<<"[mem]:" << mem << "\n";
        cout<<"[mem]:"<<mem<<endl;
        cout<<"[averagemem]:"<<mem/depth<<endl;

        // 写入覆盖矩阵
        for (size_t i = 0; i < pathCoverage.size(); ++i) {
            matrixFile << "0 ";
        }
        matrixFile << "\n";

    }


}

void SyntaxNamePrinter::processPathResult2(const EpatResult& eval,
                                          const std::string& path,
                                          std::vector<bool>& pathCoverage,
                                          int pathCount,
                                          int depth,
                                          const std::string& functionTag,
                                          bool enableVolce,
                                          int volceLower,
                                          int volceUpper,
                                          const std::vector<std::string>& callees) {
    static int globalPathId = 0;

    std::string pathFileName = "path_" + functionTag + "_" + std::to_string(pathCount) + ".txt";
    std::string resultFileName = "result_" + functionTag + "_" + std::to_string(pathCount) + ".txt";
    std::string smtFileName = "smt_" + functionTag + "_" + std::to_string(pathCount) + ".txt";
    std::string matrixFileName = "matrix2.txt";

    std::ofstream pathFile(pathFileName);
    std::ofstream resultFile(resultFileName);
    std::ofstream smtFile(smtFileName);
    std::ofstream matrixFile(matrixFileName, std::ios::app);

    // 写入路径
    pathFile << path;
    cout<<"Path:"<<path<<endl;

    const bool feasible = eval.status == result::feasible;
    resultFile << "[function_tag]:" << functionTag << "\n";
    resultFile << "[global_path_id]:" << globalPathId << "\n";
    resultFile << (feasible ? "feasible" : (eval.status == result::infeasible ? "infeasible" : "unknown")) << "\n";

    if (!feasible)
    {
         std::fill(pathCoverage.begin(), pathCoverage.end(), false);  // 将路径覆盖矩阵元素全部置为0
    }
    resultFile << (feasible ? "feasible" : "infeasible") << "\n";

    // 写入 SMT 表达式和内存使用情况
    const std::string& smt2 = eval.smt;
    const int mem = eval.mem;

    if (feasible)
    {
        cout<<"feasible!!!"<<endl;
        const std::string& model= eval.model;
        std::optional<std::uint64_t> volceCount;
        std::optional<std::size_t> volceMemoryTerms;

        smtFile << smt2 << "\n";
        resultFile << "[testcase]:" << "\n" << model << "\n"
                   << "[mem]:" << mem << "\n";

        cout<<"[mem]:"<<mem<<endl;
        cout<<"[averagemem]:"<<mem/depth<<endl;
        cout<<"[testcase]:"<<endl<<model<<endl;
        if (enableVolce) {
            cout << "[VolCE range]: [" << volceLower << ", " << volceUpper << "]" << endl;
            const auto volceResult = runVolce(
                smt2, volceLower, volceUpper, eval.loopStateSummaries,
                inputMemoryRegions_, eval.loopSccAffineStateSummaries,
                eval.loopSccMemoryCellStateSummaries,
                eval.loopSccCoupledAffineStateSummaries);
            if (volceResult) {
                volceCount = parseVolceCount(volceResult);
                volceMemoryTerms = volceResult->boundedMemoryTerms;
                resultFile << "[volce]:" << volceResult->output << "\n";
                cout << "[VolCE]" << endl;
                cout << volceResult->output << endl;
                cout << "[VOLCE BOUNDED MEMORY TERMS]: "
                     << volceResult->boundedMemoryTerms << endl;
                cout << "[VOLCE CANONICAL MEMORY REGIONS]: "
                     << volceResult->canonicalMemoryRegions << endl;
                resultFile << "[volce_canonical_memory_regions]:"
                           << volceResult->canonicalMemoryRegions << "\n";
                resultFile << "[volce_bounded_memory_terms]:"
                           << volceResult->boundedMemoryTerms << "\n";
                cout << "[VOLCE LOOP SUMMARIES APPLIED]: "
                     << volceResult->appliedStateSummaries.size() << endl;
                // Applied summaries are, by construction, summaries
                // entailed by a concrete SMT declaration.  Keep an explicit
                // SSA metric separate from ground validation for experiments.
                cout << "[VOLCE SSA SUMMARIES APPLIED]: "
                     << volceResult->appliedStateSummaries.size() << endl;
                cout << "[VOLCE LOOP SUMMARIES GROUND-VALIDATED]: "
                     << volceResult->validatedGroundStateSummaries.size() << endl;
                cout << "[VOLCE LOOP SUMMARIES REJECTED]: "
                     << volceResult->rejectedStateSummaries.size() << endl;
                cout << "[VOLCE LOOPSCC AFFINE RELATIONS APPLIED]: "
                     << volceResult->appliedAffineRelationSummaries.size()
                     << endl;
                cout << "[VOLCE LOOPSCC AFFINE RELATIONS REJECTED]: "
                     << volceResult->rejectedAffineRelationSummaries.size()
                     << endl;
                cout << "[VOLCE LOOPSCC COUPLED ROWS REQUIRED]: "
                     << volceResult->requiredCoupledAffineRows << endl;
                cout << "[VOLCE LOOPSCC COUPLED ROWS APPLIED]: "
                     << volceResult->appliedCoupledAffineRowsCount << endl;
                cout << "[VOLCE LOOPSCC COUPLED ROWS REJECTED]: "
                     << volceResult->rejectedCoupledAffineRows.size()
                     << endl;
                cout << "[VOLCE LOOPSCC COUPLED ALL ENTAILED]: "
                     << (volceResult->allCoupledAffineRowsEntailed ? 1 : 0)
                     << endl;
                cout << "[VOLCE LOOPSCC COUPLED OVERFLOW ROWS REQUIRED]: "
                     << volceResult->requiredCoupledOverflowRows << endl;
                cout << "[VOLCE LOOPSCC COUPLED OVERFLOW ROWS CERTIFIED]: "
                     << volceResult->certifiedCoupledOverflowRowsCount << endl;
                cout << "[VOLCE LOOPSCC COUPLED OVERFLOW ROWS REJECTED]: "
                     << volceResult->rejectedCoupledOverflowRows.size()
                     << endl;
                cout << "[VOLCE LOOPSCC COUPLED OVERFLOW ALL SAFE]: "
                     << (volceResult->allCoupledOverflowRowsSafe ? 1 : 0)
                     << endl;
                cout << "[VOLCE LOOPSCC MEMORY RELATIONS APPLIED]: "
                     << volceResult->appliedMemoryRelationSummaries.size()
                     << endl;
                cout << "[VOLCE LOOPSCC MEMORY RELATIONS REJECTED]: "
                     << volceResult->rejectedMemoryRelationSummaries.size()
                     << endl;
                cout << "[VOLCE LOOPSCC MEMORY FRAMES APPLIED]: "
                     << volceResult->appliedMemoryFrameSummaries.size()
                     << endl;
                cout << "[VOLCE LOOPSCC MEMORY FRAMES REJECTED]: "
                     << volceResult->rejectedMemoryFrameSummaries.size()
                     << endl;
                cout << "[VOLCE FORMULA ASSERTIONS]: "
                     << volceResult->formulaAssertions << endl;
                cout << "[VOLCE SMT DECLARATIONS]: "
                     << volceResult->smtDeclarations << endl;
                cout << "[VOLCE PROJECTION TERMS]: "
                     << volceResult->projectionTerms << endl;
                cout << "[VOLCE COUNTING ASSERTIONS]: "
                     << volceResult->countingAssertions << endl;
                cout << "[VOLCE FACTORED PROJECTION COMPONENTS]: "
                     << volceResult->factoredProjectionComponents << endl;
                cout << "[VOLCE SOLVER WARMUP US]: "
                     << volceResult->solverWarmupMicroseconds << endl;
                cout << "[VOLCE SUMMARY CHECK US]: "
                     << volceResult->summaryCheckMicroseconds << endl;
                cout << "[VOLCE MODEL COUNT US]: "
                     << volceResult->modelCountMicroseconds << endl;
                resultFile << "[volce_loop_summaries_applied]:"
                           << volceResult->appliedStateSummaries.size() << "\n";
                resultFile << "[volce_ssa_summaries_applied]:"
                           << volceResult->appliedStateSummaries.size() << "\n";
                for (const auto& applied : volceResult->appliedStateSummaries) {
                    resultFile << "[volce_loop_summary]:" << applied << "\n";
                }
                for (const auto& validated :
                     volceResult->validatedGroundStateSummaries) {
                    resultFile << "[volce_loop_summary_ground_validated]:"
                               << validated << "\n";
                }
                for (const auto& rejected :
                     volceResult->rejectedStateSummaries) {
                    resultFile << "[volce_loop_summary_rejected]:"
                               << rejected << "\n";
                    cout << "[VOLCE LOOP SUMMARY REJECTED]: "
                         << rejected << endl;
                }
                for (const auto& applied :
                     volceResult->appliedAffineRelationSummaries) {
                    resultFile << "[volce_loopscc_affine_relation]:"
                               << applied << "\n";
                    cout << "[VOLCE LOOPSCC AFFINE RELATION]: "
                         << applied << endl;
                }
                for (const auto& rejected :
                     volceResult->rejectedAffineRelationSummaries) {
                    resultFile << "[volce_loopscc_affine_relation_rejected]:"
                               << rejected << "\n";
                    cout << "[VOLCE LOOPSCC AFFINE RELATION REJECTED]: "
                         << rejected << endl;
                }
                for (const auto& applied :
                     volceResult->appliedCoupledAffineRows) {
                    resultFile << "[volce_loopscc_coupled_row]:"
                               << applied << "\n";
                    cout << "[VOLCE LOOPSCC COUPLED ROW]: "
                         << applied << endl;
                }
                for (const auto& rejected :
                     volceResult->rejectedCoupledAffineRows) {
                    resultFile << "[volce_loopscc_coupled_row_rejected]:"
                               << rejected << "\n";
                    cout << "[VOLCE LOOPSCC COUPLED ROW REJECTED]: "
                         << rejected << endl;
                }
                for (const auto& certified :
                     volceResult->certifiedCoupledOverflowRows) {
                    resultFile << "[volce_loopscc_coupled_overflow_safe]:"
                               << certified << "\n";
                    cout << "[VOLCE LOOPSCC COUPLED OVERFLOW SAFE]: "
                         << certified << endl;
                }
                for (const auto& rejected :
                     volceResult->rejectedCoupledOverflowRows) {
                    resultFile << "[volce_loopscc_coupled_overflow_rejected]:"
                               << rejected << "\n";
                    cout << "[VOLCE LOOPSCC COUPLED OVERFLOW REJECTED]: "
                         << rejected << endl;
                }
                for (const auto& applied :
                     volceResult->appliedMemoryRelationSummaries) {
                    resultFile << "[volce_loopscc_memory_relation]:"
                               << applied << "\n";
                    cout << "[VOLCE LOOPSCC MEMORY RELATION]: "
                         << applied << endl;
                }
                for (const auto& rejected :
                     volceResult->rejectedMemoryRelationSummaries) {
                    resultFile << "[volce_loopscc_memory_relation_rejected]:"
                               << rejected << "\n";
                    cout << "[VOLCE LOOPSCC MEMORY RELATION REJECTED]: "
                         << rejected << endl;
                }
                for (const auto& applied :
                     volceResult->appliedMemoryFrameSummaries) {
                    resultFile << "[volce_loopscc_memory_frame]:"
                               << applied << "\n";
                    cout << "[VOLCE LOOPSCC MEMORY FRAME]: "
                         << applied << endl;
                }
                for (const auto& rejected :
                     volceResult->rejectedMemoryFrameSummaries) {
                    resultFile << "[volce_loopscc_memory_frame_rejected]:"
                               << rejected << "\n";
                    cout << "[VOLCE LOOPSCC MEMORY FRAME REJECTED]: "
                         << rejected << endl;
                }
                for (const auto& diagnostic :
                     eval.loopStateSummaryDiagnostics) {
                    resultFile << "[volce_loop_summary_diagnostic]:"
                               << diagnostic << "\n";
                    cout << "[VOLCE LOOP SUMMARY DIAGNOSTIC]: "
                         << diagnostic << endl;
                }

                // Validation-only compressed LoopSCC paths are counted over
                // the exact same finite input domain. Equal model count plus
                // equal MEMS proves equal per-path weighted-MEMS contribution.
                for (const auto& validation :
                     eval.loopSccAccelerationValidations) {
                    if (!validation.matched ||
                        validation.compressedSmt.empty()) {
                        continue;
                    }
                    const auto compressedVolce = runVolce(
                        validation.compressedSmt,
                        volceLower, volceUpper, {},
                        inputMemoryRegions_, {});
                    const auto compressedCount =
                        parseVolceCount(compressedVolce);
                    const bool countMatch =
                        volceCount && compressedCount &&
                        *volceCount == *compressedCount;
                    const bool weightedMatch =
                        countMatch && validation.memMatched;

                    cout << "[LOOPSCC COMPRESSED VOLCE]: baseline_count="
                         << (volceCount
                                 ? std::to_string(*volceCount)
                                 : "N/A")
                         << " compressed_count="
                         << (compressedCount
                                 ? std::to_string(*compressedCount)
                                 : "N/A")
                         << " count_match=" << (countMatch ? 1 : 0)
                         << " weighted_match="
                         << (weightedMatch ? 1 : 0)
                         << endl;
                    resultFile
                        << "[loopscc_compressed_volce_count_match]:"
                        << (countMatch ? 1 : 0) << "\n";
                    resultFile
                        << "[loopscc_compressed_weighted_match]:"
                        << (weightedMatch ? 1 : 0) << "\n";
                    if (compressedCount) {
                        resultFile
                            << "[loopscc_compressed_volce_count]:"
                            << *compressedCount << "\n";
                    }
                }
                for (const auto& validation :
                     eval.loopSccCoupledAffineValidations) {
                    if (!validation.matched ||
                        validation.compressedSmt.empty()) {
                        continue;
                    }
                    const auto compressedVolce = runVolce(
                        validation.compressedSmt,
                        volceLower, volceUpper, {},
                        inputMemoryRegions_, {});
                    const auto compressedCount =
                        parseVolceCount(compressedVolce);
                    const bool countMatch =
                        volceCount && compressedCount &&
                        *volceCount == *compressedCount;
                    const bool weightedMatch =
                        countMatch && validation.memMatched;

                    cout << "[LOOPSCC COUPLED COMPRESSED VOLCE]: baseline_count="
                         << (volceCount
                                 ? std::to_string(*volceCount)
                                 : "N/A")
                         << " compressed_count="
                         << (compressedCount
                                 ? std::to_string(*compressedCount)
                                 : "N/A")
                         << " count_match=" << (countMatch ? 1 : 0)
                         << " weighted_match="
                         << (weightedMatch ? 1 : 0)
                         << endl;
                    resultFile
                        << "[loopscc_coupled_compressed_volce_count_match]:"
                        << (countMatch ? 1 : 0) << "\n";
                    resultFile
                        << "[loopscc_coupled_compressed_weighted_match]:"
                        << (weightedMatch ? 1 : 0) << "\n";
                    if (compressedCount) {
                        resultFile
                            << "[loopscc_coupled_compressed_volce_count]:"
                            << *compressedCount << "\n";
                    }
                }
                for (const auto& validation :
                     eval.loopSccMemoryAccelerationValidations) {
                    if (!validation.matched ||
                        validation.compressedSmt.empty()) {
                        continue;
                    }
                    const auto compressedVolce = runVolce(
                        validation.compressedSmt,
                        volceLower, volceUpper, {},
                        inputMemoryRegions_, {}, {});
                    const auto compressedCount =
                        parseVolceCount(compressedVolce);
                    const bool countMatch =
                        volceCount && compressedCount &&
                        *volceCount == *compressedCount;
                    const bool weightedMatch =
                        countMatch &&
                        validation.compensatedMemMatched;

                    cout << "[LOOPSCC MEMORY COMPRESSED VOLCE]: baseline_count="
                         << (volceCount
                                 ? std::to_string(*volceCount)
                                 : "N/A")
                         << " compressed_count="
                         << (compressedCount
                                 ? std::to_string(*compressedCount)
                                 : "N/A")
                         << " count_match=" << (countMatch ? 1 : 0)
                         << " weighted_match="
                         << (weightedMatch ? 1 : 0)
                         << endl;
                    resultFile
                        << "[loopscc_memory_compressed_volce_count_match]:"
                        << (countMatch ? 1 : 0) << "\n";
                    resultFile
                        << "[loopscc_memory_compressed_weighted_match]:"
                        << (weightedMatch ? 1 : 0) << "\n";
                    if (compressedCount) {
                        resultFile
                            << "[loopscc_memory_compressed_volce_count]:"
                            << *compressedCount << "\n";
                    }
                }
            } else {
                resultFile << "[volce]: N/A\n";
                cout << "[VolCE] N/A" << endl;
            }
        }
        if (!eval.loopSccGraphs.empty()) {
            std::size_t spaths = 0;
            std::size_t transitions = 0;
            std::size_t sccs = 0;
            std::size_t cyclicSccs = 0;
            std::size_t multiNodeSccs = 0;
            std::size_t maxSccSize = 0;
            std::size_t csgEdges = 0;
            std::size_t determinateCycles = 0;
            std::size_t oscillatingCycles = 0;
            std::size_t closedFormCandidates = 0;
            std::size_t insideOutNestedSummaries = 0;
            std::size_t insideOutNestedMemorySummaries = 0;
            std::size_t memorySPaths = 0;
            std::size_t memoryWritingSPaths = 0;
            std::size_t impreciseMemorySPaths = 0;
            std::size_t observedMemoryMems = 0;
            std::size_t memoryCellTransitionCandidates = 0;
            std::size_t memorySummaryCandidates = 0;
            std::size_t accelerationPlans = 0;
            std::size_t exactAccelerationPlans = 0;
            std::size_t coupledAffineCandidates = 0;
            std::size_t maxPeriod = 0;
            long long maxProvedTripCount = -1;
            std::string provedTripVariable;
            bool complete = true;
            for (const auto& graph : eval.loopSccGraphs) {
                spaths += graph.spaths.size();
                transitions += graph.transitionCount;
                sccs += graph.sccCount;
                cyclicSccs += graph.cyclicSccCount;
                multiNodeSccs += graph.multiNodeSccCount;
                maxSccSize = std::max(maxSccSize, graph.maxSccSize);
                csgEdges += graph.contractedEdgeCount;
                determinateCycles += graph.determinateCycleCount;
                oscillatingCycles += graph.oscillatingCycleCount;
                closedFormCandidates += graph.guardedClosedFormCandidateCount;
                insideOutNestedSummaries +=
                    graph.insideOutNestedSummaryCount;
                insideOutNestedMemorySummaries +=
                    graph.insideOutNestedMemorySummaryCount;
                for (const auto& spath : graph.spaths) {
                    if (spath.observedMems > 0 ||
                        !spath.memoryAccesses.empty()) {
                        ++memorySPaths;
                        observedMemoryMems += spath.observedMems;
                    }
                    if (spath.writesMemory) ++memoryWritingSPaths;
                    if (!spath.memoryAccessModelComplete) {
                        ++impreciseMemorySPaths;
                    }
                    memoryCellTransitionCandidates +=
                        spath.memoryCellTransforms.size();
                }
                memorySummaryCandidates +=
                    graph.memorySummaryCandidates.size();
                accelerationPlans += graph.accelerationPlans.size();
                coupledAffineCandidates +=
                    graph.coupledAffineCandidates.size();
                for (const auto& candidate :
                     graph.coupledAffineCandidates) {
                    cout << "[LOOPSCC COUPLED AFFINE]: cycle="
                         << candidate.cycleIndex
                         << " entry_phase=" << candidate.entryPhase
                         << " iterations=" << candidate.totalIterations
                         << " period=" << candidate.period
                         << " variables=";
                    for (std::size_t i = 0;
                         i < candidate.closedForm.variables.size(); ++i) {
                        if (i != 0) cout << ",";
                        cout << candidate.closedForm.variables[i];
                    }
                    cout << " matrix=";
                    for (std::size_t i = 0;
                         i < candidate.closedForm.matrix.size(); ++i) {
                        if (i != 0) cout << ",";
                        cout << candidate.closedForm.matrix[i];
                    }
                    cout << " offset=";
                    for (std::size_t i = 0;
                         i < candidate.closedForm.offset.size(); ++i) {
                        if (i != 0) cout << ",";
                        cout << candidate.closedForm.offset[i];
                    }
                    cout << endl;
                }
                for (const auto& plan : graph.accelerationPlans) {
                    if (plan.exact) ++exactAccelerationPlans;
                    cout << "[LOOPSCC ACCELERATION PLAN]: cycle="
                         << plan.cycleIndex
                         << " entry_phase=" << plan.entryPhase
                         << " iterations=" << plan.totalIterations
                         << " period=" << plan.period
                         << " full_periods=" << plan.completePeriods
                         << " residual=" << plan.residualPhases
                         << " mems_preserving="
                         << (plan.memsPreserving ? 1 : 0)
                         << " skippable_iterations="
                         << plan.skippableIterations
                         << " exact=" << (plan.exact ? 1 : 0)
                         << endl;
                    for (const auto& transform :
                         plan.closedFormTransforms) {
                        cout << "[LOOPSCC ACCELERATION TRANSFORM]: "
                             << transform.variable
                             << " scale=" << transform.scale
                             << " offset=" << transform.offset
                             << endl;
                    }
                }
                if (graph.provedTripCount >= 0 &&
                    graph.provedTripCount > maxProvedTripCount) {
                    maxProvedTripCount = graph.provedTripCount;
                    provedTripVariable = graph.tripCountVariable;
                }
                for (const auto& cycle : graph.cycles) {
                    maxPeriod = std::max(maxPeriod, cycle.period);
                    if (cycle.determinate) {
                        cout << "[LOOPSCC CYCLE]: scc=" << cycle.sccId
                             << " period=" << cycle.period
                             << " phase_guards_proved="
                             << (cycle.phaseGuardsProved ? 1 : 0)
                             << " closed_form_candidate="
                             << (cycle.guardedClosedFormCandidate ? 1 : 0)
                             << endl;
                        for (const auto& relation : cycle.periodAffineUpdates) {
                            cout << "[LOOPSCC PERIOD TRANSFORM]: "
                                 << relation << endl;
                        }
                    }
                }
                complete = complete && graph.complete;
                for (const auto& diagnostic : graph.diagnostics) {
                    cout << "[LOOPSCC DIAGNOSTIC]: " << diagnostic << endl;
                    resultFile << "[loopscc_diagnostic]:" << diagnostic << "\n";
                }
            }
            cout << "[LOOPSCC SPATHS]: " << spaths << endl;
            cout << "[LOOPSCC TRANSITIONS]: " << transitions << endl;
            cout << "[LOOPSCC SCCS]: " << sccs << endl;
            cout << "[LOOPSCC CYCLIC SCCS]: " << cyclicSccs << endl;
            cout << "[LOOPSCC MULTI-NODE SCCS]: " << multiNodeSccs << endl;
            cout << "[LOOPSCC MAX SCC SIZE]: " << maxSccSize << endl;
            cout << "[LOOPSCC CSG EDGES]: " << csgEdges << endl;
            cout << "[LOOPSCC DETERMINATE CYCLES]: " << determinateCycles << endl;
            cout << "[LOOPSCC OSCILLATING CYCLES]: " << oscillatingCycles << endl;
            cout << "[LOOPSCC CLOSED FORM CANDIDATES]: "
                 << closedFormCandidates << endl;
            cout << "[LOOPSCC INSIDE OUT NESTED SUMMARIES]: "
                 << insideOutNestedSummaries << endl;
            cout << "[LOOPSCC INSIDE OUT NESTED MEMORY SUMMARIES]: "
                 << insideOutNestedMemorySummaries << endl;
            cout << "[LOOPSCC MEMORY SPATHS]: "
                 << memorySPaths << endl;
            cout << "[LOOPSCC MEMORY WRITING SPATHS]: "
                 << memoryWritingSPaths << endl;
            cout << "[LOOPSCC IMPRECISE MEMORY SPATHS]: "
                 << impreciseMemorySPaths << endl;
            cout << "[LOOPSCC OBSERVED MEMORY MEMS]: "
                 << observedMemoryMems << endl;
            cout << "[LOOPSCC MEMORY CELL TRANSITION CANDIDATES]: "
                 << memoryCellTransitionCandidates << endl;
            cout << "[LOOPSCC MEMORY SUMMARY CANDIDATES]: "
                 << memorySummaryCandidates << endl;
            cout << "[LOOPSCC ACCELERATION PLANS]: "
                 << accelerationPlans << endl;
            cout << "[LOOPSCC EXACT ACCELERATION PLANS]: "
                 << exactAccelerationPlans << endl;
            cout << "[LOOPSCC COUPLED AFFINE CANDIDATES]: "
                 << coupledAffineCandidates << endl;
            cout << "[LOOPSCC MAX PERIOD]: " << maxPeriod << endl;
            if (maxProvedTripCount >= 0) {
                cout << "[LOOPSCC PROVED TRIP COUNT]: "
                     << maxProvedTripCount << endl;
                cout << "[LOOPSCC TRIP COUNT VARIABLE]: "
                     << provedTripVariable << endl;
            }
            cout << "[LOOPSCC GRAPH COMPLETE]: " << (complete ? 1 : 0) << endl;
            resultFile << "[loopscc_spaths]:" << spaths << "\n";
            resultFile << "[loopscc_transitions]:" << transitions << "\n";
            resultFile << "[loopscc_sccs]:" << sccs << "\n";
            resultFile << "[loopscc_cyclic_sccs]:" << cyclicSccs << "\n";
            resultFile << "[loopscc_multi_node_sccs]:" << multiNodeSccs << "\n";
            resultFile << "[loopscc_max_scc_size]:" << maxSccSize << "\n";
            resultFile << "[loopscc_csg_edges]:" << csgEdges << "\n";
            resultFile << "[loopscc_determinate_cycles]:" << determinateCycles << "\n";
            resultFile << "[loopscc_oscillating_cycles]:" << oscillatingCycles << "\n";
            resultFile << "[loopscc_closed_form_candidates]:"
                       << closedFormCandidates << "\n";
            resultFile << "[loopscc_inside_out_nested_summaries]:"
                       << insideOutNestedSummaries << "\n";
            resultFile << "[loopscc_memory_spaths]:"
                       << memorySPaths << "\n";
            resultFile << "[loopscc_memory_writing_spaths]:"
                       << memoryWritingSPaths << "\n";
            resultFile << "[loopscc_imprecise_memory_spaths]:"
                       << impreciseMemorySPaths << "\n";
            resultFile << "[loopscc_observed_memory_mems]:"
                       << observedMemoryMems << "\n";
            resultFile << "[loopscc_memory_cell_transition_candidates]:"
                       << memoryCellTransitionCandidates << "\n";
            resultFile << "[loopscc_memory_summary_candidates]:"
                       << memorySummaryCandidates << "\n";
            resultFile << "[loopscc_acceleration_plans]:"
                       << accelerationPlans << "\n";
            resultFile << "[loopscc_exact_acceleration_plans]:"
                       << exactAccelerationPlans << "\n";
            resultFile << "[loopscc_max_period]:" << maxPeriod << "\n";
            if (maxProvedTripCount >= 0) {
                resultFile << "[loopscc_proved_trip_count]:"
                           << maxProvedTripCount << "\n";
                resultFile << "[loopscc_trip_count_variable]:"
                           << provedTripVariable << "\n";
            }
            resultFile << "[loopscc_graph_complete]:" << (complete ? 1 : 0)
                       << "\n";
        }
        for (const auto& trace : eval.loopSccPhaseTraces) {
            cout << "[LOOPSCC PHASE TRACE]: complete="
                 << (trace.complete ? 1 : 0)
                 << " matched=" << (trace.matchedDeterminateCycle ? 1 : 0)
                 << " period=" << trace.period
                 << " entry_phase=" << trace.entryPhase
                 << " iterations=" << trace.observedIterations
                 << " full_periods=" << trace.completePeriods
                 << " residual=" << trace.residualPhases
                 << endl;
            cout << "[LOOPSCC ACCELERATION TRACE]: matched="
                 << (trace.matchedAccelerationPlan ? 1 : 0)
                 << " plan=" << trace.accelerationPlanIndex
                 << endl;
            if (!trace.spathSequence.empty()) {
                cout << "[LOOPSCC PHASE SEQUENCE]:";
                for (std::size_t id : trace.spathSequence) {
                    cout << " " << id;
                }
                cout << endl;
            }
            for (const auto& diagnostic : trace.diagnostics) {
                cout << "[LOOPSCC PHASE DIAGNOSTIC]: "
                     << diagnostic << endl;
            }
            resultFile << "[loopscc_phase_complete]:"
                       << (trace.complete ? 1 : 0) << "\n";
            resultFile << "[loopscc_phase_matched]:"
                       << (trace.matchedDeterminateCycle ? 1 : 0) << "\n";
            resultFile << "[loopscc_phase_period]:" << trace.period << "\n";
            resultFile << "[loopscc_phase_entry]:" << trace.entryPhase << "\n";
            resultFile << "[loopscc_phase_iterations]:"
                       << trace.observedIterations << "\n";
            resultFile << "[loopscc_phase_full_periods]:"
                       << trace.completePeriods << "\n";
            resultFile << "[loopscc_phase_residual]:"
                       << trace.residualPhases << "\n";
            resultFile << "[loopscc_acceleration_trace_matched]:"
                       << (trace.matchedAccelerationPlan ? 1 : 0) << "\n";
        }

        for (const auto& validation :
             eval.loopSccAccelerationValidations) {
            cout << "[LOOPSCC COMPRESSED VALIDATION]: attempted="
                 << (validation.attempted ? 1 : 0)
                 << " matched=" << (validation.matched ? 1 : 0)
                 << " status_match="
                 << (validation.statusMatched ? 1 : 0)
                 << " mem_match="
                 << (validation.memMatched ? 1 : 0)
                 << " original_decisions="
                 << validation.originalDecisionCount
                 << " compressed_decisions="
                 << validation.compressedDecisionCount
                 << " baseline_mem=" << validation.baselineMem
                 << " compressed_mem=" << validation.compressedMem
                 << endl;
            resultFile << "[loopscc_compressed_validation_matched]:"
                       << (validation.matched ? 1 : 0) << "\n";
            resultFile << "[loopscc_compressed_original_decisions]:"
                       << validation.originalDecisionCount << "\n";
            resultFile << "[loopscc_compressed_decisions]:"
                       << validation.compressedDecisionCount << "\n";
            resultFile << "[loopscc_compressed_mem_match]:"
                       << (validation.memMatched ? 1 : 0) << "\n";
        }
        for (const auto& validation :
             eval.loopSccCoupledAffineValidations) {
            cout << "[LOOPSCC COUPLED COMPRESSED VALIDATION]: attempted="
                 << (validation.attempted ? 1 : 0)
                 << " matched=" << (validation.matched ? 1 : 0)
                 << " type_certified="
                 << (validation.typeCertified ? 1 : 0)
                 << " snapshot_parallel="
                 << (validation.snapshotParallelized ? 1 : 0)
                 << " entry_range="
                 << (validation.entryRangeCertified ? 1 : 0)
                 << " preexec_overflow="
                 << (validation.preexecutionOverflowCertified ? 1 : 0)
                 << " status_match="
                 << (validation.statusMatched ? 1 : 0)
                 << " mem_match="
                 << (validation.memMatched ? 1 : 0)
                 << " original_decisions="
                 << validation.originalDecisionCount
                 << " compressed_decisions="
                 << validation.compressedDecisionCount
                 << " baseline_mem=" << validation.baselineMem
                 << " compressed_mem=" << validation.compressedMem
                 << endl;
            resultFile
                << "[loopscc_coupled_compressed_validation_matched]:"
                << (validation.matched ? 1 : 0) << "\n";
            resultFile
                << "[loopscc_coupled_type_certified]:"
                << (validation.typeCertified ? 1 : 0) << "\n";
            resultFile
                << "[loopscc_coupled_snapshot_parallel]:"
                << (validation.snapshotParallelized ? 1 : 0) << "\n";
            resultFile
                << "[loopscc_coupled_entry_range_certified]:"
                << (validation.entryRangeCertified ? 1 : 0) << "\n";
            resultFile
                << "[loopscc_coupled_preexec_overflow_certified]:"
                << (validation.preexecutionOverflowCertified ? 1 : 0)
                << "\n";
            for (const auto& diagnostic :
                 validation.certificateDiagnostics) {
                cout << "[LOOPSCC COUPLED CERTIFICATE]: "
                     << diagnostic << endl;
                resultFile
                    << "[loopscc_coupled_certificate]:"
                    << diagnostic << "\n";
            }
        }
        for (const auto& validation :
             eval.loopSccMemoryAccelerationValidations) {
            cout << "[LOOPSCC MEMORY COMPRESSED VALIDATION]: attempted="
                 << (validation.attempted ? 1 : 0)
                 << " matched=" << (validation.matched ? 1 : 0)
                 << " status_match="
                 << (validation.statusMatched ? 1 : 0)
                 << " compensated_mem_match="
                 << (validation.compensatedMemMatched ? 1 : 0)
                 << " original_decisions="
                 << validation.originalDecisionCount
                 << " compressed_decisions="
                 << validation.compressedDecisionCount
                 << " unfolded_loop_mems="
                 << validation.unfoldedLoopMems
                 << " compressed_summary_mems="
                 << validation.compressedSummaryMems
                 << " baseline_mem=" << validation.baselineMem
                 << " compressed_mem=" << validation.compressedMem
                 << " compensated_mem="
                 << validation.compensatedMem
                 << endl;
            resultFile
                << "[loopscc_memory_compressed_validation_matched]:"
                << (validation.matched ? 1 : 0) << "\n";
            resultFile
                << "[loopscc_memory_compressed_status_match]:"
                << (validation.statusMatched ? 1 : 0) << "\n";
            resultFile
                << "[loopscc_memory_compressed_mem_match]:"
                << (validation.compensatedMemMatched ? 1 : 0)
                << "\n";
            resultFile
                << "[loopscc_memory_unfolded_loop_mems]:"
                << validation.unfoldedLoopMems << "\n";
            resultFile
                << "[loopscc_memory_compressed_summary_mems]:"
                << validation.compressedSummaryMems << "\n";
        }

        std::string coverageSignature;
        coverageSignature.reserve(pathCoverage.size());
        for (bool covered : pathCoverage) {
            coverageSignature.push_back(covered ? '1' : '0');
        }
        cout << "[COVERAGE SIGNATURE]: "
             << coverageSignature << endl;
        resultFile << "[coverage_signature]:"
                   << coverageSignature << "\n";

        recordFeasiblePath(
            pathCount, mem, path, callees, volceCount, volceMemoryTerms);

        // 写入覆盖矩阵
        for (bool covered : pathCoverage) {
            matrixFile << (covered ? "1" : "0") << " ";
        }
        matrixFile << "\n";

        // 关闭文件
        pathFile.close();
        resultFile.close();
        smtFile.close();
        matrixFile.close();

        // 将路径覆盖信息添加到总覆盖矩阵中
        allPathsCoverage.push_back(pathCoverage);        

    }

    else

    {
        cout<<"infeasible!!!"<<endl;

        smtFile << smt2 << "\n";
        resultFile <<"\n"<<"[mem]:" << mem << "\n";
        cout<<"[mem]:"<<mem<<endl;
        cout<<"[averagemem]:"<<mem/depth<<endl;

        // 写入覆盖矩阵
        for (size_t i = 0; i < pathCoverage.size(); ++i) {
            matrixFile << "0 ";
        }
        matrixFile << "\n";

    }

    ++globalPathId;
}

std::vector<std::vector<int>> SyntaxNamePrinter::ReadCoverageMatrix(const std::string& filename) {

    std::vector<std::vector<int>> coverageMatrix;

    std::ifstream file(filename);

    std::string line;

    while (std::getline(file, line)) {

        std::istringstream iss(line);

        std::vector<int> row;

        int value;

        while (iss >> value) {

            row.push_back(value);

        }

        coverageMatrix.push_back(row);

    }
    cout<<"[matrix_before]:"<<endl;
    for (const auto& row : coverageMatrix) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
    return coverageMatrix;

}



//这个部分改成了贪心算法，可以得出结果

void SyntaxNamePrinter::SolveLinearProgram(const std::vector<std::vector<int>>& coverageMatrix) {
    if (coverageMatrix.empty() || coverageMatrix.front().empty()) {
        std::cout << "[COVERAGE MATRIX]: empty; no feasible paths to optimize" << std::endl;
        return;
    }
    int numStatements = coverageMatrix[0].size();
    int numPaths = coverageMatrix.size();
    std::vector<bool> isStatementCovered(numStatements, false);

    std::ofstream outputFile("final.txt");  // 创建文件输出流
    for (int i = 0; i < numPaths; ++i) {
        for (int j = 0; j < numStatements; ++j) {
            if (coverageMatrix[i][j] == 1) {
                isStatementCovered[j] = true;
            }
        }
    }

    std::vector<int> validStatements;
    for (int i = 0; i < numStatements; ++i) {
        if (isStatementCovered[i]) {
            validStatements.push_back(i);
        }
    }

    std::vector<bool> pathSelected(numPaths, false);
    std::set<int> uncoveredStatements(validStatements.begin(), validStatements.end());
    int pathCount = 0;

    while (!uncoveredStatements.empty()) {
        int maxCover = 0;
        int bestPath = -1;

        for (int i = 0; i < numPaths; ++i) {
            if (!pathSelected[i]) {
                int cover = 0;
                for (int j : uncoveredStatements) {
                    if (coverageMatrix[i][j] == 1) {
                        cover++;
                    }
                }
                if (cover > maxCover) {
                    maxCover = cover;
                    bestPath = i;
                }
            }
        }

        if (bestPath != -1) {
            pathSelected[bestPath] = true;
            pathCount++;
            for (int j = 0; j < numStatements; ++j) {
                if (coverageMatrix[bestPath][j] == 1) {
                    uncoveredStatements.erase(j);
                }
            }

            //std::cout << "Path " << bestPath + 1 << " selected." << std::endl;
            outputFile << "Path " << bestPath + 1 << " selected." << std::endl;

            // Read and display the corresponding result file content
            std::string resultFileName = "result" + std::to_string(pathCount-1) + ".txt";
            std::ifstream resultFile(resultFileName);
            if (resultFile.is_open()) {
                std::stringstream buffer;
                buffer << resultFile.rdbuf();
                //std::cout << "Contents of " << resultFileName << ":" << std::endl;
                outputFile<< "Contents of " << resultFileName << ":" << std::endl;
                //std::cout << buffer.str() << std::endl;
                outputFile<< buffer.str() << std::endl;
                resultFile.close();
            } else {
                //std::cout << "Failed to open " << resultFileName << std::endl;
                outputFile << "Failed to open " << resultFileName << std::endl;
            }
        }
    }
    outputFile.close();  // 关闭文件流
}
