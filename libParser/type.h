#ifndef TOOL_TYPE_H
#define TOOL_TYPE_H

#include <string>
#include <ostream>
#include <vector>

namespace tool {

    class Context;
    class QualType;
    class Type {
    protected:
        friend class QualType;
        mutable unsigned int ref_cnt = 0;
        // Context* parent;
        // Type(Context* parent);
        Type();
    public:
        virtual std::string getAsString() const = 0;
        // virtual std::string getAsString(const std::string& str) const = 0;
        virtual const Type* getBaseType() const;
        virtual int getSize() const = 0;
        virtual bool isNamed() const;
        virtual bool isStruct() const;

        virtual int getTotalLevel() const;

        virtual bool operator==(const Type& other) const;
        friend std::ostream& operator<<(std::ostream& os, const Type& t);
        friend std::ostream& operator<<(std::ostream& os, const Type* t);
    };
    
    inline std::ostream& operator<<(std::ostream& os, const Type& t)
    {
        return os << t.getAsString();
    }

    inline std::ostream& operator<<(std::ostream& os, const Type* t)
    {
        return os << t->getAsString();
    }

    class NamedType : public Type {
        std::string name;
        int size;
    protected:
        NamedType(const std::string& name = "%unknown", int size = 1);
    public:
        ~NamedType();
        static NamedType* get(Context* parent, const std::string& name = "%unknown", int size = 1);

        virtual std::string getAsString() const;
        // virtual std::string getAsString(const std::string& str) const;
        virtual const Type* getBaseType() const;
        std::string getName() const;
        virtual int getSize() const;
        virtual bool isNamed() const;

        virtual bool operator==(const NamedType& other) const;
    };

    class ArrayType;
    class PointerType;
    class StructType;
    class QualType {
        friend class Context;
        friend class ArrayType;
        friend class DecayedType;
        friend class PointerType;
        friend class StructType;
        const Type* type;
        // Context* getContext();
        // bool decay = false;
    public:
        QualType();
        QualType(const Type* type);
        QualType(const Type& type);
        QualType(const QualType& other);
        ~QualType();

        QualType& operator=(const QualType& other);
        bool operator==(const QualType& other) const;

        std::string getAsString() const;
        std::string getAsString(std::string vname) const;
        int getSize() const;
        bool isValid() const;
        bool isInt() const;
        bool isStruct() const;
        bool isArray() const;
        int getLenth() const;
        int getElementSize() const;
        const Type* getElementType() const;
        std::vector<int> getDimensions() const;
        bool isDecayed() const;
        bool isPointer() const;
        QualType getPointerType() const;
        // bool isPointerDecay() const;
        QualType getPointerDecay() const;
        int getLevel() const;
        int getTotalLevel() const;
        // int getTotalLevel() const;
        int getDirectPointeeSize() const;
        QualType getDirectPointeeType() const;
        int getPointeeSize() const;
        QualType getPointeeType() const;
        const Type* getBaseType() const;
        const StructType* getAsStruct() const;

        QualType operator*(int lenth);
        QualType operator*(const std::vector<int>& dimensions);

        friend std::ostream& operator<<(std::ostream& os, const QualType& qt);
    };

    inline std::ostream& operator<<(std::ostream& os, const QualType& qt)
    {
        return os << qt.getAsString();
    }

    class ArrayType : public Type {
        friend class Context;
        friend class ImplicitCastExpr;
        friend class QualType;
        QualType et;
        mutable int lenth;
        void setLenth(int lenth) const;
        void addLenth(int d) const;
        ArrayType(QualType element_type, int lenth);
    public:
        ~ArrayType();
        static ArrayType* get(QualType element_type, int lenth);
        QualType getPointerDecay() const;

        virtual std::string getAsString() const;
        virtual const Type* getBaseType() const;
        virtual int getSize() const;
        int getLenth() const;
        virtual int getTotalLevel() const;

        int getElementSize() const;
        const Type* getElementType() const;

        virtual bool operator==(const ArrayType& other) const;
    };

    class BuildInType : public NamedType {
    protected:
        BuildInType(const std::string& name = "%unknown", int size = 1);
    public:
        ~BuildInType();
        static BuildInType* get(Context* parent, const std::string& name = "%unnamed", int size = 1);

        virtual bool operator==(const BuildInType& other) const;
    };

    class DecayedType : public Type {
        friend class QualType;
        QualType original_type, new_type;
        DecayedType(const ArrayType* AT);
    public:
        ~DecayedType();
        static DecayedType* get(const ArrayType* AT);

        virtual std::string getAsString() const;
        virtual const Type* getBaseType() const;
        virtual int getSize() const;
        int getLenth() const;
        int getLevel() const;
        virtual int getTotalLevel() const;

        int getElementSize() const;
        const Type* getElementType() const;
        QualType getPointerType() const;

        virtual bool operator==(const DecayedType& other) const;
    };

    class PointerType : public Type {
        friend class QualType;
        friend class ArrayType;
        QualType pt;
        int level = 1;
        PointerType(QualType pointee_type, int level = 1);
    public:
        ~PointerType();
        static PointerType* get(QualType pointee_type, int level);

        virtual std::string getAsString() const;
        // virtual std::string getAsString(const std::string& str) const;
        virtual const Type* getBaseType() const;
        virtual int getSize() const;
        int getLevel() const;
        virtual int getTotalLevel() const;
        //bool isPointerDecay() const;

        virtual bool operator==(const PointerType& other) const;
    };

    class StructType : public NamedType {
        friend class QualType;

        class StructDecl* decl;
        StructType(StructDecl* D);
    public:
        ~StructType();
        static StructType* get(StructDecl* SD);

        virtual std::string getAsString() const;
        virtual const Type* getBaseType() const;
        virtual int getSize() const;
        virtual bool isStruct() const;

        StructDecl* getDecl() const;

        virtual bool operator==(const StructType& other) const;
    };

}

#endif // !TOOL_TYPE_H