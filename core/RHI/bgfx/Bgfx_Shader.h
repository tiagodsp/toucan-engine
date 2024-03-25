#pragma once
#include "RHI/RHI_Shader.h"
#include "bgfx/bgfx.h"

namespace Toucan
{ 

class CORE_LOCAL Bgfx_Shader : public RHI_Shader
{
    String m_FragmentFilepath;
    String m_VertexFilepath;
    String m_Name;

    std::vector<uint8> m_FragmentShaderBinaryData;
    std::vector<uint8> m_VertexShaderBinaryData;

    struct bgfx::ProgramHandle* m_Program;
    Scope<struct bgfx::ShaderHandle> m_FragmentShaderHandle;
    Scope<struct bgfx::ShaderHandle> m_VertexShaderHandle;

  public:
    Bgfx_Shader(const String &fragmentFilepath, const String &vertexFilepath);
    Bgfx_Shader(const String &name, const String &fragmentFilepath, const String &vertexFilepath);
    ~Bgfx_Shader();

    virtual void Invalidate() override;

  protected:
    virtual bool Compile() override;
};


} // namespace Toucan