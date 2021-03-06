#pragma once
#include "Toucan.h"
#include "bgfx/bgfx.h"

namespace Toucan
{
class BgfxGraphicsContext : public GraphicsContext
{
    friend class BgfxGraphicsAPI;

    bgfx::Encoder *m_Encoder;

  public:
    BgfxGraphicsContext() {}
    virtual ~BgfxGraphicsContext() {}
};
} // namespace Toucan