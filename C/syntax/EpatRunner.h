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
    SyntheticAssume, // LoopSCC summary guard
    SyntheticCode,   // LoopSCC affine/memory assignment
    SyntheticMemoryCheckpoint, // internal loop-entry whole-memory snapshot
    SyntheticMems    // cost-only compensation; emits no SMT/source code
};

struct PathDecision {
    CFGNode* node{nullptr};
    PathDecisionKind kind{PathDecisionKind::Code};
    std::string syntheticText;
    long long syntheticMems{0};
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

struct LoopSccCoupledAffineStateSummary {
    std::vector<std::string> variables;
    std::vector<long long> matrix;
    std::vector<long long> offset;
    std::size_t period{0};
    std::size_t observedIterations{0};
};

struct LoopSccMemoryCellStateSummary {
    std::string region;
    long long index{0};
    long long scale{1};
    long long offset{0};
    std::size_t period{0};
    std::size_t observedIterations{0};
    std::size_t observedMems{0};
    // Declared fixed local-array extent. VolCE uses this to prove the full
    // untouched frame instead of guessing region size from SMT occurrences.
    std::size_t regionCells{0};
};

struct LoopSccMemoryAccelerationValidation {
    std::string loopCondition;
    bool attempted{false};
    bool statusMatched{false};
    bool compensatedMemMatched{false};
    bool matched{false};
    std::size_t originalDecisionCount{0};
    std::size_t compressedDecisionCount{0};
    std::size_t unfoldedLoopMems{0};
    std::size_t compressedSummaryMems{0};
    int baselineMem{0};
    int compressedMem{0};
    int compensatedMem{0};
    std::string compressedSmt;
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

struct LoopSccCoupledAffineValidation {
    std::string loopCondition;
    bool attempted{false};
    bool typeCertified{false};
    bool snapshotParallelized{false};
    bool statusMatched{false};
    bool memMatched{false};
    bool matched{false};
    std::size_t originalDecisionCount{0};
    std::size_t compressedDecisionCount{0};
    int baselineMem{0};
    int compressedMem{0};
    std::string compressedSmt;
    std::vector<std::string> certificateDiagnostics;
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
    // Type-certified coupled relations are still validation-only: VolCE must
    // independently prove each non-identity matrix row from the unfolded SMT.
    std::vector<LoopSccCoupledAffineStateSummary>
        loopSccCoupledAffineStateSummaries;
    // Fixed-cell memory relations remain validation-only until frame/alias
    // proofs certify that untouched memory is preserved.
    std::vector<LoopSccMemoryCellStateSummary>
        loopSccMemoryCellStateSummaries;
    std::vector<LoopSccAccelerationValidation>
        loopSccAccelerationValidations;
    std::vector<LoopSccCoupledAffineValidation>
        loopSccCoupledAffineValidations;
    std::vector<LoopSccMemoryAccelerationValidation>
        loopSccMemoryAccelerationValidations;
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

struct LoopSccCoupledAffineDecisionPlan {
    std::vector<PathDecision> decisions;
    std::vector<int> coverageSlots;
    std::vector<std::string> snapshotVariables;
    bool typeCertified{false};
    bool snapshotParallelized{false};
    // Pre-execution interval proof derived only from declaration initializers
    // and the concrete PathDecision prefix before this loop.
    bool entryRangeCertified{false};
    bool preexecutionOverflowCertified{false};
    std::optional<long long> boundedRangeLower;
    std::optional<long long> boundedRangeUpper;
    // Still false in this stage: SMT row entailment is a post-hoc oracle and
    // has not yet been converted into a reusable pre-execution semantic cert.
    bool runtimeShortcutEligible{false};
    std::vector<std::string> certificateDiagnostics;
};

// Build a validation-only compressed decision stream for a coupled integer
// affine candidate. Every state variable must be a unique signed integer
// scalar. All entry values are snapshotted before any matrix row is assigned,
// preserving simultaneous state' = A*state+b semantics.
std::optional<LoopSccCoupledAffineDecisionPlan>
buildLoopSccCoupledAffineValidationDecisions(
    const std::vector<PathDecision>& prefix,
    CFGNode* loop,
    const LoopSccGraphInfo& graph,
    std::size_t candidateIndex,
    const std::string& sourcePrefix,
    std::optional<long long> boundedLower = std::nullopt,
    std::optional<long long> boundedUpper = std::nullopt);

struct LoopSccMemoryAccelerationDecisionPlan {
    std::vector<PathDecision> decisions;
    std::vector<int> coverageSlots;
    std::size_t unfoldedMems{0};
    std::size_t compressedSummaryMems{0};
    std::size_t compensationMems{0};
    // Structural certificate established before DFS replacement. It is
    // deliberately narrower than the later VolCE oracle: only unique
    // one-dimensional fixed local arrays, constant indices, complete fixed-cell
    // transitions, precise MEMS accounting, and no pointer/opaque effects.
    bool preexecutionCertified{false};
    std::vector<std::string> certificateDiagnostics;
};

// Build a fixed-cell memory summary path and its pre-execution structural
// certificate. Every summarized/accessed region must be a unique
// one-dimensional fixed local array, every access must use a constant in-bounds
// index, every write must be covered by a fixed-cell transition, and no
// pointer/opaque effect may occur. SyntheticMems restores the skipped MEMS
// cost. VolCE relation/frame validation remains an independent A/B oracle.
std::optional<LoopSccMemoryAccelerationDecisionPlan>
buildLoopSccMemoryAccelerationDecisions(
    const std::vector<PathDecision>& prefix,
    CFGNode* loop,
    const LoopSccGraphInfo& graph,
    std::size_t candidateIndex,
    const std::string& sourcePrefix);

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
    // Original source declarations, retained before bounded-VLA normalization.
    // LoopSCC uses this only for conservative fixed local-array extent checks.
    std::string sourcePrefix_;
    std::string prefix_;
};

}  // namespace C
}  // namespace psy
