#pragma once
#include "Layer.h"

namespace Toucan
{
class CORE_API ImGuiLayer : public Layer
{
  public:
    ImGuiLayer();
    static Ref<ImGuiLayer> Create();
};
} // namespace Toucan