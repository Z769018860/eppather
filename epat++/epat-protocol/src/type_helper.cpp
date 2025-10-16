#include "type_helper.h"

epat::QualType epat::TypeHelper::getType()
{
    if (dirty_) {
        // XXX: TypeSpecifier的组合情况复杂，目前只处理简单的情形
        // XXX: _Complex和_Atomic暂时不支持
        // 处理TypeSpecifier
        if (type_)
            ;
        else if (getTypeSpecifier(TypeSpecifier::Void))
            type_ = BaseType::getVoid();
        else if (getTypeSpecifier(TypeSpecifier::Char))
            type_ = BaseType::getChar();
        else if (getTypeSpecifier(TypeSpecifier::Short))
            type_ = BaseType::getChar();
        else if (getTypeSpecifier(TypeSpecifier::Int))
            type_ = BaseType::getInt();
        else if (getTypeSpecifier(TypeSpecifier::Long))
            type_ = BaseType::getInt();
        else if (getTypeSpecifier(TypeSpecifier::Float))
            type_ = BaseType::getFloat();
        else if (getTypeSpecifier(TypeSpecifier::Double))
            type_ = BaseType::getDouble();
        else if (getTypeSpecifier(TypeSpecifier::Signed))
            type_ = BaseType::getInt();
        else if (getTypeSpecifier(TypeSpecifier::Unsigned))
            type_ = BaseType::getInt();
        else if (getTypeSpecifier(TypeSpecifier::Bool))
            type_ = BaseType::getBool();
        // else if (getTypeSpecifier(TypeSpecifier::_Complex))
        //     type_ = BaseType::getComplex();
        // else if (getTypeSpecifier(TypeSpecifier::_Atomic))
        //     type_ = BaseType::getAtomic();
        else
            type_ = BaseType::getVoid();
        clearTypeSpecifier();
        // XXX: 处理storageClassSpecifier
        // XXX: 处理typeQualifier
        // XXX: 处理functionSpecifier
        // XXX: 处理alignmentSpecifier
        // 处理array and function
        struct afv {
            QualType qt;
            afv(QualType type) : qt(std::move(type)) {}
            void operator()(Expr::ptr&& ss)
            {
                qt = ArrayType::create(std::move(qt), std::move(ss));
            }
            void operator()(QualType::list&& parms)
            {
                qt = FunctionType::create(std::move(qt), std::move(parms));
            }
        };
        auto _afv = afv(type_);
        while (decl_stack_.size()) {
            auto [level, ds] = decl_stack_.pop();
            for (int i = 0; i < level; ++i)
                _afv.qt = PointerType::create(std::move(_afv.qt));
            while (ds.size())
                std::visit(_afv, ds.pop());
        }
        type_ = std::move(_afv.qt);
        dirty_ = false;
    }
    if (!type_) {
        std::cout << "debug: empty type, return int" << std::endl;
        return BaseType::getInt();
    }
    return type_;
}
