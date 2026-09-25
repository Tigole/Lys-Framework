#ifndef _LYS_STATE_MANAGER_HPP
#define _LYS_STATE_MANAGER_HPP 1

#include <map>
#include <memory>

#include "Lys/Application/Event.hpp"
#include "Lys/Core/Log.hpp"
#include "Lys/Core/Profiler.hpp"
#include "Lys/StateModule/State.hpp"
#include "Lys/WorkingModule/WorkingTask.hpp"

namespace lys
{

class LYS_API StateManager
{
public:
    StateManager();

    template<class StateType>
    void mt_Register_State(std::size_t state_id)
    {
        auto it = m_State_Registry.find(state_id);
        if (it != m_State_Registry.end())
        {
            LYS_LOG_CORE_FATAL("State with id is already registered: %zu", state_id);
            LYS_ASSERT(false);
        }
        m_State_Registry.emplace(state_id, [this]()
        {
            State* state = new StateType();
            Initialize_State(state);
            return state;
        });
        /*if (m_Current_State == nullptr)
        {
            m_Current_State = m_State_Registry[state_id];
            Initialize_State(m_Current_State.get());
        }*/
    }
    template<class StateType>
    void Set_Initial_State(std::size_t state_id, std::function<void(StateType*)> init)
    {
        LYS_LOG_CORE_INFORMATION("Set initial state: %zu", state_id);
        auto it = m_State_Registry.find(state_id);
        if (it == m_State_Registry.end())
        {
            LYS_LOG_CORE_FATAL("No state registered: %zu", state_id);
            LYS_ASSERT(false);
        }
        m_Current_State.reset(it->second());
        Initialize_State(m_Current_State.get());
        StateType* s = dynamic_cast<StateType*>(m_Current_State.get());
        if (s == nullptr)
        {
            LYS_LOG_CORE_FATAL("State type does not match");
            LYS_ASSERT(false);
        }
        init(s);
        m_Current_State->mt_On_Entry();
        m_Active_State = m_Current_State.get();
    }
    void mt_Change_State(std::size_t new_state_id, std::size_t loading_state_id = -1);
    std::size_t mt_Get_Current_State(void) const;

    void mt_On_Update(float elapsed_time);

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

private:
    std::map<std::size_t, std::function<State*()>> m_State_Registry;
    std::unique_ptr<State> m_Loading_State;
    std::unique_ptr<State> m_Current_State;
    State* m_Next_State;
    State* m_Active_State;
    std::size_t m_Current_State_Idx;
    void Initialize_State(State* s);
    void Deinitialize_State(State* s);

    WorkingTask<std::size_t> m_Loading_Task;
    bool mt_Loading_Task(std::size_t& next_state);

    void On_Update_Loading(void);
    void Switch_State(void);

    template<typename EventType>
    void mt_On_Event(const EventType& event, void (State::*method)(const EventType&))
    {
        LYS_PROFILE_FUNCTION;
        State* l_State = (m_Loading_State != nullptr) ? (m_Loading_State.get()) : (m_Current_State.get());
        (l_State->*method)(event);
    }
};

}  // namespace lys

#endif  // _LYS_STATE_MANAGER_HPP
