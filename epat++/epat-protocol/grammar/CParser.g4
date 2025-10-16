parser grammar CParser;

options {
    tokenVocab = CLexer;
}

@parser::header {
#include "stmt.h"
#include "my_stack.h"
#include "type_helper.h"
using namespace epat;
}

@parser::members {
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
}

compilationUnit
    :   translationUnit? EOF {endParse();}
    ;

translationUnit
    :   {root_ = Root::create(); enterBlock(root());}
    (   functionDefinition                         
    |   statement          {block() << stmts_.pop();}
    |   declaration   
    )+  {exitBlock();}
    ;

// expressions
expression
    :   primaryExpression
    |   expression
        (   '[' expression ']'      {makeArraySubscript();}
        |   '(' args=argumentExpressionList? ')'
                                    {makeCall($ctx->args);}
        |   arrow=('.' | '->') id=Identifier 
                                    {makeMember($id.text, $arrow.text);}
        |   '++'                    {makeUnary("++", true);}
        |   '--'                    {makeUnary("--", true);}
        )
    // |   (type){list} 复合字面量(C99)
    |   ('sizeof' | '_Alignof') '(' typeName ')'     {makeSizeof();}
    |   '(' typeName ')' expression                  {makeCast();}
    |   op=('++' | '--'
        |   '+' | '-'
        |   '!' | '~'
        |   '*'
        |   '&'
        |   'sizeof'
        ) expression                                 {makeUnary($op.text);}
    |   expression op=('*'|'/'|'%') expression       {makeBinary($op.text);}
    |   expression op=('+'|'-') expression           {makeBinary($op.text);}
    |   expression op=('<<'|'>>') expression         {makeBinary($op.text);}
    |   expression op=('<'|'<='|'>'|'>=') expression {makeBinary($op.text);}
    |   expression op=('=='|'!=') expression         {makeBinary($op.text);}
    |   expression '&' expression                    {makeBinary("&");}
    |   expression '^' expression                    {makeBinary("^");}
    |   expression '|' expression                    {makeBinary("|");}
    |   expression '&&' expression                   {makeBinary("&&");}
    |   expression '||' expression                   {makeBinary("||");}
    |   expression '?' expression ':' expression     // TODO: 三目运算符
    |   <assoc=right> expression // TODO: left operand can only be unary operator
        op=('='
        |   '+='
        |   '-='
        |   '*='
        |   '/='
        |   '%='
        |   '<<='
        |   '>>='
        |   '&='
        |   '^='
        |   '|='
        )
        expression                                   {makeBinary($op.text);}
    ;

constantExpression
    :   expression
    ;

primaryExpression
    :   Identifier        {makeRef($Identifier.text);}
    // |   enumerationConstant
    |   IntegerConstant   {makeInt($IntegerConstant.text);}
    |   FloatingConstant  {makeFlt($FloatingConstant.text);}
    |   CharacterConstant {makeChr($CharacterConstant.text);}
    |   StringLiteral     {makeStr($StringLiteral.text);}
    |   '(' commaExpression ')'
    |   genericSelection // TODO: to implement
                          {makeStr("genericSelection");}
    ;

genericSelection // TODO: to implement
    :   '_Generic' '(' expression ',' genericAssocList ')'
    ;

genericAssocList
    :   genericAssociation (',' genericAssociation)*
    ;

genericAssociation
    :   (typeName | 'default') ':' expression
    ;

argumentExpressionList 
    locals [Expr::list args]
    :   expression      {$args.push_back(exprs_.pop());} 
        (',' expression {$args.push_back(exprs_.pop());})*
        {arg_lists_.push(std::move($args));}
    ;

commaExpression
    :   expression
    |   commaExpression ',' expression {makeBinary(",");}
    ;

// Declarations
declaration // XXX: 避免在开头使用动作，暂用方案把stmt放在decl之上
    :   {enterDecl();} declarationSpecifiers initDeclaratorList ';' {exitDecl();}
    |   {enterDecl();} declarationSpecifiers ';' {exitDecl();}
    |   staticAssertDeclaration // TODO: to implement
    ;

declarationSpecifiers
    :   (   storageClassSpecifier
        |   typeSpecifier
        |   typeQualifier
        |   functionSpecifier
        |   alignmentSpecifier
        )+
    ;

initDeclaratorList
    :   initDeclarator (',' initDeclarator)* // push decl in the next rule
    ;

initDeclarator
    :   {copyHelper();} declarator ('=' initializer)?
        {context() << makeDecl($ctx->initializer());}
    ;

storageClassSpecifier
    :   'typedef'       {helpers_.top().setTypedef();}
    |   'extern'        {helpers_.top().setExtern();}
    |   'static'        {helpers_.top().setStatic();}
    |   '_Thread_local' {helpers_.top().setThreadLocal();}
    |   'auto'          {helpers_.top().setAuto();}
    |   'register'      {helpers_.top().setRegister();}
    ;

typeSpecifier
    :   'void'      {helpers_.top().setVoid();}
    |   'char'      {helpers_.top().setChar();}
    |   'short'     {helpers_.top().setShort();}
    |   'int'       {helpers_.top().setInt();}
    |   'long'      {helpers_.top().setLong();}
    |   'float'     {helpers_.top().setFloat();}
    |   'double'    {helpers_.top().setDouble();}
    |   'signed'    {helpers_.top().setSigned();}
    |   'unsigned'  {helpers_.top().setUnsigned();}
    |   '_Bool'     {helpers_.top().setBool();}
    |   '_Complex'  {helpers_.top().setComplex();}
    |   atomicTypeSpecifier    
    |   structOrUnionSpecifier
    |   enumSpecifier       
    |   typedefName
    ;

structOrUnionSpecifier // TODO: process union
    locals [StructDecl::ptr sd]
    @after {
        helpers_.top().setStruct(StructType::create(std::move($sd)));
    }
    :   structOrUnion id=Identifier?  
        {
        $sd = StructDecl::create($id.text, &context());
        enterContext(*$sd);
        }
        '{' structDeclarationList '}'
        {exitContext();}
    |   structOrUnion id=Identifier
        {$sd = getStructDecl($id.text);}
    ;

structOrUnion
    :   'struct'
    |   'union'
    ;

structDeclarationList
    // c11标准中的语法要求至少一个structDeclaration
    //:   structDeclaration+
    :   structDeclaration*
    ;

structDeclaration // The first two rules have priority order and cannot be simplified to one expression.
    :   {enterDecl();} specifierQualifierList structDeclaratorList ';' {exitDecl();}
    |   {enterDecl();} specifierQualifierList ';' {exitDecl();}
    |   staticAssertDeclaration
    ;

specifierQualifierList
    :   (typeSpecifier | typeQualifier)+
    ;

structDeclaratorList
    :   structDeclarator (',' structDeclarator)*
    ;

structDeclarator
    :   {copyHelper();} declarator {context() << makeField();}
    |   declarator? ':' constantExpression // TODO: to implement
    ;

enumSpecifier
    :   'enum' Identifier? '{' enumeratorList ','? '}'
    |   'enum' Identifier
    ;

enumeratorList
    :   enumerator (',' enumerator)*
    ;

enumerator
    :   enumerationConstant ('=' constantExpression)?
    ;

enumerationConstant
    :   Identifier
    ;

atomicTypeSpecifier
    :   '_Atomic' '(' typeName ')'
    ;

typeQualifier
    :   'const'
    |   'restrict'
    |   'volatile'
    |   '_Atomic'
    ;

functionSpecifier
    :   'inline'
    |   '_Noreturn'
    ;

alignmentSpecifier
    :   '_Alignas' '(' (typeName | constantExpression) ')'
    ;

declarator
    :   pointer? directDeclarator
    ;

directDeclarator
    :   Identifier          {ids_.push($Identifier.text);}
    |   '(' declarator ')'  {setParen();}
    |   directDeclarator '[' typeQualifierList? expression? ']'
        {setArray();}
    |   directDeclarator '[' 'static' typeQualifierList? expression ']'
    |   directDeclarator '[' typeQualifierList 'static' expression ']'
    |   directDeclarator '[' typeQualifierList? '*' ']'
    |   directDeclarator '(' parameterTypeList ')'
        {setFunction();}
    |   directDeclarator '(' identifierList? ')'
        {setFunction(!$ctx->identifierList(), true);}
    |   Identifier ':' DigitSequence  // bit field
    ;

pointer // TODO: process typeQualifierList
    :  '*' {setPointer();} typeQualifierList? pointer?
    ;

typeQualifierList
    :   typeQualifier+
    ;

parameterTypeList
    :   parameterList (',' '...')? // TODO: 不定长参数
    ;

parameterList
    :   {parm_lists_.push();}
        parameterDeclaration (',' parameterDeclaration)*
    ;

parameterDeclaration
    locals [bool has_id]
    @init {
        enterDecl();
        $has_id = false;
    }
    @after {
        parm_lists_.top().push_back(makeParm($has_id));
        exitDecl();
    }
    :   declarationSpecifiers declarator {$has_id = true;}
    |   declarationSpecifiers abstractDeclarator
    |   declarationSpecifiers
    ;

identifierList
    :   Identifier (',' Identifier)*
    ;

typeName
    :   {enterDecl();} specifierQualifierList abstractDeclarator?
        {
        types_.push(helpers_.top().getType());
        exitDecl();
        }
    ;

abstractDeclarator
    :   pointer
    |   pointer? directAbstractDeclarator
    ;

directAbstractDeclarator
    :   '(' abstractDeclarator ')'
    |   '[' typeQualifierList? expression? ']'
        {setArray();}
    |   '[' 'static' typeQualifierList? expression ']'
    |   '[' typeQualifierList 'static' expression ']'
    |   '[' '*' ']'
    |   '(' parameterTypeList? ')'
        {setFunction(!$ctx->parameterTypeList());}
    |   directAbstractDeclarator '[' typeQualifierList? expression? ']'
        {setArray();}
    |   directAbstractDeclarator '[' 'static' typeQualifierList? expression ']'
    |   directAbstractDeclarator '[' typeQualifierList 'static' expression ']'
    |   directAbstractDeclarator '[' '*' ']'
    |   directAbstractDeclarator '(' parameterTypeList? ')'
        {setFunction(!$ctx->parameterTypeList());}
    ;

typedefName
    :   {isTypedefName()}? td=Identifier {setTypedefName($td.text);}
    ;

initializer
    :   expression
    |   '{' initializerList ','? '}' {makeInitListExpr();}
    ;

initializerList // TODO: implement designation feature
    locals [Expr::list init_list]
    :   (designation? initializer {$init_list.push_back(exprs_.pop());})?
        (',' designation? initializer {$init_list.push_back(exprs_.pop());})*
        {arg_lists_.push(std::move($init_list));}
    ;

designation
    :   designatorList '='
    ;

designatorList
    :   designator+
    ;

designator
    :   '[' constantExpression ']'
    |   '.' Identifier
    ;

staticAssertDeclaration // TODO: to implement
    :   '_Static_assert' '(' constantExpression ',' StringLiteral ')' ';'
    ;

statement
    :   labeledStatement
    |   compoundStatement {stmts_.push(blocks_.pop());}
    |   expressionStatement
    |   selectionStatement
    |   iterationStatement
    |   jumpStatement
    |   signStatement
    ;

labeledStatement // TODO: label to implement
    :   Identifier ':' statement
    |   'case' constantExpression ':' statement
    |   'default' ':' statement
    ;

compoundStatement
    locals [CompoundStmt::ptr block]
    @init {
        $block = CompoundStmt::create(&context());
        enterBlock(*$block);
    }
    @after {
        exitBlock();
        blocks_.push(std::move($block));
    }
    :   '{' blockItemList? '}'
    ;

blockItemList
    :   blockItem+
    ;

blockItem
    :   statement   {block() << stmts_.pop();}
    |   declaration // push decl in rule declaration
    ;

expressionStatement
    :   commaExpression? ';' {makeExprStmt($ctx->commaExpression());}
    ;

selectionStatement
    :   'if' '(' commaExpression ')' statement (else='else' statement)?
        {makeIfStmt($else);}
    |   'switch' '(' commaExpression ')' statement // TODO: switch to implement
    ;

iterationStatement
    :   'while' '(' commaExpression ')' statement {makeWhileStmt();}
    |   'do' statement 'while' '(' commaExpression ')' ';' // TODO: do while to implement
    |   'for' '(' forCondition ')' statement      // TODO: for to implement
    ;

forCondition
	:   (commaExpression? ';' | declaration) commaExpression? ';' commaExpression?
	;

jumpStatement
    :   (   'goto' Identifier // TODO: goto to implement
        |   'continue'                {makeContinue();}
        |   'break'                   {makeBreak();}
        |   'return' commaExpression? {makeReturn($ctx->commaExpression());}
        )
        ';'
    ;

signStatement
    :   '@' commaExpression ';' {makeSignStmt();}
    ;

externalDeclaration
    :   functionDefinition
    |   declaration
    |   ';' // stray ;
    ;

functionDefinition // TODO: support k&r style function definition
                   // XXX: may fail when return a function pointer
    locals [FunctionDecl::ptr func]
    :   {
        enterFuncHead();
        helpers_.push();
        }
        declarationSpecifiers
        declarator
        declarationList?
        {
        exitFuncHead();
        $func = makeFuncDef();
        enterContext(*$func);
        }
        compoundStatement
        {
        $func->setBody(blocks_.pop());
        exitContext();
        }
    ;

declarationList
    :   declaration+
    ;
