// type.h: 头文件
// 定义了类型
#pragma once
#ifndef _EPAT_TYPE_H_
#define _EPAT_TYPE_H_
#include "node.h"
#include <memory>
#include <ostream>
#include <string>

namespace epat {
    class Expr;
    class QualType;
    // TODO: may need better size
    struct type_size {
        // TODO: need c++17
        // inline static int int_size = 1;
        // inline static int pointer_size = 1;
        // inline static int char_size = 1;
        enum {
            int_size = 1
        };
        enum {
            pointer_size = 1
        };
        enum {
            char_size = 1
        };
    };

    // Type基类
    class Type : public Node {
    public:
        using size_type = std::string::size_type;
        using ptr = std::shared_ptr<Type>;
        static inline constexpr const char default_name[] = "$type";
    protected:
        // size_type size_;
        // explicit Type(size_type size);
        explicit Type();
        // 将类型转化为字符串
        friend class QualType;
        struct code_info {
            std::string base, prefix, postfix;
            int is_pointer;
            explicit code_info() = default;
            explicit code_info(
                std::string base, std::string prefix, std::string postfix, int is_pointer
            )
                : base(base), prefix(prefix), postfix(postfix), is_pointer(is_pointer)
            {
            }
            code_info(const code_info&) = default;
            code_info(code_info&&) = default;
            code_info& operator=(const code_info&) = default;
            code_info& operator=(code_info&&) = default;
            // 添上括号
            inline void add_parentheses()
            {
                prefix = "(" + prefix;
                postfix += ")";
            }
            inline std::string get_code(const std::string& var_name = "") const
            {
                if (var_name.empty())
                    return base + prefix + postfix;
                else
                    return base + " " + prefix + var_name + postfix;
            }
        };
        friend class TypeDecl;
        virtual void buildCode(code_info& info) const;
    public:
        // 不允许复制
        Type(const Type&) = delete;
        virtual ~Type() = default;
        virtual std::string getAstString(std::string prefix = "") const override;
        virtual std::string getCode(int indent = 0) const override final;
        virtual QualType getElement() const = 0;
        virtual int getSize() const = 0; // TODO: 修改返回值类型
        virtual Type::ptr decay() const; // 一般返回空
    };

    // QualType用shared_ptr指向具体类型，并可以添加修饰符
    class QualType /*: public Node*/ {
    public:
        using list = std::vector<QualType>;
    protected:
        Type::ptr type_;
    public:
        explicit QualType();
        ~QualType() = default;
        explicit QualType(Type* type);
        // 允许隐式转换
        QualType(Type::ptr type);
        QualType(const QualType&) = default;
        QualType& operator=(const QualType&) = default;
        QualType(QualType&&) = default;
        QualType& operator=(QualType&&) = default;
        // TODO: before C++20
        bool operator==(const QualType&) const /* = default*/;
        explicit operator bool() const;

        // get
        std::string getAstString(std::string prefix = "") const;
        std::string getCode(int indent = 0) const;
        void buildCode(Type::code_info& info) const;
        std::string getDeclCode(std::string var_name) const;
        QualType getElement() const;
        inline int getSize() const { return type_->getSize(); }
        // 谓词
        bool isArray() const;
        bool isBasic() const;
        bool isFunction() const;
        bool isInteger() const;
        bool isPointer() const;
        bool isStruct() const;
        // 转换
        QualType decay() const;

        // TODO: 这些接口是否需要优化？
        Type::ptr& get();
        const Type::ptr& get() const;
        Type::ptr& operator->();
        const Type::ptr& operator->() const;
        // using node = WrappedNode<QualType>;
        // using node_ptr = std::unique_ptr<node>;
        inline auto getNode() const
        {
            return std::make_unique<WrappedNode<QualType>>(*this);
        }

        friend inline std::ostream& operator<<(std::ostream& os, const QualType& wt)
        {
            return os << wt->getCode();
        }
    };

    class ArrayType : public Type {
    protected:
        QualType element_;
        using ExprPtr = std::unique_ptr<Expr>;
        ExprPtr length_;
        explicit ArrayType(QualType element, ExprPtr length);
        virtual void buildCode(code_info& info) const;
    public:
        static ptr create(QualType element, ExprPtr length);
        static ptr create(QualType element, int length);
        virtual std::string getAstString(std::string prefix = "") const override;
        // virtual std::string getCode(int indent = 0) const override;
        virtual QualType getElement() const override;
        virtual int getSize() const override;
        virtual Type::ptr decay() const override;

        inline const Expr& getLength() const { return *length_; }
    };

    // 基础类型基类，基础类型为static全局变量
    class BaseType : public Type {
        using ptr = Type::ptr;
    public:
        static ptr getChar();
        static ptr getFloat();
        static ptr getInt();
        static ptr getStr();
        static ptr getVoid();
        // TODO: 只支持一部分
        template <typename _Ty> static ptr get();
    protected:
        std::string name_;
        size_type size;
        explicit BaseType(std::string name, Type::size_type size);
        virtual void buildCode(code_info& info) const;
    public:
        // static ptr create(QualType pointee);
        virtual std::string getAstString(std::string prefix = "") const override;
        // virtual std::string getCode(int indent = 0) const override;
        virtual QualType getElement() const override;
        virtual int getSize() const override;

        inline const std::string& getName() const { return name_; }
    };

    class FunctionType : public Type {
    protected:
        QualType ret_;
        QualType::list param_list_;
        FunctionType(QualType ret_type, QualType::list param_type_list);
        virtual void buildCode(code_info& info) const;
    public:
        static ptr create(QualType ret_type, QualType::list param_type_list);
        virtual std::string getAstString(std::string prefix = "") const override;
        // virtual std::string getCode(int indent = 0) const override;
        virtual QualType getElement() const override;
        virtual int getSize() const override;
        virtual Type::ptr decay() const override;
        inline void addParam(QualType param_type) { param_list_.push_back(param_type); }
    };

    class PointerType : public Type {
    public:
    protected:
        QualType pointee_;
        explicit PointerType(QualType pointee);
        virtual void buildCode(code_info& info) const;
    public:
        static ptr create(QualType pointee);
        virtual std::string getAstString(std::string prefix = "") const override;
        // virtual std::string getCode(int indent = 0) const override;
        virtual QualType getElement() const override;
        virtual int getSize() const override;
    };

    class StructDecl;
    class StructType : public Type {
    protected:
        using StructPtr = std::shared_ptr<StructDecl>;
        StructPtr decl_;
        explicit StructType(StructPtr decl);
        virtual void buildCode(code_info& info) const;
    public:
        static ptr create(StructPtr decl);
        virtual std::string getAstString(std::string prefix = "") const override;
        // virtual std::string getCode(int indent = 0) const override;
        virtual QualType getElement() const override;
        virtual int getSize() const override;

        inline const StructDecl& getStructDecl() const { return *decl_; }
        // bool operator==(const QualType&) const/* = default*/;
    };
}

#endif // !_EPAT_TYPE_H_
