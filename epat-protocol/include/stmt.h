// stmt.h: 头文件
// 定义了表达式
#pragma once
#ifndef _EPAT_STMT_H_
#define _EPAT_STMT_H_
#include "decl.h"
#include "node.h"
#include "type.h"
#include <iostream>
#include <map>
#include <memory>
#include <ostream>
#include <sstream>
#include <vector>

namespace epat {
    // new base class.
    class Stmt : public Node {
    public:
        using ptr = std::unique_ptr<Stmt>;
        using list = std::vector<ptr>;
        enum class StmtKind {
            ArraySubscript,
            BinaryOperator,
            BreakStmt,
            CallExpr,
            CastExpr,
            CompoundStmt,
            ContinueStmt,
            DeclRefExpr,
            DeclStmt,
            ForStmt,
            IfStmt,
            ImplicitCastExpr,
            InitListExpr,
            ChrLiteral,
            FltLiteral,
            IntLiteral,
            StrLiteral,
            MemberExpr,
            ReturnStmt,
            Root, // TODO: 名字待定
            SignStmt,
            UnaryOperator,
            WhileStmt,
            Undefined
        };
    protected:
        static inline constexpr const char* StmtKindNameList[] = {
            "ArraySubscript", "BinaryOperator", "BreakStmt",    "CallExpr",
            "CastExpr",       "CompoundStmt",   "ContinueStmt", "DeclRefExpr",
            "DeclStmt",       "ForStmt",        "IfStmt",       "ImplicitCastExpr",
            "InitListExpr",   "ChrLiteral",     "FltLiteral",   "IntLiteral",
            "StrLiteral",     "MemberExpr",     "ReturnStmt",
            "Root", // TODO: 名字待定
            "SignStmt",       "UnaryOperator",  "WhileStmt",    "Undefined"};
        static_assert(
            sizeof(StmtKindNameList) / sizeof(StmtKindNameList[0]) ==
                static_cast<int>(StmtKind::Undefined) + 1,
            "StmtKindNameList size mismatch"
        );
        StmtKind kind_;
        explicit Stmt(StmtKind kind);
    public:
        // 不允许复制
        Stmt(const Stmt&) = delete;
        virtual ~Stmt() = default;
        static const char* stmtKind2Str(StmtKind sk);
        static StmtKind str2StmtKind(std::string& str);
        inline StmtKind getStmtType() const { return kind_; };
        inline std::string getStmtTypeName() const { return stmtKind2Str(getStmtType()); }

        // Node::list getChildren() const;
        virtual std::string getAstString(std::string prefix = "") const override;
        virtual std::string getCode(int indent = 0) const override;
        inline void printAst(std::ostream& os = std::cout) const
        {
            os << getAstString() << std::endl;
        }
        inline void printCode(std::ostream& os = std::cout, int indent = 0) const
        {
            os << getCode(indent) << std::endl;
        }
    };

    class Expr : public Stmt {
    public:
        using ptr = std::unique_ptr<Expr>;
        using list = std::vector<ptr>;
        enum class ExprValueKind {
            LValue,
            RValue,
            XValue
        };
    protected:
        QualType qt_;
        ExprValueKind evk_;
        explicit Expr(
            StmtKind kind, QualType wt, ExprValueKind evk = ExprValueKind::RValue
        );
    public:
        virtual std::string getAstString(std::string prefix = "") const override;
        //virtual std::string getCode(int indent = 0) const override;
        struct constant_value {
            int value;
            bool is_const;
        };
        virtual constant_value getConstantValue() const;
        virtual int getOperatorPrecedence() const;

        virtual QualType getType() const;
        bool isLValue() const { return evk_ == ExprValueKind::LValue; };
        bool isRValue() const { return evk_ == ExprValueKind::RValue; };

        inline int getSize() const { return qt_.getSize(); }
    };

    class ArraySubscript : public Expr {
    public:
        using ptr = std::unique_ptr<ArraySubscript>;
    protected:
        Expr::ptr base_, sub_;
        explicit ArraySubscript(
            QualType wt /* write by create function */, Expr::ptr base, Expr::ptr sub
        );
    public:
        static ptr create(Expr::ptr base, Expr::ptr sub);
        virtual std::string getAstString(std::string prefix = "") const override;
        virtual std::string getCode(int indent = 0) const override;
        virtual constant_value getConstantValue() const override;
        virtual int getOperatorPrecedence() const override;
        // 获取基础表达式和下标表达式
        const Expr& getBase() const { return *base_; }
        const Expr& getSubscript() const { return *sub_; }
    };

    class BinaryOperator : public Expr {
    public:
        using ptr = std::unique_ptr<BinaryOperator>;
        enum class Bop {
            Mul,     // "*"
            Div,     // "/"
            Mod,     // "%"
            Add,     // "+"
            Sub,     // "-"
            Shl,     // "<<"
            Shr,     // ">>"
            Lt,      // "<"
            LtEq,    // "<="
            Gt,      // ">"
            GtEq,    // ">="
            Eq,      // "=="
            Neq,     // "!="
            And,     // "&"
            Xor,     // "^"
            Or,      // "|"
            LAnd,    // "&&"
            LOr,     // "||"
            Asgn,    // "="
            AddAsgn, // "+="
            SubAsgn, // "-="
            MulAsgn, // "*="
            DivAsgn, // "/="
            ModAsgn, // "%="
            ShlAsgn, // "<<="
            ShrAsgn, // ">>="
            AndAsgn, // "&="
            XorAsgn, // "^="
            OrAsgn,  // "|="
            Comma,   // ","
            Undefined
        };
    protected:
        static inline constexpr const char* BopStringList[] = {
            "*",  "/",  "%",   "+",   "-",  "<<", ">>", "<", "<=",         ">",  ">=",
            "==", "!=", "&",   "^",   "|",  "&&", "||", "=", "+=",         "-=", "*=",
            "/=", "%=", "<<=", ">>=", "&=", "^=", "|=", ",", "[undefined]"};
        static_assert(
            sizeof(BopStringList) / sizeof(BopStringList[0]) ==
                static_cast<int>(Bop::Undefined) + 1,
            "BopStringList size mismatch"
        );
        static inline constexpr int BopPrecedenceList[] = {
            3,  3,  3,  4,  4,  5,  5,  6,  6,  6,  6,  7,  7,  8,  9, 10,
            11, 12, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 15, 0};
        static_assert(
            sizeof(BopPrecedenceList) / sizeof(BopPrecedenceList[0]) ==
                static_cast<int>(Bop::Undefined) + 1,
            "BopPrecedenceList size mismatch"
        );
        Expr::ptr lhs_, rhs_;
        Bop op_;
        explicit BinaryOperator(
            QualType wt, ExprValueKind evk, Expr::ptr lhs, Expr::ptr rhs, Bop op
        );
    public:
        static ptr create(Expr::ptr lhs, Expr::ptr rhs, Bop op);
        static ptr create(Expr::ptr lhs, Expr::ptr rhs, const std::string& op);
        static const char* bop2Str(Bop op);
        static Bop str2Bop(const std::string& str);
        static int getBopPrecedence(Bop op);
        static bool isAssignOp(Bop op);
        virtual std::string getAstString(std::string prefix = "") const override;
        virtual std::string getCode(int indent = 0) const override;
        virtual constant_value getConstantValue() const override;
        virtual int getOperatorPrecedence() const override;
        inline Bop getOperator() const { return op_; }
        inline const Expr& getLeftOperand() const { return *lhs_; }
        inline const Expr& getRightOperand() const { return *rhs_; }
    };

    class BreakStmt : public Stmt {
    public:
        using ptr = std::unique_ptr<BreakStmt>;
    protected:
        explicit BreakStmt();
    public:
        static ptr create();
        // virtual std::string getAstString(std::string prefix = "") const
        // override;
        virtual std::string getCode(int indent = 0) const override;
    };

    class CallExpr : public Expr {
    public:
        using ptr = std::unique_ptr<CallExpr>;
    protected:
        Expr::ptr callee_;
        Expr::list operands_;
        explicit CallExpr(
            QualType qt, ExprValueKind evk, Expr::ptr callee, Expr::list operands
        );
    public:
        static ptr create(FunctionDecl::ptr callee, Expr::list operands);
        static ptr create(Expr::ptr callee, Expr::list operands);
        virtual std::string getAstString(std::string prefix = "") const override;
        virtual std::string getCode(int indent = 0) const override;
        virtual int getOperatorPrecedence() const override;

        const Expr& getCallee() const { return *callee_; }
        int getOperandCount() const { return (int)operands_.size(); }
        const Expr& getOperand(unsigned int idx) const { return *operands_[idx]; }
    };

    class CastExpr : public Expr {
    public:
        using ptr = std::unique_ptr<CastExpr>;
    protected:
        Expr::ptr sub_;
        QualType target_type_;
        explicit CastExpr(Expr::ptr expr, QualType target_type, ExprValueKind evk);
    public:
        static ptr create(
            Expr::ptr expr, QualType target_type,
            ExprValueKind evk = ExprValueKind::RValue
        );
        virtual std::string getAstString(std::string prefix = "") const override;
        virtual std::string getCode(int indent = 0) const override;
        virtual constant_value getConstantValue() const override;
        virtual int getOperatorPrecedence() const override;
        const Expr& getSubExpr() const { return *sub_; }
        const QualType& getTargetType() const { return target_type_; }
    };

    class CompoundStmt : public Stmt, public Context {
    public:
        using ptr = std::unique_ptr<CompoundStmt>;
    protected:
        Stmt::list stmts_;
        explicit CompoundStmt(/*Stmt::list stmts, */ Context::ref parent);
        // For the derived class
        // explicit CompoundStmt(Context::ptr parent = nullptr);
    public:
        static ptr create(/*Stmt::list stmts, */ Context::ref parent);
        virtual std::string getAstString(std::string prefix = "") const override;
        virtual std::string getCode(int indent = 0) const override;

        virtual void pushStmt(Stmt::ptr stmt);
        virtual bool addDecl(Decl::ptr decl) override;

        inline bool empty() const { return stmts_.empty(); }
        inline int getStmtCount() const { return (int)stmts_.size(); }
        inline const Stmt& getStmt(unsigned int idx) const { return *stmts_[idx]; }
        inline CompoundStmt& operator<<(Decl::ptr decl)
        {
            return this->addDecl(move(decl)), *this;
        }
        inline CompoundStmt& operator<<(Stmt::ptr stmt)
        {
            return this->pushStmt(move(stmt)), *this;
        }
    };

    // TODO: 同BreakStmt
    class ContinueStmt : public Stmt {
    public:
        using ptr = std::unique_ptr<ContinueStmt>;
    protected:
        explicit ContinueStmt();
    public:
        static ptr create();
        // virtual std::string getAstString(std::string prefix = "") const
        // override;
        virtual std::string getCode(int indent = 0) const override;
    };

    class DeclRefExpr : public Expr {
    public:
        using ptr = std::unique_ptr<DeclRefExpr>;
    protected:
        // TODO: 是否区分函数、变量等的声明？
        ValueDecl::ptr decl_;
        explicit DeclRefExpr(ValueDecl::ptr decl);
    public:
        static ptr create(ValueDecl::ptr decl);
        virtual std::string getAstString(std::string prefix = "") const override;
        virtual std::string getCode(int indent = 0) const override;
        virtual constant_value getConstantValue() const override;
        virtual int getOperatorPrecedence() const override;
        virtual QualType getType() const;
        ValueDecl::ptr getDeclPtr() const { return decl_; }
        const ValueDecl& getDecl() const { return *decl_; }
    };

    class DeclStmt : public Stmt {
    public:
        using ptr = std::unique_ptr<DeclStmt>;
    protected:
        friend class CompoundStmt;
        Decl::ptr decl_;
        explicit DeclStmt(Decl::ptr decl);
        // public:
        // DeclStmt不由用户生成
        static ptr create(Decl::ptr decl);
    public:
        virtual std::string getAstString(std::string prefix = "") const;
        virtual std::string getCode(int indent = 0) const;
        const Decl& getDecl() const { return *decl_; }
    };

    class ForStmt : public Stmt, public Context {
    public:
        using ptr = std::unique_ptr<ForStmt>;
    protected:
        Stmt::ptr init_, cond_, loop_;
        CompoundStmt::ptr body_;
        explicit ForStmt(
            Stmt::ptr init, Stmt::ptr cond, Stmt::ptr loop, CompoundStmt::ptr body
        );
    public:
        static ptr create(
            Stmt::ptr init = {}, Stmt::ptr cond = {}, Stmt::ptr loop = {},
            CompoundStmt::ptr = {}
        );
        virtual std::string getAstString(std::string prefix = "") const;
        virtual std::string getCode(int indent = 0) const;

        inline const Stmt& getInit() const { return *init_; }
        inline const Stmt& getCond() const { return *cond_; }
        inline const Stmt& getLoop() const { return *loop_; }
        inline const CompoundStmt& getBody() const { return *body_; }
    };

    // TODO: if,for,while的基类，不允许实例化
    // class CondStmt : public Stmt {
    //    ;
    //};

    class IfStmt : public Stmt {
    public:
        using ptr = std::unique_ptr<IfStmt>;
    protected:
        Expr::ptr cond_;
        Stmt::ptr then_, else_;
        explicit IfStmt(Expr::ptr cond, Stmt::ptr then, Stmt::ptr else_);
    public:
        static ptr create(Expr::ptr cond, Stmt::ptr then, Stmt::ptr _else);
        virtual std::string getAstString(std::string prefix = "") const;
        virtual std::string getCode(int indent = 0) const;

        inline const Expr& getCond() const { return *cond_; }
        inline const Stmt& getThen() const { return *then_; }
        inline bool hasElse() const { return else_.operator bool(); }
        inline const Stmt& getElse() const { return *else_; }
    };

    // TODO: 有必要区分隐式转换吗？
    class ImplicitCastExpr : public CastExpr {
    public:
        using ptr = std::unique_ptr<ImplicitCastExpr>;
        enum class CastKind {
            ArrayToPointerDecay,
            FunctionToPointerDecay,
            Undefined
        };
    protected:
        CastKind ck_;
        explicit ImplicitCastExpr(
            Expr::ptr expr, QualType target_type, ExprValueKind evk, CastKind ck
        );
    public:
        static ptr create(
            Expr::ptr expr, QualType target_type,
            ExprValueKind evk = ExprValueKind::RValue, CastKind ck = CastKind::Undefined
        );
        static Expr::ptr decay(Expr::ptr raw);
        // virtual std::string getAstString(std::string prefix = "") const override;
        virtual std::string getCode(int indent = 0) const override;
        virtual int getOperatorPrecedence() const override;
    };

    class InitListExpr : public Expr {
    public:
        using ptr = std::unique_ptr<InitListExpr>;
    protected:
        Expr::list init_list_;
        explicit InitListExpr(QualType qt, Expr::list init_list);
    public:
        static ptr create(Expr::list init_list);
        virtual std::string getAstString(std::string prefix = "") const override;
        virtual std::string getCode(int indent = 0) const override;

        inline const Expr& getInitExpr(unsigned int idx) const
        {
            return *init_list_[idx];
        }
        inline int getInitExprCount() const { return (int)init_list_.size(); }
    };

    template <typename _Ty, Stmt::StmtKind _SK> class Literal : public Expr {
    public:
        using ptr = std::unique_ptr<Literal>;
    protected:
        _Ty v_;
        explicit Literal(_Ty v)
            : Expr(_SK, BaseType::get<_Ty>(), ExprValueKind::RValue), v_(std::move(v))
        {
        }
    public:
        static ptr create(_Ty v) { return ptr(new Literal(std::move(v))); }
        virtual std::string getAstString(std::string prefix = "") const override
        {
            std::ostringstream oss;
            oss << Expr::getAstString(prefix) << ' ' << getCode();
            return oss.str();
        }
        const _Ty& getValue() const { return v_; }
    };
    class ChrLiteral : public Literal<int, Stmt::StmtKind::ChrLiteral> {
    public:
        virtual std::string getCode(int indent = 0) const override
        {
            std::ostringstream oss;
            oss << std::string(indent, ' ');
            if (0 <= v_ && v_ <= 255)
                oss << '\'' << (char)v_ << '\'';
            else
                oss << "(char)" << v_;
            return oss.str();
        }
        virtual constant_value getConstantValue() const override { return {v_, true}; }
    };
    class FltLiteral : public Literal<float, Stmt::StmtKind::FltLiteral> {
    public:
        virtual constant_value getConstantValue() const override
        {
            return {(int)v_, true};
        }
    };
    class IntLiteral : public Literal<int, Stmt::StmtKind::IntLiteral> {
    public:
        virtual constant_value getConstantValue() const override
        {
            return {(int)v_, true};
        }
    };
    class StrLiteral : public Literal<std::string, Stmt::StmtKind::StrLiteral> {
    protected:
        explicit StrLiteral(std::string v)
            : Literal<std::string, Stmt::StmtKind::StrLiteral>(move(v))
        {
            v_ += '\0';
        }
    public:
        virtual std::string getCode(int indent = 0) const override
        {
            std::ostringstream oss;
            oss << std::string(indent, ' ') << '\"' << v_ << '\"';
            return oss.str();
        }
        virtual constant_value getConstantValue() const override { return {0, false}; }
    };

    class MemberExpr : public Expr {
    public:
        using ptr = std::unique_ptr<MemberExpr>;
    protected:
        Expr::ptr base_;
        FieldDecl::ptr member_;
        bool is_arrow_;
        explicit MemberExpr(Expr::ptr base, FieldDecl::ptr member, bool is_arrow = false);
        std::string getSuffix() const;
    public:
        static ptr create(Expr::ptr base, FieldDecl::ptr member, bool is_arrow = false);
        static ptr create(
            Expr::ptr base, const StructDecl& sd, std::string member,
            bool is_arrow = false
        );
        virtual std::string getAstString(std::string prefix = "") const;
        virtual std::string getCode(int indent = 0) const;
        virtual int getOperatorPrecedence() const override;
        const Expr& getBase() const { return *base_; }
        const FieldDecl& getMember() const { return *member_; }
        bool isArrow() const { return is_arrow_; }
    };

    class ReturnStmt : public Stmt {
    public:
        using ptr = std::unique_ptr<ReturnStmt>;
    protected:
        Expr::ptr ret_;
        explicit ReturnStmt(Expr::ptr ret);
    public:
        static ptr create(Expr::ptr ret = {});
        virtual std::string getAstString(std::string prefix = "") const override;
        virtual std::string getCode(int indent = 0) const override;

        inline bool hasRet() const { return ret_.operator bool(); }
        inline const Expr& getRet() const { return *ret_; }
    };

    class Root : public CompoundStmt {
    public:
        using ptr = std::unique_ptr<Root>;
    protected:
        using CompoundStmt::CompoundStmt;
    public:
        static ptr create(/*Stmt::list stmts, */ Context::ref parent = {});
    };

    class SignStmt : public Stmt {
    public:
        using ptr = std::unique_ptr<SignStmt>;
    protected:
        Expr::ptr cond_;
        explicit SignStmt(Expr::ptr cond);
    public:
        static ptr create(Expr::ptr cond);
        virtual std::string getAstString(std::string prefix = "") const override;
        virtual std::string getCode(int indent = 0) const override;
        inline const Expr& getCondition() const { return *cond_; }
    };

    class UnaryOperator : public Expr {
    public:
        using ptr = std::unique_ptr<UnaryOperator>;
        enum class Uop {
            PreInc,   // ++
            PreDec,   // --
            Not,      // !
            Compl,    // ~
            UPlus,    // +
            UNeg,     // -
            Indirect, // *
            AddrOf,   // &
            PostInc,  // ++
            PostDec,  // --
            Undefined
        };
    protected:
        static inline constexpr const char* UopStringList[] = {
            "++", "--", "!", "~", "+", "-", "*", "&", "++", "--", "[undefined]"};
        static_assert(
            sizeof(UopStringList) / sizeof(UopStringList[0]) ==
                static_cast<int>(Uop::Undefined) + 1,
            "UopStringList size mismatch"
        );
        static inline constexpr int UopPrecedenceList[] = {2, 2, 2, 2, 2, 2,
                                                           2, 2, 1, 1, 0};
        static_assert(
            sizeof(UopPrecedenceList) / sizeof(UopPrecedenceList[0]) ==
                static_cast<int>(Uop::Undefined) + 1,
            "BopPrecedenceList size mismatch"
        );
        Expr::ptr expr_;
        Uop op_;
        explicit UnaryOperator(QualType wt, ExprValueKind evk, Expr::ptr expr, Uop op);
    public:
        static ptr create(Expr::ptr expr, Uop op);
        static ptr create(Expr::ptr expr, const std::string& op);
        static const char* uop2Str(Uop op);
        static Uop str2Uop(const std::string& str);
        static int getUopPrecedence(Uop op);
        static bool isAssignOp(Uop op);
        virtual std::string getAstString(std::string prefix = "") const override;
        virtual std::string getCode(int indent = 0) const override;
        virtual constant_value getConstantValue() const override;
        virtual int getOperatorPrecedence() const override;
        const Expr& getOperand() const { return *expr_; }
        Uop getOperator() const { return op_; }
    };

    class WhileStmt : public Stmt {
    public:
        using ptr = std::unique_ptr<WhileStmt>;
    protected:
        Expr::ptr cond_;
        Stmt::ptr body_;
        explicit WhileStmt(Expr::ptr cond, Stmt::ptr body);
    public:
        static ptr create(Expr::ptr cond, Stmt::ptr body);
        virtual std::string getAstString(std::string prefix = "") const override;
        virtual std::string getCode(int indent = 0) const override;

        const Expr& getCondition() const { return *cond_; }
        const Stmt& getBody() const { return *body_; }
    };
}

#endif // !_EPAT_STMT_H_
