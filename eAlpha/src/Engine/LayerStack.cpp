/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */
#include "pch.h"
#include "LayerStack.h"

namespace Engine
{

    LayerStack::LayerStack()
    {
    }

    LayerStack::~LayerStack()
    {
        for (Layer * layer : layers)
        {
            delete layer;
        }
    }

    void LayerStack::PushLayer(Layer * layer)
    {
        layers.emplace(layers.begin() + layerInsertIndex, layer);
        layerInsertIndex++;
        layer->OnAttatch();
    }

    void LayerStack::PushOverlay(Layer * overlay)
    {
        layers.emplace_back(overlay);
        overlay->OnAttatch(); 
    }
    
    void LayerStack::PopLayer(Layer * layer)
    {
        auto it = std::find(layers.begin(), layers.end(), layer);
        if (it != layers.end())
        {
            layers.erase(it);
            layerInsertIndex--;
        }
    }
    
    void LayerStack::PopOverlay(Layer * overlay)
    {
        auto it = std::find(layers.begin(), layers.end(), overlay);
        if (it != layers.end())
        {
            layers.erase(it);
        }
    }

}
