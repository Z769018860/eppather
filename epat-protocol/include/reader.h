// parser.h: 头文件
// 定义了语法分析器
#pragma once
#ifndef _EPAT_PARSER_H_
#define _EPAT_PARSER_H_
#include "stmt.h"
#include <istream>
#include <string>

namespace epat {
    class Reader {
    public:
        explicit Reader(std::istream& in);
        explicit Reader(const std::string& in);

        CompoundStmt::ptr getRoot();
    private:
        CompoundStmt::ptr root;
    };
}

#endif // !_EPAT_PARSER_H_
