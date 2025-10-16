#include "decl.h"
#include "debug.h"
#include "stmt.h"
#include "writer.h"
#include <ostream>
#include <sstream>

using namespace epat;
using namespace std;

epat::Decl::Decl(DeclKind dk, std::string name) : kind_(dk), name_(move(name)) {}

const char* epat::Decl::declKind2Str(DeclKind dk)
{
    return DeclKindNameList[static_cast<int>(dk)];
}

epat::Decl::DeclKind epat::Decl::str2DeclKind(const std::string& str)
{
    for (int i = 0; i != static_cast<int>(DeclKind::Undefined); ++i)
        if (DeclKindNameList[i] == str)
            return DeclKind(i);
    return DeclKind::Undefined;
}

const std::string& epat::Decl::getName() const
{
    return name_;
}

void epat::Decl::printAst(std::ostream& os, const std::string& prefix) const
{
    os << prefix << getDeclKindName();
    auto& name = getName();
    os << (name.empty() ? "" : " " + name);
}

void epat::Decl::printCode(std::ostream& os, int indent) const
{
    os << "$" << getDeclKindName();
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

void epat::ValueDecl::printAst(std::ostream& os, const std::string& prefix) const
{
    Decl::printAst(os, prefix);
    os << " '";
    getType().printCode(os, -1);
    os << "'";
}

void epat::ValueDecl::printCode(std::ostream& os, int indent) const
{
    os << getType().getDeclCode(getName(), indent);
}

epat::Context::Context(Context::ref parent) : parent_(parent) {}

void epat::Context::setParent(Context::ref parent)
{
    if (parent == parent_)
        return;
    parent_ = parent;
}

bool epat::Context::addDecl(Decl::ptr decl)
{
    if (!decl)
        return false;
    const auto& name = decl->getName();
    // 名称为空的情况: 函数参数名，匿名结构体，匿名枚举
    // XXX: 下面的写法是因为名称可能为空。但也许我们能做得更好:)
    if (!name.empty())
        if (auto it = decls_.find(name); it != decls_.end()) {
            cout << "warning: a declaration with the name \"" << name
                 << "\" already exists!" << endl;
            return false;
        }
    if (auto ctx = dynamic_cast<Context*>(decl.get()))
        ctx->setParent(this);
    if (!name.empty())
        decls_[name] = move(decl);
    return true;
}

bool epat::Context::existsDecl(const std::string& name, bool recursively) const
{
    if (auto it = decls_.find(name); it != decls_.end())
        return true;
    return parent_ ? parent_->existsDecl(name, recursively) : false;
}

epat::Decl::ptr epat::Context::getDecl(const std::string& name, bool recursively) const
{
    if (auto it = decls_.find(name); it != decls_.end())
        return it->second;
    return parent_ ? parent_->getDecl(name, recursively) : nullptr;
}

TypeDecl::ptr epat::Context::getTypeDecl(const std::string& name, bool recursively)
{
    return dynamic_pointer_cast<TypeDecl>(getDecl(name, recursively));
}

ValueDecl::ptr epat::Context::getValueDecl(const std::string& name,
                                           bool recursively) const
{
    return dynamic_pointer_cast<ValueDecl>(getDecl(name, recursively));
}

FunctionDecl::ptr epat::Context::getFunctionDecl(const std::string& name,
                                                 bool recursively) const
{
    return dynamic_pointer_cast<FunctionDecl>(getDecl(name, recursively));
}

epat::ParmVarDecl::ParmVarDecl(std::string name, QualType qt)
    : ValueDecl(DeclKind::ParmVarDecl, move(name), move(qt))
{
}

epat::ParmVarDecl::ptr epat::ParmVarDecl::create(std::string name, QualType qt)
{
    return ptr(new ParmVarDecl(move(name), move(qt)));
}

epat::FunctionDecl::FunctionDecl(std::string name, QualType ft,
                                 ParmVarDecl::list parm_list, Context::ref parent)
    : ValueDecl(DeclKind::FunctionDecl, move(name), move(ft)), Context(parent), parms_(),
      body_(nullptr)
{
    for (auto& parm : parm_list)
        if (addDecl(parm))
            parms_.push_back(parm);
}

epat::FunctionDecl::ptr epat::FunctionDecl::create(std::string name, QualType ret,
                                                   ParmVarDecl::list parm_list,
                                                   Context::ref parent)
{
    QualType::list type_list;
    for (const auto& parm : parm_list)
        type_list.emplace_back(parm->getType());
    auto ft = FunctionType::create(move(ret), move(type_list));
    auto fd = ptr(new FunctionDecl(move(name), move(ft), move(parm_list)));
    if (parent)
        parent->addDecl(fd);
    return fd;
}

epat::FunctionDecl::ptr epat::FunctionDecl::create(std::string name, QualType ret,
                                                   QualType::list type_list,
                                                   Context::ref parent)
{
    ParmVarDecl::list parm_list;
    for (const auto& type : type_list)
        parm_list.emplace_back(ParmVarDecl::create("", type));
    return create(move(name), move(ret), move(parm_list), parent);
}

epat::FunctionDecl::ptr epat::FunctionDecl::createImplicit(std::string name)
{
    auto ret = BaseType::getInt();
    if ("malloc" == name)
        ret = PointerType::create(BaseType::getVoid());
    else
        epat_warning(std::string("undefined function: ") + name +
                     ", default to return int");
    auto fd = create(move(name), move(ret), ParmVarDecl::list{});
    fd->is_implicit_ = true;
    return fd;
}

void epat::FunctionDecl::printAst(std::ostream& os, const std::string& prefix) const
{
    ValueDecl::printAst(os, prefix);
    if (body_)
        print_tree(os, prefix, parms_, body_);
    else
        print_tree(os, prefix, parms_);
}

void epat::FunctionDecl::printCode(std::ostream& os, int indent) const
{
    auto ret = getRetType().getCode(indent);
    // XXX: 填入空格，是否有更多的情况？是否有更优雅的方法？
    if (ret.size() > 1 && ret.back() != '*')
        ret.push_back(' ');
    os << ret;
    os << getName() << '(';
    // XXX: 优化打印
    for (size_t i = 0; i < parms_.size(); ++i) {
        if (i)
            os << ", ";
        parms_[i]->printCode(os, indent);
    }
    os << ')';
    if (hasBody()) {
        os << ' ';
        body_->printCode(os, indent);
    }
}

void epat::FunctionDecl::pushStmt(StmtPtr stmt)
{
    if (body_)
        body_->pushStmt(move(stmt));
}

void epat::FunctionDecl::setBody(CompoundStmtPtr body)
{
    body_ = move(body);
}

epat::FieldDecl::FieldDecl(std::string name, QualType wt, StructDeclRef parent)
    : ValueDecl(DeclKind::FieldDecl, move(name), move(wt)), parent_(parent)
{
}

epat::FieldDecl::ptr epat::FieldDecl::create(std::string name, QualType wt,
                                             StructDeclRef parent)
{
    return ptr(new FieldDecl(move(name), move(wt), parent));
}

epat::StructDecl::StructDecl(std::string name, Context::ref parent)
    : Decl(DeclKind::StructDecl, move(name)), Context(parent), fields_()
{
}

bool epat::StructDecl::addDecl(Decl::ptr decl)
{
    if (!decl)
        return false;
    // 只允许添加FieldDecl
    if (auto fd = dynamic_pointer_cast<FieldDecl>(decl)) {
        if (Context::addDecl(fd)) {
            fd->parent_ = this;
            fields_.push_back(fd);
            return true;
        }
    }
    return false;
}

epat::StructDecl::ptr epat::StructDecl::create(std::string name, Context::ref parent)
{
    auto sd = ptr(new StructDecl(move(name), parent));
    if (parent)
        parent->addDecl(sd);
    return sd;
}

void epat::StructDecl::printAst(std::ostream& os, const std::string& prefix) const
{
    Decl::printAst(os, prefix);
    print_tree(os, prefix, fields_);
}

void epat::StructDecl::printCode(std::ostream& os, int indent) const
{
    // XXX: 优化打印
    const auto& name = getName();
    os << "struct " << (name.empty() ? "" : name + " ") << "{" << endl;
    for (const auto& field : fields_) {
        os << SPACES2;
        field->printCode(os, indent + 2);
        os << ";" << endl;
    }
    os << SPACES << "}";
}

void epat::StructDecl::addField(FieldDecl::ptr field)
{
    if (field)
        addDecl(field);
}

FieldDecl::ptr epat::StructDecl::getField(const std::string& name) const
{
    for (const auto& field : fields_)
        if (field->getName() == name)
            return field;
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

epat::TypeDecl::TypeDecl(std::string name, QualType type)
    : Decl(DeclKind::TypeDecl, move(name)), type_(move(type))
{
}

epat::TypeDecl::ptr epat::TypeDecl::create(std::string name, QualType type)
{
    return ptr(new TypeDecl(move(name), move(type)));
}

void epat::TypeDecl::printAst(std::ostream& os, const std::string& prefix) const
{
    Decl::printAst(os, prefix);
    os << " '";
    type_->printCode(os, -1);
    os << "'";
    print_tree(os, prefix, type_);
}

void epat::TypeDecl::printCode(std::ostream& os, int indent) const
{
    Type::type_code _type_code;
    _type_code.indent = indent;
    type_->buildCode(_type_code);
    os << "typedef " << _type_code.get_code(getName());
}

epat::VarDecl::VarDecl(std::string name, QualType wt, ExprPtr init)
    : ValueDecl(DeclKind::VarDecl, move(name), move(wt)), init_(move(init))
{
}

epat::VarDecl::ptr epat::VarDecl::create(std::string name, QualType wt, ExprPtr init)
{
    init = ImplicitCastExpr::cast2Target(move(init), wt);
    return ptr(new VarDecl(move(name), move(wt), move(init)));
}

void epat::VarDecl::printAst(std::ostream& os, const std::string& prefix) const
{
    ValueDecl::printAst(os, prefix);
    if (init_)
        print_tree(os, prefix, init_);
}

void epat::VarDecl::printCode(std::ostream& os, int indent) const
{
    ValueDecl::printCode(os, indent);
    if (init_) {
        os << " = ";
        init_->printCode(os);
    }
}
