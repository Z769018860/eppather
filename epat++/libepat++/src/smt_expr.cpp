#include "smt_expr.h"
#include "debug.h"
#include <map>

namespace epat {
    namespace smt {
        expr to_tag(expr const& e, sort const& tag)
        {
            // XXX: 所有bv均为width长度，未来可能出问题
            auto src = e.get_sort();
            if (src.id() == tag.id())
                return e;
            if (src.is_bv()) {
                if (tag.is_int())
                    return z3::bv2int(e, true);
                if (tag.is_fpa())
                    return z3::sbv_to_fpa(e, tag);
            }
            if (tag.is_bv()) {
                if (src.is_int())
                    return z3::int2bv(width, e);
                if (src.is_fpa())
                    return z3::fpa_to_sbv(e, width);
            }
            epat_warning("unknown sort conversion: " + src.to_string() + " -> " +
                         tag.to_string());
            return e; // XXX: 是否直接报错？
        }

        sort type2sort(QualType const& qt)
        {
            // TODO: int2bv和bv2int互转产生问题，暂时先用bv
            // TODO: 有些求解方案中可能需要int
            switch (qt->getKind()) {
            case Type::TypeKind::Base: {
                std::map<std::string, sort> base2sort;
                if (base2sort.empty())
                    base2sort = {
                        {"bool", gc.bv_sort(width)},     {"int", gc.bv_sort(width)},
                        {"char", gc.bv_sort(width)},     {"long", gc.bv_sort(width)},
                        {"float", gc.fpa_sort<width>()},
                    };
                auto i = base2sort.find(qt->getCode());
                // XXX: 处理类型修饰符
                if (i != base2sort.end())
                    return i->second;
                epat_error("unsupported type for sort: " + qt.getCode());
                return gc.bv_sort(width);
            }
            case Type::TypeKind::Array:
                // 路径约束里数组对象通常以“地址/索引访问”出现；
                // 将数组整体退化为位向量，避免抛出 unsupported type for sort: int [N]
                // 导致 DFS 在可行性判定阶段中断。
                return gc.bv_sort(width);
            case Type::TypeKind::Pointer:
                return gc.bv_sort(width); // XXX: 32位指针
            case Type::TypeKind::Typedef:
                // typedef 直接沿用底层元素类型；若无法展开则退化为位向量
                if (auto elem = qt.getElement()) {
                    return type2sort(elem);
                }
                return gc.bv_sort(width);
            case Type::TypeKind::Struct:
            case Type::TypeKind::Function:
                // 当前求解器对结构体/函数不做精细建模，统一按位向量保守处理
                return gc.bv_sort(width);
            default:
                epat_error("unsupported type for sort: " + qt.getCode());
                return gc.bv_sort(width);
            }
        }
    }
}

// constexpr bool simplify = true;

// epat::smt::expr epat::smt::expr::mk_app(std::string func, std::vector<expr> args)
// {
//     if constexpr (simplify) {
//         std::map<std::string, std::function<expr(std::vector<expr>)>> strategy = {
//             {"+",
//              [](std::vector<expr> args) {
//                  int ret_c = 0;
//                  std::vector<expr> ret_args;
//                  std::function<void(expr)> do_add;
//                  do_add = [&](expr e) {
//                      if (e.is_int())
//                          ret_c += e.get_int();
//                      else if (e.is_app() && "+" == e.get_func()) {
//                          for (int i = 0, n = e.get_arg_num(); i < n; i++)
//                              do_add(e.get_arg(i));
//                      }
//                      else
//                          ret_args.push_back(e);
//                  };
//                  for (auto arg : args)
//                      do_add(arg);
//                  ret_args.push_back(mk_int(ret_c));
//                  if (ret_args.size() == 1)
//                      return ret_args[0];
//                  return expr(new epat::smt::app("+", std::move(ret_args)));
//              }},
//             {"*",
//              [](std::vector<expr> args) {
//                  int ret_k = 1;
//                  std::vector<expr> ret_args;
//                  std::function<void(expr)> do_mul;
//                  do_mul = [&](expr e) {
//                      if (e.is_int())
//                          ret_k *= e.get_int();
//                      else if (e.is_app() && "*" == e.get_func()) {
//                          for (int i = 0, n = e.get_arg_num(); i < n; i++)
//                              do_mul(e.get_arg(i));
//                      }
//                      else
//                          ret_args.push_back(e);
//                  };
//                  for (auto arg : args)
//                      do_mul(arg);
//                  if (ret_k == 0)
//                      return mk_int(0);
//                  if (ret_k != 1)
//                      ret_args.push_back(mk_int(ret_k));
//                  if (ret_args.size() == 1)
//                      return ret_args[0];
//                  return expr(new epat::smt::app("*", std::move(ret_args)));
//              }},
//         };
//         auto i = strategy.find(func);
//         if (i != strategy.end())
//             return i->second(std::move(args));
//     }
//     return expr(new epat::smt::app(std::move(func), std::move(args)));
// }

// epat::smt::expr epat::smt::expr::mk_int(int value)
// {
//     return expr(new epat::smt::vint(value));
// }

// epat::smt::expr epat::smt::expr::mk_bool(bool value)
// {
//     return expr(new epat::smt::vbool(value));
// }

// epat::smt::expr epat::smt::expr::mk_const(std::string name)
// {
//     return expr(new epat::smt::var(name));
// }

// const epat::smt::app& epat::smt::expr::to_app() const
// {
//     return static_cast<const app&>(*e_);
// }

// int epat::smt::expr::get_int() const
// {
//     if (!is_int())
//         return 0;
//     auto& i = static_cast<const vint&>(*e_);
//     return i.v_;
// }

// std::string epat::smt::expr::get_func() const
// {
//     epat_assert(is_app());
//     auto& a = static_cast<const app&>(*e_);
//     return a.func_;
// }

// int epat::smt::expr::get_arg_num() const
// {
//     epat_assert(is_app());
//     auto& a = static_cast<const app&>(*e_);
//     return (int)a.args_.size();
// }

// epat::smt::expr const& epat::smt::expr::get_arg(int pos) const
// {
//     epat_assert(is_app());
//     auto& a = static_cast<const app&>(*e_);
//     return a.args_[pos];
// }

// std::string epat::smt::expr::to_string(bool expand) const
// {
//     if (e_)
//         return e_->to_string(expand);
//     return "@error";
// }

// epat::smt::var::var(std::string name) : name_(std::move(name)) {}

// std::string epat::smt::var::to_string(bool) const
// {
//     return name_;
// }

// epat::smt::vint::vint(int value) : v_(value) {}

// std::string epat::smt::vint::to_string(bool) const
// {
//     return std::to_string(v_);
// }

// epat::smt::vbool::vbool(bool value) : v_(value) {}

// std::string epat::smt::vbool::to_string(bool) const
// {
//     return v_ ? "true" : "false";
// }

// // epat::smt::app::app(func func, std::vector<expr> args)
// //     : func_(func2Str(func)), args_(std::move(args))
// // {
// // }

// epat::smt::app::app(std::string func, std::vector<expr> args)
//     : func_(std::move(func)), args_(std::move(args))
// {
// }

// std::string epat::smt::app::to_string(bool expand) const
// {
//     // XXX: expand
//     std::stringstream ss;
//     ss << "(" << func_;
//     for (auto& arg : args_)
//         ss << " " << arg;
//     ss << ")";
//     return ss.str();
// }

// bool epat::smt::app::is_bool_sort() const
// {
//     static std::set<std::string> bools = {
//         ">", "<", ">=", "<=", "=", "distinct", "and", "or", "xor", "=>", "not",
//     };
//     return bools.find(func_) != bools.end();
// }
