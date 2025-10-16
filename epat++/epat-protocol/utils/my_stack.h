// my_stack.h: 头文件
// 定义了特制的栈数据结构
#pragma once
#ifndef _EPAT_MY_STACK_H_
#define _EPAT_MY_STACK_H_
#include "debug.h"
#include <vector>

namespace epat {
    // 仅能储存可移动对象
    template <typename _Ty> class MyStack {
        std::vector<_Ty> content_;
    public:
        inline _Ty& top() { return content_.back(); }
        inline _Ty& push(_Ty ctt)
        {
            content_.push_back(std::move(ctt));
            return top();
        }
        inline _Ty& push() { return push(_Ty()); }
        inline _Ty pop()
        {
            epat_assert(size() > 0);
            auto res = std::move(top());
            content_.pop_back();
            return res;
        }
        inline std::vector<_Ty> pop_from(int pos)
        {
            epat_assert(pos >= 0 && pos < (int)content_.size());
            std::vector<_Ty> ret(std::make_move_iterator(content_.begin() + pos),
                                 std::make_move_iterator(content_.end()));
            content_.erase(content_.begin() + pos, content_.end());
            return ret;
        }
        inline int size() const { return (int)content_.size(); }
        inline bool empty() const { return size() == 0; }
    };
}

#endif // !_EPAT_MY_STACK_H_
