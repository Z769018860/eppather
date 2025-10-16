// debug.h: 头文件
// 定义了debug工具
#pragma once
#ifndef _EPAT_DEBUG_H_
#define _EPAT_DEBUG_H_
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace epat {
    namespace debug {
        enum class kind : char {
            assertion,
            error,
            warning,
            log,
            undefined,
        };
        class solver_error : public std::exception {
            std::string msg_;
        public:
            explicit solver_error(char const* const _Message) noexcept
                : std::exception(), msg_(_Message)
            {
            }

            virtual const char* what() const noexcept { return msg_.c_str(); }
        };
        std::ostream& get_log_file();
        template <typename T, typename... Args>
        void _msg(std::ostream& os, T&& first, Args&&... args)
        {
            os << first;
            if constexpr (sizeof...(args) > 0)
                _msg(os, std::forward<Args>(args)...);
            else
                os << std::endl;
        }
        inline void _msg(std::ostream& os)
        {
            os << std::endl;
        }
        template <kind kd, typename... Args> void msg(Args&&... args)
        {
            if constexpr (kind::log == kd)
                _msg(get_log_file(), std::forward<Args>(args)...);
            else if constexpr (kind::warning == kd)
                _msg(std::cout, "Warning: ", std::forward<Args>(args)...);
            else
                // stupid gcc!!!
                // static_assert(false, "invalid kind for msg");
                (void)(0);
        }
        template <kind kd, typename... Args>
        solver_error error(char const* file, unsigned line, Args&&... args)
        {
            std::ostringstream oss;
            if constexpr (kind::error == kd)
                oss << "Error: ";
            else if constexpr (kind::assertion == kd)
                oss << "Assertion failed: ";
            else
                // stupid gcc!!!
                // static_assert(false, "invalid kind for error");
                (void)(0);
            _msg(oss, std::forward<Args>(args)..., ", file: ", file, ", line: ", line);
            return solver_error(oss.str().c_str());
        }
    }
#ifndef EPAT_DEBUG
// #define EPAT_DEBUG
#endif
#ifndef EPAT_LOG
// #define EPAT_LOG
#endif

// error总是生效，warning和assert在debug时生效，log在log时生效
#define epat_msg(kd, ...) (epat::debug::msg<kd>(__VA_ARGS__))
#define _epat_error(kd, ...)                                                             \
    (throw epat::debug::error<kd>((__FILE__), (__LINE__), __VA_ARGS__))
#define epat_error(...) (_epat_error(epat::debug::kind::error, __VA_ARGS__))

#ifdef EPAT_DEBUG
#define epat_warning(...) (epat_msg(epat::debug::kind::warning, __VA_ARGS__))
#define epat_assert(expression)                                                          \
    (void)((!!(expression)) ||                                                           \
           (_epat_error(epat::debug::kind::assertion, #expression), 0))
#else
#define epat_warning(...) ((void)0)
#define epat_assert(expression) ((void)0)
#endif
#ifdef EPAT_LOG
#define epat_log(...) (epat_msg(epat::debug::kind::log, __VA_ARGS__))
#else
#define epat_log(...) ((void)0)
#endif

    // #undef EPAT_DEBUG
    // #undef EPAT_LOG
}

#endif // !_EPAT_DEBUG_H_
