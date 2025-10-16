#include "type.h"
#include "decl.h"
#include "stmt.h"
#include <sstream>

using namespace std;
using namespace epat;

epat::Type::Type()
{
}

void epat::Type::buildCode(code_info& info) const
{
    info = code_info{default_name, "", "", -1};
}

std::string epat::Type::getAstString(std::string prefix) const
{
    return prefix + default_name;
}

std::string epat::Type::getCode(int indent) const
{
    auto info = code_info();
    buildCode(info);
    return std::string(indent, ' ') + info.get_code();
}

epat::QualType epat::Type::getElement() const
{
    return QualType();
}

int epat::Type::getSize() const
{
    return 0;
}

Type::ptr epat::Type::decay() const
{
    return {};
}

epat::QualType::QualType() : QualType(nullptr)
{
}

epat::QualType::QualType(Type* type) : type_(type)
{
}

epat::QualType::QualType(Type::ptr type) : type_(move(type))
{
}

bool epat::QualType::operator==(const QualType& other) const
{
    return type_ == other.type_;
}

epat::QualType::operator bool() const
{
    return type_.operator bool();
}

std::string epat::QualType::getAstString(std::string prefix) const
{
    if (!type_) return prefix + Type::default_name;
    // TODO: QualType的修饰符
    return type_->getAstString(prefix);
}

std::string epat::QualType::getCode(int indent) const
{
    if (!type_) return Type::default_name;
    // TODO: QualType的修饰符
    return type_->getCode(indent);
}

void epat::QualType::buildCode(Type::code_info& info) const
{
    type_->buildCode(info);
}

std::string epat::QualType::getDeclCode(std::string var_name) const
{
    auto info = Type::code_info();
    buildCode(info);
    return info.get_code(var_name);
}

QualType epat::QualType::getElement() const
{
    if (auto ret = get()->getElement()) return ret;
    return *this;
}

bool epat::QualType::isArray() const
{
    return dynamic_cast<ArrayType*>(type_.get());
}

bool epat::QualType::isBasic() const
{
    return dynamic_cast<BaseType*>(type_.get());
}

bool epat::QualType::isFunction() const
{
    return dynamic_cast<FunctionType*>(type_.get());
}

bool epat::QualType::isInteger() const
{
    if (auto bt = dynamic_cast<BaseType*>(type_.get())) return bt->getName() == "int";
    return false;
}

bool epat::QualType::isPointer() const
{
    return dynamic_cast<StructType*>(type_.get());
}

bool epat::QualType::isStruct() const
{
    return dynamic_cast<BaseType*>(type_.get());
}

QualType epat::QualType::decay() const
{
    // TODO: 保留类型修饰
    if (auto ret = get()->decay()) return ret;
    return *this;
}

epat::Type::ptr& epat::QualType::get()
{
    return type_;
}

const epat::Type::ptr& epat::QualType::get() const
{
    return type_;
}

epat::Type::ptr& epat::QualType::operator->()
{
    return type_;
}

const epat::Type::ptr& epat::QualType::operator->() const
{
    return type_;
}

epat::ArrayType::ArrayType(QualType element, ExprPtr length)
    : Type(), element_(move(element)), length_(move(length))
{
}

void epat::ArrayType::buildCode(code_info& info) const
{
    if (info.is_pointer) info.add_parentheses();
    info.postfix += "[" + length_->getCode() + "]";
    info.is_pointer = false;
    element_.buildCode(info);
}

epat::ArrayType::ptr epat::ArrayType::create(QualType element, ExprPtr length)
{
    return ptr(new ArrayType(move(element), move(length)));
}

epat::ArrayType::ptr epat::ArrayType::create(QualType pointee, int length)
{
    return create(move(pointee), IntLiteral::create(length));
}

std::string epat::ArrayType::getAstString(std::string prefix) const
{
    auto _tmp = getElement().getNode();
    return buildAstString(
        {_tmp.get()}, Type::getAstString() + " '" + getCode() + "' ", prefix
    );
}

// std::string epat::ArrayType::getCode(int indent) const
// {
//     ostringstream oss;
//     oss << string(indent, ' ') << getElement()->getCode() << "[" << getLength() << "]";
//     return oss.str();
// }

epat::QualType epat::ArrayType::getElement() const
{
    return element_;
}

int epat::ArrayType::getSize() const
{
    auto ret = length_->getConstantValue();
    if (ret.is_const)
        return element_.get()->getSize() * ret.value;
    else
        return 0;
}

Type::ptr epat::ArrayType::decay() const
{
    return PointerType::create(getElement());
}

epat::Type::ptr epat::BaseType::getChar()
{
    static ptr _char = ptr(new BaseType("char", 1));
    return _char;
}

epat::Type::ptr epat::BaseType::getFloat()
{
    static ptr _float = ptr(new BaseType("float", 1));
    return _float;
}

epat::Type::ptr epat::BaseType::getInt()
{
    static ptr _int = ptr(new BaseType("int", 1));
    return _int;
}

epat::Type::ptr epat::BaseType::getStr()
{
    // TODO: 确定长度
    return ArrayType::create(getChar(), 20);
}

epat::Type::ptr epat::BaseType::getVoid()
{
    static ptr _void = ptr(new BaseType("void", 0));
    return _void;
}

// TODO: 更多特化
template <typename _Ty> epat::Type::ptr epat::BaseType::get()
{
    return {};
}
template <> epat::Type::ptr epat::BaseType::get<char>()
{
    return getChar();
}
template <> epat::Type::ptr epat::BaseType::get<int>()
{
    return getInt();
}
template <> epat::Type::ptr epat::BaseType::get<float>()
{
    return getFloat();
}
template <> epat::Type::ptr epat::BaseType::get<void>()
{
    return getVoid();
}

template <> epat::Type::ptr epat::BaseType::get<std::string>()
{
    return getStr();
}

epat::BaseType::BaseType(std::string name, Type::size_type size)
    : Type(), name_(move(name)), size(size)
{
}

void epat::BaseType::buildCode(code_info& info) const
{
    info.base = getName();
}

std::string epat::BaseType::getAstString(std::string prefix) const
{
    return prefix + getName();
}

// std::string epat::BaseType::getCode(int indent) const
// {
//     return string(indent, ' ') + getName();
// }

epat::QualType epat::BaseType::getElement() const
{
    return QualType();
}

int epat::BaseType::getSize() const
{
    return (int)size;
}

epat::FunctionType::FunctionType(QualType ret, QualType::list param_list)
    : Type(), ret_(move(ret)), param_list_(move(param_list))
{
}

void epat::FunctionType::buildCode(code_info& info) const
{
    if (info.is_pointer) info.add_parentheses();
    info.postfix += "(";
    bool first = true;
    for (const auto& param : param_list_) {
        if (first)
            first = false;
        else
            info.postfix += ",";
        info.postfix += param.getCode();
    }
    info.postfix += ")";
    info.is_pointer = false;
    ret_.buildCode(info);
}

epat::FunctionType::ptr epat::FunctionType::create(
    QualType ret, QualType::list param_list
)
{
    return ptr(new FunctionType(move(ret), move(param_list)));
}

std::string epat::FunctionType::getAstString(std::string prefix) const
{
    return prefix + getCode();
}

// std::string epat::FunctionType::getCode(int indent) const
// {
//     ostringstream oss;
//     oss << string(indent, ' ') << ret_.getCode() << "(";
//     int first = true;
//     for (const auto& param : param_list_) {
//         if (first) {
//             first = false;
//         }
//         else {
//             oss << ",";
//         }
//         oss << param->getCode();
//     }
//     oss << ")";
//     return oss.str();
// }

epat::QualType epat::FunctionType::getElement() const
{
    return QualType();
}

int epat::FunctionType::getSize() const
{
    return 1;
}

Type::ptr epat::FunctionType::decay() const
{
    return PointerType::create(getElement());
}

epat::PointerType::PointerType(QualType pointee) : Type(), pointee_(move(pointee))
{
}

void epat::PointerType::buildCode(code_info& info) const
{
    info.prefix = "*" + info.prefix;
    info.is_pointer = true;
    pointee_.buildCode(info);
}

epat::PointerType::ptr epat::PointerType::create(QualType pointee)
{
    return ptr(new PointerType(move(pointee)));
}

std::string epat::PointerType::getAstString(std::string prefix) const
{
    auto _tmp = getElement().getNode();
    return buildAstString(
        {_tmp.get()}, Type::getAstString() + " '" + getCode() + "'", prefix
    );
}

// std::string epat::PointerType::getCode(int indent) const
// {
//     return pointee_.getCode(indent) + "*";
// }

epat::QualType epat::PointerType::getElement() const
{
    return pointee_;
}

int epat::PointerType::getSize() const
{
    return type_size::pointer_size;
}

epat::StructType::StructType(StructDecl::ptr decl) : Type(), decl_(move(decl))
{
}

epat::StructType::ptr epat::StructType::create(StructDecl::ptr decl)
{
    return ptr(new StructType(move(decl)));
}

void epat::StructType::buildCode(code_info& info) const
{
    info.base = "struct " + decl_->getName();
}

std::string epat::StructType::getAstString(std::string prefix) const
{
    return prefix + " '" + decl_->getCode() + "'";
}

// std::string epat::StructType::getCode(int indent) const
// {
//     return std::string(indent, ' ') + "struct " + decl_->getName();
// }

epat::QualType epat::StructType::getElement() const
{
    return QualType();
}

int epat::StructType::getSize() const
{
    return decl_->getSize();
}
