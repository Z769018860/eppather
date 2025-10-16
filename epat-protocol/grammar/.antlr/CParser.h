
// Generated from c://Projects//epat++//epat-protocol//grammar//C.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"




class  CParser : public antlr4::Parser {
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

  enum {
    RuleCompilationUnit = 0, RuleTranslationUnit = 1, RuleExpression = 2, 
    RuleConstantExpression = 3, RulePrimaryExpression = 4, RuleConstant = 5, 
    RuleStringLiteral = 6, RuleArgumentExpressionList = 7, RuleCommaExpression = 8, 
    RuleDeclaration = 9, RuleDeclarationSpecifiers = 10, RuleInitDeclaratorList = 11, 
    RuleInitDeclarator = 12, RuleStorageClassSpecifier = 13, RuleTypeSpecifier = 14, 
    RuleStructOrUnionSpecifier = 15, RuleStructOrUnion = 16, RuleStructDeclarationList = 17, 
    RuleStructDeclaration = 18, RuleSpecifierQualifierList = 19, RuleStructDeclaratorList = 20, 
    RuleStructDeclarator = 21, RuleEnumSpecifier = 22, RuleEnumeratorList = 23, 
    RuleEnumerator = 24, RuleEnumerationConstant = 25, RuleAtomicTypeSpecifier = 26, 
    RuleTypeQualifier = 27, RuleFunctionSpecifier = 28, RuleAlignmentSpecifier = 29, 
    RuleDeclarator = 30, RuleDirectDeclarator = 31, RulePointer = 32, RuleTypeQualifierList = 33, 
    RuleParameterTypeList = 34, RuleParameterList = 35, RuleParameterDeclaration = 36, 
    RuleIdentifierList = 37, RuleTypeName = 38, RuleAbstractDeclarator = 39, 
    RuleDirectAbstractDeclarator = 40, RuleTypedefName = 41, RuleInitializer = 42, 
    RuleInitializerList = 43, RuleDesignation = 44, RuleDesignatorList = 45, 
    RuleDesignator = 46, RuleStaticAssertDeclaration = 47, RuleStatement = 48, 
    RuleLabeledStatement = 49, RuleCompoundStatement = 50, RuleBlockItemList = 51, 
    RuleBlockItem = 52, RuleExpressionStatement = 53, RuleSelectionStatement = 54, 
    RuleIterationStatement = 55, RuleForCondition = 56, RuleJumpStatement = 57, 
    RuleExternalDeclaration = 58, RuleFunctionDefinition = 59, RuleDeclarationList = 60
  };

  explicit CParser(antlr4::TokenStream *input);

  CParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~CParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class CompilationUnitContext;
  class TranslationUnitContext;
  class ExpressionContext;
  class ConstantExpressionContext;
  class PrimaryExpressionContext;
  class ConstantContext;
  class StringLiteralContext;
  class ArgumentExpressionListContext;
  class CommaExpressionContext;
  class DeclarationContext;
  class DeclarationSpecifiersContext;
  class InitDeclaratorListContext;
  class InitDeclaratorContext;
  class StorageClassSpecifierContext;
  class TypeSpecifierContext;
  class StructOrUnionSpecifierContext;
  class StructOrUnionContext;
  class StructDeclarationListContext;
  class StructDeclarationContext;
  class SpecifierQualifierListContext;
  class StructDeclaratorListContext;
  class StructDeclaratorContext;
  class EnumSpecifierContext;
  class EnumeratorListContext;
  class EnumeratorContext;
  class EnumerationConstantContext;
  class AtomicTypeSpecifierContext;
  class TypeQualifierContext;
  class FunctionSpecifierContext;
  class AlignmentSpecifierContext;
  class DeclaratorContext;
  class DirectDeclaratorContext;
  class PointerContext;
  class TypeQualifierListContext;
  class ParameterTypeListContext;
  class ParameterListContext;
  class ParameterDeclarationContext;
  class IdentifierListContext;
  class TypeNameContext;
  class AbstractDeclaratorContext;
  class DirectAbstractDeclaratorContext;
  class TypedefNameContext;
  class InitializerContext;
  class InitializerListContext;
  class DesignationContext;
  class DesignatorListContext;
  class DesignatorContext;
  class StaticAssertDeclarationContext;
  class StatementContext;
  class LabeledStatementContext;
  class CompoundStatementContext;
  class BlockItemListContext;
  class BlockItemContext;
  class ExpressionStatementContext;
  class SelectionStatementContext;
  class IterationStatementContext;
  class ForConditionContext;
  class JumpStatementContext;
  class ExternalDeclarationContext;
  class FunctionDefinitionContext;
  class DeclarationListContext; 

  class  CompilationUnitContext : public antlr4::ParserRuleContext {
  public:
    CompilationUnitContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    TranslationUnitContext *translationUnit();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CompilationUnitContext* compilationUnit();

  class  TranslationUnitContext : public antlr4::ParserRuleContext {
  public:
    TranslationUnitContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<DeclarationContext *> declaration();
    DeclarationContext* declaration(size_t i);
    std::vector<FunctionDefinitionContext *> functionDefinition();
    FunctionDefinitionContext* functionDefinition(size_t i);
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TranslationUnitContext* translationUnit();

  class  ExpressionContext : public antlr4::ParserRuleContext {
  public:
    ExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    ExpressionContext() = default;
    void copyFrom(ExpressionContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  ShiftExpressionContext : public ExpressionContext {
  public:
    ShiftExpressionContext(ExpressionContext *ctx);

    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *LeftShift();
    antlr4::tree::TerminalNode *RightShift();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  AdditiveExpressionContext : public ExpressionContext {
  public:
    AdditiveExpressionContext(ExpressionContext *ctx);

    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *Plus();
    antlr4::tree::TerminalNode *Minus();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  RelationalExpressionContext : public ExpressionContext {
  public:
    RelationalExpressionContext(ExpressionContext *ctx);

    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *Less();
    antlr4::tree::TerminalNode *LessEqual();
    antlr4::tree::TerminalNode *Greater();
    antlr4::tree::TerminalNode *GreaterEqual();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  InclusiveOrExpressionContext : public ExpressionContext {
  public:
    InclusiveOrExpressionContext(ExpressionContext *ctx);

    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *Or();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ConditionalExpressionContext : public ExpressionContext {
  public:
    ConditionalExpressionContext(ExpressionContext *ctx);

    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *Question();
    antlr4::tree::TerminalNode *Colon();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  AssignmentExpressionContext : public ExpressionContext {
  public:
    AssignmentExpressionContext(ExpressionContext *ctx);

    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *Assign();
    antlr4::tree::TerminalNode *PlusAssign();
    antlr4::tree::TerminalNode *MinusAssign();
    antlr4::tree::TerminalNode *StarAssign();
    antlr4::tree::TerminalNode *DivAssign();
    antlr4::tree::TerminalNode *ModAssign();
    antlr4::tree::TerminalNode *LeftShiftAssign();
    antlr4::tree::TerminalNode *RightShiftAssign();
    antlr4::tree::TerminalNode *AndAssign();
    antlr4::tree::TerminalNode *XorAssign();
    antlr4::tree::TerminalNode *OrAssign();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  MultiplicativeExpressionContext : public ExpressionContext {
  public:
    MultiplicativeExpressionContext(ExpressionContext *ctx);

    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *Star();
    antlr4::tree::TerminalNode *Div();
    antlr4::tree::TerminalNode *Mod();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LogicalOrExpressionContext : public ExpressionContext {
  public:
    LogicalOrExpressionContext(ExpressionContext *ctx);

    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *OrOr();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  AndExpressionContext : public ExpressionContext {
  public:
    AndExpressionContext(ExpressionContext *ctx);

    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *And();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExclusiveOrExpressionContext : public ExpressionContext {
  public:
    ExclusiveOrExpressionContext(ExpressionContext *ctx);

    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *Caret();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  EqualityExpressionContext : public ExpressionContext {
  public:
    EqualityExpressionContext(ExpressionContext *ctx);

    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *Equal();
    antlr4::tree::TerminalNode *NotEqual();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LogicalAndExpressionContext : public ExpressionContext {
  public:
    LogicalAndExpressionContext(ExpressionContext *ctx);

    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *AndAnd();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  UnaryExpressionContext : public ExpressionContext {
  public:
    UnaryExpressionContext(ExpressionContext *ctx);

    ExpressionContext *expression();
    antlr4::tree::TerminalNode *LeftParen();
    TypeNameContext *typeName();
    antlr4::tree::TerminalNode *RightParen();
    antlr4::tree::TerminalNode *Sizeof();
    antlr4::tree::TerminalNode *Alignof();
    antlr4::tree::TerminalNode *PlusPlus();
    antlr4::tree::TerminalNode *MinusMinus();
    antlr4::tree::TerminalNode *Plus();
    antlr4::tree::TerminalNode *Minus();
    antlr4::tree::TerminalNode *Not();
    antlr4::tree::TerminalNode *Tilde();
    antlr4::tree::TerminalNode *Star();
    antlr4::tree::TerminalNode *And();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PostfixExpressionContext : public ExpressionContext {
  public:
    PostfixExpressionContext(ExpressionContext *ctx);

    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *LeftBracket();
    antlr4::tree::TerminalNode *RightBracket();
    antlr4::tree::TerminalNode *LeftParen();
    antlr4::tree::TerminalNode *RightParen();
    antlr4::tree::TerminalNode *Identifier();
    antlr4::tree::TerminalNode *PlusPlus();
    antlr4::tree::TerminalNode *MinusMinus();
    antlr4::tree::TerminalNode *Dot();
    antlr4::tree::TerminalNode *Arrow();
    ArgumentExpressionListContext *argumentExpressionList();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PrimaryContext : public ExpressionContext {
  public:
    PrimaryContext(ExpressionContext *ctx);

    PrimaryExpressionContext *primaryExpression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  ExpressionContext* expression();
  ExpressionContext* expression(int precedence);
  class  ConstantExpressionContext : public antlr4::ParserRuleContext {
  public:
    ConstantExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConstantExpressionContext* constantExpression();

  class  PrimaryExpressionContext : public antlr4::ParserRuleContext {
  public:
    PrimaryExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Identifier();
    ConstantContext *constant();
    StringLiteralContext *stringLiteral();
    antlr4::tree::TerminalNode *LeftParen();
    CommaExpressionContext *commaExpression();
    antlr4::tree::TerminalNode *RightParen();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PrimaryExpressionContext* primaryExpression();

  class  ConstantContext : public antlr4::ParserRuleContext {
  public:
    ConstantContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IntegerConstant();
    antlr4::tree::TerminalNode *FloatingConstant();
    antlr4::tree::TerminalNode *CharacterConstant();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConstantContext* constant();

  class  StringLiteralContext : public antlr4::ParserRuleContext {
  public:
    StringLiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EncodingPrefix();
    antlr4::tree::TerminalNode *SCharSequence();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StringLiteralContext* stringLiteral();

  class  ArgumentExpressionListContext : public antlr4::ParserRuleContext {
  public:
    ArgumentExpressionListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArgumentExpressionListContext* argumentExpressionList();

  class  CommaExpressionContext : public antlr4::ParserRuleContext {
  public:
    CommaExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();
    CommaExpressionContext *commaExpression();
    antlr4::tree::TerminalNode *Comma();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CommaExpressionContext* commaExpression();
  CommaExpressionContext* commaExpression(int precedence);
  class  DeclarationContext : public antlr4::ParserRuleContext {
  public:
    DeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    DeclarationSpecifiersContext *declarationSpecifiers();
    antlr4::tree::TerminalNode *Semi();
    InitDeclaratorListContext *initDeclaratorList();
    StaticAssertDeclarationContext *staticAssertDeclaration();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DeclarationContext* declaration();

  class  DeclarationSpecifiersContext : public antlr4::ParserRuleContext {
  public:
    DeclarationSpecifiersContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<StorageClassSpecifierContext *> storageClassSpecifier();
    StorageClassSpecifierContext* storageClassSpecifier(size_t i);
    std::vector<TypeSpecifierContext *> typeSpecifier();
    TypeSpecifierContext* typeSpecifier(size_t i);
    std::vector<TypeQualifierContext *> typeQualifier();
    TypeQualifierContext* typeQualifier(size_t i);
    std::vector<FunctionSpecifierContext *> functionSpecifier();
    FunctionSpecifierContext* functionSpecifier(size_t i);
    std::vector<AlignmentSpecifierContext *> alignmentSpecifier();
    AlignmentSpecifierContext* alignmentSpecifier(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DeclarationSpecifiersContext* declarationSpecifiers();

  class  InitDeclaratorListContext : public antlr4::ParserRuleContext {
  public:
    InitDeclaratorListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<InitDeclaratorContext *> initDeclarator();
    InitDeclaratorContext* initDeclarator(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  InitDeclaratorListContext* initDeclaratorList();

  class  InitDeclaratorContext : public antlr4::ParserRuleContext {
  public:
    InitDeclaratorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    DeclaratorContext *declarator();
    antlr4::tree::TerminalNode *Assign();
    InitializerContext *initializer();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  InitDeclaratorContext* initDeclarator();

  class  StorageClassSpecifierContext : public antlr4::ParserRuleContext {
  public:
    StorageClassSpecifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Typedef();
    antlr4::tree::TerminalNode *Extern();
    antlr4::tree::TerminalNode *Static();
    antlr4::tree::TerminalNode *ThreadLocal();
    antlr4::tree::TerminalNode *Auto();
    antlr4::tree::TerminalNode *Register();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StorageClassSpecifierContext* storageClassSpecifier();

  class  TypeSpecifierContext : public antlr4::ParserRuleContext {
  public:
    TypeSpecifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Void();
    antlr4::tree::TerminalNode *Char();
    antlr4::tree::TerminalNode *Short();
    antlr4::tree::TerminalNode *Int();
    antlr4::tree::TerminalNode *Long();
    antlr4::tree::TerminalNode *Float();
    antlr4::tree::TerminalNode *Double();
    antlr4::tree::TerminalNode *Signed();
    antlr4::tree::TerminalNode *Unsigned();
    antlr4::tree::TerminalNode *Bool();
    antlr4::tree::TerminalNode *Complex();
    AtomicTypeSpecifierContext *atomicTypeSpecifier();
    StructOrUnionSpecifierContext *structOrUnionSpecifier();
    EnumSpecifierContext *enumSpecifier();
    TypedefNameContext *typedefName();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeSpecifierContext* typeSpecifier();

  class  StructOrUnionSpecifierContext : public antlr4::ParserRuleContext {
  public:
    StructOrUnionSpecifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StructOrUnionContext *structOrUnion();
    antlr4::tree::TerminalNode *LeftBrace();
    StructDeclarationListContext *structDeclarationList();
    antlr4::tree::TerminalNode *RightBrace();
    antlr4::tree::TerminalNode *Identifier();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StructOrUnionSpecifierContext* structOrUnionSpecifier();

  class  StructOrUnionContext : public antlr4::ParserRuleContext {
  public:
    StructOrUnionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Struct();
    antlr4::tree::TerminalNode *Union();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StructOrUnionContext* structOrUnion();

  class  StructDeclarationListContext : public antlr4::ParserRuleContext {
  public:
    StructDeclarationListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<StructDeclarationContext *> structDeclaration();
    StructDeclarationContext* structDeclaration(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StructDeclarationListContext* structDeclarationList();

  class  StructDeclarationContext : public antlr4::ParserRuleContext {
  public:
    StructDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    SpecifierQualifierListContext *specifierQualifierList();
    StructDeclaratorListContext *structDeclaratorList();
    antlr4::tree::TerminalNode *Semi();
    StaticAssertDeclarationContext *staticAssertDeclaration();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StructDeclarationContext* structDeclaration();

  class  SpecifierQualifierListContext : public antlr4::ParserRuleContext {
  public:
    SpecifierQualifierListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<TypeSpecifierContext *> typeSpecifier();
    TypeSpecifierContext* typeSpecifier(size_t i);
    std::vector<TypeQualifierContext *> typeQualifier();
    TypeQualifierContext* typeQualifier(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SpecifierQualifierListContext* specifierQualifierList();

  class  StructDeclaratorListContext : public antlr4::ParserRuleContext {
  public:
    StructDeclaratorListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<StructDeclaratorContext *> structDeclarator();
    StructDeclaratorContext* structDeclarator(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StructDeclaratorListContext* structDeclaratorList();

  class  StructDeclaratorContext : public antlr4::ParserRuleContext {
  public:
    StructDeclaratorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    DeclaratorContext *declarator();
    antlr4::tree::TerminalNode *Colon();
    ConstantExpressionContext *constantExpression();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StructDeclaratorContext* structDeclarator();

  class  EnumSpecifierContext : public antlr4::ParserRuleContext {
  public:
    EnumSpecifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Enum();
    antlr4::tree::TerminalNode *LeftBrace();
    EnumeratorListContext *enumeratorList();
    antlr4::tree::TerminalNode *RightBrace();
    antlr4::tree::TerminalNode *Identifier();
    antlr4::tree::TerminalNode *Comma();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  EnumSpecifierContext* enumSpecifier();

  class  EnumeratorListContext : public antlr4::ParserRuleContext {
  public:
    EnumeratorListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<EnumeratorContext *> enumerator();
    EnumeratorContext* enumerator(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  EnumeratorListContext* enumeratorList();

  class  EnumeratorContext : public antlr4::ParserRuleContext {
  public:
    EnumeratorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    EnumerationConstantContext *enumerationConstant();
    antlr4::tree::TerminalNode *Assign();
    ConstantExpressionContext *constantExpression();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  EnumeratorContext* enumerator();

  class  EnumerationConstantContext : public antlr4::ParserRuleContext {
  public:
    EnumerationConstantContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Identifier();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  EnumerationConstantContext* enumerationConstant();

  class  AtomicTypeSpecifierContext : public antlr4::ParserRuleContext {
  public:
    AtomicTypeSpecifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Atomic();
    antlr4::tree::TerminalNode *LeftParen();
    TypeNameContext *typeName();
    antlr4::tree::TerminalNode *RightParen();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AtomicTypeSpecifierContext* atomicTypeSpecifier();

  class  TypeQualifierContext : public antlr4::ParserRuleContext {
  public:
    TypeQualifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Const();
    antlr4::tree::TerminalNode *Restrict();
    antlr4::tree::TerminalNode *Volatile();
    antlr4::tree::TerminalNode *Atomic();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeQualifierContext* typeQualifier();

  class  FunctionSpecifierContext : public antlr4::ParserRuleContext {
  public:
    FunctionSpecifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Inline();
    antlr4::tree::TerminalNode *Noreturn();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FunctionSpecifierContext* functionSpecifier();

  class  AlignmentSpecifierContext : public antlr4::ParserRuleContext {
  public:
    AlignmentSpecifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Alignas();
    antlr4::tree::TerminalNode *LeftParen();
    antlr4::tree::TerminalNode *RightParen();
    TypeNameContext *typeName();
    ConstantExpressionContext *constantExpression();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AlignmentSpecifierContext* alignmentSpecifier();

  class  DeclaratorContext : public antlr4::ParserRuleContext {
  public:
    DeclaratorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    DirectDeclaratorContext *directDeclarator();
    PointerContext *pointer();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DeclaratorContext* declarator();

  class  DirectDeclaratorContext : public antlr4::ParserRuleContext {
  public:
    DirectDeclaratorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Identifier();
    antlr4::tree::TerminalNode *LeftParen();
    DeclaratorContext *declarator();
    antlr4::tree::TerminalNode *RightParen();
    antlr4::tree::TerminalNode *Colon();
    antlr4::tree::TerminalNode *DigitSequence();
    DirectDeclaratorContext *directDeclarator();
    antlr4::tree::TerminalNode *LeftBracket();
    antlr4::tree::TerminalNode *RightBracket();
    TypeQualifierListContext *typeQualifierList();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *Static();
    antlr4::tree::TerminalNode *Star();
    ParameterTypeListContext *parameterTypeList();
    IdentifierListContext *identifierList();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DirectDeclaratorContext* directDeclarator();
  DirectDeclaratorContext* directDeclarator(int precedence);
  class  PointerContext : public antlr4::ParserRuleContext {
  public:
    PointerContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Star();
    TypeQualifierListContext *typeQualifierList();
    PointerContext *pointer();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PointerContext* pointer();

  class  TypeQualifierListContext : public antlr4::ParserRuleContext {
  public:
    TypeQualifierListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<TypeQualifierContext *> typeQualifier();
    TypeQualifierContext* typeQualifier(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeQualifierListContext* typeQualifierList();

  class  ParameterTypeListContext : public antlr4::ParserRuleContext {
  public:
    ParameterTypeListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ParameterListContext *parameterList();
    antlr4::tree::TerminalNode *Comma();
    antlr4::tree::TerminalNode *Ellipsis();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ParameterTypeListContext* parameterTypeList();

  class  ParameterListContext : public antlr4::ParserRuleContext {
  public:
    ParameterListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ParameterDeclarationContext *> parameterDeclaration();
    ParameterDeclarationContext* parameterDeclaration(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ParameterListContext* parameterList();

  class  ParameterDeclarationContext : public antlr4::ParserRuleContext {
  public:
    ParameterDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    DeclarationSpecifiersContext *declarationSpecifiers();
    DeclaratorContext *declarator();
    AbstractDeclaratorContext *abstractDeclarator();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ParameterDeclarationContext* parameterDeclaration();

  class  IdentifierListContext : public antlr4::ParserRuleContext {
  public:
    IdentifierListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> Identifier();
    antlr4::tree::TerminalNode* Identifier(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IdentifierListContext* identifierList();

  class  TypeNameContext : public antlr4::ParserRuleContext {
  public:
    TypeNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    SpecifierQualifierListContext *specifierQualifierList();
    AbstractDeclaratorContext *abstractDeclarator();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeNameContext* typeName();

  class  AbstractDeclaratorContext : public antlr4::ParserRuleContext {
  public:
    AbstractDeclaratorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PointerContext *pointer();
    DirectAbstractDeclaratorContext *directAbstractDeclarator();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AbstractDeclaratorContext* abstractDeclarator();

  class  DirectAbstractDeclaratorContext : public antlr4::ParserRuleContext {
  public:
    DirectAbstractDeclaratorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LeftParen();
    AbstractDeclaratorContext *abstractDeclarator();
    antlr4::tree::TerminalNode *RightParen();
    antlr4::tree::TerminalNode *LeftBracket();
    antlr4::tree::TerminalNode *RightBracket();
    TypeQualifierListContext *typeQualifierList();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *Static();
    antlr4::tree::TerminalNode *Star();
    ParameterTypeListContext *parameterTypeList();
    DirectAbstractDeclaratorContext *directAbstractDeclarator();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DirectAbstractDeclaratorContext* directAbstractDeclarator();
  DirectAbstractDeclaratorContext* directAbstractDeclarator(int precedence);
  class  TypedefNameContext : public antlr4::ParserRuleContext {
  public:
    TypedefNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Identifier();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypedefNameContext* typedefName();

  class  InitializerContext : public antlr4::ParserRuleContext {
  public:
    InitializerContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *LeftBrace();
    InitializerListContext *initializerList();
    antlr4::tree::TerminalNode *RightBrace();
    antlr4::tree::TerminalNode *Comma();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  InitializerContext* initializer();

  class  InitializerListContext : public antlr4::ParserRuleContext {
  public:
    InitializerListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<InitializerContext *> initializer();
    InitializerContext* initializer(size_t i);
    std::vector<DesignationContext *> designation();
    DesignationContext* designation(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  InitializerListContext* initializerList();

  class  DesignationContext : public antlr4::ParserRuleContext {
  public:
    DesignationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    DesignatorListContext *designatorList();
    antlr4::tree::TerminalNode *Assign();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DesignationContext* designation();

  class  DesignatorListContext : public antlr4::ParserRuleContext {
  public:
    DesignatorListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<DesignatorContext *> designator();
    DesignatorContext* designator(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DesignatorListContext* designatorList();

  class  DesignatorContext : public antlr4::ParserRuleContext {
  public:
    DesignatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LeftBracket();
    ConstantExpressionContext *constantExpression();
    antlr4::tree::TerminalNode *RightBracket();
    antlr4::tree::TerminalNode *Dot();
    antlr4::tree::TerminalNode *Identifier();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DesignatorContext* designator();

  class  StaticAssertDeclarationContext : public antlr4::ParserRuleContext {
  public:
    StaticAssertDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *StaticAssert();
    antlr4::tree::TerminalNode *LeftParen();
    ConstantExpressionContext *constantExpression();
    antlr4::tree::TerminalNode *Comma();
    StringLiteralContext *stringLiteral();
    antlr4::tree::TerminalNode *RightParen();
    antlr4::tree::TerminalNode *Semi();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StaticAssertDeclarationContext* staticAssertDeclaration();

  class  StatementContext : public antlr4::ParserRuleContext {
  public:
    StatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    LabeledStatementContext *labeledStatement();
    CompoundStatementContext *compoundStatement();
    ExpressionStatementContext *expressionStatement();
    SelectionStatementContext *selectionStatement();
    IterationStatementContext *iterationStatement();
    JumpStatementContext *jumpStatement();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatementContext* statement();

  class  LabeledStatementContext : public antlr4::ParserRuleContext {
  public:
    LabeledStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Identifier();
    antlr4::tree::TerminalNode *Colon();
    StatementContext *statement();
    antlr4::tree::TerminalNode *Case();
    ConstantExpressionContext *constantExpression();
    antlr4::tree::TerminalNode *Default();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LabeledStatementContext* labeledStatement();

  class  CompoundStatementContext : public antlr4::ParserRuleContext {
  public:
    CompoundStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LeftBrace();
    antlr4::tree::TerminalNode *RightBrace();
    BlockItemListContext *blockItemList();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CompoundStatementContext* compoundStatement();

  class  BlockItemListContext : public antlr4::ParserRuleContext {
  public:
    BlockItemListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<BlockItemContext *> blockItem();
    BlockItemContext* blockItem(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BlockItemListContext* blockItemList();

  class  BlockItemContext : public antlr4::ParserRuleContext {
  public:
    BlockItemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StatementContext *statement();
    DeclarationContext *declaration();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BlockItemContext* blockItem();

  class  ExpressionStatementContext : public antlr4::ParserRuleContext {
  public:
    ExpressionStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Semi();
    CommaExpressionContext *commaExpression();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExpressionStatementContext* expressionStatement();

  class  SelectionStatementContext : public antlr4::ParserRuleContext {
  public:
    SelectionStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *If();
    antlr4::tree::TerminalNode *LeftParen();
    CommaExpressionContext *commaExpression();
    antlr4::tree::TerminalNode *RightParen();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);
    antlr4::tree::TerminalNode *Else();
    antlr4::tree::TerminalNode *Switch();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SelectionStatementContext* selectionStatement();

  class  IterationStatementContext : public antlr4::ParserRuleContext {
  public:
    IterationStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *While();
    antlr4::tree::TerminalNode *LeftParen();
    CommaExpressionContext *commaExpression();
    antlr4::tree::TerminalNode *RightParen();
    StatementContext *statement();
    antlr4::tree::TerminalNode *Do();
    antlr4::tree::TerminalNode *Semi();
    antlr4::tree::TerminalNode *For();
    ForConditionContext *forCondition();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IterationStatementContext* iterationStatement();

  class  ForConditionContext : public antlr4::ParserRuleContext {
  public:
    ForConditionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> Semi();
    antlr4::tree::TerminalNode* Semi(size_t i);
    DeclarationContext *declaration();
    std::vector<CommaExpressionContext *> commaExpression();
    CommaExpressionContext* commaExpression(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ForConditionContext* forCondition();

  class  JumpStatementContext : public antlr4::ParserRuleContext {
  public:
    JumpStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Semi();
    antlr4::tree::TerminalNode *Goto();
    antlr4::tree::TerminalNode *Identifier();
    antlr4::tree::TerminalNode *Continue();
    antlr4::tree::TerminalNode *Break();
    antlr4::tree::TerminalNode *Return();
    CommaExpressionContext *commaExpression();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  JumpStatementContext* jumpStatement();

  class  ExternalDeclarationContext : public antlr4::ParserRuleContext {
  public:
    ExternalDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FunctionDefinitionContext *functionDefinition();
    DeclarationContext *declaration();
    antlr4::tree::TerminalNode *Semi();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExternalDeclarationContext* externalDeclaration();

  class  FunctionDefinitionContext : public antlr4::ParserRuleContext {
  public:
    FunctionDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    DeclarationSpecifiersContext *declarationSpecifiers();
    DeclaratorContext *declarator();
    CompoundStatementContext *compoundStatement();
    DeclarationListContext *declarationList();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FunctionDefinitionContext* functionDefinition();

  class  DeclarationListContext : public antlr4::ParserRuleContext {
  public:
    DeclarationListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<DeclarationContext *> declaration();
    DeclarationContext* declaration(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DeclarationListContext* declarationList();


  bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;

  bool expressionSempred(ExpressionContext *_localctx, size_t predicateIndex);
  bool commaExpressionSempred(CommaExpressionContext *_localctx, size_t predicateIndex);
  bool directDeclaratorSempred(DirectDeclaratorContext *_localctx, size_t predicateIndex);
  bool directAbstractDeclaratorSempred(DirectAbstractDeclaratorContext *_localctx, size_t predicateIndex);

  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

