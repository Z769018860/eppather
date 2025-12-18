// Wrapper helpers for invoking epat++ with CFG-aware paths.
#pragma once

#include <memory>
#include <string>
#include <vector>

#include "solver.h"

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
    LoopUpdate  // for-loop post expression
};

struct PathDecision {
    CFGNode* node{nullptr};
    PathDecisionKind kind{PathDecisionKind::Code};
};

struct EpatResult {
    epat::result status{epat::result::unknown};
    int mem{0};
    std::string smt;
    std::string model;
};

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
