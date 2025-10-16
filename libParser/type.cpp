#include "debug.h"
#include "expression.h"
#include "type.h"

using namespace std;
using namespace tool;

//tool::Type::Type(Context* parent)
//	: parent(parent)
//{
//}

//std::string tool::Type::getAsString() const
//{
//	debug << "为什么？？？？？" << tool::endl;
//	return "%unnamed";
//}

tool::Type::Type()
{
}

const Type* tool::Type::getBaseType() const
{
    return this;
}

bool tool::Type::isNamed() const
{
    return false;
}

bool tool::Type::isStruct() const
{
    return false;
}

//int tool::Type::getSize() const
//{
//	debug << "为什么？？？？？？？？？" << tool::endl;
//	return 1;
//}

int tool::Type::getTotalLevel() const
{
    return 0;
}

bool tool::Type::operator==(const Type& other) const
{
    return false;
}

tool::NamedType::NamedType(const std::string& name, int size)
    : Type(), name(name), size(size)
{
}

tool::NamedType::~NamedType()
{
}

NamedType* tool::NamedType::get(Context* parent, const std::string& name, int size)
{
    auto ret = new NamedType(name, size);
    parent->addType(ret);
    return ret;
}

std::string tool::NamedType::getAsString() const
{
    return name;
}

const Type* tool::NamedType::getBaseType() const
{
    return this;
}

std::string tool::NamedType::getName() const
{
    return name;
}

int tool::NamedType::getSize() const
{
    return size;
}

bool tool::NamedType::isNamed() const
{
    return true;
}

bool tool::NamedType::operator==(const NamedType& other) const
{
    return name == other.name;
}

tool::QualType::QualType()
    : QualType(nullptr)
{
}

// main constructor
tool::QualType::QualType(const Type* type)
    : type(type)
{
    if (type)
        ++(type->ref_cnt);
}

tool::QualType::QualType(const Type& type)
    : QualType(&type)
{
}

tool::QualType::QualType(const QualType& other)
{
    type = other.type;
    // decay = other.decay;
    if (type)
        ++(type->ref_cnt);
}

tool::QualType::~QualType()
{
    if (!type)
        return;
    --(type->ref_cnt);
    if (!type->ref_cnt && !type->isNamed()) {
        // debug << "delete an obsolete type" << tool::endL;
        delete type;
    }
}

QualType& tool::QualType::operator=(const QualType& other)
{
    if (type)
        --(type->ref_cnt);
    type = other.type;
    // decay = other.decay;
    if (type)
        ++(type->ref_cnt);
    return *this;
}

bool tool::QualType::operator==(const QualType& other) const
{
    return type == other.type || *type == *other.type;
}

std::string tool::QualType::getAsString() const
{
    int level = getTotalLevel();
    auto dims = getDimensions();
    bool decay = dynamic_cast<const DecayedType*>(type);
    auto ret = getBaseType()->getAsString();
    if (level > 0 || dims.size() > 0)
        ret += " ";
    if (level > 0) {
        if (decay) {
            --level;
            dims.erase(dims.begin());
        }
        ret += string(level, '*');
        if (decay && dims.size() > 0)
            ret += "(*)";
        else if (decay)
            ret += "*";
    }
    for (auto dim : dims)
        ret += "[" + to_string(dim) + "]";
    return ret;
}

std::string tool::QualType::getAsString(std::string vname) const
{
    int level = getTotalLevel();
    auto dims = getDimensions();
    std::string ret = std::string(level, '*');
    ret += vname;
    for (auto i : dims)
        ret += ("[" + to_string(i) + "]");
    return ret;
}

int tool::QualType::getSize() const
{
    if (type)
        return type->getSize();
    return 0;
}

bool tool::QualType::isValid() const
{
    return type;
}

bool tool::QualType::isInt() const
{
    if (auto nt = dynamic_cast<const NamedType*>(type))
        return nt->getName() == "int";
    return false;
}

bool tool::QualType::isStruct() const
{
    return dynamic_cast<const StructType*>(type);
}

bool tool::QualType::isArray() const
{
    return dynamic_cast<const ArrayType*>(type);
}

int tool::QualType::getLenth() const
{
    if (auto at = dynamic_cast<const ArrayType*>(type))
        return at->lenth;
    if (auto dt = dynamic_cast<const DecayedType*>(type))
        return dt->getLenth();
    return 0;
}

int tool::QualType::getElementSize() const
{
    if (auto at = dynamic_cast<const ArrayType*>(type))
        return at->getElementSize();
    if (auto dt = dynamic_cast<const DecayedType*>(type))
        return dt->getElementSize();
    debug << "不是数组或弱化指针。返回默认值1" << endL;
    return 1;
}

const Type* tool::QualType::getElementType() const
{
    if (auto at = dynamic_cast<const ArrayType*>(type))
        return at->getElementType();
    if (auto dt = dynamic_cast<const DecayedType*>(type))
        return dt->getElementType();
    debug << "不是数组或弱化指针。返回默认值nullptr" << endL;
    return nullptr;
}

std::vector<int> tool::QualType::getDimensions() const
{
    if (auto at = dynamic_cast<const ArrayType*>(type)) {
        auto res = at->et.getDimensions();
        res.insert(res.begin(), at->lenth);
        return res;
    }
    else if (auto pt = dynamic_cast<const PointerType*>(type)) {
        return pt->pt.getDimensions();
    }
    else if (auto dt = dynamic_cast<const DecayedType*>(type)) {
        return dt->original_type.getDimensions();
    }
    return std::vector<int>();
}

bool tool::QualType::isDecayed() const
{
    return dynamic_cast<const DecayedType*>(type);
}

bool tool::QualType::isPointer() const
{
    return dynamic_cast<const PointerType*>(type)
        or isDecayed();
}

QualType tool::QualType::getPointerType() const
{
    if (auto pt = dynamic_cast<const PointerType*>(type))
        return pt;
    if (auto dt = dynamic_cast<const DecayedType*>(type))
        return dt;
    return *this;
}

//bool tool::QualType::isPointerDecay() const
//{
//	if (auto pt = dynamic_cast<const PointerType*>(type))
//		return pt->isPointerDecay();
//	return false;
//}

QualType tool::QualType::getPointerDecay() const
{
    if (auto at = dynamic_cast<const ArrayType*>(type))
        return at->getPointerDecay();
    debug << "试图弱化非数组" << tool::endL;
    return *this;
}

int tool::QualType::getLevel() const
{
    if (auto pt = dynamic_cast<const PointerType*>(type))
        return pt->getLevel();
    else if (auto dt = dynamic_cast<const DecayedType*>(type))
        return 1;
    return 0;
}

int tool::QualType::getTotalLevel() const
{
    if (type)
        return type->getTotalLevel();
    return 0;
}

int tool::QualType::getDirectPointeeSize() const
{
    if (auto pt = dynamic_cast<const PointerType*>(type))
        if (pt->getLevel() == 1)
            return pt->pt.getSize();
    return 1;
}

QualType tool::QualType::getDirectPointeeType() const
{
    if (auto pt = dynamic_cast<const PointerType*>(type)) {
        if (pt->getLevel() == 1)
            return pt;
        else
            return PointerType::get(pt->pt, pt->getLevel() - 1);
    }
    else if (auto dt = dynamic_cast<const DecayedType*>(type))
        return dt->new_type.getPointeeType();
    return *this;
}

int tool::QualType::getPointeeSize() const
{
    return getPointeeType().getSize();
}

QualType tool::QualType::getPointeeType() const
{
    if (auto pt = dynamic_cast<const PointerType*>(type))
        return pt->pt;
    else if (auto dt = dynamic_cast<const DecayedType*>(type))
        return dt->new_type.getPointeeType();
    return nullptr;
}

const Type* tool::QualType::getBaseType() const
{
    return type->getBaseType();
}

const StructType* tool::QualType::getAsStruct() const
{
    return dynamic_cast<const StructType*>(type);
}

QualType tool::QualType::operator*(int lenth)
{
    return new ArrayType(*this, lenth);
}

QualType tool::QualType::operator*(const std::vector<int>& dimensions)
{
    if (dimensions.empty())
        return *this;
    QualType ret = *this;
    for (auto ii = dimensions.rbegin(), ie = dimensions.rend();
            ii != ie; ++ii)
        ret = ret * *ii;
    return ret;
}

//Context* tool::QualType::getContext()
//{
//	if (type)
//		return type->parent;
//	return nullptr;
//}

void tool::ArrayType::setLenth(int lenth) const
{
    if (this->lenth != lenth)
        this->lenth = lenth;
}

void tool::ArrayType::addLenth(int d) const
{
    lenth += d;
}

tool::ArrayType::ArrayType(QualType et, int lenth)
    : Type(/*et.getContext()*/), et(et), lenth(lenth)
{
}

tool::ArrayType::~ArrayType()
{
}

ArrayType* tool::ArrayType::get(QualType element_type, int lenth)
{
    return new ArrayType(element_type, lenth);
}

QualType tool::ArrayType::getPointerDecay() const
{
    return DecayedType::get(this);
}

std::string tool::ArrayType::getAsString() const
{
    return et.getAsString() + " [" + to_string(lenth) + "]";
}

const Type* tool::ArrayType::getBaseType() const
{
    return et.getBaseType();
}

int tool::ArrayType::getSize() const
{
    return lenth * et.getSize();
}

int tool::ArrayType::getLenth() const
{
    return lenth;
}

int tool::ArrayType::getTotalLevel() const
{
    return et.getTotalLevel();
}

int tool::ArrayType::getElementSize() const
{
    return et.getSize();
}

const Type* tool::ArrayType::getElementType() const
{
    return et.type;
}

bool tool::ArrayType::operator==(const ArrayType& other) const
{
    return et == other.et && lenth == other.lenth;
}

tool::BuildInType::BuildInType(const std::string& name, int size)
    : NamedType(name, size)
{
}

tool::BuildInType::~BuildInType()
{
}

BuildInType* tool::BuildInType::get(Context* parent, const std::string& name, int size)
{
    auto ret = new BuildInType(name, size);
    parent->addType(ret);
    return ret;
}

bool tool::BuildInType::operator==(const BuildInType& other) const
{
    return NamedType::operator==(other);
}

tool::DecayedType::DecayedType(const ArrayType* AT)
    : Type(), original_type(AT),
    new_type(PointerType::get(AT->getElementType(), 1))
{
}

tool::DecayedType::~DecayedType()
{}

DecayedType* tool::DecayedType::get(const ArrayType* AT)
{
    return new DecayedType(AT);
}

std::string tool::DecayedType::getAsString() const
{
    if (original_type.isArray()) {
        auto&& ret = new_type.getAsString();
        // TODO: 做点什么？
        return ret;
    }
    return new_type.getAsString();
}

const Type* tool::DecayedType::getBaseType() const
{
    return original_type.getBaseType();
}

int tool::DecayedType::getSize() const
{
    return new_type.getSize();
}

int tool::DecayedType::getLenth() const
{
    return original_type.getLenth();
}

int tool::DecayedType::getLevel() const
{
    return 1;
}

int tool::DecayedType::getTotalLevel() const
{
    return new_type.getTotalLevel();
}

int tool::DecayedType::getElementSize() const
{
    return original_type.getElementSize();
}

const Type* tool::DecayedType::getElementType() const
{
    return original_type.getElementType();
}

QualType tool::DecayedType::getPointerType() const
{
    return new_type;
}

bool tool::DecayedType::operator==(const DecayedType& other) const
{
    return original_type == other.original_type;
}

tool::PointerType::PointerType(QualType pointee_type, int level)
    : Type(/*pointee_type.getContext()*/),
    pt(pointee_type), level(level)
{
}

tool::PointerType::~PointerType()
{
}

PointerType* tool::PointerType::get(QualType pointee_type, int level)
{
    if (auto ppt = dynamic_cast<const PointerType*>(pointee_type.type))
        return new PointerType(ppt->pt, ppt->level + level);
    return new PointerType(pointee_type, level);
}

std::string tool::PointerType::getAsString() const
{
    //if (level < 0)
    //	return pt.getAsString("(*)");
    return pt.getAsString() + " " + std::string(level, '*');
}

//std::string tool::PointerType::getAsString(const std::string& str) const
//{
//	// 要么是最里层（级数>0），要么是最外层的退化指针（级数<0)
//	if (level < 0)
//		return pt.getAsString("(*)");
//	return pt.getAsString() + " " + std::string(level, '*') + str;
//}

const Type* tool::PointerType::getBaseType() const
{
    return pt.getBaseType();
}

int tool::PointerType::getSize() const
{
    return 1;
}

int tool::PointerType::getLevel() const
{
    return level;
}

int tool::PointerType::getTotalLevel() const
{
    return getLevel() + pt.getLevel();
}

bool tool::PointerType::operator==(const PointerType& other) const
{
    return level == other.level && pt == other.pt;
}

//bool tool::PointerType::isPointerDecay() const
//{
//	return level == -1;
//}

tool::StructType::StructType(StructDecl* D)
    : NamedType(D->getName(), D->getSize()), decl(D)
{
}

tool::StructType::~StructType()
{
}

StructType* tool::StructType::get(StructDecl* SD)
{
    return new StructType(SD);
}

std::string tool::StructType::getAsString() const
{
    return "struct " + decl->getName();
}

const Type* tool::StructType::getBaseType() const
{
    return this;
}

int tool::StructType::getSize() const
{
    return decl->getSize();
}

bool tool::StructType::isStruct() const
{
    return true;
}

StructDecl* tool::StructType::getDecl() const
{
    return decl;
}

bool tool::StructType::operator==(const StructType& other) const
{
    return decl == other.decl;
}