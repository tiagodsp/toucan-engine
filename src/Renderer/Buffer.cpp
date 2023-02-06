#include "Renderer/Buffer.h"
#include "bgfx/bgfxBuffer.h"

namespace Toucan
{
Ref<VertexBuffer> VertexBuffer::Create(void *Vertices, uint32 Size, const BufferLayout &Layout)
{
    Ref<BgfxVertexBuffer> buffer = std::make_shared<BgfxVertexBuffer>();
    buffer->SetLayout(Layout);
    buffer->SetData(Vertices, Size);
    return buffer;
}

Ref<IndexBuffer> IndexBuffer::Create(void *Indexes, uint32 Count)
{
    Ref<BgfxIndexBuffer> buffer = std::make_shared<BgfxIndexBuffer>();
    buffer->SetData(Indexes, Count);
    return buffer;
}
} // namespace Toucan