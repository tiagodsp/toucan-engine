#include "LayerStack.h"

namespace Toucan
{

LayerStack::LayerStack() {}

LayerStack::~LayerStack()
{
    m_Layers.clear();
}

void LayerStack::PushLayer(Ref<Layer> layer)
{
    m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex++, layer);
}

void LayerStack::PushOverlay(Ref<Layer> overlayer)
{
    m_Layers.emplace_back(overlayer);
}

void LayerStack::PopLayer(Ref<Layer> layer)
{
    auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
    if (it != m_Layers.end())
    {
        m_Layers.erase(it);
        m_LayerInsertIndex--;
    }
}

void LayerStack::PopOverlay(Ref<Layer> overlay)
{
    auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
    if (it != m_Layers.end())
    {
        m_Layers.erase(it);
    }
}

} // namespace Toucan