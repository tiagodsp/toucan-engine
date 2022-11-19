#pragma once
#include "Toucan.h"

namespace Toucan
{
class Shader
{
  public:
    virtual void Invalidate() = 0;
    virtual void Bind() = 0;
    virtual void Unbind() = 0;
    virtual void* GetNativeHandle() = 0;

    static Ref<Shader> Create(const String &Name, const String &FragmentFilepath, const String &VertexFilepath);

  protected:
    virtual bool Compile() = 0;
};

class ShaderLibrary
{
    Map<String, Ref<Shader>> m_Shaders;
    static Map<String, Ref<ShaderLibrary>> s_ShaderLibraries;


  public:
    ShaderLibrary();
    ~ShaderLibrary();

    void Load(const String &name);
    Ref<Shader> GetShader(const String &name);

    static Ref<ShaderLibrary> Create(const String &name);
    static Ref<ShaderLibrary> GetLibrary(const String &name);
};

} // namespace Toucan
