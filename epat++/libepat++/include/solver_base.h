// solver_base.h: 头文件
// 定义了求解器类的基类
#pragma once
#ifndef _EPAT_SOLVER_BASE_H_
#define _EPAT_SOLVER_BASE_H_
#include "memory_model.h"
#include "smt_solver.h"
#include "solver.h"
#include "visitor.h"
#include <sstream>

namespace epat {
    template <typename Lv> class SolverBase : public epat::Visitor {
    protected:
        static inline std::string
            default_model_ = "no model available. use feasible() before getModel().",
            default_smt2_ = "; an empty smt2 string.";
        CompoundStmt const& ast_;
        using MD = MemoryBase<Lv>;
        using lv = typename MD::lv;
        using rv = typename MD::rv;
        MD mem_;
        struct ModelVarInfo {
            std::string decl;
        };
        std::map<std::string, ModelVarInfo> model_var_map_;
        void registerModelVar(const std::string& name, std::string decl)
        {
            model_var_map_.insert_or_assign(name, ModelVarInfo{std::move(decl)});
        }
        // TODO: tmp code!!!
        // SMTSolver smt_;
        smt::Solver smt_;
    public:
        explicit SolverBase(CompoundStmt const& ast) : ast_(ast) {}
        virtual result feasible()
        {
            try {
                visit(ast_);
                switch (smt_.solve()) {
                case smt::result::sat:
                    return result::feasible;
                case smt::result::unsat:
                    return result::infeasible;
                case smt::result::unknown:
                default:
                    return result::unknown;
                }
            }
            catch (std::exception& e) {
                std::cout << e.what() << std::endl;
                return result::unknown;
            }
        }
        virtual std::string getModel()
        {
            auto model = smt_.getModel();
            if (model_var_map_.empty())
                return model;
            std::istringstream iss(model);
            std::ostringstream oss;
            std::string line;
            while (std::getline(iss, line)) {
                if (line.empty())
                    continue;
                auto pos = line.find(" = ");
                if (pos == std::string::npos)
                    continue;
                auto name = line.substr(0, pos);
                auto value = line.substr(pos + 3);
                auto it = model_var_map_.find(name);
                if (it == model_var_map_.end())
                    continue;
                oss << it->second.decl << " = " << value << '\n';
            }
            return oss.str();
        }
        virtual std::string getSMT2() { return smt_.getSMT2(); }
        // std::ostringstream& smt() { return smtsolver_.oss(); }

        // 为每个vardecl分配一个独特的名称
        std::map<void*, int> uid_map_;
        std::map<std::string, int> name_record_map_;
        std::string getUniqueName(ValueDecl const& vard)
        {
            auto name = vard.getName();
            auto key = (void*)&vard;
            auto i = uid_map_.find(key);
            if (i != uid_map_.end())
                return name + "@" + std::to_string(i->second);
            auto j = name_record_map_.find(name);
            if (j != name_record_map_.end()) {
                ++j->second;
                uid_map_[key] = j->second;
                return name + "@" + std::to_string(j->second);
            }
            uid_map_[key] = 0;
            name_record_map_[name] = 0;
            return name + "@0";
        }
    };

    // template <typename MemoryModel> class SolverBase : public epat::Visitor {
    // protected:
    //     inline static std::string
    //         default_model_ = "; no model available. use feasible() before getModel().",
    //         default_smt2_ = "; no smtlib2 available. use feasible() before getSMT2().";
    //     const Root& ast_;
    //     SMTSolver smtsolver_;
    //     MemoryModel::ptr memory_;
    //     using lvalue = smt::expr;
    //     MyStack<lvalue> lv_stack_;
    //     MyStack<rvalue> rv_stack_;
    // public:
    //     SolverBase(const Root& ast);
    //     virtual ~SolverBase();

    //     virtual result feasible();
    //     virtual std::string getModel();
    //     virtual std::string getSMT2();
    //     std::ostringstream& smt() { return smtsolver_.oss(); }

    //     // define and declare
    //     void pushConst(const std::string& name, smt::sort sort,
    //                    smt::expr init = smt::expr());
    //     void pushConst(smt::expr var, smt::expr init = smt::expr());
    //     // assert
    //     void pushCond(smt::expr cond);
    //     void pushLimit(smt::expr value, smt::expr start, smt::expr end);

    //     // utils
    //     using type_size = MemoryBase::rvalue;
    //     using type_size_map = std::map<Type*, type_size>;
    //     type_size_map type_size_map_; // for caching
    //     type_size getTypeSize(const QualType& qt);
    // };
}

#endif // !_EPAT_SOLVER_BASE_H_
