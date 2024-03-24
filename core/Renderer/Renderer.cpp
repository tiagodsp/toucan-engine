#include "Renderer.h"
#include "Globals.h"
#include "RHI/RHI_GraphicsAPI.h"
#include "Renderer/Renderer2D.h"
#include <memory>

namespace Toucan
{
Ref<Renderer> Renderer::Get()
{
    static Ref<Renderer> instance = std::make_shared<Renderer>();
    return instance;
}

void Renderer::Initialize()
{
    RHI_GraphicsAPI::Get()->Initialize();
    Renderer2D::Get()->Initialize();
    Vector2 viewportSize = Global::g_Window->GetWindowSize();
    SetViewportSize(viewportSize);
}

void Renderer::Shutdown()
{
    RHI_GraphicsAPI::Get()->Shutdown();
    Renderer2D::Get()->Shutdown();
}

void Renderer::Begin()
{
    RHI_GraphicsAPI::Get()->BeginScene();
}

void Renderer::End()
{
    RHI_GraphicsAPI::Get()->EndScene();
}

void Renderer::Clear(const LinearColor &color)
{
    RHI_GraphicsAPI::Get()->SetClearColor(color);
    RHI_GraphicsAPI::Get()->Clear();
}

void Renderer::SetClearState(const LinearColor &color)
{
    RHI_GraphicsAPI::Get()->SetClearColor(color);
}

void Renderer::SetViewportSize(const Vector2Int &Size)
{
    RHI_GraphicsAPI::Get()->SetViewport(0, 0, Size.x, Size.y);
}
} // namespace Toucan