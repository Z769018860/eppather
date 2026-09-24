#include "solver.h"
#include <unordered_set>
#include "c1_solver.h"
#include "mem_visitor.h"
#include "solver_base.h"

using namespace std;
using namespace epat;

namespace {
thread_local std::unordered_set<std::string> ssa_provenance_variables;
thread_local bool memory_ssa_provenance_enabled = false;
}

void epat::setSsaProvenanceVariables(
    const std::vector<std::string>& names)
{
    ssa_provenance_variables.clear();
    ssa_provenance_variables.insert(names.begin(), names.end());
}

void epat::clearSsaProvenanceVariables()
{
    ssa_provenance_variables.clear();
}

bool epat::isSsaProvenanceVariable(const std::string& name)
{
    return ssa_provenance_variables.find(name) !=
           ssa_provenance_variables.end();
}

void epat::setMemorySsaProvenanceEnabled(bool enabled)
{
    memory_ssa_provenance_enabled = enabled;
}

bool epat::isMemorySsaProvenanceEnabled()
{
    return memory_ssa_provenance_enabled;
}

namespace {
    class SolverImpl : public epat::Solver {
        epat::Root::ptr ast_;
        std::string model_, smt2_;
        epat::result result_ = epat::result::unknown;
        bool collect_artifacts_ = true;
        explicit SolverImpl(epat::Root::ptr ast) : Solver(), ast_(move(ast)) {}
    public:
        using ptr = std::unique_ptr<SolverImpl>;
        virtual ~SolverImpl() = default;
        static ptr create(epat::Root::ptr Ast) { return ptr(new SolverImpl(move(Ast))); }
        // epat::result _feasible()
        // {
        //     if (!dirty)
        //         return result_;
        //     result_ = feasible();
        //     dirty = false;
        //     return result_;
        // }
        virtual epat::result feasible() override
        {
            if (!ast_) {
                std::cout << "input is empty." << std::endl;
                return epat::result::unknown;
            }
            C1Solver<LinearMemoryLv> solver(*ast_);
            result_ = solver.feasible();
            if (collect_artifacts_) {
                if (epat::result::feasible == result_)
                    model_ = solver.getModel();
                else
                    model_ = "; no model available.";
                smt2_ = solver.getSMT2();
            }
            else {
                model_.clear();
                smt2_.clear();
            }
            return result_;

            // return _feasible();
            // // 预处理
            // auto info = PathInfo::of(*ast_);
            // if (!info->isPath()) {
            //     std::cout << "input is not a path." << std::endl;
            //     return result::unknown;
            // }
            // auto is_c1 = info->isC1();
            // if (is_c1) {
            //     epat_debug << "input is a c1 path." << std::endl;
            //     solver_ = std::make_unique<C1Solver>(*ast_);
            //     return solver_->feasible();
            // }
            // // if (is_c1) {
            // //     cout << "debug: skip a c1 path." << endl;
            // //     return result::unknown;
            // // }
            // auto has_array_access = info->has_array_access;
            // // if (has_array_access)
            // //     epat_debug << "input has array access." << endl;
            // // else
            // //     epat_debug << "input has no array access." << endl;
            // epat_debug << "input is a c0 path." << endl;
            // // TODO: 目前仅使用c1solver
            // solver_ = std::make_unique<C1Solver>(*ast_);
            // return solver_->feasible();
        }
        virtual void setCollectArtifacts(bool enabled) override {
            collect_artifacts_ = enabled;
        }
        virtual std::string getModel() const override { return model_; }
        virtual std::string getSMT2() const override { return smt2_; }
        virtual int getMem() const override { return MemVisitor::getMem(*ast_); }
    };
}

epat::Solver::Solver() {}

epat::Solver::~Solver() {}

epat::Solver::ptr epat::Solver::create(epat::Root::ptr Ast)
{
    return SolverImpl::create(move(Ast));
}

epat::result epat::Solver::feasible()
{
    return result::feasible;
}

void epat::Solver::setCollectArtifacts(bool)
{
}

void epat::Solver::printModel(std::ostream& os) const
{
    os << "the method \"printModel\" is unfinished." << endl;
}

std::string epat::Solver::getModel() const
{
    return "the method \"getModel\" is unfinished.";
}

void epat::Solver::printSMT2(std::ostream& os) const
{
    os << "the method \"printSMT2\" is unfinished." << endl;
}

std::string epat::Solver::getSMT2() const
{
    return "the method \"getSMT2\" is unfinished.";
}

void epat::Solver::printMem(std::ostream& os) const
{
    os << getMem() << endl;
}

int epat::Solver::getMem() const
{
    return 0;
}
