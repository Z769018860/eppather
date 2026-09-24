#include "syntax/LoopSccAdapter.h"
#include "syntax/EpatRunner.h"
#include "solver.h"
#include "syntax/SyntaxNamePrinter.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>

using psy::C::CFGNode;
using psy::C::LoopSccAdapter;
using psy::C::PathDecisionKind;
using psy::C::buildLoopSccAccelerationDecisions;
using psy::C::buildLoopSccMemoryAccelerationDecisions;

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

    // Memory observations must match epat++ MEMS semantics while remaining
    // ineligible for scalar-only acceleration until a memory-state summary is
    // proved.
    {
        auto loop = loopNode("i < 4");
        loop->initstmt_str = "i = 0;";
        auto write = node("a[i] = i;");
        auto increment = node("i = i + 1;");
        auto exit = node("return i;");
        loop->setNextNode(write);
        loop->setNextFalseNode(exit);
        write->setNextNode(increment);
        increment->setNextNode(loop);

        const auto graph = LoopSccAdapter::analyze(loop.get());
        const bool ok = graph.complete &&
            graph.spaths.size() == 1 &&
            graph.spaths[0].observedMems == 1 &&
            graph.spaths[0].memoryAccessModelComplete &&
            graph.spaths[0].writesMemory &&
            !graph.spaths[0].accelerationEffectSafe &&
            graph.accelerationPlans.empty();
        failures += !report("loopscc-array-write-mems-certificate", ok);
    }

    {
        auto loop = loopNode("i < 4");
        loop->initstmt_str = "i = 0;";
        auto write1 = node("a[0] = a[0] + 1;");
        auto write2 = node("a[0] += 2;");
        auto increment = node("i = i + 1;");
        auto exit = node("return i;");
        loop->setNextNode(write1);
        loop->setNextFalseNode(exit);
        write1->setNextNode(write2);
        write2->setNextNode(increment);
        increment->setNextNode(loop);

        const auto graph = LoopSccAdapter::analyze(loop.get());
        bool cellOk = false;
        if (graph.spaths.size() == 1 &&
            graph.spaths[0].memoryCellTransforms.size() == 1) {
            const auto& cell = graph.spaths[0].memoryCellTransforms[0];
            cellOk = cell.region == "a" &&
                cell.index == 0 &&
                cell.scale == 1 &&
                cell.offset == 3;
        }
        bool summaryOk = false;
        if (graph.memorySummaryCandidates.size() == 1 &&
            graph.memorySummaryCandidates[0].closedFormTransforms.size() == 1) {
            const auto& summary = graph.memorySummaryCandidates[0];
            const auto& cell = summary.closedFormTransforms[0];
            summaryOk = summary.exact &&
                summary.totalIterations == 4 &&
                summary.observedMems == 16 &&
                cell.region == "a" &&
                cell.index == 0 &&
                cell.scale == 1 &&
                cell.offset == 12;
        }
        bool shortcutPlanOk = false;
        if (graph.memorySummaryCandidates.size() == 1) {
            const auto shortcut =
                buildLoopSccMemoryAccelerationDecisions(
                    {}, loop.get(), graph, 0,
                    "int a[1];\nint i = 0;\n");
            if (shortcut) {
                bool sawSyntheticMems = false;
                for (const auto& decision : shortcut->decisions) {
                    if (decision.kind ==
                        PathDecisionKind::SyntheticMems) {
                        sawSyntheticMems =
                            decision.syntheticMems == 14;
                    }
                }
                psy::C::EpatRunner shortcutRunner(
                    "int a[1];\nint i = 0;\n");
                const auto shortcutEval =
                    shortcutRunner.solve(shortcut->decisions);
                const auto ambiguousShortcut =
                    buildLoopSccMemoryAccelerationDecisions(
                        {}, loop.get(), graph, 0,
                        "int a[1];\nint a[1];\nint i = 0;\n");
                const bool ambiguousRejected =
                    ambiguousShortcut &&
                    !ambiguousShortcut->preexecutionCertified &&
                    !ambiguousShortcut->certificateDiagnostics.empty();
                shortcutPlanOk =
                    shortcut->preexecutionCertified &&
                    !shortcut->certificateDiagnostics.empty() &&
                    shortcut->unfoldedMems == 16 &&
                    shortcut->compressedSummaryMems == 2 &&
                    shortcut->compensationMems == 14 &&
                    sawSyntheticMems &&
                    shortcutEval.status == epat::result::feasible &&
                    shortcutEval.mem == 16 &&
                    ambiguousRejected;
            }
        }
        const bool ok = graph.complete &&
            graph.spaths.size() == 1 &&
            graph.spaths[0].observedMems == 4 &&
            graph.spaths[0].writesMemory &&
            graph.spaths[0].memoryAccessModelComplete &&
            graph.spaths[0].memoryTransitionModelComplete &&
            cellOk && summaryOk && shortcutPlanOk &&
            graph.accelerationPlans.empty();
        failures += !report(
            "loopscc-fixed-cell-memory-transition-candidate", ok);
    }

    // A structurally recognized fixed cell still has to fit the declared
    // one-dimensional local array region before EpatRunner exports it.
    {
        auto loop = loopNode("i < 4");
        loop->initstmt_str = "i = 0;";
        auto write = node("a[1] = a[1] + 1;");
        auto increment = node("i = i + 1;");
        auto exit = node("return i;");
        loop->setNextNode(write);
        loop->setNextFalseNode(exit);
        write->setNextNode(increment);
        increment->setNextNode(loop);

        std::vector<psy::C::PathDecision> decisions;
        for (int iteration = 0; iteration < 4; ++iteration) {
            decisions.push_back({
                loop.get(), PathDecisionKind::TrueBranch, {}});
            decisions.push_back({
                write.get(), PathDecisionKind::Code, {}});
            decisions.push_back({
                increment.get(), PathDecisionKind::Code, {}});
        }
        decisions.push_back({
            loop.get(), PathDecisionKind::FalseBranch, {}});
        decisions.push_back({
            exit.get(), PathDecisionKind::Code, {}});

        setenv("EPPATHER_LOOP_SCC_ANALYZE", "1", 1);
        psy::C::EpatRunner runner("int a[1];\nint i = 0;\n");
        const auto eval = runner.solve(decisions);
        unsetenv("EPPATHER_LOOP_SCC_ANALYZE");

        bool diagnosed = false;
        for (const auto& diagnostic :
             eval.loopStateSummaryDiagnostics) {
            if (diagnostic.find(
                    "outside declared local array region a[1]") !=
                std::string::npos) {
                diagnosed = true;
                break;
            }
        }
        const bool ok =
            eval.loopSccMemoryCellStateSummaries.empty() &&
            diagnosed;
        failures += !report(
            "loopscc-fixed-cell-local-region-bounds", ok);
    }

    // Cross-cell and symbolic-index writes are observable memory effects but
    // are outside the fixed-cell transition model. They must not produce a
    // full-loop memory summary.
    {
        auto loop = loopNode("i < 4");
        loop->initstmt_str = "i = 0;";
        auto write = node("a[0] = a[1] + 1;");
        auto increment = node("i = i + 1;");
        auto exit = node("return i;");
        loop->setNextNode(write);
        loop->setNextFalseNode(exit);
        write->setNextNode(increment);
        increment->setNextNode(loop);

        const auto graph = LoopSccAdapter::analyze(loop.get());
        const bool ok = graph.complete &&
            graph.spaths.size() == 1 &&
            !graph.spaths[0].memoryTransitionModelComplete &&
            graph.memorySummaryCandidates.empty() &&
            graph.accelerationPlans.empty();
        failures += !report(
            "loopscc-cross-cell-memory-summary-fallback", ok);
    }

    {
        auto loop = loopNode("i < 4");
        loop->initstmt_str = "i = 0;";
        auto write = node("a[i] = a[i] + 1;");
        auto increment = node("i = i + 1;");
        auto exit = node("return i;");
        loop->setNextNode(write);
        loop->setNextFalseNode(exit);
        write->setNextNode(increment);
        increment->setNextNode(loop);

        const auto graph = LoopSccAdapter::analyze(loop.get());
        const bool ok = graph.complete &&
            graph.spaths.size() == 1 &&
            !graph.spaths[0].memoryTransitionModelComplete &&
            graph.memorySummaryCandidates.empty() &&
            graph.accelerationPlans.empty();
        failures += !report(
            "loopscc-symbolic-cell-memory-summary-fallback", ok);
    }

    {
        auto loop = loopNode("i < 4");
        loop->initstmt_str = "i = 0;";
        auto read = node("s = s + a[i];");
        auto increment = node("i = i + 1;");
        auto exit = node("return s;");
        loop->setNextNode(read);
        loop->setNextFalseNode(exit);
        read->setNextNode(increment);
        increment->setNextNode(loop);

        const auto graph = LoopSccAdapter::analyze(loop.get());
        const bool ok = graph.complete &&
            graph.spaths.size() == 1 &&
            graph.spaths[0].observedMems == 1 &&
            graph.spaths[0].memoryAccessModelComplete &&
            !graph.spaths[0].writesMemory &&
            !graph.spaths[0].accelerationEffectSafe &&
            graph.accelerationPlans.empty();
        failures += !report("loopscc-array-read-mems-certificate", ok);
    }

    {
        auto loop = loopNode("i < 4");
        loop->initstmt_str = "i = 0;";
        auto write = node("*p = i;");
        auto read = node("s = s + *p;");
        auto advance = node("p = p + 1;");
        auto increment = node("i = i + 1;");
        auto exit = node("return s;");
        loop->setNextNode(write);
        loop->setNextFalseNode(exit);
        write->setNextNode(read);
        read->setNextNode(advance);
        advance->setNextNode(increment);
        increment->setNextNode(loop);

        const auto graph = LoopSccAdapter::analyze(loop.get());
        const bool ok = graph.complete &&
            graph.spaths.size() == 1 &&
            graph.spaths[0].observedMems == 2 &&
            graph.spaths[0].memoryAccessModelComplete &&
            graph.spaths[0].writesMemory &&
            !graph.spaths[0].accelerationEffectSafe &&
            graph.accelerationPlans.empty();
        failures += !report("loopscc-pointer-mems-certificate", ok);
    }

    {
        auto loop = loopNode("i < 1");
        loop->initstmt_str = "i = 0;";
        auto updatePtr = node("*p += 1;");
        auto increment = node("i = i + 1;");
        auto exit = node("return i;");
        loop->setNextNode(updatePtr);
        loop->setNextFalseNode(exit);
        updatePtr->setNextNode(increment);
        increment->setNextNode(loop);

        const auto graph = LoopSccAdapter::analyze(loop.get());
        const bool ok = graph.complete &&
            graph.spaths.size() == 1 &&
            graph.spaths[0].observedMems == 2 &&
            graph.spaths[0].writesMemory &&
            graph.spaths[0].memoryAccessModelComplete &&
            !graph.spaths[0].memoryTransitionModelComplete &&
            graph.memorySummaryCandidates.empty() &&
            graph.accelerationPlans.empty();
        failures += !report(
            "loopscc-pointer-compound-mems-certificate", ok);
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

    // A unique constant pointer alias may reuse the fixed-cell memory
    // summary pipeline. Four iterations of *p=*p+1 through p=&a[1] produce
    // a[1]'=a[1]+4 and exactly two MEMS per iteration.
    {
        auto loop = loopNode("i < 4");
        loop->initstmt_str = "i = 0;";
        auto memory = node("*p = *p + 1;");
        auto increment = node("i = i + 1;");
        auto exit = node("return i;");
        loop->setNextNode(memory);
        loop->setNextFalseNode(exit);
        memory->setNextNode(increment);
        increment->setNextNode(loop);

        const std::string prefix =
            "int a[2];\nint *p = &a[1];\nint i = 0;\n";
        const auto aliases =
            LoopSccAdapter::parseConstantPointerAliases(prefix);
        const auto graph =
            LoopSccAdapter::analyzeWithConstantPointerAliases(
                loop.get(), prefix);

        bool relation = false;
        if (graph.memorySummaryCandidates.size() == 1) {
            const auto& candidate = graph.memorySummaryCandidates[0];
            relation = candidate.exact &&
                candidate.totalIterations == 4 &&
                candidate.observedMems == 8 &&
                candidate.closedFormTransforms.size() == 1 &&
                candidate.closedFormTransforms[0].region == "a" &&
                candidate.closedFormTransforms[0].index == 1 &&
                candidate.closedFormTransforms[0].scale == 1 &&
                candidate.closedFormTransforms[0].offset == 4;
        }
        auto memoryPlan =
            graph.memorySummaryCandidates.empty()
                ? std::optional<psy::C::LoopSccMemoryAccelerationDecisionPlan>{}
                : psy::C::buildLoopSccMemoryAccelerationDecisions(
                      {}, loop.get(), graph, 0, prefix);
        const bool certificate =
            memoryPlan &&
            memoryPlan->preexecutionCertified &&
            memoryPlan->unfoldedMems == 8 &&
            memoryPlan->compressedSummaryMems == 2 &&
            memoryPlan->compensationMems == 6;

        const bool ok = aliases.size() == 1 &&
            aliases[0].pointer == "p" &&
            aliases[0].region == "a" &&
            aliases[0].index == 1 &&
            graph.complete &&
            graph.provedTripCount == 4 &&
            relation &&
            certificate;
        failures += !report(
            "loopscc-constant-pointer-fixed-cell", ok);
    }

    // Array-decay initialization is the index-zero form of the same narrow
    // certificate. Keep this as a positive test so a moving-pointer fallback
    // cannot pass merely because "p = a" failed to parse.
    {
        auto loop = loopNode("i < 3");
        loop->initstmt_str = "i = 0;";
        auto memory = node("*p += 2;");
        auto increment = node("i = i + 1;");
        auto exit = node("return i;");
        loop->setNextNode(memory);
        loop->setNextFalseNode(exit);
        memory->setNextNode(increment);
        increment->setNextNode(loop);

        const std::string prefix =
            "int a[2];\nint *p = a;\nint i = 0;\n";
        const auto aliases =
            LoopSccAdapter::parseConstantPointerAliases(prefix);
        const auto graph =
            LoopSccAdapter::analyzeWithConstantPointerAliases(
                loop.get(), prefix);
        bool relation = false;
        if (graph.memorySummaryCandidates.size() == 1) {
            const auto& candidate = graph.memorySummaryCandidates[0];
            relation = candidate.exact &&
                candidate.observedMems == 6 &&
                candidate.closedFormTransforms.size() == 1 &&
                candidate.closedFormTransforms[0].region == "a" &&
                candidate.closedFormTransforms[0].index == 0 &&
                candidate.closedFormTransforms[0].scale == 1 &&
                candidate.closedFormTransforms[0].offset == 6;
        }
        const bool ok = aliases.size() == 1 &&
            aliases[0].pointer == "p" &&
            aliases[0].region == "a" &&
            aliases[0].index == 0 &&
            relation;
        failures += !report(
            "loopscc-array-decay-pointer-alias", ok);
    }

    // An address literal outside the certificate's signed 64-bit index
    // domain must conservatively fall back rather than throwing from stoll.
    {
        bool threw = false;
        std::vector<psy::C::LoopSccConstantPointerAlias> aliases;
        try {
            aliases = LoopSccAdapter::parseConstantPointerAliases(
                "int a[2];\n"
                "int *p = &a[999999999999999999999999999999999999];\n");
        } catch (...) {
            threw = true;
        }
        const bool ok = !threw && aliases.empty();
        failures += !report(
            "loopscc-oversized-pointer-alias-fallback", ok);
    }

    // The same declaration is not a certificate after p is moved/reassigned
    // in the loop. Alias invalidation must prevent a fixed-cell candidate.
    {
        auto loop = loopNode("i < 4");
        loop->initstmt_str = "i = 0;";
        auto memory = node("*p = *p + 1;");
        auto movePointer = node("p = p + 1;");
        auto increment = node("i = i + 1;");
        auto exit = node("return i;");
        loop->setNextNode(memory);
        loop->setNextFalseNode(exit);
        memory->setNextNode(movePointer);
        movePointer->setNextNode(increment);
        increment->setNextNode(loop);

        const std::string prefix =
            "int a[8];\nint *p = a;\nint i = 0;\n";
        const auto graph =
            LoopSccAdapter::analyzeWithConstantPointerAliases(
                loop.get(), prefix);
        const bool ok = graph.complete &&
            graph.memorySummaryCandidates.empty();
        failures += !report(
            "loopscc-moving-pointer-alias-fallback", ok);
    }

    // Plain multiplication is arithmetic, not pointer dereference. It remains
    // outside the restricted affine shortcut model, but the memory observer
    // must neither count MEMS nor throw a std::regex range exception.
    {
        auto loop = loopNode("i < 2");
        loop->initstmt_str = "i = 0;";
        auto multiply = node("x = i * 4;");
        auto increment = node("i = i + 1;");
        auto exit = node("return x;");
        loop->setNextNode(multiply);
        loop->setNextFalseNode(exit);
        multiply->setNextNode(increment);
        increment->setNextNode(loop);

        const auto graph = LoopSccAdapter::analyze(loop.get());
        const bool ok = graph.complete &&
            graph.spaths.size() == 1 &&
            graph.spaths[0].observedMems == 0 &&
            !graph.spaths[0].accelerationEffectSafe &&
            graph.accelerationPlans.empty();
        failures += !report("loopscc-multiplication-not-pointer", ok);
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
            graph.tripCountVariable == "i" &&
            graph.accelerationPlans.size() == 1 &&
            graph.accelerationPlans[0].exact &&
            graph.accelerationPlans[0].memsPreserving &&
            sawX6 && sawI3 && !leakedInnerJ;
        failures += !report("loopscc-inside-out-nested-for", ok);
    }

    // If the nested for reuses a variable declared in an outer scope, that
    // induction state remains visible after the nested loop and must therefore
    // be exported as the folded constant j=2.
    {
        auto outer = forLoopNode("int i = 0;", "i < 3", "i = i + 1");
        auto inner = forLoopNode("j = 0;", "j < 2", "j = j + 1");
        auto incX = node("x = x + 1;");
        auto exit = node("return x;");

        outer->setNextNode(inner);
        outer->setNextFalseNode(exit);
        inner->setNextNode(incX);
        inner->setNextFalseNode(outer);
        incX->setNextNode(inner);

        const auto graph = LoopSccAdapter::analyze(outer.get());
        bool sawJ2 = false;
        if (graph.accelerationPlans.size() == 1) {
            for (const auto& transform :
                 graph.accelerationPlans[0].closedFormTransforms) {
                if (transform.variable == "j") {
                    sawJ2 = transform.scale == 0 &&
                            transform.offset == 2;
                }
            }
        }
        const bool ok = graph.complete &&
            graph.insideOutNestedSummaryCount == 1 &&
            graph.accelerationPlans.size() == 1 &&
            graph.accelerationPlans[0].exact &&
            sawJ2;
        failures += !report(
            "loopscc-inside-out-predeclared-for-index", ok);
    }

    // A fixed-cell inner loop can be folded into one exact outer SPath.
    // Three outer iterations x four inner iterations produce a[1]+=12 while
    // preserving all 24 unfolded memory MEMS for SyntheticMems compensation.
    {
        auto outer = forLoopNode("int i = 0;", "i < 3", "i = i + 1");
        auto inner = forLoopNode("j = 0;", "j < 4", "j = j + 1");
        auto memory = node("a[1] = a[1] + 1;");
        auto exit = node("return a[1];");

        outer->setNextNode(inner);
        outer->setNextFalseNode(exit);
        inner->setNextNode(memory);
        inner->setNextFalseNode(outer);
        memory->setNextNode(inner);

        const auto graph = LoopSccAdapter::analyze(outer.get());
        bool sawCell = false;
        bool sawI = false;
        bool sawJ4 = false;
        if (graph.memorySummaryCandidates.size() == 1) {
            const auto& candidate =
                graph.memorySummaryCandidates.front();
            for (const auto& transform :
                 candidate.closedFormTransforms) {
                if (transform.region == "a" &&
                    transform.index == 1) {
                    sawCell = transform.scale == 1 &&
                              transform.offset == 12;
                }
            }
            for (const auto& transform :
                 candidate.scalarClosedFormTransforms) {
                if (transform.variable == "i") {
                    sawI = transform.scale == 1 &&
                           transform.offset == 3;
                } else if (transform.variable == "j") {
                    sawJ4 = transform.scale == 0 &&
                            transform.offset == 4;
                }
            }
        }

        const auto plan =
            graph.memorySummaryCandidates.empty()
                ? std::optional<psy::C::LoopSccMemoryAccelerationDecisionPlan>{}
                : buildLoopSccMemoryAccelerationDecisions(
                      {}, outer.get(), graph, 0, "int a[2];\n");
        const bool ok = graph.complete &&
            graph.insideOutNestedSummaryCount == 1 &&
            graph.insideOutNestedMemorySummaryCount == 1 &&
            graph.provedTripCount == 3 &&
            graph.spaths.size() == 1 &&
            graph.spaths[0].observedMems == 8 &&
            graph.spaths[0].certifiedNestedMemoryMems == 8 &&
            graph.spaths[0].memoryAccesses.empty() &&
            graph.accelerationPlans.empty() &&
            graph.memorySummaryCandidates.size() == 1 &&
            graph.memorySummaryCandidates[0].exact &&
            graph.memorySummaryCandidates[0].observedMems == 24 &&
            sawCell && sawI && sawJ4 &&
            plan && plan->preexecutionCertified &&
            plan->unfoldedMems == 24 &&
            plan->compressedSummaryMems == 2 &&
            plan->compensationMems == 22;
        failures += !report(
            "loopscc-inside-out-nested-fixed-memory", ok);
    }

    // Even exact fixed-cell inner summaries are not exportable when the
    // externally visible transform depends on the cycle entry phase. With
    // five inner iterations, the two alternating phases would add 7 vs 8.
    {
        auto outer = forLoopNode("int i = 0;", "i < 2", "i = i + 1");
        auto inner = loopNode("j < 5");
        inner->initstmt_str = "j = 0;";
        auto branch = ifNode("x >= 0");
        auto memoryA = node("a[1] = a[1] + 1;");
        auto flipA = node("x = 0 - x - 1;");
        auto memoryB = node("a[1] = a[1] + 2;");
        auto flipB = node("x = 0 - x - 1;");
        auto incJ = node("j = j + 1;");
        auto exit = node("return a[1];");

        outer->setNextNode(inner);
        outer->setNextFalseNode(exit);
        inner->setNextNode(branch);
        inner->setNextFalseNode(outer);
        branch->setNextNode(memoryA);
        branch->setNextFalseNode(memoryB);
        memoryA->setNextNode(flipA);
        flipA->setNextNode(incJ);
        memoryB->setNextNode(flipB);
        flipB->setNextNode(incJ);
        incJ->setNextNode(inner);

        const auto innerGraph = LoopSccAdapter::analyze(inner.get());
        bool sawDifferentPhases =
            innerGraph.memorySummaryCandidates.size() == 2;
        if (sawDifferentPhases) {
            const auto& first =
                innerGraph.memorySummaryCandidates[0];
            const auto& second =
                innerGraph.memorySummaryCandidates[1];
            sawDifferentPhases =
                first.closedFormTransforms.size() == 1 &&
                second.closedFormTransforms.size() == 1 &&
                first.closedFormTransforms[0].offset !=
                    second.closedFormTransforms[0].offset;
        }

        const auto outerGraph = LoopSccAdapter::analyze(outer.get());
        const bool ok = innerGraph.complete &&
            innerGraph.provedTripCount == 5 &&
            innerGraph.cycles.size() == 1 &&
            innerGraph.cycles[0].period == 2 &&
            sawDifferentPhases &&
            !outerGraph.complete &&
            outerGraph.insideOutNestedMemorySummaryCount == 0 &&
            outerGraph.memorySummaryCandidates.empty();
        failures += !report(
            "loopscc-inside-out-phase-dependent-memory-fallback", ok);
    }

    // Symbolic-index memory remains outside the fixed-cell proof. The inner
    // loop therefore has no exact memory candidate and the outer graph must
    // stay incomplete instead of treating it as an inside-out summary.
    {
        auto outer = forLoopNode("int i = 0;", "i < 2", "i = i + 1");
        auto inner = forLoopNode("int j = 0;", "j < 2", "j = j + 1");
        auto memory = node("a[k] = a[k] + 1;");
        auto exit = node("return i;");

        outer->setNextNode(inner);
        outer->setNextFalseNode(exit);
        inner->setNextNode(memory);
        inner->setNextFalseNode(outer);
        memory->setNextNode(inner);

        const auto graph = LoopSccAdapter::analyze(outer.get());
        const bool ok = !graph.complete &&
            graph.insideOutNestedMemorySummaryCount == 0 &&
            graph.memorySummaryCandidates.empty();
        failures += !report(
            "loopscc-inside-out-symbolic-memory-fallback", ok);
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

    // Final-memory SSA provenance is opt-in. It must expose the final
    // functional-store array only when explicitly enabled, leaving the legacy
    // memory formula unchanged by default.
    {
        const std::string script =
            "int a[1];\n"
            "a[0] = 1;\n"
            "return a[0];\n";
        psy::C::EpatRunner runner("");
        epat::setMemorySsaProvenanceEnabled(false);
        const auto baseline = runner.solveScript(script);
        epat::setMemorySsaProvenanceEnabled(true);
        const auto withMemorySsa = runner.solveScript(script);
        epat::setMemorySsaProvenanceEnabled(false);

        const bool ok =
            baseline.status == epat::result::feasible &&
            withMemorySsa.status == epat::result::feasible &&
            baseline.smt.find("%a#ssa_final") == std::string::npos &&
            baseline.smt.find("a@0#base") == std::string::npos &&
            withMemorySsa.smt.find("%a#ssa_final") != std::string::npos &&
            withMemorySsa.smt.find("a@0#base") != std::string::npos;
        failures += !report("loopscc-final-memory-ssa-provenance", ok);
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
