#pragma once
#ifdef BUILD_DARWIN
#include "Toucan.h"
#include "DarwinWindow.h"
#include "RHI/RHI_GraphicsAPI.h"
#include "Renderer/Renderer2D.h"

#include "Core/Events/WindowEvents.h"
#include "Core/Events/KeyEvents.h"
#include "Core/Events/MouseEvents.h"

#include "SDL_events.h"
#include "SDL2/SDL.h"
#include "SDL_error.h"
#include "SDL_render.h"
#include "SDL_video.h"

#include "SDL_syswm.h"

namespace Toucan
{

DarwinWindow::DarwinWindow(WindowInitializationParams params)
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

    // Create window
    m_SDLWindowHandle = SDL_CreateWindow(
        params.Title.c_str(),
        params.InitialPosition.x,
        params.InitialPosition.y,
        params.Resolution.x,
        params.Resolution.y,
        SDL_WINDOW_METAL | SDL_WINDOW_RESIZABLE);
    if (!m_SDLWindowHandle)
    {
        const char *error = SDL_GetError();
        CORE_LOGF("Failed to initialize window: {}", error);
    }

    // Create renderer
    m_SDLRendererHandle = SDL_CreateRenderer((SDL_Window *)m_SDLWindowHandle, -1, 0);
    if (!m_SDLRendererHandle)
    {
        const char *error = SDL_GetError();
        CORE_LOGF("Failed to initialize renderer: {}", error);
    }

    // Get native window handle
    SDL_SysWMinfo wmInfo;
    SDL_VERSION(&wmInfo.version);
    if (!SDL_GetWindowWMInfo((SDL_Window *)m_SDLWindowHandle, &wmInfo))
    {
        CORE_LOGF("Failed to get native window handle: {}", SDL_GetError());
        exit(1);
    }
    m_NativeWindowHandle = wmInfo.info.cocoa.window;

    // Set events
}

void DarwinWindow::Update()
{
    PollEvents();

    // TODO - Just to test the renderer. Remove this later.
    Renderer::Get()->Clear(LinearColor(0.2f, 0.2f, 0.2f, 1.0f));
    // Renderer2D::Get()->DrawRect(Rect(10), LinearColor(0.2f, 0.2f, 1.0f, 1.0f));
}

void DarwinWindow::PollEvents()
{
    // Get an event
    SDL_Event event;
    SDL_PollEvent(&event);

    // Handle the event
    if (event.type == SDL_QUIT)
    {
        m_EventCallback(new WindowCloseEvent());
    }
    if (event.type == SDL_KEYDOWN)
    {
        m_EventCallback(new KeyPressedEvent(event.key.keysym.sym));
    }
    if (event.type == SDL_KEYUP)
    {
        m_EventCallback(new KeyReleasedEvent(event.key.keysym.sym));
    }
    if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        m_EventCallback(new MouseKeyPressedEvent({event.button.x, event.button.y}, event.button.button));
    }
    if (event.type == SDL_MOUSEBUTTONUP)
    {
        m_EventCallback(new MouseKeyReleasedEvent({event.button.x, event.button.y}, event.button.button));
    }
    if (event.type == SDL_MOUSEMOTION)
    {
        m_EventCallback(new MouseMotionEvent({event.motion.x, event.motion.y}, {event.motion.xrel, event.motion.yrel}));
    }
    if (event.type == SDL_WINDOWEVENT)
    {
        if (event.window.event == SDL_WINDOWEVENT_RESIZED)
        {
            m_WindowSize = {event.window.data1, event.window.data2};
            m_EventCallback(new WindowResizeEvent(event.window.data1, event.window.data2));
        }
    }
}

Ref<Window> Window::Create(WindowInitializationParams params)
{
    Ref<Window> window;
    window.reset(new DarwinWindow(params));
    Global::g_Window = window.get();
    return window;
}

} // namespace Toucan

#endif // BUILD_DARWIN