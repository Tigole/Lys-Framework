#include "Lys/StateModule/StateManager.hpp"

#include "Lys/Core/Log.hpp"
#include "Lys/Core/Profiler.hpp"

namespace lys
{

StateManager::StateManager() :
    m_State_Registry(),
    m_Loading_State(nullptr),
    m_Current_State(nullptr),
    m_Active_State(nullptr),
    m_Current_State_Idx(-2),
    m_Loading_Task("StateManager", &StateManager::mt_Loading_Task, this)
{}

void StateManager::mt_Change_State(std::size_t new_state_id, std::size_t loading_state_id)
{
    LYS_LOG_CORE_DEBUG("Request change state: '%d' -> '%d'", m_Current_State.get(), new_state_id);
    if (m_Loading_State != nullptr)
    {
        LYS_LOG_CORE_FATAL("Already changing state\n");
        LYS_ASSERT(false);
    }
    auto nextIt = m_State_Registry.find(new_state_id);
    if (nextIt == m_State_Registry.end())
    {
        LYS_LOG_CORE_FATAL("No state registered: %zu", new_state_id);
        LYS_ASSERT(false);
    }
    m_Next_State = nextIt->second();
    Initialize_State(m_Next_State);

    auto loadingIt = m_State_Registry.find(loading_state_id);
    if (loadingIt != m_State_Registry.end())
    {
        LYS_LOG_CORE_DEBUG("Request change state using loading state");
        m_Loading_State.reset(loadingIt->second());
        m_Loading_State->mt_On_Entry();
        m_Loading_Task.mt_Push_Order(new_state_id);
        m_Active_State = m_Loading_State.get();
    }
    else
    {
        LYS_LOG_CORE_DEBUG("Request change state without loading state");
        m_Current_State->mt_On_Exit();
        m_Next_State->mt_On_Entry();
        Switch_State();
    }
}

std::size_t StateManager::mt_Get_Current_State(void) const
{
    return m_Current_State_Idx;
}

void StateManager::mt_On_Update(float elapsed_time)
{
    LYS_PROFILE_FUNCTION;
    /*LYS_LOG_CORE_DEBUG("active: %p, next: %p, load: %p, curr: %p", m_Active_State, m_Next_State, m_Loading_State.get(),
                       m_Current_State.get());*/
    m_Active_State->mt_UpdateLogic(elapsed_time);
    m_Active_State->mt_UpdateRender();
    On_Update_Loading();
}

void StateManager::On_Update_Loading(void)
{
    if (m_Loading_State != nullptr)
    {
        std::size_t l_New_State;

        if (m_Loading_Task.mt_Pop_Result(l_New_State))
        {
            m_Current_State_Idx = l_New_State;

            if (m_Loading_State != nullptr)
            {
                m_Loading_State->mt_On_Exit();
            }

            Deinitialize_State(m_Loading_State.get());
            m_Loading_State.reset(nullptr);

            Switch_State();
        }
    }
}

void StateManager::Switch_State(void)
{
    Deinitialize_State(m_Current_State.get());
    m_Current_State.reset(m_Next_State);
    m_Active_State = m_Current_State.get();
    m_Next_State   = nullptr;
}

void StateManager::Initialize_State(State* s)
{
    s->m_State_Manager = this;
    s->mt_On_Create();
}

void StateManager::Deinitialize_State(State* s)
{
    s->mt_On_Destroy();
}

bool StateManager::mt_Loading_Task(std::size_t& next_state)
{
    bool l_b_Ret = true;

    if (m_Current_State != nullptr)
    {
        l_b_Ret = m_Current_State->mt_On_Exit();
    }

    if (l_b_Ret == true)
    {
        l_b_Ret = m_Next_State->mt_On_Entry();
    }

    return l_b_Ret;
}

}  // namespace lys
