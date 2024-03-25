#pragma once
#include "CoreTypes.h"

namespace Toucan
{

class RHI_Shader;
class RHI_VertexBuffer;
class RHI_IndexBuffer;
class BufferLayout;

class CORE_API RHI_GraphicsAPI
{
  public:
    enum EAPIName
    {
        API_None,
        API_OpenGL,
        API_Direct3D11,
        API_Direct3D12,
        API_Vulkan,
        API_Metal,
    };

  private:
    EAPIName m_APIName;

  public:
    /** Get the graphics API. */
    static Ref<RHI_GraphicsAPI> Get();
    
    /** Initialize the graphics API. */
    virtual void Initialize() = 0;
    /** Shutdown the graphics API. */
    virtual void Shutdown() = 0;
    /** Begin a new scene. */
    virtual void BeginScene() = 0;
    /** End the current scene. */
    virtual void EndScene() = 0;
    /** Set the clear color. */
    virtual void SetClearColor(const LinearColor &color) = 0;
    /** Set the viewport. */
    virtual void SetViewport(uint32 x, uint32 y, uint32 width, uint32 height) = 0;
    /** Clear the screen. */
    virtual void Clear() = 0;
    /** Get the name of the graphics API. */
    const EAPIName GetAPIName() const { return m_APIName; }
    /** Submit program to rendering */
    virtual void Submit(const Ref<RHI_Shader>& ShaderProgram) = 0;
    /** Set the vertex buffer */
    virtual void SetVertexBuffer(const Ref<RHI_VertexBuffer>& VertexBuffer) = 0;
    /** Set the index buffer */
    virtual void SetIndexBuffer(const Ref<RHI_IndexBuffer>& IndexBuffer) = 0;
    /** Draw primitives */
    virtual void DrawIndexed() = 0;

    /** Create a vertex buffer */
    virtual Ref<RHI_VertexBuffer> CreateVertexBuffer(void *Vertices, uint32 Size, const BufferLayout &Layout) = 0;
    /** Create an index buffer */
    virtual Ref<RHI_IndexBuffer> CreateIndexBuffer(void *Indexes, uint32 Count) = 0;

  protected:
    /** Set graphics api name. Only called by subclasses. */
    void SetAPIName(EAPIName apiName) { m_APIName = apiName; }
};

} // namespace Toucan