// Wrapper helpers for invoking epat++ with CFG-aware paths.
#pragma once

#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "solver.h"
#include "LoopSccAdapter.h"

namespace psy {
namespace C {

class CFGNode;

/**
 * How a CFG node participates in a concrete path.
 */
enum class PathDecisionKind {
    Code,       // use node->getCode()
    TrueBranch, // assume condition is true
    FalseBranch,// assume condition is false
    LoopInit,   // for-loop initializer
    LoopUpdate, // for-loop post expression
    SyntheticAssume, // LoopSCC validation-only summary guard
    SyntheticCode    // LoopSCC validation-only affine assignment
};

struct PathDecision {
    CFGNode* node{nullptr};
    PathDecisionKind kind{PathDecisionKind::Code};
    std::string syntheticText;
};

struct AffineLoopStateSummary {
    std::string variable;
    long long initialValue{0};
    long long step{0};
    long long iterations{0};
    long long finalValue{0};
    std::string sourceRelation;
};

struct LoopSccPhaseTrace {
    std::string loopCondition;
    bool complete{false};
    bool matchedDeterminateCycle{false};
    std::size_t cycleIndex{0};
    std::size_t period{0};
    std::size_t entryPhase{0};
    std::size_t observedIterations{0};
    std::size_t completePeriods{0};
    std::size_t residualPhases{0};
    bool matchedAccelerationPlan{false};
    std::size_t accelerationPlanIndex{0};
    std::vector<std::size_t> spathSequence;
    // Exact transform across the observed, cycle-matched loop execution.
    std::vector<LoopSccAffineTransform> pathAffineTransforms;
    // Independently derived from proved trip count + T^k, then compared
    // against the concrete unfolded path before VolCE sees it.
    std::vector<LoopSccAffineTransform> accelerationTransforms;
    std::vector<std::string> diagnostics;
};

struct LoopSccAffineStateSummary {
    std::string variable;
    long long scale{1};
    long long offset{0};
    std::size_t period{0};
    std::size_t observedIterations{0};
};

struct LoopSccAccelerationValidation {
    std::string loopCondition;
    bool attempted{false};
    bool statusMatched{false};
    bool memMatched{false};
    bool matched{false};
    std::size_t originalDecisionCount{0};
    std::size_t compressedDecisionCount{0};
    int baselineMem{0};
    int compressedMem{0};
    // SMT emitted by the validation-only compressed path. Model-count A/B is
    // performed by SyntaxNamePrinter/VolCE using the same finite domain.
    std::string compressedSmt;
};

struct EpatResult {
    epat::result status{epat::result::unknown};
    int mem{0};
    std::string smt;
    std::string model;
    std::vector<AffineLoopStateSummary> loopStateSummaries;
    std::vector<std::string> loopStateSummaryDiagnostics;
    // Optional structural LoopSCC stage. Populated only when
    // EPPATHER_LOOP_SCC_ANALYZE=1; it never changes feasibility/counting.
    std::vector<LoopSccGraphInfo> loopSccGraphs;
    std::vector<LoopSccPhaseTrace> loopSccPhaseTraces;
    // Path-specific affine relations from a proved determinate SPath cycle.
    // They are candidates only; VolCE must still prove them entailed by SMT.
    std::vector<LoopSccAffineStateSummary> loopSccAffineStateSummaries;
    std::vector<LoopSccAccelerationValidation>
        loopSccAccelerationValidations;
};

// Build a summarized decision stream for one certified LoopSCC
// acceleration plan. The input decisions are the prefix immediately before
// the loop. The returned stream contains the initial loop guard, entry-phase
// guard, closed-form scalar assignments, and final loop-exit guard.
std::optional<std::vector<PathDecision>>
buildLoopSccAccelerationDecisions(
    const std::vector<PathDecision>& prefix,
    CFGNode* loop,
    const LoopSccGraphInfo& graph,
    std::size_t planIndex);

class EpatRunner {
public:
    explicit EpatRunner(std::string prefix);

    // Render a script from the given decisions.
    std::string render(const std::vector<PathDecision>& decisions) const;

    // Run epat++ for a rendered script.
    EpatResult solveScript(const std::string& script) const;

    // Run epat++ using CFG decisions directly.
    EpatResult solve(const std::vector<PathDecision>& decisions) const;

    bool feasible(const std::vector<PathDecision>& decisions) const {
        return solve(decisions).status == epat::result::feasible;
    }

private:
    std::string prefix_;
};

}  // namespace C
}  // namespace psy
