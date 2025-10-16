#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <vector>
#include <string>
#include <map>

#include "type.h"

namespace z3 {
    class context;
    class expr;
    class solver;
}

namespace tool {
    class Solver;
    class Driver;

    class Context;
    class Expr;
    class Stmt;

    class Node {
    protected:
        std::vector<Node*> children;
    public:
        // using iter = std::vector<Node*>::iterator;

        virtual ~Node();
        virtual std::string className() const { return "$Unknown$"; }
        virtual std::vector<Node*>& getChildren();
        void printInfo(std::ostream& os) const;
        virtual std::string getInfo() const;
        void printCode(std::ostream& os, int indent = 0) const;
        virtual std::string getCode(int indent = 0) const;

        virtual void visit(tool::Solver& solver);
        virtual int getMem();
        // virtual void exec(tool::Solver& solver);
        // virtual z3::expr* cast2z3(tool::Solver& solver);
        virtual int getAddr(tool::Solver& solver);
        // virtual iter cast2C1(tool::Solver& solver, iter it);
        virtual Node* cast2C1(Context *ctx);

        void skip(std::ostream& os, std::string prefix = "");
        void print(std::ostream& os, std::string prefix = "");
    };

    std::ostream& operator<<(std::ostream& os, Node& n);
    std::ostream& operator<<(std::ostream& os, Node* n);

    class Decl : public Node {
        friend class Context;
    public:
        enum class DeclKind {
            Field,
            Struct,
            TranslationUnit,
            Var,
            ParmVar,
            Function
        };
        static std::string DeclKind2Str(DeclKind K) {
            switch (K)
            {
            case Decl::DeclKind::Field:
                return "Field";
            case Decl::DeclKind::Struct:
                return "Struct";
            case Decl::DeclKind::TranslationUnit:
                return "TranslationUnit";
            case Decl::DeclKind::Var:
                return "Var";
            case Decl::DeclKind::ParmVar:
                return "ParmVar";
            case Decl::DeclKind::Function:
                return "Function";
            default:
                return "Undefined";
            }
        }
    protected:
        DeclKind dk;
        Context* ctx;
        Decl(DeclKind DeclKind, Context* Ctx);
    public:
        ~Decl();
        virtual std::string className() const { return "Decl"; }
        virtual std::vector<Node*>& getChildren();
        virtual std::string getCode(int indent = 0) const;

        DeclKind getDeclKind() const { return dk; }
        bool isFunction() const { return dk == DeclKind::Function; }
        Context* getContext();
    };

    class TranslationUnitDecl : public Decl {
        std::vector<Node*> children;
        TranslationUnitDecl(Context* ctx);
        ~TranslationUnitDecl();
    public:
        static TranslationUnitDecl* create(Context* ctx);
        virtual std::string className() const { return "TranslationUnitDecl"; }
        virtual std::vector<Node*>& getChildren();
        virtual std::string getCode(int indent = 0) const;

        void visit(tool::Solver& solver);
        virtual TranslationUnitDecl* cast2C1(Context* ctx);

        void push(Decl* decl);
        void push(Stmt* stmt);
    };

    class NamedDecl : public Decl {
    protected:
        std::string name;
        NamedDecl(DeclKind DeclKind, Context* Ctx, const std::string& name);
    public:
        const std::string& getName() const;
    };

    class TypeDecl : public NamedDecl {
    protected:
        Type* type = nullptr;
        TypeDecl(DeclKind DeclKind, Context* Ctx, const std::string& name, int size = 1);
    public:
        ~TypeDecl();

        virtual bool isStruct() const;
    };

    class StructDecl;

    class ValueDecl : public NamedDecl {
    protected:
        QualType type;
        ValueDecl(DeclKind DeclKind, Context* Ctx,
            const std::string& name, QualType type);
    public:
        virtual std::string getCode(int indent = 0) const;

        QualType getType() const;
    };

    class FieldDecl : public ValueDecl {
    protected:
        int offset = 0;
        FieldDecl(Context* Ctx, const std::string& name,
            const QualType& qt);
    public:
        ~FieldDecl();
        static FieldDecl* create(Context* Ctx,
            const std::string& name, const QualType QT);
        virtual std::string className() const { return "FieldDecl"; }
        virtual std::string getInfo() const;
        virtual std::string getCode(int indent = 0) const;

        int getFieldOffset() const;
        StructDecl* getParent() const;
    };

    class VarDecl : public ValueDecl {
        friend class Context;
        friend class DeclRefExpr;
        friend class DeclStmt;
        friend class Expr;
    protected:
        int av_adr = 0;
        Expr* initExpr = nullptr;
        VarDecl(Context* Ctx, const std::string& name,
            const QualType& qt, Expr* initExpr = nullptr);
    public:
        ~VarDecl();
        static VarDecl* create(Context* Ctx, const std::string& name,
            const QualType& qt, Expr* initExpr = nullptr);
        virtual std::string className() const { return "VarDecl"; }
        virtual std::vector<Node*>& getChildren();
        virtual std::string getInfo() const;
        virtual std::string getCode(int indent = 0) const;

        virtual void visit(tool::Solver& solver);

        Expr* getInitExpr() const;
        std::vector<int> getDimensions() const;
        int getLenth() const;
        int getSize() const;
        int getAvAddress() const;
    };

    class Stmt : public Node {
    protected:
        enum class StmtKind {
            ArraySubscriptExpr,
            BinaryOperator,
            CallExpr,
            CharLiteral,
            CompoundStmt,
            DeclRefExpr,
            DeclStmt,
            IfStmt,
            ImplicitCastExpr,
            IntLiteral,
            MemberExpr,
            ReturnStmt,
            SignStmt,
            FltLiteral,
            StrLiteral,
            UnaryOperatorExpr,
            Empty
        };
        StmtKind sk;
        Stmt(StmtKind StmtKind);
    public:
        static Stmt* createEmpty();

        virtual std::string className() const { return "Stmt"; }
        virtual std::string getInfo() const;
        virtual std::string getCode(int indent = 0) const;

        // virtual void exec(tool::Solver& solver);
        virtual Stmt* cast2C1(Context* ctx);
    };

    class CompoundStmt : public Stmt {
        friend class TranslationUnitDecl;
    protected:
        std::vector<Stmt*> stmts;
        CompoundStmt(std::vector<Stmt*>&& stmts = {});

        void clear();
        void swap(std::vector<Stmt*>& stmts);
    public:
        ~CompoundStmt();
        static CompoundStmt* create(std::vector<Stmt*>&& stmts);

        std::vector<Stmt*> getStmts() const;
        void addStmt(Stmt* stmt);
    };

    class DeclStmt : public Stmt {
    protected:
        std::vector<Decl*> decls;
        DeclStmt(Decl* D);
        DeclStmt(const std::vector<Decl*>& Decls);
    public:
        ~DeclStmt();
        static DeclStmt* create(Decl* D);
        static DeclStmt* create(const std::vector<Decl*>& Decls);

        virtual std::string className() const { return "DeclStmt"; }
        virtual std::vector<Node*>& getChildren();
        virtual std::string getCode(int indent = 0) const;

        virtual void visit(tool::Solver& solver);
        virtual Stmt* cast2C1(Context* ctx);
        // virtual iter cast2C1(tool::Solver& solver, iter it);
        // virtual void exec(tool::Solver& solver);
    };

    class ValueStmt : public Stmt {
    protected:
        using Stmt::Stmt;
    public:
        // virtual void exec(tool::Solver& solver);
    };

    class SignStmt : public Stmt {
    protected:
        Expr* expr;
        SignStmt(Expr* E);
    public:
        ~SignStmt();
        static SignStmt* create(Expr* E);

        virtual std::string className() const { return "SignStmt"; }
        virtual std::vector<Node*>& getChildren();
        virtual std::string getCode(int indent = 0) const;

        virtual void visit(tool::Solver& solver);
        // virtual void exec(tool::Solver& solver);
        virtual Stmt* cast2C1(Context* ctx);
    };

    class Expr : public ValueStmt {
    public:
        enum class ExprValueKind {
            LValue,
            RValue,
            XValue
        };
        static std::string ExprValueKind2Str(ExprValueKind vk);
    protected:
        QualType qt;
        ExprValueKind vk;
        Expr(StmtKind StmtKind, QualType QT, ExprValueKind EVK);
    public:
        ~Expr();
        virtual std::string className() const { return "Expr"; }
        virtual std::string getInfo() const;
        virtual Expr* cast2C1(Context* ctx);

        virtual ValueDecl* getValueDecl() const;

        bool isLvExpr() const;
        bool isRvExpr() const;
        virtual bool isArrayRef() const;
        virtual bool isArrayPointer() const;
        virtual bool isConstant() const;
        virtual int getConstantValue() const;

        QualType getType() const;
    };

    class ArraySubscriptExpr : public Expr {
        friend class UnaryOperator;
    protected:
        Expr* base, * subscript;
        int lower_bound = 0, upper_bound = 0;
        ArraySubscriptExpr(Expr* BS, Expr* SS);
    public:
        ~ArraySubscriptExpr();
        static ArraySubscriptExpr* create(Expr* BS, Expr* SS);
        ArraySubscriptExpr* increaseSubscriptBy(Expr* Delta, Context* Ctx);
        void setBound(int lower, int upper);
        void moveBound(int offset);
        Expr* getBase() const;
        Expr* getSubscript() const;

        virtual std::string className() const { return "ArraySubscriptExpr"; }
        virtual std::vector<Node*>& getChildren();
        virtual std::string getInfo() const;
        virtual std::string getCode(int indent = 0) const;
        virtual int getMem();
        virtual ValueDecl* getValueDecl() const;

        virtual void visit(tool::Solver& solver);
        // virtual z3::expr* cast2z3(tool::Solver& solver);
        virtual Expr* cast2C1(Context* ctx);
    };

    class BinaryOperator : public Expr {
    public:
        enum class BOp {
            Assign,
            Add,
            Sub,
            Mul,
            Div,
            Add_As,
            Sub_As,
            Mul_As,
            Div_As,
            Mod,
            Unequal,
            Equal,
            Greater,
            Less,
            GE,
            LE,
            LogicAnd,
            LogicOr,
            Undefined
        };
        static std::string bop2Str(BOp op);
        static BOp str2BOp(const std::string& s);
        static bool isLogicalBOp(BOp op);
        static bool isAssignmentBOp(BOp op);
    protected:
        BOp op;
        Expr* lhs, * rhs;
        BinaryOperator(Expr* LHS, Expr* RHS, BOp OP, QualType QT);
        BinaryOperator(Expr* LHS, Expr* RHS, const std::string& s, QualType QT);
    public:
        ~BinaryOperator();
        static BinaryOperator* create(Expr* LHS, Expr* RHS, BOp op, Context* Ctx);
        static BinaryOperator* create(Expr* LHS, Expr* RHS, const std::string& s, Context* Ctx);
        static Expr* createSimplified(Expr* LHS, Expr* RHS, BOp op, Context* ctx);
        static Expr* createSimplified(Expr* LHS, Expr* RHS, const std::string& s, Context* ctx);

        virtual std::string className() const { return "BinaryOperator"; }
        virtual std::vector<Node*>& getChildren();
        virtual std::string getInfo() const;
        virtual std::string getCode(int indent = 0) const;

        virtual void visit(tool::Solver& solver);
        virtual Expr* cast2C1(Context* ctx);
        // virtual z3::expr* cast2z3(tool::Solver& solver);
    };

    std::ostream& operator<<(std::ostream& os, BinaryOperator::BOp op);
    
    // TODO: incomplete class
    class CallExpr : public Expr {
        std::string callee;
    protected:
        CallExpr(StmtKind SK, QualType QT, ExprValueKind VK, const std::string& callee);
    public:
        ~CallExpr();
        static CallExpr* create(QualType QT, const std::string& callee);

        virtual std::string className() const { return "CallExpr"; }
        virtual std::vector<Node*>& getChildren();
        virtual std::string getInfo() const;
        virtual std::string getCode(int indent = 0) const;

        virtual void visit(tool::Solver& solver);
        virtual Expr* cast2C1(Context* ctx);
    };

    class CastExpr : public Expr {
    public:
        enum class CastKind {
            ArrayToPointerDecay,
            DecayedToPointer,
            IntegralToPointer,
            LValueToRValue,
            PointerToIntegral
        };
        static std::string ck2Str(CastKind ck);
    protected:
        CastKind ck;
        Expr* expr;
        CastExpr(StmtKind SK, QualType QT, ExprValueKind VK, CastKind CK, Expr* E);
    public:
        ~CastExpr();
        virtual std::string className() const { return "CastExpr"; }
        virtual std::vector<Node*>& getChildren();
        virtual std::string getInfo() const;
        virtual std::string getCode(int indent = 0) const;

        static Expr* unwrap(Expr* E);

        virtual ValueDecl* getValueDecl() const;
        virtual Expr* getSubExpr() const;
        virtual Expr* reduceSubExpr();

        virtual void visit(tool::Solver& solver);
        virtual Expr* cast2C1(Context* ctx);
        // virtual z3::expr* cast2z3(tool::Solver& solver);

        virtual bool isArrayRef() const;
        virtual bool isConstant() const;
        virtual int getConstantValue() const;
    };

    class CharLiteral : public Expr {
    protected:
        unsigned int value;
        CharLiteral(Context* Ctx, unsigned int V);
    public:
        ~CharLiteral();
        static CharLiteral* create(Context* Ctx, int V);
        virtual std::string className() const { return "CharLiteral"; }
        virtual std::string getInfo() const;
        virtual std::string getCode(int indent = 0) const;

        virtual void visit(tool::Solver& solver);

        int getValue() const;
        virtual bool isConstant() const;
        virtual int getConstantValue() const;
    };

    class DeclRefExpr : public Expr {
        friend class Expr;
    protected:
        ValueDecl* vd;
        DeclRefExpr(ValueDecl* VD, QualType QT);
    public:
        ~DeclRefExpr();
        static DeclRefExpr* create(ValueDecl* VD, QualType QT);

        virtual std::string className() const { return "DeclRefExpr"; }
        virtual std::vector<Node*>& getChildren();
        virtual std::string getInfo() const;
        virtual std::string getCode(int indent = 0) const;

        virtual void visit(tool::Solver& solver);
        virtual Expr *cast2C1(Context* ctx);
        // virtual z3::expr* cast2z3(tool::Solver& solver);

        virtual ValueDecl* getValueDecl() const;
        virtual bool isArrayRef() const;
    };

    class ImplicitCastExpr : public CastExpr {
    protected:
        ImplicitCastExpr(QualType QT, CastKind CK, Expr* expr, ExprValueKind EVK);
    public:
        virtual ~ImplicitCastExpr();
        static ImplicitCastExpr* create(QualType QT, CastKind CK, Expr* E, ExprValueKind VK);
        virtual std::string className() const { return "ImplicitCastExpr"; }

        static Expr* cast2RvExpr(Expr* expr);
        static Expr* cast2ArrayPointer(Expr* expr);
        //static Expr* castDecayed2Pointer(Expr* expr);
        static Expr* castIntegral2Pointer(Expr* expr, QualType pt);
        static Expr* castPointer2Integral(Expr* expr, QualType integral);
        static Expr* cast2(Expr* E, QualType target_type);
    };

    class InitListExpr : public Expr {
        friend class VarDecl;
    protected:
        std::vector<Expr*> init_list;
        InitListExpr(std::vector<Expr*>& init_list, QualType qt);

        void setType(QualType qt);
    public:
        ~InitListExpr();
        static InitListExpr* create(std::vector<Expr*>& init_list, QualType qt);
        virtual std::string className() const { return "InitListExpr"; }
        virtual std::vector<Node*>& getChildren();
        virtual std::string getInfo() const;
        virtual std::string getCode(int indent = 0) const;

        virtual void visit(tool::Solver& solver);
        virtual Expr* cast2C1(Context* ctx);

        int getLenth() const;
        Expr* at(int i);
    };

    class IntLiteral : public Expr {
    protected:
        int value;
        IntLiteral(Context* Ctx, int V);
    public:
        ~IntLiteral();
        static IntLiteral* create(Context* ctx, int V);
        virtual std::string className() const { return "IntLiteral"; }
        virtual std::string getInfo() const;
        virtual std::string getCode(int indent = 0) const;

        virtual void visit(tool::Solver& solver);
        // virtual z3::expr* cast2z3(tool::Solver& solver);

        int getValue() const;
        virtual bool isConstant() const;
        virtual int getConstantValue() const;
    };

    class MemberExpr :public Expr {
        bool isArrow;
        Expr* Base;
        FieldDecl* MemberDecl;
        MemberExpr(Expr* BS, FieldDecl* MD,
            QualType QT, bool isArrow);
    public:
        ~MemberExpr();
        static MemberExpr* create(Expr* BS, ValueDecl* MD,
            QualType QT, bool isArrow = false);

        virtual std::string className() const { return "MemberExpr"; }
        virtual std::vector<Node*>& getChildren();
        virtual std::string getInfo() const;
        virtual std::string getCode(int indent = 0) const;
        virtual bool isArrayRef() const;

        virtual void visit(tool::Solver& solver);
        virtual Expr* cast2C1(Context* ctx);
    };

    class RangeCopyExpr : public Expr {
    protected:
        VarDecl* vard;
        int left, right;
        Expr* rexpr;
        RangeCopyExpr(VarDecl* vard, int left, int right, Expr* rexpr);
    public:
        ~RangeCopyExpr();
        static RangeCopyExpr* create(VarDecl* vard, int left, int right, Expr* rexpr);
        virtual std::string className() const { return "RangeCopyExpr"; }
        virtual std::vector<Node*>& getChildren();
        virtual std::string getInfo() const;
        virtual std::string getCode(int indent = 0) const;

        virtual void visit(tool::Solver& solver);
    };

    class StrLiteral : public Expr {
    protected:
        std::string value;
        StrLiteral(Context* Ctx, const std::string& V);
    public:
        ~StrLiteral();
        static StrLiteral* create(Context* Ctx, std::string V);
        virtual std::string className() const { return "StrLiteral"; }
        virtual std::string getInfo() const;
        virtual std::string getCode(int indent = 0) const;

        virtual void visit(tool::Solver& solver);
        // virtual z3::expr* cast2z3(tool::Solver& solver);

        // int getValue() const;
        const std::string& getValue() const;
        virtual bool isConstant() const;
        virtual int getConstantValue() const;
    };

    class UnaryOperator : public Expr {
    public:
        enum class UOp {
            Neg,
            LogicNeg,
            Deref,
            Ref,
            Undefined
        };
        static std::string uop2Str(UOp op);
        static UOp str2UOp(const std::string& s);
    protected:
        UOp op;
        Expr* expr;
        UnaryOperator(Expr* E, UOp op, QualType QT, ExprValueKind EVK);
        //UnaryOperator(Expr* E, const std::string& s);
    public:
        ~UnaryOperator();
        static UnaryOperator* create(Expr* E, UOp op, Context* Ctx);
        static UnaryOperator* create(Expr* E, const std::string& s, Context* Ctx);
        bool isPointerOperation() const;

        virtual std::string className() const { return "UnaryOperator"; }
        virtual std::vector<Node*>& getChildren();
        virtual std::string getInfo() const;
        virtual std::string getCode(int indent = 0) const;

        virtual void visit(tool::Solver& solver);
        // virtual z3::expr* cast2z3(tool::Solver& solver);
        virtual Expr* cast2C1(Context* ctx);
    };

    std::ostream& operator<<(std::ostream& os, UnaryOperator::UOp op);

    class Context {
        friend class Driver;
        friend class Parser;
    protected:
        Context* parent = nullptr;
        std::map<std::string, Type*> types;
        std::map<std::string, Decl*> decls;
        std::map<int, VarDecl*> mapping_table;
        std::vector<Node*> ASTs;
        int path_type = 0;

        Context(Context* parent = nullptr);
        void clearContext();

    public:
        ~Context();
        virtual void dumpInfo();
        TranslationUnitDecl* getAST();
        // virtual bool isStruct() const;

        void addType(NamedType* type);
        bool existsType(const std::string& tname) const;
        Type* getType(const std::string& tname) const;
        Type* getCharType() const;
        Type* getIntType() const;
        Type* getFltType() const;
        Type* getStrType(int lenth) const;
        Type* getVoidType() const;
        void setPathType(int type);
        int getPathType() const;
        std::string getOriginalExprOfAvAddress(int addr);

        IntLiteral* createInt(int v);
        CharLiteral* createChar(int v);
        StrLiteral* createStr(const std::string& s);

        void addDecl(NamedDecl* decl);
        bool existsDecl(const std::string& dname) const;
        bool existsDeclHere(const std::string& dname) const;
        NamedDecl* getDecl(const std::string& dname) const;
        // void bindToPrev(FunctionDecl* decl);
        // FunctionDecl* getMain() const;

        void init_av();
        VarDecl* getAvDecl();
        void cast2C1();
    };

    class StructDecl : public TypeDecl, public Context {
        friend class FieldDecl;

    protected:
        int completed = false;
        StructDecl(Context* ctx, const std::string& name);
    public:
        ~StructDecl();
        static StructDecl* create(Context* ctx, const std::string& name);
        virtual std::string className() const { return "StructDecl"; }
        virtual std::vector<Node*>& getChildren();
        virtual std::string getCode(int indent = 0) const;
        virtual bool isStruct() const;

        void addFieldDecl(FieldDecl* FD);
        void addFieldDecls(std::vector<FieldDecl*>& FDs);
        void complete();
        bool isCompleted() const;
        std::vector<FieldDecl*> getFieldDecls() const;
        FieldDecl* getFieldDecl(const std::string& fname) const;
        FieldDecl* getFieldDecl(int off) const;
        bool existsFieldDecl(const std::string& fname) const;
        int getSize() const;

        virtual void visit(tool::Solver& solver);
    };
}

#endif // !EXPRESSION_H