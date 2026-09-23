#include "syntax/LoopSccAdapter.h"
#include "syntax/SyntaxNamePrinter.h"

#include <algorithm>
#include <iostream>
#include <memory>
#include <string>

using psy::C::CFGNode;
using psy::C::LoopSccAdapter;

namespace {

std::shared_ptr<CFGNode> node(const std::string& code = {}) {
    auto n = std::make_shared<CFGNode>();
    if (!code.empty()) n->setCode(code);
    return n;
}

std::shared_ptr<CFGNode> loopNode(const std::string& condition) {
    auto n = node();
    n->isLoop = true;
    n->isWhile = true;
    n->isCondition = true;
    n->cond_str = condition;
    return n;
}

std::shared_ptr<CFGNode> ifNode(const std::string& condition) {
    auto n = node();
    n->isIf = true;
    n->isCondition = true;
    n->cond_str = condition;
    return n;
}

bool report(const char* name, bool ok) {
    std::cout << name << ": " << (ok ? "PASS" : "FAIL") << '\n';
    return ok;
}

}  // namespace

int main() {
    int failures = 0;

    // One canonical SPath with a self-transition.
    {
        auto loop = loopNode("i < 4");
        auto body = node("i = i + 1;");
        auto exit = node("return i;");
        loop->setNextNode(body);
        loop->setNextFalseNode(exit);
        body->setNextNode(loop);

        const auto graph = LoopSccAdapter::analyze(loop.get());
        const bool ok = graph.complete &&
            graph.spaths.size() == 1 &&
            graph.spaths[0].returnsToHeader &&
            graph.transitionCount == 1 &&
            graph.transitions.size() == 1 &&
            graph.sccCount == 1 &&
            graph.sccs.size() == 1 &&
            graph.cyclicSccCount == 1 &&
            graph.maxSccSize == 1;
        failures += !report("loopscc-single-spath", ok);
    }

    // Two branch SPaths oscillate around x=0. Every branch can be followed by
    // either branch on some state, producing one two-node SCC.
    {
        auto loop = loopNode("i < 10");
        auto branch = ifNode("x > 0");
        auto positive = node("x = x - 1;");
        auto nonPositive = node("x = x + 1;");
        auto exit = node("return x;");
        loop->setNextNode(branch);
        loop->setNextFalseNode(exit);
        branch->setNextNode(positive);
        branch->setNextFalseNode(nonPositive);
        positive->setNextNode(loop);
        nonPositive->setNextNode(loop);

        const auto graph = LoopSccAdapter::analyze(loop.get());
        const bool ok = graph.complete &&
            graph.spaths.size() == 2 &&
            graph.transitionCount == 4 &&
            graph.sccCount == 1 &&
            graph.sccs.size() == 1 &&
            graph.sccs[0].size() == 2 &&
            graph.multiNodeSccCount == 1 &&
            graph.cyclicSccCount == 1 &&
            graph.maxSccSize == 2 &&
            graph.contractedEdgeCount == 0 &&
            graph.determinateCycleCount == 0 &&
            graph.oscillatingCycleCount == 0;
        failures += !report("loopscc-oscillating-scc", ok);
    }


    // A proved sign-flipping oscillation. For x >= 0 and x < 0 alike,
    // x' = -x - 1 crosses the phase boundary exactly. Interval reasoning
    // therefore leaves one unique successor and predecessor per SPath.
    // Applying the transform twice yields x_after_period=x.
    {
        auto loop = loopNode("i < 4");
        loop->initstmt_str = "i = 0;";
        auto branch = ifNode("x >= 0");
        auto nonNegative = node("x = 0 - x - 1;");
        auto negative = node("x = 0 - x - 1;");
        auto increment = node("i = i + 1;");
        auto exit = node("return x;");
        loop->setNextNode(branch);
        loop->setNextFalseNode(exit);
        branch->setNextNode(nonNegative);
        branch->setNextFalseNode(negative);
        nonNegative->setNextNode(increment);
        negative->setNextNode(increment);
        increment->setNextNode(loop);

        const auto graph = LoopSccAdapter::analyze(loop.get());
        const bool relation =
            !graph.cycles.empty() &&
            std::find(graph.cycles[0].periodAffineUpdates.begin(),
                      graph.cycles[0].periodAffineUpdates.end(),
                      "x_after_period=x") !=
                graph.cycles[0].periodAffineUpdates.end() &&
            std::find(graph.cycles[0].periodAffineUpdates.begin(),
                      graph.cycles[0].periodAffineUpdates.end(),
                      "i_after_period=i+2") !=
                graph.cycles[0].periodAffineUpdates.end();
        bool accelerationOk = graph.accelerationPlans.size() == 2;
        for (const auto& plan : graph.accelerationPlans) {
            bool sawX = false;
            bool sawI = false;
            for (const auto& transform : plan.closedFormTransforms) {
                if (transform.variable == "x") {
                    sawX = transform.scale == 1 &&
                           transform.offset == 0;
                } else if (transform.variable == "i") {
                    sawI = transform.scale == 1 &&
                           transform.offset == 4;
                }
            }
            accelerationOk = accelerationOk &&
                plan.exact &&
                plan.totalIterations == 4 &&
                plan.period == 2 &&
                plan.completePeriods == 2 &&
                plan.residualPhases == 0 &&
                plan.residualSPaths.empty() &&
                sawX && sawI;
        }

        const bool ok = graph.complete &&
            graph.spaths.size() == 2 &&
            graph.transitionCount == 2 &&
            graph.sccCount == 1 &&
            graph.multiNodeSccCount == 1 &&
            graph.determinateCycleCount == 1 &&
            graph.oscillatingCycleCount == 1 &&
            graph.guardedClosedFormCandidateCount == 1 &&
            graph.cycles.size() == 1 &&
            graph.cycles[0].period == 2 &&
            graph.cycles[0].determinate &&
            graph.cycles[0].guardedClosedFormCandidate &&
            graph.provedTripCount == 4 &&
            graph.tripCountVariable == "i" &&
            graph.tripCountStep == 1 &&
            accelerationOk &&
            relation;
        failures += !report("loopscc-determinate-period-two", ok);
    }

    // The same cycle with five exact iterations exercises residual-phase
    // composition: two complete periods plus one SPath must yield
    // x'=-x-1 and i'=i+5 for either possible entry phase.
    {
        auto loop = loopNode("i < 5");
        loop->initstmt_str = "i = 0;";
        auto branch = ifNode("x >= 0");
        auto nonNegative = node("x = 0 - x - 1;");
        auto negative = node("x = 0 - x - 1;");
        auto increment = node("i = i + 1;");
        auto exit = node("return x;");
        loop->setNextNode(branch);
        loop->setNextFalseNode(exit);
        branch->setNextNode(nonNegative);
        branch->setNextFalseNode(negative);
        nonNegative->setNextNode(increment);
        negative->setNextNode(increment);
        increment->setNextNode(loop);

        const auto graph = LoopSccAdapter::analyze(loop.get());
        bool plansOk = graph.provedTripCount == 5 &&
                       graph.accelerationPlans.size() == 2;
        for (const auto& plan : graph.accelerationPlans) {
            bool sawX = false;
            bool sawI = false;
            for (const auto& transform : plan.closedFormTransforms) {
                if (transform.variable == "x") {
                    sawX = transform.scale == -1 &&
                           transform.offset == -1;
                } else if (transform.variable == "i") {
                    sawI = transform.scale == 1 &&
                           transform.offset == 5;
                }
            }
            plansOk = plansOk && plan.exact &&
                plan.completePeriods == 2 &&
                plan.residualPhases == 1 &&
                plan.residualSPaths.size() == 1 &&
                sawX && sawI;
        }
        failures += !report(
            "loopscc-acceleration-residual-phase", plansOk);
    }

    // x<0 can move to either side after +1, while x>=0 can only remain on the
    // non-negative side. The SPath graph therefore has two SCCs and one CSG
    // edge from the negative component to the non-negative component.
    {
        auto loop = loopNode("i < 10");
        auto branch = ifNode("x < 0");
        auto negative = node("x = x + 1;");
        auto nonNegative = node("x = x + 1;");
        auto exit = node("return x;");
        loop->setNextNode(branch);
        loop->setNextFalseNode(exit);
        branch->setNextNode(negative);
        branch->setNextFalseNode(nonNegative);
        negative->setNextNode(loop);
        nonNegative->setNextNode(loop);

        const auto graph = LoopSccAdapter::analyze(loop.get());
        const bool ok = graph.complete &&
            graph.spaths.size() == 2 &&
            graph.transitionCount == 3 &&
            graph.sccCount == 2 &&
            graph.multiNodeSccCount == 0 &&
            graph.cyclicSccCount == 2 &&
            graph.maxSccSize == 1 &&
            graph.contractedEdgeCount == 1 &&
            graph.contractedEdges.size() == 1;
        failures += !report("loopscc-contracted-csg", ok);
    }

    // Nested loops require inside-out summaries. The first adapter stage must
    // diagnose and fall back instead of pretending the outer graph is exact.
    {
        auto outer = loopNode("i < 4");
        auto inner = loopNode("j < 3");
        auto exit = node("return i;");
        outer->setNextNode(inner);
        outer->setNextFalseNode(exit);
        inner->setNextNode(inner);
        inner->setNextFalseNode(outer);

        const auto graph = LoopSccAdapter::analyze(outer.get());
        const bool ok = !graph.complete && graph.spaths.empty() &&
                        !graph.diagnostics.empty();
        failures += !report("loopscc-nested-fallback", ok);
    }

    return failures == 0 ? 0 : 1;
}
