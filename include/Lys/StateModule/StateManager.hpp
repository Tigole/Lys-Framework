#ifndef _LYS_STATE_MANAGER_HPP
#define _LYS_STATE_MANAGER_HPP 1

#include <map>
#include <memory>

#include "Lys/Application/Event.hpp"
#include "Lys/Core/Profiler.hpp"
#include "Lys/WorkingModule/WorkingTask.hpp"
#include "State.hpp"

namespace lys
{

class LYS_API StateManager
{
public:
    StateManager();

    void mt_Add_State(std::size_t state_id, State* s);
    void mt_Set_Loading_State(State* s);
    void mt_Change_State(std::size_t new_state_id);
    std::size_t mt_Get_Current_State(void) const;

    void mt_OnUpdate(float elapsed_time);

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

private:
    std::map<std::size_t, std::unique_ptr<State>> m_States;
    std::unique_ptr<State> m_Loading_State;
    std::size_t m_Current_State;

    WorkingTask<std::size_t> m_Loading_Task;
    bool m_Loading;
    bool mt_Loading_Task(std::size_t& next_state);

    template<typename EventType>
    void mt_On_Event(const EventType& event, void (State::*method)(const EventType&))
    {
        LYS_PROFILE_FUNCTION;
        State* l_State = (m_Loading == true) ? (m_Loading_State.get()) : (m_States[m_Current_State].get());
        (l_State->*method)(event);
        // if (m_Loading == true)
        //{
        //     if (!= nullptr)
        //     {
        //         (m_Loading_State->*method)(event);
        //     }
        // }
        // else
        //{
        //     (m_States[m_Current_State]->*method)(event);
        // }
    }
};

}  // namespace lys

#endif  // _LYS_STATE_MANAGER_HPP
