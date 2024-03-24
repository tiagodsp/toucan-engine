#pragma once
#include "Layer.h"

namespace Toucan
{

/**
 * @brief Base Layer interface for initializing, deinitialize, updating and forward events to ImGui.
 */
class CORE_API ImGuiLayer : public Layer
{
  public:
    ImGuiLayer();
    static Ref<ImGuiLayer> Create();
    virtual void Begin() = 0;
    virtual void End() = 0;
};
} // namespace Toucan