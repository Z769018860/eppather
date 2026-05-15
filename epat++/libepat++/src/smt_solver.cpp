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

namespace {
std::string formatValue(const z3::expr& value)
{
    try {
        if (value.is_bool()) {
            switch (Z3_get_bool_value(value.ctx(), value)) {
            case Z3_L_TRUE:
                return "true";
            case Z3_L_FALSE:
                return "false";
            default:
                return "unknown";
            }
        }
        if (value.is_numeral())
            return Z3_get_numeral_string(value.ctx(), value);
    }
    catch (z3::exception& e) {
        std::cout << e << std::endl;
        return value.to_string();
    }

    return value.to_string();
}
} // namespace

std::string epat::smt::Solver::getModel()
{
    try {
        auto model = impl_->z3solver.get_model();
        std::ostringstream oss;
        for (unsigned i = 0; i < model.size(); ++i) {
            auto decl = model[i];
            auto value = model.get_const_interp(decl);
            oss << decl.name() << " = " << formatValue(value) << '\n';
        }
        return oss.str();
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
    try {
        epat_log("push cond: ", cond);
        impl_->z3solver.add(cond.is_bool() ? cond : (cond != 0));
    }
    catch (const z3::exception& e) {
        std::cout << "[pushCond z3 exception] " << e << std::endl;
        // Keep analysis progressing when a single condition is ill-typed.
    }
}

void epat::smt::Solver::pushLimit(smt::expr value, smt::expr start, smt::expr end)
{
    auto is_orderable = [](const z3::sort& s) {
        return s.is_bv() || s.is_int() || s.is_real() || s.is_fpa();
    };
    try {
        auto sv = value.get_sort();
        auto ss = start.get_sort();
        auto se = end.get_sort();
        if (!is_orderable(sv) || !is_orderable(ss) || !is_orderable(se)) {
            std::cout << "[pushLimit skip] non-orderable sort: "
                      << ss << " , " << sv << " , " << se << std::endl;
            return;
        }
        auto s2 = smt::to_tag(start, sv);
        auto e2 = smt::to_tag(end, sv);
        pushCond((s2 <= value) && (value < e2));
    }
    catch (const z3::exception& e) {
        std::cout << "[pushLimit z3 exception] " << e << std::endl;
    }
    catch (...) {
        std::cout << "[pushLimit exception] unknown failure while building range constraint"
                  << std::endl;
    }
}
