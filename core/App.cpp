#include "App.h"

#include "Core/Events/WindowEvents.h"
#include "Core/Events/KeyEvents.h"
#include "Core/Events/MouseEvents.h"

#include "Renderer/Renderer.h"
#include "Utils/Path.h"
#include "Window.h"

#include "glm/fwd.hpp"

namespace Toucan
{

App::App(const char *Name)
{
    WindowInitializationParams params;
    params.Title = std::string(Name);
    params.Resolution = {800, 600};

    m_LayerStack = std::make_unique<LayerStack>();

    m_Window = Window::Create(params);
    m_Window->SetEventCallback([this](Event *event) { OnEvent(event); });
}

void App::Run()
{
    CORE_LOGI("GameDir: {}", Path::ExecutableDir());

    Renderer::Get()->Init();
    Renderer::Get()->SetClearState({0.2f, 0.2f, 0.2f, 1.0f});

    while (!m_ShouldTerminate)
    {
        for (auto &layer : *m_LayerStack)
        {
            layer->OnUpdate();
        }

        for (auto &layer : *m_LayerStack)
        {
            layer->OnImGuiRender();
        }

        m_Window->Update();
    }
    Renderer::Get()->Shutdown();
}

void App::OnEvent(Event *event)
{
    EventForwarder forwarder(event);
    forwarder.Dispatch<WindowCloseEvent>([this](Event *e) {
        LOGI(LogEvent,"Window close event received.");
        m_ShouldTerminate = true;
        return true;
    });
    forwarder.Dispatch<WindowResizeEvent>([this](Event* e){
        glm::vec2 NewSize = {((WindowResizeEvent*)e)->GetWidth(), ((WindowResizeEvent*)e)->GetHeight()};
        LOGI(LogEvent,"Window resized to: {}x{}", NewSize.x, NewSize.y);
        // TODO - Resize viewport
        return true;
    });

    // Dispatch events to layer stack from overlay to base layer. If an event is handled, stop dispatching.
    for (auto it = m_LayerStack->end(); it != m_LayerStack->begin();)
    {
        (*--it)->OnEvent(event);
        if (event->IsHandled())
            break;
    }
}

} // namespace Toucan