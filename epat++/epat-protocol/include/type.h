// type.h: 头文件
// 定义了类型
#pragma once
#ifndef _EPAT_TYPE_H_
#define _EPAT_TYPE_H_
#include "node.h"
#include <iostream>
#include <memory>
#include <ostream>
#include <string>

namespace epat {
    class Expr;
    class QualType;

    // Type基类
    class Type : public Node {
    public:
        // TODO: may need better size
        struct type_size {
            inline static int int_size = 1;
            inline static int pointer_size = 1;
            inline static int char_size = 1;
        };
        using size_type = std::string::size_type;
        using ptr = std::shared_ptr<Type>;
        using list = std::vector<ptr>;
        enum class TypeKind {
            Array,
            Base,
            Function,
            Pointer,
            Struct,
            Typedef,
            Undefined
        };
        static constexpr const char default_name[] = "$type";
    protected:
        static constexpr const char* TypeKindNameList[] = {
            "ArrayType",  "BaseType",    "FunctionType", "PointerType",
            "StructType", "TypedefType", "UndefinedType"};
        static_assert(sizeof(TypeKindNameList) / sizeof(TypeKindNameList[0]) ==
                          static_cast<int>(TypeKind::Undefined) + 1,
                      "TypeKindNameList size mismatch");
        // size_type size_;
        explicit Type();
        // 将类型转化为字符串
        friend class QualType;
        struct type_code {
            std::string base, prefix, postfix;
            int is_pointer_ = 0;
            int indent = 0, simply = false; // 缩进和是否简化
            explicit type_code() = default;
            type_code(const type_code&) = default;
            type_code(type_code&&) = default;
            type_code& operator=(const type_code&) = default;
            type_code& operator=(type_code&&) = default;
            // 添上括号
            inline void is_pointer(bool is = true)
            {
                if (is_pointer_ && !is) { // 添加括号
                    prefix = "(" + prefix;
                    postfix += ")";
                }
                else if (is) {
                    prefix = "*" + prefix;
                }
                is_pointer_ = is;
            }
            inline std::string get_code(const std::string& var_name = "") const
            {
                std::ostringstream oss;
                oss << base;
                if (prefix.size() || var_name.size() || postfix.size())
                    oss << " ";
                oss << prefix << var_name << postfix;
                return oss.str();
            }
        };
        friend class TypeDecl;
        virtual void buildCode(type_code& info) const;
    public:
        // 不允许复制
        Type(const Type&) = delete;
        virtual ~Type() = default;
        static const char* typeKind2Str(TypeKind tk);
        static TypeKind str2TypeKind(const std::string& str);
        virtual TypeKind getKind() const { return TypeKind::Undefined; }
        virtual bool operator==(const Type&) const;
        virtual bool operator!=(const Type&) const;
        virtual void printAst(std::ostream& os,
                              const std::string& prefix = "") const override;
        virtual void printCode(std::ostream& os, int indent = 0) const override;
        virtual QualType getElement() const = 0;
        virtual int getSize() const = 0; // TODO: 修改返回值类型
        // virtual Type::ptr decay() const; // 一般返回空
        virtual bool isComplete() const;
    };

    inline std::ostream& operator<<(std::ostream& os, Type::TypeKind tk)
    {
        return os << Type::typeKind2Str(tk);
    }

    // QualType用shared_ptr指向具体类型，并可以添加修饰符
    class QualType /*: public Node*/ {
    public:
        using list = std::vector<QualType>;
    protected:
        using ExprPtr = std::unique_ptr<Expr>;
        Type::ptr type_;
    public:
        explicit QualType() = default;
        ~QualType() = default;
        // 允许隐式转换
        // QualType(Type::ptr type);
        template <typename T, std::enable_if_t<std::is_base_of_v<Type, T>, int> = 0>
        QualType(std::shared_ptr<T> type) : type_(std::move(type))
        {
        }
        QualType(const QualType&) = default;
        QualType& operator=(const QualType&) = default;
        QualType(QualType&&) = default;
        QualType& operator=(QualType&&) = default;
        // TODO: before C++20
        virtual bool operator==(const QualType&) const;
        virtual bool operator!=(const QualType&) const;
        explicit operator bool() const;

        // TODO: get based on print, not the opposite
        void printAst(std::ostream& os = std::cout, const std::string& prefix = "") const;
        void printCode(std::ostream& os = std::cout, int indent = 0) const;
        std::string getAstString(const std::string& prefix = "") const;
        std::string getCode(int indent = 0) const;
        void buildCode(Type::type_code& info) const;
        std::string getDeclCode(std::string var_name, int indent = 0) const;
        QualType getElement() const;
        inline int getSize() const { return type_->getSize(); }
        list getContents(bool recursively = true) const;
        QualType getReturnType() const;
        // 谓词
        bool isArray() const;
        bool isBase() const;
        bool isBool() const;
        bool isComplete() const;
        bool isFloat() const;
        bool isFpa() const;
        bool isFunction() const;
        bool isInteger() const;
        bool isInt() const;
        bool isPointer() const;
        bool isStruct() const;
        // 转换
        QualType decay() const;

        // XXX: 这些接口是否需要优化？
        template <typename T = Type,
                  std::enable_if_t<std::is_base_of_v<Type, T>, int> = 0>
        const typename T::ptr get() const;
        template <typename T = Type,
                  std::enable_if_t<std::is_base_of_v<Type, T>, int> = 0>
        typename T::ptr get();
        Type::ptr& operator->();
        const Type::ptr& operator->() const;
        Type& operator*();
        const Type& operator*() const;
        bool operator<(const QualType& other) const { return type_ < other.type_; }

        friend inline std::ostream& operator<<(std::ostream& os, const QualType& wt)
        {
            return os << wt->getCode();
        }
    };

    class ArrayType : public Type {
    public:
        using ptr = std::shared_ptr<ArrayType>;
    protected:
        QualType element_;
        using ExprPtr = std::unique_ptr<Expr>;
        ExprPtr length_;
        explicit ArrayType(QualType element, ExprPtr length);
        virtual void buildCode(type_code& info) const override;
    public:
        virtual TypeKind getKind() const override { return TypeKind::Array; }
        virtual bool operator==(const Type& other) const override;
        static ptr create(QualType element, ExprPtr length);
        static ptr create(QualType element, int length);
        virtual void printAst(std::ostream& os,
                              const std::string& prefix = "") const override;
        virtual QualType getElement() const override;
        virtual int getSize() const override;
        // virtual Type::ptr decay() const override;
        virtual bool isComplete() const override;

        inline const Expr& getLength() const { return *length_; }
    };

    // 基础类型基类，基础类型为static全局变量
    class BaseType : public Type {
    public:
        using ptr = std::shared_ptr<BaseType>;
    public:
        static Type::ptr getBool();
        static Type::ptr getChar();
        static Type::ptr getDouble();
        static Type::ptr getFloat();
        static Type::ptr getInt();
        static Type::ptr getStr();
        static Type::ptr getVoid();
        // TODO: 只支持一部分
        template <typename _Ty> static Type::ptr get();
    protected:
        std::string name_;
        size_type size;
        explicit BaseType(std::string name, Type::size_type size);
        virtual void buildCode(type_code& info) const override;
    public:
        virtual TypeKind getKind() const override { return TypeKind::Base; }
        virtual bool operator==(const Type& other) const override;
        virtual void printAst(std::ostream& os,
                              const std::string& prefix = "") const override;
        virtual QualType getElement() const override;
        virtual int getSize() const override;
        virtual bool isComplete() const override;

        inline const std::string& getName() const { return name_; }
    };

    class FunctionType : public Type {
    public:
        using ptr = std::shared_ptr<FunctionType>;
    protected:
        QualType ret_;
        QualType::list param_list_;
        FunctionType(QualType ret_type, QualType::list param_type_list);
        virtual void buildCode(type_code& info) const override;
    public:
        virtual TypeKind getKind() const override { return TypeKind::Function; }
        virtual bool operator==(const Type& other) const override;
        static ptr create(QualType ret_type, QualType::list param_type_list);
        virtual void printAst(std::ostream& os,
                              const std::string& prefix = "") const override;
        virtual QualType getElement() const override;
        virtual int getSize() const override;
        // virtual Type::ptr decay() const override;
        virtual bool isComplete() const override;

        inline void addParam(QualType param_type) { param_list_.push_back(param_type); }
        inline QualType getReturnType() const { return ret_; }
    };

    class PointerType : public Type {
    public:
        using ptr = std::shared_ptr<PointerType>;
    protected:
        QualType pointee_;
        explicit PointerType(QualType pointee);
        virtual void buildCode(type_code& info) const override;
    public:
        virtual TypeKind getKind() const override { return TypeKind::Pointer; }
        virtual bool operator==(const Type& other) const override;
        static ptr create(QualType pointee);
        virtual void printAst(std::ostream& os,
                              const std::string& prefix = "") const override;
        virtual QualType getElement() const override;
        virtual int getSize() const override;
        virtual bool isComplete() const override;
    };

    class StructDecl;
    class StructType : public Type {
    public:
        using ptr = std::shared_ptr<StructType>;
    protected:
        using StructDeclPtr = std::shared_ptr<StructDecl>;
        StructDeclPtr decl_;
        explicit StructType(StructDeclPtr decl);
        virtual void buildCode(type_code& info) const override;
    public:
        virtual TypeKind getKind() const override { return TypeKind::Struct; }
        virtual bool operator==(const Type& other) const override;
        static ptr create(StructDeclPtr decl);
        virtual void printAst(std::ostream& os,
                              const std::string& prefix = "") const override;
        virtual QualType getElement() const override;
        virtual int getSize() const override;
        virtual bool isComplete() const override;

        inline const StructDecl& getStructDecl() const { return *decl_; }
        // bool operator==(const QualType&) const/* = default*/;
    };

    class TypeDecl;
    class TypedefType : public Type {
    public:
        using ptr = std::shared_ptr<TypedefType>;
    protected:
        using TypeDeclPtr = std::shared_ptr<TypeDecl>;
        TypeDeclPtr decl_;
        explicit TypedefType(TypeDeclPtr decl);
        virtual void buildCode(type_code& info) const override;
    public:
        virtual TypeKind getKind() const override { return TypeKind::Typedef; }
        virtual bool operator==(const Type& other) const override;
        static ptr create(TypeDeclPtr decl);
        virtual void printAst(std::ostream& os,
                              const std::string& prefix = "") const override;
        virtual QualType getElement() const override;
        virtual int getSize() const override;
        virtual bool isComplete() const override;

        inline const TypeDecl& getTypeDecl() const { return *decl_; }
        const std::string& getName() const;
        QualType getType() const;
    };

    template <typename T, std::enable_if_t<std::is_base_of_v<Type, T>, int>>
    const typename T::ptr QualType::get() const
    {
        if (auto tdt = std::dynamic_pointer_cast<TypedefType>(type_))
            return tdt->getType().get<T>();
        return std::dynamic_pointer_cast<T>(type_);
    }

    template <typename T, std::enable_if_t<std::is_base_of_v<Type, T>, int>>
    typename T::ptr QualType::get()
    {
        if (auto tdt = std::dynamic_pointer_cast<TypedefType>(type_))
            return tdt->getType().get<T>();
        return std::dynamic_pointer_cast<T>(type_);
    }
}

#endif // !_EPAT_TYPE_H_
