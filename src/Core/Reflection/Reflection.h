#pragma once
#include "Core/Reflection/Type.h"
#include "Toucan.h"

namespace Toucan
{

// Reflection macros ---------------------------------------------------------
#define REFLECTION_BEGIN(TYPE)                                                                                         \
    friend ClassType;                                                                                                  \
    using _T = TYPE;                                                                                                   \
                                                                                                                       \
  public:                                                                                                              \
    using _B = base_of<TYPE>::type;                                                                                    \
    static ClassType StaticType;                                                                                       \
    void f()                                                                                                           \
    {                                                                                                                  \
    }                                                                                                                  \
    virtual const ClassType &GetDerivedType() const                                                                                \
    {                                                                                                                  \
        return StaticType;                                                                                             \
    }                                                                                                                  \
                                                                                                                       \
  private:                                                                                                             \
    static void InitReflection(ClassType *_type)                                                                       \
    {                                                                                                                  \
        _type->BaseClass = (ClassType *)TypeRegister::Get().GetType<_B>();                                             \
        _type->Name = #TYPE;                                                                                           \
        _type->Size = sizeof(_T);                                                                                      \
        _type->Constructor = Construct<_T>;                                                                            \
        _type->Destructor = Destruct<_T>;

#define REFLECTION_MEMBER(TYPE, NAME)                                                                                  \
    _type->Members.emplace_back(#NAME, *TypeRegister::Get().GetType<TYPE>(), offsetof(_T, NAME));

#define REFLECTION_END()                                                                                               \
    TypeRegister::Get().RegisterType(_type->Name, *_type);                                                             \
    }

#define REFLECTION_INIT(TYPE) Toucan::ClassType TYPE::StaticType(TYPE::InitReflection)
} // namespace Toucan
