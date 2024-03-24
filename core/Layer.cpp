#include "Layer.h"
#include <imgui.h>

namespace Toucan
{

Layer::Layer(const String &name) : m_Name(name) {}

Layer::~Layer() {}

void Layer::OnAttach() {}

void Layer::OnDetach() {}

void Layer::OnUpdate() {}

void Layer::OnImGuiRender(ImGuiContext* context) {}

void Layer::OnEvent(Event *event) {}

} // namespace Toucan