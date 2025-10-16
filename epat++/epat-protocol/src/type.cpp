#include "type.h"
#include "decl.h"
#include "stmt.h"
#include "writer.h"
#include <set>
#include <sstream>

using namespace std;
using namespace epat;

epat::Type::Type() {}

void epat::Type::buildCode(type_code& code) const
{
    code = type_code();
    code.base = default_name;
}

const char* epat::Type::typeKind2Str(Type::TypeKind tk)
{
    return TypeKindNameList[static_cast<int>(tk)];
}

epat::Type::TypeKind epat::Type::str2TypeKind(const std::string& str)
{
    for (int i = 0; i != static_cast<int>(TypeKind::Undefined); ++i)
        if (TypeKindNameList[i] == str)
            return TypeKind(i);
    return TypeKind::Undefined;
}

bool epat::Type::operator==(const Type& other) const
{
    return this == &other;
}

bool epat::Type::operator!=(const Type& other) const
{
    return !(*this == other);
}

void epat::Type::printAst(std::ostream& os, const std::string& prefix) const
{
    os << prefix << getKind() << " '";
    printCode(os, -1);
    os << "'";
}

void epat::Type::printCode(std::ostream& os, int indent) const
{
    type_code info;
    if (indent < 0) {
        info.simply = true;
        indent = 0;
    }
    else
        info.indent = indent;
    buildCode(info);
    os << info.get_code();
}

epat::QualType epat::Type::getElement() const
{
    return QualType();
}

int epat::Type::getSize() const
{
    return 0;
}

bool epat::Type::isComplete() const
{
    return false;
}

// epat::QualType::QualType(Type::ptr type) : type_(move(type)) {}

bool epat::QualType::operator==(const QualType& other) const
{
    // XXX: 更复杂的相等情况
    if (type_ == other.type_)
        return true;
    if (!type_ || !other.type_)
        return false;
    if (type_->getKind() != other.type_->getKind())
        return false;
    return *type_ == *other.type_;
}

bool epat::QualType::operator!=(const QualType&) const
{
    return false;
}

epat::QualType::operator bool() const
{
    return type_.operator bool();
}

void epat::QualType::printAst(std::ostream& os, const std::string& prefix) const
{
    if (!type_)
        os << prefix << Type::default_name;
    else
        type_->printAst(os, prefix);
}

void epat::QualType::printCode(std::ostream& os, int indent) const
{
    if (!type_)
        os << SPACES << Type::default_name;
    else
        type_->printCode(os, indent);
}

std::string epat::QualType::getAstString(const std::string& prefix) const
{
    std::ostringstream oss;
    printAst(oss, prefix);
    return oss.str();
}

std::string epat::QualType::getCode(int indent) const
{
    std::ostringstream oss;
    printCode(oss, indent);
    return oss.str();
}

void epat::QualType::buildCode(Type::type_code& info) const
{
    // XXX: 类型限定符
    type_->buildCode(info);
}

std::string epat::QualType::getDeclCode(std::string var_name, int indent) const
{
    Type::type_code info;
    info.indent = indent;
    buildCode(info);
    return info.get_code(var_name);
}

QualType epat::QualType::getElement() const
{
    if (auto ret = get()->getElement())
        return ret;
    return *this;
}

epat::QualType::list epat::QualType::getContents(bool recursively) const
{
    if (!isComplete())
        return {};
    switch (type_->getKind()) {
    case Type::TypeKind::Base:
        return {*this};
    case Type::TypeKind::Function:
        return {*this};
    case Type::TypeKind::Pointer:
        return {*this};
    case Type::TypeKind::Struct: {
        auto ret = list{};
        auto& sd = static_cast<StructType*>(type_.get())->getStructDecl();
        for (int i = 0, n = sd.getFieldCount(); i < n; ++i) {
            if (recursively) {
                auto tmp = sd.getField(i).getType().getContents(recursively);
                ret.insert(ret.end(), tmp.begin(), tmp.end());
            }
            else
                ret.insert(ret.end(), sd.getField(i).getType());
        }
        return ret;
    }
    case Type::TypeKind::Typedef: {
        auto td = static_cast<TypedefType*>(type_.get());
        return td->getType().getContents(recursively);
    }
    case Type::TypeKind::Array:
    default:
        return {};
    }
}

QualType epat::QualType::getReturnType() const
{
    if (auto ft = get<FunctionType>())
        return ft->getReturnType();
    return *this;
}

bool epat::QualType::isArray() const
{
    return !!get<ArrayType>();
}

bool epat::QualType::isBase() const
{
    return !!get<BaseType>();
}

bool epat::QualType::isBool() const
{
    if (auto bt = get<BaseType>())
        return bt->getName() == "_Bool" || bt->getName() == "bool";
    return false;
}

bool epat::QualType::isComplete() const
{
    return type_ && type_->isComplete();
}

bool epat::QualType::isFloat() const
{
    if (auto bt = get<BaseType>())
        return bt->getName() == "float";
    return false;
}

bool epat::QualType::isFpa() const
{
    if (auto bt = get<BaseType>())
        return bt->getName() == "float" || bt->getName() == "double";
    return false;
}

bool epat::QualType::isFunction() const
{
    return !!get<FunctionType>();
}

bool epat::QualType::isInteger() const
{
    if (auto baseType = get<BaseType>()) {
        static const std::set<std::string> integer_names{"char", "short", "int", "long",
                                                         "long long"};
        if (integer_names.find(baseType->getName()) != integer_names.end())
            return true;
    }
    return false;
}

bool epat::QualType::isInt() const
{
    if (auto baseType = get<BaseType>())
        return baseType->getName() == "int";
    return false;
}

bool epat::QualType::isPointer() const
{
    return !!get<PointerType>();
}

bool epat::QualType::isStruct() const
{
    return !!get<StructType>();
}

QualType epat::QualType::decay() const
{
    QualType ret = *this;
    if (auto ft = get<FunctionType>())
        ret = PointerType::create(ret);
    else if (auto at = get<ArrayType>())
        ret = PointerType::create(at->getElement());
    return ret;
}

epat::Type::ptr& epat::QualType::operator->()
{
    return type_;
}

const epat::Type::ptr& epat::QualType::operator->() const
{
    return type_;
}

epat::Type& epat::QualType::operator*()
{
    return *type_;
}

const epat::Type& epat::QualType::operator*() const
{
    return *type_;
}

epat::ArrayType::ArrayType(QualType element, ExprPtr length)
    : Type(), element_(move(element)), length_(move(length))
{
}

void epat::ArrayType::buildCode(type_code& info) const
{
    info.is_pointer(false);
    info.postfix += "[" + (length_ ? length_->getCode() : "") + "]";
    element_.buildCode(info);
}

bool epat::ArrayType::operator==(const Type& other) const
{
    if (this == &other)
        return true;
    if (auto other_array = dynamic_cast<const ArrayType*>(&other)) {
        if (element_ != other_array->getElement())
            return false;
        auto len1 = getLength().getConstantValue(),
             len2 = other_array->getLength().getConstantValue();
        if (len1 && len2) {
            auto &tmp1 = len1.value(), &tmp2 = len2.value();
            if (holds_alternative<long long>(tmp1) && holds_alternative<long long>(tmp2))
                return get<long long>(tmp1) == get<long long>(tmp2);
        }
    }
    return false;
}

epat::ArrayType::ptr epat::ArrayType::create(QualType element, ExprPtr length)
{
    length = ImplicitCastExpr::cast2RValue(move(length));
    return ptr(new ArrayType(move(element), move(length)));
}

epat::ArrayType::ptr epat::ArrayType::create(QualType pointee, int length)
{
    return create(move(pointee), IntLiteral::create(length));
}

void epat::ArrayType::printAst(std::ostream& os, const std::string& prefix) const
{
    Type::printAst(os, prefix);
    print_tree(os, prefix, element_, length_);
}

epat::QualType epat::ArrayType::getElement() const
{
    return element_;
}

int epat::ArrayType::getSize() const
{
    auto ret = length_->getConstantValue();
    if (ret.has_value()) {
        auto& value = ret.value();
        if (holds_alternative<long long>(value))
            return (int)get<long long>(value) * getElement().getSize();
    }
    return 0;
}

bool epat::ArrayType::isComplete() const
{
    return length_->getConstantValue().has_value() && element_.isComplete();
}

epat::Type::ptr epat::BaseType::getBool()
{
    static ptr _bool = ptr(new BaseType("bool", 1));
    return _bool;
}

epat::Type::ptr epat::BaseType::getChar()
{
    static ptr _char = ptr(new BaseType("char", 1));
    return _char;
}

epat::Type::ptr epat::BaseType::getDouble()
{
    static ptr _double = ptr(new BaseType("double", 2));
    return _double;
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
template <> epat::Type::ptr epat::BaseType::get<double>()
{
    return getDouble(); // XXX: 更长的类型
}
template <> epat::Type::ptr epat::BaseType::get<long double>()
{
    return getDouble(); // XXX: 更长的类型
}
template <> epat::Type::ptr epat::BaseType::get<int>()
{
    return getInt();
}
template <> epat::Type::ptr epat::BaseType::get<long>()
{
    return getInt(); // XXX: 更长的类型
}
template <> epat::Type::ptr epat::BaseType::get<long long>()
{
    return getInt(); // XXX: 更长的类型
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

void epat::BaseType::buildCode(type_code& info) const
{
    info.base = getName();
}

bool epat::BaseType::operator==(const Type& other) const
{
    return this == &other;
}

void epat::BaseType::printAst(std::ostream& os, const std::string& prefix) const
{
    Type::printAst(os, prefix);
}

epat::QualType epat::BaseType::getElement() const
{
    return QualType();
}

int epat::BaseType::getSize() const
{
    return (int)size;
}

bool epat::BaseType::isComplete() const
{
    return true;
}

epat::FunctionType::FunctionType(QualType ret, QualType::list param_list)
    : Type(), ret_(move(ret)), param_list_(move(param_list))
{
}

void epat::FunctionType::buildCode(type_code& info) const
{
    info.is_pointer(false);
    info.postfix += "(";
    bool first = true;
    for (const auto& param : param_list_) {
        if (first)
            first = false;
        else
            info.postfix += ", ";
        info.postfix += param.getCode();
    }
    info.postfix += ")";
    ret_.buildCode(info);
}

bool epat::FunctionType::operator==(const Type& other) const
{
    if (this == &other)
        return true;
    if (auto f = dynamic_cast<const FunctionType*>(&other)) {
        if (ret_ != f->ret_)
            return false;
        auto n = param_list_.size();
        if (f->param_list_.size() != n)
            return false;
        for (int i = 0; i < n; ++i)
            if (param_list_[i] != f->param_list_[i])
                return false;
        return true;
    }
    return false;
}

epat::FunctionType::ptr epat::FunctionType::create(QualType ret,
                                                   QualType::list param_list)
{
    return ptr(new FunctionType(move(ret), move(param_list)));
}

void epat::FunctionType::printAst(std::ostream& os, const std::string& prefix) const
{
    Type::printAst(os, prefix);
    print_tree(os, prefix, ret_, param_list_);
}

epat::QualType epat::FunctionType::getElement() const
{
    return QualType();
}

int epat::FunctionType::getSize() const
{
    return 1;
}

// Type::ptr epat::FunctionType::decay() const
// {
//     return PointerType::create(getElement());
// }

bool epat::FunctionType::isComplete() const
{
    return false;
}

epat::PointerType::PointerType(QualType pointee) : Type(), pointee_(move(pointee)) {}

void epat::PointerType::buildCode(type_code& info) const
{
    info.is_pointer(true);
    pointee_.buildCode(info);
}

bool epat::PointerType::operator==(const Type& other) const
{
    if (this == &other)
        return true;
    if (auto p = dynamic_cast<const PointerType*>(&other))
        return pointee_ == p->pointee_;
    return false;
}

epat::PointerType::ptr epat::PointerType::create(QualType pointee)
{
    return ptr(new PointerType(move(pointee)));
}

void epat::PointerType::printAst(std::ostream& os, const std::string& prefix) const
{
    Type::printAst(os, prefix);
    print_tree(os, prefix, pointee_);
}

epat::QualType epat::PointerType::getElement() const
{
    return pointee_;
}

int epat::PointerType::getSize() const
{
    // return type_size::pointer_size;
    return 1;
}

bool epat::PointerType::isComplete() const
{
    return true;
}

epat::StructType::StructType(StructDeclPtr decl) : Type(), decl_(move(decl)) {}

void epat::StructType::buildCode(type_code& info) const
{
    auto& name = decl_->getName();
    if (info.simply) {
        info.base = "struct " + (name.empty() ? "$unnamed" : name);
    }
    else {
        if (name.empty())
            info.base = decl_->getCode(info.indent);
        else
            info.base = "struct " + decl_->getName();
    }
}

bool epat::StructType::operator==(const Type& other) const
{
    if (this == &other)
        return true;
    if (auto s = dynamic_cast<const StructType*>(&other))
        return decl_ == s->decl_;
    return false;
}

epat::StructType::ptr epat::StructType::create(StructDeclPtr decl)
{
    return ptr(new StructType(move(decl)));
}

void epat::StructType::printAst(std::ostream& os, const std::string& prefix) const
{
    Type::printAst(os, prefix);
}

epat::QualType epat::StructType::getElement() const
{
    return QualType();
}

int epat::StructType::getSize() const
{
    return decl_->getSize();
}

bool epat::StructType::isComplete() const
{
    // TODO: 声明时不完整，定义后完整
    return true;
}

epat::TypedefType::TypedefType(TypeDeclPtr decl) : Type(), decl_(move(decl)) {}

void epat::TypedefType::buildCode(type_code& info) const
{
    auto& name = decl_->getName();
    if (info.simply) {
        // TODO: 打印原本的类型
        info.base = name;
    }
    else {
        info.base = name;
    }
}

bool epat::TypedefType::operator==(const Type& other) const
{
    // XXX: 更复杂的相等情况
    if (this == &other)
        return true;
    if (auto t = dynamic_cast<const TypedefType*>(&other))
        return decl_ == t->decl_;
    return false;
}

epat::TypedefType::ptr epat::TypedefType::create(TypeDeclPtr decl)
{
    return ptr(new TypedefType(move(decl)));
}

void epat::TypedefType::printAst(std::ostream& os, const std::string& prefix) const
{
    Type::printAst(os, prefix);
}

epat::QualType epat::TypedefType::getElement() const
{
    return getType().getElement();
}

int epat::TypedefType::getSize() const
{
    return getType().getSize();
}

bool epat::TypedefType::isComplete() const
{
    return getType().isComplete();
}

const std::string& epat::TypedefType::getName() const
{
    return decl_->getName();
}

QualType epat::TypedefType::getType() const
{
    return decl_->getType();
}
