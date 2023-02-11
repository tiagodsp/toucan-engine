#pragma once

#include "Toucan.h"

namespace Toucan
{

class Layer;

class LayerStack
{
  private:
    Array<Ref<Layer>> m_Layers;
    unsigned int m_LayerInsertIndex = 0;

  public:
    LayerStack();
    ~LayerStack();

    void PushLayer(Ref<Layer> layer);
    void PushOverlay(Ref<Layer> overlay);
    void PopLayer(Ref<Layer> layer);
    void PopOverlay(Ref<Layer> overlay);

    Array<Ref<Layer>>::iterator begin() { return m_Layers.begin(); }
    Array<Ref<Layer>>::iterator end() { return m_Layers.end(); }
};

} // namespace Toucan