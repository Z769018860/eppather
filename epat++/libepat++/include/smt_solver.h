// smt_solver.h: 头文件
// 定义了SMT求解器代理类
#pragma once
#ifndef _EPAT_SMT_SOLVER_H_
#define _EPAT_SMT_SOLVER_H_
#include "smt_expr.h"
#include <memory>
#include <sstream>
#include <string>

namespace epat {
    namespace smt {
        class SolverImpl;
        class Solver {
            std::unique_ptr<SolverImpl> impl_;
        public:
            Solver();
            ~Solver();
            result solve();
            std::string getModel();
            std::string getSMT2();

            // std::ostringstream& oss();

            // // define and declare
            // void pushConst(const std::string& name, smt::sort sort,
            //                smt::expr init = smt::expr());
            // void pushConst(smt::expr var, smt::expr init = smt::expr());
            // assert
            void pushCond(smt::expr const& cond);
            void pushLimit(smt::expr value, smt::expr start, smt::expr end);
        };
    }
}

#endif // !_EPAT_C0_SOLVER_H_
