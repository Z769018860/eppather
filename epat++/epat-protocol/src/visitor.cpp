#include "visitor.h"
#include "debug.h"

using namespace epat;
using namespace std;

epat::Visitor::Visitor() {}

void epat::Visitor::visit(const epat::Stmt& stmt)
{
#define MY_VISIT(name)                                                                   \
    case epat::Stmt::StmtKind::name:                                                     \
        visit##name(static_cast<const name&>(stmt));                                     \
        break;
    switch (stmt.getKind()) {
        MY_VISIT(ArraySubscript)
        MY_VISIT(BinaryOperator)
        MY_VISIT(BreakStmt)
        MY_VISIT(CallExpr)
        MY_VISIT(CastExpr)
        MY_VISIT(CompoundStmt)
        MY_VISIT(ContinueStmt)
        MY_VISIT(DeclRefExpr)
        MY_VISIT(DeclStmt)
        // MY_VISIT(EmptyStmt)
        MY_VISIT(ForStmt)
        MY_VISIT(IfStmt)
        MY_VISIT(ImplicitCastExpr)
        MY_VISIT(InitListExpr)
        MY_VISIT(ChrLiteral)
        MY_VISIT(FltLiteral)
        MY_VISIT(IntLiteral)
        MY_VISIT(StrLiteral)
        MY_VISIT(MemberExpr)
        MY_VISIT(NullStmt)
        MY_VISIT(ReturnStmt)
        MY_VISIT(Root)
        MY_VISIT(SignStmt)
        MY_VISIT(SizeofExpr)
        MY_VISIT(UnaryOperator)
        MY_VISIT(WhileStmt)
#undef MY_VISIT
    case epat::Stmt::StmtKind::Undefined:
    default:
        epat_error("reach an undefined stmt:" + stmt.getCode());
    }
}

void epat::Visitor::visitArraySubscript(const epat::ArraySubscript& ary)
{
    visit(ary.getBase());
    visit(ary.getSubscript());
    processArraySubscript(ary);
}

void epat::Visitor::visitBinaryOperator(const epat::BinaryOperator& bop)
{
    visit(bop.getLeftOperand());
    visit(bop.getRightOperand());
    processBinaryOperator(bop);
}

void epat::Visitor::visitBreakStmt(const epat::BreakStmt& brk)
{
    return;
}

void epat::Visitor::visitCallExpr(const epat::CallExpr& call)
{
    // TODO: 目前不支持函数指针
    //visit(call.getCallee());
    for (auto n = call.getOperandCount(), i = 0; i != n; ++i)
        visit(call.getOperand(i));
    processCallExpr(call);
}

void epat::Visitor::visitCastExpr(const epat::CastExpr& cast)
{
    visit(cast.getSubExpr());
    processCastExpr(cast);
}

void epat::Visitor::visitCompoundStmt(const epat::CompoundStmt& comp)
{
    for (int i = 0, n = comp.getStmtCount(); i != n; ++i)
        visit(comp.getStmt(i));
    processCompoundStmt(comp);
}

void epat::Visitor::visitContinueStmt(const epat::ContinueStmt& cont)
{
    return;
}

void epat::Visitor::visitDeclRefExpr(const epat::DeclRefExpr& decl)
{
    processDeclRefExpr(decl);
}

void epat::Visitor::visitDeclStmt(const epat::DeclStmt& declstmt)
{
    // 如果是VarDecl，访问初始化表达式
    if (auto& decl = declstmt.getDecl(); decl.isVarDecl()) {
        auto& vardecl = static_cast<const VarDecl&>(decl);
        if (vardecl.hasInit())
            visit(vardecl.getInit());
        processDeclStmt(declstmt);
    }
}

void epat::Visitor::visitForStmt(const epat::ForStmt& forstmt)
{
    // XXX: 访问顺序未定
    visit(forstmt.getInit());
    visit(forstmt.getCond());
    visit(forstmt.getLoop());
    visit(forstmt.getBody());
    processForStmt(forstmt);
}

void epat::Visitor::visitIfStmt(const epat::IfStmt& ifstmt)
{
    visit(ifstmt.getCond());
    visit(ifstmt.getThen());
    visit(ifstmt.getElse());
    processIfStmt(ifstmt);
}

void epat::Visitor::visitImplicitCastExpr(const epat::ImplicitCastExpr& cast)
{
    // XXX: 目前没有独立的处理方法
    return visitCastExpr(cast);
}

void epat::Visitor::visitInitListExpr(const epat::InitListExpr& init)
{
    for (int i = 0; i < init.getInitExprCount(); ++i)
        visit(init.getInitExpr(i));
    processInitListExpr(init);
}

void epat::Visitor::visitChrLiteral(const epat::ChrLiteral& lit)
{
    processChrLiteral(lit);
}

void epat::Visitor::visitFltLiteral(const epat::FltLiteral& lit)
{
    processFltLiteral(lit);
}

void epat::Visitor::visitIntLiteral(const epat::IntLiteral& lit)
{
    processIntLiteral(lit);
}

void epat::Visitor::visitStrLiteral(const epat::StrLiteral& lit)
{
    processStrLiteral(lit);
}

void epat::Visitor::visitMemberExpr(const epat::MemberExpr& mem)
{
    visit(mem.getBase());
    // TODO: lazy implementation.
    // visit(mem.getMember());
    processMemberExpr(mem);
}

void epat::Visitor::visitNullStmt(const epat::NullStmt& null_stmt)
{
    processNullStmt(null_stmt);
}

void epat::Visitor::visitReturnStmt(const epat::ReturnStmt& ret)
{
    if (ret.hasRet())
        visit(ret.getRet());
    processReturnStmt(ret);
}

void epat::Visitor::visitRoot(const epat::Root& root)
{
    // XXX: 目前没有独立的处理方法
    visitCompoundStmt(root);
}

void epat::Visitor::visitSignStmt(const epat::SignStmt& sign)
{
    visit(sign.getCondition());
    processSignStmt(sign);
}

void epat::Visitor::visitSizeofExpr(const epat::SizeofExpr& size)
{
    processSizeofExpr(size);
}

void epat::Visitor::visitUnaryOperator(const epat::UnaryOperator& unop)
{
    visit(unop.getOperand());
    processUnaryOperator(unop);
}

void epat::Visitor::visitWhileStmt(const epat::WhileStmt& whl)
{
    visit(whl.getCondition());
    visit(whl.getBody());
    processWhileStmt(whl);
}

void epat::Visitor::processArraySubscript(const epat::ArraySubscript& ary) {}

void epat::Visitor::processBinaryOperator(const epat::BinaryOperator& bop) {}

void epat::Visitor::processBreakStmt(const epat::BreakStmt& brk) {}

void epat::Visitor::processCallExpr(const epat::CallExpr& call) {}

void epat::Visitor::processCastExpr(const epat::CastExpr& cast) {}

void epat::Visitor::processCompoundStmt(const epat::CompoundStmt& comp) {}

void epat::Visitor::processContinueStmt(const epat::ContinueStmt& cont) {}

void epat::Visitor::processDeclRefExpr(const epat::DeclRefExpr& dref) {}

void epat::Visitor::processDeclStmt(const epat::DeclStmt& decl_stmt) {}

void epat::Visitor::processForStmt(const epat::ForStmt& fstmt) {}

void epat::Visitor::processIfStmt(const epat::IfStmt& ifstmt) {}

void epat::Visitor::processImplicitCastExpr(const epat::ImplicitCastExpr& icast) {}

void epat::Visitor::processInitListExpr(const epat::InitListExpr& init) {}

void epat::Visitor::processChrLiteral(const epat::ChrLiteral& lit) {}

void epat::Visitor::processFltLiteral(const epat::FltLiteral& lit) {}

void epat::Visitor::processIntLiteral(const epat::IntLiteral& lit) {}

void epat::Visitor::processStrLiteral(const epat::StrLiteral& lit) {}

void epat::Visitor::processMemberExpr(const epat::MemberExpr& mem) {}

void epat::Visitor::processNullStmt(const epat::NullStmt& null_stmt) {}

void epat::Visitor::processReturnStmt(const epat::ReturnStmt& ret) {}

void epat::Visitor::processRoot(const epat::Root& root) {}

void epat::Visitor::processSignStmt(const epat::SignStmt& sign) {}

void epat::Visitor::processSizeofExpr(const epat::SizeofExpr& size) {}

void epat::Visitor::processUnaryOperator(const epat::UnaryOperator& uop) {}

void epat::Visitor::processWhileStmt(const epat::WhileStmt& wstmt) {}
