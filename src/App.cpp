#include "App.h"
#include "Events.h"
#include "Core/Events/WindowEvents.h"
#include "Core/Events/KeyEvents.h"
#include "Core/Events/MouseEvents.h"
#include "Log.h"
#include "Renderer/Renderer.h"
#include "Renderer/Shader.h"
#include "Window.h"
#include "Utils/Path.h"

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
    EventDispatcher::Get().AddEventListener<KeyPressedEvent>(
        [this](const Event *e) { CORE_LOGF("Key pressed: {}", ((const KeyPressedEvent *)e)->GetKeyCode()); });
    EventDispatcher::Get().AddEventListener<KeyReleasedEvent>(
        [this](const Event *e) { CORE_LOGF("Key released: {}", ((const KeyReleasedEvent *)e)->GetKeyCode()); });
    EventDispatcher::Get().AddEventListener<MouseKeyPressedEvent>([this](const Event *e) {
        CORE_LOGF("Mouse button pressed: {}", ((const MouseKeyPressedEvent *)e)->GetKeyCode());
    });
    EventDispatcher::Get().AddEventListener<MouseKeyReleasedEvent>([this](const Event *e) {
        CORE_LOGF("Mouse button released: {}", ((const MouseKeyReleasedEvent *)e)->GetKeyCode());
    });
    EventDispatcher::Get().AddEventListener<MouseMotionEvent>([this](const Event *e) {
        CORE_LOGF(
            "Mouse moved: X:{} Y:{}",
            ((const MouseMotionEvent *)e)->GetPosition().x,
            ((const MouseMotionEvent *)e)->GetPosition().y);
    });

    CORE_LOGI("GameDir: {}", Path::ExecutableDir());

    Renderer::Get()->Init();

    // auto sl = new ShaderLibrary();
    // sl->Load("Color");
    
    while (!shouldTerminate)
    {
        m_Window->Update();
    }
    Renderer::Get()->Shutdown();
}

} // namespace Toucan