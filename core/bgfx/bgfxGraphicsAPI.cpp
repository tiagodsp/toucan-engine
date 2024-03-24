#include "bgfxGraphicsAPI.h"
#include <bgfx/bgfx.h>
#include <bgfx/defines.h>
#include <bgfx/platform.h>
#include "CoreTypes.h"
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
    init.platformData.ndt = NULL;
    init.platformData.nwh = Global::g_Window->GetNativeWindow(); // get the native window handle from the window class
    bgfx::init(init);                                            // initialize bgfx
    bgfx::setDebug(BGFX_DEBUG_TEXT); // Enable debug text.
}

void BgfxGraphicsAPI::Shutdown()
{
    bgfx::shutdown();
}

void BgfxGraphicsAPI::BeginScene()
{
    bgfx::begin();
}

void BgfxGraphicsAPI::EndScene()
{
    bgfx::frame();
    // bgfx::end(m_Context->m_Encoder);
}

void BgfxGraphicsAPI::SetClearColor(const LinearColor &color)
{
    m_ClearColor = color;
}

void BgfxGraphicsAPI::SetViewport(uint32 x, uint32 y, uint32 width, uint32 height)
{
    bgfx::setViewRect(0, x, y, width, height);
    bgfx::reset(width, height, BGFX_RESET_NONE);
}

void BgfxGraphicsAPI::Clear()
{
    unsigned int rgba = 0;
    rgba |= (unsigned int)(glm::clamp(m_ClearColor.r, .0f, 1.0f) * 255.0f) << 24;
    rgba |= (unsigned int)(glm::clamp(m_ClearColor.g, .0f, 1.0f) * 255.0f) << 16;
    rgba |= (unsigned int)(glm::clamp(m_ClearColor.b, .0f, 1.0f) * 255.0f) << 8;
    rgba |= (unsigned int)(glm::clamp(m_ClearColor.a, .0f, 1.0f) * 255.0f);    
    bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, rgba, 1.0f, 0);
}

void BgfxGraphicsAPI::Submit(const Ref<Shader>& ShaderProgram)
{
    // submit and draw the shader program
    uint64_t state = 0
				| BGFX_STATE_WRITE_R
				| BGFX_STATE_WRITE_G
				| BGFX_STATE_WRITE_B
				| BGFX_STATE_WRITE_A
				| BGFX_STATE_WRITE_Z
				| BGFX_STATE_DEPTH_TEST_LESS
				| BGFX_STATE_CULL_CW
				| BGFX_STATE_MSAA;

    bgfx::setState(state);
    bgfx::submit(0, *static_cast<bgfx::ProgramHandle*>(ShaderProgram->GetNativeHandle()));
}

void BgfxGraphicsAPI::DrawIndexed()
{
}

} // namespace Toucan