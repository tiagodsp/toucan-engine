#include "Renderer.h"
#include "Renderer/GraphicsAPI.h"
#include "Renderer/Renderer2D.h"
#include <memory>

namespace Toucan
{
Ref<Renderer> Renderer::Get()
{
    static Ref<Renderer> instance = std::make_shared<Renderer>();
    return instance;
}

void Renderer::Init()
{
    GraphicsAPI::Get()->Init();
    Renderer2D::Get()->Init();
}

void Renderer::Shutdown()
{
    GraphicsAPI::Get()->Shutdown();
    Renderer2D::Get()->Shutdown();
}

void Renderer::Begin() { GraphicsAPI::Get()->BeginScene(); }

void Renderer::End() { GraphicsAPI::Get()->EndScene(); }

void Renderer::Clear(const LinearColor &color)
{
    GraphicsAPI::Get()->Clear();
}

void Renderer::SetClearState(const LinearColor &color)
{
    GraphicsAPI::Get()->SetClearColor(color);
}

} // namespace Toucan