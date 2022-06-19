#pragma once
#include "Toucan.h"

namespace Toucan
{
class GraphicsAPI
{
  public:
    virtual void Init() = 0;
    virtual void Shutdown() = 0;
    virtual void BeginScene() = 0;
    virtual void EndScene() = 0;

    virtual void SetClearColor(const LinearColor &color) = 0;
    virtual void Clear() = 0;

    static Ref<GraphicsAPI> Get();
};

} // namespace Toucan