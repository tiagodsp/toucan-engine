#include "Renderer/Buffer.h"
#include "bgfx/bgfxBuffer.h"

namespace Toucan
{
Ref<VertexBuffer> VertexBuffer::Create(void *Vertices, uint32 Size)
{
    Ref<BgfxVertexBuffer> buffer = std::make_shared<BgfxVertexBuffer>();
    buffer->SetLayout(
        {{BufferElementType::Float3, "POSITION"},
         {BufferElementType::Float3, "NORMAL"},
         {BufferElementType::Float2, "TEXCOORD"}});
    buffer->SetData(Vertices, Size);
}
} // namespace Toucan