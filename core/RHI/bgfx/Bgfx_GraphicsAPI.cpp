#include "Bgfx_GraphicsAPI.h"
#include <bgfx/bgfx.h>
#include <bgfx/defines.h>
#include <bgfx/platform.h>
#include "Toucan.h"
#include "RHI/RHI_Buffer.h"

#include <cstddef>
#include <sys/types.h>

namespace Toucan
{
Bgfx_GraphicsAPI::Bgfx_GraphicsAPI()
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

Bgfx_GraphicsAPI::~Bgfx_GraphicsAPI() {}

void Bgfx_GraphicsAPI::Initialize()
{
    bgfx::renderFrame();                   // tells bgfx to start single threaded mode (?)
    bgfx::Init init;                       // initialize bgfx
    init.type = bgfx::RendererType::Count; // tells bgfx to use the default renderer
    init.platformData.ndt = NULL;
    init.platformData.nwh = Global::g_Window->GetNativeWindow(); // get the native window handle from the window class
    bgfx::init(init);                                            // initialize bgfx
    bgfx::setDebug(BGFX_DEBUG_TEXT); // Enable debug text.
}

void Bgfx_GraphicsAPI::Shutdown()
{
    bgfx::shutdown();
}

void Bgfx_GraphicsAPI::BeginScene()
{
    bgfx::begin();
}

void Bgfx_GraphicsAPI::EndScene()
{
    bgfx::frame();
}

void Bgfx_GraphicsAPI::SetClearColor(const LinearColor &color)
{
    m_ClearColor = color;
}

void Bgfx_GraphicsAPI::SetViewport(uint32 x, uint32 y, uint32 width, uint32 height)
{
    bgfx::setViewRect(0, x, y, width, height);
    bgfx::reset(width, height, BGFX_RESET_NONE);
}

void Bgfx_GraphicsAPI::Clear()
{
    unsigned int rgba = 0;
    rgba |= (unsigned int)(glm::clamp(m_ClearColor.r, .0f, 1.0f) * 255.0f) << 24;
    rgba |= (unsigned int)(glm::clamp(m_ClearColor.g, .0f, 1.0f) * 255.0f) << 16;
    rgba |= (unsigned int)(glm::clamp(m_ClearColor.b, .0f, 1.0f) * 255.0f) << 8;
    rgba |= (unsigned int)(glm::clamp(m_ClearColor.a, .0f, 1.0f) * 255.0f);    
    bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, rgba, 1.0f, 0);
}

void Bgfx_GraphicsAPI::SetVertexBuffer(const Ref<RHI_VertexBuffer>& VertexBuffer)
{
    //cast down void* to uint16_t
    uint16_t handle = static_cast<uint16_t>(reinterpret_cast<uintptr_t>(VertexBuffer->GetRHIResourceHandle()));
    bgfx::setVertexBuffer(0, bgfx::VertexBufferHandle{handle});
}

void Bgfx_GraphicsAPI::SetIndexBuffer(const Ref<RHI_IndexBuffer>& IndexBuffer)
{
    //cast down void* to uint16_t
    uint16_t handle = static_cast<uint16_t>(reinterpret_cast<uintptr_t>(IndexBuffer->GetRHIResourceHandle()));
    bgfx::setIndexBuffer(bgfx::IndexBufferHandle{handle});
}

void Bgfx_GraphicsAPI::Submit(const Ref<RHI_Shader>& ShaderProgram)
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
    bgfx::submit(0, {static_cast<uint16_t>(reinterpret_cast<uintptr_t>(ShaderProgram->GetRHIResourceHandle()))});
}

void Bgfx_GraphicsAPI::DrawIndexed()
{
}

Ref<RHI_VertexBuffer> Bgfx_GraphicsAPI::CreateVertexBuffer(void *Vertices, uint32 Size, const BufferLayout &Layout)
{
    bgfx::VertexLayout layout;
    const Array<BufferElement> &elements = Layout.GetElements();

    layout.begin();
    for (auto &element : elements)
    {
        bgfx::Attrib::Enum attrib;
        if (element.Name.find("POSITION") != String::npos)
            attrib = bgfx::Attrib::Position;
        else if (element.Name.find("NORMAL") != String::npos)
            attrib = bgfx::Attrib::Normal;
        else if (element.Name.find("TANGENT") != String::npos)
            attrib = bgfx::Attrib::Tangent;
        else if (element.Name.find("BITANGENT") != String::npos)
            attrib = bgfx::Attrib::Bitangent;
        else if (element.Name.find("TEXCOORD") != String::npos)
            attrib = bgfx::Attrib::TexCoord0;
        else if (element.Name.find("COLOR") != String::npos)
            attrib = bgfx::Attrib::Color0;
        else
            attrib = bgfx::Attrib::Count;

        uint32 NumComponents = 0;
        switch (element.ElementType)
        {
        case BufferElementType::Float:
        case BufferElementType::Int:
            NumComponents = 1;
            break;
        case BufferElementType::Float2:
        case BufferElementType::Int2:
            NumComponents = 2;
            break;
        case BufferElementType::Float3:
        case BufferElementType::Int3:
            NumComponents = 3;
            break;
        case BufferElementType::Float4:
        case BufferElementType::Int4:
            NumComponents = 4;
            break;
        default:
            break;
        }

        bgfx::AttribType::Enum Type;
        switch (element.ElementType)
        {
        case BufferElementType::Float:
        case BufferElementType::Float2:
        case BufferElementType::Float3:
        case BufferElementType::Float4:
            Type = bgfx::AttribType::Float;
            break;
        case BufferElementType::Int:
        case BufferElementType::Int2:
        case BufferElementType::Int3:
        case BufferElementType::Int4:
            Type = bgfx::AttribType::Int16;
            break;
        default:
            break;
        }

        layout.add(attrib, NumComponents, Type, element.IsNormalized, false);
    }
    layout.end();

    uint64 Handle = bgfx::createVertexBuffer(bgfx::makeRef(Vertices, Size), layout).idx;

    Ref<RHI_VertexBuffer> VertexBuffer = std::make_shared<RHI_VertexBuffer>(reinterpret_cast<void *>(Handle), Layout, Size);

    return VertexBuffer;
}

Ref<RHI_IndexBuffer> Bgfx_GraphicsAPI::CreateIndexBuffer(void *Indexes, uint32 Count)
{
    uint64 Handle = bgfx::createIndexBuffer(bgfx::makeRef(Indexes, Count * sizeof(int)), BGFX_BUFFER_COMPUTE_READ | BGFX_BUFFER_INDEX32).idx;
    Ref<RHI_IndexBuffer> IndexBuffer = std::make_shared<RHI_IndexBuffer>(reinterpret_cast<void *>(Handle), Count);
    return IndexBuffer;
}

} // namespace Toucan