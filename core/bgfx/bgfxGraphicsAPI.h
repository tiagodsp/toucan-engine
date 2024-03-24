#pragma once
#include "CoreTypes.h"
#include "Toucan.h"
#include "bgfx/bgfxGraphicsContext.h"
#include <bgfx/bgfx.h>

namespace Toucan
{

class CORE_LOCAL BgfxGraphicsAPI : public GraphicsAPI
{
    BgfxGraphicsContext *m_Context;
    LinearColor m_ClearColor;

  public:
    BgfxGraphicsAPI();
    virtual ~BgfxGraphicsAPI();
    virtual void Init() override;
    virtual void Shutdown() override;
    virtual void BeginScene() override;
    virtual void EndScene() override;

    virtual void SetClearColor(const LinearColor &color) override;
    virtual void SetViewport(uint32 x, uint32 y, uint32 width, uint32 height) override;
    virtual void Clear() override;

    virtual void Submit(const Ref<Shader>& ShaderProgram) override;

    virtual void DrawIndexed() override;
};

} // namespace Toucan