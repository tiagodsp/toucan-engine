#pragma once
#include "Toucan.h"

namespace Toucan
{
class BgfxShader : public Shader
{
    String m_Source;
    String m_FilePath;
    String m_Name;

  public:
    BgfxShader(const String &filepath);
    BgfxShader(const String &name, const String &filepath);
    ~BgfxShader();

    virtual void Invalidate() override;
    virtual void Bind() override;
    virtual void Unbind() override;

  protected:
    virtual void Compile() override;
};


} // namespace Toucan