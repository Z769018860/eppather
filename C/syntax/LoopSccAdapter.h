#pragma once

#include <cstddef>
#include <string>
#include <utility>
#include <vector>

namespace psy {
namespace C {

class CFGNode;

// One acyclic entry-to-backedge/exit path through a single loop iteration.
// This is structural metadata only: the adapter does not replace bounded
// unfolding or assert any summary into VolCE.
struct LoopSccSPathInfo {
    std::size_t id{0};
    std::vector<std::string> guards;
    std::vector<std::string> writes;
    std::vector<std::string> affineUpdates;
    bool returnsToHeader{false};
    bool exitsLoop{false};
};

struct LoopSccCycleInfo {
    std::size_t sccId{0};
    // Canonical SPath order for one proved deterministic cycle.
    std::vector<std::size_t> spathOrder;
    std::size_t period{0};
    bool determinate{false};
    bool guardedClosedFormCandidate{false};
    // Exact affine transform accumulated across one complete cycle, rendered
    // as human-readable relations for validation and later VolCE transport.
    std::vector<std::string> periodAffineUpdates;
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
