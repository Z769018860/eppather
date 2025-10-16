#include "stmt.h"
#include "decl.h"
#include "reader.h"
#include "writer.h"
#include <ostream>
#include <sstream>
#include <string>

using namespace std;

epat::Stmt::Stmt(StmtKind kind) : Node() //, kind_(kind)
{
}

const char* epat::Stmt::stmtKind2Str(StmtKind sk)
{
    return StmtKindNameList[static_cast<int>(sk)];
}

epat::Stmt::StmtKind epat::Stmt::str2StmtKind(const std::string& str)
{
    for (int i = 0; i != static_cast<int>(StmtKind::Undefined); ++i)
        if (StmtKindNameList[i] == str)
            return StmtKind(i);
    return StmtKind::Undefined;
}

void epat::Stmt::printAst(std::ostream& os, const std::string& prefix) const
{
    os << prefix << getStmtTypeName();
}

void epat::Stmt::printCode(std::ostream& os, int indent) const
{
    os << '$' << getStmtTypeName() << ";";
}

epat::Expr::Expr(StmtKind kind, QualType wt, ExprValueKind evk)
    : Stmt(kind), qt_(std::move(wt)), evk_(evk)
{
    // TODO: 校验？
}

epat::Expr::constant_value epat::Expr::getConstantValue() const
{
    return nullopt;
}

bool epat::Expr::isRightAssoc() const
{
    return false;
}

int epat::Expr::getOpPrec() const
{
    return 0;
}

epat::QualType epat::Expr::getType() const
{
    return qt_;
}

void epat::Expr::printAst(std::ostream& os, const std::string& prefix) const
{
    Stmt::printAst(os, prefix);
    os << " '" << qt_.getCode() << "'";
    if (isLValue())
        os << " lvalue";
}

epat::ArraySubscript::ArraySubscript(QualType wt, Expr::ptr base, Expr::ptr sub)
    : Expr(StmtKind::ArraySubscript, std::move(wt), ExprValueKind::LValue),
      base_(std::move(base)), sub_(std::move(sub))
{
}

int epat::ArraySubscript::getOpPrec() const
{
    return 1;
}

epat::ArraySubscript::ptr epat::ArraySubscript::create(Expr::ptr base, Expr::ptr sub)
{
    base = ImplicitCastExpr::decay(std::move(base));
    sub = ImplicitCastExpr::cast2RValue(std::move(sub));
    auto wt = base->getType()->getElement();
    return ptr(new ArraySubscript(wt, std::move(base), std::move(sub)));
}

void epat::ArraySubscript::printAst(std::ostream& os, const std::string& prefix) const
{
    Expr::printAst(os, prefix);
    print_tree(os, prefix, base_, sub_);
}

void epat::ArraySubscript::printCode(std::ostream& os, int indent) const
{
    print_expr(os, base_, this, -1);
    os << "[";
    sub_->printCode(os);
    os << "]";
}

epat::Expr::constant_value epat::ArraySubscript::getConstantValue() const
{
    return nullopt;
}

epat::BinaryOperator::BinaryOperator(QualType wt, ExprValueKind evk, Expr::ptr lhs,
                                     Expr::ptr rhs, Bop op)
    : Expr(StmtKind::BinaryOperator, std::move(wt), evk), lhs_(std::move(lhs)),
      rhs_(std::move(rhs)), op_(op)
{
}

epat::BinaryOperator::ptr epat::BinaryOperator::create(Expr::ptr lhs, Expr::ptr rhs,
                                                       Bop op)
{
    rhs = ImplicitCastExpr::cast2RValue(std::move(rhs));
    if (!isAssignOp(op))
        lhs = ImplicitCastExpr::cast2RValue(std::move(lhs));
    if (Bop::Asgn == op)
        rhs = ImplicitCastExpr::cast2Target(std::move(rhs), lhs->getType(),
                                            lhs->getExprValueKind());
    // TODO: 根据符号变化
    auto qt = lhs->getType();
    // C语言二元操作符只会返回右值
    auto evk = ExprValueKind::RValue;
    return ptr(new BinaryOperator(qt, evk, std::move(lhs), std::move(rhs), op));
}

epat::BinaryOperator::ptr epat::BinaryOperator::create(Expr::ptr lhs, Expr::ptr rhs,
                                                       const std::string& op)
{
    return create(std::move(lhs), std::move(rhs), str2Bop(op));
}

const char* epat::BinaryOperator::bop2Str(Bop op)
{
    return BopStringList[static_cast<int>(op)];
}

epat::BinaryOperator::Bop epat::BinaryOperator::str2Bop(const std::string& str)
{
    for (int i = 0; i != static_cast<int>(Bop::Undefined); ++i)
        if (BopStringList[i] == str)
            return Bop(i);
    return Bop::Undefined;
}

int epat::BinaryOperator::getBopPrecedence(Bop op)
{
    if (int i = static_cast<int>(op); 0 <= i && i <= static_cast<int>(Bop::Undefined))
        return BopPrecedenceList[i];
    return BopPrecedenceList[static_cast<int>(Bop::Undefined)];
}

bool epat::BinaryOperator::isAssignOp(Bop op)
{
    return Bop::Asgn <= op && op <= Bop::OrAsgn;
}

bool epat::BinaryOperator::isBitwiseOp(Bop op)
{
    return (Bop::And <= op && op <= Bop::Or) ||
           (Bop::ShlAsgn <= op && op <= Bop::OrAsgn) ||
           (Bop::Shl <= op && op <= Bop::Shr);
}

bool epat::BinaryOperator::isRelationalOp(Bop op)
{
    return Bop::Lt <= op && op <= Bop::Neq;
}

bool epat::BinaryOperator::isModuloOp(Bop op)
{
    return Bop::Mod == op || Bop::ModAsgn == op;
}

void epat::BinaryOperator::printAst(std::ostream& os, const std::string& prefix) const
{
    Expr::printAst(os, prefix);
    os << " " << bop2Str(op_);
    print_tree(os, prefix, lhs_, rhs_);
}

void epat::BinaryOperator::printCode(std::ostream& os, int indent) const
{
    print_expr(os, lhs_, this, -1);
    os << (Bop::Comma == op_ ? "" : " ") << bop2Str(op_) << " ";
    print_expr(os, rhs_, this, 1);
}

epat::Expr::constant_value epat::BinaryOperator::getConstantValue() const
{
    auto lhs = lhs_->getConstantValue(), rhs = rhs_->getConstantValue();
    if (!lhs.has_value() || !rhs.has_value())
        return nullopt;
    // TODO: 返回值类型和表达式类型对应
    auto op = op_;
    auto &lv = lhs.value(), &rv = rhs.value();
    if (isAssignOp(op))
        return nullopt;
    if (isBitwiseOp(op) || isModuloOp(op)) {
        // 需求整数
        if (holds_alternative<long long>(lv) && holds_alternative<long long>(rv)) {
            long long l = get<long long>(lv), r = get<long long>(rv);
            switch (op) {
            case Bop::Mod:
                return l % r;
            case Bop::Shl:
                return l << r;
            case Bop::Shr:
                return l >> r;
            case Bop::And:
                return l & r;
            case Bop::Xor:
                return l ^ r;
            case Bop::Or:
                return l | r;
            default:
                return nullopt;
            }
        }
        else
            return nullopt;
    }
    // 其余操作符，其中比较操作符要类型转换
    using visitor_ret_type = std::optional<std::variant<long long, double, bool>>;
    auto visitor = [=](auto&& lv, auto&& rv) -> visitor_ret_type {
        switch (op) {
#define MY_BOP(op_name, op)                                                              \
    case Bop::op_name:                                                                   \
        return lv op rv;
            MY_BOP(Add, +)
            MY_BOP(Sub, -)
            MY_BOP(Mul, *)
            MY_BOP(Div, /)
            MY_BOP(Lt, <)
            MY_BOP(LtEq, <=)
            MY_BOP(Gt, >)
            MY_BOP(GtEq, >=)
            MY_BOP(Eq, ==)
            MY_BOP(Neq, !=)
            MY_BOP(LAnd, &&)
            MY_BOP(LOr, ||)
#undef MY_BOP
        case Bop::Comma:
            return rv;
        default:
            cout << "debug:" << __LINE__ << ": "
                 << "undefined binary operator: " << static_cast<int>(op_) << endl;
            return nullopt;
        }
    };
    auto ret = std::visit(visitor, lhs.value(), rhs.value());
    if (!ret.has_value())
        return nullopt;
    auto& value = ret.value();
    if (holds_alternative<long long>(value))
        return get<long long>(value);
    if (holds_alternative<double>(value))
        return get<double>(value);
    if (holds_alternative<bool>(value))
        return (long long)get<bool>(value);
    return nullopt;
}

bool epat::BinaryOperator::isRightAssoc() const
{
    return isAssignOp(op_); // XXX: 或三目运算符
}

int epat::BinaryOperator::getOpPrec() const
{
    return getBopPrecedence(op_);
}

epat::BreakStmt::BreakStmt() : Stmt(StmtKind::BreakStmt) {}

epat::BreakStmt::ptr epat::BreakStmt::create()
{
    return ptr(new BreakStmt);
}

void epat::BreakStmt::printCode(std::ostream& os, int indent) const
{
    os << "break;";
}

epat::CallExpr::CallExpr(QualType wt, ExprValueKind evk, Expr::ptr callee,
                         Expr::list operands)
    : Expr(StmtKind::CallExpr, std::move(wt), evk), callee_(std::move(callee)),
      operands_(std::move(operands))
{
}

epat::CallExpr::ptr epat::CallExpr::create(Expr::ptr callee, Expr::list operands)
{
    for (auto& opd : operands)
        opd = ImplicitCastExpr::cast2RValue(std::move(opd));
    auto qt = callee->getType();
    if (qt.isFunction()) {
        callee = ImplicitCastExpr::decay(std::move(callee));
        auto ret = qt.getReturnType();
        return ptr(new CallExpr(std::move(ret), ExprValueKind::RValue, std::move(callee),
                                std::move(operands)));
    }
    else if (qt.isPointer() && qt.getElement().isFunction()) {
        // XXX: 检查参数合法性。
        auto ft = static_pointer_cast<FunctionType>(qt.getElement().get());
        auto ret = ft->getReturnType();
        return ptr(new CallExpr(std::move(ret), ExprValueKind::RValue, std::move(callee),
                                std::move(operands)));
    }
    cout << "debug:" << __LINE__
         << ": callee is not valid: " << (callee ? callee->getCode() : "$error") << endl;
    return {};
}

epat::CallExpr::ptr epat::CallExpr::create(FunctionDecl::ptr callee, Expr::list operands)
{
    auto wt = callee->getRetType();
    auto evk = ExprValueKind::RValue;
    // operands在下面转右值
    return CallExpr::create(ImplicitCastExpr::decay(DeclRefExpr::create(callee)),
                            std::move(operands));
}

void epat::CallExpr::printAst(std::ostream& os, const std::string& prefix) const
{
    Expr::printAst(os, prefix);
    print_tree(os, prefix, callee_, operands_);
}

void epat::CallExpr::printCode(std::ostream& os, int indent) const
{
    print_expr(os, callee_, this, -1);
    os << "(";
    for (size_t i = 0, n = operands_.size(); i != n; ++i) {
        if (i)
            os << ", ";
        if (const auto& opd = operands_[i])
            operands_[i]->printCode(os);
        else
            os << "$null";
    }
    os << ")";
}

int epat::CallExpr::getOpPrec() const
{
    return 1;
}

epat::CastExpr::CastExpr(StmtKind kind, Expr::ptr expr, QualType target_type,
                         ExprValueKind evk, CastKind ck)
    : Expr(kind, std::move(target_type), evk), sub_(std::move(expr)), ck_(ck)
{
}

epat::CastExpr::ptr epat::CastExpr::create(Expr::ptr expr, QualType target_type,
                                           ExprValueKind evk)
{
    // XXX: 先转换成右值是否有问题？
    expr = ImplicitCastExpr::cast2RValue(std::move(expr));
    return ptr(new CastExpr(StmtKind::CastExpr, std::move(expr), std::move(target_type),
                            evk, CastKind::CStyleCast));
}

void epat::CastExpr::printAst(std::ostream& os, const std::string& prefix) const
{
    // TODO: 打印CastKind
    Expr::printAst(os, prefix);
    os << " <" << ck_ << ">";
    print_tree(os, prefix, sub_);
}

void epat::CastExpr::printCode(std::ostream& os, int indent) const
{
    // XXX: 区分各种类型
    os << "(";
    getType().printCode(os);
    os << ")";
    print_expr(os, sub_, this, -1);
}

epat::Expr::constant_value epat::CastExpr::getConstantValue() const
{
    auto sub = sub_->getConstantValue();
    if (sub == std::nullopt)
        return std::nullopt;
    else {
        auto target = getType();
        if (target.isFpa())
            return std::visit([](auto&& arg) { return (double)arg; }, sub.value());
        else if (target.isBool())
            return std::visit([](auto&& arg) { return (long long)(bool)arg; },
                              sub.value());
        else
            return sub;
    }
}

bool epat::CastExpr::isRightAssoc() const
{
    return true;
}

int epat::CastExpr::getOpPrec() const
{
    return 2;
}

bool epat::CastExpr::isDecay() const
{
    return CastKind::ArrayToPointerDecay == ck_ ||
           CastKind::FunctionToPointerDecay == ck_;
}

const epat::Expr& epat::CastExpr::removeCast(const Expr& expr)
{
    auto ptr = &expr;
    while (auto cast = dynamic_cast<const CastExpr*>(ptr))
        ptr = cast->sub_.get();
    return *ptr;
}

// TODO: 修改parent
epat::CompoundStmt::CompoundStmt(Context::ref parent)
    : Stmt(StmtKind::CompoundStmt), Context(parent), stmts_()
{
}

epat::CompoundStmt::CompoundStmt() : Stmt(StmtKind::Root), Context(nullptr), stmts_() {}

epat::CompoundStmt::ptr epat::CompoundStmt::create(Context::ref parent)
{
    return ptr(new CompoundStmt(parent));
}

void epat::CompoundStmt::printAst(std::ostream& os, const std::string& prefix) const
{
    Stmt::printAst(os, prefix);
    print_tree(os, prefix, stmts_);
}

void epat::CompoundStmt::printCode(std::ostream& os, int indent) const
{
    os << "{" << endl;
    for (const auto& stmt : stmts_) {
        os << SPACES2;
        stmt->printCode(os, indent + 2);
        // expr需要加分号，其他语句自己决定是否加分号
        if (stmt->isExpr())
            os << ";";
        os << std::endl;
    }
    os << SPACES << "}";
}

void epat::CompoundStmt::pushStmt(Stmt::ptr stmt)
{
    if (stmt)
        stmts_.emplace_back(std::move(stmt));
    else {
        cout << "debug:" << __LINE__ << ": empty stmt" << endl;
        stmts_.push_back(StrLiteral::create("$empty"));
    }
}

bool epat::CompoundStmt::addDecl(Decl::ptr decl)
{
    if (Context::addDecl(decl)) {
        // 匿名结构体和枚举不需要声明语句
        // XXX: 当前不判断匿名的是什么
        if (!decl->getName().empty())
            pushStmt(DeclStmt::create(decl));
        return true;
    }
    return false;
}

epat::ContinueStmt::ContinueStmt() : Stmt(StmtKind::ContinueStmt) {}

epat::ContinueStmt::ptr epat::ContinueStmt::create()
{
    return ptr(new ContinueStmt);
}

void epat::ContinueStmt::printCode(std::ostream& os, int indent) const
{
    os << "continue;";
}

epat::DeclRefExpr::DeclRefExpr(ValueDecl::ptr decl)
    : Expr(StmtKind::DeclRefExpr, decl->getType(), ExprValueKind::LValue), decl_(decl)
{
}

int epat::DeclRefExpr::getOpPrec() const
{
    return 0;
}

// epat::QualType epat::DeclRefExpr::getType() const
// {
//     return decl_->getType();
// }

epat::DeclRefExpr::ptr epat::DeclRefExpr::create(ValueDecl::ptr decl)
{
    return ptr(new DeclRefExpr(std::move(decl)));
}

void epat::DeclRefExpr::printAst(std::ostream& os, const std::string& prefix) const
{
    Expr::printAst(os, prefix);
    os << " '" << decl_->getName() << "'";
    // print_tree(os, prefix, decl_);
}

void epat::DeclRefExpr::printCode(std::ostream& os, int indent) const
{
    os << decl_->getName();
}

epat::Expr::constant_value epat::DeclRefExpr::getConstantValue() const
{
    // TODO: 在指向enum时可能有常数值
    return nullopt;
}

epat::DeclStmt::DeclStmt(Decl::ptr decl)
    : Stmt(StmtKind::DeclStmt), decl_(std::move(decl))
{
}

epat::DeclStmt::ptr epat::DeclStmt::create(Decl::ptr decl)
{
    return ptr(new DeclStmt(std::move(decl)));
}

void epat::DeclStmt::printAst(std::ostream& os, const std::string& prefix) const
{
    Stmt::printAst(os, prefix);
    print_tree(os, prefix, decl_);
}

void epat::DeclStmt::printCode(std::ostream& os, int indent) const
{
    decl_->printCode(os, indent);
    // XXX: 是否可以更优雅
    if (auto fd = dynamic_cast<FunctionDecl*>(decl_.get())) {
        if (fd->isDefinition())
            return;
    }
    os << ";";
}

epat::ForStmt::ForStmt(Stmt::ptr init, Expr::ptr cond, Expr::ptr loop,
                       CompoundStmt::ptr body)
    : Stmt(StmtKind::ForStmt), init_(std::move(init)), cond_(std::move(cond)),
      loop_(std::move(loop)), body_(std::move(body))
{
    body_->setParent(this);
}

epat::ForStmt::ptr epat::ForStmt::create(Stmt::ptr init, Expr::ptr cond, Expr::ptr loop,
                                         CompoundStmt::ptr body)
{
    // TODO: 参数中的Stmt改为Expr
    if (!body)
        body = CompoundStmt::create({});
    return ptr(
        new ForStmt(std::move(init), std::move(cond), std::move(loop), std::move(body)));
}

void epat::ForStmt::printAst(std::ostream& os, const std::string& prefix) const
{
    Stmt::printAst(os, prefix);
    print_tree(os, prefix, init_, cond_, loop_, body_);
}

void epat::ForStmt::printCode(std::ostream& os, int indent) const
{
    os << "for (";
    if (init_)
        init_->printCode(os);
    if (init_->isExpr())
        os << ";";
    os << " ";
    if (cond_)
        cond_->printCode(os);
    os << "; ";
    if (loop_)
        loop_->printCode(os);
    os << ")" << std::endl;
    if (body_->isCompoundStmt())
        body_->printCode(os, indent);
    else
        body_->printCode(os, indent + 2);
}

epat::IfStmt::IfStmt(Expr::ptr cond, Stmt::ptr then, Stmt::ptr else_)
    : Stmt(StmtKind::IfStmt), cond_(std::move(cond)), then_(std::move(then)),
      else_(std::move(else_))
{
}

epat::IfStmt::ptr epat::IfStmt::create(Expr::ptr cond, Stmt::ptr then, Stmt::ptr _else)
{
    cond = ImplicitCastExpr::cast2RValue(std::move(cond));
    return ptr(new IfStmt(std::move(cond), std::move(then), std::move(_else)));
}

void epat::IfStmt::printAst(std::ostream& os, const std::string& prefix) const
{
    Stmt::printAst(os, prefix);
    print_tree(os, prefix, cond_, then_, else_);
}

void epat::IfStmt::printCode(std::ostream& os, int indent) const
{
    os << "if (";
    cond_->printCode(os);
    os << ") ";
    if (then_->isCompoundStmt())
        then_->printCode(os, indent);
    else {
        os << endl << SPACES2;
        then_->printCode(os, indent + 2);
    }
    if (!else_)
        return;
    os << std::endl << SPACES << "else";
    if (else_->isCompoundStmt() || else_->isIfStmt()) {
        os << " ";
        else_->printCode(os, indent);
    }
    else {
        os << endl << SPACES2;
        else_->printCode(os, indent + 2);
    }
}

epat::ImplicitCastExpr::ImplicitCastExpr(Expr::ptr expr, QualType target_type,
                                         ExprValueKind evk, CastKind ck)
    : CastExpr(StmtKind::ImplicitCastExpr, std::move(expr), target_type, evk, ck)
{
}

epat::ImplicitCastExpr::ptr epat::ImplicitCastExpr::create(Expr::ptr expr,
                                                           QualType target_type,
                                                           ExprValueKind evk, CastKind ck)
{
    return ptr(new ImplicitCastExpr(std::move(expr), std::move(target_type), evk, ck));
}

epat::Expr::ptr epat::ImplicitCastExpr::decay(Expr::ptr raw)
{
    // only support function and array
    auto qt = raw->getType();
    if (qt.isArray())
        return create(std::move(raw), qt.decay(), ExprValueKind::RValue,
                      CastKind::ArrayToPointerDecay);
    else if (qt.isFunction())
        return create(std::move(raw), qt.decay(), ExprValueKind::RValue,
                      CastKind::FunctionToPointerDecay);
    else
        return ImplicitCastExpr::cast2RValue(std::move(raw));
}

epat::Expr::ptr epat::ImplicitCastExpr::cast2RValue(Expr::ptr raw)
{
    if (!raw)
        return std::move(raw);
    if (raw->isRValue())
        return std::move(raw);
    return create(std::move(raw), raw->getType(), ExprValueKind::RValue,
                  CastKind::LValueToRValue);
}

epat::Expr::ptr epat::ImplicitCastExpr::cast2Target(Expr::ptr raw, QualType target,
                                                    ExprValueKind evk)
{
    if (!raw)
        return std::move(raw);
    if (target.isPointer() || target.isInteger())
        raw = ImplicitCastExpr::decay(std::move(raw));
    // XXX: ptr to int
    raw = ImplicitCastExpr::bitcast(std::move(raw), target);
    if (ExprValueKind::RValue == evk)
        raw = ImplicitCastExpr::cast2RValue(std::move(raw));
    return raw;
}

epat::Expr::ptr epat::ImplicitCastExpr::bitcast(Expr::ptr raw, QualType target)
{
    if (target.isPointer() && raw->getType() != target) {
        auto is_void_ptr = [&]() {
            return raw->getType() == PointerType::create(BaseType::getVoid());
        }();
        auto is_null = [&]() {
            return raw->getKind() == StmtKind::IntLiteral &&
                   static_cast<IntLiteral&>(*raw).getValue() == 0;
        }();
        if (is_void_ptr || is_null) {
            raw = ImplicitCastExpr::cast2RValue(std::move(raw));
            return ImplicitCastExpr::create(std::move(raw), target, ExprValueKind::RValue,
                                            CastKind::BitCast);
        }
    }
    // 不用报错
    return raw;
}

void epat::ImplicitCastExpr::printCode(std::ostream& os, int indent) const
{
    print_expr(os, sub_, nullptr, 1);
}

bool epat::ImplicitCastExpr::isRightAssoc() const
{
    return getSubExpr().isRightAssoc();
}

int epat::ImplicitCastExpr::getOpPrec() const
{
    return getSubExpr().getOpPrec();
}

epat::InitListExpr::InitListExpr(QualType qt, Expr::list init_list)
    : Expr(StmtKind::InitListExpr, std::move(qt), ExprValueKind::RValue),
      init_list_(std::move(init_list))
{
}

epat::InitListExpr::ptr epat::InitListExpr::create(Expr::list init_list, QualType qt)
{
    for (auto& init : init_list)
        init = ImplicitCastExpr::cast2RValue(std::move(init));
    // TODO: 数组以外的类型
    if (!qt) {
        if (auto size = init_list.size())
            qt = ArrayType::create(init_list[0]->getType(), (int)size);
        else {
            qt = BaseType::getVoid();
        }
    }
    return ptr(new InitListExpr(std::move(qt), std::move(init_list)));
}

void epat::InitListExpr::printAst(std::ostream& os, const std::string& prefix) const
{
    Expr::printAst(os, prefix);
    print_tree(os, prefix, init_list_);
}

void epat::InitListExpr::printCode(std::ostream& os, int indent) const
{
    os << "{";
    for (size_t i = 0; i < init_list_.size(); i++) {
        if (i)
            os << ", ";
        init_list_[i]->printCode(os);
    }
    os << "}";
}

std::string epat::MemberExpr::getSuffix() const
{
    string res = is_arrow_ ? string("->") : ".";
    return res + member_->getName();
}

epat::MemberExpr::MemberExpr(Expr::ptr base, FieldDecl::ptr member, bool is_arrow)
    : Expr(StmtKind::MemberExpr, member->getType(), ExprValueKind::LValue),
      base_(std::move(base)), member_(std::move(member)), is_arrow_(is_arrow)
{
}

int epat::MemberExpr::getOpPrec() const
{
    return 1;
}

epat::MemberExpr::ptr epat::MemberExpr::create(Expr::ptr base, FieldDecl::ptr member,
                                               bool is_arrow)
{
    if (is_arrow)
        base = ImplicitCastExpr::cast2RValue(std::move(base));
    return ptr(new MemberExpr(std::move(base), std::move(member), is_arrow));
}

epat::MemberExpr::ptr epat::MemberExpr::create(Expr::ptr base, std::string member,
                                               bool is_arrow)
{
    if (!base) {
        cout << "error: MemberExpr::create get null base!" << endl;
        return {};
    }
    auto qt = base->getType();
    if (is_arrow) {
        if (auto pt = qt.get<PointerType>())
            qt = pt->getElement();
        else {
            cout << "error: base not a pointer type!" << endl;
            return {};
        }
    }
    auto st = qt.get<StructType>();
    if (!st) {
        cout << "error: base not a struct type!" << endl;
        return {};
    }
    return create(std::move(base), st->getStructDecl().getField(member), is_arrow);
}

void epat::MemberExpr::printAst(std::ostream& os, const std::string& prefix) const
{
    Stmt::printAst(os, prefix);
    os << " " << getSuffix();
    print_tree(os, prefix, base_);
}

void epat::MemberExpr::printCode(std::ostream& os, int indent) const
{
    print_expr(os, base_, this, -1);
    os << getSuffix();
}

epat::NullStmt::NullStmt() : Stmt(StmtKind::NullStmt) {}

epat::NullStmt::ptr epat::NullStmt::create()
{
    return ptr(new NullStmt());
}

void epat::NullStmt::printAst(std::ostream& os, const std::string& prefix) const
{
    Stmt::printAst(os, prefix);
}

void epat::NullStmt::printCode(std::ostream& os, int indent) const
{
    os << ";";
}

epat::ReturnStmt::ReturnStmt(Expr::ptr ret)
    : Stmt(StmtKind::ReturnStmt), ret_(std::move(ret))
{
}

epat::ReturnStmt::ptr epat::ReturnStmt::create(Expr::ptr ret)
{
    ret = ImplicitCastExpr::cast2RValue(std::move(ret));
    return ptr(new ReturnStmt(std::move(ret)));
}

void epat::ReturnStmt::printAst(std::ostream& os, const std::string& prefix) const
{
    Stmt::printAst(os, prefix);
    print_tree(os, prefix, ret_);
}

void epat::ReturnStmt::printCode(std::ostream& os, int indent) const
{
    os << "return";
    if (ret_) {
        os << " ";
        ret_->printCode(os, indent);
    }
    os << ";";
}

epat::Root::Root() : CompoundStmt() {}

epat::Root::ptr epat::Root::create()
{
    auto root = ptr(new Root());
    // 会自动生成隐式声明
    // auto int_type = BaseType::getInt();
    // auto void_type = BaseType::getVoid();
    // auto void_ptr = PointerType::create(BaseType::getVoid());
    // *root << FunctionDecl::create("malloc", void_ptr, {int_type})
    //       << FunctionDecl::create("free", void_type, {void_ptr})
    //       << FunctionDecl::create("memcpy", void_ptr, {void_ptr, void_ptr, int_type})
    //       << FunctionDecl::create("memset", void_ptr, {void_ptr, int_type, int_type});
    return root;
}

epat::Root::ptr epat::Root::fromStream(std::istream& is)
{
    Reader reader(is);
    return reader.getRoot();
}

epat::Root::ptr epat::Root::fromString(const std::string& input)
{
    Reader reader(input);
    return reader.getRoot();
}

epat::SignStmt::SignStmt(Expr::ptr cond)
    : Stmt(StmtKind::SignStmt), cond_(std::move(cond))
{
}

epat::SignStmt::ptr epat::SignStmt::create(Expr::ptr cond)
{
    cond = ImplicitCastExpr::cast2RValue(std::move(cond));
    return ptr(new SignStmt(std::move(cond)));
}

void epat::SignStmt::printAst(std::ostream& os, const std::string& prefix) const
{
    Stmt::printAst(os, prefix);
    print_tree(os, prefix, cond_);
}

void epat::SignStmt::printCode(std::ostream& os, int indent) const
{
    os << "@ ";
    cond_->printCode(os);
    os << ";";
}

epat::SizeofExpr::SizeofExpr(QualType type)
    : Expr(StmtKind::SizeofExpr, BaseType::getInt()), sub_(std::move(type))
{
    // XXX: 类型为uint64_t
}

epat::SizeofExpr::SizeofExpr(Expr::ptr expr) // XXX: 临时处理。expr会在此处析构
    : Expr(StmtKind::SizeofExpr, BaseType::getInt()), sub_(std::move(expr->getType()))
{
    // XXX: 类型为uint64_t
}

epat::SizeofExpr::ptr epat::SizeofExpr::create(QualType type)
{
    return ptr(new SizeofExpr(std::move(type)));
}

epat::SizeofExpr::ptr epat::SizeofExpr::create(Expr::ptr expr)
{
    return ptr(new SizeofExpr(std::move(expr)));
}

void epat::SizeofExpr::printAst(std::ostream& os, const std::string& prefix) const
{
    Expr::printAst(os, prefix);
    // print_tree(os, prefix, sub_);
}

void epat::SizeofExpr::printCode(std::ostream& os, int indent) const
{
    os << "sizeof(";
    sub_.printCode(os);
    os << ")";
}

epat::UnaryOperator::UnaryOperator(QualType wt, ExprValueKind evk, Expr::ptr expr, Uop op)
    : Expr(StmtKind::UnaryOperator, std::move(wt), evk), expr_(std::move(expr)), op_(op)
{
}

bool epat::UnaryOperator::isRightAssoc() const
{
    switch (op_) {
    case Uop::PreInc:
    case Uop::PreDec:
    case Uop::Not:
    case Uop::Compl:
    case Uop::UPlus:
    case Uop::UNeg:
    case Uop::Deref:
    case Uop::AddrOf:
        return true;
    default:
        return false;
    }
}

int epat::UnaryOperator::getOpPrec() const
{
    return getUopPrecedence(op_);
}

bool epat::UnaryOperator::isAssignOp(Uop op)
{
    return op == Uop::PreInc || op == Uop::PreDec || op == Uop::PostInc ||
           op == Uop::PostDec;
}

bool epat::UnaryOperator::isPointerOp(Uop op)
{
    return Uop::Deref == op || Uop::AddrOf == op;
}

epat::Expr::constant_value epat::UnaryOperator::getConstantValue() const
{
    auto expr = expr_->getConstantValue();
    if (!expr.has_value())
        return nullopt;
    auto op = op_;
    if (isAssignOp(op) || isPointerOp(op))
        return nullopt;
    if (Uop::Compl == op) {
        // 需求整数
        if (holds_alternative<long long>(*expr))
            return ~get<long long>(*expr);
        else
            return nullopt;
    }
    // 其余操作符，其中比较操作符要类型转换
    using visitor_ret_type = std::optional<std::variant<long long, double, bool>>;
    auto visitor = [=](auto&& v) -> visitor_ret_type {
        switch (op) {
#define MY_UOP(op_name, op)                                                              \
    case Uop::op_name:                                                                   \
        return op v;
            MY_UOP(Not, !)
            MY_UOP(UPlus, +)
            MY_UOP(UNeg, -)
#undef MY_BOP
        default:
            cout << "debug:" << __LINE__ << ": "
                 << "undefined unary operator: " << static_cast<int>(op_) << endl;
            return nullopt;
        }
    };
    auto ret = std::visit(visitor, expr.value());
    if (!ret.has_value())
        return nullopt;
    auto& value = ret.value();
    if (holds_alternative<long long>(value))
        return get<long long>(value);
    if (holds_alternative<double>(value))
        return get<double>(value);
    if (holds_alternative<bool>(value))
        return (long long)get<bool>(value);
    return nullopt;
}

epat::UnaryOperator::ptr epat::UnaryOperator::create(Expr::ptr expr, Uop op)
{
    // c的前自增也是右值
    ExprValueKind evk = Uop::Deref == op ? ExprValueKind::LValue : ExprValueKind::RValue;
    if (Uop::AddrOf != op)
        expr = ImplicitCastExpr::cast2RValue(std::move(expr));
    // TODO: 确定类型
    auto qt = expr->getType();
    return ptr(new UnaryOperator(qt, evk, std::move(expr), op));
}

epat::UnaryOperator::ptr epat::UnaryOperator::create(Expr::ptr expr,
                                                     const std::string& op, bool postfix)
{
    return UnaryOperator::create(std::move(expr), str2Uop(op, postfix));
}

const char* epat::UnaryOperator::uop2Str(Uop op)
{
    return UopStringList[static_cast<int>(op)];
}

epat::UnaryOperator::Uop epat::UnaryOperator::str2Uop(const std::string& str,
                                                      bool postfix)
{
    Uop uop = Uop::Undefined;
    if ("++" == str)
        uop = postfix ? Uop::PostInc : Uop::PreInc;
    else if ("--" == str)
        uop = postfix ? Uop::PostDec : Uop::PreDec;
    else {
        for (int i = 0; i != static_cast<int>(Uop::Undefined); ++i)
            if (UopStringList[i] == str)
                return Uop(i);
    }
    return uop;
}

int epat::UnaryOperator::getUopPrecedence(Uop op)
{
    if (int i = static_cast<int>(op); 0 <= i && i <= static_cast<int>(Uop::Undefined))
        return UopPrecedenceList[i];
    return UopPrecedenceList[static_cast<int>(Uop::Undefined)];
}

void epat::UnaryOperator::printAst(std::ostream& os, const std::string& prefix) const
{
    Expr::printAst(os, prefix);
    os << " \'" << uop2Str(op_) << "\'";
    print_tree(os, prefix, expr_);
}

void epat::UnaryOperator::printCode(std::ostream& os, int indent) const
{
    bool left = op_ == Uop::PostInc || op_ == Uop::PostDec;
    if (!left)
        os << op_;
    print_expr(os, expr_, this, left ? -1 : 1);
    if (left)
        os << op_;
}

epat::WhileStmt::WhileStmt(Expr::ptr cond, Stmt::ptr body)
    : Stmt(StmtKind::WhileStmt), cond_(std::move(cond)), body_(std::move(body))
{
}

epat::WhileStmt::ptr epat::WhileStmt::create(Expr::ptr cond, Stmt::ptr body)
{
    if (!cond) {
        cout << "warning: WhileStmt must have a condition." << endl;
        cond = IntLiteral::create(0);
    }
    if (!body) {
        cout << "warning: WhileStmt must have a body." << endl;
        body = CompoundStmt::create(nullptr);
    }
    cond = ImplicitCastExpr::cast2RValue(std::move(cond));
    return ptr(new WhileStmt(std::move(cond), std::move(body)));
}

void epat::WhileStmt::printAst(std::ostream& os, const std::string& prefix) const
{
    Stmt::printAst(os, prefix);
    print_tree(os, prefix, cond_, body_);
}

void epat::WhileStmt::printCode(std::ostream& os, int indent) const
{
    os << "while (";
    cond_->printCode(os);
    os << ")";
    if (body_->isCompoundStmt()) {
        os << " ";
        body_->printCode(os, indent);
    }
    else {
        os << endl << SPACES2;
        body_->printCode(os, indent + 2);
    }
}
