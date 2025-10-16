#ifndef TOOL_SCANNER_H
#define TOOL_SCANNER_H

#ifndef YY_DECL
#define YY_DECL \
    tool::Parser::symbol_type \
    tool::Scanner::lex( \
        class Driver &drv \
    )
#endif // !YY_DECL

#ifndef __FLEX_LEXER_H
#define yyFlexLexer ToolFlexLexer
#include "FlexLexer.h"
#undef yyFlexLexer
#endif // !__FLEX_LEXER_H

#include "parser.h"

using namespace std;

namespace tool {

    class Scanner : public ToolFlexLexer
    {
    public:
        Scanner(istream* arg_yyin = nullptr, ostream* arg_yyout = nullptr);
        virtual ~Scanner();

        virtual Parser::symbol_type lex(
            Driver& drv
        );

        void set_debug(bool debug);
    };

}

#endif // !TOOL_SCANNER_H
