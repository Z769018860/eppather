#ifndef TOOL_DEBUG_H
#define TOOL_DEBUG_H

#include <string>

#ifdef __linux__
  #define __my_cdecl
#else
  #define __my_cdecl __cdecl
#endif

#ifdef _DEBUG
constexpr bool _debug1 = true;
#else
constexpr bool _debug1 = false;
#endif

constexpr bool _debug = false;

namespace z3 {
    class ast;
}

namespace tool {
    class Node;
    class Debug {
    public:
        Debug(const char _File[], unsigned int _Line);

        Debug& operator<<(int i);
        Debug& operator<<(const std::string& str);
        Debug& operator<<(const void* ptr);
        Debug& operator<<(const char* str);
        Debug& operator<<(Debug& (__my_cdecl* fn)(Debug&));
        Debug& operator<<(z3::ast const& n);
        Debug& operator<<(Node& e);
    };

    Debug& __my_cdecl endL(Debug& D);
};

// std::ostream& operator<<(std::ostream& os, tool::Debug& (__cdecl* fn)(tool::Debug&));

#ifndef debug
  #define debug tool::Debug(__FILE__, __LINE__)
#endif // !debug

#endif // !TOOL_DEBUG_H