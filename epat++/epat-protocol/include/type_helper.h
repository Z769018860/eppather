// type_helper.h: 头文件
// 定义了类型助手
#pragma once
#ifndef _EPAT_TYPE_HELPER_H_
#define _EPAT_TYPE_HELPER_H_
#include "my_stack.h"
#include "stmt.h"
#include "type.h"
#include <cstring> // XXX: 改用比特数组
#include <variant>

namespace epat {
    struct TypeHelper { // TODO: pointer入栈
        // 用于处理乱序的storegeClassSpecifier,typeSpecifer,typeQualifier等
    public:
        enum class StorageClassSpecifier {
            Typedef,
            Extern,
            Static,
            Thread_local,
            Auto,
            Register,
            Undefined
        };
        enum class TypeSpecifier {
            Void,
            Char,
            Short,
            Int,
            Long,
            Float,
            Double,
            Signed,
            Unsigned,
            Bool,
            Complex,
            Atomic,
            Struct,
            Union,
            Enum,
            TypedefName,
            Undefined
        };
        enum class TypeQualifier {
            Const,
            Restrict,
            Volatile,
            Atomic,
            Undefined
        };
    private:
        QualType type_;
        bool dirty_ = false;
        // for directDeclarator
        using decl_postfix = std::variant<Expr::ptr, QualType::list>;
        using decl_postfix_stack = MyStack<decl_postfix>;
        using decl_pointer_level = int;
        using decl_pair = std::pair<decl_pointer_level, decl_postfix_stack>;
        using decl_stack = MyStack<decl_pair>;
        decl_stack decl_stack_;
        // std::bitset<(unsigned)StorageClassSpecifier::Undefined> scs_;
        int scs_[(unsigned)StorageClassSpecifier::Undefined] = {0};
        inline int getStorageClassSpecifier(StorageClassSpecifier scs) const
        {
            return scs_[(unsigned)scs];
        }
        inline void setStorageClassSpecifier(StorageClassSpecifier scs)
        {
            ++scs_[(unsigned)scs];
            dirty_ = true;
        }
        int ts_[(unsigned)TypeSpecifier::Undefined] = {0};
        inline int getTypeSpecifier(TypeSpecifier ts) const { return ts_[(unsigned)ts]; }
        inline void setTypeSpecifier(TypeSpecifier ts)
        {
            ++ts_[(unsigned)ts];
            dirty_ = true;
        }
        inline void setTypeSpecifier(TypeSpecifier ts, QualType type)
        {
            ++ts_[(unsigned)ts];
            type_ = std::move(type);
            dirty_ = true;
        }
        inline void clearTypeSpecifier() { memset(ts_, 0, sizeof(ts_)); }
        int tq_[(unsigned)TypeQualifier::Undefined] = {0};
        inline int getTypeQualifier(TypeQualifier tq) const { return tq_[(unsigned)tq]; }
        inline void setTypeQualifier(TypeQualifier tq)
        {
            ++tq_[(unsigned)tq];
            dirty_ = true;
        }
    public:
        explicit TypeHelper() = default;
        TypeHelper(const TypeHelper& other) = delete;
        TypeHelper(TypeHelper&&) noexcept = default;
        TypeHelper& operator=(const TypeHelper&) = delete;
        TypeHelper& operator=(TypeHelper&&) noexcept = default;
        TypeHelper copy()
        {
            auto qt = getType();
            auto ret = TypeHelper();
            ret.setType(std::move(qt));
            memcpy(ret.scs_, scs_, sizeof(scs_));
            memcpy(ret.ts_, ts_, sizeof(ts_));
            memcpy(ret.tq_, tq_, sizeof(tq_));
            return ret;
        }
        QualType getType();
        inline void setType(QualType type) { type_ = std::move(type); }
        // for directDeclarator
        inline void setArray(Expr::ptr subscript)
        {
            if (decl_stack_.empty())
                decl_stack_.push();
            decl_stack_.top().second.push(std::move(subscript));
            dirty_ = true;
        }
        inline void setFunction(QualType::list parms)
        {
            if (decl_stack_.empty())
                decl_stack_.push();
            decl_stack_.top().second.push(std::move(parms));
            dirty_ = true;
        }
        inline void setPointer()
        {
            if (decl_stack_.empty())
                decl_stack_.push();
            decl_stack_.top().first++;
            dirty_ = true;
        }
        inline void setParen()
        {
            decl_stack_.push();
            dirty_ = true;
        }
        inline bool isTypeDef() const
        {
            return getStorageClassSpecifier(StorageClassSpecifier::Typedef);
        }
        // storageClassSpecifier
        inline void setTypedef()
        {
            setStorageClassSpecifier(StorageClassSpecifier::Typedef);
        }
        inline void setExtern()
        {
            setStorageClassSpecifier(StorageClassSpecifier::Extern);
        }
        inline void setStatic()
        {
            setStorageClassSpecifier(StorageClassSpecifier::Static);
        }
        inline void setThreadLocal()
        {
            setStorageClassSpecifier(StorageClassSpecifier::Thread_local);
        }
        inline void setAuto() { setStorageClassSpecifier(StorageClassSpecifier::Auto); }
        inline void setRegister()
        {
            setStorageClassSpecifier(StorageClassSpecifier::Register);
        }
        // typeSpecifier
        inline void setVoid() { setTypeSpecifier(TypeSpecifier::Void); }
        inline void setChar() { setTypeSpecifier(TypeSpecifier::Char); }
        inline void setShort() { setTypeSpecifier(TypeSpecifier::Short); }
        inline void setInt() { setTypeSpecifier(TypeSpecifier::Int); }
        inline void setLong() { setTypeSpecifier(TypeSpecifier::Long); }
        inline void setFloat() { setTypeSpecifier(TypeSpecifier::Float); }
        inline void setDouble() { setTypeSpecifier(TypeSpecifier::Double); }
        inline void setSigned() { setTypeSpecifier(TypeSpecifier::Signed); }
        inline void setUnsigned() { setTypeSpecifier(TypeSpecifier::Unsigned); }
        inline void setBool() { setTypeSpecifier(TypeSpecifier::Bool); }
        inline void setComplex() { setTypeSpecifier(TypeSpecifier::Complex); }
        inline void setAtomic(QualType type)
        {
            setTypeSpecifier(TypeSpecifier::Atomic, std::move(type));
        }
        inline void setStruct(QualType type)
        {
            setTypeSpecifier(TypeSpecifier::Struct, std::move(type));
        }
        inline void setUnion(QualType type)
        {
            setTypeSpecifier(TypeSpecifier::Union, std::move(type));
        }
        inline void setEnum(QualType type)
        {
            setTypeSpecifier(TypeSpecifier::Enum, std::move(type));
        }
        inline void setTypedefName(QualType type)
        {
            setTypeSpecifier(TypeSpecifier::TypedefName, std::move(type));
        }
        // typeQualifier
        inline void setConst() { setTypeQualifier(TypeQualifier::Const); }
        inline void setRestrict() { setTypeQualifier(TypeQualifier::Restrict); }
        inline void setVolatile() { setTypeQualifier(TypeQualifier::Volatile); }
        inline void setAtomic() { setTypeQualifier(TypeQualifier::Atomic); }
    };
};

#endif // !_EPAT_TYPE_HELPER_H_
