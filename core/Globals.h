#pragma once
#include "CoreTypes.h"

namespace Toucan
{

class Window;
class GraphicsContext;
class GraphicsAPI;
class Renderer2D;

struct CORE_API Global
{
    static Window *g_Window;
    static GraphicsContext *g_GraphicsContext;
    static GraphicsAPI *g_GraphicsAPI;
    static Renderer2D *g_Renderer2D;
};

} // namespace Toucan