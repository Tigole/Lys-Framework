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
    s->mt_OnCreate();
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
        m_Loading_State->mt_OnEntry();
    }
}

std::size_t StateManager::mt_Get_Current_State(void) const
{
    return m_Current_State;
}

void StateManager::mt_OnUpdate(float elapsed_time)
{
    LYS_PROFILE_FUNCTION;
    if (m_Loading == true)
    {
        std::size_t l_New_State;

        if (m_Loading_State != nullptr)
        {
            m_Loading_State->mt_OnUpdate(elapsed_time);
        }

        if (m_Loading_Task.mt_Pop_Result(l_New_State))
        {
            m_Current_State = l_New_State;

            if (m_Loading_State != nullptr)
            {
                m_Loading_State->mt_OnExit();
            }

            m_Loading = false;
        }
    }
    else
    {
        auto l_Current_State = m_States.find(m_Current_State)->second.get();
        l_Current_State->mt_OnUpdate(elapsed_time);
    }
}

void StateManager::mt_OnEvent(const Event& event)
{
    LYS_PROFILE_FUNCTION;
    if (m_Loading == true)
    {
        if (m_Loading_State != nullptr)
        {
            m_Loading_State->mt_OnEvent(event);
        }
    }
    else
    {
        m_States[m_Current_State]->mt_OnEvent(event);
    }
}


bool StateManager::mt_Loading_Task(std::size_t& next_state)
{
    bool l_b_Ret = true;
    auto l_Current_State = m_States.find(m_Current_State);
    auto l_Next_State = m_States.find(next_state);

    if (l_Current_State != m_States.end())
    {
        l_b_Ret = l_Current_State->second->mt_OnExit();
    }

    if ((l_b_Ret == true) && (l_Next_State != m_States.end()))
    {
        l_b_Ret = l_Next_State->second->mt_OnEntry();
    }

    return l_b_Ret;
}



}
