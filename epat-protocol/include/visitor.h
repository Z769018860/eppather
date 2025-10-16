// ast_visitor.h: 头文件
// 定义了语法树遍历类
#pragma once
#ifndef _EAPT_VISITOR_H_
#define _EAPT_VISITOR_H_
#include "stmt.h"

namespace epat {
    // 基础遍历类
    class Visitor {
    public:
        using ptr = std::unique_ptr<Visitor>;
        explicit Visitor();
        virtual ~Visitor() = default;

        virtual void visit(const epat::Stmt& stmt);

        virtual void visitArraySubscript(const epat::ArraySubscript& ary);
        virtual void visitBinaryOperator(const epat::BinaryOperator& bop);
        virtual void visitBreakStmt(const epat::BreakStmt& brk);
        virtual void visitCallExpr(const epat::CallExpr& call);
        virtual void visitCastExpr(const epat::CastExpr& cast);
        virtual void visitCompoundStmt(const epat::CompoundStmt& comp);
        virtual void visitContinueStmt(const epat::ContinueStmt& cont);
        virtual void visitDeclRefExpr(const epat::DeclRefExpr& dref);
        virtual void visitDeclStmt(const epat::DeclStmt& decl_stmt);
        virtual void visitForStmt(const epat::ForStmt& fstmt);
        virtual void visitIfStmt(const epat::IfStmt& ifstmt);
        virtual void visitImplicitCastExpr(const epat::ImplicitCastExpr& icast);
        virtual void visitInitListExpr(const epat::InitListExpr& init_list);
        // 虚函数不能带模板参数 :)
        // virtual void visitLiteral(const ast::Literal& literal);
        virtual void visitChrLiteral(const epat::ChrLiteral& lit);
        virtual void visitFltLiteral(const epat::FltLiteral& lit);
        virtual void visitIntLiteral(const epat::IntLiteral& lit);
        virtual void visitMemberExpr(const epat::MemberExpr& mem);
        virtual void visitReturnStmt(const epat::ReturnStmt& ret);
        virtual void visitRoot(const epat::Root& root);
        virtual void visitSignStmt(const epat::SignStmt& sign_stmt);
        virtual void visitUnaryOperator(const epat::UnaryOperator& uop);
        virtual void visitWhileStmt(const epat::WhileStmt& wstmt);

        // 处理节点
        virtual void processArraySubscript(const epat::ArraySubscript& ary);
        virtual void processBinaryOperator(const epat::BinaryOperator& bop);
        virtual void processBreakStmt(const epat::BreakStmt& brk);
        virtual void processCallExpr(const epat::CallExpr& call);
        virtual void processCastExpr(const epat::CastExpr& cast);
        virtual void processCompoundStmt(const epat::CompoundStmt& comp);
        virtual void processContinueStmt(const epat::ContinueStmt& cont);
        virtual void processDeclRefExpr(const epat::DeclRefExpr& dref);
        virtual void processDeclStmt(const epat::DeclStmt& decl_stmt);
        virtual void processForStmt(const epat::ForStmt& fstmt);
        virtual void processIfStmt(const epat::IfStmt& ifstmt);
        virtual void processImplicitCastExpr(const epat::ImplicitCastExpr& icast
        );
        virtual void processInitListExpr(const epat::InitListExpr& init_list);
        // 虚函数不能带模板参数 :)
        // virtual void processLiteral(const ast::Literal& literal);
        virtual void processChrLiteral(const epat::ChrLiteral& lit);
        virtual void processFltLiteral(const epat::FltLiteral& lit);
        virtual void processIntLiteral(const epat::IntLiteral& lit);
        virtual void processMemberExpr(const epat::MemberExpr& mem);
        virtual void processReturnStmt(const epat::ReturnStmt& ret);
        virtual void processRoot(const epat::Root& root);
        virtual void processSignStmt(const epat::SignStmt& sign_stmt);
        virtual void processUnaryOperator(const epat::UnaryOperator& uop);
        virtual void processWhileStmt(const epat::WhileStmt& wstmt);
    };
}

#endif // !_EAPT_VISITOR_H_
