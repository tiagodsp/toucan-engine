#include "RHI/RHI_Buffer.h"
#include "RHI/RHI_GraphicsAPI.h"

namespace Toucan
{
Ref<RHI_VertexBuffer> RHI_VertexBuffer::Create(void *Vertices, uint32 Size, const BufferLayout &Layout)
{
    return RHI_GraphicsAPI::Get()->CreateVertexBuffer(Vertices, Size, Layout);
}

Ref<RHI_IndexBuffer> RHI_IndexBuffer::Create(void *Indexes, uint32 Count)
{
    return RHI_GraphicsAPI::Get()->CreateIndexBuffer(Indexes, Count);
}
} // namespace Toucan