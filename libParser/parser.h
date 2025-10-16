// A Bison parser, made by GNU Bison 3.7.4.

// Skeleton interface for Bison LALR(1) parsers in C++

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


/**
 ** \file parser.h
 ** Define the tool::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.

#ifndef YY_TOOL_PARSER_H_INCLUDED
# define YY_TOOL_PARSER_H_INCLUDED
// "%code requires" blocks.

#pragma warning( disable : 4065 )

#include "exception.h"
#include "expression.h"
#include <string>
#include <iostream>
namespace tool {
    class Driver;
}
using namespace tool;
using namespace std;
struct VarDeclInfo {
    std::string name;
    int level = 1;
    std::vector<int> lenth;
    Expr* init = nullptr;
    void print(std::ostream& os) {
        os << "{ " << name << ", ";
        os << "level=" << level << ", ";
        os << ", ";
        os << (int)!!init << " }";
    }
};

#ifndef CTX
  #define CTX (driver.getContext())
#endif



# include <cassert>
# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>

#if defined __cplusplus
# define YY_CPLUSPLUS __cplusplus
#else
# define YY_CPLUSPLUS 199711L
#endif

// Support move semantics when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_MOVE           std::move
# define YY_MOVE_OR_COPY   move
# define YY_MOVE_REF(Type) Type&&
# define YY_RVREF(Type)    Type&&
# define YY_COPY(Type)     Type
#else
# define YY_MOVE
# define YY_MOVE_OR_COPY   copy
# define YY_MOVE_REF(Type) Type&
# define YY_RVREF(Type)    const Type&
# define YY_COPY(Type)     const Type&
#endif

// Support noexcept when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_NOEXCEPT noexcept
# define YY_NOTHROW
#else
# define YY_NOEXCEPT
# define YY_NOTHROW throw ()
#endif

// Support constexpr when possible.
#if 201703 <= YY_CPLUSPLUS
# define YY_CONSTEXPR constexpr
#else
# define YY_CONSTEXPR
#endif
# include "location.hh"
#include <typeinfo>
#ifndef TOOL_ASSERT
# include <cassert>
# define TOOL_ASSERT assert
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Debug traces.  */
#ifndef TOOLDEBUG
# if defined YYDEBUG
#if YYDEBUG
#   define TOOLDEBUG 1
#  else
#   define TOOLDEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define TOOLDEBUG 1
# endif /* ! defined YYDEBUG */
#endif  /* ! defined TOOLDEBUG */

namespace tool {




  /// A Bison parser.
  class Parser
  {
  public:
#ifndef TOOLSTYPE
  /// A buffer to store and retrieve objects.
  ///
  /// Sort of a variant, but does not keep track of the nature
  /// of the stored data, since that knowledge is available
  /// via the current parser state.
  class semantic_type
  {
  public:
    /// Type of *this.
    typedef semantic_type self_type;

    /// Empty construction.
    semantic_type () YY_NOEXCEPT
      : yybuffer_ ()
      , yytypeid_ (YY_NULLPTR)
    {}

    /// Construct and fill.
    template <typename T>
    semantic_type (YY_RVREF (T) t)
      : yytypeid_ (&typeid (T))
    {
      TOOL_ASSERT (sizeof (T) <= size);
      new (yyas_<T> ()) T (YY_MOVE (t));
    }

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    semantic_type (const self_type&) = delete;
    /// Non copyable.
    self_type& operator= (const self_type&) = delete;
#endif

    /// Destruction, allowed only if empty.
    ~semantic_type () YY_NOEXCEPT
    {
      TOOL_ASSERT (!yytypeid_);
    }

# if 201103L <= YY_CPLUSPLUS
    /// Instantiate a \a T in here from \a t.
    template <typename T, typename... U>
    T&
    emplace (U&&... u)
    {
      TOOL_ASSERT (!yytypeid_);
      TOOL_ASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (std::forward <U>(u)...);
    }
# else
    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    emplace ()
    {
      TOOL_ASSERT (!yytypeid_);
      TOOL_ASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T ();
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    emplace (const T& t)
    {
      TOOL_ASSERT (!yytypeid_);
      TOOL_ASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (t);
    }
# endif

    /// Instantiate an empty \a T in here.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build ()
    {
      return emplace<T> ();
    }

    /// Instantiate a \a T in here from \a t.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build (const T& t)
    {
      return emplace<T> (t);
    }

    /// Accessor to a built \a T.
    template <typename T>
    T&
    as () YY_NOEXCEPT
    {
      TOOL_ASSERT (yytypeid_);
      TOOL_ASSERT (*yytypeid_ == typeid (T));
      TOOL_ASSERT (sizeof (T) <= size);
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const YY_NOEXCEPT
    {
      TOOL_ASSERT (yytypeid_);
      TOOL_ASSERT (*yytypeid_ == typeid (T));
      TOOL_ASSERT (sizeof (T) <= size);
      return *yyas_<T> ();
    }

    /// Swap the content with \a that, of same type.
    ///
    /// Both variants must be built beforehand, because swapping the actual
    /// data requires reading it (with as()), and this is not possible on
    /// unconstructed variants: it would require some dynamic testing, which
    /// should not be the variant's responsibility.
    /// Swapping between built and (possibly) non-built is done with
    /// self_type::move ().
    template <typename T>
    void
    swap (self_type& that) YY_NOEXCEPT
    {
      TOOL_ASSERT (yytypeid_);
      TOOL_ASSERT (*yytypeid_ == *that.yytypeid_);
      std::swap (as<T> (), that.as<T> ());
    }

    /// Move the content of \a that to this.
    ///
    /// Destroys \a that.
    template <typename T>
    void
    move (self_type& that)
    {
# if 201103L <= YY_CPLUSPLUS
      emplace<T> (std::move (that.as<T> ()));
# else
      emplace<T> ();
      swap<T> (that);
# endif
      that.destroy<T> ();
    }

# if 201103L <= YY_CPLUSPLUS
    /// Move the content of \a that to this.
    template <typename T>
    void
    move (self_type&& that)
    {
      emplace<T> (std::move (that.as<T> ()));
      that.destroy<T> ();
    }
#endif

    /// Copy the content of \a that to this.
    template <typename T>
    void
    copy (const self_type& that)
    {
      emplace<T> (that.as<T> ());
    }

    /// Destroy the stored \a T.
    template <typename T>
    void
    destroy ()
    {
      as<T> ().~T ();
      yytypeid_ = YY_NULLPTR;
    }

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    semantic_type (const self_type&);
    /// Non copyable.
    self_type& operator= (const self_type&);
#endif

    /// Accessor to raw memory as \a T.
    template <typename T>
    T*
    yyas_ () YY_NOEXCEPT
    {
      void *yyp = yybuffer_.yyraw;
      return static_cast<T*> (yyp);
     }

    /// Const accessor to raw memory as \a T.
    template <typename T>
    const T*
    yyas_ () const YY_NOEXCEPT
    {
      const void *yyp = yybuffer_.yyraw;
      return static_cast<const T*> (yyp);
     }

    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // ArraySubscriptExpr
      char dummy1[sizeof (ArraySubscriptExpr*)];

      // BinaryOperator
      char dummy2[sizeof (BinaryOperator*)];

      // CallExpr
      char dummy3[sizeof (CallExpr*)];

      // SingleVarDecl
      char dummy4[sizeof (Decl*)];

      // DeclRefExpr
      char dummy5[sizeof (DeclRefExpr*)];

      // DeclStmt
      char dummy6[sizeof (DeclStmt*)];

      // InitExpr
      // Expr
      // Literal
      char dummy7[sizeof (Expr*)];

      // InitListExpr
      char dummy8[sizeof (InitListExpr*)];

      // MemberExpr
      char dummy9[sizeof (MemberExpr*)];

      // @1
      // QualType
      char dummy10[sizeof (QualType)];

      // SignStmt
      char dummy11[sizeof (SignStmt*)];

      // Stmt
      // ReturnStmt
      char dummy12[sizeof (Stmt*)];

      // StructDecl
      // @2
      char dummy13[sizeof (StructDecl*)];

      // TranslationUnitDecl
      char dummy14[sizeof (TranslationUnitDecl*)];

      // Type
      char dummy15[sizeof (Type*)];

      // UnaryOperator
      char dummy16[sizeof (UnaryOperator*)];

      // FieldDeclInfo
      char dummy17[sizeof (VarDeclInfo)];

      // ArrowOrPeriod
      char dummy18[sizeof (bool)];

      // "integer"
      // "char"
      // Stars
      // ArrayLenth
      // ArgumentList
      char dummy19[sizeof (int)];

      // "identifier"
      // "type id"
      // "string"
      // VarName
      char dummy20[sizeof (std::string)];

      // VarDecl
      // VarDeclList
      char dummy21[sizeof (std::vector<Decl*>)];

      // ExprList
      char dummy22[sizeof (std::vector<Expr*>)];

      // FieldDecls
      // FieldDecl
      char dummy23[sizeof (std::vector<FieldDecl*>)];

      // FieldDeclInfoList
      char dummy24[sizeof (std::vector<VarDeclInfo>)];

      // ArrayLenthList
      char dummy25[sizeof (std::vector<int>)];
    };

    /// The size of the largest semantic type.
    enum { size = sizeof (union_type) };

    /// A buffer to store semantic values.
    union
    {
      /// Strongest alignment constraints.
      long double yyalign_me;
      /// A buffer large enough to store any of the semantic values.
      char yyraw[size];
    } yybuffer_;

    /// Whether the content is built: if defined, the name of the stored type.
    const std::type_info *yytypeid_;
  };

#else
    typedef TOOLSTYPE semantic_type;
#endif
    /// Symbol locations.
    typedef location location_type;

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const location_type& l, const std::string& m)
        : std::runtime_error (m)
        , location (l)
      {}

      syntax_error (const syntax_error& s)
        : std::runtime_error (s.what ())
        , location (s.location)
      {}

      ~syntax_error () YY_NOEXCEPT YY_NOTHROW;

      location_type location;
    };

    /// Token kinds.
    struct token
    {
      enum token_kind_type
      {
        TOK_TOOLEMPTY = -2,
    TOK_END = 0,                   // "end of file"
    TOK_TOOLerror = 256,           // error
    TOK_TOOLUNDEF = 257,           // "invalid token"
    TOK_LPAREN = 258,              // "("
    TOK_RPAREN = 259,              // ")"
    TOK_LBRACK = 260,              // "["
    TOK_RBRACK = 261,              // "]"
    TOK_LBRACE = 262,              // "{"
    TOK_RBRACE = 263,              // "}"
    TOK_PERIOD = 264,              // "."
    TOK_ARROW = 265,               // "->"
    TOK_SEMICOLON = 266,           // ";"
    TOK_COMMA = 267,               // ","
    TOK_ASSIGN = 268,              // "="
    TOK_PLUS = 269,                // "+"
    TOK_MINUS = 270,               // "-"
    TOK_STAR = 271,                // "*"
    TOK_SLASH = 272,               // "/"
    TOK_PLUSEQ = 273,              // "+="
    TOK_MINUSEQ = 274,             // "-="
    TOK_STAREQ = 275,              // "*="
    TOK_SLASHEQ = 276,             // "/="
    TOK_PERCENT = 277,             // "%"
    TOK_EXEQ = 278,                // "!="
    TOK_EQEQ = 279,                // "=="
    TOK_GREATER = 280,             // ">"
    TOK_LESS = 281,                // "<"
    TOK_GEQ = 282,                 // ">="
    TOK_LEQ = 283,                 // "<="
    TOK_AMPAMP = 284,              // "&&"
    TOK_PIPEPIPE = 285,            // "||"
    TOK_EXCLAIM = 286,             // "!"
    TOK_AMP = 287,                 // "&"
    TOK_PIPE = 288,                // "|"
    TOK_AT = 289,                  // "@"
    TOK_RETURN = 290,              // "return"
    TOK_STRUCT = 291,              // "struct"
    TOK_IDENTIFIER = 292,          // "identifier"
    TOK_TYPEID = 293,              // "type id"
    TOK_INTEGER = 294,             // "integer"
    TOK_CHAR = 295,                // "char"
    TOK_STRING = 296,              // "string"
    TOK_NEG = 297,                 // NEG
    TOK_DEREF = 298                // DEREF
      };
      /// Backward compatibility alias (Bison 3.6).
      typedef token_kind_type yytokentype;
    };

    /// Token kind, as returned by yylex.
    typedef token::yytokentype token_kind_type;

    /// Backward compatibility alias (Bison 3.6).
    typedef token_kind_type token_type;

    /// Symbol kinds.
    struct symbol_kind
    {
      enum symbol_kind_type
      {
        YYNTOKENS = 44, ///< Number of tokens.
        S_YYEMPTY = -2,
        S_YYEOF = 0,                             // "end of file"
        S_YYerror = 1,                           // error
        S_YYUNDEF = 2,                           // "invalid token"
        S_LPAREN = 3,                            // "("
        S_RPAREN = 4,                            // ")"
        S_LBRACK = 5,                            // "["
        S_RBRACK = 6,                            // "]"
        S_LBRACE = 7,                            // "{"
        S_RBRACE = 8,                            // "}"
        S_PERIOD = 9,                            // "."
        S_ARROW = 10,                            // "->"
        S_SEMICOLON = 11,                        // ";"
        S_COMMA = 12,                            // ","
        S_ASSIGN = 13,                           // "="
        S_PLUS = 14,                             // "+"
        S_MINUS = 15,                            // "-"
        S_STAR = 16,                             // "*"
        S_SLASH = 17,                            // "/"
        S_PLUSEQ = 18,                           // "+="
        S_MINUSEQ = 19,                          // "-="
        S_STAREQ = 20,                           // "*="
        S_SLASHEQ = 21,                          // "/="
        S_PERCENT = 22,                          // "%"
        S_EXEQ = 23,                             // "!="
        S_EQEQ = 24,                             // "=="
        S_GREATER = 25,                          // ">"
        S_LESS = 26,                             // "<"
        S_GEQ = 27,                              // ">="
        S_LEQ = 28,                              // "<="
        S_AMPAMP = 29,                           // "&&"
        S_PIPEPIPE = 30,                         // "||"
        S_EXCLAIM = 31,                          // "!"
        S_AMP = 32,                              // "&"
        S_PIPE = 33,                             // "|"
        S_AT = 34,                               // "@"
        S_RETURN = 35,                           // "return"
        S_STRUCT = 36,                           // "struct"
        S_IDENTIFIER = 37,                       // "identifier"
        S_TYPEID = 38,                           // "type id"
        S_INTEGER = 39,                          // "integer"
        S_CHAR = 40,                             // "char"
        S_STRING = 41,                           // "string"
        S_NEG = 42,                              // NEG
        S_DEREF = 43,                            // DEREF
        S_YYACCEPT = 44,                         // $accept
        S_start = 45,                            // start
        S_TranslationUnitDecl = 46,              // TranslationUnitDecl
        S_Stmt = 47,                             // Stmt
        S_DeclStmt = 48,                         // DeclStmt
        S_VarDecl = 49,                          // VarDecl
        S_50_1 = 50,                             // @1
        S_VarDeclList = 51,                      // VarDeclList
        S_SingleVarDecl = 52,                    // SingleVarDecl
        S_QualType = 53,                         // QualType
        S_Type = 54,                             // Type
        S_Stars = 55,                            // Stars
        S_VarName = 56,                          // VarName
        S_ArrayLenthList = 57,                   // ArrayLenthList
        S_ArrayLenth = 58,                       // ArrayLenth
        S_InitExpr = 59,                         // InitExpr
        S_InitListExpr = 60,                     // InitListExpr
        S_ExprList = 61,                         // ExprList
        S_ReturnStmt = 62,                       // ReturnStmt
        S_SignStmt = 63,                         // SignStmt
        S_Expr = 64,                             // Expr
        S_ArraySubscriptExpr = 65,               // ArraySubscriptExpr
        S_BinaryOperator = 66,                   // BinaryOperator
        S_CallExpr = 67,                         // CallExpr
        S_ArgumentList = 68,                     // ArgumentList
        S_DeclRefExpr = 69,                      // DeclRefExpr
        S_MemberExpr = 70,                       // MemberExpr
        S_ArrowOrPeriod = 71,                    // ArrowOrPeriod
        S_UnaryOperator = 72,                    // UnaryOperator
        S_Literal = 73,                          // Literal
        S_StructDecl = 74,                       // StructDecl
        S_75_2 = 75,                             // @2
        S_FieldDecls = 76,                       // FieldDecls
        S_FieldDecl = 77,                        // FieldDecl
        S_FieldDeclInfoList = 78,                // FieldDeclInfoList
        S_FieldDeclInfo = 79                     // FieldDeclInfo
      };
    };

    /// (Internal) symbol kind.
    typedef symbol_kind::symbol_kind_type symbol_kind_type;

    /// The number of tokens.
    static const symbol_kind_type YYNTOKENS = symbol_kind::YYNTOKENS;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol kind
    /// via kind ().
    ///
    /// Provide access to semantic value and location.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol ()
        : value ()
        , location ()
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      basic_symbol (basic_symbol&& that)
        : Base (std::move (that))
        , value ()
        , location (std::move (that.location))
      {
        switch (this->kind ())
    {
      case symbol_kind::S_ArraySubscriptExpr: // ArraySubscriptExpr
        value.move< ArraySubscriptExpr* > (std::move (that.value));
        break;

      case symbol_kind::S_BinaryOperator: // BinaryOperator
        value.move< BinaryOperator* > (std::move (that.value));
        break;

      case symbol_kind::S_CallExpr: // CallExpr
        value.move< CallExpr* > (std::move (that.value));
        break;

      case symbol_kind::S_SingleVarDecl: // SingleVarDecl
        value.move< Decl* > (std::move (that.value));
        break;

      case symbol_kind::S_DeclRefExpr: // DeclRefExpr
        value.move< DeclRefExpr* > (std::move (that.value));
        break;

      case symbol_kind::S_DeclStmt: // DeclStmt
        value.move< DeclStmt* > (std::move (that.value));
        break;

      case symbol_kind::S_InitExpr: // InitExpr
      case symbol_kind::S_Expr: // Expr
      case symbol_kind::S_Literal: // Literal
        value.move< Expr* > (std::move (that.value));
        break;

      case symbol_kind::S_InitListExpr: // InitListExpr
        value.move< InitListExpr* > (std::move (that.value));
        break;

      case symbol_kind::S_MemberExpr: // MemberExpr
        value.move< MemberExpr* > (std::move (that.value));
        break;

      case symbol_kind::S_50_1: // @1
      case symbol_kind::S_QualType: // QualType
        value.move< QualType > (std::move (that.value));
        break;

      case symbol_kind::S_SignStmt: // SignStmt
        value.move< SignStmt* > (std::move (that.value));
        break;

      case symbol_kind::S_Stmt: // Stmt
      case symbol_kind::S_ReturnStmt: // ReturnStmt
        value.move< Stmt* > (std::move (that.value));
        break;

      case symbol_kind::S_StructDecl: // StructDecl
      case symbol_kind::S_75_2: // @2
        value.move< StructDecl* > (std::move (that.value));
        break;

      case symbol_kind::S_TranslationUnitDecl: // TranslationUnitDecl
        value.move< TranslationUnitDecl* > (std::move (that.value));
        break;

      case symbol_kind::S_Type: // Type
        value.move< Type* > (std::move (that.value));
        break;

      case symbol_kind::S_UnaryOperator: // UnaryOperator
        value.move< UnaryOperator* > (std::move (that.value));
        break;

      case symbol_kind::S_FieldDeclInfo: // FieldDeclInfo
        value.move< VarDeclInfo > (std::move (that.value));
        break;

      case symbol_kind::S_ArrowOrPeriod: // ArrowOrPeriod
        value.move< bool > (std::move (that.value));
        break;

      case symbol_kind::S_INTEGER: // "integer"
      case symbol_kind::S_CHAR: // "char"
      case symbol_kind::S_Stars: // Stars
      case symbol_kind::S_ArrayLenth: // ArrayLenth
      case symbol_kind::S_ArgumentList: // ArgumentList
        value.move< int > (std::move (that.value));
        break;

      case symbol_kind::S_IDENTIFIER: // "identifier"
      case symbol_kind::S_TYPEID: // "type id"
      case symbol_kind::S_STRING: // "string"
      case symbol_kind::S_VarName: // VarName
        value.move< std::string > (std::move (that.value));
        break;

      case symbol_kind::S_VarDecl: // VarDecl
      case symbol_kind::S_VarDeclList: // VarDeclList
        value.move< std::vector<Decl*> > (std::move (that.value));
        break;

      case symbol_kind::S_ExprList: // ExprList
        value.move< std::vector<Expr*> > (std::move (that.value));
        break;

      case symbol_kind::S_FieldDecls: // FieldDecls
      case symbol_kind::S_FieldDecl: // FieldDecl
        value.move< std::vector<FieldDecl*> > (std::move (that.value));
        break;

      case symbol_kind::S_FieldDeclInfoList: // FieldDeclInfoList
        value.move< std::vector<VarDeclInfo> > (std::move (that.value));
        break;

      case symbol_kind::S_ArrayLenthList: // ArrayLenthList
        value.move< std::vector<int> > (std::move (that.value));
        break;

      default:
        break;
    }

      }
#endif

      /// Copy constructor.
      basic_symbol (const basic_symbol& that);

      /// Constructors for typed symbols.
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, location_type&& l)
        : Base (t)
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const location_type& l)
        : Base (t)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ArraySubscriptExpr*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ArraySubscriptExpr*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, BinaryOperator*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const BinaryOperator*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, CallExpr*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const CallExpr*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, Decl*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const Decl*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, DeclRefExpr*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const DeclRefExpr*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, DeclStmt*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const DeclStmt*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, Expr*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const Expr*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, InitListExpr*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const InitListExpr*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, MemberExpr*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const MemberExpr*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, QualType&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const QualType& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, SignStmt*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const SignStmt*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, Stmt*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const Stmt*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, StructDecl*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const StructDecl*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, TranslationUnitDecl*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const TranslationUnitDecl*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, Type*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const Type*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, UnaryOperator*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const UnaryOperator*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, VarDeclInfo&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const VarDeclInfo& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, bool&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const bool& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, int&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const int& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::string&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::string& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<Decl*>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<Decl*>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<Expr*>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<Expr*>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<FieldDecl*>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<FieldDecl*>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<VarDeclInfo>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<VarDeclInfo>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<int>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<int>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

      /// Destroy the symbol.
      ~basic_symbol ()
      {
        clear ();
      }

      /// Destroy contents, and record that is empty.
      void clear ()
      {
        // User destructor.
        symbol_kind_type yykind = this->kind ();
        basic_symbol<Base>& yysym = *this;
        (void) yysym;
        switch (yykind)
        {
       default:
          break;
        }

        // Value type destructor.
switch (yykind)
    {
      case symbol_kind::S_ArraySubscriptExpr: // ArraySubscriptExpr
        value.template destroy< ArraySubscriptExpr* > ();
        break;

      case symbol_kind::S_BinaryOperator: // BinaryOperator
        value.template destroy< BinaryOperator* > ();
        break;

      case symbol_kind::S_CallExpr: // CallExpr
        value.template destroy< CallExpr* > ();
        break;

      case symbol_kind::S_SingleVarDecl: // SingleVarDecl
        value.template destroy< Decl* > ();
        break;

      case symbol_kind::S_DeclRefExpr: // DeclRefExpr
        value.template destroy< DeclRefExpr* > ();
        break;

      case symbol_kind::S_DeclStmt: // DeclStmt
        value.template destroy< DeclStmt* > ();
        break;

      case symbol_kind::S_InitExpr: // InitExpr
      case symbol_kind::S_Expr: // Expr
      case symbol_kind::S_Literal: // Literal
        value.template destroy< Expr* > ();
        break;

      case symbol_kind::S_InitListExpr: // InitListExpr
        value.template destroy< InitListExpr* > ();
        break;

      case symbol_kind::S_MemberExpr: // MemberExpr
        value.template destroy< MemberExpr* > ();
        break;

      case symbol_kind::S_50_1: // @1
      case symbol_kind::S_QualType: // QualType
        value.template destroy< QualType > ();
        break;

      case symbol_kind::S_SignStmt: // SignStmt
        value.template destroy< SignStmt* > ();
        break;

      case symbol_kind::S_Stmt: // Stmt
      case symbol_kind::S_ReturnStmt: // ReturnStmt
        value.template destroy< Stmt* > ();
        break;

      case symbol_kind::S_StructDecl: // StructDecl
      case symbol_kind::S_75_2: // @2
        value.template destroy< StructDecl* > ();
        break;

      case symbol_kind::S_TranslationUnitDecl: // TranslationUnitDecl
        value.template destroy< TranslationUnitDecl* > ();
        break;

      case symbol_kind::S_Type: // Type
        value.template destroy< Type* > ();
        break;

      case symbol_kind::S_UnaryOperator: // UnaryOperator
        value.template destroy< UnaryOperator* > ();
        break;

      case symbol_kind::S_FieldDeclInfo: // FieldDeclInfo
        value.template destroy< VarDeclInfo > ();
        break;

      case symbol_kind::S_ArrowOrPeriod: // ArrowOrPeriod
        value.template destroy< bool > ();
        break;

      case symbol_kind::S_INTEGER: // "integer"
      case symbol_kind::S_CHAR: // "char"
      case symbol_kind::S_Stars: // Stars
      case symbol_kind::S_ArrayLenth: // ArrayLenth
      case symbol_kind::S_ArgumentList: // ArgumentList
        value.template destroy< int > ();
        break;

      case symbol_kind::S_IDENTIFIER: // "identifier"
      case symbol_kind::S_TYPEID: // "type id"
      case symbol_kind::S_STRING: // "string"
      case symbol_kind::S_VarName: // VarName
        value.template destroy< std::string > ();
        break;

      case symbol_kind::S_VarDecl: // VarDecl
      case symbol_kind::S_VarDeclList: // VarDeclList
        value.template destroy< std::vector<Decl*> > ();
        break;

      case symbol_kind::S_ExprList: // ExprList
        value.template destroy< std::vector<Expr*> > ();
        break;

      case symbol_kind::S_FieldDecls: // FieldDecls
      case symbol_kind::S_FieldDecl: // FieldDecl
        value.template destroy< std::vector<FieldDecl*> > ();
        break;

      case symbol_kind::S_FieldDeclInfoList: // FieldDeclInfoList
        value.template destroy< std::vector<VarDeclInfo> > ();
        break;

      case symbol_kind::S_ArrayLenthList: // ArrayLenthList
        value.template destroy< std::vector<int> > ();
        break;

      default:
        break;
    }

        Base::clear ();
      }

      /// The user-facing name of this symbol.
      std::string name () const YY_NOEXCEPT
      {
        return Parser::symbol_name (this->kind ());
      }

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// Whether empty.
      bool empty () const YY_NOEXCEPT;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      semantic_type value;

      /// The location.
      location_type location;

    private:
#if YY_CPLUSPLUS < 201103L
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& that);
#endif
    };

    /// Type access provider for token (enum) based symbols.
    struct by_kind
    {
      /// Default constructor.
      by_kind ();

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      by_kind (by_kind&& that) noexcept;
#endif

      /// Copy constructor.
      by_kind (const by_kind& that);

      /// The symbol kind as needed by the constructor.
      typedef token_kind_type kind_type;

      /// Constructor from (external) token numbers.
      by_kind (kind_type t);

      /// Record that this symbol is empty.
      void clear ();

      /// Steal the symbol kind from \a that.
      void move (by_kind& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// The symbol kind.
      /// \a S_YYEMPTY when empty.
      symbol_kind_type kind_;
    };

    /// Backward compatibility for a private implementation detail (Bison 3.6).
    typedef by_kind by_type;

    /// "External" symbols: returned by the scanner.
    struct symbol_type : basic_symbol<by_kind>
    {
      /// Superclass.
      typedef basic_symbol<by_kind> super_type;

      /// Empty symbol.
      symbol_type () {}

      /// Constructor for valueless symbols, and symbols from each type.
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, location_type l)
        : super_type(token_type (tok), std::move (l))
#else
      symbol_type (int tok, const location_type& l)
        : super_type(token_type (tok), l)
#endif
      {
        TOOL_ASSERT (tok == token::TOK_END
                   || (token::TOK_TOOLerror <= tok && tok <= token::TOK_STRUCT)
                   || (token::TOK_NEG <= tok && tok <= token::TOK_DEREF));
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, int v, location_type l)
        : super_type(token_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const int& v, const location_type& l)
        : super_type(token_type (tok), v, l)
#endif
      {
        TOOL_ASSERT ((token::TOK_INTEGER <= tok && tok <= token::TOK_CHAR));
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, std::string v, location_type l)
        : super_type(token_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const std::string& v, const location_type& l)
        : super_type(token_type (tok), v, l)
#endif
      {
        TOOL_ASSERT ((token::TOK_IDENTIFIER <= tok && tok <= token::TOK_TYPEID)
                   || tok == token::TOK_STRING);
      }
    };

    /// Build a parser object.
    Parser (class Driver &driver_yyarg);
    virtual ~Parser ();

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    Parser (const Parser&) = delete;
    /// Non copyable.
    Parser& operator= (const Parser&) = delete;
#endif

    /// Parse.  An alias for parse ().
    /// \returns  0 iff parsing succeeded.
    int operator() ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if TOOLDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param loc    where the syntax error is found.
    /// \param msg    a description of the syntax error.
    virtual void error (const location_type& loc, const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

    /// The user-facing name of the symbol whose (internal) number is
    /// YYSYMBOL.  No bounds checking.
    static std::string symbol_name (symbol_kind_type yysymbol);

    // Implementation of make_symbol for each symbol type.
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_END (location_type l)
      {
        return symbol_type (token::TOK_END, std::move (l));
      }
#else
      static
      symbol_type
      make_END (const location_type& l)
      {
        return symbol_type (token::TOK_END, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOOLerror (location_type l)
      {
        return symbol_type (token::TOK_TOOLerror, std::move (l));
      }
#else
      static
      symbol_type
      make_TOOLerror (const location_type& l)
      {
        return symbol_type (token::TOK_TOOLerror, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOOLUNDEF (location_type l)
      {
        return symbol_type (token::TOK_TOOLUNDEF, std::move (l));
      }
#else
      static
      symbol_type
      make_TOOLUNDEF (const location_type& l)
      {
        return symbol_type (token::TOK_TOOLUNDEF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LPAREN (location_type l)
      {
        return symbol_type (token::TOK_LPAREN, std::move (l));
      }
#else
      static
      symbol_type
      make_LPAREN (const location_type& l)
      {
        return symbol_type (token::TOK_LPAREN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RPAREN (location_type l)
      {
        return symbol_type (token::TOK_RPAREN, std::move (l));
      }
#else
      static
      symbol_type
      make_RPAREN (const location_type& l)
      {
        return symbol_type (token::TOK_RPAREN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LBRACK (location_type l)
      {
        return symbol_type (token::TOK_LBRACK, std::move (l));
      }
#else
      static
      symbol_type
      make_LBRACK (const location_type& l)
      {
        return symbol_type (token::TOK_LBRACK, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RBRACK (location_type l)
      {
        return symbol_type (token::TOK_RBRACK, std::move (l));
      }
#else
      static
      symbol_type
      make_RBRACK (const location_type& l)
      {
        return symbol_type (token::TOK_RBRACK, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LBRACE (location_type l)
      {
        return symbol_type (token::TOK_LBRACE, std::move (l));
      }
#else
      static
      symbol_type
      make_LBRACE (const location_type& l)
      {
        return symbol_type (token::TOK_LBRACE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RBRACE (location_type l)
      {
        return symbol_type (token::TOK_RBRACE, std::move (l));
      }
#else
      static
      symbol_type
      make_RBRACE (const location_type& l)
      {
        return symbol_type (token::TOK_RBRACE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PERIOD (location_type l)
      {
        return symbol_type (token::TOK_PERIOD, std::move (l));
      }
#else
      static
      symbol_type
      make_PERIOD (const location_type& l)
      {
        return symbol_type (token::TOK_PERIOD, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ARROW (location_type l)
      {
        return symbol_type (token::TOK_ARROW, std::move (l));
      }
#else
      static
      symbol_type
      make_ARROW (const location_type& l)
      {
        return symbol_type (token::TOK_ARROW, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SEMICOLON (location_type l)
      {
        return symbol_type (token::TOK_SEMICOLON, std::move (l));
      }
#else
      static
      symbol_type
      make_SEMICOLON (const location_type& l)
      {
        return symbol_type (token::TOK_SEMICOLON, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_COMMA (location_type l)
      {
        return symbol_type (token::TOK_COMMA, std::move (l));
      }
#else
      static
      symbol_type
      make_COMMA (const location_type& l)
      {
        return symbol_type (token::TOK_COMMA, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ASSIGN (location_type l)
      {
        return symbol_type (token::TOK_ASSIGN, std::move (l));
      }
#else
      static
      symbol_type
      make_ASSIGN (const location_type& l)
      {
        return symbol_type (token::TOK_ASSIGN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PLUS (location_type l)
      {
        return symbol_type (token::TOK_PLUS, std::move (l));
      }
#else
      static
      symbol_type
      make_PLUS (const location_type& l)
      {
        return symbol_type (token::TOK_PLUS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MINUS (location_type l)
      {
        return symbol_type (token::TOK_MINUS, std::move (l));
      }
#else
      static
      symbol_type
      make_MINUS (const location_type& l)
      {
        return symbol_type (token::TOK_MINUS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_STAR (location_type l)
      {
        return symbol_type (token::TOK_STAR, std::move (l));
      }
#else
      static
      symbol_type
      make_STAR (const location_type& l)
      {
        return symbol_type (token::TOK_STAR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SLASH (location_type l)
      {
        return symbol_type (token::TOK_SLASH, std::move (l));
      }
#else
      static
      symbol_type
      make_SLASH (const location_type& l)
      {
        return symbol_type (token::TOK_SLASH, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PLUSEQ (location_type l)
      {
        return symbol_type (token::TOK_PLUSEQ, std::move (l));
      }
#else
      static
      symbol_type
      make_PLUSEQ (const location_type& l)
      {
        return symbol_type (token::TOK_PLUSEQ, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MINUSEQ (location_type l)
      {
        return symbol_type (token::TOK_MINUSEQ, std::move (l));
      }
#else
      static
      symbol_type
      make_MINUSEQ (const location_type& l)
      {
        return symbol_type (token::TOK_MINUSEQ, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_STAREQ (location_type l)
      {
        return symbol_type (token::TOK_STAREQ, std::move (l));
      }
#else
      static
      symbol_type
      make_STAREQ (const location_type& l)
      {
        return symbol_type (token::TOK_STAREQ, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SLASHEQ (location_type l)
      {
        return symbol_type (token::TOK_SLASHEQ, std::move (l));
      }
#else
      static
      symbol_type
      make_SLASHEQ (const location_type& l)
      {
        return symbol_type (token::TOK_SLASHEQ, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PERCENT (location_type l)
      {
        return symbol_type (token::TOK_PERCENT, std::move (l));
      }
#else
      static
      symbol_type
      make_PERCENT (const location_type& l)
      {
        return symbol_type (token::TOK_PERCENT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EXEQ (location_type l)
      {
        return symbol_type (token::TOK_EXEQ, std::move (l));
      }
#else
      static
      symbol_type
      make_EXEQ (const location_type& l)
      {
        return symbol_type (token::TOK_EXEQ, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EQEQ (location_type l)
      {
        return symbol_type (token::TOK_EQEQ, std::move (l));
      }
#else
      static
      symbol_type
      make_EQEQ (const location_type& l)
      {
        return symbol_type (token::TOK_EQEQ, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_GREATER (location_type l)
      {
        return symbol_type (token::TOK_GREATER, std::move (l));
      }
#else
      static
      symbol_type
      make_GREATER (const location_type& l)
      {
        return symbol_type (token::TOK_GREATER, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LESS (location_type l)
      {
        return symbol_type (token::TOK_LESS, std::move (l));
      }
#else
      static
      symbol_type
      make_LESS (const location_type& l)
      {
        return symbol_type (token::TOK_LESS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_GEQ (location_type l)
      {
        return symbol_type (token::TOK_GEQ, std::move (l));
      }
#else
      static
      symbol_type
      make_GEQ (const location_type& l)
      {
        return symbol_type (token::TOK_GEQ, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LEQ (location_type l)
      {
        return symbol_type (token::TOK_LEQ, std::move (l));
      }
#else
      static
      symbol_type
      make_LEQ (const location_type& l)
      {
        return symbol_type (token::TOK_LEQ, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_AMPAMP (location_type l)
      {
        return symbol_type (token::TOK_AMPAMP, std::move (l));
      }
#else
      static
      symbol_type
      make_AMPAMP (const location_type& l)
      {
        return symbol_type (token::TOK_AMPAMP, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PIPEPIPE (location_type l)
      {
        return symbol_type (token::TOK_PIPEPIPE, std::move (l));
      }
#else
      static
      symbol_type
      make_PIPEPIPE (const location_type& l)
      {
        return symbol_type (token::TOK_PIPEPIPE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EXCLAIM (location_type l)
      {
        return symbol_type (token::TOK_EXCLAIM, std::move (l));
      }
#else
      static
      symbol_type
      make_EXCLAIM (const location_type& l)
      {
        return symbol_type (token::TOK_EXCLAIM, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_AMP (location_type l)
      {
        return symbol_type (token::TOK_AMP, std::move (l));
      }
#else
      static
      symbol_type
      make_AMP (const location_type& l)
      {
        return symbol_type (token::TOK_AMP, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PIPE (location_type l)
      {
        return symbol_type (token::TOK_PIPE, std::move (l));
      }
#else
      static
      symbol_type
      make_PIPE (const location_type& l)
      {
        return symbol_type (token::TOK_PIPE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_AT (location_type l)
      {
        return symbol_type (token::TOK_AT, std::move (l));
      }
#else
      static
      symbol_type
      make_AT (const location_type& l)
      {
        return symbol_type (token::TOK_AT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RETURN (location_type l)
      {
        return symbol_type (token::TOK_RETURN, std::move (l));
      }
#else
      static
      symbol_type
      make_RETURN (const location_type& l)
      {
        return symbol_type (token::TOK_RETURN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_STRUCT (location_type l)
      {
        return symbol_type (token::TOK_STRUCT, std::move (l));
      }
#else
      static
      symbol_type
      make_STRUCT (const location_type& l)
      {
        return symbol_type (token::TOK_STRUCT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IDENTIFIER (std::string v, location_type l)
      {
        return symbol_type (token::TOK_IDENTIFIER, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_IDENTIFIER (const std::string& v, const location_type& l)
      {
        return symbol_type (token::TOK_IDENTIFIER, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TYPEID (std::string v, location_type l)
      {
        return symbol_type (token::TOK_TYPEID, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_TYPEID (const std::string& v, const location_type& l)
      {
        return symbol_type (token::TOK_TYPEID, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_INTEGER (int v, location_type l)
      {
        return symbol_type (token::TOK_INTEGER, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_INTEGER (const int& v, const location_type& l)
      {
        return symbol_type (token::TOK_INTEGER, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CHAR (int v, location_type l)
      {
        return symbol_type (token::TOK_CHAR, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_CHAR (const int& v, const location_type& l)
      {
        return symbol_type (token::TOK_CHAR, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_STRING (std::string v, location_type l)
      {
        return symbol_type (token::TOK_STRING, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_STRING (const std::string& v, const location_type& l)
      {
        return symbol_type (token::TOK_STRING, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NEG (location_type l)
      {
        return symbol_type (token::TOK_NEG, std::move (l));
      }
#else
      static
      symbol_type
      make_NEG (const location_type& l)
      {
        return symbol_type (token::TOK_NEG, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DEREF (location_type l)
      {
        return symbol_type (token::TOK_DEREF, std::move (l));
      }
#else
      static
      symbol_type
      make_DEREF (const location_type& l)
      {
        return symbol_type (token::TOK_DEREF, l);
      }
#endif


    class context
    {
    public:
      context (const Parser& yyparser, const symbol_type& yyla);
      const symbol_type& lookahead () const { return yyla_; }
      symbol_kind_type token () const { return yyla_.kind (); }
      const location_type& location () const { return yyla_.location; }

      /// Put in YYARG at most YYARGN of the expected tokens, and return the
      /// number of tokens stored in YYARG.  If YYARG is null, return the
      /// number of expected tokens (guaranteed to be less than YYNTOKENS).
      int expected_tokens (symbol_kind_type yyarg[], int yyargn) const;

    private:
      const Parser& yyparser_;
      const symbol_type& yyla_;
    };

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    Parser (const Parser&);
    /// Non copyable.
    Parser& operator= (const Parser&);
#endif


    /// Stored state numbers (used for stacks).
    typedef unsigned char state_type;

    /// The arguments of the error message.
    int yy_syntax_error_arguments_ (const context& yyctx,
                                    symbol_kind_type yyarg[], int yyargn) const;

    /// Generate an error message.
    /// \param yyctx     the context in which the error occurred.
    virtual std::string yysyntax_error_ (const context& yyctx) const;
    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    static state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue);

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue);

    static const signed char yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token kind \a t to a symbol kind.
    /// In theory \a t should be a token_kind_type, but character literals
    /// are valid, yet not members of the token_type enum.
    static symbol_kind_type yytranslate_ (int t);

    /// Convert the symbol name \a n to a form suitable for a diagnostic.
    static std::string yytnamerr_ (const char *yystr);

    /// For a symbol, its name in clear.
    static const char* const yytname_[];


    // Tables.
    // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
    // STATE-NUM.
    static const short yypact_[];

    // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
    // Performed when YYTABLE does not specify something else to do.  Zero
    // means the default is an error.
    static const signed char yydefact_[];

    // YYPGOTO[NTERM-NUM].
    static const signed char yypgoto_[];

    // YYDEFGOTO[NTERM-NUM].
    static const signed char yydefgoto_[];

    // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
    // positive, shift that token.  If negative, reduce the rule whose
    // number is the opposite.  If YYTABLE_NINF, syntax error.
    static const short yytable_[];

    static const short yycheck_[];

    // YYSTOS[STATE-NUM] -- The (internal number of the) accessing
    // symbol of state STATE-NUM.
    static const signed char yystos_[];

    // YYR1[YYN] -- Symbol number of symbol that rule YYN derives.
    static const signed char yyr1_[];

    // YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.
    static const signed char yyr2_[];


#if TOOLDEBUG
    // YYRLINE[YYN] -- Source line where rule number YYN was defined.
    static const short yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r) const;
    /// Print the state stack on the debug stream.
    virtual void yy_stack_print_ () const;

    /// Debugging level.
    int yydebug_;
    /// Debug stream.
    std::ostream* yycdebug_;

    /// \brief Display a symbol kind, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state () YY_NOEXCEPT;

      /// The symbol kind as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s) YY_NOEXCEPT;

      /// Copy constructor.
      by_state (const by_state& that) YY_NOEXCEPT;

      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_state& that);

      /// The symbol kind (corresponding to \a state).
      /// \a symbol_kind::S_YYEMPTY when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// The state number used to denote an empty symbol.
      /// We use the initial state, as it does not have a value.
      enum { empty_state = 0 };

      /// The state.
      /// \a empty when empty.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Move or copy construction.
      stack_symbol_type (YY_RVREF (stack_symbol_type) that) noexcept;
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) sym);
#if YY_CPLUSPLUS < 201103L
      /// Assignment, needed by push_back by some old implementations.
      /// Moves the contents of that.
      stack_symbol_type& operator= (stack_symbol_type& that);

      /// Assignment, needed by push_back by other implementations.
      /// Needed by some other old implementations.
      stack_symbol_type& operator= (const stack_symbol_type& that);
#endif
    };

    /// A stack with random access from its top.
    template <typename T, typename S = std::vector<T> >
    class stack
    {
    public:
      // Hide our reversed order.
      typedef typename S::iterator iterator;
      typedef typename S::const_iterator const_iterator;
      typedef typename S::size_type size_type;
      typedef typename std::ptrdiff_t index_type;

      stack (size_type n = 200)
        : seq_ (n)
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Non copyable.
      stack (const stack&) = delete;
      /// Non copyable.
      stack& operator= (const stack&) = delete;
#endif

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      const T&
      operator[] (index_type i) const
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      T&
      operator[] (index_type i)
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Steal the contents of \a t.
      ///
      /// Close to move-semantics.
      void
      push (YY_MOVE_REF (T) t)
      {
        seq_.push_back (T ());
        operator[] (0).move (t);
      }

      /// Pop elements from the stack.
      void
      pop (std::ptrdiff_t n = 1) YY_NOEXCEPT
      {
        for (; 0 < n; --n)
          seq_.pop_back ();
      }

      /// Pop all elements from the stack.
      void
      clear () YY_NOEXCEPT
      {
        seq_.clear ();
      }

      /// Number of elements on the stack.
      index_type
      size () const YY_NOEXCEPT
      {
        return index_type (seq_.size ());
      }

      /// Iterator on top of the stack (going downwards).
      const_iterator
      begin () const YY_NOEXCEPT
      {
        return seq_.begin ();
      }

      /// Bottom of the stack.
      const_iterator
      end () const YY_NOEXCEPT
      {
        return seq_.end ();
      }

      /// Present a slice of the top of a stack.
      class slice
      {
      public:
        slice (const stack& stack, index_type range)
          : stack_ (stack)
          , range_ (range)
        {}

        const T&
        operator[] (index_type i) const
        {
          return stack_[range_ - i];
        }

      private:
        const stack& stack_;
        index_type range_;
      };

    private:
#if YY_CPLUSPLUS < 201103L
      /// Non copyable.
      stack (const stack&);
      /// Non copyable.
      stack& operator= (const stack&);
#endif
      /// The wrapped container.
      S seq_;
    };


    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param sym  the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a sym.value is stolen.
    void yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym);

    /// Pop \a n symbols from the stack.
    void yypop_ (int n = 1);

    /// Constants.
    enum
    {
      yylast_ = 307,     ///< Last index in yytable_.
      yynnts_ = 36,  ///< Number of nonterminal symbols.
      yyfinal_ = 3 ///< Termination state number.
    };


    // User arguments.
    class Driver &driver;

  };

  inline
  Parser::symbol_kind_type
  Parser::yytranslate_ (int t)
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const signed char
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43
    };
    // Last valid token kind.
    const int code_max = 298;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return YY_CAST (symbol_kind_type, translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

  // basic_symbol.
  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
    , location (that.location)
  {
    switch (this->kind ())
    {
      case symbol_kind::S_ArraySubscriptExpr: // ArraySubscriptExpr
        value.copy< ArraySubscriptExpr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_BinaryOperator: // BinaryOperator
        value.copy< BinaryOperator* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_CallExpr: // CallExpr
        value.copy< CallExpr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_SingleVarDecl: // SingleVarDecl
        value.copy< Decl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_DeclRefExpr: // DeclRefExpr
        value.copy< DeclRefExpr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_DeclStmt: // DeclStmt
        value.copy< DeclStmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_InitExpr: // InitExpr
      case symbol_kind::S_Expr: // Expr
      case symbol_kind::S_Literal: // Literal
        value.copy< Expr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_InitListExpr: // InitListExpr
        value.copy< InitListExpr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_MemberExpr: // MemberExpr
        value.copy< MemberExpr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_50_1: // @1
      case symbol_kind::S_QualType: // QualType
        value.copy< QualType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_SignStmt: // SignStmt
        value.copy< SignStmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Stmt: // Stmt
      case symbol_kind::S_ReturnStmt: // ReturnStmt
        value.copy< Stmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_StructDecl: // StructDecl
      case symbol_kind::S_75_2: // @2
        value.copy< StructDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TranslationUnitDecl: // TranslationUnitDecl
        value.copy< TranslationUnitDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Type: // Type
        value.copy< Type* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_UnaryOperator: // UnaryOperator
        value.copy< UnaryOperator* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FieldDeclInfo: // FieldDeclInfo
        value.copy< VarDeclInfo > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ArrowOrPeriod: // ArrowOrPeriod
        value.copy< bool > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INTEGER: // "integer"
      case symbol_kind::S_CHAR: // "char"
      case symbol_kind::S_Stars: // Stars
      case symbol_kind::S_ArrayLenth: // ArrayLenth
      case symbol_kind::S_ArgumentList: // ArgumentList
        value.copy< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENTIFIER: // "identifier"
      case symbol_kind::S_TYPEID: // "type id"
      case symbol_kind::S_STRING: // "string"
      case symbol_kind::S_VarName: // VarName
        value.copy< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_VarDecl: // VarDecl
      case symbol_kind::S_VarDeclList: // VarDeclList
        value.copy< std::vector<Decl*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ExprList: // ExprList
        value.copy< std::vector<Expr*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FieldDecls: // FieldDecls
      case symbol_kind::S_FieldDecl: // FieldDecl
        value.copy< std::vector<FieldDecl*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FieldDeclInfoList: // FieldDeclInfoList
        value.copy< std::vector<VarDeclInfo> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ArrayLenthList: // ArrayLenthList
        value.copy< std::vector<int> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

  }



  template <typename Base>
  Parser::symbol_kind_type
  Parser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }

  template <typename Base>
  bool
  Parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->kind ())
    {
      case symbol_kind::S_ArraySubscriptExpr: // ArraySubscriptExpr
        value.move< ArraySubscriptExpr* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_BinaryOperator: // BinaryOperator
        value.move< BinaryOperator* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_CallExpr: // CallExpr
        value.move< CallExpr* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_SingleVarDecl: // SingleVarDecl
        value.move< Decl* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_DeclRefExpr: // DeclRefExpr
        value.move< DeclRefExpr* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_DeclStmt: // DeclStmt
        value.move< DeclStmt* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_InitExpr: // InitExpr
      case symbol_kind::S_Expr: // Expr
      case symbol_kind::S_Literal: // Literal
        value.move< Expr* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_InitListExpr: // InitListExpr
        value.move< InitListExpr* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_MemberExpr: // MemberExpr
        value.move< MemberExpr* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_50_1: // @1
      case symbol_kind::S_QualType: // QualType
        value.move< QualType > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_SignStmt: // SignStmt
        value.move< SignStmt* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_Stmt: // Stmt
      case symbol_kind::S_ReturnStmt: // ReturnStmt
        value.move< Stmt* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_StructDecl: // StructDecl
      case symbol_kind::S_75_2: // @2
        value.move< StructDecl* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_TranslationUnitDecl: // TranslationUnitDecl
        value.move< TranslationUnitDecl* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_Type: // Type
        value.move< Type* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_UnaryOperator: // UnaryOperator
        value.move< UnaryOperator* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_FieldDeclInfo: // FieldDeclInfo
        value.move< VarDeclInfo > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_ArrowOrPeriod: // ArrowOrPeriod
        value.move< bool > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_INTEGER: // "integer"
      case symbol_kind::S_CHAR: // "char"
      case symbol_kind::S_Stars: // Stars
      case symbol_kind::S_ArrayLenth: // ArrayLenth
      case symbol_kind::S_ArgumentList: // ArgumentList
        value.move< int > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_IDENTIFIER: // "identifier"
      case symbol_kind::S_TYPEID: // "type id"
      case symbol_kind::S_STRING: // "string"
      case symbol_kind::S_VarName: // VarName
        value.move< std::string > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_VarDecl: // VarDecl
      case symbol_kind::S_VarDeclList: // VarDeclList
        value.move< std::vector<Decl*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_ExprList: // ExprList
        value.move< std::vector<Expr*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_FieldDecls: // FieldDecls
      case symbol_kind::S_FieldDecl: // FieldDecl
        value.move< std::vector<FieldDecl*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_FieldDeclInfoList: // FieldDeclInfoList
        value.move< std::vector<VarDeclInfo> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_ArrayLenthList: // ArrayLenthList
        value.move< std::vector<int> > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

    location = YY_MOVE (s.location);
  }

  // by_kind.
  inline
  Parser::by_kind::by_kind ()
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  inline
  Parser::by_kind::by_kind (by_kind&& that) noexcept
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  inline
  Parser::by_kind::by_kind (const by_kind& that)
    : kind_ (that.kind_)
  {}

  inline
  Parser::by_kind::by_kind (token_kind_type t)
    : kind_ (yytranslate_ (t))
  {}

  inline
  void
  Parser::by_kind::clear ()
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  inline
  void
  Parser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  inline
  Parser::symbol_kind_type
  Parser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }

  inline
  Parser::symbol_kind_type
  Parser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }

} // tool




#endif // !YY_TOOL_PARSER_H_INCLUDED
