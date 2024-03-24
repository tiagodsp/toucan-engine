#include "Renderer2D.h"

#include "Globals.h"

#include "RHI/RHI_Buffer.h"
#include "Renderer/Shader.h"
#include "RHI/RHI_GraphicsAPI.h"

namespace Toucan
{
Ref<Renderer2D> Renderer2D::Get()
{
    static Ref<Renderer2D> instance = std::make_shared<Renderer2D>();
    return instance;
}
void Renderer2D::Initialize() {
    // Create a Vertex buffer for 2D primitives;
    // square with 4 vertices, each vertex has 3 floats for position and 4 floats for color.
    float* vertices = new float[4 * 7]{
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
    };
    
    m_VertexBuffer = RHI_VertexBuffer::Create(vertices, sizeof(float) * 4 * 7, {
        { BufferElementType::Float3, "POSITION"},
        { BufferElementType::Float4, "COLOR"}
    });

    // Create an index buffer for 2D primitives;
    // square with 2 triangles, each triangle has 3 vertices.
    uint32* indices = new uint32[2 * 3]{
        0, 1, 2,
        2, 3, 0
    };

    m_IndexBuffer = RHI_IndexBuffer::Create(indices, 6);

    Ref<ShaderLibrary> PrimitivesLibrary = ShaderLibrary::Create("Default");
    PrimitivesLibrary->Load("Color");

}
void Renderer2D::Shutdown() {}

void Renderer2D::DrawRect(const Rect &rect, const LinearColor &color) {
    RHI_GraphicsAPI::Get()->SetVertexBuffer(m_VertexBuffer);
    RHI_GraphicsAPI::Get()->SetIndexBuffer(m_IndexBuffer);
    
    Ref<ShaderLibrary> PrimitivesLibrary = ShaderLibrary::GetLibrary("Default");
    Ref<Shader> m_ShaderProgram = PrimitivesLibrary->GetShader("Color");
    RHI_GraphicsAPI::Get()->Submit(m_ShaderProgram);
}
} // namespace Toucan