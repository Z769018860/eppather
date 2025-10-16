#include "smt_solver.h"
#include "z3++.h"
#include <iostream>
#include <sstream>

class epat::smt::SolverImpl {
public:
    // z3::context z3ctx;
    z3::solver z3solver;
    // std::ostringstream oss_;
    SolverImpl() : z3solver(gc) {}
    ~SolverImpl() = default;
};

epat::smt::Solver::Solver() : impl_(std::make_unique<smt::SolverImpl>()) {}

epat::smt::Solver::~Solver() = default;

epat::smt::result epat::smt::Solver::solve()
{
    try {
        // TODO: 获取smt2
        auto& solver = impl_->z3solver;
        // impl_->z3solver.from_string(oss_.str().c_str());
        epat_log("smt:\n", solver.to_smt2());
        auto ret = solver.check();
        switch (ret) {
        case z3::sat:
            return smt::result::sat;
        case z3::unsat:
            return smt::result::unsat;
        case z3::unknown:
        default:
            return smt::result::unknown;
        }
    }
    catch (z3::exception& e) {
        std::cout << e << std::endl;
        return smt::result::unknown;
    }
}

std::string epat::smt::Solver::getModel()
{
    try {
        // TODO: 改写
        return impl_->z3solver.get_model().to_string();
    }
    catch (z3::exception& e) {
        std::cout << e << std::endl;
        return "; error when get model.";
    }
}

std::string epat::smt::Solver::getSMT2()
{
    try {
        return impl_->z3solver.to_smt2();
    }
    catch (z3::exception& e) {
        std::cout << e << std::endl;
        return "; error when get smt2.";
    }
}

// std::ostringstream& epat::smt::Solver::oss()
// {
//     return impl_->oss_;
// }

void epat::smt::Solver::pushCond(smt::expr const& cond)
{
    epat_log("push cond: ", cond);
    impl_->z3solver.add(cond.is_bool() ? cond : (cond != 0));
}

void epat::smt::Solver::pushLimit(smt::expr value, smt::expr start, smt::expr end)
{
    pushCond((start <= value) && (value < end));
}
