// Implementation of CFG-aware epat++ invocation utilities.
#include "EpatRunner.h"

#include <utility>

#include "SyntaxNamePrinter.h"

namespace psy {
namespace C {

namespace {
bool endsWithSemicolon(const std::string& s) {
    return !s.empty() && s.back() == ';';
}
}  // namespace

EpatRunner::EpatRunner(std::string prefix) : prefix_(std::move(prefix)) {
    if (!prefix_.empty() && prefix_.back() != '\n') prefix_.push_back('\n');
}

std::string EpatRunner::render(const std::vector<PathDecision>& decisions) const {
    std::string script = prefix_;

    for (const auto& step : decisions) {
        if (!step.node) continue;
        switch (step.kind) {
            case PathDecisionKind::LoopInit: {
                const auto& init = step.node->initstmt_str;
                if (!init.empty() && init != ";") {
                    script += init;
                    if (!endsWithSemicolon(init)) script += ";";
                    script += "\n";
                }
                break;
            }
            case PathDecisionKind::TrueBranch: {
                if (!step.node->cond_str.empty()) {
                    script += "@(" + step.node->cond_str + ");\n";
                }
                break;
            }
            case PathDecisionKind::FalseBranch: {
                if (!step.node->cond_str.empty()) {
                    script += "@(!(" + step.node->cond_str + "));\n";
                }
                break;
            }
            case PathDecisionKind::LoopUpdate: {
                if (!step.node->expr_str.empty()) {
                    script += step.node->expr_str;
                    if (!endsWithSemicolon(step.node->expr_str)) script += ";";
                    script += "\n";
                }
                break;
            }
            case PathDecisionKind::Code:
            default: {
                auto code = step.node->getCode();
                if (!code.empty()) {
                    script += code;
                    if (!endsWithSemicolon(code)) script += "\n";
                }
                break;
            }
        }
    }

    return script;
}

EpatResult EpatRunner::solveScript(const std::string& script) const {
    auto root = epat::Root::fromString(script);
    auto solver = epat::Solver::create(std::move(root));

    EpatResult result;
    result.status = solver->feasible();
    result.mem = solver->getMem();
    result.smt = solver->getSMT2();
    result.model = solver->getModel();
    result.raw_model = solver->getRawModel();
    return result;
}

EpatResult EpatRunner::solve(const std::vector<PathDecision>& decisions) const {
    return solveScript(render(decisions));
}

}  // namespace C
}  // namespace psy
