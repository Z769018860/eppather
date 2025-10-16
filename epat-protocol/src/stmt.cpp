#include "stmt.h"
#include "decl.h"
#include <ostream>
#include <sstream>
#include <string>

using namespace std;

using constant_value = epat::Expr::constant_value;

std::string add_parentheses(std::string raw, bool need = true)
{
    if (need) return "(" + move(raw) + ")";
    return move(raw);
}

epat::Stmt::Stmt(StmtKind kind) : Node(), kind_(kind)
{
}

const char* epat::Stmt::stmtKind2Str(StmtKind sk)
{
    return StmtKindNameList[static_cast<int>(sk)];
}

epat::Stmt::StmtKind epat::Stmt::str2StmtKind(std::string& str)
{
    for (int i = 0; i != static_cast<int>(StmtKind::Undefined); ++i)
        if (StmtKindNameList[i] == str) return StmtKind(i);
    return StmtKind::Undefined;
}

std::string epat::Stmt::getAstString(std::string prefix) const
{
    return prefix + getStmtTypeName();
}

std::string epat::Stmt::getCode(int indent) const
{
    return string(indent, ' ') + '$' + getStmtTypeName();
}

epat::Expr::Expr(StmtKind kind, QualType wt, ExprValueKind evk)
    : Stmt(kind), qt_(move(wt)), evk_(evk)
{
    // TODO: 校验？
}

constant_value epat::Expr::getConstantValue() const
{
    return {0, false};
}

int epat::Expr::getOperatorPrecedence() const
{
    return 0;
}

epat::QualType epat::Expr::getType() const
{
    return qt_;
}

std::string epat::Expr::getAstString(std::string prefix) const
{
    ostringstream oss;
    oss << Stmt::getAstString(prefix) << " '" << qt_.getCode() << "'";
    if (ExprValueKind::LValue == evk_) oss << " lvalue";
    return oss.str();
}

epat::ArraySubscript::ArraySubscript(QualType wt, Expr::ptr base, Expr::ptr sub)
    : Expr(StmtKind::ArraySubscript, move(wt), ExprValueKind::LValue), base_(move(base)),
      sub_(move(sub))
{
}

int epat::ArraySubscript::getOperatorPrecedence() const
{
    return 1;
}

epat::ArraySubscript::ptr epat::ArraySubscript::create(Expr::ptr base, Expr::ptr sub)
{
    auto wt = base->getType()->getElement();
    return ptr(new ArraySubscript(wt, move(base), move(sub)));
}

std::string epat::ArraySubscript::getAstString(std::string prefix) const
{
    return buildAstString({base_.get(), sub_.get()}, Expr::getAstString(), prefix);
    return std::string();
}

std::string epat::ArraySubscript::getCode(int indent) const
{
    bool need_paren = base_->getOperatorPrecedence() > getOperatorPrecedence();
    return std::string(indent, ' ') + add_parentheses(base_->getCode(), need_paren) +
           "[" + sub_->getCode() + "]";
}

constant_value epat::ArraySubscript::getConstantValue() const
{
    return {0, false};
}

epat::BinaryOperator::BinaryOperator(
    QualType wt, ExprValueKind evk, Expr::ptr lhs, Expr::ptr rhs, Bop op
)
    : Expr(StmtKind::BinaryOperator, move(wt), evk), lhs_(move(lhs)), rhs_(move(rhs)),
      op_(op)
{
}

int epat::BinaryOperator::getOperatorPrecedence() const
{
    return getBopPrecedence(op_);
}

epat::BinaryOperator::ptr epat::BinaryOperator::create(
    Expr::ptr lhs, Expr::ptr rhs, Bop op
)
{
    // TODO: 根据符号变化
    auto wt = lhs->getType();
    // C语言二元操作符只会返回右值
    auto evk = ExprValueKind::RValue;
    return ptr(new BinaryOperator(wt, evk, move(lhs), move(rhs), op));
}

epat::BinaryOperator::ptr epat::BinaryOperator::create(
    Expr::ptr lhs, Expr::ptr rhs, const std::string& op
)
{
    return create(move(lhs), move(rhs), str2Bop(op));
}

const char* epat::BinaryOperator::bop2Str(Bop op)
{
    return BopStringList[static_cast<int>(op)];
}

epat::BinaryOperator::Bop epat::BinaryOperator::str2Bop(const std::string& str)
{
    for (int i = 0; i != static_cast<int>(Bop::Undefined); ++i)
        if (BopStringList[i] == str) return Bop(i);
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
    switch (op) {
    case Bop::Asgn:
    case Bop::AddAsgn:
    case Bop::SubAsgn:
    case Bop::MulAsgn:
    case Bop::DivAsgn:
    case Bop::ModAsgn:
    case Bop::ShlAsgn:
    case Bop::ShrAsgn:
    case Bop::AndAsgn:
    case Bop::XorAsgn:
    case Bop::OrAsgn:
        return true;
    default:
        return false;
    }
}

std::string epat::BinaryOperator::getAstString(std::string prefix) const
{
    auto self = Expr::getAstString() + " \'" + bop2Str(op_) + "\'";
    return buildAstString({lhs_.get(), rhs_.get()}, move(self), move(prefix));
}

std::string epat::BinaryOperator::getCode(int indent) const
{
    // 赋值系右结合，其余左结合
    bool lhs_need_paren, rhs_need_paren;
    int lhs_precedence = lhs_->getOperatorPrecedence(),
        rhs_precedence = rhs_->getOperatorPrecedence(),
        op_precedence = getOperatorPrecedence();
    if (isAssignOp(op_)) {
        lhs_need_paren = lhs_precedence >= op_precedence;
        rhs_need_paren = rhs_precedence > op_precedence;
    }
    else {
        lhs_need_paren = lhs_precedence > op_precedence;
        rhs_need_paren = rhs_precedence >= op_precedence;
    }
    return std::string(indent, ' ') + add_parentheses(lhs_->getCode(), lhs_need_paren) +
           " " + bop2Str(op_) + (op_ == Bop::Comma ? "" : " ") +
           add_parentheses(rhs_->getCode(), rhs_need_paren);
}

constant_value epat::BinaryOperator::getConstantValue() const
{
    if (isAssignOp(op_)) return {0, false};
    auto lhs = lhs_->getConstantValue(), rhs = rhs_->getConstantValue();
    if (!lhs.is_const || !rhs.is_const) return {0, false};
    auto lv = lhs.value, rv = rhs.value;
#define MY_BOP(op_name, op)                                                              \
    case Bop::op_name:                                                                   \
        return {(lv op rv), true};
    switch (op_) {
        MY_BOP(Add, +)
        MY_BOP(Sub, -)
        MY_BOP(Mul, *)
        MY_BOP(Div, /)
        MY_BOP(Mod, %)
        MY_BOP(Shl, <<)
        MY_BOP(Shr, >>)
        MY_BOP(Lt, <)
        MY_BOP(LtEq, <=)
        MY_BOP(Gt, >)
        MY_BOP(GtEq, >=)
        MY_BOP(Eq, ==)
        MY_BOP(Neq, !=)
        MY_BOP(And, &)
        MY_BOP(Xor, ^)
        MY_BOP(Or, |)
        MY_BOP(LAnd, &&)
        MY_BOP(LOr, ||)
#undef MY_BOP
    case Bop::Comma:
        return {rv, true};
    default:
        cout << "debug:" << __LINE__ << ": "
             << "undefined binary operator: " << static_cast<int>(op_) << endl;
        return {0, false};
    }
}

epat::BreakStmt::BreakStmt() : Stmt(StmtKind::BreakStmt)
{
}

epat::BreakStmt::ptr epat::BreakStmt::create()
{
    return ptr(new BreakStmt);
}

//std::string ast::BreakStmt::getAstString(std::string prefix) const
//{
//     return ;
//}

std::string epat::BreakStmt::getCode(int indent) const
{
    return std::string(indent, ' ') + "break";
}

epat::CallExpr::CallExpr(
    QualType wt, ExprValueKind evk, Expr::ptr callee, Expr::list operands
)
    : Expr(StmtKind::CallExpr, move(wt), evk), callee_(move(callee)),
      operands_(move(operands))
{
}

int epat::CallExpr::getOperatorPrecedence() const
{
    return 1;
}

epat::CallExpr::ptr epat::CallExpr::create(FunctionDecl::ptr callee, Expr::list operands)
{
    // TODO: C语言中，对被调用函数的引用会被隐式转换为弱化指针
    auto wt = callee->getRetType();
    auto evk = ExprValueKind::RValue;
    return CallExpr::create(
        ImplicitCastExpr::decay(DeclRefExpr::create(callee)), move(operands)
    );
}

epat::CallExpr::ptr epat::CallExpr::create(Expr::ptr callee, Expr::list operands)
{
    auto qt = callee->getType();
    if (qt.isPointer() && qt.getElement().isFunction()) {
        // TODO: 检查参数合法性
        return ptr(new CallExpr(qt, ExprValueKind::RValue, move(callee), move(operands)));
    }
    cout << "debug:" << __LINE__
         << ": callee is not valid: " << (callee ? callee->getCode() : "$error") << endl;
    return {};
}

std::string epat::CallExpr::getAstString(std::string prefix) const
{
    Node::list children;
    children.emplace_back(callee_.get());
    for (const auto& opd : operands_)
        children.emplace_back(opd.get());
    return buildAstString(move(children), Expr::getAstString(), move(prefix));
}

std::string epat::CallExpr::getCode(int indent) const
{
    ostringstream oss;
    // bool need_pran = callee_->getOperatorPrecedence() > getOperatorPrecedence();
    // oss << add_parentheses(callee_->getCode(indent), need_paran);
    oss << callee_->getCode(indent) << "(";
    for (int i = 0, n = (int)operands_.size(); i != n; ++i) {
        if (i) oss << ", ";
        oss << operands_[i]->getCode();
    }
    oss << ")";
    return oss.str();
}

epat::CastExpr::CastExpr(Expr::ptr expr, QualType target_type, ExprValueKind evk)
    : Expr(StmtKind::CastExpr, move(target_type), evk), sub_(move(expr)),
      target_type_(move(target_type))
{
}

int epat::CastExpr::getOperatorPrecedence() const
{
    return 2;
}

epat::CastExpr::ptr epat::CastExpr::create(
    Expr::ptr expr, QualType target_type, ExprValueKind evk
)
{
    return ptr(new CastExpr(move(expr), move(target_type), evk));
}

std::string epat::CastExpr::getAstString(std::string prefix) const
{
    return buildAstString({sub_.get()}, Expr::getAstString(), move(prefix));
}

std::string epat::CastExpr::getCode(int indent) const
{
    bool need_paren = sub_->getOperatorPrecedence() > getOperatorPrecedence();
    return string(indent, ' ') + add_parentheses(target_type_->getCode(), true) +
           add_parentheses(sub_->getCode(), need_paren);
}

constant_value epat::CastExpr::getConstantValue() const
{
    return sub_->getConstantValue();
}

// TODO: 修改parent
epat::CompoundStmt::CompoundStmt(/*Stmt::list stmts, */ Context::ref parent)
    : Stmt(StmtKind::CompoundStmt), Context(parent), stmts_()
{
}

epat::CompoundStmt::ptr epat::CompoundStmt::create(
    /*Stmt::list stmts, */ Context::ref parent
)
{
    return ptr(new CompoundStmt(/*move(stmts), */ parent));
}

std::string epat::CompoundStmt::getAstString(std::string prefix) const
{
    Node::list children;
    for (const auto& c : stmts_)
        children.emplace_back(c.get());
    return buildAstString(move(children), Stmt::getAstString(), move(prefix));
}

std::string epat::CompoundStmt::getCode(int indent) const
{
    ostringstream oss;
    oss << string(indent, ' ') << "{" << endl;
    for (const auto& stmt : stmts_) {
        oss << stmt->getCode(indent + 2);
        // TODO: if等语句后有多余的分号
        oss << ";";
        oss << endl;
    }
    oss << string(indent, ' ') << "}" /* << endl*/;
    return oss.str();
}

void epat::CompoundStmt::pushStmt(Stmt::ptr stmt)
{
    if (stmt)
        stmts_.emplace_back(move(stmt));
    else {
        cout << "debug:" << __LINE__ << ": empty stmt" << endl;
        stmts_.push_back(StrLiteral::create("$empty"));
    }
}

bool epat::CompoundStmt::addDecl(Decl::ptr decl)
{
    if (Context::addDecl(decl)) {
        // 生成一个DeclStmt
        pushStmt(DeclStmt::create(decl));
        return true;
    }
    return false;
}

epat::ContinueStmt::ContinueStmt() : Stmt(StmtKind::ContinueStmt)
{
}

epat::ContinueStmt::ptr epat::ContinueStmt::create()
{
    return ptr(new ContinueStmt);
}

std::string epat::ContinueStmt::getCode(int indent) const
{
    return std::string(indent, ' ') + "continue";
}

epat::DeclRefExpr::DeclRefExpr(ValueDecl::ptr decl)
    : Expr(StmtKind::DeclRefExpr, decl->getType(), ExprValueKind::LValue), decl_(decl)
{
}

int epat::DeclRefExpr::getOperatorPrecedence() const
{
    return 0;
}

epat::QualType epat::DeclRefExpr::getType() const
{
    return decl_->getType();
}

epat::DeclRefExpr::ptr epat::DeclRefExpr::create(ValueDecl::ptr decl)
{
    return ptr(new DeclRefExpr(move(decl)));
}

std::string epat::DeclRefExpr::getAstString(std::string prefix) const
{
    // TODO: 打印更细节
    // DeclRefExpr 0x1f6e900 <col:6> 'double' lvalue Var 0x1f6e860 'a' 'double'
    return buildAstString(
        {/*decl_.get()*/}, Expr::getAstString() + " '" + decl_->getName() + "'",
        move(prefix)
    );
}

std::string epat::DeclRefExpr::getCode(int indent) const
{
    return string(indent, ' ') + decl_->getName();
}

constant_value epat::DeclRefExpr::getConstantValue() const
{
    // TODO: 仅在指向enum时
    return {0, false};
}

epat::DeclStmt::DeclStmt(Decl::ptr decl) : Stmt(StmtKind::DeclStmt), decl_(move(decl))
{
}

epat::DeclStmt::ptr epat::DeclStmt::create(Decl::ptr decl)
{
    return ptr(new DeclStmt(move(decl)));
}

std::string epat::DeclStmt::getAstString(std::string prefix) const
{
    Node::list children;
    children.emplace_back(decl_.get());
    return buildAstString(children, Stmt::getAstString(), move(prefix));
}

std::string epat::DeclStmt::getCode(int indent) const
{
    if (decl_) return decl_->getCode(indent);
    return Stmt::getCode(indent);
}

epat::ForStmt::ForStmt(
    Stmt::ptr init, Stmt::ptr cond, Stmt::ptr loop, CompoundStmt::ptr body
)
    : Stmt(StmtKind::ForStmt), init_(move(init)), cond_(move(cond)), loop_(move(loop)),
      body_(move(body))
{
    body_->setParent(this);
}

epat::ForStmt::ptr epat::ForStmt::create(
    Stmt::ptr init, Stmt::ptr cond, Stmt::ptr loop, CompoundStmt::ptr body
)
{
    if (!body) body = CompoundStmt::create({});
    return ptr(new ForStmt(move(init), move(cond), move(loop), move(body)));
}

std::string epat::ForStmt::getAstString(std::string prefix) const
{
    return buildAstString(
        {init_.get(), cond_.get(), loop_.get(), body_.get()}, Stmt::getAstString(),
        move(prefix)
    );
}

std::string epat::ForStmt::getCode(int indent) const
{
    ostringstream oss;
    oss << string(indent, ' ') << "for (" << (init_ ? init_->getCode() : "") << ";"
        << (cond_ ? " " + cond_->getCode() : "") << ";"
        << (loop_ ? " " + loop_->getCode() : "") << ")" << endl
        << body_->getCode(indent);
    return oss.str();
}

epat::IfStmt::IfStmt(Expr::ptr cond, Stmt::ptr then, Stmt::ptr else_)
    : Stmt(StmtKind::IfStmt), cond_(move(cond)), then_(move(then)), else_(move(else_))
{
}

epat::IfStmt::ptr epat::IfStmt::create(Expr::ptr cond, Stmt::ptr then, Stmt::ptr _else)
{
    return ptr(new IfStmt(move(cond), move(then), move(_else)));
}

std::string epat::IfStmt::getAstString(std::string prefix) const
{
    return buildAstString(
        {cond_.get(), then_.get(), else_.get()}, Stmt::getAstString(), move(prefix)
    );
}

std::string epat::IfStmt::getCode(int indent) const
{
    ostringstream oss;
    oss << string(indent, ' ') << "if (" << (cond_ ? cond_->getCode() : "") << ")" << endl
        << then_->getCode(indent);
    if (else_) {
        oss << endl << "else" << endl;
        oss << else_->getCode(indent);
    }
    return oss.str();
}

epat::ImplicitCastExpr::ImplicitCastExpr(
    Expr::ptr expr, QualType target_type, ExprValueKind evk, CastKind ck
)
    : CastExpr(move(expr), target_type, evk), ck_(ck)
{
}

epat::ImplicitCastExpr::ptr epat::ImplicitCastExpr::create(
    Expr::ptr expr, QualType target_type, ExprValueKind evk, CastKind ck
)
{
    return ptr(new ImplicitCastExpr(move(expr), move(target_type), evk, ck));
}

epat::Expr::ptr epat::ImplicitCastExpr::decay(Expr::ptr raw)
{
    // only support function and array
    auto qt = raw->getType();
    if (qt.isArray())
        return create(
            move(raw), qt.decay(), ExprValueKind::RValue, CastKind::ArrayToPointerDecay
        );
    else if (qt.isFunction())
        return create(
            move(raw), qt.decay(), ExprValueKind::RValue, CastKind::FunctionToPointerDecay
        );
    else
        return move(raw);
}

std::string epat::ImplicitCastExpr::getCode(int indent) const
{
    return getSubExpr().getCode(indent);
}

int epat::ImplicitCastExpr::getOperatorPrecedence() const
{
    return getSubExpr().getOperatorPrecedence();
}

epat::InitListExpr::InitListExpr(QualType qt, Expr::list init_list)
    : Expr(StmtKind::InitListExpr, move(qt), ExprValueKind::RValue),
      init_list_(std::move(init_list))
{
}

epat::InitListExpr::ptr epat::InitListExpr::create(Expr::list init_list)
{
    QualType qt = BaseType::getVoid();
    if (auto size = init_list.size())
        qt = ArrayType::create(init_list[0]->getType(), (int)size);
    return ptr(new InitListExpr(move(qt), move(init_list)));
}

std::string epat::InitListExpr::getAstString(std::string prefix) const
{
    Node::list children;
    for (const auto& init : init_list_)
        children.emplace_back(init.get());
    return buildAstString(children, Expr::getAstString(), move(prefix));
}

std::string epat::InitListExpr::getCode(int indent) const
{
    ostringstream oss;
    oss << string(indent, ' ') << "{";
    for (size_t i = 0; i < init_list_.size(); i++) {
        if (i) oss << ", ";
        oss << init_list_[i]->getCode();
    }
    oss << "}";
    return oss.str();
}

std::string epat::MemberExpr::getSuffix() const
{
    string res = is_arrow_ ? string("->") : ".";
    return res + member_->getCode();
}

epat::MemberExpr::MemberExpr(Expr::ptr base, FieldDecl::ptr member, bool is_arrow)
    : Expr(StmtKind::MemberExpr, member->getType(), ExprValueKind::LValue),
      base_(move(base)), member_(move(member)), is_arrow_(is_arrow)
{
}

int epat::MemberExpr::getOperatorPrecedence() const
{
    return 1;
}

epat::MemberExpr::ptr epat::MemberExpr::create(
    Expr::ptr base, FieldDecl::ptr member, bool is_arrow
)
{
    return ptr(new MemberExpr(move(base), move(member), is_arrow));
}

epat::MemberExpr::ptr epat::MemberExpr::create(
    Expr::ptr base, const StructDecl& sd, std::string member, bool is_arrow
)
{
    if (auto fd = sd.getField(member)) {
        return create(move(base), move(fd), is_arrow);
    }
    else {
        cout << "warning: member \"" << member << "\" not found in struct \""
             << sd.getName() << "\"" << endl;
        return {};
    }
}

std::string epat::MemberExpr::getAstString(std::string prefix) const
{
    return buildAstString(
        {base_.get()}, Expr::getAstString() + " " + getSuffix(), move(prefix)
    );
}

std::string epat::MemberExpr::getCode(int indent) const
{
    bool need_paren = base_->getOperatorPrecedence() > getOperatorPrecedence();
    return string(indent, ' ') + add_parentheses(base_->getCode(), need_paren) +
           getSuffix();
}

epat::ReturnStmt::ReturnStmt(Expr::ptr ret) : Stmt(StmtKind::ReturnStmt), ret_(move(ret))
{
}

epat::ReturnStmt::ptr epat::ReturnStmt::create(Expr::ptr ret)
{
    return ptr(new ReturnStmt(move(ret)));
}

std::string epat::ReturnStmt::getAstString(std::string prefix) const
{
    return buildAstString({ret_.get()}, Stmt::getAstString(), move(prefix));
}

std::string epat::ReturnStmt::getCode(int indent) const
{
    return std::string(indent, ' ') + "return " + ret_->getCode();
}

// ast::Root::Root()
//     : CompoundStmt()
//{
// }

epat::Root::ptr epat::Root::create(/*Stmt::list stmts, */ Context::ref parent)
{
    return ptr(new Root(
        /*move(stmts), */ move(parent)
    ));
}

epat::SignStmt::SignStmt(Expr::ptr cond) : Stmt(StmtKind::SignStmt), cond_(move(cond))
{
}

epat::SignStmt::ptr epat::SignStmt::create(Expr::ptr cond)
{
    return ptr(new SignStmt(move(cond)));
}

std::string epat::SignStmt::getAstString(std::string prefix) const
{
    return buildAstString({cond_.get()}, Stmt::getAstString(), move(prefix));
}

std::string epat::SignStmt::getCode(int indent) const
{
    return string(indent, ' ') + "@ " + cond_->getCode();
}

epat::UnaryOperator::UnaryOperator(QualType wt, ExprValueKind evk, Expr::ptr expr, Uop op)
    : Expr(StmtKind::UnaryOperator, move(wt), evk), expr_(move(expr)), op_(op)
{
}

int epat::UnaryOperator::getOperatorPrecedence() const
{
    return getUopPrecedence(op_);
}

bool epat::UnaryOperator::isAssignOp(Uop op)
{
    return op == Uop::PreInc || op == Uop::PreDec || op == Uop::PostInc ||
           op == Uop::PostDec;
}

constant_value epat::UnaryOperator::getConstantValue() const
{
    if (isAssignOp(op_)) return {0, false};
    auto expr = expr_->getConstantValue();
    if (!expr.is_const) return {0, false};
    auto opd = expr.value;
#define MY_UOP(op_name, op)                                                              \
    case Uop::op_name:                                                                   \
        return {(op opd), true};
    switch (op_) {
        MY_UOP(Not, !)
        MY_UOP(Compl, ~)
        MY_UOP(UPlus, +)
        MY_UOP(UNeg, -)
#undef MY_BOP
    case Uop::Indirect:
    case Uop::AddrOf:
        return {0, false};
    default:
        cout << "debug:" << __LINE__ << ": "
             << "undefined unary operator: " << static_cast<int>(op_) << endl;
        return {0, false};
    }
}

epat::UnaryOperator::ptr epat::UnaryOperator::create(Expr::ptr expr, Uop op)
{
    auto type = expr->getType();
    // TODO: 确定类型和左右值
    return ptr(new UnaryOperator(type, ExprValueKind::RValue, move(expr), op));
}

epat::UnaryOperator::ptr epat::UnaryOperator::create(
    Expr::ptr expr, const std::string& op
)
{
    return UnaryOperator::create(move(expr), str2Uop(op));
}

const char* epat::UnaryOperator::uop2Str(Uop op)
{
    return UopStringList[static_cast<int>(op)];
}

epat::UnaryOperator::Uop epat::UnaryOperator::str2Uop(const std::string& str)
{
    for (int i = 0; i != static_cast<int>(Uop::Undefined); ++i)
        if (UopStringList[i] == str) return Uop(i);
    return Uop::Undefined;
}

int epat::UnaryOperator::getUopPrecedence(Uop op)
{
    if (int i = static_cast<int>(op); 0 <= i && i <= static_cast<int>(Uop::Undefined))
        return UopPrecedenceList[i];
    return UopPrecedenceList[static_cast<int>(Uop::Undefined)];
}

std::string epat::UnaryOperator::getAstString(std::string prefix) const
{
    return buildAstString(
        {expr_.get()}, Expr::getAstString() + " \'" + uop2Str(op_) + "\'", move(prefix)
    );
}

std::string epat::UnaryOperator::getCode(int indent) const
{
    if (op_ == Uop::PostInc || op_ == Uop::PostDec)
        return std::string(indent, ' ') + "(" + expr_->getCode() + ")" + uop2Str(op_);
    bool need_paren = expr_->getOperatorPrecedence() > getOperatorPrecedence();
    return std::string(indent, ' ') + uop2Str(op_) +
           add_parentheses(expr_->getCode(), need_paren);
}

epat::WhileStmt::WhileStmt(Expr::ptr cond, Stmt::ptr body)
    : Stmt(StmtKind::WhileStmt), cond_(move(cond)), body_(move(body))
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
    return ptr(new WhileStmt(move(cond), move(body)));
}

std::string epat::WhileStmt::getAstString(std::string prefix) const
{
    return buildAstString({cond_.get(), body_.get()}, Stmt::getAstString(), move(prefix));
}

std::string epat::WhileStmt::getCode(int indent) const
{
    ostringstream oss;
    oss << string(indent, ' ') << "while (" << (cond_ ? cond_->getCode() : "") << ")"
        << endl
        << body_->getCode(indent);
    return oss.str();
}
