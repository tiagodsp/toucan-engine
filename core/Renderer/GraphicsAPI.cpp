#include "GraphicsAPI.h"
#include "bgfx/bgfxGraphicsAPI.h"
#include <memory>

namespace Toucan
{
Ref<GraphicsAPI> GraphicsAPI::Get()
{
    static Ref<GraphicsAPI> s_API;
    if (s_API == nullptr) { s_API = std::make_shared<BgfxGraphicsAPI>(); }
    return s_API;
}
} // namespace Toucan