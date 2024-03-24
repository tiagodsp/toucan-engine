#include "RHI_GraphicsAPI.h"
#include "RHI/bgfx/bgfx_GraphicsAPI.h"
#include <memory>

namespace Toucan
{
Ref<RHI_GraphicsAPI> RHI_GraphicsAPI::Get()
{
    static Ref<RHI_GraphicsAPI> s_API;
    if (s_API == nullptr) { s_API = std::make_shared<Bgfx_GraphicsAPI>(); }
    return s_API;
}
} // namespace Toucan