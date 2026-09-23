#pragma once

#include <cstddef>
#include <string>
#include <utility>
#include <vector>

namespace psy {
namespace C {

class CFGNode;

struct LoopSccAffineTransform {
    std::string variable;
    // x' = scale * x + offset. The current structural adapter supports
    // scale -1 (sign flip), 0 (constant), and 1 (increment/decrement).
    long long scale{1};
    long long offset{0};
};

// One acyclic entry-to-backedge/exit path through a single loop iteration.
// This is structural metadata only: the adapter does not replace bounded
// unfolding or assert any summary into VolCE.
struct LoopSccSPathInfo {
    std::size_t id{0};
    std::vector<std::string> guards;
    std::vector<std::string> writes;
    std::vector<std::string> affineUpdates;
    // Machine-readable form of the exact scalar transforms above.
    std::vector<LoopSccAffineTransform> affineTransforms;
    // True only when every executable statement on this SPath is represented
    // by the restricted scalar-affine model and no array/dereference access or
    // opaque call/effect was observed.
    bool accelerationEffectSafe{true};
    // False when any branch guard on the SPath is outside the interval model.
    bool guardModelComplete{true};
    bool returnsToHeader{false};
    bool exitsLoop{false};
};

struct LoopSccAccelerationPlan {
    std::size_t cycleIndex{0};
    std::size_t entryPhase{0};
    std::size_t period{0};
    long long totalIterations{0};
    long long completePeriods{0};
    std::size_t residualPhases{0};
    std::vector<std::size_t> residualSPaths;
    // Exact scalar relation after all proved iterations for this entry phase.
    std::vector<LoopSccAffineTransform> closedFormTransforms;
    // Current epat++ MEMS counts array subscripts and pointer dereferences.
    // The first shortcut gate admits only paths proved free of those accesses,
    // so skipping the repeated periods preserves MEMS without compensation.
    bool memsPreserving{false};
    long long skippableIterations{0};
    bool exact{false};
    std::vector<std::string> diagnostics;
};

struct LoopSccCycleInfo {
    std::size_t sccId{0};
    // Canonical SPath order for one proved deterministic cycle.
    std::vector<std::size_t> spathOrder;
    std::size_t period{0};
    bool determinate{false};
    // Every internal phase transition is proved by interval inclusion after
    // applying the source affine transform. The loop-control guard is excluded
    // here because exact trip-count proof handles it separately.
    bool phaseGuardsProved{false};
    bool guardedClosedFormCandidate{false};
    // Exact affine transform accumulated across one complete cycle, rendered
    // as human-readable relations for validation and later VolCE transport.
    std::vector<std::string> periodAffineUpdates;
    // Same period transform in machine-readable form for path-specific
    // composition and VolCE entailment.
    std::vector<LoopSccAffineTransform> periodAffineTransforms;
    std::vector<std::string> diagnostics;
};

struct LoopSccGraphInfo {
    std::string loopCondition;
    bool complete{false};
    std::vector<LoopSccSPathInfo> spaths;
    // Concrete SPath graph and its SCC contraction, retained for the next
    // periodic/oscillation analysis stage.
    std::vector<std::pair<std::size_t, std::size_t>> transitions;
    std::vector<std::vector<std::size_t>> sccs;
    std::vector<std::pair<std::size_t, std::size_t>> contractedEdges;
    std::size_t transitionCount{0};
    std::size_t sccCount{0};
    std::size_t cyclicSccCount{0};
    std::size_t multiNodeSccCount{0};
    std::size_t maxSccSize{0};
    std::size_t contractedEdgeCount{0};
    std::vector<LoopSccCycleInfo> cycles;
    std::size_t determinateCycleCount{0};
    std::size_t oscillatingCycleCount{0};
    std::size_t guardedClosedFormCandidateCount{0};
    // Exact trip count recovered from the SPath set when every returning
    // iteration path has the same affine step for the loop-control variable.
    // -1 means no such proof is available.
    long long provedTripCount{-1};
    std::string tripCountVariable;
    long long tripCountStep{0};
    // Symbolic acceleration plans derived from proved trip count + cycle
    // structure. One plan is emitted per possible cycle entry phase.
    std::vector<LoopSccAccelerationPlan> accelerationPlans;
    std::vector<std::string> diagnostics;
};

// Conservative structural adapter for the first LoopSCC stage:
//   loop CFG -> one-iteration SPaths -> SPath graph -> SCC contraction.
//
// Transitions are over-approximated. A transition is removed only when simple
// integer guard intervals and exact affine updates prove it impossible.
// Nested loops, unsupported internal cycles, and path-budget truncation make
// the graph incomplete; callers must keep the existing bounded-unrolling path.
class LoopSccAdapter {
public:
    static LoopSccGraphInfo analyze(CFGNode* loop,
                                    std::size_t maxPaths = 64,
                                    std::size_t maxNodesPerPath = 128);
};

}  // namespace C
}  // namespace psy
