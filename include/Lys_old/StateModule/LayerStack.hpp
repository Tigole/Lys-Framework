#ifndef _LYS_LAYER_STACK_HPP
#define _LYS_LAYER_STACK_HPP 1

#include <utility>
#include <vector>

#include "Lys/Application/Event.hpp"
#include "Lys/LysConfig.hpp"
#include "Lys/StateModule/Layer.hpp"

namespace lys
{

class StateManager;

struct Event;

struct Message_ChangeState;

class LYS_API LayerStack
{
public:
    /// Last registered is on top
    void mt_Register_Layer(Layer* layer, bool default_activation);
    void mt_Activate_Layer(Layer* layer);
    void mt_Deactivate_Layer(Layer* layer);

    void mt_Clean_Active_Layers(void);

    void mt_On_Event_Closed(const WindowCloseRequestEvent& event);
    void mt_On_Event_Resized(const WindowResizeEvent& event);
    void mt_On_Event_FocusLost(const WindowFocusLostEvent& event);
    void mt_On_Event_FocusGained(const WindowFocusGainedEvent& event);

    void mt_On_Event_TextEntered(const TextEvent& event);

    void mt_On_Event_KeyPressed(const KeyPressedEvent& event);
    void mt_On_Event_KeyReleased(const KeyReleasedEvent& event);

    void mt_On_Event_MouseButtonPressed(const MouseButtonPressedEvent& event);
    void mt_On_Event_MouseButtonReleased(const MouseButtonReleasedEvent& event);
    void mt_On_Event_MouseMoved(const MouseMovedEvent& event);
    void mt_On_Event_MouseWheelScrolled(const MouseWheelScrolledEvent& event);

    void mt_On_Event_JoystickConnected(const JoystickConnectedEvent& event);
    void mt_On_Event_JoystickDisconnected(const JoystickDisconnectedEvent& event);
    void mt_On_Event_JoystickButtonPressed(const JoystickButtonPressedEvent& event);
    void mt_On_Event_JoystickButtonReleased(const JoystickButtonReleasedEvent& event);
    void mt_On_Event_JoystickMoved(const JoystickMovedEvent& event);

    void mt_On_Update(float elapsed_time);
    void mt_On_Render(void);

private:
    void mt_Set_Layer_Activation(Layer* layer, bool activation);

    template<typename EventType>
    void mt_Handle_Event(const EventType& event, LayerForward (Layer::*function)(const EventType&))
    {
        LayerForward l_Forward;

        l_Forward = LayerForward::Continue;
        for (auto it = m_Layers.rbegin(); (it != m_Layers.rend()) && (l_Forward == LayerForward::Continue); it++)
        {
            if (it->second == true)
            {
                Layer* l_Layer = it->first;
                l_Forward      = (l_Layer->*function)(event);
            }
        }
    }

    std::vector<std::pair<Layer*, bool>> m_Layers = {};
};
}  // namespace lys

#endif  // _LYS_LAYER_STACK_HPP
