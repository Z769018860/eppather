#include "decl.h"
#include "stmt.h"
#include <ostream>
#include <sstream>

using namespace epat;
using namespace std;

epat::Decl::Decl(DeclKind dk, std::string name) : kind_(dk), name_(move(name))
{
}

const char* epat::Decl::declKind2Str(DeclKind dk)
{
    return DeclKindNameList[static_cast<int>(dk)];
}

epat::Decl::DeclKind epat::Decl::str2DeclKind(std::string& str)
{
    for (int i = 0; i != static_cast<int>(DeclKind::Undefined); ++i)
        if (DeclKindNameList[i] == str) return DeclKind(i);
    return DeclKind::Undefined;
}

const std::string& epat::Decl::getName() const
{
    return name_;
}

std::string epat::Decl::getAstString(std::string prefix) const
{
    return prefix + getDeclTypeName() + " " + getName();
}

std::string epat::Decl::getCode(int indent) const
{
    return string(indent, ' ') + "$Decl";
}

bool epat::Decl::isVarDecl() const
{
    return kind_ == DeclKind::VarDecl;
}

epat::ValueDecl::ValueDecl(DeclKind dk, std::string name, QualType wt)
    : Decl(dk, move(name)), wt_(move(wt))
{
}

epat::ValueDecl::ptr epat::ValueDecl::create(std::string name, QualType wt)
{
    return ptr(new ValueDecl(DeclKind::ValueDecl, move(name), move(wt)));
}

std::string epat::ValueDecl::getAstString(std::string prefix) const
{
    return Decl::getAstString(prefix) + " '" + getType().getCode() + "'";
}

std::string epat::ValueDecl::getCode(int indent) const
{
    return std::string(indent, ' ') + getType().getDeclCode(getName());
}

epat::Context::Context(Context::ref parent) : parent_(parent)
{
}

void epat::Context::setParent(Context::ref parent)
{
    // TODO: 是否修改parent
    if (parent == parent_) return;
    parent_ = parent;
}

bool epat::Context::addDecl(Decl::ptr decl)
{
    if (!decl) return false;
    const auto& name = decl->getName();
    if (auto it = decls_.find(name); it != decls_.end()) {
        cout << "warning: a declaration with the name \"" << name << "\" already exists!"
             << endl;
        return false;
    }
    else {
        if (auto ctx = dynamic_cast<Context*>(decl.get())) ctx->setParent(this);
        decls_[name] = move(decl);
    }
    return true;
}

bool epat::Context::existsDecl(const std::string& name, bool recursively) const
{
    if (auto it = decls_.find(name); it != decls_.end()) return true;
    return parent_ ? parent_->existsDecl(name, recursively) : false;
}

epat::Decl::ptr epat::Context::getDecl(const std::string& name, bool recursively) const
{
    if (auto it = decls_.find(name); it != decls_.end()) return it->second;
    return parent_ ? parent_->getDecl(name, recursively) : nullptr;
}

ValueDecl::ptr epat::Context::getValueDecl(const std::string& name, bool recursively)
    const
{
    return dynamic_pointer_cast<ValueDecl>(getDecl(name, recursively));
}

epat::ParmVarDecl::ParmVarDecl(std::string name, QualType qt)
    : ValueDecl(DeclKind::ParmVarDecl, move(name), move(qt))
{
}

epat::ParmVarDecl::ptr epat::ParmVarDecl::create(std::string name, QualType qt)
{
    return ptr(new ParmVarDecl(move(name), move(qt)));
}

epat::FunctionDecl::FunctionDecl(
    std::string name, QualType qt, QualType ret, ParmVarDecl::list parm_list,
    Context::ref parent
)
    : ValueDecl(DeclKind::FunctionDecl, move(name), move(qt)), Context(parent),
      ret_(move(ret)), parms_(move(parm_list))
{
    body_ = CompoundStmt::create(this);
}

bool epat::FunctionDecl::addDecl(Decl::ptr decl)
{
    if (!decl) return false;
    // TODO: 用static_pointer_cast没问题吧？
    if (Context::addDecl(decl)) {
        parms_.push_back(dynamic_pointer_cast<ParmVarDecl>(decl));
        auto qt = getType();
        if (qt.isFunction()) {
            auto ft = static_pointer_cast<FunctionType>(qt.get());
            if (auto vd = dynamic_pointer_cast<ValueDecl>(decl))
                ft->addParam(vd->getType());
        }
        return true;
    }
    return false;
}

epat::FunctionDecl::ptr epat::FunctionDecl::create(
    std::string name, QualType ret, ParmVarDecl::list parm_list, Context::ref parent
)
{
    QualType::list parm_type_list;
    for (const auto& parm : parm_list)
        parm_type_list.push_back(parm->getType());
    auto ft = FunctionType::create(ret, move(parm_type_list));
    return ptr(new FunctionDecl(move(name), move(ft), move(ret), move(parm_list), parent)
    );
}

std::string epat::FunctionDecl::getAstString(std::string prefix) const
{
    Node::list children;
    for (const auto& parm : parms_)
        children.emplace_back(parm.get());
    children.emplace_back(body_.get());
    return buildAstString(move(children), ValueDecl::getAstString(), move(prefix));
}

std::string epat::FunctionDecl::getCode(int indent) const
{
    ostringstream oss;
    oss << ValueDecl::getCode(indent) << "(";
    bool first = true;
    for (const auto& parm : parms_) {
        if (first)
            first = false;
        else
            oss << ", ";
        oss << parm->getCode();
    }
    oss << ")" << endl;
    oss << (body_ ? body_->getCode(indent) : "{}");
    return oss.str();
}

void epat::FunctionDecl::addParm(ParmVarDecl::ptr parm)
{
    if (parm) addDecl(parm);
}

void epat::FunctionDecl::pushStmt(StmtPtr stmt)
{
    // TODO: body_可能不存在吗？
    if (body_) body_->pushStmt(move(stmt));
}

epat::FieldDecl::ptr epat::FieldDecl::create(std::string name, QualType wt)
{
    return ptr(new FieldDecl(DeclKind::FieldDecl, move(name), move(wt)));
}

epat::StructDecl::
    StructDecl(std::string name, Context::ref parent /*, FieldDecl::list list*/)
    : Decl(DeclKind::StructDecl, move(name)), Context(parent), fields_(/*move(list)*/)
{
}

bool epat::StructDecl::addDecl(Decl::ptr decl)
{
    if (!decl) return false;
    // TODO: 用static_pointer_cast没问题吧？
    if (Context::addDecl(decl)) {
        fields_.push_back(dynamic_pointer_cast<FieldDecl>(decl));
        return true;
    }
    return false;
}

epat::StructDecl::ptr epat::StructDecl::
    create(std::string name, Context::ref parent /*, FieldDecl::list list*/)
{
    return ptr(new StructDecl(
        move(name), move(parent) /*, move(list)*/
    ));
}

std::string epat::StructDecl::getAstString(std::string prefix) const
{
    Node::list children;
    for (const auto& fd : fields_)
        children.emplace_back(fd.get());
    return buildAstString(move(children), Decl::getAstString(), move(prefix));
}

std::string epat::StructDecl::getCode(int indent) const
{
    ostringstream oss;
    oss << string(indent, ' ') << "struct " << getName() << " {" << endl;
    for (const auto& field : fields_)
        oss << field->getCode(indent + 2) << ";" << endl;
    oss << string(indent, ' ') << "}";
    return oss.str();
}

void epat::StructDecl::addField(FieldDecl::ptr field)
{
    if (field) addDecl(field);
}

FieldDecl::ptr epat::StructDecl::getField(const std::string& name) const
{
    for (const auto& field : fields_)
        if (field->getName() == name) return field;
    return {};
}

int epat::StructDecl::getSize() const
{
    // TODO: use cache.
    int res = 0;
    for (const auto& field : fields_)
        res += field->getType().getSize();
    return res;
}

epat::TypeDecl::TypeDecl(std::string name, Type::ptr type)
    : Decl(DeclKind::TypeDecl, move(name)), type_(move(type))
{
}

epat::TypeDecl::ptr epat::TypeDecl::create(std::string name, Type::ptr type)
{
    return ptr(new TypeDecl(move(name), move(type)));
}

std::string epat::TypeDecl::getAstString(std::string prefix) const
{
    return buildAstString(
        {type_.get()}, Decl::getAstString() + " '" + type_->getCode() + "'", prefix
    );
}

std::string epat::TypeDecl::getCode(int indent) const
{
    Type::code_info code_info;
    type_->buildCode(code_info);
    return string(indent, ' ') + "typedef " + code_info.get_code(getName());
}

epat::VarDecl::VarDecl(std::string name, QualType wt, ExprPtr init)
    : ValueDecl(DeclKind::VarDecl, move(name), move(wt)), init_(move(init))
{
}

epat::VarDecl::ptr epat::VarDecl::create(std::string name, QualType wt, ExprPtr init)
{
    return ptr(new VarDecl(move(name), move(wt), move(init)));
}

std::string epat::VarDecl::getAstString(std::string prefix) const
{
    return buildAstString(
        {init_.get()}, ValueDecl::getAstString() + " '" + getType().getCode() + "'",
        move(prefix)
    );
}

std::string epat::VarDecl::getCode(int indent) const
{
    ostringstream oss;
    oss << ValueDecl::getCode(indent);
    if (init_) oss << " = " << init_->getCode();
    return oss.str();
}
