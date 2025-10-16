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
        static_assert(sizeof(DeclKindNameList) / sizeof(DeclKindNameList[0]) ==
                          static_cast<int>(DeclKind::Undefined) + 1,
                      "DeclKindNameList size mismatch");
        DeclKind kind_;
        std::string name_;
        explicit Decl(DeclKind dk, std::string name);
    public:
        // 不允许复制
        Decl(const Decl&) = delete;
        virtual ~Decl() = default;
        static const char* declKind2Str(DeclKind dk);
        static DeclKind str2DeclKind(const std::string& str);
        inline DeclKind getDeclKind() const { return kind_; }
        inline std::string getDeclKindName() const { return declKind2Str(getDeclKind()); }

        const std::string& getName() const;
        virtual void printAst(std::ostream& os = std::cout,
                              const std::string& prefix = "") const override;
        virtual void printCode(std::ostream& os = std::cout,
                               int indent = 0) const override;

        // 谓词
        bool isVarDecl() const;
    };

    inline std::ostream& operator<<(std::ostream& os, Decl::DeclKind dk)
    {
        return os << Decl::declKind2Str(dk);
    }

    class TypeDecl : public Decl {
    public:
        using ptr = std::shared_ptr<TypeDecl>;
    protected:
        QualType type_;
        explicit TypeDecl(std::string name, QualType type);
    public:
        static ptr create(std::string name, QualType type);
        virtual void printAst(std::ostream& os = std::cout,
                              const std::string& prefix = "") const override;
        virtual void printCode(std::ostream& os = std::cout,
                               int indent = 0) const override;

        inline const QualType& getType() const { return type_; }
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
        virtual void printAst(std::ostream& os = std::cout,
                              const std::string& prefix = "") const override;
        virtual void printCode(std::ostream& os = std::cout,
                               int indent = 0) const override;

        inline QualType getType() const { return wt_; }
    };

    class FunctionDecl;
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
        TypeDecl::ptr getTypeDecl(const std::string& name, bool recursively = true);
        ValueDecl::ptr getValueDecl(const std::string& name,
                                    bool recursively = true) const;
        using FunctionDeclPtr = std::shared_ptr<FunctionDecl>;
        FunctionDeclPtr getFunctionDecl(const std::string& name,
                                        bool recursively = true) const;

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
    };

    class FunctionDecl : public ValueDecl, public Context {
    public:
        using ptr = std::shared_ptr<FunctionDecl>;
    protected:
        using StmtPtr = std::unique_ptr<Stmt>;
        using StmtList = std::vector<StmtPtr>;
        using CompoundStmtPtr = std::unique_ptr<CompoundStmt>;
        ParmVarDecl::list parms_; // 记录顺序
        CompoundStmtPtr body_;
        bool is_implicit_ = false; // 隐式的
        explicit FunctionDecl(std::string name, QualType ft, ParmVarDecl::list parm_list,
                              Context::ref parent = {});
    public:
        static ptr create(std::string name, QualType ret, ParmVarDecl::list parm_list,
                          Context::ref parent = {});
        static ptr create(std::string name, QualType ret, QualType::list type_list,
                          Context::ref parent = {});
        static ptr createImplicit(std::string name);
        virtual void printAst(std::ostream& os = std::cout,
                              const std::string& prefix = "") const override;
        virtual void printCode(std::ostream& os = std::cout,
                               int indent = 0) const override;

        void pushStmt(StmtPtr stmt);
        void setBody(CompoundStmtPtr body);

        inline bool isDefinition() const { return body_ != nullptr; }
        inline bool isImplicit() const { return is_implicit_; }
        inline QualType getRetType() const { return getType().getReturnType(); }
        inline bool hasBody() const { return body_.operator bool(); }
        inline CompoundStmt& getBody() { return *body_; }
    };

    class StructDecl;
    class FieldDecl : public ValueDecl {
    public:
        using ptr = std::shared_ptr<FieldDecl>;
        using list = std::vector<ptr>;
    protected:
        friend class StructDecl;
        using StructDeclRef = StructDecl*;
        StructDeclRef parent_ = nullptr;
        explicit FieldDecl(std::string name, QualType qt, StructDeclRef parent);
    public:
        static ptr create(std::string name, QualType qt, StructDeclRef parent = nullptr);
        bool hasParent() const { return parent_; }
        const StructDecl& getParent() const { return *parent_; }
    };

    class StructDecl : public Decl, public Context {
    public:
        using ptr = std::shared_ptr<StructDecl>;
        using ref = StructDecl*;
    protected:
        // XXX: 记录顺序，是否有更优雅的方式？
        FieldDecl::list fields_;
        explicit StructDecl(std::string name, Context::ref parent);
        virtual bool addDecl(Decl::ptr decl) override;
    public:
        static ptr create(std::string name, Context::ref parent = {});
        virtual void printAst(std::ostream& os = std::cout,
                              const std::string& prefix = "") const override;
        virtual void printCode(std::ostream& os = std::cout,
                               int indent = 0) const override;

        void addField(FieldDecl::ptr field);
        FieldDecl::ptr getField(const std::string& name) const;
        int getSize() const;

        inline int getFieldCount() const { return (int)fields_.size(); }
        inline const FieldDecl& getField(int i) const { return *fields_[i]; }
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
        virtual void printAst(std::ostream& os = std::cout,
                              const std::string& prefix = "") const override;
        virtual void printCode(std::ostream& os = std::cout,
                               int indent = 0) const override;

        bool hasInit() const { return init_ != nullptr; }
        const Expr& getInit() const { return *init_; }
    };
}

#endif // !_EPAT_DECL_H_
