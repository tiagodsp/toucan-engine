#pragma once
#include "CoreTypes.h"
#include "RHI/RHI_Resource.h"

namespace Toucan
{
class CORE_API RHI_Shader : public IRHI_Resource
{
  public:
    virtual void Invalidate() = 0;

    static Ref<RHI_Shader> Create(const String &Name, const String &FragmentFilepath, const String &VertexFilepath);

  protected:
    virtual bool Compile() = 0;
};

class CORE_API ShaderLibrary
{
    Map<String, Ref<RHI_Shader>> m_Shaders;
    static Map<String, Ref<ShaderLibrary>> s_ShaderLibraries;


  public:
    ShaderLibrary();
    ~ShaderLibrary();

    void Load(const String &name);
    Ref<RHI_Shader> GetShader(const String &name);

    static Ref<ShaderLibrary> Create(const String &name);
    static Ref<ShaderLibrary> GetLibrary(const String &name);
};

} // namespace Toucan
