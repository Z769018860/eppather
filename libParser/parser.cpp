// A Bison parser, made by GNU Bison 3.7.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2020 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.


// Take the name prefix into account.
#define yylex   toollex



#include "parser.h"


// Unqualified %code blocks.

#include "driver.h"
#include "scanner.h"

#undef yylex
#define yylex driver.lexer->lex



#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if TOOLDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !TOOLDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !TOOLDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace tool {

  /// Build a parser object.
  Parser::Parser (class Driver &driver_yyarg)
#if TOOLDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      driver (driver_yyarg)
  {}

  Parser::~Parser ()
  {}

  Parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | symbol kinds.  |
  `---------------*/



  // by_state.
  Parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  Parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  Parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  Parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  Parser::symbol_kind_type
  Parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  Parser::stack_symbol_type::stack_symbol_type ()
  {}

  Parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that) noexcept
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_ArraySubscriptExpr: // ArraySubscriptExpr
        value.YY_MOVE_OR_COPY< ArraySubscriptExpr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_BinaryOperator: // BinaryOperator
        value.YY_MOVE_OR_COPY< BinaryOperator* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_CallExpr: // CallExpr
        value.YY_MOVE_OR_COPY< CallExpr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_SingleVarDecl: // SingleVarDecl
        value.YY_MOVE_OR_COPY< Decl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_DeclRefExpr: // DeclRefExpr
        value.YY_MOVE_OR_COPY< DeclRefExpr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_DeclStmt: // DeclStmt
        value.YY_MOVE_OR_COPY< DeclStmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_InitExpr: // InitExpr
      case symbol_kind::S_Expr: // Expr
      case symbol_kind::S_Literal: // Literal
        value.YY_MOVE_OR_COPY< Expr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_InitListExpr: // InitListExpr
        value.YY_MOVE_OR_COPY< InitListExpr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_MemberExpr: // MemberExpr
        value.YY_MOVE_OR_COPY< MemberExpr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_50_1: // @1
      case symbol_kind::S_QualType: // QualType
        value.YY_MOVE_OR_COPY< QualType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_SignStmt: // SignStmt
        value.YY_MOVE_OR_COPY< SignStmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Stmt: // Stmt
      case symbol_kind::S_ReturnStmt: // ReturnStmt
        value.YY_MOVE_OR_COPY< Stmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_StructDecl: // StructDecl
      case symbol_kind::S_75_2: // @2
        value.YY_MOVE_OR_COPY< StructDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TranslationUnitDecl: // TranslationUnitDecl
        value.YY_MOVE_OR_COPY< TranslationUnitDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Type: // Type
        value.YY_MOVE_OR_COPY< Type* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_UnaryOperator: // UnaryOperator
        value.YY_MOVE_OR_COPY< UnaryOperator* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FieldDeclInfo: // FieldDeclInfo
        value.YY_MOVE_OR_COPY< VarDeclInfo > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ArrowOrPeriod: // ArrowOrPeriod
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INTEGER: // "integer"
      case symbol_kind::S_CHAR: // "char"
      case symbol_kind::S_Stars: // Stars
      case symbol_kind::S_ArrayLenth: // ArrayLenth
      case symbol_kind::S_ArgumentList: // ArgumentList
        value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENTIFIER: // "identifier"
      case symbol_kind::S_TYPEID: // "type id"
      case symbol_kind::S_STRING: // "string"
      case symbol_kind::S_VarName: // VarName
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_VarDecl: // VarDecl
      case symbol_kind::S_VarDeclList: // VarDeclList
        value.YY_MOVE_OR_COPY< std::vector<Decl*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ExprList: // ExprList
        value.YY_MOVE_OR_COPY< std::vector<Expr*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FieldDecls: // FieldDecls
      case symbol_kind::S_FieldDecl: // FieldDecl
        value.YY_MOVE_OR_COPY< std::vector<FieldDecl*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FieldDeclInfoList: // FieldDeclInfoList
        value.YY_MOVE_OR_COPY< std::vector<VarDeclInfo> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ArrayLenthList: // ArrayLenthList
        value.YY_MOVE_OR_COPY< std::vector<int> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  Parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_ArraySubscriptExpr: // ArraySubscriptExpr
        value.move< ArraySubscriptExpr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_BinaryOperator: // BinaryOperator
        value.move< BinaryOperator* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_CallExpr: // CallExpr
        value.move< CallExpr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_SingleVarDecl: // SingleVarDecl
        value.move< Decl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_DeclRefExpr: // DeclRefExpr
        value.move< DeclRefExpr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_DeclStmt: // DeclStmt
        value.move< DeclStmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_InitExpr: // InitExpr
      case symbol_kind::S_Expr: // Expr
      case symbol_kind::S_Literal: // Literal
        value.move< Expr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_InitListExpr: // InitListExpr
        value.move< InitListExpr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_MemberExpr: // MemberExpr
        value.move< MemberExpr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_50_1: // @1
      case symbol_kind::S_QualType: // QualType
        value.move< QualType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_SignStmt: // SignStmt
        value.move< SignStmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Stmt: // Stmt
      case symbol_kind::S_ReturnStmt: // ReturnStmt
        value.move< Stmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_StructDecl: // StructDecl
      case symbol_kind::S_75_2: // @2
        value.move< StructDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TranslationUnitDecl: // TranslationUnitDecl
        value.move< TranslationUnitDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Type: // Type
        value.move< Type* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_UnaryOperator: // UnaryOperator
        value.move< UnaryOperator* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FieldDeclInfo: // FieldDeclInfo
        value.move< VarDeclInfo > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ArrowOrPeriod: // ArrowOrPeriod
        value.move< bool > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INTEGER: // "integer"
      case symbol_kind::S_CHAR: // "char"
      case symbol_kind::S_Stars: // Stars
      case symbol_kind::S_ArrayLenth: // ArrayLenth
      case symbol_kind::S_ArgumentList: // ArgumentList
        value.move< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENTIFIER: // "identifier"
      case symbol_kind::S_TYPEID: // "type id"
      case symbol_kind::S_STRING: // "string"
      case symbol_kind::S_VarName: // VarName
        value.move< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_VarDecl: // VarDecl
      case symbol_kind::S_VarDeclList: // VarDeclList
        value.move< std::vector<Decl*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ExprList: // ExprList
        value.move< std::vector<Expr*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FieldDecls: // FieldDecls
      case symbol_kind::S_FieldDecl: // FieldDecl
        value.move< std::vector<FieldDecl*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FieldDeclInfoList: // FieldDeclInfoList
        value.move< std::vector<VarDeclInfo> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ArrayLenthList: // ArrayLenthList
        value.move< std::vector<int> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_ArraySubscriptExpr: // ArraySubscriptExpr
        value.copy< ArraySubscriptExpr* > (that.value);
        break;

      case symbol_kind::S_BinaryOperator: // BinaryOperator
        value.copy< BinaryOperator* > (that.value);
        break;

      case symbol_kind::S_CallExpr: // CallExpr
        value.copy< CallExpr* > (that.value);
        break;

      case symbol_kind::S_SingleVarDecl: // SingleVarDecl
        value.copy< Decl* > (that.value);
        break;

      case symbol_kind::S_DeclRefExpr: // DeclRefExpr
        value.copy< DeclRefExpr* > (that.value);
        break;

      case symbol_kind::S_DeclStmt: // DeclStmt
        value.copy< DeclStmt* > (that.value);
        break;

      case symbol_kind::S_InitExpr: // InitExpr
      case symbol_kind::S_Expr: // Expr
      case symbol_kind::S_Literal: // Literal
        value.copy< Expr* > (that.value);
        break;

      case symbol_kind::S_InitListExpr: // InitListExpr
        value.copy< InitListExpr* > (that.value);
        break;

      case symbol_kind::S_MemberExpr: // MemberExpr
        value.copy< MemberExpr* > (that.value);
        break;

      case symbol_kind::S_50_1: // @1
      case symbol_kind::S_QualType: // QualType
        value.copy< QualType > (that.value);
        break;

      case symbol_kind::S_SignStmt: // SignStmt
        value.copy< SignStmt* > (that.value);
        break;

      case symbol_kind::S_Stmt: // Stmt
      case symbol_kind::S_ReturnStmt: // ReturnStmt
        value.copy< Stmt* > (that.value);
        break;

      case symbol_kind::S_StructDecl: // StructDecl
      case symbol_kind::S_75_2: // @2
        value.copy< StructDecl* > (that.value);
        break;

      case symbol_kind::S_TranslationUnitDecl: // TranslationUnitDecl
        value.copy< TranslationUnitDecl* > (that.value);
        break;

      case symbol_kind::S_Type: // Type
        value.copy< Type* > (that.value);
        break;

      case symbol_kind::S_UnaryOperator: // UnaryOperator
        value.copy< UnaryOperator* > (that.value);
        break;

      case symbol_kind::S_FieldDeclInfo: // FieldDeclInfo
        value.copy< VarDeclInfo > (that.value);
        break;

      case symbol_kind::S_ArrowOrPeriod: // ArrowOrPeriod
        value.copy< bool > (that.value);
        break;

      case symbol_kind::S_INTEGER: // "integer"
      case symbol_kind::S_CHAR: // "char"
      case symbol_kind::S_Stars: // Stars
      case symbol_kind::S_ArrayLenth: // ArrayLenth
      case symbol_kind::S_ArgumentList: // ArgumentList
        value.copy< int > (that.value);
        break;

      case symbol_kind::S_IDENTIFIER: // "identifier"
      case symbol_kind::S_TYPEID: // "type id"
      case symbol_kind::S_STRING: // "string"
      case symbol_kind::S_VarName: // VarName
        value.copy< std::string > (that.value);
        break;

      case symbol_kind::S_VarDecl: // VarDecl
      case symbol_kind::S_VarDeclList: // VarDeclList
        value.copy< std::vector<Decl*> > (that.value);
        break;

      case symbol_kind::S_ExprList: // ExprList
        value.copy< std::vector<Expr*> > (that.value);
        break;

      case symbol_kind::S_FieldDecls: // FieldDecls
      case symbol_kind::S_FieldDecl: // FieldDecl
        value.copy< std::vector<FieldDecl*> > (that.value);
        break;

      case symbol_kind::S_FieldDeclInfoList: // FieldDeclInfoList
        value.copy< std::vector<VarDeclInfo> > (that.value);
        break;

      case symbol_kind::S_ArrayLenthList: // ArrayLenthList
        value.copy< std::vector<int> > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_ArraySubscriptExpr: // ArraySubscriptExpr
        value.move< ArraySubscriptExpr* > (that.value);
        break;

      case symbol_kind::S_BinaryOperator: // BinaryOperator
        value.move< BinaryOperator* > (that.value);
        break;

      case symbol_kind::S_CallExpr: // CallExpr
        value.move< CallExpr* > (that.value);
        break;

      case symbol_kind::S_SingleVarDecl: // SingleVarDecl
        value.move< Decl* > (that.value);
        break;

      case symbol_kind::S_DeclRefExpr: // DeclRefExpr
        value.move< DeclRefExpr* > (that.value);
        break;

      case symbol_kind::S_DeclStmt: // DeclStmt
        value.move< DeclStmt* > (that.value);
        break;

      case symbol_kind::S_InitExpr: // InitExpr
      case symbol_kind::S_Expr: // Expr
      case symbol_kind::S_Literal: // Literal
        value.move< Expr* > (that.value);
        break;

      case symbol_kind::S_InitListExpr: // InitListExpr
        value.move< InitListExpr* > (that.value);
        break;

      case symbol_kind::S_MemberExpr: // MemberExpr
        value.move< MemberExpr* > (that.value);
        break;

      case symbol_kind::S_50_1: // @1
      case symbol_kind::S_QualType: // QualType
        value.move< QualType > (that.value);
        break;

      case symbol_kind::S_SignStmt: // SignStmt
        value.move< SignStmt* > (that.value);
        break;

      case symbol_kind::S_Stmt: // Stmt
      case symbol_kind::S_ReturnStmt: // ReturnStmt
        value.move< Stmt* > (that.value);
        break;

      case symbol_kind::S_StructDecl: // StructDecl
      case symbol_kind::S_75_2: // @2
        value.move< StructDecl* > (that.value);
        break;

      case symbol_kind::S_TranslationUnitDecl: // TranslationUnitDecl
        value.move< TranslationUnitDecl* > (that.value);
        break;

      case symbol_kind::S_Type: // Type
        value.move< Type* > (that.value);
        break;

      case symbol_kind::S_UnaryOperator: // UnaryOperator
        value.move< UnaryOperator* > (that.value);
        break;

      case symbol_kind::S_FieldDeclInfo: // FieldDeclInfo
        value.move< VarDeclInfo > (that.value);
        break;

      case symbol_kind::S_ArrowOrPeriod: // ArrowOrPeriod
        value.move< bool > (that.value);
        break;

      case symbol_kind::S_INTEGER: // "integer"
      case symbol_kind::S_CHAR: // "char"
      case symbol_kind::S_Stars: // Stars
      case symbol_kind::S_ArrayLenth: // ArrayLenth
      case symbol_kind::S_ArgumentList: // ArgumentList
        value.move< int > (that.value);
        break;

      case symbol_kind::S_IDENTIFIER: // "identifier"
      case symbol_kind::S_TYPEID: // "type id"
      case symbol_kind::S_STRING: // "string"
      case symbol_kind::S_VarName: // VarName
        value.move< std::string > (that.value);
        break;

      case symbol_kind::S_VarDecl: // VarDecl
      case symbol_kind::S_VarDeclList: // VarDeclList
        value.move< std::vector<Decl*> > (that.value);
        break;

      case symbol_kind::S_ExprList: // ExprList
        value.move< std::vector<Expr*> > (that.value);
        break;

      case symbol_kind::S_FieldDecls: // FieldDecls
      case symbol_kind::S_FieldDecl: // FieldDecl
        value.move< std::vector<FieldDecl*> > (that.value);
        break;

      case symbol_kind::S_FieldDeclInfoList: // FieldDeclInfoList
        value.move< std::vector<VarDeclInfo> > (that.value);
        break;

      case symbol_kind::S_ArrayLenthList: // ArrayLenthList
        value.move< std::vector<int> > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if TOOLDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        switch (yykind)
    {
      case symbol_kind::S_IDENTIFIER: // "identifier"
                 { yyo << yysym.value.template as < std::string > (); }
        break;

      case symbol_kind::S_TYPEID: // "type id"
                 { yyo << yysym.value.template as < std::string > (); }
        break;

      case symbol_kind::S_INTEGER: // "integer"
                 { yyo << yysym.value.template as < int > (); }
        break;

      case symbol_kind::S_CHAR: // "char"
                 { yyo << yysym.value.template as < int > (); }
        break;

      case symbol_kind::S_STRING: // "string"
                 { yyo << yysym.value.template as < std::string > (); }
        break;

      case symbol_kind::S_TranslationUnitDecl: // TranslationUnitDecl
                 { yyo << yysym.value.template as < TranslationUnitDecl* > (); }
        break;

      case symbol_kind::S_Stmt: // Stmt
                 { yyo << yysym.value.template as < Stmt* > (); }
        break;

      case symbol_kind::S_DeclStmt: // DeclStmt
                 { yyo << yysym.value.template as < DeclStmt* > (); }
        break;

      case symbol_kind::S_VarDecl: // VarDecl
                 { yyo << "{ "; for (auto d : yysym.value.template as < std::vector<Decl*> > ()) yyo << *d << " "; yyo << "}"; }
        break;

      case symbol_kind::S_50_1: // @1
                 { yyo << yysym.value.template as < QualType > ().getAsString(); }
        break;

      case symbol_kind::S_VarDeclList: // VarDeclList
                 { yyo << "{ "; for (auto d : yysym.value.template as < std::vector<Decl*> > ()) yyo << *d << " "; yyo << "}"; }
        break;

      case symbol_kind::S_SingleVarDecl: // SingleVarDecl
                 { yyo << yysym.value.template as < Decl* > (); }
        break;

      case symbol_kind::S_QualType: // QualType
                 { yyo << yysym.value.template as < QualType > ().getAsString(); }
        break;

      case symbol_kind::S_Type: // Type
                 { yyo << yysym.value.template as < Type* > (); }
        break;

      case symbol_kind::S_Stars: // Stars
                 { yyo << yysym.value.template as < int > (); }
        break;

      case symbol_kind::S_VarName: // VarName
                 { yyo << yysym.value.template as < std::string > (); }
        break;

      case symbol_kind::S_ArrayLenthList: // ArrayLenthList
                 { yyo << "{ "; for (auto &i : yysym.value.template as < std::vector<int> > ()) yyo << i << " "; yyo << "}"; }
        break;

      case symbol_kind::S_ArrayLenth: // ArrayLenth
                 { yyo << yysym.value.template as < int > (); }
        break;

      case symbol_kind::S_InitExpr: // InitExpr
                 { yyo << yysym.value.template as < Expr* > (); }
        break;

      case symbol_kind::S_InitListExpr: // InitListExpr
                 { yyo << yysym.value.template as < InitListExpr* > (); }
        break;

      case symbol_kind::S_ExprList: // ExprList
                 { yyo << "{ "; for (auto e : yysym.value.template as < std::vector<Expr*> > ()) yyo << *e << " "; yyo << "}"; }
        break;

      case symbol_kind::S_ReturnStmt: // ReturnStmt
                 { yyo << yysym.value.template as < Stmt* > (); }
        break;

      case symbol_kind::S_SignStmt: // SignStmt
                 { yyo << yysym.value.template as < SignStmt* > (); }
        break;

      case symbol_kind::S_Expr: // Expr
                 { yyo << yysym.value.template as < Expr* > (); }
        break;

      case symbol_kind::S_ArraySubscriptExpr: // ArraySubscriptExpr
                 { yyo << yysym.value.template as < ArraySubscriptExpr* > (); }
        break;

      case symbol_kind::S_BinaryOperator: // BinaryOperator
                 { yyo << yysym.value.template as < BinaryOperator* > (); }
        break;

      case symbol_kind::S_CallExpr: // CallExpr
                 { yyo << yysym.value.template as < CallExpr* > (); }
        break;

      case symbol_kind::S_ArgumentList: // ArgumentList
                 { yyo << yysym.value.template as < int > (); }
        break;

      case symbol_kind::S_DeclRefExpr: // DeclRefExpr
                 { yyo << yysym.value.template as < DeclRefExpr* > (); }
        break;

      case symbol_kind::S_MemberExpr: // MemberExpr
                 { yyo << yysym.value.template as < MemberExpr* > (); }
        break;

      case symbol_kind::S_ArrowOrPeriod: // ArrowOrPeriod
                 { yyo << yysym.value.template as < bool > (); }
        break;

      case symbol_kind::S_UnaryOperator: // UnaryOperator
                 { yyo << yysym.value.template as < UnaryOperator* > (); }
        break;

      case symbol_kind::S_Literal: // Literal
                 { yyo << yysym.value.template as < Expr* > (); }
        break;

      case symbol_kind::S_StructDecl: // StructDecl
                 { yyo << yysym.value.template as < StructDecl* > (); }
        break;

      case symbol_kind::S_75_2: // @2
                 { yyo << yysym.value.template as < StructDecl* > (); }
        break;

      case symbol_kind::S_FieldDecls: // FieldDecls
                 { yyo << "{ "; for (auto fd : yysym.value.template as < std::vector<FieldDecl*> > ()) yyo << *fd << " "; yyo << "}"; }
        break;

      case symbol_kind::S_FieldDecl: // FieldDecl
                 { yyo << "{ "; for (auto fd : yysym.value.template as < std::vector<FieldDecl*> > ()) yyo << *fd << " "; yyo << "}"; }
        break;

      case symbol_kind::S_FieldDeclInfoList: // FieldDeclInfoList
                 { yyo << "{ "; for (auto &i : yysym.value.template as < std::vector<VarDeclInfo> > ()) yyo << "$vdi" << " "; yyo << "}"; }
        break;

      case symbol_kind::S_FieldDeclInfo: // FieldDeclInfo
                 { yyo << "$vdi;"; }
        break;

      default:
        break;
    }
        yyo << ')';
      }
  }
#endif

  void
  Parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  Parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  Parser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if TOOLDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // TOOLDEBUG

  Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return (unsigned char)yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::operator() ()
  {
    return parse ();
  }

  int
  Parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex (driver));
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_ArraySubscriptExpr: // ArraySubscriptExpr
        yylhs.value.emplace< ArraySubscriptExpr* > ();
        break;

      case symbol_kind::S_BinaryOperator: // BinaryOperator
        yylhs.value.emplace< BinaryOperator* > ();
        break;

      case symbol_kind::S_CallExpr: // CallExpr
        yylhs.value.emplace< CallExpr* > ();
        break;

      case symbol_kind::S_SingleVarDecl: // SingleVarDecl
        yylhs.value.emplace< Decl* > ();
        break;

      case symbol_kind::S_DeclRefExpr: // DeclRefExpr
        yylhs.value.emplace< DeclRefExpr* > ();
        break;

      case symbol_kind::S_DeclStmt: // DeclStmt
        yylhs.value.emplace< DeclStmt* > ();
        break;

      case symbol_kind::S_InitExpr: // InitExpr
      case symbol_kind::S_Expr: // Expr
      case symbol_kind::S_Literal: // Literal
        yylhs.value.emplace< Expr* > ();
        break;

      case symbol_kind::S_InitListExpr: // InitListExpr
        yylhs.value.emplace< InitListExpr* > ();
        break;

      case symbol_kind::S_MemberExpr: // MemberExpr
        yylhs.value.emplace< MemberExpr* > ();
        break;

      case symbol_kind::S_50_1: // @1
      case symbol_kind::S_QualType: // QualType
        yylhs.value.emplace< QualType > ();
        break;

      case symbol_kind::S_SignStmt: // SignStmt
        yylhs.value.emplace< SignStmt* > ();
        break;

      case symbol_kind::S_Stmt: // Stmt
      case symbol_kind::S_ReturnStmt: // ReturnStmt
        yylhs.value.emplace< Stmt* > ();
        break;

      case symbol_kind::S_StructDecl: // StructDecl
      case symbol_kind::S_75_2: // @2
        yylhs.value.emplace< StructDecl* > ();
        break;

      case symbol_kind::S_TranslationUnitDecl: // TranslationUnitDecl
        yylhs.value.emplace< TranslationUnitDecl* > ();
        break;

      case symbol_kind::S_Type: // Type
        yylhs.value.emplace< Type* > ();
        break;

      case symbol_kind::S_UnaryOperator: // UnaryOperator
        yylhs.value.emplace< UnaryOperator* > ();
        break;

      case symbol_kind::S_FieldDeclInfo: // FieldDeclInfo
        yylhs.value.emplace< VarDeclInfo > ();
        break;

      case symbol_kind::S_ArrowOrPeriod: // ArrowOrPeriod
        yylhs.value.emplace< bool > ();
        break;

      case symbol_kind::S_INTEGER: // "integer"
      case symbol_kind::S_CHAR: // "char"
      case symbol_kind::S_Stars: // Stars
      case symbol_kind::S_ArrayLenth: // ArrayLenth
      case symbol_kind::S_ArgumentList: // ArgumentList
        yylhs.value.emplace< int > ();
        break;

      case symbol_kind::S_IDENTIFIER: // "identifier"
      case symbol_kind::S_TYPEID: // "type id"
      case symbol_kind::S_STRING: // "string"
      case symbol_kind::S_VarName: // VarName
        yylhs.value.emplace< std::string > ();
        break;

      case symbol_kind::S_VarDecl: // VarDecl
      case symbol_kind::S_VarDeclList: // VarDeclList
        yylhs.value.emplace< std::vector<Decl*> > ();
        break;

      case symbol_kind::S_ExprList: // ExprList
        yylhs.value.emplace< std::vector<Expr*> > ();
        break;

      case symbol_kind::S_FieldDecls: // FieldDecls
      case symbol_kind::S_FieldDecl: // FieldDecl
        yylhs.value.emplace< std::vector<FieldDecl*> > ();
        break;

      case symbol_kind::S_FieldDeclInfoList: // FieldDeclInfoList
        yylhs.value.emplace< std::vector<VarDeclInfo> > ();
        break;

      case symbol_kind::S_ArrayLenthList: // ArrayLenthList
        yylhs.value.emplace< std::vector<int> > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // start: TranslationUnitDecl
                      { driver.pushAST(yystack_[0].value.as < TranslationUnitDecl* > ()); }
    break;

  case 3: // TranslationUnitDecl: %empty
         { yylhs.value.as < TranslationUnitDecl* > () = TranslationUnitDecl::create(driver.getContext()); }
    break;

  case 4: // TranslationUnitDecl: TranslationUnitDecl Stmt ";"
                               { yylhs.value.as < TranslationUnitDecl* > () = (yystack_[2].value.as < TranslationUnitDecl* > ()->push(yystack_[1].value.as < Stmt* > ()), yystack_[2].value.as < TranslationUnitDecl* > ()); }
    break;

  case 5: // Stmt: %empty
         { yylhs.value.as < Stmt* > () = Stmt::createEmpty(); }
    break;

  case 6: // Stmt: Expr
  {
    yylhs.value.as < Stmt* > () = ImplicitCastExpr::cast2RvExpr(yystack_[0].value.as < Expr* > ());
  }
    break;

  case 7: // Stmt: DeclStmt
           { yylhs.value.as < Stmt* > () = yystack_[0].value.as < DeclStmt* > (); }
    break;

  case 8: // Stmt: ReturnStmt
             { yylhs.value.as < Stmt* > () = yystack_[0].value.as < Stmt* > (); }
    break;

  case 9: // Stmt: SignStmt
           { yylhs.value.as < Stmt* > () = yystack_[0].value.as < SignStmt* > (); }
    break;

  case 10: // DeclStmt: VarDecl
          { yylhs.value.as < DeclStmt* > () = DeclStmt::create(yystack_[0].value.as < std::vector<Decl*> > ()); }
    break;

  case 11: // DeclStmt: StructDecl
             { yylhs.value.as < DeclStmt* > () = DeclStmt::create(yystack_[0].value.as < StructDecl* > ()); }
    break;

  case 12: // @1: %empty
             {
    yylhs.value.as < QualType > () = yystack_[0].value.as < QualType > ();
    driver.setQualType(yystack_[0].value.as < QualType > ());
  }
    break;

  case 13: // VarDecl: QualType @1 VarDeclList
  {
    yylhs.value.as < std::vector<Decl*> > () = yystack_[0].value.as < std::vector<Decl*> > ();
  }
    break;

  case 14: // VarDeclList: SingleVarDecl
  {
    yylhs.value.as < std::vector<Decl*> > ().push_back(yystack_[0].value.as < Decl* > ());
  }
    break;

  case 15: // VarDeclList: VarDeclList "," SingleVarDecl
  {
    yylhs.value.as < std::vector<Decl*> > ().swap(yystack_[2].value.as < std::vector<Decl*> > ());
    yylhs.value.as < std::vector<Decl*> > ().push_back(yystack_[0].value.as < Decl* > ());
  }
    break;

  case 16: // SingleVarDecl: Stars VarName ArrayLenthList InitExpr
  {
    QualType qt = driver.getQualType();
    if (yystack_[3].value.as < int > () > 0) {
        qt = PointerType::get(qt, yystack_[3].value.as < int > ());
        driver.getContext()->setPathType(2);
    }
    if (yystack_[1].value.as < std::vector<int> > ().size() == 1 && yystack_[1].value.as < std::vector<int> > ()[0] == -1) {
        if (yystack_[0].value.as < Expr* > ()) {
            if (auto il = dynamic_cast<InitListExpr*>(yystack_[0].value.as < Expr* > ()))
                yystack_[1].value.as < std::vector<int> > ()[0] = il->getLenth();
            else
                yystack_[1].value.as < std::vector<int> > ()[0] = yystack_[0].value.as < Expr* > ()->getType().getLenth();
        } else
            error(yystack_[2].location, "数组应显式指定长度，或被初始化");
    }
    qt = qt * yystack_[1].value.as < std::vector<int> > ();
    // if (qt.isArray())
    //    driver.getContext()->setPathType(2);
    yylhs.value.as < Decl* > () = VarDecl::create(driver.getContext(), yystack_[2].value.as < std::string > (), qt, yystack_[0].value.as < Expr* > ());
  }
    break;

  case 17: // QualType: Type
  {
    if (yystack_[0].value.as < Type* > () == nullptr) error(yystack_[0].location, "无类型？");
    yylhs.value.as < QualType > () = yystack_[0].value.as < Type* > ();
  }
    break;

  case 18: // Type: "type id"
  {
    yylhs.value.as < Type* > () = driver.getContext()->getType(yystack_[0].value.as < std::string > ());
    if (yylhs.value.as < Type* > () == nullptr)
        error(yystack_[0].location, std::string("没有类型\'") + yystack_[0].value.as < std::string > () + "\'");
  }
    break;

  case 19: // Type: "struct" "type id"
  {
    yylhs.value.as < Type* > () = driver.getContext()->getType(yystack_[0].value.as < std::string > ());
    if (yylhs.value.as < Type* > () == nullptr || !dynamic_cast<StructType*>(yylhs.value.as < Type* > ()))
        error(yystack_[0].location, std::string("没有结构体类型\'") + yystack_[0].value.as < std::string > () + "\'");
  }
    break;

  case 20: // Stars: %empty
         { yylhs.value.as < int > () = 0; }
    break;

  case 21: // Stars: Stars "*"
            { yylhs.value.as < int > () = yystack_[1].value.as < int > () + 1; }
    break;

  case 22: // VarName: "identifier"
               { yylhs.value.as < std::string > () = yystack_[0].value.as < std::string > (); }
    break;

  case 23: // ArrayLenthList: %empty
         { yylhs.value.as < std::vector<int> > () = {}; }
    break;

  case 24: // ArrayLenthList: ArrayLenthList ArrayLenth
  {
    yylhs.value.as < std::vector<int> > ().swap(yystack_[1].value.as < std::vector<int> > ());
    if (yylhs.value.as < std::vector<int> > ().size() > 0 && yystack_[0].value.as < int > () == -1)
        error(yystack_[0].location, "多维数组必须显式指定长度");
    yylhs.value.as < std::vector<int> > ().push_back(yystack_[0].value.as < int > ());
  }
    break;

  case 25: // ArrayLenth: "[" "]"
          { yylhs.value.as < int > () = -1; }
    break;

  case 26: // ArrayLenth: "[" Expr "]"
  {
    if (yystack_[1].value.as < Expr* > ()->isConstant()) {
        yylhs.value.as < int > () = yystack_[1].value.as < Expr* > ()->getConstantValue();
        if (yylhs.value.as < int > () <= 0)
            error(yystack_[0].location, "数组长度须为正数！");
    } else
        error(yystack_[0].location, "仅支持数组长度是常数！");
  }
    break;

  case 27: // InitExpr: %empty
  { yylhs.value.as < Expr* > () = nullptr; }
    break;

  case 28: // InitExpr: "=" Expr
  { yylhs.value.as < Expr* > () = yystack_[0].value.as < Expr* > (); }
    break;

  case 29: // InitExpr: "=" InitListExpr
  { yylhs.value.as < Expr* > () = yystack_[0].value.as < InitListExpr* > (); }
    break;

  case 30: // InitListExpr: "{" ExprList "}"
  { yylhs.value.as < InitListExpr* > () = InitListExpr::create(yystack_[1].value.as < std::vector<Expr*> > (), QualType()); }
    break;

  case 31: // ExprList: %empty
  { std::vector<Expr*>().swap(yylhs.value.as < std::vector<Expr*> > ()); }
    break;

  case 32: // ExprList: Expr
  { yylhs.value.as < std::vector<Expr*> > ().push_back(yystack_[0].value.as < Expr* > ()); }
    break;

  case 33: // ExprList: ExprList "," Expr
  {
    yylhs.value.as < std::vector<Expr*> > ().swap(yystack_[2].value.as < std::vector<Expr*> > ());
    yylhs.value.as < std::vector<Expr*> > ().push_back(yystack_[0].value.as < Expr* > ());
  }
    break;

  case 34: // ReturnStmt: "return" Expr
                { yylhs.value.as < Stmt* > () = Stmt::createEmpty(); }
    break;

  case 35: // SignStmt: "@" Expr
  { 
    yylhs.value.as < SignStmt* > () = SignStmt::create(ImplicitCastExpr::cast2RvExpr(yystack_[0].value.as < Expr* > ())); 
  }
    break;

  case 36: // Expr: ArraySubscriptExpr
  {
    yylhs.value.as < Expr* > () = yystack_[0].value.as < ArraySubscriptExpr* > ();
    driver.getContext()->setPathType(0);
  }
    break;

  case 37: // Expr: BinaryOperator
                 { yylhs.value.as < Expr* > () = yystack_[0].value.as < BinaryOperator* > (); }
    break;

  case 38: // Expr: CallExpr
           { yylhs.value.as < Expr* > () = yystack_[0].value.as < CallExpr* > (); }
    break;

  case 39: // Expr: DeclRefExpr
              { yylhs.value.as < Expr* > () = yystack_[0].value.as < DeclRefExpr* > (); }
    break;

  case 40: // Expr: MemberExpr
  {
    yylhs.value.as < Expr* > () = yystack_[0].value.as < MemberExpr* > ();
    driver.getContext()->setPathType(2);
  }
    break;

  case 41: // Expr: UnaryOperator
  {
    yylhs.value.as < Expr* > () = yystack_[0].value.as < UnaryOperator* > ();
    if (yystack_[0].value.as < UnaryOperator* > ()->isPointerOperation())
        driver.getContext()->setPathType(2);
  }
    break;

  case 42: // Expr: Literal
          { yylhs.value.as < Expr* > () = yystack_[0].value.as < Expr* > (); }
    break;

  case 43: // Expr: "(" Expr ")"
               { yylhs.value.as < Expr* > () = yystack_[1].value.as < Expr* > (); }
    break;

  case 44: // ArraySubscriptExpr: Expr "[" Expr "]"
  {
    try {
        auto drf = dynamic_cast<DeclRefExpr*>(yystack_[3].value.as < Expr* > ());
        if (drf && drf->getType().isArray())
            yystack_[3].value.as < Expr* > () = ImplicitCastExpr::cast2ArrayPointer(yystack_[3].value.as < Expr* > ());
        else if (yystack_[3].value.as < Expr* > ()->getType().isPointer()) {
            driver.getContext()->setPathType(2);
            yystack_[3].value.as < Expr* > () = ImplicitCastExpr::cast2RvExpr(yystack_[3].value.as < Expr* > ());
        } else
            throw parser_exception("subscripted value is not an array or pointer");
        yylhs.value.as < ArraySubscriptExpr* > () = ArraySubscriptExpr::create(yystack_[3].value.as < Expr* > (), yystack_[1].value.as < Expr* > ());
    }
    catch (parser_exception& pe) {
        error(yystack_[3].location, pe.what());
    }
  }
    break;

  case 45: // BinaryOperator: Expr "=" Expr
                { yylhs.value.as < BinaryOperator* > () = BinaryOperator::create(yystack_[2].value.as < Expr* > (), yystack_[0].value.as < Expr* > (), "=", CTX); }
    break;

  case 46: // BinaryOperator: Expr "+=" Expr
                 { yylhs.value.as < BinaryOperator* > () = BinaryOperator::create(yystack_[2].value.as < Expr* > (), yystack_[0].value.as < Expr* > (), "+=", CTX); }
    break;

  case 47: // BinaryOperator: Expr "-=" Expr
                 { yylhs.value.as < BinaryOperator* > () = BinaryOperator::create(yystack_[2].value.as < Expr* > (), yystack_[0].value.as < Expr* > (), "-=", CTX); }
    break;

  case 48: // BinaryOperator: Expr "*=" Expr
                 { yylhs.value.as < BinaryOperator* > () = BinaryOperator::create(yystack_[2].value.as < Expr* > (), yystack_[0].value.as < Expr* > (), "*=", CTX); }
    break;

  case 49: // BinaryOperator: Expr "/=" Expr
                 { yylhs.value.as < BinaryOperator* > () = BinaryOperator::create(yystack_[2].value.as < Expr* > (), yystack_[0].value.as < Expr* > (), "/=", CTX); }
    break;

  case 50: // BinaryOperator: Expr "+" Expr
                { yylhs.value.as < BinaryOperator* > () = BinaryOperator::create(yystack_[2].value.as < Expr* > (), yystack_[0].value.as < Expr* > (), "+", CTX); }
    break;

  case 51: // BinaryOperator: Expr "-" Expr
                { yylhs.value.as < BinaryOperator* > () = BinaryOperator::create(yystack_[2].value.as < Expr* > (), yystack_[0].value.as < Expr* > (), "-", CTX); }
    break;

  case 52: // BinaryOperator: Expr "*" Expr
                { yylhs.value.as < BinaryOperator* > () = BinaryOperator::create(yystack_[2].value.as < Expr* > (), yystack_[0].value.as < Expr* > (), "*", CTX); }
    break;

  case 53: // BinaryOperator: Expr "/" Expr
                { yylhs.value.as < BinaryOperator* > () = BinaryOperator::create(yystack_[2].value.as < Expr* > (), yystack_[0].value.as < Expr* > (), "/", CTX); }
    break;

  case 54: // BinaryOperator: Expr "%" Expr
                { yylhs.value.as < BinaryOperator* > () = BinaryOperator::create(yystack_[2].value.as < Expr* > (), yystack_[0].value.as < Expr* > (), "%", CTX); }
    break;

  case 55: // BinaryOperator: Expr "!=" Expr
                 { yylhs.value.as < BinaryOperator* > () = BinaryOperator::create(yystack_[2].value.as < Expr* > (), yystack_[0].value.as < Expr* > (), "!=", CTX); }
    break;

  case 56: // BinaryOperator: Expr "==" Expr
                 { yylhs.value.as < BinaryOperator* > () = BinaryOperator::create(yystack_[2].value.as < Expr* > (), yystack_[0].value.as < Expr* > (), "==", CTX); }
    break;

  case 57: // BinaryOperator: Expr ">" Expr
                { yylhs.value.as < BinaryOperator* > () = BinaryOperator::create(yystack_[2].value.as < Expr* > (), yystack_[0].value.as < Expr* > (), ">", CTX); }
    break;

  case 58: // BinaryOperator: Expr "<" Expr
                { yylhs.value.as < BinaryOperator* > () = BinaryOperator::create(yystack_[2].value.as < Expr* > (), yystack_[0].value.as < Expr* > (), "<", CTX); }
    break;

  case 59: // BinaryOperator: Expr ">=" Expr
                 { yylhs.value.as < BinaryOperator* > () = BinaryOperator::create(yystack_[2].value.as < Expr* > (), yystack_[0].value.as < Expr* > (), ">=", CTX); }
    break;

  case 60: // BinaryOperator: Expr "<=" Expr
                 { yylhs.value.as < BinaryOperator* > () = BinaryOperator::create(yystack_[2].value.as < Expr* > (), yystack_[0].value.as < Expr* > (), "<=", CTX); }
    break;

  case 61: // BinaryOperator: Expr "&&" Expr
                 { yylhs.value.as < BinaryOperator* > () = BinaryOperator::create(yystack_[2].value.as < Expr* > (), yystack_[0].value.as < Expr* > (), "&&", CTX); }
    break;

  case 62: // BinaryOperator: Expr "||" Expr
                 { yylhs.value.as < BinaryOperator* > () = BinaryOperator::create(yystack_[2].value.as < Expr* > (), yystack_[0].value.as < Expr* > (), "||", CTX); }
    break;

  case 63: // CallExpr: "identifier" "(" ArgumentList ")"
  {
    yylhs.value.as < CallExpr* > () = CallExpr::create(driver.getContext()->getIntType(), yystack_[3].value.as < std::string > ());
  }
    break;

  case 64: // ArgumentList: %empty
         { yylhs.value.as < int > () = 0; }
    break;

  case 65: // ArgumentList: Expr
       { yylhs.value.as < int > () = 1; }
    break;

  case 66: // ArgumentList: ArgumentList "," Expr
  {
    yylhs.value.as < int > () = yystack_[2].value.as < int > () + 1;
  }
    break;

  case 67: // DeclRefExpr: "identifier"
  {
    auto d = driver.getContext()->getDecl(yystack_[0].value.as < std::string > ());
    auto vd = dynamic_cast<ValueDecl*>(d);
    if (vd)
        yylhs.value.as < DeclRefExpr* > () = DeclRefExpr::create(vd, vd->getType());
    else
        throw not_value_exception(yystack_[0].value.as < std::string > ());
  }
    break;

  case 68: // MemberExpr: Expr ArrowOrPeriod "identifier"
  {
    auto bt = yystack_[2].value.as < Expr* > ()->getType().getBaseType();
    if (!bt->isStruct()) {
        error(yystack_[1].location, std::string("member reference base type \'")
            + bt->getAsString() + "\' is not a structure");
    } else {
        const auto st = dynamic_cast<const StructType*>(bt);
        if (!st)
            error(yystack_[2].location, std::string("can't find such struct type"));
        auto sd = st->getDecl();
        if (!sd->existsFieldDecl(yystack_[0].value.as < std::string > ()))
            error(yystack_[0].location, std::string("no member named \'")
                + yystack_[0].value.as < std::string > () + "\' in \'" + st->getAsString() + "\'");
        auto fd = sd->getFieldDecl(yystack_[0].value.as < std::string > ());
        yylhs.value.as < MemberExpr* > () = MemberExpr::create(yystack_[2].value.as < Expr* > (), fd, fd->getType(), yystack_[1].value.as < bool > ());
        driver.getContext()->setPathType(2);
    }
  }
    break;

  case 69: // ArrowOrPeriod: "->"
       { yylhs.value.as < bool > () = true; }
    break;

  case 70: // ArrowOrPeriod: "."
      { yylhs.value.as < bool > () = false; }
    break;

  case 71: // UnaryOperator: "-" Expr
  { yylhs.value.as < UnaryOperator* > () = UnaryOperator::create(yystack_[0].value.as < Expr* > (), "-", CTX); }
    break;

  case 72: // UnaryOperator: "!" Expr
  { yylhs.value.as < UnaryOperator* > () = UnaryOperator::create(yystack_[0].value.as < Expr* > (), "!", CTX); }
    break;

  case 73: // UnaryOperator: "&" Expr
  {
    yylhs.value.as < UnaryOperator* > () = UnaryOperator::create(yystack_[0].value.as < Expr* > (), "&", CTX);
    driver.getContext()->setPathType(2);
  }
    break;

  case 74: // UnaryOperator: "*" Expr
  {
    yylhs.value.as < UnaryOperator* > () = UnaryOperator::create(yystack_[0].value.as < Expr* > (), "*", CTX);
    driver.getContext()->setPathType(2);
  }
    break;

  case 75: // Literal: "integer"
            { yylhs.value.as < Expr* > () = driver.getContext()->createInt(yystack_[0].value.as < int > ()); }
    break;

  case 76: // Literal: "char"
         { yylhs.value.as < Expr* > () = driver.getContext()->createChar(yystack_[0].value.as < int > ()); }
    break;

  case 77: // Literal: "string"
           { yylhs.value.as < Expr* > () = driver.getContext()->createStr(yystack_[0].value.as < std::string > ()); }
    break;

  case 78: // @2: %empty
                {
    yylhs.value.as < StructDecl* > () = StructDecl::create(driver.getContext(), yystack_[1].value.as < std::string > ());
    driver.push(yylhs.value.as < StructDecl* > ());
  }
    break;

  case 79: // StructDecl: "struct" "identifier" "{" @2 FieldDecls "}"
  {
    yylhs.value.as < StructDecl* > () = yystack_[2].value.as < StructDecl* > ();
    // $$->addFieldDecls($5);
    driver.pop();
    yylhs.value.as < StructDecl* > ()->complete();
  }
    break;

  case 80: // FieldDecls: %empty
  { yylhs.value.as < std::vector<FieldDecl*> > () = std::vector<FieldDecl*>(); }
    break;

  case 81: // FieldDecls: FieldDecls FieldDecl ";"
  {
    yylhs.value.as < std::vector<FieldDecl*> > ().swap(yystack_[2].value.as < std::vector<FieldDecl*> > ());
    yylhs.value.as < std::vector<FieldDecl*> > ().insert(yylhs.value.as < std::vector<FieldDecl*> > ().end(), yystack_[1].value.as < std::vector<FieldDecl*> > ().begin(), yystack_[1].value.as < std::vector<FieldDecl*> > ().end());
  }
    break;

  case 82: // FieldDecl: QualType FieldDeclInfoList
  {
    for (auto& fdi : yystack_[0].value.as < std::vector<VarDeclInfo> > ()) {
        QualType qt(yystack_[1].value.as < QualType > ());
        if (fdi.level > 0)
            qt = PointerType::get(qt, fdi.level);
        qt = qt * fdi.lenth;
        auto bt = qt.getBaseType();
        if (bt->isStruct()) {
            auto st = dynamic_cast<const StructType*>(bt);
            if (!st->getDecl()->isCompleted() && !qt.getLevel()) {
                driver.pop();
                error(yystack_[1].location, "field has incomplete type \'"
                    + bt->getAsString() + "\'");
            }
        }
        yylhs.value.as < std::vector<FieldDecl*> > ().push_back(FieldDecl::create(driver.getContext(), fdi.name, qt));
    }
  }
    break;

  case 83: // FieldDeclInfoList: FieldDeclInfo
  {
    yylhs.value.as < std::vector<VarDeclInfo> > ().push_back(yystack_[0].value.as < VarDeclInfo > ());
  }
    break;

  case 84: // FieldDeclInfoList: FieldDeclInfoList "," FieldDeclInfo
  {
    yylhs.value.as < std::vector<VarDeclInfo> > ().swap(yystack_[2].value.as < std::vector<VarDeclInfo> > ());
    yylhs.value.as < std::vector<VarDeclInfo> > ().push_back(yystack_[0].value.as < VarDeclInfo > ());
  }
    break;

  case 85: // FieldDeclInfo: Stars VarName ArrayLenthList
  {
    yylhs.value.as < VarDeclInfo > ().level = yystack_[2].value.as < int > ();
    yylhs.value.as < VarDeclInfo > ().name = yystack_[1].value.as < std::string > ();
    yylhs.value.as < VarDeclInfo > ().lenth = yystack_[0].value.as < std::vector<int> > ();
    if (yystack_[0].value.as < std::vector<int> > ().size() > 1 && yystack_[0].value.as < std::vector<int> > ()[0] == -1)
        error(yystack_[0].location, "结构体中的数组应显式指定长度");
  }
    break;



            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yyerror_range[1].location = yystack_[0].location;
        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

  std::string
  Parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // Parser::context.
  Parser::context::context (const Parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  Parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

    int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        int yychecklim = yylast_ - yyn + 1;
        int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
          if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
              && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
            {
              if (!yyarg)
                ++yycount;
              else if (yycount == yyargn)
                return 0;
              else
                yyarg[yycount++] = YY_CAST (symbol_kind_type, yyx);
            }
      }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }



  int
  Parser::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char Parser::yypact_ninf_ = -45;

  const signed char Parser::yytable_ninf_ = -6;

  const short
  Parser::yypact_[] =
  {
     -45,    10,    59,   -45,   119,   119,   119,   119,   119,   119,
     119,    29,     9,   -45,   -45,   -45,   -45,    32,   -45,   -45,
     -45,   -45,   -45,   -45,   208,   -45,   -45,   -45,   -45,   -45,
     -45,   -45,   -45,     4,     6,     6,     6,     6,   208,   208,
      65,   -45,   119,   -45,   -45,   119,   -45,   -45,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,     2,   -45,   -45,   208,
      61,    56,   -45,    26,   156,   208,   285,   285,     6,     6,
     208,   208,   208,   208,     6,   116,   116,   283,   283,   283,
     283,   259,   234,   -45,   -45,   -45,   119,   -45,   -45,   -45,
     -45,   -45,    -1,   208,   -45,    64,   -45,    33,   -45,    67,
      73,   108,   -45,   -45,    26,    69,   -45,   -45,   -45,   182,
     119,   -45,   208,   -45,   -45,   -45,    28,   208,    77,   -45,
     -45,   119,   208
  };

  const signed char
  Parser::yydefact_[] =
  {
       3,     0,     2,     1,     0,     0,     0,     0,     0,     0,
       0,     0,    67,    18,    75,    76,    77,     0,     7,    10,
      12,    17,     8,     9,     6,    36,    37,    38,    39,    40,
      41,    42,    11,     0,    71,    74,    72,    73,    35,    34,
       0,    19,    64,     4,    20,     0,    70,    69,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    43,    78,    65,
       0,    13,    14,     0,     0,    45,    50,    51,    52,    53,
      46,    47,    48,    49,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    68,    80,    63,     0,    20,    21,    22,
      23,    44,     0,    66,    15,    27,    79,     0,    20,     0,
       0,     0,    24,    16,     0,    82,    83,    81,    25,     0,
      31,    29,    28,    23,    20,    26,     0,    32,    85,    84,
      30,     0,    33
  };

  const signed char
  Parser::yypgoto_[] =
  {
     -45,   -45,   -45,   -45,   -45,   -45,   -45,   -45,   -14,   -18,
     -45,   -44,   -29,   -37,   -45,   -45,   -45,   -45,   -45,   -45,
      -4,   -45,   -45,   -45,   -45,   -45,   -45,   -45,   -45,   -45,
     -45,   -45,   -45,   -45,   -45,   -23
  };

  const signed char
  Parser::yydefgoto_[] =
  {
      -1,     1,     2,    17,    18,    19,    44,    71,    72,    20,
      21,    73,   100,   105,   112,   113,   121,   126,    22,    23,
      24,    25,    26,    27,    70,    28,    29,    66,    30,    31,
      32,    94,   102,   109,   115,   116
  };

  const short
  Parser::yytable_[] =
  {
      33,    34,    35,    36,    37,    38,    39,   106,    67,    45,
       3,    45,    42,    46,    47,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,   107,   130,    13,    69,    93,
     131,    74,    98,    43,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,     4,    99,   114,    95,    40,    41,    97,   110,
      -5,    41,    68,    96,     5,     6,     4,   111,   117,   118,
     114,   124,   110,   104,   108,   123,   128,     0,     5,     6,
       7,     8,   103,     9,    10,    11,    12,    13,    14,    15,
      16,   129,     0,     0,     7,     8,   119,   122,     0,     0,
      12,     4,    14,    15,    16,   120,   127,     0,     0,     0,
       0,    45,     4,     5,     6,    46,    47,   132,     0,     0,
      49,    50,    51,    52,     5,     6,     0,     0,    57,     7,
       8,    60,    61,    62,    63,    12,     0,    14,    15,    16,
       7,     8,     0,     0,     0,     0,    12,     0,    14,    15,
      16,    45,   101,     0,     0,    46,    47,     0,     0,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    45,   125,     0,
       0,    46,    47,     0,     0,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    45,     0,     0,     0,    46,    47,     0,
       0,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    45,
       0,     0,     0,    46,    47,     0,     0,     0,    49,    50,
      51,    52,     0,     0,     0,     0,    57,    58,    59,    60,
      61,    62,    63,    64,    45,     0,     0,     0,    46,    47,
       0,     0,     0,    49,    50,    51,    52,     0,     0,     0,
       0,    57,    58,    59,    60,    61,    62,    63,    45,     0,
      45,     0,    46,    47,    46,    47,     0,    49,    50,    51,
      52,    51,    52,     0,     0,    57,     0,    57
  };

  const short
  Parser::yycheck_[] =
  {
       4,     5,     6,     7,     8,     9,    10,     8,     4,     5,
       0,     5,     3,     9,    10,     9,    10,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    36,     8,    38,    42,    37,
      12,    45,    16,    11,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,     3,    37,   108,     4,    37,    38,    12,     5,
      11,    38,     7,    12,    15,    16,     3,    13,    11,     6,
     124,    12,     5,    97,   102,   114,   123,    -1,    15,    16,
      31,    32,    96,    34,    35,    36,    37,    38,    39,    40,
      41,   124,    -1,    -1,    31,    32,   110,   111,    -1,    -1,
      37,     3,    39,    40,    41,     7,   120,    -1,    -1,    -1,
      -1,     5,     3,    15,    16,     9,    10,   131,    -1,    -1,
      14,    15,    16,    17,    15,    16,    -1,    -1,    22,    31,
      32,    25,    26,    27,    28,    37,    -1,    39,    40,    41,
      31,    32,    -1,    -1,    -1,    -1,    37,    -1,    39,    40,
      41,     5,     6,    -1,    -1,     9,    10,    -1,    -1,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,     5,     6,    -1,
      -1,     9,    10,    -1,    -1,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,     5,    -1,    -1,    -1,     9,    10,    -1,
      -1,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,     5,
      -1,    -1,    -1,     9,    10,    -1,    -1,    -1,    14,    15,
      16,    17,    -1,    -1,    -1,    -1,    22,    23,    24,    25,
      26,    27,    28,    29,     5,    -1,    -1,    -1,     9,    10,
      -1,    -1,    -1,    14,    15,    16,    17,    -1,    -1,    -1,
      -1,    22,    23,    24,    25,    26,    27,    28,     5,    -1,
       5,    -1,     9,    10,     9,    10,    -1,    14,    15,    16,
      17,    16,    17,    -1,    -1,    22,    -1,    22
  };

  const signed char
  Parser::yystos_[] =
  {
       0,    45,    46,     0,     3,    15,    16,    31,    32,    34,
      35,    36,    37,    38,    39,    40,    41,    47,    48,    49,
      53,    54,    62,    63,    64,    65,    66,    67,    69,    70,
      72,    73,    74,    64,    64,    64,    64,    64,    64,    64,
      37,    38,     3,    11,    50,     5,     9,    10,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    71,     4,     7,    64,
      68,    51,    52,    55,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    37,    75,     4,    12,    12,    16,    37,
      56,     6,    76,    64,    52,    57,     8,    36,    53,    77,
       5,    13,    58,    59,    55,    78,    79,    11,     6,    64,
       7,    60,    64,    56,    12,     6,    61,    64,    57,    79,
       8,    12,    64
  };

  const signed char
  Parser::yyr1_[] =
  {
       0,    44,    45,    46,    46,    47,    47,    47,    47,    47,
      48,    48,    50,    49,    51,    51,    52,    53,    54,    54,
      55,    55,    56,    57,    57,    58,    58,    59,    59,    59,
      60,    61,    61,    61,    62,    63,    64,    64,    64,    64,
      64,    64,    64,    64,    65,    66,    66,    66,    66,    66,
      66,    66,    66,    66,    66,    66,    66,    66,    66,    66,
      66,    66,    66,    67,    68,    68,    68,    69,    70,    71,
      71,    72,    72,    72,    72,    73,    73,    73,    75,    74,
      76,    76,    77,    78,    78,    79
  };

  const signed char
  Parser::yyr2_[] =
  {
       0,     2,     1,     0,     3,     0,     1,     1,     1,     1,
       1,     1,     0,     3,     1,     3,     4,     1,     1,     2,
       0,     2,     1,     0,     2,     2,     3,     0,     2,     2,
       3,     0,     1,     3,     2,     2,     1,     1,     1,     1,
       1,     1,     1,     3,     4,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     4,     0,     1,     3,     1,     3,     1,
       1,     2,     2,     2,     2,     1,     1,     1,     0,     6,
       0,     3,     2,     1,     3,     3
  };


#if TOOLDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "\"(\"", "\")\"",
  "\"[\"", "\"]\"", "\"{\"", "\"}\"", "\".\"", "\"->\"", "\";\"", "\",\"",
  "\"=\"", "\"+\"", "\"-\"", "\"*\"", "\"/\"", "\"+=\"", "\"-=\"",
  "\"*=\"", "\"/=\"", "\"%\"", "\"!=\"", "\"==\"", "\">\"", "\"<\"",
  "\">=\"", "\"<=\"", "\"&&\"", "\"||\"", "\"!\"", "\"&\"", "\"|\"",
  "\"@\"", "\"return\"", "\"struct\"", "\"identifier\"", "\"type id\"",
  "\"integer\"", "\"char\"", "\"string\"", "NEG", "DEREF", "$accept",
  "start", "TranslationUnitDecl", "Stmt", "DeclStmt", "VarDecl", "@1",
  "VarDeclList", "SingleVarDecl", "QualType", "Type", "Stars", "VarName",
  "ArrayLenthList", "ArrayLenth", "InitExpr", "InitListExpr", "ExprList",
  "ReturnStmt", "SignStmt", "Expr", "ArraySubscriptExpr", "BinaryOperator",
  "CallExpr", "ArgumentList", "DeclRefExpr", "MemberExpr", "ArrowOrPeriod",
  "UnaryOperator", "Literal", "StructDecl", "@2", "FieldDecls",
  "FieldDecl", "FieldDeclInfoList", "FieldDeclInfo", YY_NULLPTR
  };
#endif


#if TOOLDEBUG
  const short
  Parser::yyrline_[] =
  {
       0,   159,   159,   162,   163,   166,   167,   171,   172,   173,
     176,   177,   181,   180,   191,   195,   202,   225,   232,   238,
     246,   247,   250,   253,   254,   263,   264,   275,   277,   279,
     284,   288,   290,   292,   299,   302,   308,   313,   314,   315,
     316,   321,   327,   328,   331,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   370,   376,   377,   378,   384,   395,   416,
     417,   420,   422,   424,   429,   436,   437,   438,   442,   441,
     455,   457,   464,   485,   489,   496
  };

  void
  Parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  Parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // TOOLDEBUG


} // tool



#include <sstream>

void tool::Parser::error (const location_type& l, const std::string& m)
{
    // TODO: tmp code
    while (auto sd = dynamic_cast<StructDecl*>(driver.getContext())) {
        if (sd->isCompleted())
            break;
        driver.pop();
    }

    stringstream ss;
    ss << l << ": error: " << m << endl;
    throw parser_exception(ss.str());
}
