// writer.h: 头文件
// 定义了writer
#pragma once
#ifndef _EPAT_WRITER_H_
#define _EPAT_WRITER_H_
#include "stmt.h"
#include "visitor.h"
#include <ostream>
#include <string>

namespace epat {
    template <typename T> struct is_std_vector : std::false_type {};

    template <typename T> struct is_std_vector<std::vector<T>> : std::true_type {};

    template <typename T> bool is_empty(const T& arg)
    {
        if constexpr (is_std_vector<T>::value)
            return arg.empty();
        else
            return false;
    }

    template <typename... T> bool is_empty_tree(const T&... args)
    {
        if constexpr (sizeof...(T) == 0)
            return true;
        else
            return (is_empty(args) && ...);
    }

    template <class T>
    void print_item(std::ostream& os, const std::string& prefix, const T& arg,
                    bool last = false)
    {
        if constexpr (is_std_vector<T>::value) {
            for (size_t i = 0, n = arg.size(); i < n; ++i)
                print_item(os, prefix, arg[i], last && (i == n - 1));
        }
        else {
            os << std::endl;
            if constexpr (std::is_same_v<T, epat::QualType>)
                arg.printAst(os, prefix + (last ? "`-" : "|-"));
            else {
                // 不是vector，也不是QualType，应该是智能指针
                if (arg)
                    arg->printAst(os, prefix + (last ? "`-" : "|-"));
                else
                    os << prefix + (last ? "`-" : "|-") << "<<<NULL>>";
            }
        }
    }

    template <typename T1, typename... T>
    void _print_tree(std::ostream& os, const std::string& prefix, const T1& arg1,
                     const T&... args)
    {
        print_item(os, prefix, arg1, is_empty_tree(args...));
        if constexpr (sizeof...(T) > 0)
            _print_tree(os, prefix, args...);
    }

    template <typename... T>
    void print_tree(std::ostream& os, const std::string& prefix, const T&... args)
    {
        auto str = prefix;
        if (auto len = str.size(); len > 1) {
            str[len - 1] = ' ';
            if (str[len - 2] == '`')
                str[len - 2] = ' ';
        }
        _print_tree(os, str, args...);
    }

#define SPACES (std::string(indent, ' '))
#define SPACES2 (std::string(indent + 2, ' '))

    // XXX: 检查类型
    // pos -1 表示左，1 表示右
    template <typename T>
    void print_expr(std::ostream& os, const T& expr, const Expr* parent, int pos = -1)
    {
        if (!expr) {
            std::cout << "$error" << std::endl;
            return;
        }
        if (!parent) {
            expr->printCode(os);
            return;
        }
        auto parentheses = false;
        auto diff = expr->getOpPrec() - parent->getOpPrec();
        if (diff > 0) // 优先级低于父亲
            parentheses = true;
        else if (diff == 0) { // 优先级等于父亲
            if (expr->isRightAssoc() && pos == -1)
                parentheses = true;
            else if (!expr->isRightAssoc() && pos == 1)
                parentheses = true;
        }
        if (parentheses)
            os << "(";
        expr->printCode(os);
        if (parentheses)
            os << ")";
    }
}

#endif // !_EPAT_WRITER_H_
