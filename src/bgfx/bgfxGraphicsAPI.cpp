#include "bgfxGraphicsAPI.h"
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include "Globals.h"

#include <cstddef>

namespace Toucan
{
BgfxGraphicsAPI::BgfxGraphicsAPI()
{
#if defined(BUILD_DARWIN)
    SetAPIName(EAPIName::API_Metal);
#elif defined(BUILD_WINDOWS)
    SetAPIName(EAPIName::API_Direct3D12);
#elif defined(BUILD_LINUX)
    SetAPIName(EAPIName::API_Vulkan);
#else
    SetAPIName(EAPIName::API_OpenGL);
#endif
}

BgfxGraphicsAPI::~BgfxGraphicsAPI() {}

void BgfxGraphicsAPI::Init()
{
    bgfx::renderFrame();                   // tells bgfx to start single threaded mode (?)
    bgfx::Init init;                       // initialize bgfx
    init.type = bgfx::RendererType::Count; // tells bgfx to use the default renderer
    init.resolution.width = 800;
    init.resolution.height = 600;
    init.platformData.ndt = NULL;
    init.platformData.nwh = Global::g_Window->GetNativeWindow(); // get the native window handle from the window class
    bgfx::init(init);                                            // initialize bgfx
    bgfx::setViewRect(0, 0, 0, uint32_t(800), uint32_t(600));

    bgfx::setDebug(BGFX_DEBUG_TEXT); // Enable debug text.
}

void BgfxGraphicsAPI::Shutdown()
{
    bgfx::shutdown();
}

void BgfxGraphicsAPI::BeginScene()
{
    m_Context->m_Encoder = bgfx::begin();
}

void BgfxGraphicsAPI::EndScene()
{
    bgfx::end(m_Context->m_Encoder);
}

void BgfxGraphicsAPI::SetClearColor(const LinearColor &color)
{
    unsigned int rgba = 0;
    rgba |= (unsigned int)(glm::clamp(color.r, .0f, 1.0f) * 255.0f) << 24;
    rgba |= (unsigned int)(glm::clamp(color.g, .0f, 1.0f) * 255.0f) << 16;
    rgba |= (unsigned int)(glm::clamp(color.b, .0f, 1.0f) * 255.0f) << 8;
    rgba |= (unsigned int)(glm::clamp(color.a, .0f, 1.0f) * 255.0f);
    bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, rgba, 1.0f, 0);
}

void BgfxGraphicsAPI::Clear()
{
    // Set view rect called here for testing purposes.
    bgfx::setViewRect(0, 0, 0, uint32_t(800), uint32_t(600));
    bgfx::touch(0);
    bgfx::frame();
}

} // namespace Toucan