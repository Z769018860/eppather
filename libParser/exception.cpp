#ifdef __linux
#include <string.h>
#define filename(x) (strrchr((x),'/')?strrchr((x),'/')+1:(x))
#else
#include <comdef.h>
#define filename(x) (strrchr((x),'\\')?strrchr((x),'\\')+1:(x))
#endif

#include "exception.h"
#include "solver.h"

base_expception::base_expception(const string& info)
    : info(info)
{
}

const char* base_expception::what() const throw()
{
    return info.c_str();
}

debug_exception::debug_exception(const string& info, const char _File[], unsigned int _Line)
    : base_expception('#' + to_string(_Line) + '@' + filename((char*)_File) + ": 发生了预期外的错误 ———— " + info)
{
}

parser_exception::parser_exception(const string& info)
    : base_expception(info)
{}

no_type_exception::no_type_exception(const string& name)
    : parser_exception(string("we have no type named \"") + name + string("\""))
{}

no_decl_exception::no_decl_exception(const string& name)
    : parser_exception(string("we have no decl named \"") + name + string("\""))
{}

not_value_exception::not_value_exception(const string& name)
    : parser_exception(string("decl \"") + name + string("\" is not a value"))
{}

feasibility_exception::feasibility_exception(tool::result res)
    : res(res)
{
}

tool::result feasibility_exception::get_result() const
{
    return res;
}

const char* feasibility_exception::what() const throw()
{
    return "It's a feasibility_exception";
}