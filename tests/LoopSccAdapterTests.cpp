#include "syntax/LoopSccAdapter.h"
#include "syntax/SyntaxNamePrinter.h"

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
            graph.contractedEdgeCount == 0;
        failures += !report("loopscc-oscillating-scc", ok);
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
