#include "CParser.h"
#include <iostream>

using namespace std;

void CParser::dumpStackInfo()
{
    // cout << "stack:" << endl;
    // cout << "ctx_stack_: " << ctx_stack_.size() << endl;
    // cout << "decls_: " << decls_.size() << endl;
    // cout << "arg_lists_: " << arg_lists_.size() << endl;
    // cout << "exprs_: " << exprs_.size() << endl;
    // cout << "types_: " << types_.size() << endl;
    // cout << "helpers_: " << helpers_.size() << endl;
}

void CParser::copyHelper()
{
    helpers_.push(helpers_.top().copy());
}

void CParser::makeArraySubscript()
{
    auto sub_ = exprs_.pop();
    auto base_ = exprs_.pop();
    // base类型必须是数组或是指针
    auto qt = base_->getType();
    if (qt.isArray() || qt.isPointer())
        exprs_.push(ArraySubscript::create(std::move(base_), std::move(sub_)));
    else
        epat_error("array subscript base must be array or pointer");
}

void CParser::makeBinary(const std::string& op)
{
    auto rhs = exprs_.pop();
    auto lhs = exprs_.pop();
    exprs_.push(BinaryOperator::create(std::move(lhs), std::move(rhs), op));
}

void CParser::makeCall(bool has_args)
{
    auto args = has_args ? arg_lists_.pop() : Expr::list();
    exprs_.push(CallExpr::create(exprs_.pop(), std::move(args)));
}

void CParser::makeCast()
{
    exprs_.push(CastExpr::create(exprs_.pop(), types_.pop()));
}

void CParser::makeExprStmt(bool not_empty)
{
    if (not_empty)
        stmts_.push(exprs_.pop());
    else
        stmts_.push(NullStmt::create());
}

void CParser::makeIfStmt(bool has_else)
{
    Expr::ptr _cond;
    Stmt::ptr _then, _else;
    if (has_else)
        _else = stmts_.pop();
    _then = stmts_.pop();
    _cond = exprs_.pop();
    stmts_.push(IfStmt::create(std::move(_cond), std::move(_then), std::move(_else)));
}

void CParser::makeInitListExpr()
{
    exprs_.push(InitListExpr::create(arg_lists_.pop()));
}

void CParser::makeChr(const std::string& text)
{
    // C语言中的字符常量可以很长，如'abc'
    // TODO: 忽视EncodingPredix
    auto begin = text.find('\''), end = text.size() - 1;
    long long res = 0;
    for (auto i = begin + 1; i < end; ++i) {
        res *= 256;
        res += text[i];
    }
    exprs_.push(ChrLiteral::create(res));
}

void CParser::makeInt(const std::string& text)
{
    try {
        auto value = std::stoll(text);
        exprs_.push(IntLiteral::create(value));
    }
    catch (...) {
        exprs_.push(IntLiteral::create(404));
    }
}

void CParser::makeFlt(const std::string& text)
{
    try {
        auto value = std::stold(text);
        exprs_.push(FltLiteral::create(value));
    }
    catch (...) {
        exprs_.push(FltLiteral::create(404.0));
    }
}

void CParser::makeStr(const std::string& text)
{
    exprs_.push(StrLiteral::create(text));
}

void CParser::makeMember(const std::string& mbr, const std::string& arrow)
{
    exprs_.push(MemberExpr::create(exprs_.pop(), mbr, "->" == arrow));
}

void CParser::setArray() // TODO: int a[] = {};
{
    helpers_.top().setArray(exprs_.pop());
}

void CParser::setFunction(bool no_parm, bool k_and_r)
{
    if (no_parm)
        parm_lists_.push();
    auto types = QualType::list();
    auto& parms = parm_lists_.top();
    for (auto& p : parms)
        types.push_back(p->getType());
    if (!in_func_head_)
        parm_lists_.pop();
    // TODO: K&R to implement
    helpers_.top().setFunction(std::move(types));
}

void CParser::setParen()
{
    helpers_.top().setParen();
}

void CParser::setPointer()
{
    helpers_.top().setPointer();
}

void CParser::setTypedefName(std::string const& name)
{
    auto td = getTypeDecl(name); // XXX: 是否检查是不是td
    helpers_.top().setTypedefName(TypedefType::create(td));
}

void CParser::makeRef(const std::string& name)
{
    auto vd = context().getValueDecl(name);
    if (!vd) {
        // XXX: 未定义符号默认为函数
        // 允许未定义函数
        std::cout << "find an undefined symbol: " << name
                  << ", assuming it is a function." << std::endl;
        vd = FunctionDecl::createImplicit(name);
    }
    exprs_.push(DeclRefExpr::create(vd));
}

void CParser::makeReturn(bool has_ret)
{
    if (has_ret)
        stmts_.push(ReturnStmt::create(exprs_.pop()));
    else
        stmts_.push(ReturnStmt::create());
}

void CParser::makeSignStmt()
{
    stmts_.push(SignStmt::create(exprs_.pop()));
}

void CParser::makeSizeof(bool isExpr)
{
    if (isExpr)
        exprs_.push(SizeofExpr::create(exprs_.pop()));
    else
        exprs_.push(SizeofExpr::create(types_.pop()));
}

void CParser::makeUnary(const std::string& op, bool postfix)
{
    if ("sizeof" == op)
        makeSizeof(true);
    else
        exprs_.push(UnaryOperator::create(exprs_.pop(), op, postfix));
}

void CParser::makeWhileStmt()
{
    auto _body = stmts_.pop();
    auto _cond = exprs_.pop();
    stmts_.push(WhileStmt::create(std::move(_cond), std::move(_body)));
}

bool CParser::isTypedefName()
{
    auto id = getCurrentToken()->getText();
    auto td = getTypeDecl(id); // XXX: 是否判断是不是td？
    return !!td;
}

StructDecl::ptr CParser::getStructDecl(const std::string& name)
{
    auto d = context().getDecl(name);
    if (!d) {
        std::cout << "error: struct " << name << " not found" << std::endl;
        return {};
    }
    if (auto sd = dynamic_pointer_cast<StructDecl>(d)) {
        return sd;
    }
    else {
        std::cout << "error: " << name << " is not a struct" << std::endl;
        return {};
    }
}

Decl::ptr CParser::makeDecl(bool init)
{
    auto name = ids_.pop();
    auto helper = helpers_.pop();
    auto type = helper.getType();
    if (helper.isTypeDef()) {
        return TypeDecl::create(std::move(name), type);
    }
    else if (type.isFunction()) {
        // XXX: 检查兼容性等
        return {};
    }
    else {
        return VarDecl::create(std::move(name), type, init ? exprs_.pop() : nullptr);
    }
    return {};
}

FieldDecl::ptr CParser::makeField()
{
    auto name = ids_.pop();
    auto helper = helpers_.pop();
    return FieldDecl::create(std::move(name), helper.getType());
}

FunctionDecl::ptr CParser::makeFuncDef()
{
    auto name = ids_.pop();
    auto helper = helpers_.pop();
    auto fd = context().getFunctionDecl(name);
    if (fd) {
        // XXX: 判断兼容性。不判断可能导致崩溃
        return fd;
    }
    else {
        return FunctionDecl::create(std::move(name), helper.getType().getReturnType(),
                                    std::move(parm_lists_.pop()), &context());
    }
}

ParmVarDecl::ptr CParser::makeParm(bool has_id)
{
    auto name = has_id ? ids_.pop() : "";
    auto type = helpers_.top().getType();
    return ParmVarDecl::create(std::move(name), std::move(type));
}

TypeDecl::ptr CParser::getTypeDecl(const std::string& name)
{
    return context().getTypeDecl(name);
}

void CParser::pushArg()
{
    arg_lists_.top().push_back(exprs_.pop());
}

void CParser::pushStruct(const std::string& name)
{
    auto sd = StructDecl::create(name, &context());
    structs_.push(sd);
    context() << sd;
    ctx_stack_.push(sd.get());
}

void CParser::popStruct()
{
    ctx_stack_.pop();
    types_.push(StructType::create(structs_.pop()));
}
