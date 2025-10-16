#include "visitor.h"

using namespace epat;
using namespace std;

epat::Visitor::Visitor()
{
}

void epat::Visitor::visit(const epat::Stmt& stmt)
{
    switch (stmt.getStmtType()) {
    case epat::Stmt::StmtKind::ArraySubscript:
        return visitArraySubscript(static_cast<const ArraySubscript&>(stmt));
    case epat::Stmt::StmtKind::BinaryOperator:
        return visitBinaryOperator(static_cast<const BinaryOperator&>(stmt));
    case epat::Stmt::StmtKind::BreakStmt:
        return visitBreakStmt(static_cast<const BreakStmt&>(stmt));
    case epat::Stmt::StmtKind::CallExpr:
        return visitCallExpr(static_cast<const CallExpr&>(stmt));
    case epat::Stmt::StmtKind::CastExpr:
        return visitCastExpr(static_cast<const CastExpr&>(stmt));
    case epat::Stmt::StmtKind::CompoundStmt:
        return visitCompoundStmt(static_cast<const CompoundStmt&>(stmt));
    case epat::Stmt::StmtKind::ContinueStmt:
        return visitContinueStmt(static_cast<const ContinueStmt&>(stmt));
    case epat::Stmt::StmtKind::DeclRefExpr:
        return visitDeclRefExpr(static_cast<const DeclRefExpr&>(stmt));
    case epat::Stmt::StmtKind::DeclStmt:
        return visitDeclStmt(static_cast<const DeclStmt&>(stmt));
    case epat::Stmt::StmtKind::ForStmt:
        return visitForStmt(static_cast<const ForStmt&>(stmt));
    case epat::Stmt::StmtKind::IfStmt:
        return visitIfStmt(static_cast<const IfStmt&>(stmt));
    case epat::Stmt::StmtKind::ImplicitCastExpr:
        return visitImplicitCastExpr(static_cast<const ImplicitCastExpr&>(stmt));
    case epat::Stmt::StmtKind::InitListExpr:
        return visitInitListExpr(static_cast<const InitListExpr&>(stmt));
    case epat::Stmt::StmtKind::ChrLiteral:
        return visitChrLiteral(static_cast<const ChrLiteral&>(stmt));
    case epat::Stmt::StmtKind::FltLiteral:
        return visitFltLiteral(static_cast<const FltLiteral&>(stmt));
    case epat::Stmt::StmtKind::IntLiteral:
        return visitIntLiteral(static_cast<const IntLiteral&>(stmt));
    case epat::Stmt::StmtKind::MemberExpr:
        return visitMemberExpr(static_cast<const MemberExpr&>(stmt));
    case epat::Stmt::StmtKind::ReturnStmt:
        return visitReturnStmt(static_cast<const ReturnStmt&>(stmt));
    case epat::Stmt::StmtKind::Root:
        return visitRoot(static_cast<const Root&>(stmt));
    case epat::Stmt::StmtKind::SignStmt:
        return visitSignStmt(static_cast<const SignStmt&>(stmt));
    case epat::Stmt::StmtKind::UnaryOperator:
        return visitUnaryOperator(static_cast<const UnaryOperator&>(stmt));
    case epat::Stmt::StmtKind::WhileStmt:
        return visitWhileStmt(static_cast<const WhileStmt&>(stmt));
    case epat::Stmt::StmtKind::Undefined:
    default:
        try {
            cout << "debug: reach an undefined stmt:" << stmt.getCode() << endl;
        }
        catch (exception& e) {
            cout << "debug: there is an exception:" << e.what() << endl;
        }
        break;
    }
    return;
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
        if (vardecl.hasInit()) visit(vardecl.getInit());
        processDeclStmt(declstmt);
    }
}

void epat::Visitor::visitForStmt(const epat::ForStmt& forstmt)
{
    // TODO: 访问顺序未定
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
    // TODO: 目前没有独立的处理方法
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

void epat::Visitor::visitMemberExpr(const epat::MemberExpr& mem)
{
    visit(mem.getBase());
    // TODO: lazy implementation.
    // visit(mem.getMember());
    processMemberExpr(mem);
}

void epat::Visitor::visitReturnStmt(const epat::ReturnStmt& ret)
{
    visit(ret.getRet());
    processReturnStmt(ret);
}

void epat::Visitor::visitRoot(const epat::Root& root)
{
    // TODO: 目前没有独立的处理方法
    visitCompoundStmt(root);
}

void epat::Visitor::visitSignStmt(const epat::SignStmt& sign)
{
    visit(sign.getCondition());
    processSignStmt(sign);
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

void epat::Visitor::processArraySubscript(const epat::ArraySubscript& ary)
{
}

void epat::Visitor::processBinaryOperator(const epat::BinaryOperator& bop)
{
}

void epat::Visitor::processBreakStmt(const epat::BreakStmt& brk)
{
}

void epat::Visitor::processCallExpr(const epat::CallExpr& call)
{
}

void epat::Visitor::processCastExpr(const epat::CastExpr& cast)
{
}

void epat::Visitor::processCompoundStmt(const epat::CompoundStmt& comp)
{
}

void epat::Visitor::processContinueStmt(const epat::ContinueStmt& cont)
{
}

void epat::Visitor::processDeclRefExpr(const epat::DeclRefExpr& dref)
{
}

void epat::Visitor::processDeclStmt(const epat::DeclStmt& decl_stmt)
{
}

void epat::Visitor::processForStmt(const epat::ForStmt& fstmt)
{
}

void epat::Visitor::processIfStmt(const epat::IfStmt& ifstmt)
{
}

void epat::Visitor::processImplicitCastExpr(const epat::ImplicitCastExpr& icast)
{
}

void epat::Visitor::processInitListExpr(const epat::InitListExpr& init)
{
}

void epat::Visitor::processChrLiteral(const epat::ChrLiteral& lit)
{
}

void epat::Visitor::processFltLiteral(const epat::FltLiteral& lit)
{
}

void epat::Visitor::processIntLiteral(const epat::IntLiteral& lit)
{
}

void epat::Visitor::processMemberExpr(const epat::MemberExpr& mem)
{
}

void epat::Visitor::processReturnStmt(const epat::ReturnStmt& ret)
{
}

void epat::Visitor::processRoot(const epat::Root& root)
{
}

void epat::Visitor::processSignStmt(const epat::SignStmt& sign)
{
}

void epat::Visitor::processUnaryOperator(const epat::UnaryOperator& uop)
{
}

void epat::Visitor::processWhileStmt(const epat::WhileStmt& wstmt)
{
}
