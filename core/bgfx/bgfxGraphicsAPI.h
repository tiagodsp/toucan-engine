#pragma once
#include "Toucan.h"
#include "bgfx/bgfxGraphicsContext.h"
#include <bgfx/bgfx.h>

namespace Toucan
{

class CORE_LOCAL BgfxGraphicsAPI : public GraphicsAPI
{
    BgfxGraphicsContext *m_Context;

  public:
    BgfxGraphicsAPI();
    virtual ~BgfxGraphicsAPI();
    virtual void Init() override;
    virtual void Shutdown() override;
    virtual void BeginScene() override;
    virtual void EndScene() override;

    virtual void SetClearColor(const LinearColor &color) override;
    virtual void Clear() override;

    virtual void Submit(const Ref<Shader>& ShaderProgram) override;

    virtual void DrawIndexed() override;
};

} // namespace Toucan