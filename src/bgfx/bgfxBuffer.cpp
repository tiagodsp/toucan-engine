#include "bgfxBuffer.h"
#include "bgfx/bgfx.h"
#include <bgfx/defines.h>

namespace Toucan
{
void BgfxVertexBuffer::Bind()
{
    bgfx::setVertexBuffer(0, bgfx::VertexBufferHandle{m_Handle});
}

void BgfxVertexBuffer::Unbind()
{
    bgfx::setVertexBuffer(0, bgfx::VertexBufferHandle{bgfx::kInvalidHandle});
}

void BgfxVertexBuffer::SetData(void *Data, uint32 Size)
{
    bgfx::VertexLayout layout;
    const Array<BufferElement> &elements = m_Layout.GetElements();

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
    }

    m_Handle = bgfx::createVertexBuffer(bgfx::makeRef(Data, Size), layout).idx;
}

void BgfxIndexBuffer::Bind()
{
    bgfx::setIndexBuffer(bgfx::IndexBufferHandle{m_Handle});
}

void BgfxIndexBuffer::Unbind()
{
    bgfx::setIndexBuffer(bgfx::IndexBufferHandle{bgfx::kInvalidHandle});
}

void BgfxIndexBuffer::SetData(void *Data, uint32 Size)
{
    m_Handle = bgfx::createIndexBuffer(bgfx::makeRef(Data, Size), BGFX_BUFFER_COMPUTE_READ | BGFX_BUFFER_INDEX32).idx;
}

} // namespace Toucan