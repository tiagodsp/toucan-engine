#include "Layer.h"

namespace Toucan
{

Layer::Layer(const String &name) : m_Name(name) {}

Layer::~Layer() {}

void Layer::OnAttach() {}

void Layer::OnDetach() {}

void Layer::OnUpdate() {}

void Layer::OnImGuiRender() {}

void Layer::OnEvent(Event *event) {}

} // namespace Toucan