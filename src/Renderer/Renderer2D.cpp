#include "Renderer2D.h"

namespace Toucan
{
Ref<Renderer2D> Renderer2D::Get()
{
    static Ref<Renderer2D> instance = std::make_shared<Renderer2D>();
    return instance;
}
void Renderer2D::Init() {}
void Renderer2D::Shutdown() {}
} // namespace Toucan