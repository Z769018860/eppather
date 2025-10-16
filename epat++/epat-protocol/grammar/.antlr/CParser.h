
#include "stmt.h"
#include "my_stack.h"
#include "type_helper.h"
using namespace epat;


// Generated from c://Projects//epat++//epat-protocol//grammar//CParser.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"




class  CParser : public antlr4::Parser {
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

  enum {
    RuleCompilationUnit = 0, RuleTranslationUnit = 1, RuleExpression = 2, 
    RuleConstantExpression = 3, RulePrimaryExpression = 4, RuleGenericSelection = 5, 
    RuleGenericAssocList = 6, RuleGenericAssociation = 7, RuleArgumentExpressionList = 8, 
    RuleCommaExpression = 9, RuleDeclaration = 10, RuleDeclarationSpecifiers = 11, 
    RuleInitDeclaratorList = 12, RuleInitDeclarator = 13, RuleStorageClassSpecifier = 14, 
    RuleTypeSpecifier = 15, RuleStructOrUnionSpecifier = 16, RuleStructOrUnion = 17, 
    RuleStructDeclarationList = 18, RuleStructDeclaration = 19, RuleSpecifierQualifierList = 20, 
    RuleStructDeclaratorList = 21, RuleStructDeclarator = 22, RuleEnumSpecifier = 23, 
    RuleEnumeratorList = 24, RuleEnumerator = 25, RuleEnumerationConstant = 26, 
    RuleAtomicTypeSpecifier = 27, RuleTypeQualifier = 28, RuleFunctionSpecifier = 29, 
    RuleAlignmentSpecifier = 30, RuleDeclarator = 31, RuleDirectDeclarator = 32, 
    RulePointer = 33, RuleTypeQualifierList = 34, RuleParameterTypeList = 35, 
    RuleParameterList = 36, RuleParameterDeclaration = 37, RuleIdentifierList = 38, 
    RuleTypeName = 39, RuleAbstractDeclarator = 40, RuleDirectAbstractDeclarator = 41, 
    RuleTypedefName = 42, RuleInitializer = 43, RuleInitializerList = 44, 
    RuleDesignation = 45, RuleDesignatorList = 46, RuleDesignator = 47, 
    RuleStaticAssertDeclaration = 48, RuleStatement = 49, RuleLabeledStatement = 50, 
    RuleCompoundStatement = 51, RuleBlockItemList = 52, RuleBlockItem = 53, 
    RuleExpressionStatement = 54, RuleSelectionStatement = 55, RuleIterationStatement = 56, 
    RuleForCondition = 57, RuleJumpStatement = 58, RuleSignStatement = 59, 
    RuleExternalDeclaration = 60, RuleFunctionDefinition = 61, RuleDeclarationList = 62
  };

  explicit CParser(antlr4::TokenStream *input);

  CParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~CParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  // options and features
  bool k_and_r_ = false;
  int in_func_head_ = 0;
  // member variables
  Root::ptr root_;
  MyStack<Context*> ctx_stack_;
  inline CompoundStmt& root() { return *root_; }
  inline Context& context() { return *ctx_stack_.top(); }
  inline void pushContext(Context& ctx) { ctx_stack_.push(&ctx); }
  inline void popContext() { ctx_stack_.pop(); }
  inline CompoundStmt& block() { return dynamic_cast<CompoundStmt&>(*ctx_stack_.top()); }
  inline void pushBlock(CompoundStmt& blk) { ctx_stack_.push(&blk); }
  inline void popBlock() { ctx_stack_.pop(); }
  MyStack<Expr::list> arg_lists_;
  MyStack<CompoundStmt::ptr> blocks_;
  MyStack<Decl::ptr> decls_;
  MyStack<Expr::ptr> exprs_;
  MyStack<TypeHelper> helpers_;
  MyStack<std::string> ids_;
  MyStack<ParmVarDecl::list> parm_lists_;
  MyStack<Stmt::ptr> stmts_;
  MyStack<StructDecl::ptr> structs_;
  MyStack<QualType> types_;
  void dumpStackInfo();
  // member functions
  void copyHelper();
  // expr and stmt
  void makeArraySubscript();
  void makeBinary(const std::string& op);
  void makeBreak() { stmts_.push(BreakStmt::create()); }
  void makeCall(bool args);
  void makeCast();
  void makeContinue() { stmts_.push(ContinueStmt::create()); }
  void makeExprStmt(bool not_empty = true);
  void makeIfStmt(bool has_else = false);
  void makeInitListExpr();
  // void makeLiteral();
  void makeChr(const std::string& text);
  void makeInt(const std::string& text);
  void makeFlt(const std::string& text);
  void makeStr(const std::string& text);
  void makeMember(const std::string& mbr, const std::string& arrow);
  void makeRef(const std::string& name);
  void makeReturn(bool has_ret = false);
  void makeSignStmt();
  void makeSizeof(bool isExpr = false);
  void makeUnary(const std::string& op, bool postfix = false);
  void makeWhileStmt();
  // predicate
  bool isTypedefName();
  // type helper
  void setArray();
  void setFunction(bool no_parm = false, bool k_and_r = false);
  void setParen();
  void setPointer();
  void setTypedefName(std::string const& name);
  // decl
  StructDecl::ptr getStructDecl(const std::string& name);
  Decl::ptr makeDecl(bool init);
  FieldDecl::ptr makeField();
  FunctionDecl::ptr makeFuncDef();
  ParmVarDecl::ptr makeParm(bool has_id = false);
  // find
  TypeDecl::ptr getTypeDecl(const std::string& name);
  // predicate
  //bool isTypedefName(const std::string& name);
  // enter and exit
  void enterBlock(CompoundStmt& block) { ctx_stack_.push(&block); }
  void exitBlock() { ctx_stack_.pop(); }
  void enterContext(Context& ctx) { ctx_stack_.push(&ctx); }
  void exitContext() { ctx_stack_.pop(); }
  void enterDecl() { helpers_.push(); }
  void exitDecl()  { helpers_.pop(); }
  void enterFuncHead() { ++in_func_head_; }
  void exitFuncHead() { --in_func_head_; }
  // void enterStruct() { helpers_.push(); }
  // void exitStruct()  { helpers_.pop(); }
  // end
  void endParse() { if (!root_) root_ = Root::create(); dumpStackInfo(); }
  // push decl, stmt and so on
  void pushArg();
  void pushStruct(const std::string& name);
  void popStruct();


  class CompilationUnitContext;
  class TranslationUnitContext;
  class ExpressionContext;
  class ConstantExpressionContext;
  class PrimaryExpressionContext;
  class GenericSelectionContext;
  class GenericAssocListContext;
  class GenericAssociationContext;
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
  class SignStatementContext;
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
    std::vector<FunctionDefinitionContext *> functionDefinition();
    FunctionDefinitionContext* functionDefinition(size_t i);
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);
    std::vector<DeclarationContext *> declaration();
    DeclarationContext* declaration(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TranslationUnitContext* translationUnit();

  class  ExpressionContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *op = nullptr;
    CParser::ArgumentExpressionListContext *args = nullptr;
    antlr4::Token *arrow = nullptr;
    antlr4::Token *id = nullptr;
    ExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PrimaryExpressionContext *primaryExpression();
    antlr4::tree::TerminalNode *LeftParen();
    TypeNameContext *typeName();
    antlr4::tree::TerminalNode *RightParen();
    antlr4::tree::TerminalNode *Sizeof();
    antlr4::tree::TerminalNode *Alignof();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *PlusPlus();
    antlr4::tree::TerminalNode *MinusMinus();
    antlr4::tree::TerminalNode *Plus();
    antlr4::tree::TerminalNode *Minus();
    antlr4::tree::TerminalNode *Not();
    antlr4::tree::TerminalNode *Tilde();
    antlr4::tree::TerminalNode *Star();
    antlr4::tree::TerminalNode *And();
    antlr4::tree::TerminalNode *Div();
    antlr4::tree::TerminalNode *Mod();
    antlr4::tree::TerminalNode *LeftShift();
    antlr4::tree::TerminalNode *RightShift();
    antlr4::tree::TerminalNode *Less();
    antlr4::tree::TerminalNode *LessEqual();
    antlr4::tree::TerminalNode *Greater();
    antlr4::tree::TerminalNode *GreaterEqual();
    antlr4::tree::TerminalNode *Equal();
    antlr4::tree::TerminalNode *NotEqual();
    antlr4::tree::TerminalNode *Caret();
    antlr4::tree::TerminalNode *Or();
    antlr4::tree::TerminalNode *AndAnd();
    antlr4::tree::TerminalNode *OrOr();
    antlr4::tree::TerminalNode *Question();
    antlr4::tree::TerminalNode *Colon();
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
    antlr4::tree::TerminalNode *LeftBracket();
    antlr4::tree::TerminalNode *RightBracket();
    antlr4::tree::TerminalNode *Identifier();
    antlr4::tree::TerminalNode *Dot();
    antlr4::tree::TerminalNode *Arrow();
    ArgumentExpressionListContext *argumentExpressionList();


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
    antlr4::Token *identifierToken = nullptr;
    antlr4::Token *integerconstantToken = nullptr;
    antlr4::Token *floatingconstantToken = nullptr;
    antlr4::Token *characterconstantToken = nullptr;
    antlr4::Token *stringliteralToken = nullptr;
    PrimaryExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Identifier();
    antlr4::tree::TerminalNode *IntegerConstant();
    antlr4::tree::TerminalNode *FloatingConstant();
    antlr4::tree::TerminalNode *CharacterConstant();
    antlr4::tree::TerminalNode *StringLiteral();
    antlr4::tree::TerminalNode *LeftParen();
    CommaExpressionContext *commaExpression();
    antlr4::tree::TerminalNode *RightParen();
    GenericSelectionContext *genericSelection();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PrimaryExpressionContext* primaryExpression();

  class  GenericSelectionContext : public antlr4::ParserRuleContext {
  public:
    GenericSelectionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Generic();
    antlr4::tree::TerminalNode *LeftParen();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *Comma();
    GenericAssocListContext *genericAssocList();
    antlr4::tree::TerminalNode *RightParen();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GenericSelectionContext* genericSelection();

  class  GenericAssocListContext : public antlr4::ParserRuleContext {
  public:
    GenericAssocListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<GenericAssociationContext *> genericAssociation();
    GenericAssociationContext* genericAssociation(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GenericAssocListContext* genericAssocList();

  class  GenericAssociationContext : public antlr4::ParserRuleContext {
  public:
    GenericAssociationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Colon();
    ExpressionContext *expression();
    TypeNameContext *typeName();
    antlr4::tree::TerminalNode *Default();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GenericAssociationContext* genericAssociation();

  class  ArgumentExpressionListContext : public antlr4::ParserRuleContext {
  public:
    Expr::list args;
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
    InitDeclaratorListContext *initDeclaratorList();
    antlr4::tree::TerminalNode *Semi();
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
    StructDecl::ptr sd;
    antlr4::Token *id = nullptr;
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
    antlr4::Token *identifierToken = nullptr;
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
    bool has_id;
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
    antlr4::Token *td = nullptr;
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
    Expr::list init_list;
    InitializerListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<InitializerContext *> initializer();
    InitializerContext* initializer(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);
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
    antlr4::tree::TerminalNode *StringLiteral();
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
    SignStatementContext *signStatement();


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
    CompoundStmt::ptr block;
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
    antlr4::Token *else_ = nullptr;
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

  class  SignStatementContext : public antlr4::ParserRuleContext {
  public:
    SignStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *At();
    CommaExpressionContext *commaExpression();
    antlr4::tree::TerminalNode *Semi();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SignStatementContext* signStatement();

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
    FunctionDecl::ptr func;
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
  bool typedefNameSempred(TypedefNameContext *_localctx, size_t predicateIndex);

  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

