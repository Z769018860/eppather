#include <iostream>
#include <string>
#ifdef __linux
  #include <string.h>
  #define filename(x) (strrchr(x,'/')?strrchr(x,'/')+1:x)
#else
  #include <comdef.h>
  #define filename(x) (strrchr(x,'\\')?strrchr(x,'\\')+1:x)
#endif

#include "debug.h"
#include "expression.h"
#include "z3++.h"

using namespace tool;
using namespace std;

tool::Debug::Debug(const char _File[], unsigned int _Line)
{
    if (_debug)
        cout << "#" << _Line << "@" << filename(_File) << ": ";
}

Debug& tool::Debug::operator<<(int i)
{
    if (_debug)
        cout << i;
    return *this;
}

Debug& tool::Debug::operator<<(const string& str)
{
    if (_debug)
        cout << str;
    return *this;
}

Debug& tool::Debug::operator<<(const void* ptr)
{
    if (_debug)
        cout << ptr;
    return *this;
}

Debug& tool::Debug::operator<<(const char* str)
{
    if (_debug)
        cout << str;
    return *this;
}

Debug& tool::Debug::operator<<(Debug& (__my_cdecl* fn)(Debug&))
{
    return fn(*this);
}

Debug& tool::Debug::operator<<(z3::ast const& n)
{
    if (_debug)
        cout << n;
    return *this;
}

Debug& tool::Debug::operator<<(Node& e)
{
    if (_debug)
        cout << e;
    return *this;
}

Debug& __my_cdecl tool::endL(Debug& D)
{
    if (_debug)
        cout << std::endl;
    return D;
}
