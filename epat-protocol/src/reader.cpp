#include "reader.h"
#include "CBaseVisitor.h"
#include "CLexer.h"
#include "CParser.h"
#include <sstream>

using namespace epat;
using namespace std;

template <typename _Ty> class MyStack {
    std::vector<_Ty> content_;
public:
    inline _Ty& top() { return content_.back(); }
    inline _Ty& push()
    {
        content_.push_back(_Ty());
        return top();
    }
    inline _Ty& push(_Ty ctt)
    {
        content_.push_back(move(ctt));
        return top();
    }
    inline _Ty pop()
    {
        auto res = move(top());
        content_.pop_back();
        return res;
    }
    inline std::vector<_Ty> pop_from(int pos)
    {
        if (pos > (int)content_.size()) {
            cout << "debug:" << __LINE__ << ": pos out of range" << endl;
            return {};
        }
        std::vector<_Ty> ret(
            std::make_move_iterator(content_.begin() + pos),
            std::make_move_iterator(content_.end())
        );
        content_.erase(content_.begin() + pos, content_.end());
        return ret;
    }
    inline int size() const { return (int)content_.size(); }
};

struct TypeHelper {
    // 用于处理乱序的storegeClassSpecifier,typeSpecifer,typeQualifier等
    // using ptr = std::unique_ptr<TypeHelper>;
private:
    // storageClassSpecifier
    int typedef_ = 0, static_ = 0;
    // typeSpecifier
    int void_ = 0, char_ = 0, short_ = 0, int_ = 0, long_ = 0, float_ = 0;
    int double_ = 0, signed_ = 0, unsigned_ = 0, bool_ = 0, complex_ = 0;
    // int unsigned_ = 0, long_ = 0;
    int struct_ = 0, union_ = 0, enum_ = 0;
    Type::ptr type_;
    // typeQualifier
    // TODO:
public:
    explicit TypeHelper() = default;
    inline QualType getQualType() const { return QualType(); }
    inline void setTypeDef() { ++typedef_; }
    inline void setStatic() { ++static_; }
    inline void setVoid() { ++void_; }
    inline void setChar() { ++char_; }
    inline void setShort() { ++short_; }
    inline void setInt() { ++int_; }
    inline void setLong() { ++long_; }
    inline void setFloat() { ++float_; }
    inline void setDouble() { ++double_; }
    inline void setSigned() { ++signed_; }
    inline void setUnsigned() { ++unsigned_; }
    inline void setBool() { ++bool_; }
    inline void setComplex() { ++complex_; }
    inline void setStruct(StructType::ptr st)
    {
        ++struct_;
        type_ = move(st);
    }
};

// 仅用于数据收集，并非所有语法都支持
class MyVisitor : public CBaseVisitor {
    CLexer& lexer_;
    CompoundStmt::ptr root_;
    // CompoundStmt* ctx_;
    MyStack<Context::ref> ctx_stack_;
    CompoundStmt& root() { return *root_; }
    Context& context() { return *ctx_stack_.top(); }
    CompoundStmt& block() { return *dynamic_cast<CompoundStmt*>(ctx_stack_.top()); }
    MyStack<QualType> type_stack_;
    MyStack<Decl::ptr> decl_stack_;
    MyStack<ParmVarDecl::ptr> parm_decl_stack_;
    MyStack<std::string> identifier_stack_;
    MyStack<Expr::ptr> expr_stack_;
    MyStack<std::string> literal_stack_;
    MyStack<Stmt::ptr> stmt_stack_;
    MyStack<TypeHelper> type_helper_stack_;
public:
    explicit MyVisitor(CLexer& lexer)
        : CBaseVisitor(), lexer_(lexer), root_(Root::create())
    {
        ctx_stack_.push(root_.get());
    }
    CompoundStmt::ptr getRoot() { return move(root_); }
    void dump_info(ostream& os) const
    {
        os << "type_stack: " << type_stack_.size() << endl;
        os << "decl_stack: " << decl_stack_.size() << endl;
        os << "parm_decl_stack: " << parm_decl_stack_.size() << endl;
        os << "identifier_stack: " << identifier_stack_.size() << endl;
        os << "expr_stack: " << expr_stack_.size() << endl;
        os << "literal_stack: " << literal_stack_.size() << endl;
        os << "stmt_stack: " << stmt_stack_.size() << endl;
    }

    // std::any visitCompilationUnit(CParser::CompilationUnitContext* ctx) override;
    std::any visitTranslationUnit(CParser::TranslationUnitContext* ctx) override;
    // expressions
    // std::any visitPrimary(CParser::PrimaryContext* ctx) override;
    std::any visitPostfixExpression(CParser::PostfixExpressionContext* ctx) override;
    std::any visitUnaryExpression(CParser::UnaryExpressionContext* ctx) override;
#define VISIT_BINARY_EXPRESSION_DECL(NAME)                                               \
    std::any visit##NAME##Expression(CParser::NAME##ExpressionContext* ctx) override;
    VISIT_BINARY_EXPRESSION_DECL(Multiplicative);
    VISIT_BINARY_EXPRESSION_DECL(Additive);
    VISIT_BINARY_EXPRESSION_DECL(Shift);
    VISIT_BINARY_EXPRESSION_DECL(Relational);
    VISIT_BINARY_EXPRESSION_DECL(Equality);
    VISIT_BINARY_EXPRESSION_DECL(And);
    VISIT_BINARY_EXPRESSION_DECL(ExclusiveOr);
    VISIT_BINARY_EXPRESSION_DECL(InclusiveOr);
    VISIT_BINARY_EXPRESSION_DECL(LogicalAnd);
    VISIT_BINARY_EXPRESSION_DECL(LogicalOr);
    std::any visitConditionalExpression(CParser::ConditionalExpressionContext* ctx
    ) override;
    VISIT_BINARY_EXPRESSION_DECL(Assignment);
#undef VISIT_BINARY_EXPRESSION_DECL
    std::any visitConstantExpression(CParser::ConstantExpressionContext* ctx) override;
    std::any visitPrimaryExpression(CParser::PrimaryExpressionContext* ctx) override;
    std::any visitConstant(CParser::ConstantContext* ctx) override;
    std::any visitStringLiteral(CParser::StringLiteralContext* ctx) override;
    // std::any visitArgumentExpressionList(CParser::ArgumentExpressionListContext* ctx)
    // override;
    std::any visitCommaExpression(CParser::CommaExpressionContext* ctx) override;
    // declarations
    std::any visitDeclaration(CParser::DeclarationContext* ctx) override;
    std::any visitDeclarationSpecifiers(CParser::DeclarationSpecifiersContext* ctx
    ) override;
    // std::any visitInitDeclaratorList(CParser::InitDeclaratorListContext* ctx) override;
    std::any visitInitDeclarator(CParser::InitDeclaratorContext* ctx) override;
    std::any visitStorageClassSpecifier(CParser::StorageClassSpecifierContext* ctx
    ) override;
    std::any visitTypeSpecifier(CParser::TypeSpecifierContext* ctx) override;
    std::any visitStructOrUnionSpecifier(CParser::StructOrUnionSpecifierContext* ctx
    ) override;
    // std::any visitStructOrUnion(CParser::StructOrUnionContext* ctx) override;
    // std::any visitStructDeclarationList(CParser::StructDeclarationListContext* ctx
    // ) override;
    std::any visitStructDeclaration(CParser::StructDeclarationContext* ctx) override;
    std::any visitSpecifierQualifierList(CParser::SpecifierQualifierListContext* ctx
    ) override;
    // std::any visitStructDeclaratorList(CParser::StructDeclaratorListContext* ctx)
    // override;
    std::any visitStructDeclarator(CParser::StructDeclaratorContext* ctx) override;
    std::any visitEnumSpecifier(CParser::EnumSpecifierContext* ctx) override;
    // std::any visitEnumeratorList(CParser::EnumeratorListContext* ctx) override;
    // std::any visitEnumerator(CParser::EnumeratorContext* ctx) override;
    std::any visitEnumerationConstant(CParser::EnumerationConstantContext* ctx) override;
    std::any visitAtomicTypeSpecifier(CParser::AtomicTypeSpecifierContext* ctx) override;
    std::any visitTypeQualifier(CParser::TypeQualifierContext* ctx) override;
    std::any visitFunctionSpecifier(CParser::FunctionSpecifierContext* ctx) override;
    std::any visitAlignmentSpecifier(CParser::AlignmentSpecifierContext* ctx) override;
    std::any visitDeclarator(CParser::DeclaratorContext* ctx) override;
    std::any visitDirectDeclarator(CParser::DirectDeclaratorContext* ctx) override;
    std::any visitPointer(CParser::PointerContext* ctx) override;
    // std::any visitTypeQualifierList(CParser::TypeQualifierListContext* ctx) override;
    // std::any visitParameterTypeList(CParser::ParameterTypeListContext* ctx) override;
    // std::any visitParameterList(CParser::ParameterListContext* ctx) override;
    std::any visitParameterDeclaration(CParser::ParameterDeclarationContext* ctx
    ) override;
    // std::any visitIdentifierList(CParser::IdentifierListContext* ctx) override;
    std::any visitTypeName(CParser::TypeNameContext* ctx) override;
    std::any visitAbstractDeclarator(CParser::AbstractDeclaratorContext* ctx) override;
    std::any visitDirectAbstractDeclarator(CParser::DirectAbstractDeclaratorContext* ctx
    ) override;
    std::any visitTypedefName(CParser::TypedefNameContext* ctx) override;
    std::any visitInitializer(CParser::InitializerContext* ctx) override;
    std::any visitInitializerList(CParser::InitializerListContext* ctx) override;
    // std::any visitDesignation(CParser::DesignationContext* ctx) override;
    // std::any visitDesignatorList(CParser::DesignatorListContext* ctx) override;
    // std::any visitDesignator(CParser::DesignatorContext* ctx) override;
    std::any visitStaticAssertDeclaration(CParser::StaticAssertDeclarationContext* ctx
    ) override;
    // statements
    std::any visitStatement(CParser::StatementContext* ctx) override;
    std::any visitLabeledStatement(CParser::LabeledStatementContext* ctx) override;
    std::any visitCompoundStatement(CParser::CompoundStatementContext* ctx) override;
    // std::any visitBlockItemList(CParser::BlockItemListContext* ctx) override;
    std::any visitBlockItem(CParser::BlockItemContext* ctx) override;
    std::any visitExpressionStatement(CParser::ExpressionStatementContext* ctx) override;
    std::any visitSelectionStatement(CParser::SelectionStatementContext* ctx) override;
    std::any visitIterationStatement(CParser::IterationStatementContext* ctx) override;
    std::any visitForCondition(CParser::ForConditionContext* ctx) override;
    std::any visitJumpStatement(CParser::JumpStatementContext* ctx) override;
    // external definitions
    // std::any visitExternalDeclaration(CParser::ExternalDeclarationContext* ctx)
    // override;
    std::any visitFunctionDefinition(CParser::FunctionDefinitionContext* ctx) override;
    std::any visitDeclarationList(CParser::DeclarationListContext* ctx) override;
    // TODO: Preprocessing directives
};

std::any MyVisitor::visitTranslationUnit(CParser::TranslationUnitContext* ctx)
{
    for (auto child : ctx->children) {
        int decl_size = decl_stack_.size(),
            stmt_size = stmt_stack_.size(); // 记录当前语句块的声明和语句数量
        visit(child);
        auto decl_list = decl_stack_.pop_from(decl_size);
        for (auto& decl : decl_list)
            root() << move(decl);
        auto stmt_list = stmt_stack_.pop_from(stmt_size);
        for (auto& stmt : stmt_list)
            root() << move(stmt);
    }
    return {};
}

std::any MyVisitor::visitPostfixExpression(CParser::PostfixExpressionContext* ctx)
{
    visit(ctx->expression()[0]);
    auto base = expr_stack_.pop();
    auto second = ctx->children[1]->getText();
    if (second == "[") { // '[' expression ']'
        visit(ctx->expression()[1]);
        expr_stack_.push(ArraySubscript::create(move(base), expr_stack_.pop()));
    }
    else if (second == "(") { // '(' argumentExpressionList? ')'
        Expr::list args;
        if (auto argumentExpressionList = ctx->argumentExpressionList()) {
            int expr_size = expr_stack_.size();
            visitArgumentExpressionList(argumentExpressionList);
            args = expr_stack_.pop_from(expr_size);
        }
        if (auto ret = CallExpr::create(move(base), move(args)))
            expr_stack_.push(move(ret));
        else {
            cout << "debug: unsupported call expression: " << ctx->getText() << endl;
            expr_stack_.push(IntLiteral::create(__LINE__));
        }
    }
    else if (second == ".") { // '.' Identifier
        if (auto qt = base->getType(); qt.isStruct()) {
            auto st = static_pointer_cast<StructType>(qt.get());
            expr_stack_.push(MemberExpr::create(
                move(base), st->getStructDecl(), ctx->Identifier()->getText(), false
            ));
        }
        else {
            cout << "debug: base is not struct: " << ctx->getText() << endl;
            expr_stack_.push(IntLiteral::create(__LINE__));
        }
    }
    else if (second == "->") { // '->' Identifier
        if (auto qt = base->getType(); qt.isPointer()) {
            if (auto pt = qt->getElement(); pt.isStruct()) {
                auto st = static_pointer_cast<StructType>(pt.get());
                expr_stack_.push(MemberExpr::create(
                    move(base), st->getStructDecl(), ctx->Identifier()->getText(), true
                ));
            }
            else {
                cout << "debug: base is not struct: " << ctx->getText() << endl;
                expr_stack_.push(IntLiteral::create(__LINE__));
            }
        }
        else {
            cout << "debug: base is not pointer: " << ctx->getText() << endl;
            expr_stack_.push(IntLiteral::create(__LINE__));
        }
    }
    else if (second == "++") { // '++'
        expr_stack_.push(UnaryOperator::create(move(base), UnaryOperator::Uop::PostInc));
    }
    else if (second == "--") { // '--'
        expr_stack_.push(UnaryOperator::create(move(base), UnaryOperator::Uop::PostDec));
    }
    else {
        cout << "debug: unsupported postfix expression: " << ctx->getText() << endl;
        expr_stack_.push(IntLiteral::create(__LINE__));
    }
    return {};
}

std::any MyVisitor::visitUnaryExpression(CParser::UnaryExpressionContext* ctx)
{
    if (!ctx->expression()) { // ('sizeof' | '_Alignof') '(' typeName ')'
        visitTypeName(ctx->typeName());
        auto type = type_stack_.pop();
        auto first = ctx->children[0]->getText();
        if (first == "sizeof") {
            expr_stack_.push(IntLiteral::create(type->getSize()));
        }
        else if (first == "_Alignof") {
            // TODO: 对齐未实现。等同于sizeof
            expr_stack_.push(IntLiteral::create(type->getSize()));
        }
        else {
            cout << "debug: unsupported unary expression: " << ctx->getText() << endl;
            expr_stack_.push(IntLiteral::create(__LINE__));
        }
    }
    visit(ctx->expression());
    auto base = expr_stack_.pop();
    auto first = ctx->children[0]->getText();
    if (first == "++" || first == "--" || first == "+" || first == "-" || first == "!" ||
        first == "~" || first == "&" || first == "*") {
        expr_stack_.push(UnaryOperator::create(move(base), first));
    }
    else if (first == "(") { // '(' typename ')' expression
        visitTypeName(ctx->typeName());
        auto type = type_stack_.pop();
        expr_stack_.push(CastExpr::create(move(base), type));
    }
    else if (first == "sizeof") { // 'sizeof' expression
        expr_stack_.push(IntLiteral::create(base->getSize()));
    }
    else {
        cout << "debug: unsupported unary expression: " << ctx->getText() << endl;
        expr_stack_.push(IntLiteral::create(__LINE__));
    }
    return {};
}

#define VISIT_BINARY_EXPRESSION(NAME)                                                    \
    std::any MyVisitor::visit##NAME##Expression(CParser::NAME##ExpressionContext* ctx)   \
    {                                                                                    \
        visit(ctx->expression()[0]);                                                     \
        auto lhs = expr_stack_.pop();                                                    \
        visit(ctx->expression()[1]);                                                     \
        auto rhs = expr_stack_.pop();                                                    \
        expr_stack_.push(                                                                \
            BinaryOperator::create(move(lhs), move(rhs), ctx->children[1]->getText())    \
        );                                                                               \
        return {};                                                                       \
    }
VISIT_BINARY_EXPRESSION(Multiplicative)
VISIT_BINARY_EXPRESSION(Additive)
VISIT_BINARY_EXPRESSION(Shift)
VISIT_BINARY_EXPRESSION(Relational)
VISIT_BINARY_EXPRESSION(Equality)
VISIT_BINARY_EXPRESSION(And)
VISIT_BINARY_EXPRESSION(ExclusiveOr)
VISIT_BINARY_EXPRESSION(InclusiveOr)
VISIT_BINARY_EXPRESSION(LogicalAnd)
VISIT_BINARY_EXPRESSION(LogicalOr)

std::any MyVisitor::visitConditionalExpression(CParser::ConditionalExpressionContext* ctx)
{
    // TODO: to implement
    cout << "debug: conditionalExpression is not supported: " << ctx->getText() << endl;
    expr_stack_.push(StrLiteral::create("conditionalExpression"));
    return {};
}

VISIT_BINARY_EXPRESSION(Assignment)
#undef VISIT_BINARY_EXPRESSION

std::any MyVisitor::visitConstantExpression(CParser::ConstantExpressionContext* ctx)
{
    // TODO: 预定的流程是： 生成表达式->evaluate->返回IntLiteral
    // 目前仅支持整数常量
    visit(ctx->expression());
    auto expr = expr_stack_.pop();
    if (auto intLit = dynamic_cast<IntLiteral*>(expr.get())) return {};
    cout << "debug: should be a constant: " << ctx->getText() << endl;
    expr_stack_.push(IntLiteral::create(__LINE__));
    return {};
}

std::any MyVisitor::visitPrimaryExpression(CParser::PrimaryExpressionContext* ctx)
{
    if (auto commaExpression = ctx->commaExpression()) {
        visitCommaExpression(commaExpression);
    }
    else if (auto Identifier = ctx->Identifier()) {
        auto vd = root().getValueDecl(Identifier->getText());
        if (vd)
            expr_stack_.push(DeclRefExpr::create(vd));
        else {
            cout << "debug: undefined or invalid identifier: " << Identifier->getText()
                 << endl;
            expr_stack_.push(IntLiteral::create(__LINE__));
        }
    }
    else if (auto constant = ctx->constant()) {
        visitConstant(constant);
    }
    else {
        cout << "debug: unsupported primary expression: " << ctx->getText() << endl;
        expr_stack_.push(IntLiteral::create(__LINE__));
    }
    return {};
}

std::any MyVisitor::visitConstant(CParser::ConstantContext* ctx)
{
    if (auto IntegerConstant = ctx->IntegerConstant()) {
        try {
            expr_stack_.push(IntLiteral::create((int)std::stoll(IntegerConstant->getText()
            )));
        }
        catch (...) {
            cout << "debug: invalid integer constant: " << IntegerConstant->getText()
                 << endl;
            expr_stack_.push(IntLiteral::create(__LINE__));
        }
    }
    else if (auto FloatingConstant = ctx->FloatingConstant()) {
        try {
            expr_stack_.push(FltLiteral::create((float
            )std::stold(FloatingConstant->getText())));
        }
        catch (...) {
            cout << "debug: invalid floating constant: " << FloatingConstant->getText()
                 << endl;
            expr_stack_.push(IntLiteral::create(__LINE__));
        }
    }
    else if (auto CharacterConstant = ctx->CharacterConstant()) {
        // C语言中的字符常量可以很长，如'abc'
        // TODO: 忽视EncodingPredix
        auto literal = CharacterConstant->getText();
        auto begin = literal.find('\''), end = literal.size() - 1;
        int res = 0;
        for (auto i = begin; i < end; ++i) {
            res *= 256;
            res += literal[i];
        }
        expr_stack_.push(IntLiteral::create(res));
    }
    return {};
}

std::any MyVisitor::visitStringLiteral(CParser::StringLiteralContext* ctx)
{
    std::string literal = "";
    // TODO: 忽视EncodingPredix
    if (auto SCharSequence = ctx->SCharSequence()) literal = SCharSequence->getText();
    literal += '\0';
    expr_stack_.push(StrLiteral::create(move(literal)));
    return {};
}

std::any MyVisitor::visitCommaExpression(CParser::CommaExpressionContext* ctx)
{
    visit(ctx->expression());
    if (auto commaExpression = ctx->commaExpression()) {
        auto expr = expr_stack_.pop();
        visitCommaExpression(commaExpression);
        expr_stack_.push(BinaryOperator::create(expr_stack_.pop(), move(expr), ","));
    }
    return {};
}

std::any MyVisitor::visitDeclaration(CParser::DeclarationContext* ctx)
{
    if (auto declarationSpecifiers = ctx->declarationSpecifiers()) {
        visitDeclarationSpecifiers(declarationSpecifiers); //类型入栈
        if (auto initDeclaratorList = ctx->initDeclaratorList())
            visitInitDeclaratorList(initDeclaratorList);
        type_stack_.pop(); //类型出栈
    }
    else if (auto staticAssertDeclaration = ctx->staticAssertDeclaration()) {
        visitStaticAssertDeclaration(staticAssertDeclaration);
    }
    else {
        cout << "debug: unsupported declaration: " << ctx->getText() << endl;
    }
    return {};
}

std::any MyVisitor::visitDeclarationSpecifiers(CParser::DeclarationSpecifiersContext* ctx)
{
    type_helper_stack_.push();
    visitChildren(ctx);
    type_stack_.push(type_helper_stack_.pop().getQualType());
    return visitChildren(ctx);
}

// std::any MyVisitor::visitInitDeclaratorList(CParser::InitDeclaratorListContext* ctx) {}

std::any MyVisitor::visitInitDeclarator(CParser::InitDeclaratorContext* ctx)
{
    type_stack_.push(type_stack_.top()); // 复制一份基础类型入栈
    visitDeclarator(ctx->declarator());  // 获取完整类型和标识符
    if (auto initializer = ctx->initializer()) {
        visitInitializer(initializer);
        decl_stack_.push(
            VarDecl::create(identifier_stack_.pop(), type_stack_.pop(), expr_stack_.pop())
        );
    }
    else
        decl_stack_.push(VarDecl::create(identifier_stack_.pop(), type_stack_.pop()));
    return {};
}

std::any MyVisitor::visitStorageClassSpecifier(CParser::StorageClassSpecifierContext* ctx)
{
    auto text = ctx->getText();
    if (text == "typedef") {
        type_helper_stack_.top().setTypeDef();
    }
    else if (text == "static") {
        type_helper_stack_.top().setStatic();
    }
    else {
        cout << "debug: unsupported storage class specifier: " << ctx->getText() << endl;
    }
    return {};
}

std::any MyVisitor::visitTypeSpecifier(CParser::TypeSpecifierContext* ctx)
{
    if (auto atomicTypeSpecifier = ctx->atomicTypeSpecifier())
        return visitAtomicTypeSpecifier(atomicTypeSpecifier);
    else if (auto structOrUnionSpecifier = ctx->structOrUnionSpecifier())
        return visitStructOrUnionSpecifier(structOrUnionSpecifier);
    else if (auto enumSpecifier = ctx->enumSpecifier())
        return visitEnumSpecifier(enumSpecifier);
    else if (auto typedefName = ctx->typedefName())
        return visitTypedefName(typedefName);
    // TODO: long long int等
    if (auto first = ctx->children[0]->getText(); first == "void")
        type_helper_stack_.top().setVoid();
    else if (first == "char")
        type_helper_stack_.top().setChar();
    else if (first == "short")
        type_helper_stack_.top().setShort();
    else if (first == "int")
        type_helper_stack_.top().setInt();
    else if (first == "long")
        type_helper_stack_.top().setLong();
    else if (first == "float")
        type_helper_stack_.top().setFloat();
    else if (first == "double")
        type_helper_stack_.top().setDouble();
    else if (first == "signed")
        type_helper_stack_.top().setSigned();
    else if (first == "unsigned")
        type_helper_stack_.top().setUnsigned();
    // else if (first == "_Bool")
    //     type_helper_stack_.get().setBool();
    // else if (first == "_Complex")
    //     type_helper_stack_.get().setComplex();
    else {
        cout << "debug: unsupported type specifier: " << ctx->getText() << endl;
        type_helper_stack_.top().setInt();
    }
    return {};
}

std::any MyVisitor::visitStructOrUnionSpecifier(
    CParser::StructOrUnionSpecifierContext* ctx
)
{
    // TODO: 处理union
    auto Identifier = ctx->Identifier();
    auto name = Identifier ? Identifier->getText() : "";
    if (auto structDeclarationList = ctx->structDeclarationList()) {
        auto sd = StructDecl::create(name, &context());
        context() << sd;
        ctx_stack_.push(sd.get());
        visitStructDeclarationList(structDeclarationList);
        ctx_stack_.pop();
        type_helper_stack_.top().setStruct(StructType::create(sd));
    }
    else {
        auto vd = context().getValueDecl(name);
        if (auto sd = dynamic_pointer_cast<StructDecl>(vd)) {
            type_helper_stack_.top().setStruct(StructType::create(sd));
        }
        else {
            cout << "debug: identifier is not a struct: " << Identifier->getText()
                 << endl;
            type_helper_stack_.top().setInt();
        }
    }
    return {};
}

// std::any visitStructOrUnion(CParser::StructOrUnionContext* ctx) {}

// std::any MyVisitor::visitStructDeclarationList(CParser::StructDeclarationListContext*
// ctx) {}

std::any MyVisitor::visitStructDeclaration(CParser::StructDeclarationContext* ctx)
{
    // only process specifierQualifierList structDeclaratorList ';'
    if (auto structDeclaratorList = ctx->structDeclaratorList()) {
        visitSpecifierQualifierList(ctx->specifierQualifierList()); // 类型出栈
        auto type = type_stack_.pop();                              // 类型出栈
        visitStructDeclaratorList(structDeclaratorList);
    }
    else {
        cout << "debug: unsupported struct declaration: " << ctx->getText() << endl;
    }
    return {};
}

std::any MyVisitor::visitSpecifierQualifierList(
    CParser::SpecifierQualifierListContext* ctx
)
{
    type_helper_stack_.push();
    visitChildren(ctx);
    type_stack_.push(type_helper_stack_.pop().getQualType());
    return {};
}

// std::any MyVisitor::visitStructDeclaratorList(CParser::StructDeclaratorListContext*
// ctx) {}

std::any MyVisitor::visitStructDeclarator(CParser::StructDeclaratorContext* ctx)
{
    // TODO: process declarator? ':' constantExpression
    visitDeclarator(ctx->declarator());
    return {};
}

std::any MyVisitor::visitEnumSpecifier(CParser::EnumSpecifierContext* ctx)
{
    // TODO: enum is not supported now.
    cout << "debug: enum is not supported now: " << ctx->getText() << "" << endl;
    type_helper_stack_.top().setInt();
    // auto Identifier = ctx->Identifier();
    // auto name = Identifier ? Identifier->getText() : "";
    // if (auto enumeratorList = ctx->enumeratorList()) {
    //     auto sd = StructDecl::create(name, &context());
    //     context() << sd;
    //     ctx_stack_.push(sd.get());
    //     visitStructDeclarationList(structDeclarationList);
    //     ctx_stack_.pop();
    //     type_helper_stack_.get().setStruct(StructType::create(sd));
    // }
    // else {
    //     auto vd = context().getValueDecl(name);
    //     if (auto sd = dynamic_pointer_cast<StructDecl>(vd)) {
    //         type_helper_stack_.get().setStruct(StructType::create(sd));
    //     }
    //     else {
    //         cout << "debug: identifier is not a struct: " << Identifier->getText()
    //              << endl;
    //         type_helper_stack_.get().setInt();
    //     }
    // }
    return {};
}

// std::any MyVisitor::visitEnumeratorList(CParser::EnumeratorListContext* ctx) {}

// std::any MyVisitor::visitEnumerator(CParser::EnumeratorContext* ctx) {}

std::any MyVisitor::visitEnumerationConstant(CParser::EnumerationConstantContext* ctx)
{
    cout << "debug: enumeration constant is not supported now: " << ctx->getText()
         << endl;
    expr_stack_.push(IntLiteral::create(__LINE__));
    return {};
}

std::any MyVisitor::visitAtomicTypeSpecifier(CParser::AtomicTypeSpecifierContext* ctx)
{
    cout << "debug: atomic type specifier is not supported now: " << ctx->getText()
         << endl;
    return {};
}

std::any MyVisitor::visitTypeQualifier(CParser::TypeQualifierContext* ctx)
{
    // TODO: to implement
    cout << "debug: skip type qualifier: " << ctx->getText() << endl;
    return {};
}

std::any MyVisitor::visitFunctionSpecifier(CParser::FunctionSpecifierContext* ctx)
{
    cout << "debug: skip function specifier: " << ctx->getText() << endl;
    return {};
}

std::any MyVisitor::visitAlignmentSpecifier(CParser::AlignmentSpecifierContext* ctx)
{
    cout << "debug: skip alignment specifier: " << ctx->getText() << endl;
    return {};
}

std::any MyVisitor::visitDeclarator(CParser::DeclaratorContext* ctx)
{
    if (auto pointer = ctx->pointer()) visitPointer(pointer);
    return visitDirectDeclarator(ctx->directDeclarator());
}

std::any MyVisitor::visitDirectDeclarator(CParser::DirectDeclaratorContext* ctx)
{
    if (auto Identifier = ctx->Identifier()) {
        if (auto DigitSequence = ctx->DigitSequence()) { // Identifier ':' DigitSequence
            cout << "debug: unsupported identifier: " << ctx->getText() << endl;
            identifier_stack_.push(Identifier->getText());
        }
        else { // Identifier
            identifier_stack_.push(Identifier->getText());
        }
    }
    else if (auto declartor = ctx->declarator()) {
        visitDeclarator(declartor);
    }
    else if (ctx->children[1]->getText() == "[") {
        // directDeclarator '[' typeQualifierList? expression? ']'
        // directDeclarator '[' 'static' typeQualifierList? expression ']'
        // directDeclarator '[' typeQualifierList 'static' expression ']'
        // directDeclarator '[' typeQualifierList? '*' ']'
        // TODO: 其中很多种只能用于函数定义，所以暂时不处理
        Expr::ptr expr;
        if (auto expression = ctx->expression()) {
            visit(expression);
            expr = expr_stack_.pop();
        }
        auto& type = type_stack_.top();
        type = ArrayType::create(type, move(expr));
        visitDirectDeclarator(ctx->directDeclarator());
    }
    else if (ctx->children[1]->getText() == "(") {
        // directDeclarator '(' parameterTypeList ')'
        // directDeclarator '(' identifierList? ')'
        // TODO: 第二条规则究竟什么意思？？？K&R？
        auto parm_list = ParmVarDecl::list();
        if (auto parmeterTypeList = ctx->parameterTypeList()) {
            int pos = parm_decl_stack_.size();
            visitParameterTypeList(parmeterTypeList);
            parm_list = parm_decl_stack_.pop_from(pos);
        }
        QualType::list type_list;
        for (auto& parm : parm_list)
            type_list.push_back(parm->getType());
        auto& type = type_stack_.top();
        type = FunctionType::create(type, move(type_list));
        visitDirectDeclarator(ctx->directDeclarator());
    }
    else {
        cout << "debug: unsupported DirectDeclarator: " << ctx->getText() << endl;
    }
    return {};
}

std::any MyVisitor::visitPointer(CParser::PointerContext* ctx)
{
    // TODO: 处理typeQualifierList
    auto& type = type_stack_.top();
    type = PointerType::create(type);
    if (auto pointer = ctx->pointer()) visitPointer(pointer);
    return {};
}

// std::any MyVisitor::visitTypeQualifierList(CParser::TypeQualifierListContext* ctx) {}

// std::any MyVisitor::visitParameterTypeList(CParser::ParameterTypeListContext* ctx) {}

// std::any MyVisitor::visitParameterList(CParser::ParameterListContext* ctx) {}

std::any MyVisitor::visitParameterDeclaration(CParser::ParameterDeclarationContext* ctx)
{
    auto declarationSpecifiers = ctx->declarationSpecifiers();
    visitDeclarationSpecifiers(declarationSpecifiers);
    if (auto declarator = ctx->declarator()) {
        visitDeclarator(declarator);
        parm_decl_stack_.push(
            ParmVarDecl::create(identifier_stack_.pop(), type_stack_.pop())
        );
    }
    else if (auto abstractDeclarator = ctx->abstractDeclarator()) {
        visitAbstractDeclarator(abstractDeclarator);
        parm_decl_stack_.push(ParmVarDecl::create("", type_stack_.pop()));
    }
    else {
        cout << "debug: unsupported parameter declaration: " << ctx->getText() << endl;
        parm_decl_stack_.push(ParmVarDecl::create("", type_stack_.pop()));
    }
    return {};
}

// std::any MyVisitor::visitIdentifierList(CParser::IdentifierListContext* ctx) {}

std::any MyVisitor::visitTypeName(CParser::TypeNameContext* ctx)
{
    visitSpecifierQualifierList(ctx->specifierQualifierList());
    if (auto abstractDeclarator = ctx->abstractDeclarator())
        visitAbstractDeclarator(abstractDeclarator);
    return {};
}

std::any MyVisitor::visitAbstractDeclarator(CParser::AbstractDeclaratorContext* ctx)
{
    if (auto pointer = ctx->pointer()) visitPointer(pointer);
    if (auto directAbstractDeclarator = ctx->directAbstractDeclarator())
        visitDirectAbstractDeclarator(directAbstractDeclarator);
    return {};
}

std::any MyVisitor::visitDirectAbstractDeclarator(
    CParser::DirectAbstractDeclaratorContext* ctx
)
{
    if (auto abstractDeclarator = ctx->abstractDeclarator())
        visitAbstractDeclarator(abstractDeclarator);
    else if (ctx->children[0]->getText() == "[" || ctx->children[1]->getText() == "[") { // directAbstractDeclarator? '[' IntegerConstant? ']'
        auto expr = Expr::ptr();
        if (auto expression = ctx->expression()) {
            visit(expression);
            expr = expr_stack_.pop();
        }
        auto& type = type_stack_.top();
        type = ArrayType::create(type, move(expr));
        if (auto directAbstractDeclarator = ctx->directAbstractDeclarator())
            visitDirectAbstractDeclarator(directAbstractDeclarator);
    }
    else if (ctx->children[0]->getText() == "(" || ctx->children[1]->getText() == "(") { // directAbstractDeclarator? '(' parameterTypeList? ')'
        auto parm_list = ParmVarDecl::list();
        if (auto parmeterTypeList = ctx->parameterTypeList()) {
            int pos = parm_decl_stack_.size();
            visitParameterTypeList(parmeterTypeList);
            parm_list = parm_decl_stack_.pop_from(pos);
        }
        QualType::list type_list;
        for (auto& parm : parm_list)
            type_list.push_back(parm->getType());
        auto& type = type_stack_.top();
        type = FunctionType::create(type, move(type_list));
        if (auto directAbstractDeclarator = ctx->directAbstractDeclarator())
            visitDirectAbstractDeclarator(directAbstractDeclarator);
    }
    else {
        cout << "debug: unsupported directAbstractDeclarator: " << ctx->getText() << endl;
    }
    return {};
}

std::any MyVisitor::visitTypedefName(CParser::TypedefNameContext* ctx)
{
    // TODO: to implement
    auto Identifier = ctx->Identifier();
    type_helper_stack_.top().setInt();
    return {};
}

std::any MyVisitor::visitInitializer(CParser::InitializerContext* ctx)
{
    if (auto expression = ctx->expression())
        visit(expression);
    else if (auto initializerList = ctx->initializerList())
        visitInitializerList(initializerList);
    else {
        cout << "debug: unsupported initializer: " << ctx->getText() << endl;
        expr_stack_.push(IntLiteral::create(__LINE__));
    }
    return {};
}

std::any MyVisitor::visitInitializerList(CParser::InitializerListContext* ctx)
{
    auto list = Expr::list();
    // TODO: 包括designation
    for (auto init : ctx->initializer()) {
        visitInitializer(init);
        list.push_back(expr_stack_.pop());
    }
    expr_stack_.push(InitListExpr::create(move(list)));
    return {};
}

// std::any MyVisitor::visitDesignation(CParser::DesignationContext* ctx) {}

// std::any MyVisitor::visitDesignatorList(CParser::DesignatorListContext* ctx) {}

// std::any MyVisitor::visitDesignator(CParser::DesignatorContext* ctx) {}

std::any MyVisitor::visitStaticAssertDeclaration(
    CParser::StaticAssertDeclarationContext* ctx
)
{
    return {};
}

std::any MyVisitor::visitStatement(CParser::StatementContext* ctx)
{
    return visitChildren(ctx);
}

std::any MyVisitor::visitLabeledStatement(CParser::LabeledStatementContext* ctx)
{
    cout << "debug: skip labeled statement: " << ctx->getText() << endl;
    stmt_stack_.push(StrLiteral::create(ctx->getText()));
    return {};
}

std::any MyVisitor::visitCompoundStatement(CParser::CompoundStatementContext* ctx)
{
    auto cs = CompoundStmt::create(&context());
    ctx_stack_.push(cs.get());
    stmt_stack_.push(move(cs));
    return visitChildren(ctx);
}

// std::any MyVisitor::visitBlockItemList(CParser::BlockItemListContext* ctx) {}

std::any MyVisitor::visitBlockItem(CParser::BlockItemContext* ctx)
{
    if (auto statement = ctx->statement()) {
        visit(statement);
        block() << stmt_stack_.pop();
    }
    else if (auto declaration = ctx->declaration()) {
        visit(declaration);
        context() << decl_stack_.pop();
    }
    else {
        cout << "debug: unsupported block item: " << ctx->getText() << endl;
        block() << StrLiteral::create(ctx->getText());
    }
    return {};
}

std::any MyVisitor::visitExpressionStatement(CParser::ExpressionStatementContext* ctx)
{
    if (auto expression = ctx->commaExpression()) {
        visit(expression);
        stmt_stack_.push(expr_stack_.pop());
    }
    else
        stmt_stack_.push(StrLiteral::create(ctx->getText()));
    return {};
}

std::any MyVisitor::visitSelectionStatement(CParser::SelectionStatementContext* ctx)
{
    auto first = ctx->children[0]->getText();
    if (first == "if") {
        visitCommaExpression(ctx->commaExpression());
        auto cond = expr_stack_.pop();
        auto stmt_list = ctx->statement();
        visitStatement(stmt_list[0]);
        auto body = stmt_stack_.pop(), _else = Stmt::ptr();
        if (stmt_list.size() > 1) {
            visitStatement(stmt_list[1]);
            _else = stmt_stack_.pop();
        }
        stmt_stack_.push(IfStmt::create(move(cond), move(body), move(_else)));
    }
    else if (first == "switch") {
        cout << "debug: skip switch statement: " << ctx->getText() << endl;
    }
    else {
        cout << "debug: unsupported selection statement: " << ctx->getText() << endl;
        stmt_stack_.push(StrLiteral::create(ctx->getText()));
    }
    return {};
}

std::any MyVisitor::visitIterationStatement(CParser::IterationStatementContext* ctx)
{
    auto first = ctx->children[0]->getText();
    if (first == "while") {
        visitCommaExpression(ctx->commaExpression());
        auto cond = expr_stack_.pop();
        visitStatement(ctx->statement());
        auto body = stmt_stack_.pop();
        stmt_stack_.push(WhileStmt::create(move(cond), move(body)));
    }
    else if (first == "do") {
        cout << "debug: skip do statement: " << ctx->getText() << endl;
    }
    else if (first == "for") {
        // TODO: to implement
        cout << "debug: skip for statement: " << ctx->getText() << endl;
    }
    return {};
}

std::any MyVisitor::visitForCondition(CParser::ForConditionContext* ctx)
{
    // TODO: to implement
    cout << "debug: skip for condition: " << ctx->getText() << endl;
    return {};
}

std::any MyVisitor::visitJumpStatement(CParser::JumpStatementContext* ctx)
{
    auto first = ctx->children[0]->getText();
    if (first == "goto") {
        cout << "debug: skip goto statement: " << ctx->getText() << endl;
    }
    else if (first == "continue") {
        block() << ContinueStmt::create();
    }
    else if (first == "break") {
        block() << BreakStmt::create();
    }
    else if (first == "return") {
        if (auto commaExpression = ctx->commaExpression()) {
            visitCommaExpression(commaExpression);
            block() << ReturnStmt::create(expr_stack_.pop());
        }
        else
            block() << ReturnStmt::create();
    }
    else {
        cout << "debug: unsupported jump statement: " << ctx->getText() << endl;
        stmt_stack_.push(StrLiteral::create(ctx->getText()));
    }
    return {};
}

// std::any MyVisitor::visitExternalDeclaration(CParser::ExternalDeclarationContext* ctx)
// {}

std::any MyVisitor::visitFunctionDefinition(CParser::FunctionDefinitionContext* ctx)
{
    // TODO: to implement
    cout << "debug: skip function definition: " << ctx->getText() << endl;
    return {};
}

std::any MyVisitor::visitDeclarationList(CParser::DeclarationListContext* ctx)
{
    // TODO: to implement
    cout << "debug: skip declaration list: " << ctx->getText() << endl;
    return {};
}

CompoundStmt::ptr parseFromStream(std::istream& in)
{
    antlr4::ANTLRInputStream input(in);
    CLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    CParser parser(&tokens);

    auto tree = parser.compilationUnit();
    auto visitor = MyVisitor(lexer);
    visitor.visit(tree);
    visitor.dump_info(cout);

    // for debug
    cout << tree->getText() << endl;

    return visitor.getRoot();
}

epat::Reader::Reader(std::istream& in)
{
    root = parseFromStream(in);
}

epat::Reader::Reader(const std::string& in)
{
    istringstream _in(in);
    root = parseFromStream(_in);
}

CompoundStmt::ptr epat::Reader::getRoot()
{
    return move(root);
}
