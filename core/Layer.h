#pragma once
#include "CoreTypes.h"

namespace Toucan {

class Event;

class CORE_API Layer {
private:
    String m_Name;

public:
    Layer(const String& name = "Layer");
    virtual ~Layer();

    virtual void OnAttach() {}
    virtual void OnDetach() {}
    virtual void OnUpdate() {}
    virtual void OnImGuiRender() {}
    virtual void OnEvent(Event* event) {}

    inline const std::string& GetName() const { return m_Name; }
};
} // namespace Toucan