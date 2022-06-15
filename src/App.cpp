#include "App.h"
#include "Core/Events/WindowEvents.h"
#include "Events.h"
#include "Window.h"
#include <memory>

namespace Toucan
{

App::App(const char *Name)
{
    WindowInitializationParams params;
    params.Title = std::string(Name);
    params.Resolution = {800, 600};

    m_Window = Window::Create(params);
}

void App::Run()
{
    bool shouldTerminate = false;
    EventDispatcher::Get().AddEventListener<WindowCloseEvent>(
        [this, &shouldTerminate](const Event *e) { shouldTerminate = true; });
    while (!shouldTerminate)
    {
        m_Window->Update();
    }
}

} // namespace Toucan