// reader.h: 头文件
// 定义了语法分析器
#pragma once
#ifndef _EPAT_READER_H_
#define _EPAT_READER_H_
#include "stmt.h"
#include <istream>
#include <string>

namespace epat {
    class Reader {
    public:
        explicit Reader(std::istream& in);
        explicit Reader(const std::string& in);
        static Root::ptr fromString(const std::string& input)
        {
            Reader reader(input);
            return reader.getRoot();
        }
        static Root::ptr fromStream(std::istream& in)
        {
            Reader reader(in);
            return reader.getRoot();
        }

        Root::ptr getRoot();
        inline bool isValid() const { return valid; }
    private:
        Root::ptr root;
        bool valid;
    };
}

#endif // !_EPAT_READER_H_
