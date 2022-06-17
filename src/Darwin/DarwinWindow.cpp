#ifdef BUILD_DARWIN
#include "Window.h"

#include "Events.h"
#include "Core/Events/WindowEvents.h"
#include "Core/Events/KeyEvents.h"
#include "Core/Events/MouseEvents.h"

#include "SDL_events.h"
#include "SDL2/SDL.h"
#include "SDL_error.h"
#include "SDL_render.h"
#include "SDL_video.h"

namespace Toucan
{

Window::Window(WindowInitializationParams params)
{
    CORE_LOGI("Creating window.");
    CORE_LOGI("Window title: {}", params.Title);
    CORE_LOGI("Window resolution: {}x{}", params.Resolution.x, params.Resolution.y);

    // intialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING))
    {
        const char *error = SDL_GetError();
        CORE_LOGF("Failed to initialize window: {}", error);
    }

    m_WindowHandle =
        SDL_CreateWindow(params.Title.c_str(), params.InitialPosition.x, params.InitialPosition.y, params.Resolution.x,
                         params.Resolution.y, SDL_WINDOW_METAL | SDL_WINDOW_RESIZABLE);
    if (!m_WindowHandle)
    {
        const char *error = SDL_GetError();
        CORE_LOGF("Failed to initialize window: {}", error);
    }

    m_RendererHandle = SDL_CreateRenderer((SDL_Window *)m_WindowHandle, -1, 0);
    if (!m_RendererHandle)
    {
        const char *error = SDL_GetError();
        CORE_LOGF("Failed to initialize renderer: {}", error);
    }

    // Set events
}

void Window::Update()
{
    // Get an event
    SDL_Event event;
    SDL_PollEvent(&event);

    // Handle the event
    if (event.type == SDL_QUIT) { EventDispatcher::Get().Dispatch(new WindowCloseEvent()); }
    if (event.type == SDL_KEYDOWN) { EventDispatcher::Get().Dispatch(new KeyPressedEvent(event.key.keysym.sym)); }
    if (event.type == SDL_KEYUP) { EventDispatcher::Get().Dispatch(new KeyReleasedEvent(event.key.keysym.sym)); }
    if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        EventDispatcher::Get().Dispatch(new MouseKeyPressedEvent({event.button.x, event.button.y}, event.button.button));
    }
    if (event.type == SDL_MOUSEBUTTONUP)
    {
        EventDispatcher::Get().Dispatch(new MouseKeyReleasedEvent({event.button.x, event.button.y}, event.button.button));
    }
    if (event.type == SDL_MOUSEMOTION)
    {
        EventDispatcher::Get().Dispatch(
            new MouseMotionEvent({event.motion.x, event.motion.y}, {event.motion.xrel, event.motion.yrel}));
    }
}

Ref<Window> Window::Create(WindowInitializationParams params)
{
    Ref<Window> window;
    window.reset(new Window(params));
    return window;
}

} // namespace Toucan

#endif // BUILD_DARWIN