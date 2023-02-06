#pragma once
#include "Toucan.h"
#include "bgfx/bgfx.h"

namespace Toucan
{
class BgfxShader : public Shader
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
    BgfxShader(const String &fragmentFilepath, const String &vertexFilepath);
    BgfxShader(const String &name, const String &fragmentFilepath, const String &vertexFilepath);
    ~BgfxShader();

    virtual void Invalidate() override;
    virtual void Bind() override;
    virtual void Unbind() override;
    virtual void* GetNativeHandle() override { return static_cast<void*>(m_Program); }

  protected:
    virtual bool Compile() override;
};


} // namespace Toucan