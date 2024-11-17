#ifndef _LYS_STATE_HPP
#define _LYS_STATE_HPP 1

#include <memory>
#include <mutex>
#include <vector>

#include "Lys/Application/Event.hpp"
#include "Lys/LysConfig.hpp"
#include "Lys/StateModule/Layer.hpp"

namespace lys
{

class StateManager;
class Layer;

struct Event;

struct Message_ChangeState;

class LYS_API State
{
    friend StateManager;

public:
    virtual ~State();

    virtual bool mt_On_Create(void);
    virtual bool mt_On_Destroy(void);

    virtual bool mt_On_Entry(void);
    virtual bool mt_On_Exit(void);

    void mt_On_Update(float elapsed_time);

    void mt_On_Event_TextEntered(const TextEvent& event);

    void mt_On_Event_KeyPressed(const KeyPressedEvent& event);
    void mt_On_Event_KeyReleased(const KeyReleasedEvent& event);

    void mt_On_Event_MouseButtonPressed(const MouseButtonPressedEvent& event);
    void mt_On_Event_MouseButtonReleased(const MouseButtonReleasedEvent& event);
    void mt_On_Event_MouseMove(const MouseMoveEvent& event);
    void mt_On_Event_MouseWheelScroll(const MouseWheelScrollEvent& event);

    void mt_On_Event_JoystickConnected(const JoystickConnectedEvent& event);
    void mt_On_Event_JoystickDisconnected(const JoystickDisconnectedEvent& event);
    void mt_On_Event_JoystickButtonPressed(const JoystickButtonPressedEvent& event);
    void mt_On_Event_JoystickButtonReleased(const JoystickButtonReleasedEvent& event);
    void mt_On_Event_JoystickMove(const JoystickMoveEvent& event);

protected:
    void mt_Push_Layer(Layer* layer);
    void mt_Pop_Layer(Layer* layer);

private:
    void mt_Update_Active_Layers(float elapsed_time);
    void mt_Render_Active_Layers(void);
    void mt_Pop_Pending_Layers(void);
    void mt_Push_Pending_Layers(void);

    std::vector<lys::Layer*> m_Active_Layers;
    std::vector<lys::Layer*> m_Pop_Layers;
    std::vector<lys::Layer*> m_Push_Layers;

    void mt_On_Change_State(const Message_ChangeState& msg);

    template<typename EventType>
    void mt_On_Event(const EventType& event, lys::LayerForward (Layer::*method)(const EventType&))
    {
        lys::LayerForward l_Forward;

        l_Forward = lys::LayerForward::Continue;
        for (auto it = m_Active_Layers.rbegin(); (it != m_Active_Layers.rend()) && (l_Forward == lys::LayerForward::Continue); it++)
        {
            l_Forward = ((*it)->*method)(event);
        }
    }

    StateManager* m_State_Manager;
};

}  // namespace lys

#endif  // _LYS_STATE_HPP
