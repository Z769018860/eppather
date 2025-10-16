// scope_guard.h: 头文件
// 定义了Scope卫兵
#pragma once
#ifndef _EPAT_SCOPE_GUARD_H_
#define _EPAT_SCOPE_GUARD_H_
#include "debug.h"
#include <vector>

namespace epat {
    template <typename Enter_, typename Exit_> class ScopeGuard {
        Enter_ enter_;
        Exit_ exit_;
        bool released_ = false;
    public:
        explicit ScopeGuard(Enter_ enter, Exit_ exit) : enter_(enter), exit_(exit)
        {
            enter_();
        }
        ~ScopeGuard()
        {
            if (!released_)
                exit_();
        }
        void release()
        {
            if (!released_) {
                released_ = true;
                exit_();
            }
        }
    };
}

#endif // !_EPAT_SCOPE_GUARD_H_
