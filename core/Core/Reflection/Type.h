#pragma once
#include "CoreTypes.h"

namespace Toucan
{

struct CORE_API Type
{
    const char *Name;
    size_t Size;
    Type(const char *_Name, size_t _Size) : Name(_Name), Size(_Size) {}
};

struct CORE_API Member
{
    const char *Name;
    Type Type;
    size_t Offset;
    Member(const char *_Name, struct Type _Type, size_t _Offset) : Name(_Name), Type(_Type), Offset(_Offset) {}
};

struct CORE_API StructType : Type
{
    std::vector<Member> Members;
    StructType(void (*init)(StructType *)) : Type(nullptr, 0) { init(this); }
};

struct CORE_API ClassType : Type
{
    ClassType *BaseClass;
    std::vector<Member> Members;
    std::function<void(void *)> Constructor;
    std::function<void(void *)> Destructor;

    ClassType(void (*init)(ClassType *)) : Type(nullptr, 0) { init(this); }
};

template <typename T>
inline Type *GetPrimitiveType()
{
    static_assert(true, "Type not supported");
    return nullptr;
}

/**
 * @brief Class that holds the reflection information of all types
 */
class CORE_API TypeRegister
{
    std::map<const char *, Type> _Types;

  public:
    static TypeRegister &Get()
    {
        static TypeRegister instance;
        return instance;
    }

    template <typename T>
    static char Test(decltype(&T::StaticType));
    template <typename T>
    static int Test(...);
    template <typename T>
    struct IsReflected
    {
        static constexpr bool value = sizeof(Test<T>(nullptr)) == sizeof(char);
    };

    template <typename T, typename std::enable_if<IsReflected<T>::value, int>::type = 0>
    Type *GetType()
    {
        return &T::StaticType;
    }

    template <typename T, typename std::enable_if<!IsReflected<T>::value, int>::type = 0>
    Type *GetType()
    {
        return GetPrimitiveType<T>();
    }

    // template<typename T, typename std::enable_if<IsReflected<T>::value, int>::type = 0> std::vector<Type*>
    // GetBaseClasses()
    // {
    //     std::vector<Type*> baseClasses;
    //     for (typename B : base_classes_of(this)) {
    //         baseClasses.push_back(B::StaticType);
    //     }
    //     return baseClasses;
    // }

    Type *GetTypeByName(const char *name)
    {
        auto it = _Types.find(name);
        if (it == _Types.end()) return nullptr;
        return &it->second;
    }
    void RegisterType(const char *name, Type type) { _Types.insert({name, type}); }
};

// Primitive types --------------------------------------------------------

#define DECLARE_PRIMITIVE_TYPE(TYPE)                                                                                   \
    class CORE_API TYPE##Type : public Type                                                                                     \
    {                                                                                                                  \
      public:                                                                                                          \
        TYPE##Type() : Type(#TYPE, sizeof(TYPE)) {}                                                                    \
    };                                                                                                                 \
    template <>                                                                                                        \
    inline Type *GetPrimitiveType<TYPE>()                                                                              \
    {                                                                                                                  \
        static TYPE##Type type;                                                                                        \
        return &type;                                                                                                  \
    }

#define DECLARE_TYPE_SCOPED(SCOPE, TYPE)                                                                               \
    class CORE_API SCOPE##_##TYPE##Type : public Type                                                                           \
    {                                                                                                                  \
      public:                                                                                                          \
        SCOPE##_##TYPE##Type() : Type("SCOPE::TYPE", sizeof(SCOPE::TYPE)) {}                                           \
    };                                                                                                                 \
    template <>                                                                                                        \
    inline Type *GetPrimitiveType<SCOPE::TYPE>()                                                                       \
    {                                                                                                                  \
        static SCOPE##_##TYPE##Type type;                                                                              \
        return &type;                                                                                                  \
    }

DECLARE_PRIMITIVE_TYPE(int);
DECLARE_PRIMITIVE_TYPE(char);
DECLARE_PRIMITIVE_TYPE(bool);
DECLARE_PRIMITIVE_TYPE(float);
DECLARE_PRIMITIVE_TYPE(double);

DECLARE_PRIMITIVE_TYPE(String);
DECLARE_PRIMITIVE_TYPE(Vector2);
DECLARE_PRIMITIVE_TYPE(Vector3);
DECLARE_PRIMITIVE_TYPE(Vector4);
// DECLARE_PRIMITIVE_TYPE(Vector);
DECLARE_PRIMITIVE_TYPE(Vector2Int);
DECLARE_PRIMITIVE_TYPE(Vector3Int);
DECLARE_PRIMITIVE_TYPE(Vector4Int);
DECLARE_PRIMITIVE_TYPE(Matrix4);
// DECLARE_PRIMITIVE_TYPE(Quaternion);
// DECLARE_PRIMITIVE_TYPE(Color);
// DECLARE_PRIMITIVE_TYPE(Rect);
// DECLARE_PRIMITIVE_TYPE(Size);
// DECLARE_PRIMITIVE_TYPE(Point);
// DECLARE_PRIMITIVE_TYPE(Range);

// Constructor and desctuctor helpers
template <typename TYPE>
void Construct(void *object)
{
    new (object) TYPE();
}

template <typename TYPE>
void Destruct(void *object)
{
    ((TYPE *)object)->~TYPE();
}
// ----------------------------------------------------------------------------

// Helpers to check if Type is a base class -------------------------------------
template <typename T>
char Test(decltype(&T::f));
template <typename T>
int Test(...);
template <typename T>
struct HasBaseClass
{
    static constexpr bool value = sizeof(Test<T>(nullptr)) == sizeof(char);
};
// ----------------------------------------------------------------------------

// Helpers to get the base classes of a class ---------------------------------
template <typename T, typename T2 = void>
struct base_of
{
    using type = T2;
};

template <typename T, typename R>
T _base_of(R T::*);
template <typename T>
struct base_of<T, typename std::enable_if<HasBaseClass<T>::value>::type>
{
    using type = decltype(_base_of(&T::f));
};
// ----------------------------------------------------------------------------

} // namespace Toucan