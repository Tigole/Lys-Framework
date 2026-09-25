#include "lys-application-states/lys-application-layer-stack.hpp"

#include <algorithm>

#if 0
#include "Lys/Log/Log.hpp"
#endif

namespace lys
{

void ApplicationLayerStack::Register_Layer(ApplicationLayer* layer, bool default_activation)
{
    m_Layers.push_back(std::make_pair(layer, false));
    Set_Layer_Activation(layer, default_activation);
}

void ApplicationLayerStack::Activate_Layer(ApplicationLayer* layer)
{
    layer->On_Activate();
    Set_Layer_Activation(layer, true);
}

void ApplicationLayerStack::Deactivate_Layer(ApplicationLayer* layer)
{
    layer->On_Deactivate();
    Set_Layer_Activation(layer, false);
}

void ApplicationLayerStack::Clean_Active_Layers(void)
{
    for (std::size_t ii = 0; ii < m_Layers.size(); ii++)
    {
        m_Layers[ii].second = false;
    }
}

void ApplicationLayerStack::On_Update(void)
{
    ApplicationLayerForward l_Forward;

    l_Forward = ApplicationLayerForward::Continue;
    for (auto it = m_Layers.rbegin(); (it != m_Layers.rend()) && (l_Forward == ApplicationLayerForward::Continue); it++)
    {
        if (it->second == true)
        {
            l_Forward = it->first->On_Update();
        }
    }
}

void ApplicationLayerStack::On_Render(void)
{
    ApplicationLayerForward l_Forward = ApplicationLayerForward::Stop;
    std::size_t l_First_Rendering_Layer_Id;

    for (l_First_Rendering_Layer_Id = m_Layers.size() - 1; true; l_First_Rendering_Layer_Id--)
    {
        if ((m_Layers[l_First_Rendering_Layer_Id].second == true) &&
            (m_Layers[l_First_Rendering_Layer_Id].first->Get_Rendering_Forward_Strategy() == ApplicationLayerForward::Stop))
        {
            break;
        }
        if (l_First_Rendering_Layer_Id == 0)
        {
            l_Forward = ApplicationLayerForward::Continue;
            break;
        }
    }

    for (; l_First_Rendering_Layer_Id < m_Layers.size(); l_First_Rendering_Layer_Id++)
    {
        if (m_Layers[l_First_Rendering_Layer_Id].second == true)
        {
            m_Layers[l_First_Rendering_Layer_Id].first->On_Render();
        }
    }
}

void ApplicationLayerStack::Set_Layer_Activation(ApplicationLayer* layer, bool activation)
{
    auto it = std::find_if(m_Layers.begin(), m_Layers.end(), [&](const std::pair<ApplicationLayer*, bool>& p) { return p.first == layer; });

    if (it != m_Layers.end())
    {
#if 0
        LYS_LOG_CORE_DEBUG("'%s' activation: %d -> %d", it->first->Get_Layer_Id(), it->second, activation);
#endif
        it->second = activation;
    }
}

}  // namespace lys
