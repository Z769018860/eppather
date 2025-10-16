// mem_visitor.h: 头文件
// 定义了mem遍历类
#pragma once
#ifndef _EPAT_MEM_VISITOR_H_
#define _EPAT_MEM_VISITOR_H_
#include "visitor.h"

namespace epat {
    class MemVisitor : public epat::Visitor {
    public:
        static int getMem(const Block& ast)
        {
            MemVisitor mv;
            mv.visit(ast);
            return mv.mem_;
        }
    private:
        int mem_ = 0;
        // 访问函数
        virtual void processArraySubscript(const epat::ArraySubscript& ary) override
        {
            ++mem_;
        }
    };
}

#endif // !_EPAT_MEM_VISITOR_H_
