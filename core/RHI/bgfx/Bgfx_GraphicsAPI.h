#pragma once
#include "Core/CoreTypes.h"
#include "RHI/RHI_Shader.h"
#include "Toucan.h"
#include "RHI/RHI_GraphicsAPI.h"

namespace Toucan
{

class RHI_IndexBuffer;
class RHI_VertexBuffer;
class RHI_Shader;

class CORE_LOCAL Bgfx_GraphicsAPI : public RHI_GraphicsAPI
{
    LinearColor m_ClearColor;

  public:
    Bgfx_GraphicsAPI();
    virtual ~Bgfx_GraphicsAPI();
    virtual void Initialize() override;
    virtual void Shutdown() override;
    virtual void BeginScene() override;
    virtual void EndScene() override;

    virtual void SetClearColor(const LinearColor &color) override;
    virtual void SetViewport(uint32 x, uint32 y, uint32 width, uint32 height) override;
    virtual void Clear() override;

    virtual void Submit(const Ref<RHI_Shader>& ShaderProgram) override;

    virtual void SetVertexBuffer(const Ref<RHI_VertexBuffer>& VertexBuffer) override;
    virtual void SetIndexBuffer(const Ref<RHI_IndexBuffer>& IndexBuffer) override;
    virtual void DrawIndexed() override;

    virtual Ref<RHI_VertexBuffer> CreateVertexBuffer(void *Vertices, uint32 Size, const BufferLayout &Layout) override;
    virtual Ref<RHI_IndexBuffer> CreateIndexBuffer(void *Indexes, uint32 Count) override;
};

} // namespace Toucan