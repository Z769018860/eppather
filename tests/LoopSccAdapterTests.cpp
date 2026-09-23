#include "syntax/LoopSccAdapter.h"
#include "syntax/EpatRunner.h"
#include "solver.h"
#include "syntax/SyntaxNamePrinter.h"

#include <algorithm>
#include <iostream>
#include <memory>
#include <string>

using psy::C::CFGNode;
using psy::C::LoopSccAdapter;
using psy::C::PathDecisionKind;
using psy::C::buildLoopSccAccelerationDecisions;

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

std::shared_ptr<CFGNode> forLoopNode(const std::string& init,
                                     const std::string& condition,
                                     const std::string& update) {
    auto n = node();
    n->isLoop = true;
    n->isFor = true;
    n->isCondition = true;
    n->initstmt_str = init;
    n->cond_str = condition;
    n->expr_str = update;
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
                plan.memsPreserving &&
                plan.skippableIterations == 4 &&
                !plan.coverageSlots.empty() &&
                sawX && sawI;
        }

        bool decisionBuilderOk = false;
        if (!graph.accelerationPlans.empty()) {
            auto accelerated = buildLoopSccAccelerationDecisions(
                {}, loop.get(), graph, 0);
            if (accelerated && accelerated->size() >= 4) {
                bool sawAssume = false;
                bool sawCode = false;
                for (const auto& decision : *accelerated) {
                    sawAssume = sawAssume ||
                        decision.kind ==
                            PathDecisionKind::SyntheticAssume;
                    sawCode = sawCode ||
                        decision.kind ==
                            PathDecisionKind::SyntheticCode;
                }
                decisionBuilderOk =
                    accelerated->front().kind ==
                        PathDecisionKind::TrueBranch &&
                    accelerated->back().kind ==
                        PathDecisionKind::FalseBranch &&
                    sawAssume && sawCode;
            }
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
            graph.cycles[0].phaseGuardsProved &&
            graph.cycles[0].guardedClosedFormCandidate &&
            graph.provedTripCount == 4 &&
            graph.tripCountVariable == "i" &&
            graph.tripCountStep == 1 &&
            accelerationOk &&
            decisionBuilderOk &&
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
                plan.memsPreserving &&
                plan.skippableIterations == 5 &&
                sawX && sawI;
        }
        bool residualBuilderOk = false;
        if (!graph.accelerationPlans.empty()) {
            auto accelerated = buildLoopSccAccelerationDecisions(
                {}, loop.get(), graph, 0);
            residualBuilderOk = accelerated &&
                accelerated->front().kind ==
                    PathDecisionKind::TrueBranch &&
                accelerated->back().kind ==
                    PathDecisionKind::FalseBranch;
        }
        failures += !report(
            "loopscc-acceleration-residual-phase",
            plansOk && residualBuilderOk);
    }

    // Unsupported guards may still be useful structurally, but they are not
    // enough to certify a shortcut. "!=" is intentionally outside the single
    // interval model and therefore must leave acceleration disabled.
    {
        auto loop = loopNode("i < 4");
        loop->initstmt_str = "i = 0;";
        auto branch = ifNode("x != 0");
        auto nonZero = node("x = 0 - x - 1;");
        auto zero = node("x = 0 - x - 1;");
        auto increment = node("i = i + 1;");
        auto exit = node("return x;");
        loop->setNextNode(branch);
        loop->setNextFalseNode(exit);
        branch->setNextNode(nonZero);
        branch->setNextFalseNode(zero);
        nonZero->setNextNode(increment);
        zero->setNextNode(increment);
        increment->setNextNode(loop);

        const auto graph = LoopSccAdapter::analyze(loop.get());
        bool incompleteGuard = false;
        for (const auto& spath : graph.spaths) {
            incompleteGuard = incompleteGuard ||
                !spath.guardModelComplete;
        }
        bool noProvedPhase = true;
        for (const auto& cycle : graph.cycles) {
            noProvedPhase = noProvedPhase &&
                !cycle.phaseGuardsProved;
        }
        const bool ok = graph.complete &&
            incompleteGuard &&
            noProvedPhase &&
            graph.accelerationPlans.empty();
        failures += !report("loopscc-unsupported-guard-fallback", ok);
    }

    // Opaque calls are not part of the restricted scalar-affine semantics.
    // Even if the surrounding scalar state looks periodic, acceleration must
    // fall back so hidden memory accesses or side effects cannot be skipped.
    {
        auto loop = loopNode("i < 4");
        loop->initstmt_str = "i = 0;";
        auto branch = ifNode("x >= 0");
        auto positive = node("x = 0 - x - 1;");
        auto negative = node("x = 0 - x - 1;");
        auto opaque = node("touch(x);");
        auto increment = node("i = i + 1;");
        auto exit = node("return x;");
        loop->setNextNode(branch);
        loop->setNextFalseNode(exit);
        branch->setNextNode(positive);
        branch->setNextFalseNode(negative);
        positive->setNextNode(opaque);
        negative->setNextNode(opaque);
        opaque->setNextNode(increment);
        increment->setNextNode(loop);

        const auto graph = LoopSccAdapter::analyze(loop.get());
        bool allUnsafe = true;
        for (const auto& spath : graph.spaths) {
            allUnsafe = allUnsafe && !spath.accelerationEffectSafe;
        }
        const bool ok = graph.complete &&
            graph.spaths.size() == 2 &&
            allUnsafe &&
            graph.guardedClosedFormCandidateCount == 0 &&
            graph.accelerationPlans.empty();
        failures += !report("loopscc-opaque-effect-fallback", ok);
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

    // Safe scalar nesting is summarized inside-out. The inner j-loop adds
    // two to x; the outer i-loop repeats that exact summary three times.
    {
        auto outer = loopNode("i < 3");
        outer->initstmt_str = "i = 0;";
        auto resetJ = node("j = 0;");
        auto inner = loopNode("j < 2");
        inner->initstmt_str = "j = 0;";
        auto incX = node("x = x + 1;");
        auto incJ = node("j = j + 1;");
        auto incI = node("i = i + 1;");
        auto exit = node("return x;");

        outer->setNextNode(resetJ);
        outer->setNextFalseNode(exit);
        resetJ->setNextNode(inner);
        inner->setNextNode(incX);
        inner->setNextFalseNode(incI);
        incX->setNextNode(incJ);
        incJ->setNextNode(inner);
        incI->setNextNode(outer);

        const auto graph = LoopSccAdapter::analyze(outer.get());
        bool sawX6 = false;
        bool sawI3 = false;
        bool leakedInnerJ = false;
        if (graph.accelerationPlans.size() == 1) {
            for (const auto& transform :
                 graph.accelerationPlans[0].closedFormTransforms) {
                if (transform.variable == "x") {
                    sawX6 = transform.scale == 1 &&
                            transform.offset == 6;
                } else if (transform.variable == "i") {
                    sawI3 = transform.scale == 1 &&
                            transform.offset == 3;
                } else if (transform.variable == "j") {
                    leakedInnerJ = true;
                }
            }
        }
        const bool ok = graph.complete &&
            graph.insideOutNestedSummaryCount == 1 &&
            graph.provedTripCount == 3 &&
            graph.accelerationPlans.size() == 1 &&
            graph.accelerationPlans[0].exact &&
            graph.accelerationPlans[0].memsPreserving &&
            graph.accelerationPlans[0].skippableIterations == 3 &&
            sawX6 && sawI3 && sawJ2;
        failures += !report("loopscc-inside-out-scalar-nested", ok);
    }

    // Canonical nested for-loops also participate in inside-out summaries.
    // The inner initializer must be folded into the nested closed form:
    // j starts from 0 on every outer iteration, so the outer summary observes
    // j=2 rather than j_out=j_entry+2.
    {
        auto outer = forLoopNode("int i = 0;", "i < 3", "i = i + 1");
        auto inner = forLoopNode("int j = 0;", "j < 2", "j = j + 1");
        auto incX = node("x = x + 1;");
        auto exit = node("return x;");

        outer->setNextNode(inner);
        outer->setNextFalseNode(exit);
        inner->setNextNode(incX);
        inner->setNextFalseNode(outer);
        incX->setNextNode(inner);

        const auto graph = LoopSccAdapter::analyze(outer.get());
        bool sawX6 = false;
        bool sawI3 = false;
        bool sawJ2 = false;
        if (graph.accelerationPlans.size() == 1) {
            for (const auto& transform :
                 graph.accelerationPlans[0].closedFormTransforms) {
                if (transform.variable == "x") {
                    sawX6 = transform.scale == 1 &&
                            transform.offset == 6;
                } else if (transform.variable == "i") {
                    sawI3 = transform.scale == 1 &&
                            transform.offset == 3;
                } else if (transform.variable == "j") {
                    sawJ2 = transform.scale == 0 &&
                            transform.offset == 2;
                }
            }
        }
        const bool ok = graph.complete &&
            graph.insideOutNestedSummaryCount == 1 &&
            graph.provedTripCount == 3 &&
            graph.tripCountVariable == "i" &&
            graph.accelerationPlans.size() == 1 &&
            graph.accelerationPlans[0].exact &&
            graph.accelerationPlans[0].memsPreserving &&
            sawX6 && sawI3 && !leakedInnerJ;
        failures += !report("loopscc-inside-out-nested-for", ok);
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

    // Isolate epat++/SSA from CFG wiring: this is the exact expected
    // determinate four-iteration path for the end-to-end periodic fixture.
    {
        const std::string script =
            "int state = 0;\n"
            "int i = 0;\n"
            "@(i < 4);\n"
            "@(state < 1);\n"
            "state = 2;\n"
            "i = i + 1;\n"
            "@(i < 4);\n"
            "@(!(state < 1));\n"
            "state = 0;\n"
            "i = i + 1;\n"
            "@(i < 4);\n"
            "@(state < 1);\n"
            "state = 2;\n"
            "i = i + 1;\n"
            "@(i < 4);\n"
            "@(!(state < 1));\n"
            "state = 0;\n"
            "i = i + 1;\n"
            "@(!(i < 4));\n"
            "return state;\n";
        psy::C::EpatRunner runner("");
        const auto raw = runner.solveScript(script);
        epat::setSsaProvenanceVariables({"state", "i"});
        const auto withSsa = runner.solveScript(script);
        epat::clearSsaProvenanceVariables();
        const bool ok =
            raw.status == epat::result::feasible &&
            withSsa.status == epat::result::feasible;
        failures += !report("loopscc-periodic-epat-script", ok);
    }

    return failures == 0 ? 0 : 1;
}
