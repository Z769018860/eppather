
// Generated from c://Projects//epat++//epat-protocol//grammar//CLexer.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"




class  CLexer : public antlr4::Lexer {
public:
  enum {
    Auto = 1, Break = 2, Case = 3, Char = 4, Const = 5, Continue = 6, Default = 7, 
    Do = 8, Double = 9, Else = 10, Enum = 11, Extern = 12, Float = 13, For = 14, 
    Goto = 15, If = 16, Inline = 17, Int = 18, Long = 19, Register = 20, 
    Restrict = 21, Return = 22, Short = 23, Signed = 24, Sizeof = 25, Static = 26, 
    Struct = 27, Switch = 28, Typedef = 29, Union = 30, Unsigned = 31, Void = 32, 
    Volatile = 33, While = 34, Alignas = 35, Alignof = 36, Atomic = 37, 
    Bool = 38, Complex = 39, Generic = 40, Imaginary = 41, Noreturn = 42, 
    StaticAssert = 43, ThreadLocal = 44, LeftParen = 45, RightParen = 46, 
    LeftBracket = 47, RightBracket = 48, LeftBrace = 49, RightBrace = 50, 
    Less = 51, LessEqual = 52, Greater = 53, GreaterEqual = 54, LeftShift = 55, 
    RightShift = 56, Plus = 57, PlusPlus = 58, Minus = 59, MinusMinus = 60, 
    Star = 61, Div = 62, Mod = 63, And = 64, Or = 65, AndAnd = 66, OrOr = 67, 
    Caret = 68, Not = 69, Tilde = 70, Question = 71, Colon = 72, Semi = 73, 
    Comma = 74, Assign = 75, StarAssign = 76, DivAssign = 77, ModAssign = 78, 
    PlusAssign = 79, MinusAssign = 80, LeftShiftAssign = 81, RightShiftAssign = 82, 
    AndAssign = 83, XorAssign = 84, OrAssign = 85, Equal = 86, NotEqual = 87, 
    Arrow = 88, Dot = 89, At = 90, Ellipsis = 91, Identifier = 92, IntegerConstant = 93, 
    FloatingConstant = 94, CharacterConstant = 95, StringLiteral = 96, DigitSequence = 97, 
    MultiLineMacro = 98, Directive = 99, AsmBlock = 100, Whitespace = 101, 
    Newline = 102, BlockComment = 103, LineComment = 104
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

