#pragma once
#include "CoreTypes.h"

namespace Toucan
{

extern class Window;
extern class GraphicsContext;
extern class GraphicsAPI;
extern class Renderer2D;

struct CORE_API Global
{
    static class Window *g_Window;
    static class GraphicsContext *g_GraphicsContext;
    static class GraphicsAPI *g_GraphicsAPI;
    static class Renderer2D *g_Renderer2D;
};

} // namespace Toucan