#include "bgfxGraphicsAPI.h"
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include "Globals.h"
#include "glm/common.hpp"
#include "glm/packing.hpp"

#include "SDL2/SDL.h"
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
    bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x303030ff, 1.0f, 0);
}

void BgfxGraphicsAPI::Clear()
{
    // bgfx::renderFrame();
    // bgfx::setViewRect(0, 0, 0, uint16_t(800), uint16_t(600));
    bgfx::setViewRect(0, 0, 0, uint32_t(800), uint32_t(600));
    bgfx::touch(0);
    // Use debug font to print information about this example.
    bgfx::dbgTextPrintf(
        80,
        1,
        0x0f,
        "\x1b[;0m    \x1b[;1m    \x1b[; 2m    \x1b[; 3m    \x1b[; 4m    \x1b[; 5m    \x1b[; 6m    \x1b[; 7m    "
        "\x1b[0m");
    bgfx::dbgTextPrintf(
        80,
        2,
        0x0f,
        "\x1b[;8m    \x1b[;9m    \x1b[;10m    \x1b[;11m    \x1b[;12m    \x1b[;13m    \x1b[;14m    \x1b[;15m    "
        "\x1b[0m");

    const bgfx::Stats *stats = bgfx::getStats();
    bgfx::dbgTextPrintf(
        0,
        2,
        0x0f,
        "Backbuffer %dW x %dH in pixels. Debug text %dW x %dH in characters.",
        stats->width,
        stats->height,
        stats->textWidth,
        stats->textHeight);

    // Print general statistics of BGFX.
    bgfx::dbgTextPrintf(
        0,
        3,
        0x0f,
        "Draw calls: %d (vs %d, fs %d), Compute calls: %d, Triangles: %d",
        stats->numDraw,
        stats->numCompute,
        stats->numBlit,
        stats->numCompute,
        stats->numPrims);

    bgfx::frame();
}

} // namespace Toucan