#ifndef TOOL_EXCEPTION_H
#define TOOL_EXCEPTION_H

#include <exception>
#include <string>

#ifdef __linux__
  #ifndef __my_cdecl
    #define __my_cdecl
  #endif
#else
  #ifndef __my_cdecl
    #define __my_cdecl __cdecl
  #endif
#endif

using namespace std;

class base_expception : public std::exception
{
protected:
    string info;
public:
    base_expception(const string& info);
    const char* what() const throw() override;
};

class debug_exception : public base_expception
{
public:
    debug_exception(const string& info, const char _File[], unsigned int _Line);
};

#ifndef BUG
#define BUG(info) debug_exception((info), (__FILE__), (unsigned)(__LINE__))
#endif // !BUG

class parser_exception : public base_expception
{
public:
    parser_exception(const string& info);
};

class no_type_exception : public parser_exception
{
public:
    no_type_exception(const string& name);
};

class no_decl_exception : public parser_exception
{
public:
    no_decl_exception(const string& name);
};

class not_value_exception : public parser_exception
{
public:
    not_value_exception(const string& name);
};

namespace tool {
    enum class result;
}

class feasibility_exception : public std::exception
{
    tool::result res;
public:
    feasibility_exception(tool::result res);
    tool::result get_result() const;

    const char* what() const throw() override;
};

#endif // !TOOL_EXCEPTION_H