#pragma once
#include "CoreTypes.h"
#include <imgui.h>

namespace Toucan
{

class Event;

/**
 * @brief Base class for all layers
 */
class CORE_API Layer
{
  private:
    String m_Name;

  public:
    Layer(const String &name = "Layer");
    virtual ~Layer();

    virtual void OnAttach();
    virtual void OnDetach();
    virtual void OnUpdate();
    virtual void OnImGuiRender(ImGuiContext *context);
    virtual void OnEvent(Event *event);

    inline const std::string &GetName() const { return m_Name; }
};
} // namespace Toucan