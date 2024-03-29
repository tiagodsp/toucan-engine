#pragma once
#include "Core/CoreTypes.h"

namespace Toucan
{

class RHI_VertexBuffer;
class RHI_IndexBuffer;

class CORE_API Renderer2D
{
  Ref<RHI_VertexBuffer> m_VertexBuffer;
  Ref<RHI_IndexBuffer> m_IndexBuffer;

  public:
    /**
     * @brief Get the instance of the renderer
     * @return Ref<Renderer2D> 
     */
    static Ref<Renderer2D> Get();
    
    /**
     * @brief Initialize the renderer
     */
    void Initialize();

    /**
     * @brief Shutdown the renderer
     */
    void Shutdown();
    
    // void DrawLine(const Vector2 &from, const Vector2 &to, const Color &color);

    void DrawRect(const Rect &rect, const LinearColor &color);

    // void DrawCircle(const Vector2 &center, float radius, const Color &color);

    // void DrawTriangle(const Vector2 &a, const Vector2 &b, const Vector2 &c, const Color &color);

    // void DrawQuad(const Vector2 &a, const Vector2 &b, const Vector2 &c, const Vector2 &d, const Color &color);
};
} // namespace Toucan