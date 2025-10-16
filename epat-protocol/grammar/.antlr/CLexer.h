
// Generated from c://Projects//epat++//epat-protocol//grammar//C.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"




class  CLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, Auto = 2, Break = 3, Case = 4, Char = 5, Const = 6, Continue = 7, 
    Default = 8, Do = 9, Double = 10, Else = 11, Enum = 12, Extern = 13, 
    Float = 14, For = 15, Goto = 16, If = 17, Inline = 18, Int = 19, Long = 20, 
    Register = 21, Restrict = 22, Return = 23, Short = 24, Signed = 25, 
    Sizeof = 26, Static = 27, Struct = 28, Switch = 29, Typedef = 30, Union = 31, 
    Unsigned = 32, Void = 33, Volatile = 34, While = 35, Alignas = 36, Alignof = 37, 
    Atomic = 38, Bool = 39, Complex = 40, Generic = 41, Imaginary = 42, 
    Noreturn = 43, StaticAssert = 44, ThreadLocal = 45, LeftParen = 46, 
    RightParen = 47, LeftBracket = 48, RightBracket = 49, LeftBrace = 50, 
    RightBrace = 51, Less = 52, LessEqual = 53, Greater = 54, GreaterEqual = 55, 
    LeftShift = 56, RightShift = 57, Plus = 58, PlusPlus = 59, Minus = 60, 
    MinusMinus = 61, Star = 62, Div = 63, Mod = 64, And = 65, Or = 66, AndAnd = 67, 
    OrOr = 68, Caret = 69, Not = 70, Tilde = 71, Question = 72, Colon = 73, 
    Semi = 74, Comma = 75, Assign = 76, StarAssign = 77, DivAssign = 78, 
    ModAssign = 79, PlusAssign = 80, MinusAssign = 81, LeftShiftAssign = 82, 
    RightShiftAssign = 83, AndAssign = 84, XorAssign = 85, OrAssign = 86, 
    Equal = 87, NotEqual = 88, Arrow = 89, Dot = 90, Ellipsis = 91, Identifier = 92, 
    IntegerConstant = 93, FloatingConstant = 94, DigitSequence = 95, CharacterConstant = 96, 
    EncodingPrefix = 97, SCharSequence = 98, MultiLineMacro = 99, Directive = 100, 
    AsmBlock = 101, Whitespace = 102, Newline = 103, BlockComment = 104, 
    LineComment = 105
  };

  explicit CLexer(antlr4::CharStream *input);

  ~CLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

