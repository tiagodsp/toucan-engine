#pragma once
#include "Toucan.h"
#include "bgfx/bgfxGraphicsContext.h"
#include <bgfx/bgfx.h>

namespace Toucan
{

class BgfxGraphicsAPI : public GraphicsAPI
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
};

} // namespace Toucan