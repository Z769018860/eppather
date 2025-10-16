// decl.h: 头文件
// 定义了声明
#pragma once
#ifndef _EPAT_DECL_H_
#define _EPAT_DECL_H_
#include "node.h"
#include "type.h"
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace epat {
    class Expr;
    class Stmt;
    class CompoundStmt;

    // TODO: 需要改为NamedDecl吗？
    class Decl : public Node {
    public:
        using ptr = std::shared_ptr<Decl>;
        using ref = std::weak_ptr<Decl>;
        enum class DeclKind {
            FieldDecl,
            FunctionDecl,
            ParmVarDecl,
            StructDecl,
            TypeDecl,
            ValueDecl, // impossible
            VarDecl,
            Undefined
        };
    protected:
        static inline constexpr const char* DeclKindNameList[] = {
            "FieldDecl", "FunctionDecl", "ParmVarDecl", "StructDecl",
            "TypeDecl",  "ValueDecl",    "VarDecl",     "Undefined"};
        static_assert(
            sizeof(DeclKindNameList) / sizeof(DeclKindNameList[0]) ==
                static_cast<int>(DeclKind::Undefined) + 1,
            "DeclKindNameList size mismatch"
        );
        DeclKind kind_;
        std::string name_;
        explicit Decl(DeclKind dk, std::string name);
    public:
        // 不允许复制
        Decl(const Decl&) = delete;
        virtual ~Decl() = default;
        static const char* declKind2Str(DeclKind dk);
        static DeclKind str2DeclKind(std::string& str);
        inline DeclKind getDeclType() const { return kind_; }
        inline std::string getDeclTypeName() const { return declKind2Str(getDeclType()); }

        const std::string& getName() const;
        virtual std::string getAstString(std::string prefix = "") const override;
        virtual std::string getCode(int indent = 0) const override;

        // 谓词
        bool isVarDecl() const;
    };

    // 仅用于继承，不允许独立实例
    class ValueDecl : public Decl {
    public:
        using ptr = std::shared_ptr<ValueDecl>;
        using ref = std::weak_ptr<ValueDecl>;
    protected:
        QualType wt_;
        explicit ValueDecl(DeclKind dk, std::string name, QualType wt);
    public:
        static ptr create(std::string name, QualType wt);
        virtual std::string getAstString(std::string prefix = "") const override;
        virtual std::string getCode(int indent = 0) const override;

        inline QualType getType() const { return wt_; }
    };

    class Context {
    public:
        using ptr = std::unique_ptr<Context>;
        using ref = Context*;
    protected:
        Context::ref parent_;
        // TODO: 需要记录孩子吗？
        // TODO: hash_map or something else
        std::map<std::string, Type::ptr> types_; // 需要吗？
        std::map<std::string, Decl::ptr> decls_;
        explicit Context(Context::ref parent = nullptr);
    public:
        virtual ~Context() = default;
        // 没有create函数，因为用户不应该创建独立的Context实例
        // static ptr create() { return {}; }
        void setParent(Context::ref ctx);
        inline Context::ref getParent() const { return parent_; }

        virtual bool addDecl(Decl::ptr decl);
        bool existsDecl(const std::string& name, bool recursively = true) const;
        Decl::ptr getDecl(const std::string& name, bool recursively = true) const;
        ValueDecl::ptr getValueDecl(const std::string& name, bool recursively = true)
            const;

        inline Context& operator<<(Decl::ptr decl)
        {
            return this->addDecl(move(decl)), *this;
        }
    };

    class ParmVarDecl : public ValueDecl {
    public:
        using ptr = std::shared_ptr<ParmVarDecl>;
        using list = std::vector<ptr>;
    protected:
        explicit ParmVarDecl(std::string name, QualType wt);
    public:
        static ptr create(std::string name, QualType qt);
        // virtual std::string getAstString(std::string prefix = "") const
        // override; virtual std::string getCode(int indent = 0) const override;
    };

    class FunctionDecl : public ValueDecl, public Context {
    public:
        using ptr = std::shared_ptr<FunctionDecl>;
    protected:
        using StmtPtr = std::unique_ptr<Stmt>;
        using StmtList = std::vector<StmtPtr>;
        using CompoundStmtPtr = std::unique_ptr<CompoundStmt>;
        QualType ret_;
        CompoundStmtPtr body_;
        ParmVarDecl::list parms_;
        explicit FunctionDecl(
            std::string name, QualType qt, QualType ret, ParmVarDecl::list parm_list,
            Context::ref parent
        );
        virtual bool addDecl(Decl::ptr decl) override;
    public:
        static ptr create(
            std::string name, QualType ret, ParmVarDecl::list parm_list = {},
            Context::ref parent = {}
        );
        virtual std::string getAstString(std::string prefix = "") const override;
        virtual std::string getCode(int indent = 0) const override;

        void addParm(ParmVarDecl::ptr parm);
        void pushStmt(StmtPtr stmt);
        inline QualType getRetType() const { return ret_; }
        inline CompoundStmt& getBody() { return *body_; }
    };

    class FieldDecl : public ValueDecl {
    public:
        // using ValueDecl::ptr;
        using ptr = std::shared_ptr<FieldDecl>;
        using list = std::vector<ptr>;
    protected:
        using ValueDecl::ValueDecl;
    public:
        static ptr create(std::string name, QualType wt);
        // virtual std::string getAstString(std::string prefix = "") const
        // override; virtual std::string getCode(int indent = 0) const override;
    };

    class StructDecl : public Decl, public Context {
    public:
        using ptr = std::shared_ptr<StructDecl>;
    protected:
        // 记录下顺序
        FieldDecl::list fields_;
        explicit StructDecl(
            std::string name, Context::ref parent /*, FieldDecl::list list = {}*/
        );
        virtual bool addDecl(Decl::ptr decl) override;
    public:
        static ptr create(
            std::string name, Context::ref parent = {} /*, FieldDecl::list list = {}*/
        );
        virtual std::string getAstString(std::string prefix = "") const override;
        virtual std::string getCode(int indent = 0) const override;

        void addField(FieldDecl::ptr field);
        FieldDecl::ptr getField(const std::string& name) const;
        int getSize() const;
    };

    class TypeDecl : public Decl {
    public:
        using ptr = std::shared_ptr<TypeDecl>;
    protected:
        // 存储Type::ptr而不是QualType
        Type::ptr type_;
        explicit TypeDecl(std::string name, Type::ptr type);
    public:
        static ptr create(std::string name, Type::ptr type);
        virtual std::string getAstString(std::string prefix = "") const override;
        virtual std::string getCode(int indent = 0) const override;

        inline Type::ptr getRawType() const { return type_; }
    };

    class VarDecl : public ValueDecl {
    public:
        using ptr = std::shared_ptr<VarDecl>;
    protected:
        using ExprPtr = std::unique_ptr<Expr>;
        ExprPtr init_;
        explicit VarDecl(std::string name, QualType wt, ExprPtr init);
    public:
        // virtual ~VarDecl();
        static ptr create(std::string name, QualType wt, ExprPtr init = {});
        virtual std::string getAstString(std::string prefix = "") const override;
        virtual std::string getCode(int indent = 0) const override;

        bool hasInit() const { return init_ != nullptr; }
        const Expr& getInit() const { return *init_; }
    };
}

#endif // !_EPAT_DECL_H_
