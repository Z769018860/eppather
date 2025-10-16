// solver.h: 头文件
// 定义了求解器接口类
#pragma once
#ifndef _EPAT_SOLVER_H_
#define _EPAT_SOLVER_H_
#include "stmt.h"
#include <iostream>
#include <memory>

namespace epat {
    /**
     * @brief 分析结果的枚举
     * 枚举类result，用于表示工具的分析结果
     */
    enum class result : char {
        feasible,
        infeasible,
        unknown
    };

    inline std::ostream& operator<<(std::ostream& os, result res)
    {
        switch (res) {
        case epat::result::feasible:
            return os << "feasible";
        case epat::result::infeasible:
            return os << "infeasible";
        case epat::result::unknown:
            return os << "unknown";
        default:
            return os << "undefined";
        }
    }

    /**
     * @brief 求解器类
     * 用于求解的类，提供了功能所需的接口。在求解前需要用create方法创建一个Solver对象。
     */
    class Solver {
    public:
        using ptr = std::unique_ptr<Solver>;
    protected:
        /**
         * @brief Solver的构造函数
         * 保护的构造函数，创建Solver对象请使用@ref create "create"方法
         */
        explicit Solver();
    public:
        /**
         * @brief Solver的析构函数
         */
        virtual ~Solver() = 0;
        /**
         * @brief Solver的工厂函数
         * 用此方法创建Solver对象
         * @param Ast 语法树根节点的智能指针
         */
        static ptr create(const epat::Root::ptr Ast);
        /**
         * @brief 分析路径可行性。
         * @note 需要先读取路径再调用该函数。
         * @see parseStream parseString parseFile
         * @return 路径可行与否
         *	@retval false 不可行
         *	@retval	true  可行
         */
        virtual result feasible();
        /**
         * @brief 打印可行的初始输入
         * @note 输出为SMT2格式。使用前需要先调用\ref feasible。
         * @see feasible
         * @param os 输出流，默认为标准输出流
         */
        virtual void printModel(std::ostream& os = std::cout) const;
        /**
         * @brief 获取可行的初始输入
         * @note 返回为SMT2格式。使用前需要先调用\ref feasible。
         * @see feasible
         * @return 表示输入的SMT2格式字符串
         */
        virtual std::string getModel() const;
        /**
         * @brief 打印可行输入的解空间
         * @note 需要先调用\ref feasible。
         * @see feasible
         * @param os 输出流，默认为标准输出流
         */
        virtual void printSMT2(std::ostream& os = std::cout) const;
        /**
         * @brief 获取可行输入的解空间
         * @note 需要先调用\ref feasible。
         * @see feasible
         * @return 表示输入解空间的SMT2格式字符串
         */
        virtual std::string getSMT2() const;
        /**
         * @brief 打印数组访存次数
         * @param os 输出流，默认为标准输出
         */
        virtual void printMem(std::ostream& os = std::cout) const;
        /**
         * @brief 获取数组访存次数
         * @return 数组访存次数
         */
        virtual int getMem() const;
    };
}

#endif // !_EPAT_SOLVER_H_
