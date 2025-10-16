// smt_expr.h: 头文件
// 定义了符号表达式类
#pragma once
#ifndef _EPAT_SMT_EXPR_H_
#define _EPAT_SMT_EXPR_H_
#include "debug.h"
#include "type.h"
#include "z3++.h"
#include <memory>
#include <ostream>
#include <string>
#include <vector>

namespace epat {
    inline z3::context gc = z3::context(); // TODO: 新的求解前清理gc
    struct z3_expr_less {
        bool operator()(z3::expr const& lhs, z3::expr const& rhs) const
        {
            return lhs.id() < rhs.id();
        }
    };
    constexpr inline int sizeof_int = 4; // XXX: uint会导致z3::expr除法歧义
    constexpr inline unsigned int width = 32;
    // inline auto _1 = gc.int_val(1);
    inline auto _0 = gc.bv_val(0, width);
    // inline auto _0 = gc.int_val(0);
    inline auto _1 = gc.bv_val(1, width);
    inline auto _true = gc.bool_val(true);
    inline auto _false = gc.bool_val(false);

    namespace smt {
        using expr = z3::expr;
        using sort = z3::sort;
        enum class result {
            sat,
            unsat,
            unknown
        };
        inline expr to_bool(expr const& e)
        {
            return e.is_bool() ? e : e != 0;
        }
        inline expr to_bv(expr const& e, int w = width)
        {
            if (e.is_bv())
                return e;
            if (e.is_int())
                return z3::int2bv(w, e);
            if (e.is_fpa())
                return z3::fpa_to_sbv(e, width);
            return e;
        }
        expr to_tag(expr const& e, sort const& tag);
        sort type2sort(QualType const& qt);
        inline expr bool2int(expr const& e)
        {
            if (e.is_bool())
                return z3::ite(e, _1, _0);
            return e;
        }
    }
}

// 我实现的smt封装，暂时遗弃
// namespace epat {
//     namespace smt {
//         // class ctx;
//         using sort = std::string;
//         class expr;
//         class expr_base {
//         public:
//             virtual ~expr_base() = default;

//             virtual std::string to_string(bool expand = false) const = 0;
//             virtual bool is_app() const { return false; }
//             virtual bool is_bool() const { return false; }
//             virtual bool is_int() const { return false; }
//             virtual bool is_var() const { return false; }
//             virtual bool is_bool_sort() const { return false; }
//             // virtual bool is_int_sort() const { return false; }
//         protected:
//             expr_base() = default;
//             expr_base(const expr_base&) = delete;
//         };

//         class app;
//         class expr {
//         public:
//         protected:
//             std::shared_ptr<expr_base> e_;
//             explicit expr(expr_base* e) : e_(e) {}
//         public:
//             explicit expr() = default;
//             expr(expr const& other) = default;
//             expr(expr&& other) = default;
//             expr& operator=(expr const& other) = default;
//             expr& operator=(expr&& other) = default;
//             operator bool() const { return e_.operator bool(); }
//             bool eq(expr const& other) const { return e_ == other.e_; }
//             struct less {
//                 bool operator()(const expr& e1, const expr& e2) const
//                 {
//                     return e1.e_ < e2.e_;
//                 };
//             };
//             ~expr() = default;

//             // static expr mk_app(func func, std::vector<expr> args);
//             static expr mk_app(std::string func, std::vector<expr> args);
//             static expr mk_bool(bool value);
//             static expr mk_int(int value);
//             static expr mk_const(std::string name);

//             bool is_app() const { return e_ && e_->is_app(); }
//             bool is_bool() const { return e_ && e_->is_bool(); }
//             bool is_int() const { return e_ && e_->is_int(); }
//             bool is_var() const { return e_ && e_->is_var(); }
//             bool is_bool_sort() const { return e_ && e_->is_bool_sort(); }
//             // bool is_int_sort() const { return e_ && e_->is_int_sort(); }

//             const app& to_app() const;
//             int get_int() const;
//             std::string get_func() const;
//             int get_arg_num() const;
//             expr const& get_arg(int pos) const;

// #define DEFINE_SMT_OP(op, func)                                                          \
//     expr& operator op##=(expr const& other)                                              \
//     {                                                                                    \
//         *this = mk_app(func, {std::move(*this), other});                                 \
//         return *this;                                                                    \
//     }                                                                                    \
//     friend expr operator op(expr const& lhs, expr const& rhs)                            \
//     {                                                                                    \
//         return expr(lhs) op## = rhs;                                                     \
//     }                                                                                    \
//     friend expr operator op(int lhs, expr const& rhs)                                    \
//     {                                                                                    \
//         return mk_int(lhs) op rhs;                                                       \
//     }                                                                                    \
//     friend expr operator op(expr const& lhs, int rhs)                                    \
//     {                                                                                    \
//         return lhs op mk_int(rhs);                                                       \
//     }

//             DEFINE_SMT_OP(+, "+")
//             DEFINE_SMT_OP(-, "-")
//             DEFINE_SMT_OP(*, "*")
//             DEFINE_SMT_OP(/, "/")
// #undef DEFINE_SMT_OP

// #define DEFINE_SMT_OP2(op, func)                                                         \
//     friend expr operator op(expr const& lhs, expr const& rhs)                            \
//     {                                                                                    \
//         return mk_app(func, {lhs, rhs});                                                 \
//     }                                                                                    \
//     friend expr operator op(expr const& lhs, int rhs)                                    \
//     {                                                                                    \
//         return lhs op mk_int(rhs);                                                       \
//     }                                                                                    \
//     friend expr operator op(int lhs, expr const& rhs)                                    \
//     {                                                                                    \
//         return mk_int(lhs) op rhs;                                                       \
//     }

//             DEFINE_SMT_OP2(<, "<")
//             DEFINE_SMT_OP2(<=, "<=")
//             DEFINE_SMT_OP2(>, ">")
//             DEFINE_SMT_OP2(>=, ">=")
//             DEFINE_SMT_OP2(==, "=")
//             DEFINE_SMT_OP2(!=, "distinct")
// #undef DEFINE_SMT_OP2

//             expr operator-() const { return mk_app("-", {*this}); }
//             expr operator!() const { return mk_app("not", {*this}); }
//             expr operator&&(expr other) const { return mk_app("and", {*this, other}); }
//             expr select(expr pos) const
//             {
//                 return mk_app("select", {*this, std::move(pos)});
//             }
//             expr store(expr pos, expr value) const
//             {
//                 return mk_app("store", {*this, std::move(pos), std::move(value)});
//             }

//             std::string to_string(bool expand = false) const;

//             friend std::ostream& operator<<(std::ostream& os, expr const& expr)
//             {
//                 return os << expr.to_string();
//             }
//         };

//         class var : public expr_base {
//             friend class expr;
//         protected:
//             std::string name_;
//             explicit var(std::string name);
//         public:
//             virtual std::string to_string(bool expand = false) const override;
//             virtual bool is_var() const override { return true; }
//         };

//         class vint : public expr_base {
//             friend class expr;
//         protected:
//             int v_;
//             explicit vint(int value);
//         public:
//             virtual std::string to_string(bool expand = false) const override;
//             virtual bool is_int() const override { return true; }
//         };

//         class vbool : public expr_base {
//             friend class expr;
//         protected:
//             bool v_;
//             explicit vbool(bool value);
//         public:
//             virtual std::string to_string(bool expand = false) const override;
//             virtual bool is_bool() const override { return true; }
//             virtual bool is_bool_sort() const override { return true; }
//         };

//         class app : public expr_base {
//             friend class expr;
//         protected:
//             std::string func_;
//             std::vector<expr> args_;
//             // explicit app(func func, std::vector<expr> args);
//             explicit app(std::string func, std::vector<expr> args);
//         public:
//             virtual std::string to_string(bool expand = false) const override;
//             virtual bool is_app() const override { return true; }
//             virtual bool is_bool_sort() const override;
//         };

//         inline const smt::expr _1 = smt::expr::mk_int(1);
//         inline const smt::expr _0 = smt::expr::mk_int(0);
//         inline const smt::expr _false = smt::expr::mk_bool(false);
//         inline const smt::expr _true = smt::expr::mk_bool(true);
//     };
// }

#endif // !_EPAT_SMT_EXPR_H_
