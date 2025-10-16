#include "debug.h"
#include "exception.h"
#include "expression.h"
#include "solver.h"

#include <iostream>

#include "z3++.h"

using namespace std;
using namespace tool;
using namespace z3;

template<class T>
inline void safe_delete(T* ptr) {
    if (ptr) delete ptr;
}

inline z3::expr cast2bool(const z3::expr& e) {
    return e.is_bool() ? e : e != 0;
}

template<class T>
class Deleter {
    T* ptr;
public:
    Deleter(T* ptr) : ptr(ptr) {}
    ~Deleter() { safe_delete(ptr); }
    void skip() { ptr = nullptr; }
};

Node::~Node()
{
}

std::vector<Node*>& Node::getChildren() {
    return children;
}

void tool::Node::printInfo(std::ostream& os) const
{
    os << getInfo() << std::endl;
}

std::string tool::Node::getInfo() const
{
    return className();
}

void Node::printCode(std::ostream& os, int indent) const
{
    os << getCode() << std::endl;
}

std::string tool::Node::getCode(int indent) const
{
    return string(indent, ' ')
        + '$' + className() + '$';
}

void tool::Node::visit(tool::Solver& solver)
{
    return;
}

int Node::getMem()
{
    int tot = 0;
    for (auto c : getChildren())
        tot += c->getMem();
    return tot;
}

//void Node::exec(tool::Solver& solver)
//{
//	debug << className() << "没有实现exec方法。" << endl;
//	skip(cout);
//}

//z3::expr* Node::cast2z3(tool::Solver& solver) {
//	debug << className() << "没有实现cast2z3方法。" << endl;
//	return new z3::expr(*solver.getZ3Context());
//}

int Node::getAddr(tool::Solver& solver)
{
    return 0;
}

Node* tool::Node::cast2C1(Context* ctx)
{
    return this;
}

void Node::skip(ostream& os, string prefix) {
    cout << "Skip a node \"" << this << "\"" << std::endl;
}

void Node::print(std::ostream& os, std::string prefix)
{
    char suffix = '`';
    os << prefix << getInfo() << std::endl;
    if (prefix.size() > 0) {
        prefix.pop_back();
        if (prefix.back() == suffix)
            prefix.back() = ' ';
        prefix.push_back(' ');
    }
    prefix += "|-";
    auto& c = getChildren();
    for (size_t i = 0, size = c.size(); i != size; ++i) {
        if (i == size - 1)
            prefix[prefix.size() - 2] = suffix;
        c[i]->print(os, prefix);
    }
}

std::ostream& tool::operator<<(std::ostream& os, Node& n) {
    return os << n.getCode();
}

std::ostream& tool::operator<<(std::ostream& os, Node* n) {
    if (n)
        return os << n->getCode();
    return os << "nullptr";
}

Decl::Decl(DeclKind DeclKind, Context* ctx)
    : dk(DeclKind), ctx(ctx)
{
}

Decl::~Decl()
{ // TODO: remove in ctx ?
}

std::vector<Node*>& Decl::getChildren()
{
    return children;
}

std::string tool::Decl::getCode(int indent) const
{
    return string(indent, ' ') + "$Decl";
}

Context* Decl::getContext() {
    return ctx;
}

TranslationUnitDecl::TranslationUnitDecl(Context* ctx)
    : Decl(DeclKind::TranslationUnit, ctx)
{
}

TranslationUnitDecl::~TranslationUnitDecl()
{
    for (auto c : children)
        safe_delete(c);
}

TranslationUnitDecl* TranslationUnitDecl::create(Context* ctx) {
    return new TranslationUnitDecl(ctx);
}

std::vector<Node*>& TranslationUnitDecl::getChildren()
{
    return children;
}

std::string tool::TranslationUnitDecl::getCode(int indent) const
{
    std::string ret;
    bool first = true;
    for (auto c : children) {
        ret += string(indent, ' ');
        ret += c->getCode();
        if (dynamic_cast<Expr*>(c))
            ret += ";";
        if (first)
            ret += "\n";
        else
            first = false;
    }
    return ret;
}

void TranslationUnitDecl::visit(tool::Solver& solver)
{
    for (auto ii = children.begin(), ie = children.end();
        ii != ie; ++ii)
        solver.visit(*ii);
}

TranslationUnitDecl* tool::TranslationUnitDecl::cast2C1(Context* ctx)
{
    auto avd = ctx->getAvDecl();
    auto ii = children.insert(children.begin(), DeclStmt::create(avd));
    for (++ii; ii != children.end();) {
        auto n = *ii;
        if (auto ds = dynamic_cast<DeclStmt*>(n)) {
            auto tmp = dynamic_cast<CompoundStmt*>(ds->cast2C1(ctx));
            ii = children.erase(ii);
            if (tmp) {
                vector<Stmt*> stmts;
                tmp->swap(stmts);
                for (auto ri = stmts.rbegin(), re = stmts.rend();
                        ri != re; ++ri) {
                    ii = children.insert(ii, *ri);
                }
            }
        }
        else {
            auto ret = n->cast2C1(ctx);
            if (ret != n) {
                // TODO: 在子对象里删除。
                // delete n;
                *ii = ret;
            }
            ++ii;
        }
    }
    return this;
}

void TranslationUnitDecl::push(Decl* decl) {
    children.push_back(decl);
}

void TranslationUnitDecl::push(Stmt* stmt) {
    children.push_back(stmt);
}

NamedDecl::NamedDecl(DeclKind DeclKind, Context* Ctx, const string& name)
    : Decl(DeclKind, Ctx), name(name)
{
    ctx->addDecl(this);
}

const std::string& NamedDecl::getName() const
{
    return name;
}

TypeDecl::TypeDecl(DeclKind DeclKind, Context* Ctx, const string& name, int size)
    : NamedDecl(DeclKind, Ctx, name)
{	// TODO: add type here ?
}

TypeDecl::~TypeDecl()
{ // TODO: should we delete the type here?
}

bool tool::TypeDecl::isStruct() const
{
    return false;
}

ValueDecl::ValueDecl(DeclKind DeclKind, Context* Ctx, const string& name, QualType type)
    : NamedDecl(DeclKind, Ctx, name), type(type)
{
}

std::string tool::ValueDecl::getCode(int indent) const
{
    return string(indent, ' ') + type.getAsString() + " " + name;
}

QualType ValueDecl::getType() const
{
    return type;
}

tool::FieldDecl::FieldDecl(Context* Ctx, const std::string& name, const QualType& qt)
    : ValueDecl(DeclKind::Field, Ctx, name, qt), offset(0)
{
}

tool::FieldDecl::~FieldDecl()
{}

FieldDecl* tool::FieldDecl::create(Context * Ctx, const std::string & name, const QualType QT)
{
    return new FieldDecl(Ctx, name, QT);
}

std::string tool::FieldDecl::getInfo() const
{
    return className() + " " + getName()
        + " \'" + getType().getAsString() + "\'";
}

std::string tool::FieldDecl::getCode(int indent) const
{
    return std::string(indent, ' ')
        + getType().getBaseType()->getAsString()
        + " " + getType().getAsString(name);
}

int tool::FieldDecl::getFieldOffset() const
{
    if (offset)
        return offset - 1;
    auto sd = getParent();
    int o = 0;
    for (auto fd : sd->getFieldDecls()) {
        fd->offset = o + 1;
        o += fd->getType().getSize();
    }
    return offset - 1;
}

StructDecl* tool::FieldDecl::getParent() const
{
    return static_cast<StructDecl*>(ctx);
}

tool::VarDecl::VarDecl(Context* Ctx, const std::string& name, const QualType& qt, Expr* initExpr)
    : ValueDecl(DeclKind::Var, Ctx, name, qt), initExpr(initExpr)
{
}

VarDecl::~VarDecl()
{
    safe_delete(initExpr);
}

VarDecl* VarDecl::create(Context* Ctx, const string& name, const QualType& qt, Expr* initExpr)
{
    if (initExpr && initExpr->isArrayRef())
        Ctx->setPathType(2);
    if (auto il = dynamic_cast<InitListExpr*>(initExpr))
        il->setType(qt);
    return new VarDecl(
        Ctx, name, qt,
        ImplicitCastExpr::cast2(initExpr, qt)
    );
}

std::vector<Node*>& VarDecl::getChildren()
{
    children = std::vector<Node*>();
    if (initExpr) children.push_back(initExpr);
    return children;
}

std::string tool::VarDecl::getInfo() const
{
    return className() + " " + getName()
        + " \'" + getType().getAsString() + "\'"
        + (initExpr ? " cinit" : "");
}

std::string tool::VarDecl::getCode(int indent) const
{
    return std::string(indent, ' ') + type.getAsString(name);
}

void tool::VarDecl::visit(tool::Solver& solver)
{
    // TODO: 有复杂的初始化情况，如列表初始化
    if (initExpr)
        initExpr->visit(solver);
    solver.alloc(this, initExpr);
}

Expr* VarDecl::getInitExpr() const
{
    return initExpr;
}

std::vector<int> tool::VarDecl::getDimensions() const
{
    return type.getDimensions();
}

int VarDecl::getLenth() const
{
    return getType().getLenth();
}

int VarDecl::getSize() const
{
    return getType().getSize();
}

int tool::VarDecl::getAvAddress() const
{
    return av_adr;
}

Stmt::Stmt(StmtKind StmtKind)
    : sk(StmtKind)
{
}

Stmt* Stmt::createEmpty()
{
    return new Stmt(StmtKind::Empty);
}

std::string tool::Stmt::getInfo() const
{
    return className();
}

std::string tool::Stmt::getCode(int indent) const
{
    return string(indent, ' ') + ";";
}

Stmt* tool::Stmt::cast2C1(Context* ctx)
{
    //for (auto& c : getChildren()) {
    //	auto nc = c->cast2C1(ctx);
    //	if (nc != c) {
    //		// TODO: 当前版本子对象会释放自身
    //		// TODO: 这要求子节点cast2C1重构时舍弃了自身
    //		// delete c;
    //		c = nc;
    //	}
    //}
    return this;
}

//void Stmt::exec(tool::Solver& solver)
//{
//	skip(cout);
//}

tool::CompoundStmt::CompoundStmt(std::vector<Stmt*>&& stmts)
    : Stmt(StmtKind::CompoundStmt), stmts(stmts)
{
}

void tool::CompoundStmt::clear()
{
    stmts.clear();
}

void tool::CompoundStmt::swap(std::vector<Stmt*>& stmts)
{
    this->stmts.swap(stmts);
}

tool::CompoundStmt::~CompoundStmt()
{
    for (auto stmt : stmts)
        if (stmt)
            delete stmt;
}

CompoundStmt* tool::CompoundStmt::create(std::vector<Stmt*>&& stmts)
{
    return new CompoundStmt(move(stmts));
}

std::vector<Stmt*> tool::CompoundStmt::getStmts() const
{
    return stmts;
}

void tool::CompoundStmt::addStmt(Stmt* stmt)
{
    stmts.push_back(stmt);
}

DeclStmt::DeclStmt(Decl* D)
    : Stmt(StmtKind::DeclStmt), decls({ D })
{
}

DeclStmt::DeclStmt(const std::vector<Decl*>& Decls)
    : Stmt(StmtKind::DeclStmt), decls(Decls)
{
}

DeclStmt::~DeclStmt()
{ // TODO: should we delete decls here?
}

DeclStmt* DeclStmt::create(Decl* D)
{
    return new DeclStmt(D);
}

DeclStmt* DeclStmt::create(const vector<Decl*>& Decls)
{
    return new DeclStmt(Decls);
}

vector<Node*>& DeclStmt::getChildren()
{
    children = std::vector<Node*>();
    for (auto d : decls) children.push_back(d);
    return children;
}

std::string tool::DeclStmt::getCode(int indent) const
{
    std::string ret = "";
    bool first = true;
    for (auto d : decls) {
        if (auto vd = dynamic_cast<VarDecl*>(d)) {
            const QualType& qt = vd->getType();
            if (first) {
                first = false;
                ret += std::string(indent, ' ');
                ret += qt.getBaseType()->getAsString() + " ";
            }
            else
                ret += ", ";
            ret += qt.getAsString(vd->getName());
            if (vd->initExpr)
                ret += " = " + vd->initExpr->getCode();
        }
        else if (auto sd = dynamic_cast<StructDecl*>(d)) {
            // TODO: structdecl和vardecl不能同时出现
            ret += sd->getCode(indent);
        }
    }
    return ret + ";";
}

void DeclStmt::visit(tool::Solver& solver)
{
    for (auto d : decls)
        d->visit(solver);
}

Stmt* tool::DeclStmt::cast2C1(Context* ctx)
{
    CompoundStmt* ret = CompoundStmt::create({});
    for (auto d : decls)
        if (auto vard = dynamic_cast<VarDecl*>(d)) {
            if (auto init = vard->getInitExpr()) {
                if (auto tmp = dynamic_cast<Expr*>(init->cast2C1(ctx))) {
                    int size = vard->getType().getSize();
                    if (size == 1)
                        ret->addStmt(
                            BinaryOperator::create(
                                DeclRefExpr::create(vard, vard->getType()),
                                tmp, "=", ctx
                            )
                        );
                    else if (size > 1) {
                        int left = vard->getAvAddress(), right = left + size;
                        ret->addStmt(
                            RangeCopyExpr::create(
                                ctx->getAvDecl(), left, right, tmp
                            )
                        );
                    }
                }
                vard->initExpr = nullptr;
            }
        }
    Deleter d(this);
    return ret;
}

//Node::iter tool::DeclStmt::cast2C1(tool::Solver& solver, iter it)
//{
//	vector<Node*> ns;
//	ns.erase()
//	return it;
//}

//void DeclStmt::exec(tool::Solver& solver)
//{
//	for (auto d : decls) {
//		auto vard = dynamic_cast<VarDecl*>(d);
//		if (vard == nullptr) {
//			debug << "DeclStmt含有非VarDecl的声明，已跳过。" << endl;
//			continue;
//		}
//		solver.getTable()->init(vard);
//		solver.getTable()->print(cout);
//	}
//}

//void ValueStmt::exec(tool::Solver& solver)
//{
//	safe_delete(this->cast2z3(solver));
//}

SignStmt::SignStmt(Expr* E)
    : Stmt(StmtKind::SignStmt), expr(ImplicitCastExpr::cast2RvExpr(E))
{
}

SignStmt::~SignStmt()
{
    safe_delete(expr);
}

SignStmt* SignStmt::create(Expr* E)
{
    return new SignStmt(E);
}

std::vector<Node*>& SignStmt::getChildren()
{
    return children = std::vector<Node*>({ expr });
}

std::string tool::SignStmt::getCode(int indent) const
{
    return string(indent, ' ') + "@ " + expr->getCode() + ";";
}

void SignStmt::visit(tool::Solver& solver)
{
    solver.visit(expr);
    debug << solver.getRValue(expr) << tool::endL;
    debug << cast2bool(solver.getRValue(expr)) << tool::endL;
    solver.addCond(cast2bool(solver.getRValue(expr)));
}

Stmt* tool::SignStmt::cast2C1(Context* ctx)
{
    expr = dynamic_cast<Expr*>(expr->cast2C1(ctx));
    return this;
}

//void SignStmt::exec(Solver& solver)
//{
//	solver.pushCond(*expr->cast2z3(solver));
//}

std::string Expr::ExprValueKind2Str(ExprValueKind vk)
{
    switch (vk)
    {
    case Expr::ExprValueKind::LValue:
        return "lvalue";
    case Expr::ExprValueKind::RValue:
        return "rvalue";
    case Expr::ExprValueKind::XValue:
        return "xvalue";
    default:
        return "undefined";
    }
}

Expr::Expr(StmtKind StmtKind, QualType QT, ExprValueKind EVK)
    : ValueStmt(StmtKind), qt(QT), vk(EVK)
{
}

Expr::~Expr()
{
}

std::string tool::Expr::getInfo() const
{
    string ret = className() + " \'"
        + getType().getAsString() + "\'";
    if (isLvExpr())
        ret += " lvalue";
    return ret;
}

Expr* tool::Expr::cast2C1(Context* ctx)
{
    return this;
}

bool Expr::isLvExpr() const
{
    return vk == ExprValueKind::LValue;
}

bool Expr::isRvExpr() const
{
    return vk == ExprValueKind::RValue;
}

bool Expr::isArrayRef() const
{
    return false;
}

bool Expr::isArrayPointer() const
{
    return false;
}

bool Expr::isConstant() const
{
    return false;
}

int Expr::getConstantValue() const
{
    return 0;
}

ValueDecl* Expr::getValueDecl() const
{
    debug << "error: getValueDecl on an expr" << tool::endL;
    return nullptr;
}

QualType Expr::getType() const
{
    return qt;
}

ArraySubscriptExpr::ArraySubscriptExpr(Expr* BS, Expr* SS)
    : Expr(StmtKind::ArraySubscriptExpr,
        BS->getType().getPointeeType(), ExprValueKind::LValue),
    base(BS), subscript(SS)
{
    // TODO: 上下界确认难题，下面的过程只适应传入的基是弱化数组指针。
    // 现阶段在编译前端进行转换，避免除此以外的情形。
    lower_bound = 0;
    if (BS->getType().isDecayed())
        upper_bound = lower_bound + BS->getType().getLenth();
    else {
        // cout << "warning: 现版本不支持数组指针取值" << endl;
        upper_bound = lower_bound + BS->getType().getLenth();
    }
}

ArraySubscriptExpr::~ArraySubscriptExpr()
{
    safe_delete(base);
    safe_delete(subscript);
}

ArraySubscriptExpr* ArraySubscriptExpr::create(Expr* BS, Expr* SS)
{
    BS = ImplicitCastExpr::cast2ArrayPointer(BS);
    SS = ImplicitCastExpr::cast2RvExpr(SS);
    return new ArraySubscriptExpr(BS, SS);
}

ArraySubscriptExpr* tool::ArraySubscriptExpr::increaseSubscriptBy(Expr* Delta, Context* Ctx)
{
    subscript = BinaryOperator::createSimplified(
        subscript, Delta, "+", Ctx
    );
    return this;
}

void tool::ArraySubscriptExpr::setBound(int lower, int upper)
{
    lower_bound = lower;
    upper_bound = upper;
}

void tool::ArraySubscriptExpr::moveBound(int offset)
{
    lower_bound += offset;
    upper_bound += offset;
}

Expr* tool::ArraySubscriptExpr::getBase() const
{
    return base;
}

Expr* tool::ArraySubscriptExpr::getSubscript() const
{
    return subscript;
}

std::vector<Node*>& ArraySubscriptExpr::getChildren()
{
    return children = std::vector<Node*>({ base, subscript });
}

std::string tool::ArraySubscriptExpr::getInfo() const
{
    return Expr::getInfo();
}

std::string ArraySubscriptExpr::getCode(int indent) const
{
    return string(indent, ' ') + base->getCode()
        + "[" + subscript->getCode() + "]";
}

int ArraySubscriptExpr::getMem()
{
    return 1 + subscript->getMem();
}

ValueDecl* tool::ArraySubscriptExpr::getValueDecl() const
{
    return base->getValueDecl();
}

void ArraySubscriptExpr::visit(tool::Solver& solver)
{
    // 此处的代码应与Solver的内部实现无关
    solver.visit(base); // TODO: 不知道是否有必要
    // auto [vard, off] = solver.getLValue(base); // 有可能base是数组下标表达式
    solver.setBacktrackingPoint(this); // solver会给其赋左值
    
    //solver.visit(base); // TODO: 似乎没有必要？与数组指针有关的运算会被先转换，base似乎只会是DeclRef
    //// solver.visit(subscript);
    //auto qt = base->getType();
    //int sz = qt.getElementSize(), len = qt.getLenth();
    //auto [vd, off] = solver.getLValue(base);
    //if (solver.usingSparseArray()) {
    //    // 不使用稀疏数组
    //    if (subscript->isConstant()) {
    //        int v = subscript->getConstantValue();
    //        if (v < lower_bound || v >= upper_bound)
    //            throw feasibility_exception(result::infeasible);
    //        solver.visit(subscript);
    //        solver.setLValue(this, { vd, off + sz * v });
    //    }
    //    else {
    //        solver.setBacktrackPoint(subscript, 0, len);
    //        solver.setLValue(this, { vd, off + sz * solver.getBacktrackPointValue(subscript) });
    //    }
    //}
    //else {
    //    // 使用稀疏数组
    //    solver.setBacktrackPoint(subscript, 0, len);
    //    
    //}
}

Expr* tool::ArraySubscriptExpr::cast2C1(Context* ctx)
{
    // TODO: assert(...);
    base->cast2C1(ctx);
    auto new_base = base;
    subscript->cast2C1(ctx);
    auto off = BinaryOperator::createSimplified(
        ctx->createInt(getType().getSize()),
        subscript, "*", ctx
    );
    // release self
    base = subscript = nullptr;
    Deleter d(this);
    auto ary = ctx->getAvDecl();
    return ArraySubscriptExpr::create(
        DeclRefExpr::create(ary, ary->getType()),
        BinaryOperator::createSimplified(
            new_base, off, "+", ctx
        )
    );
}

string BinaryOperator::bop2Str(BOp op)
{
    switch (op)
    {
    case BinaryOperator::BOp::Assign:
        return "=";
    case BinaryOperator::BOp::Add:
        return "+";
    case BinaryOperator::BOp::Sub:
        return "-";
    case BinaryOperator::BOp::Mul:
        return "*";
    case BinaryOperator::BOp::Div:
        return "/";
    case BinaryOperator::BOp::Add_As:
        return "+=";
    case BinaryOperator::BOp::Sub_As:
        return "-=";
    case BinaryOperator::BOp::Mul_As:
        return "*=";
    case BinaryOperator::BOp::Div_As:
        return "/=";
    case BinaryOperator::BOp::Mod:
        return "%";
    case BinaryOperator::BOp::Unequal:
        return "!=";
    case BinaryOperator::BOp::Equal:
        return "==";
    case BinaryOperator::BOp::Greater:
        return ">";
    case BinaryOperator::BOp::Less:
        return "<";
    case BinaryOperator::BOp::GE:
        return ">=";
    case BinaryOperator::BOp::LE:
        return "<=";
    case BinaryOperator::BOp::LogicAnd:
        return "&&";
    case BinaryOperator::BOp::LogicOr:
        return "||";
    case BinaryOperator::BOp::Undefined:
    default:
        return "$undefined$";
    }
}

BinaryOperator::BOp BinaryOperator::str2BOp(const std::string& s)
{
    for (int i = 0; i < (int)BOp::Undefined; ++i) {
        auto res = (BOp)i;
        if (bop2Str(res) == s)
            return res;
    }
    return BOp::Undefined;
}

bool tool::BinaryOperator::isLogicalBOp(BOp op)
{
    return op == BOp::Equal || op == BOp::Greater || op == BOp::Less || op == BOp::GE || op == BOp::LE;
}

bool tool::BinaryOperator::isAssignmentBOp(BOp op)
{
    return op == BOp::Assign || op == BOp::Add_As || op == BOp::Sub_As || op == BOp::Mul_As || op == BOp::Div_As;
}

BinaryOperator::BinaryOperator(Expr* LHS, Expr* RHS, BOp OP, QualType QT)
    : Expr(StmtKind::BinaryOperator, QT, ExprValueKind::RValue),
    lhs(LHS), rhs(RHS), op(OP)
{
    rhs = ImplicitCastExpr::cast2RvExpr(rhs);
    if (!isAssignmentBOp(op))
        lhs = ImplicitCastExpr::cast2RvExpr(lhs);
}

BinaryOperator::BinaryOperator(Expr* LHS, Expr* RHS, const std::string& s, QualType QT)
    : BinaryOperator(LHS, RHS, str2BOp(s), QT)
{
}

BinaryOperator::~BinaryOperator()
{
    safe_delete(lhs);
    safe_delete(rhs);
}

QualType get_result_type(QualType lt, QualType rt, BinaryOperator::BOp op, Context* Ctx)
{
    using BOp = BinaryOperator::BOp;
    if (lt.isPointer()) {
        if (rt.isPointer() && (op == BOp::Sub || op == BOp::Sub_As))
            return Ctx->getIntType();
        else if (rt.isInt() && (op == BOp::Sub || op == BOp::Sub_As || op == BOp::Add || op == BOp::Add_As))
            return lt;
    }
    else if (rt.isPointer())
        if (lt.isInt())
            return rt;
    if (BinaryOperator::isLogicalBOp(op))
        return Ctx->getIntType();
    return lt;
}

BinaryOperator* BinaryOperator::create(Expr* LHS, Expr* RHS, BOp Op, Context* Ctx)
{
    if (isAssignmentBOp(Op) && LHS->isRvExpr())
        throw parser_exception("\"" + LHS->getCode() + "\"不是左值表达式");

    if (LHS->isArrayRef() || RHS->isArrayRef())
        Ctx->setPathType(2);
    auto lt = LHS->getType(), rt = RHS->getType();
    if (rt.isArray())
        RHS = ImplicitCastExpr::cast2ArrayPointer(RHS);
    if (lt.isArray())
        LHS = ImplicitCastExpr::cast2ArrayPointer(LHS);
    if (isLogicalBOp(Op))
        RHS = ImplicitCastExpr::cast2(RHS, lt);

    return new BinaryOperator(LHS, RHS, Op, get_result_type(LHS->getType(), RHS->getType(), Op, Ctx));
}

BinaryOperator* BinaryOperator::create(Expr* LHS, Expr* RHS, const string& s, Context* Ctx)
{
    return BinaryOperator::create(LHS, RHS, str2BOp(s), Ctx);
}

Expr* tool::BinaryOperator::createSimplified(Expr* LHS, Expr* RHS, BOp op, Context* ctx)
{
    if (LHS->isConstant() && RHS->isConstant()) {
        int v = 0, l = LHS->getConstantValue(),
            r = RHS->getConstantValue();
        switch (op)
        {
        case tool::BinaryOperator::BOp::Assign:
            v = (l = r); break;
        case tool::BinaryOperator::BOp::Add:
            v = l + r; break;
        case tool::BinaryOperator::BOp::Sub:
            v = 1 - r; break;
        case tool::BinaryOperator::BOp::Mul:
            v = l * r; break;
        case tool::BinaryOperator::BOp::Div:
            v = 1 / r; break;
        //case tool::BinaryOperator::BOp::Add_As:
        //	break;
        //case tool::BinaryOperator::BOp::Sub_As:
        //	break;
        //case tool::BinaryOperator::BOp::Mul_As:
        //	break;
        //case tool::BinaryOperator::BOp::Div_As:
        //	break;
        case tool::BinaryOperator::BOp::Mod:
            v = l % r; break;
        case tool::BinaryOperator::BOp::Unequal:
            v = (l != r); break;
        case tool::BinaryOperator::BOp::Equal:
            v = (l == r); break;
        case tool::BinaryOperator::BOp::Greater:
            v = (l > r); break;
        case tool::BinaryOperator::BOp::Less:
            v = (l < r); break;
        case tool::BinaryOperator::BOp::GE:
            v = (l >= r); break;
        case tool::BinaryOperator::BOp::LE:
            v = (1 <= r); break;
        case tool::BinaryOperator::BOp::LogicAnd:
            v = (l != 0) and (r != 0); break;
        case tool::BinaryOperator::BOp::LogicOr:
            v = (l != 0) or (r != 0); break;
        case tool::BinaryOperator::BOp::Undefined:
        default:
            break;
        }
        delete LHS;
        delete RHS;
        return IntLiteral::create(ctx, v);
    }
    return BinaryOperator::create(LHS, RHS, op, ctx);
}

Expr* tool::BinaryOperator::createSimplified(Expr* LHS, Expr* RHS, const std::string& s, Context* ctx)
{
    return BinaryOperator::createSimplified(LHS, RHS, str2BOp(s), ctx);
}

std::vector<Node*>& BinaryOperator::getChildren()
{
    return children = std::vector<Node*>({ lhs, rhs });
}

std::string tool::BinaryOperator::getInfo() const
{
    return Expr::getInfo() + " \'" + bop2Str( op) + "\'";
}

std::string BinaryOperator::getCode(int indent) const
{
    return string(indent, ' ') + "(" + lhs->getCode() + ") "
        + bop2Str(op) + " (" + rhs->getCode() + ")";
}

void BinaryOperator::visit(tool::Solver& solver)
{
    // TODO: 指针运算需要特别处理！
    if (op == BOp::Assign) {
        solver.visit(rhs); solver.visit(lhs);
        solver.assign(solver.getLValue(lhs), solver.getRValue(rhs));
        solver.setRValue(this, solver.getRValue(rhs));
    }
    else if (op == BOp::Add_As || op == BOp::Sub_As
        || op == BOp::Mul_As || op == BOp::Div_As) {
        solver.visit(lhs); solver.visit(rhs);
        auto adr = solver.getLValue(lhs);
        auto&& lop = solver.getMemory(adr),
            && rop = solver.getRValue(rhs);
        auto&& lt = lhs->getType(), && rt = rhs->getType();
        switch (op)
        {
        case BinaryOperator::BOp::Add_As:
            // 仅当lhs是指针，rhs是整型时有定义
            if (lt.isPointer()) {
                if (rt.isInt())
                    rop = rop * lt.getDirectPointeeSize();
            }
            solver.assign(adr, lop + rop); break;
        case BinaryOperator::BOp::Sub_As:
            // 仅当lhs是指针，rhs是整型或指针时有定义
            if (lt.isPointer()) {
                int lp_sz = lt.getDirectPointeeSize();
                if (rt.isInt())
                    solver.assign(adr, lop - rop * lp_sz);
                else if (rt.isPointer()) {
                    int rp_sz = rt.getDirectPointeeSize();
                    auto&& tmp = lop - rop;
                    if (lp_sz == rp_sz)
                        solver.assign(adr, tmp / rp_sz);
                    else
                        solver.assign(adr, move(tmp));
                }
            }
            break;
        case BinaryOperator::BOp::Mul_As:
            solver.assign(adr, lop * rop); break;
        case BinaryOperator::BOp::Div_As:
            solver.assign(adr, lop / rop); break;
        case BinaryOperator::BOp::Undefined:
        default:
            break;
        }
        solver.setRValue(this, solver.getMemory(adr));
    }
    else {
        solver.visit(lhs); solver.visit(rhs);
        z3::expr res = solver.getZ3Context().int_val(0);
        z3::expr l = solver.getRValue(lhs), 
            r = solver.getRValue(rhs);
        auto&& lt = lhs->getType(), && rt = rhs->getType();
        switch (op)
        {
        case BinaryOperator::BOp::Add:
            // 当一个操作数是指针时，仅当另一操作数是整型时有定义
            if (lt.isPointer() && rt.isInt())
                r = r * lt.getDirectPointeeSize();
            else if (lt.isInt() && rt.isPointer())
                l = l * rt.getDirectPointeeSize();
            res = l + r; break;
        case BinaryOperator::BOp::Sub:
            // 仅当lhs是指针，rhs是整型或指针时有定义
            if (lt.isPointer()) {
                if (rt.isPointer()) {
                    if (lt == rt)
                        res = (l - r) / lt.getDirectPointeeSize();
                    else
                        res = l - r;
                }
                else if (rt.isInt())
                    res = l - r * lt.getDirectPointeeSize();
            }
            else
                res = l - r;
            break;
        case BinaryOperator::BOp::Mul:
            res = l * r; break;
        case BinaryOperator::BOp::Div:
            res = l / r; break;
        case BinaryOperator::BOp::Mod:
            res = l % r; break;
        case BinaryOperator::BOp::Unequal:
            res = l != r; break;
        case BinaryOperator::BOp::Equal:
            // cout << l << ", " << r << ", " << (l == r) << endl;
            res = l == r; break;
        case BinaryOperator::BOp::Greater:
            res = l > r; break;
        case BinaryOperator::BOp::Less:
            res = l < r; break;
        case BinaryOperator::BOp::GE:
            res = l >= r; break;
        case BinaryOperator::BOp::LE:
            res = l <= r; break;
        case BinaryOperator::BOp::LogicAnd:
            res = cast2bool(std::move(l)) && cast2bool(std::move(r)); break;
        case BinaryOperator::BOp::LogicOr:
            res = cast2bool(std::move(l)) || cast2bool(std::move(r)); break;
        case BinaryOperator::BOp::Undefined:
        default:
            debug << "无法把操作符" << bop2Str(op) << "转换成z3表达式" << tool::endL;
            break;
        }
        solver.setRValue(this, std::move(res));
    }
}

Expr* tool::BinaryOperator::cast2C1(Context* ctx)
{
    lhs = dynamic_cast<Expr*>(lhs->cast2C1(ctx));
    rhs = dynamic_cast<Expr*>(rhs->cast2C1(ctx));
    return this;
}

ostream& tool::operator<<(ostream& os, BinaryOperator::BOp op)
{
    return (os << BinaryOperator::bop2Str(op), os);
}


tool::CallExpr::CallExpr(StmtKind SK, QualType QT, ExprValueKind VK, const std::string& callee)
    :Expr(SK, QT, VK), callee(callee)
{
}

tool::CallExpr::~CallExpr()
{
}

CallExpr* tool::CallExpr::create(QualType QT, const std::string& callee)
{
    return new CallExpr(StmtKind::CallExpr, QT, ExprValueKind::RValue, callee);
}

std::vector<Node*>& tool::CallExpr::getChildren()
{
    return Expr::getChildren();
}

std::string tool::CallExpr::getInfo() const
{
    return Expr::getInfo();
}

std::string tool::CallExpr::getCode(int indent) const
{
    return string(indent, ' ') + callee + "(...)";
}

void tool::CallExpr::visit(tool::Solver& solver)
{
    // TODO: it will always return the same value
    solver.setRValue(this, 
        solver.getZ3Context().int_const(callee.c_str()));
}

Expr* tool::CallExpr::cast2C1(Context* ctx)
{
    return this;
}

std::string tool::CastExpr::ck2Str(CastKind ck)
{
    switch (ck)
    {
    case tool::CastExpr::CastKind::ArrayToPointerDecay:
        return "ArrayToPointerDecay";
    case tool::CastExpr::CastKind::DecayedToPointer:
        return "DecayedToPointer";
    case tool::CastExpr::CastKind::IntegralToPointer:
        return "IntegralToPointer";
    case tool::CastExpr::CastKind::LValueToRValue:
        return "LValueToRValue";
    case tool::CastExpr::CastKind::PointerToIntegral:
        return "PointerToIntegral";
    default:
        return "Undefined(" + to_string(int(ck)) + ")";
    }
}

CastExpr::CastExpr(StmtKind SK, QualType QT, ExprValueKind VK, CastKind CK, Expr* E)
    : Expr(SK, QT, VK), ck(CK), expr(E)
{
}

CastExpr::~CastExpr()
{
    safe_delete(expr);
}

std::vector<Node*>& CastExpr::getChildren()
{
    return children = std::vector<Node*>({ expr });
}

std::string tool::CastExpr::getInfo() const
{
    return Expr::getInfo() + " <"
        + ck2Str(ck) + ">";
}

std::string CastExpr::getCode(int indent) const
{
    return string(indent, ' ') + expr->getCode();
}

Expr* tool::CastExpr::unwrap(Expr* E)
{
    if (auto ce = dynamic_cast<CastExpr*>(E))
        return unwrap(ce->expr);
    return E;
}

ValueDecl* tool::CastExpr::getValueDecl() const
{
    return expr->getValueDecl();
}

Expr* tool::CastExpr::getSubExpr() const
{
    return expr;
}

Expr* tool::CastExpr::reduceSubExpr()
{
    auto ret = expr;
    expr = nullptr;
    Deleter d(this);
    return ret;
}

void CastExpr::visit(tool::Solver& solver)
{
    solver.visit(expr);
    if (ck == CastKind::LValueToRValue)
        solver.setRValue(this, solver.getMemory(solver.getLValue(expr)));
    else {
        // TODO: 更多复杂情况未考虑
        if (expr->isLvExpr())
            solver.setLValue(this, solver.getLValue(expr));
        else
            solver.setRValue(this, solver.getRValue(expr));
    }
}

Expr* tool::CastExpr::cast2C1(Context* ctx)
{
    expr = dynamic_cast<Expr*>(expr->cast2C1(ctx));
    return this;
}

bool tool::CastExpr::isArrayRef() const
{
    return expr->isArrayRef();
}

bool tool::CastExpr::isConstant() const
{
    return expr->isConstant();
}

int tool::CastExpr::getConstantValue() const
{
    return expr->getConstantValue();
}

tool::CharLiteral::CharLiteral(Context* Ctx, unsigned int V)
    : Expr(StmtKind::CharLiteral,
        Ctx->getCharType(), ExprValueKind::RValue),
    value(V)
{
}

tool::CharLiteral::~CharLiteral()
{
}

CharLiteral* tool::CharLiteral::create(Context* Ctx, int V)
{
    return new CharLiteral(Ctx, V);
}

std::string tool::CharLiteral::getInfo() const
{
    return Expr::getInfo() + " " + to_string(value);
}

std::string tool::CharLiteral::getCode(int indent) const
{
    return string(indent, ' ') + '\'' + string(1, value) + '\'';
}

void tool::CharLiteral::visit(tool::Solver& solver)
{
    solver.setRValue(this, solver.getZ3Context().int_val(value));
}

int tool::CharLiteral::getValue() const
{
    return value;
}

bool tool::CharLiteral::isConstant() const
{
    return true;
}

int tool::CharLiteral::getConstantValue() const
{
    return value;
}

DeclRefExpr::DeclRefExpr(ValueDecl* VD, QualType QT)
    : Expr(StmtKind::DeclRefExpr, QT, ExprValueKind::LValue), vd(VD)
{
}

DeclRefExpr::~DeclRefExpr()
{
}

DeclRefExpr* DeclRefExpr::create(ValueDecl* VD, QualType QT)
{
    return new DeclRefExpr(VD, QT);
}

std::vector<Node*>& DeclRefExpr::getChildren()
{
    return children = std::vector<Node*>();
}

std::string tool::DeclRefExpr::getInfo() const
{ // TODO: only Var
    return Expr::getInfo() + " Var "
        + "\'" + vd->getName() + "\' "
        + "\'" + vd->getType().getAsString() + "\'";
}

std::string DeclRefExpr::getCode(int indent) const
{
    return string(indent, ' ') + vd->getName();
}

void DeclRefExpr::visit(tool::Solver& solver)
{
    auto vard = dynamic_cast<VarDecl*>(this->vd);
    solver.setLValue(this, { vard, 0 });
}

Expr* tool::DeclRefExpr::cast2C1(Context* ctx)
{
    auto avd = ctx->getAvDecl();
    auto vard = dynamic_cast<VarDecl*>(vd);
    if (!vard)
        return this;
    Deleter d(this);
    if (vard->getType().isArray())
        return ctx->createInt(vard->av_adr);
    return ArraySubscriptExpr::create(
        DeclRefExpr::create(avd, avd->getType()),
        IntLiteral::create(ctx, vard->av_adr)
    );
}

//z3::expr* DeclRefExpr::cast2z3(tool::Solver& solver)
//{
//	return solver.getTable()->get(dynamic_cast<VarDecl*>(vd));
//}

ValueDecl* DeclRefExpr::getValueDecl() const
{
    return vd;
}

bool DeclRefExpr::isArrayRef() const
{
    auto vard = dynamic_cast<VarDecl*>(vd);
    return vard && vard->getType().isArray();
}

ImplicitCastExpr::ImplicitCastExpr(QualType QT, CastKind CK, Expr* E, ExprValueKind VK)
    : CastExpr(StmtKind::ImplicitCastExpr, QT, VK, CK, E)
{
}

ImplicitCastExpr* ImplicitCastExpr::create(QualType QT, CastKind CK, Expr* E, ExprValueKind VK)
{
    return new ImplicitCastExpr(QT, CK, E, VK);
}

ImplicitCastExpr::~ImplicitCastExpr()
{
}

Expr* ImplicitCastExpr::cast2RvExpr(Expr* expr)
{
    if (expr->isRvExpr())
        return expr;
    if (expr->getType().isArray())
        return ImplicitCastExpr::cast2ArrayPointer(expr);
    return new ImplicitCastExpr(expr->getType(),
        CastKind::LValueToRValue, expr, ExprValueKind::RValue);
}

Expr* ImplicitCastExpr::cast2ArrayPointer(Expr* expr)
{
    auto qt = expr->getType();
    /*if (qt.isPointer())
        return ImplicitCastExpr::cast2RvExpr(expr);
    else */
    if (qt.isArray())
        return new ImplicitCastExpr(qt.getPointerDecay(),
            CastKind::ArrayToPointerDecay, expr, ExprValueKind::RValue);
    return expr;
}

//Expr* tool::ImplicitCastExpr::castDecayed2Pointer(Expr* expr)
//{
//    auto qt = expr->getType();
//    if (qt.isDecayed())
//        return new ImplicitCastExpr(qt.getPointerType(),
//            CastKind::DecayedToPointer, expr, ExprValueKind::RValue);
//    return expr;
//}

Expr* tool::ImplicitCastExpr::castIntegral2Pointer(Expr* expr, QualType pt)
{
    if (pt.isPointer() && expr->getType().isInt())
        return ImplicitCastExpr::create(
            pt, CastKind::IntegralToPointer,
            ImplicitCastExpr::cast2RvExpr(expr),
            ExprValueKind::RValue
        );
    return expr;
}

Expr* tool::ImplicitCastExpr::castPointer2Integral(Expr* expr, QualType integral)
{
    auto qt = expr->getType();
    if ((qt.isPointer() || qt.isDecayed()) && integral.isInt())
        return ImplicitCastExpr::create(
            integral, CastKind::PointerToIntegral,
            ImplicitCastExpr::cast2RvExpr(expr),
            ExprValueKind::RValue
        );
    return expr;
}

Expr* tool::ImplicitCastExpr::cast2(Expr* E, QualType target_type)
{
    if (!E)
        return nullptr;
    auto qt = E->getType();
    if (qt == target_type)
        return E;
    if (E->getType().isArray() && !target_type.isArray())
        E = ImplicitCastExpr::cast2ArrayPointer(E);
    qt = E->getType();
    if (qt.isInt() && target_type.isPointer())
        E = castIntegral2Pointer(E, target_type);
    else if (qt.isPointer() && target_type.isInt())
        E = castPointer2Integral(E, target_type);
    return E;
}

tool::InitListExpr::InitListExpr(std::vector<Expr*>& init_list, QualType qt)
    : Expr(StmtKind::IntLiteral, qt, ExprValueKind::RValue)
{
    this->init_list.swap(init_list);
}

void tool::InitListExpr::setType(QualType qt)
{
    this->qt = qt;
}

tool::InitListExpr::~InitListExpr()
{
    for (auto e : init_list)
        delete e;
}

InitListExpr* tool::InitListExpr::create(std::vector<Expr*>& init_list, QualType qt)
{
    for (auto& e : init_list)
        e = ImplicitCastExpr::cast2RvExpr(e);
    return new InitListExpr(init_list, qt);
}

std::vector<Node*>& tool::InitListExpr::getChildren()
{
    children.clear();
    for (auto e : init_list)
        children.push_back(e);
    return children;
}

std::string tool::InitListExpr::getInfo() const
{
    return Expr::getInfo();
}

std::string tool::InitListExpr::getCode(int indent) const
{
    string ret = string(indent, ' ') + "{ ";
    bool first = true;
    for (auto e : init_list) {
        if (first)
            first = false;
        else
            ret += ", ";
        ret += e->getCode();
    }
    ret += " }";
    return ret;
}

void tool::InitListExpr::visit(tool::Solver& solver)
{
    for (auto e : init_list)
        solver.visit(e);
}

Expr* tool::InitListExpr::cast2C1(Context* ctx)
{
    for (auto& e : init_list)
        e = e->cast2C1(ctx);
    return this;
}

int tool::InitListExpr::getLenth() const
{
    return (int)init_list.size();
}

Expr* tool::InitListExpr::at(int i)
{
    if (0 <= i && i < init_list.size())
        return init_list.at(i);
    return nullptr;
}

tool::IntLiteral::IntLiteral(Context* Ctx, int V)
    : Expr(StmtKind::IntLiteral, Ctx->getIntType(), ExprValueKind::RValue), value(V)
{
}

tool::IntLiteral::~IntLiteral()
{
}

IntLiteral* IntLiteral::create(Context* Ctx, int V) {
    return new IntLiteral(Ctx, V);
}

std::string tool::IntLiteral::getInfo() const
{
    return Expr::getInfo() + " " + to_string(value);
}

std::string IntLiteral::getCode(int indent) const
{
    return string(indent, ' ') + to_string(value);
}

void IntLiteral::visit(tool::Solver& solver)
{
    solver.setRValue(this, solver.getZ3Context().int_val(value));
}

int IntLiteral::getValue() const
{
    return value;
}

bool IntLiteral::isConstant() const
{
    return true;
}

int IntLiteral::getConstantValue() const
{
    return value;
}

tool::MemberExpr::MemberExpr(Expr* BS, FieldDecl* MD, QualType QT, bool isArrow)
    :Expr(StmtKind::MemberExpr, QT, ExprValueKind::LValue),
    Base(BS), MemberDecl(MD), isArrow(isArrow)
{
}

tool::MemberExpr::~MemberExpr()
{
    safe_delete(Base);
}

MemberExpr* tool::MemberExpr::create(Expr* BS, ValueDecl* MD, QualType QT, bool isArrow)
{
    return new MemberExpr(ImplicitCastExpr::cast2RvExpr(BS),
        dynamic_cast<FieldDecl*>(MD), QT, isArrow);
}

std::vector<Node*>& tool::MemberExpr::getChildren()
{
    std::vector<Node*>().swap(children);
    children.push_back(Base);
    return children;
}

std::string tool::MemberExpr::getInfo() const
{
    return Expr::getInfo() + " " + (isArrow ? "->" : ".")
        + MemberDecl->getName();
}

std::string tool::MemberExpr::getCode(int indent) const
{
    return std::string(indent, ' ') + "(" + Base->getCode() + ")"
        + (isArrow ? "->" : ".") + MemberDecl->getName();
}

bool tool::MemberExpr::isArrayRef() const
{
    return getType().isArray();
}

void tool::MemberExpr::visit(tool::Solver& solver)
{
    cout << "这不可能：MemberExpr::visit被调用" << endl;
}

Expr* tool::MemberExpr::cast2C1(Context* ctx)
{
    auto new_bs = Base->cast2C1(ctx);
    Base = nullptr;
    Deleter d(this);
    Expr* tmp = nullptr;
    if (auto ce = dynamic_cast<CastExpr*>(new_bs))
        tmp = ce->getSubExpr();
    else
        tmp = ce;
    if (auto ret = dynamic_cast<ArraySubscriptExpr*>(tmp)) {
        auto off = ctx->createInt(MemberDecl->getFieldOffset());
        if (isArrow) {
            auto ary = ctx->getAvDecl();
            return ArraySubscriptExpr::create(
                DeclRefExpr::create(ary, ary->getType()),
                BinaryOperator::createSimplified(
                    ret, off, "+", ctx
                )
            );
        }
        else {
            return ret->increaseSubscriptBy(off, ctx);
        }
    }
    cout << "转换" << *this << "时出错。" << endl;
    return this;
}

tool::RangeCopyExpr::RangeCopyExpr(VarDecl* vard, int left, int right, Expr* rexpr)
    : Expr(StmtKind::MemberExpr, rexpr->getType(), ExprValueKind::RValue),
    vard(vard), left(left), right(right), rexpr(rexpr)
{
}

tool::RangeCopyExpr::~RangeCopyExpr()
{
    safe_delete(rexpr);
}

RangeCopyExpr* tool::RangeCopyExpr::create(VarDecl* vard, int left, int right, Expr* rexpr)
{
    return new RangeCopyExpr(vard, left, right, rexpr);
}

std::vector<Node*>& tool::RangeCopyExpr::getChildren()
{
    children.clear();
    children.emplace_back(vard);
    children.emplace_back(rexpr);
    return children;
}

std::string tool::RangeCopyExpr::getInfo() const
{
    return Expr::getInfo();
}

std::string tool::RangeCopyExpr::getCode(int indent) const
{
    return string(indent, ' ') + vard->getName() 
        + "[" + to_string(left) + ":" + to_string(right) + "] = "
        + rexpr->getCode();
}

void tool::RangeCopyExpr::visit(tool::Solver& solver)
{
    solver.visit(rexpr);
    if (auto str = dynamic_cast<StrLiteral*>(rexpr)) {
        const string& s = str->getValue();
        for (int i = left, size = (int)s.size(); i < right; ++i) {
            int idx = i - left;
            if (idx < size)
                solver.assign({ vard, i }, solver.getZ3Context().int_val(s[idx]));
            else
                break;
        }
    }
    else if (auto il = dynamic_cast<InitListExpr*>(rexpr)) {
        for (int i = left, size = il->getLenth(); i < right; ++i) {
            int idx = i - left;
            if (idx < size)
                solver.assign({ vard, i }, solver.getRValue(il->at(idx)));
            else
                break;
        }
    }
    else {
        if (left < right)
            solver.assign({ vard, left }, solver.getRValue(rexpr));
    }
}

tool::StrLiteral::StrLiteral(Context* Ctx, const std::string& V)
    : Expr(StmtKind::StrLiteral, Ctx->getStrType((int)V.size()), ExprValueKind::RValue),
    value(V)
{
}

tool::StrLiteral::~StrLiteral()
{
}

StrLiteral* tool::StrLiteral::create(Context* Ctx, std::string V)
{
    return new StrLiteral(Ctx, V);
}

std::string tool::StrLiteral::getInfo() const
{
    return Expr::getInfo() + " \"" + value + '"';
}

std::string tool::StrLiteral::getCode(int indent) const
{
    return string(indent, ' ') + '"' + value + '"';
}

void tool::StrLiteral::visit(tool::Solver& solver)
{
    // TODO: should we set an exact value instead of zero?
    solver.setRValue(this, solver.getZ3Context().int_val(0));
}

const string& tool::StrLiteral::getValue() const
{
    return value;
}

bool tool::StrLiteral::isConstant() const
{
    // TODO: is a constant string constant?
    return true;
}

int tool::StrLiteral::getConstantValue() const
{
    // TODO: what value should we return?
    return 0;
}

string UnaryOperator::uop2Str(UOp op)
{
    switch (op)
    {
    case UnaryOperator::UOp::Neg:
        return "-";
    case UnaryOperator::UOp::LogicNeg:
        return "!";
    case UnaryOperator::UOp::Deref:
        return "*";
    case UnaryOperator::UOp::Ref:
        return "&";
    case UnaryOperator::UOp::Undefined:
    default:
        return "$undefined$";
    }
}

UnaryOperator::UOp UnaryOperator::str2UOp(const std::string& s)
{
    for (int i = 0; i < (int)UOp::Undefined; ++i) {
        auto res = (UOp)i;
        if (uop2Str(res) == s)
            return res;
    }
    return UOp::Undefined;
}

UnaryOperator::UnaryOperator(Expr* E, UOp op, QualType QT, ExprValueKind EVK)
    : Expr(StmtKind::UnaryOperatorExpr, QT, EVK), expr(E), op(op)
{
    if (op != UOp::Ref)
        expr = ImplicitCastExpr::cast2RvExpr(expr);
    else if (E->isRvExpr())
        throw parser_exception("\"" + E->getCode() + "\"应当是左值表达式");
}

//UnaryOperator::UnaryOperator(Expr* E, const string& s)
//    : UnaryOperator(E, str2UOp(s))
//{
//}

UnaryOperator::~UnaryOperator()
{
    safe_delete(expr);
}

UnaryOperator* UnaryOperator::create(Expr* E, UOp op, Context* Ctx)
{
    if (E->isArrayRef())
        Ctx->setPathType(2);
    E = ImplicitCastExpr::cast2ArrayPointer(E);
    QualType qt = E->getType();
    if (op == UOp::Ref)
        qt = PointerType::get(qt, 1);
    else if (op == UOp::Deref)
        qt = qt.getDirectPointeeType();
    else if (op == UOp::LogicNeg)
        qt = Ctx->getIntType();
    ExprValueKind evk = ExprValueKind::RValue;
    if (op == UOp::Deref)
        evk = ExprValueKind::LValue;
    return new UnaryOperator(E, op, qt, evk);
}

UnaryOperator* UnaryOperator::create(Expr* E, const string& s, Context* Ctx)
{
    return UnaryOperator::create(E, str2UOp(s), Ctx);
}

bool tool::UnaryOperator::isPointerOperation() const
{
    return op == UOp::Ref || op == UOp::Deref;
}

std::vector<Node*>& UnaryOperator::getChildren()
{
    return children = std::vector<Node*>({ expr });
}

std::string UnaryOperator::getInfo() const
{
    return Expr::getInfo() + " \'" + uop2Str(op) + "\'";
}

std::string UnaryOperator::getCode(int indent) const
{
    return string(indent, ' ') + uop2Str(op) + "(" + expr->getCode() + ")";
}

void UnaryOperator::visit(tool::Solver& solver)
{
    solver.visit(expr);
    switch (op)
    {
    case UnaryOperator::UOp::Neg:
        solver.setRValue(this, -solver.getRValue(expr)); break;
    case UnaryOperator::UOp::LogicNeg:
        solver.setRValue(this, !cast2bool(solver.getRValue(expr))); break;
    case UnaryOperator::UOp::Deref:
        break;
    case UnaryOperator::UOp::Ref:
        break;
    case UnaryOperator::UOp::Undefined:
    default:
        debug << "运算符" << uop2Str(op) << "不能转换为z3表达式" << tool::endL;
        break;
    }
}

Expr* tool::UnaryOperator::cast2C1(Context* ctx)
{
    expr = dynamic_cast<Expr*>(expr->cast2C1(ctx));
    auto avd = ctx->getAvDecl();
    // TODO:
    switch (op)
    {
    case tool::UnaryOperator::UOp::Deref: {
        // * : 解引用
        auto ret = ArraySubscriptExpr::create(
            DeclRefExpr::create(avd, avd->getType()), expr
        );
        expr = nullptr;
        Deleter d(this);
        return ret;
    }
    case tool::UnaryOperator::UOp::Ref: {
        // & : 取地址
        // assert(expr->isArray());
        if (auto ary = dynamic_cast<ArraySubscriptExpr*>(expr)) {
            return ary->getSubscript();
        }
        else if (auto ce = dynamic_cast<CastExpr*>(expr)) {
            auto ary = dynamic_cast<ArraySubscriptExpr*>(ce->getSubExpr());
            return ary->getSubscript();
        }
        else {
            cout << "转换" << *this << "时出错" << endl;
        }
        break;
    }
    default:
        return Expr::cast2C1(ctx);
    }
    return this;
}

ostream& tool::operator<<(ostream& os, UnaryOperator::UOp op)
{
    return (os << UnaryOperator::uop2Str(op), os);
}

void tool::Context::setPathType(int type)
{
    type = type > 0;
    if (path_type < type) {
        path_type = type;
        if (parent)
            parent->setPathType(type);
    }
}

int tool::Context::getPathType() const
{
    return path_type;
}

std::string tool::Context::getOriginalExprOfAvAddress(int addr)
{
    int len = getAvDecl()->getLenth();
    if (addr < 0 || addr >= len) {
        cout << "error: " << addr << "越界" << endl;
        return "%av[" + to_string(addr) + "]";
    }
    int s = addr;
    for (; s >= 0; --s)
        if (mapping_table.find(s) != mapping_table.end())
            break;
    int off = addr - s;
    auto vd = mapping_table[s];
    std::string ret = vd->getName();
    auto qt = vd->getType();
    while (true)
    {
        if (qt.isArray()) {
            auto et = qt.getElementType();
            int et_sz = et->getSize();
            ret += "[" + to_string(off / et_sz) + "]";
            qt = et;
            off %= et_sz;
        }
        else if (qt.isStruct()) {
            auto st = qt.getAsStruct();
            auto fd = st->getDecl()->getFieldDecl(off);
            ret += "." + fd->getName();
            qt = fd->getType();
            off -= fd->getFieldOffset();
        }
        else {
            // assert off == 0
            break;
        }
    }
    return ret;
}

tool::Context::Context(Context* parent)
    : parent(parent)
{
}

tool::Context::~Context()
{	// TODO: sort
    // 有名字的类型才会存在types中
    // decls里有vardecl，typedecl。释放typedecl时不释放对应type
    clearContext();

    for (auto& [_, d] : decls)
        // TODO: StructDecl在clearContext中已经释放
        //if (!dynamic_cast<StructDecl*>(d))
        //	safe_delete(d);
        safe_delete(d);
    decls.clear();

    for (auto& [_, t] : types)
        safe_delete(t);
    types.clear();
}

void tool::Context::clearContext()
{
    // TODO: StructDecl既在AST里，也在decls里
    for (auto i : ASTs)
        safe_delete(i);
    ASTs.clear();
}

void Context::dumpInfo()
{
    ASTs[0]->print(cout);
}

void Context::addType(NamedType* type)
{
    const string& name = type->getName();
    if (name.empty())
        debug << "can't add an nameless type !" << endL;
    else if (existsType(name))
        debug << "can't add an existed type !" << endL;
    else
        types[name] = type;
}

bool Context::existsType(const string& tname) const
{
    for (auto& i : types)
        if (i.first == tname)
            return true;
    return parent ? parent->existsType(tname) : false;
}

Type* Context::getType(const string& tname) const
{
    for (auto& i : types)
        if (i.first == tname)
            return i.second;
    if (parent)
        return parent->getType(tname);
    throw no_type_exception(tname);
}

Type* tool::Context::getCharType() const
{
    return getType("char");
}

Type* Context::getIntType() const
{
    return getType("int");
}

Type* Context::getFltType() const
{
    return getType("double");
}

Type* Context::getStrType(int lenth) const
{
    return ArrayType::get(getCharType(), lenth);
}

Type* Context::getVoidType() const
{
    return getType("void");
}

IntLiteral* Context::createInt(int v)
{
    return IntLiteral::create(this, v);
}

CharLiteral* tool::Context::createChar(int v)
{
    return CharLiteral::create(this, v);
}

StrLiteral* tool::Context::createStr(const std::string& s)
{
    return StrLiteral::create(this, s);
}

TranslationUnitDecl* Context::getAST()
{
    if (ASTs.empty()) {
        debug << "没有语法树？";
        return nullptr;
    }
    return dynamic_cast<TranslationUnitDecl*>(ASTs.front());
}

void Context::addDecl(NamedDecl* decl)
{
    if (decl->getName().empty())
        debug << "can't add an nameless decl !" << endL;
    else if (existsDeclHere(decl->getName()))
        debug << "redefinition of \"" << decl->getName() << "\" with a different type" << endL;
    else
        decls[decl->getName()] = decl;
}

bool Context::existsDecl(const string& dname) const
{
    if (existsDeclHere(dname))
        return true;
    return parent ? parent->existsDecl(dname) : false;
}

bool tool::Context::existsDeclHere(const std::string& dname) const
{
    return decls.find(dname) != decls.end();
}

NamedDecl* Context::getDecl(const string& dname) const
{
    auto i = decls.find(dname);
    if (i != decls.end())
        return dynamic_cast<NamedDecl*>(i->second);
    if (parent)
        return parent->getDecl(dname);
    debug << "can't find a declaration named \'" << dname << "\'!" << endL;
    return nullptr;
}

void Context::init_av()
{
    VarDecl* av = nullptr;
    if (av = getAvDecl()) {
        auto qt = av->getType();
        auto at = dynamic_cast<const ArrayType*>(qt.type);
        if (at)
            at->setLenth(0);
    }
    else {
        auto at = QualType(getIntType()) * 0;
        av = VarDecl::create(this, "%av", at, nullptr);
    }
    std::map<int, VarDecl*>().swap(mapping_table);
    for (auto& [_, d] : decls) {
        auto vd = dynamic_cast<VarDecl*>(d);
        if (vd && vd != av) {
            mapping_table[vd->av_adr = av->getLenth()]= vd;
            auto qt = av->getType();
            auto at = dynamic_cast<const ArrayType*>(qt.type);
            at->addLenth(vd->getSize());
        }
    }
}

VarDecl* Context::getAvDecl()
{
    return dynamic_cast<VarDecl*>(getDecl("%av"));
}

void tool::Context::cast2C1()
{
    if (path_type < 1)
        return;
    cout << "转换中..." << std::endl;
    init_av();
    getAST()->cast2C1(this);
    cout << "转换完成。" << std::endl;
}

StructDecl::StructDecl(Context* ctx, const std::string& name)
    : TypeDecl(DeclKind::Struct, ctx, name), Context(ctx)
{
    auto tmp = StructType::get(this);
    type = tmp;
    ctx->addType(tmp);
}

tool::StructDecl::~StructDecl()
{
}

StructDecl* tool::StructDecl::create(Context* ctx, const std::string& name)
{
    return new StructDecl(ctx, name);
}

std::vector<Node*>& tool::StructDecl::getChildren()
{
    auto tmp = std::vector<Node*>();
    for (auto& [_, d] : decls)
        tmp.push_back(d);
    children.swap(tmp);
    return children;
}

std::string tool::StructDecl::getCode(int indent) const
{
    std::string pre = std::string(indent, ' '), ret;
    ret += (pre + "struct " + name + " {\n");
    for (const auto fd : getFieldDecls())
        ret += fd->getCode(indent + 2) + ";\n";
    ret += (pre + "}");
    return ret;
}

void tool::StructDecl::addFieldDecl(FieldDecl* FD)
{
    addDecl(FD);
}

void tool::StructDecl::addFieldDecls(std::vector<FieldDecl*>& FDs)
{
    for (auto fd : FDs)
        addDecl(fd);
}

void tool::StructDecl::complete()
{
    completed = true;
}

bool tool::StructDecl::isCompleted() const
{
    return completed;
}

std::vector<FieldDecl*> tool::StructDecl::getFieldDecls() const
{
    auto ret = std::vector<FieldDecl*>();
    for (auto& [_, d] : decls)
        ret.push_back(dynamic_cast<FieldDecl*>(d));
    return ret;
}

FieldDecl* tool::StructDecl::getFieldDecl(const std::string& fname) const
{
    return dynamic_cast<FieldDecl*>(getDecl(fname));
}

FieldDecl* tool::StructDecl::getFieldDecl(int off) const
{
    int tot = 0;
    FieldDecl* ret = nullptr;
    for (auto& nd : decls) {
        auto fd = dynamic_cast<FieldDecl*>(nd.second);
        if (!fd) {
            cout << "warning: \'" << *nd.second << "\'不是FieldDecl" << endl;
            continue;
        }
        if (tot <= off)
            ret = fd;
        else
            break;
        tot += fd->getType().getSize();
    }
    return ret;
}

bool tool::StructDecl::existsFieldDecl(const std::string& fname) const
{
    return existsDeclHere(fname);
}

bool tool::StructDecl::isStruct() const
{
    return true;
}

int tool::StructDecl::getSize() const
{
    int ret = 0;
    for (auto fd : getFieldDecls())
        ret += fd->getType().getSize();
    return ret;
}

void tool::StructDecl::visit(tool::Solver& solver)
{
    // TODO: do nothing
    return;
}
