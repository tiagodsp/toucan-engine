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

    static Ref<Shader> Create(const String &Name, const String &Filepath);

  protected:
    virtual void Compile() = 0;
};

class ShaderLibrary
{
    Map<String, Ref<Shader>> m_Shaders;

  public:
    ShaderLibrary();
    ~ShaderLibrary();

    void Load(const String &name);
    Ref<Shader> GetShader(const String &name);
};

} // namespace Toucan
