#include "Lys/StateModule/LayerStack.hpp"

#include "Lys/Core/Log.hpp"

namespace lys
{

void LayerStack::mt_Register_Layer(Layer* layer, bool default_activation)
{
    m_Layers.push_back(std::make_pair(layer, false));
    mt_Set_Layer_Activation(layer, default_activation);
}

void LayerStack::mt_Activate_Layer(Layer* layer)
{
    layer->mt_On_Activate();
    mt_Set_Layer_Activation(layer, true);
}

void LayerStack::mt_Deactivate_Layer(Layer* layer)
{
    layer->mt_On_Deactivate();
    mt_Set_Layer_Activation(layer, false);
}

void LayerStack::mt_Clean_Active_Layers(void)
{
    for (std::size_t ii = 0; ii < m_Layers.size(); ii++)
    {
        m_Layers[ii].second = false;
    }
}

void LayerStack::mt_On_Event_Closed(const WindowCloseRequestEvent& event)
{
    mt_Handle_Event(event, &Layer::mt_On_Event_Closed);
}

void LayerStack::mt_On_Event_Resized(const WindowResizeEvent& event)
{
    mt_Handle_Event(event, &Layer::mt_On_Event_Resized);
}

void LayerStack::mt_On_Event_FocusLost(const WindowFocusLostEvent& event)
{
    mt_Handle_Event(event, &Layer::mt_On_Event_FocusLost);
}

void LayerStack::mt_On_Event_FocusGained(const WindowFocusGainedEvent& event)
{
    mt_Handle_Event(event, &Layer::mt_On_Event_FocusGained);
}

void LayerStack::mt_On_Event_TextEntered(const TextEvent& event)
{
    mt_Handle_Event(event, &Layer::mt_On_Event_TextEntered);
}

void LayerStack::mt_On_Event_KeyPressed(const KeyPressedEvent& event)
{
    mt_Handle_Event(event, &Layer::mt_On_Event_KeyPressed);
}

void LayerStack::mt_On_Event_KeyReleased(const KeyReleasedEvent& event)
{
    mt_Handle_Event(event, &Layer::mt_On_Event_KeyReleased);
}

void LayerStack::mt_On_Event_MouseButtonPressed(const MouseButtonPressedEvent& event)
{
    mt_Handle_Event(event, &Layer::mt_On_Event_MouseButtonPressed);
}

void LayerStack::mt_On_Event_MouseButtonReleased(const MouseButtonReleasedEvent& event)
{
    mt_Handle_Event(event, &Layer::mt_On_Event_MouseButtonReleased);
}

void LayerStack::mt_On_Event_MouseMoved(const MouseMovedEvent& event)
{
    mt_Handle_Event(event, &Layer::mt_On_Event_MouseMoved);
}

void LayerStack::mt_On_Event_MouseWheelScrolled(const MouseWheelScrolledEvent& event)
{
    mt_Handle_Event(event, &Layer::mt_On_Event_MouseWheelScrolled);
}

#if 0
void LayerStack::mt_On_Event_MouseMovedRaw(const sf::Event::MouseMovedRaw& event)
{
     mt_Handle_Event(event, &Layer::mt_On_Event_MouseMovedRaw);
}

void LayerStack::mt_On_Event_MouseEntered(const sf::Event::MouseEntered& event)
{
     mt_Handle_Event(event, &Layer::mt_On_Event_MouseEntered);
}

void LayerStack::mt_On_Event_MouseLeft(const sf::Event::MouseLeft& event)
{
    mt_Handle_Event(event, &Layer::mt_On_Event_MouseLeft);
}
#endif

void LayerStack::mt_On_Event_JoystickConnected(const JoystickConnectedEvent& event)
{
    mt_Handle_Event(event, &Layer::mt_On_Event_JoystickConnected);
}

void LayerStack::mt_On_Event_JoystickDisconnected(const JoystickDisconnectedEvent& event)
{
    mt_Handle_Event(event, &Layer::mt_On_Event_JoystickDisconnected);
}

void LayerStack::mt_On_Event_JoystickButtonPressed(const JoystickButtonPressedEvent& event)
{
    mt_Handle_Event(event, &Layer::mt_On_Event_JoystickButtonPressed);
}

void LayerStack::mt_On_Event_JoystickButtonReleased(const JoystickButtonReleasedEvent& event)
{
    mt_Handle_Event(event, &Layer::mt_On_Event_JoystickButtonReleased);
}

void LayerStack::mt_On_Event_JoystickMoved(const JoystickMovedEvent& event)
{
    mt_Handle_Event(event, &Layer::mt_On_Event_JoystickMoved);
}

void LayerStack::mt_On_Update(float elapsed_time)
{
    LayerForward l_Forward;

    l_Forward = LayerForward::Continue;
    for (auto it = m_Layers.rbegin(); (it != m_Layers.rend()) && (l_Forward == LayerForward::Continue); it++)
    {
        if (it->second == true)
        {
            l_Forward = it->first->mt_On_Update(elapsed_time);
        }
    }
}

void LayerStack::mt_On_Render(void)
{
    LayerForward l_Forward = LayerForward::Stop;
    std::size_t l_First_Rendering_Layer_Id;

    for (l_First_Rendering_Layer_Id = m_Layers.size() - 1; true; l_First_Rendering_Layer_Id--)
    {
        if ((m_Layers[l_First_Rendering_Layer_Id].second == true) &&
            (m_Layers[l_First_Rendering_Layer_Id].first->mt_Get_Rendering_Forward_Strategy() == LayerForward::Stop))
        {
            break;
        }
        if (l_First_Rendering_Layer_Id == 0)
        {
            l_Forward = LayerForward::Continue;
            break;
        }
    }

    for (; l_First_Rendering_Layer_Id < m_Layers.size(); l_First_Rendering_Layer_Id++)
    {
        if (m_Layers[l_First_Rendering_Layer_Id].second == true)
        {
            m_Layers[l_First_Rendering_Layer_Id].first->mt_On_Render();
        }
    }
}

void LayerStack::mt_Set_Layer_Activation(Layer* layer, bool activation)
{
    auto it = std::find_if(m_Layers.begin(), m_Layers.end(), [&](const std::pair<Layer*, bool>& p) { return p.first == layer; });

    if (it != m_Layers.end())
    {
        LYS_LOG_CORE_DEBUG("'%s' activation: %d -> %d", it->first->mt_Get_Layer_Id(), it->second, activation);
        it->second = activation;
    }
}

}  // namespace lys
