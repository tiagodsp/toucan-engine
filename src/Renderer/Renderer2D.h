#pragma once
#include "Toucan.h"

namespace Toucan
{

class VertexBuffer;
class IndexBuffer;

class Renderer2D
{
  Ref<VertexBuffer> m_VertexBuffer;
  Ref<IndexBuffer> m_IndexBuffer;

  public:
    /**
     * @brief Get the instance of the renderer
     * @return Ref<Renderer2D> 
     */
    static Ref<Renderer2D> Get();
    
    /**
     * @brief Initialize the renderer
     */
    void Init();

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