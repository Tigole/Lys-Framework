#include "Lys/StateModule/StateManager.hpp"

#include "Lys/Core/Log.hpp"
#include "Lys/Core/Profiler.hpp"

namespace lys
{

StateManager::StateManager() :
    m_States(),
    m_Loading_State(nullptr),
    m_Current_State(-2),
    m_Loading_Task("StateManager", &StateManager::mt_Loading_Task, this),
    m_Loading(false)
{}

void StateManager::mt_Add_State(std::size_t state_id, State* s)
{
    s->m_State_Manager = this;
    m_States.emplace(state_id, s);
    s->mt_On_Create();
}

void StateManager::mt_Set_Loading_State(State* s)
{
    m_Loading_State.reset(s);
}

void StateManager::mt_Change_State(std::size_t new_state_id)
{
    m_Loading = true;
    m_Loading_Task.mt_Push_Order(new_state_id);

    LYS_LOG_CORE_TRACE("Request change state: '%d' -> '%d'", m_Current_State, new_state_id);

    if (m_Loading_State != nullptr)
    {
        m_Loading_State->mt_On_Entry();
    }
}

std::size_t StateManager::mt_Get_Current_State(void) const
{
    return m_Current_State;
}

void StateManager::mt_On_Update(float elapsed_time)
{
    LYS_PROFILE_FUNCTION;
    State* l_State = (m_Loading == true) ? m_Loading_State.get() : m_States.find(m_Current_State)->second.get();

    l_State->mt_UpdateLogic(elapsed_time);
    l_State->mt_UpdateRender();

    if (m_Loading == true)
    {
        std::size_t l_New_State;

        if (m_Loading_Task.mt_Pop_Result(l_New_State))
        {
            m_Current_State = l_New_State;

            if (m_Loading_State != nullptr)
            {
                m_Loading_State->mt_On_Exit();
            }

            m_Loading = false;
        }
    }
}

void StateManager::mt_On_Event_Closed(const WindowCloseRequestEvent& event)
{
    mt_On_Event(event, &State::mt_On_Event_Closed);
}

void StateManager::mt_On_Event_Resized(const WindowResizeEvent& event)
{
    mt_On_Event(event, &State::mt_On_Event_Resized);
}

void StateManager::mt_On_Event_FocusLost(const WindowFocusLostEvent& event)
{
    mt_On_Event(event, &State::mt_On_Event_FocusLost);
}

void StateManager::mt_On_Event_FocusGained(const WindowFocusGainedEvent& event)
{
    mt_On_Event(event, &State::mt_On_Event_FocusGained);
}

void StateManager::mt_On_Event_TextEntered(const TextEvent& event)
{
    mt_On_Event(event, &State::mt_On_Event_TextEntered);
}

void StateManager::mt_On_Event_KeyPressed(const KeyPressedEvent& event)
{
    mt_On_Event(event, &State::mt_On_Event_KeyPressed);
}

void StateManager::mt_On_Event_KeyReleased(const KeyReleasedEvent& event)
{
    mt_On_Event(event, &State::mt_On_Event_KeyReleased);
}

void StateManager::mt_On_Event_MouseButtonPressed(const MouseButtonPressedEvent& event)
{
    mt_On_Event(event, &State::mt_On_Event_MouseButtonPressed);
}

void StateManager::mt_On_Event_MouseButtonReleased(const MouseButtonReleasedEvent& event)
{
    mt_On_Event(event, &State::mt_On_Event_MouseButtonReleased);
}

void StateManager::mt_On_Event_MouseMoved(const MouseMovedEvent& event)
{
    mt_On_Event(event, &State::mt_On_Event_MouseMoved);
}

void StateManager::mt_On_Event_MouseWheelScrolled(const MouseWheelScrolledEvent& event)
{
    mt_On_Event(event, &State::mt_On_Event_MouseWheelScrolled);
}

void StateManager::mt_On_Event_JoystickConnected(const JoystickConnectedEvent& event)
{
    mt_On_Event(event, &State::mt_On_Event_JoystickConnected);
}

void StateManager::mt_On_Event_JoystickDisconnected(const JoystickDisconnectedEvent& event)
{
    mt_On_Event(event, &State::mt_On_Event_JoystickDisconnected);
}

void StateManager::mt_On_Event_JoystickButtonPressed(const JoystickButtonPressedEvent& event)
{
    mt_On_Event(event, &State::mt_On_Event_JoystickButtonPressed);
}

void StateManager::mt_On_Event_JoystickButtonReleased(const JoystickButtonReleasedEvent& event)
{
    mt_On_Event(event, &State::mt_On_Event_JoystickButtonReleased);
}

void StateManager::mt_On_Event_JoystickMoved(const JoystickMovedEvent& event)
{
    mt_On_Event(event, &State::mt_On_Event_JoystickMoved);
}

bool StateManager::mt_Loading_Task(std::size_t& next_state)
{
    bool l_b_Ret         = true;
    auto l_Current_State = m_States.find(m_Current_State);
    auto l_Next_State    = m_States.find(next_state);

    if (l_Current_State != m_States.end())
    {
        l_b_Ret = l_Current_State->second->mt_On_Exit();
    }

    if ((l_b_Ret == true) && (l_Next_State != m_States.end()))
    {
        l_b_Ret = l_Next_State->second->mt_On_Entry();
    }

    return l_b_Ret;
}

}  // namespace lys
