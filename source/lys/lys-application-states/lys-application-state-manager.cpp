#include "lys-application-states/lys-application-state-manager.hpp"

#if 0
#include "Lys/Core/Profiler.hpp"
#include "Lys/Log/Log.hpp"
#endif

namespace lys
{

ApplicationStateManager::ApplicationStateManager() :
    m_State_Registry(),
    m_Loading_State(nullptr),
    m_Current_State(nullptr),
    m_Active_State(nullptr),
    m_Current_State_Idx(-2),
    m_Working_Thread(),
    m_Loading_Task("StateManager", &ApplicationStateManager::Loading_Task, this)
{}

ApplicationStateManager::~ApplicationStateManager()
{
    Clear();
}

void ApplicationStateManager::Change_State(std::size_t new_state_id, std::size_t loading_state_id)
{
#if 0
    LYS_LOG_CORE_DEBUG("Request change state: '%d' -> '%d'", m_Current_State.get(), new_state_id);
#endif
    if (m_Loading_State != nullptr)
    {
#if 0
        LYS_LOG_CORE_FATAL("Already changing state\n");
#endif
        LYS_ASSERT(false);
    }
    auto nextIt = m_State_Registry.find(new_state_id);
    if (nextIt == m_State_Registry.end())
    {
#if 0
        LYS_LOG_CORE_FATAL("No state registered: %zu", new_state_id);
#endif
        LYS_ASSERT(false);
    }
    m_Next_State = nextIt->second();

    auto loadingIt = m_State_Registry.find(loading_state_id);
    if (loadingIt != m_State_Registry.end())
    {
#if 0
        LYS_LOG_CORE_DEBUG("Request change state using loading state");
#endif
        m_Loading_State.reset(loadingIt->second());
        m_Loading_State->On_Entry();
        m_Loading_Task.Push_Order(new_state_id, m_Working_Thread);
        m_Active_State = m_Loading_State.get();
    }
    else
    {
#if 0
        LYS_LOG_CORE_DEBUG("Request change state without loading state");
#endif
    }
}

std::size_t ApplicationStateManager::Get_Current_State(void) const
{
    return m_Current_State_Idx;
}

void ApplicationStateManager::Clear(void)
{
    if (m_Current_State != nullptr)
    {
        m_Current_State->On_Exit();
        m_Current_State->On_Destroy();
        m_Current_State.reset(nullptr);
    }
}

void ApplicationStateManager::On_Update_Logic(void)
{
#if 0
    LYS_PROFILE_FUNCTION;
    /*LYS_LOG_CORE_DEBUG("active: %p, next: %p, load: %p, curr: %p", m_Active_State, m_Next_State, m_Loading_State.get(),
                       m_Current_State.get());*/
#endif
    On_Update_Loading();
    m_Active_State->Update_Logic();
}

void ApplicationStateManager::On_Update_Render(void)
{
    m_Active_State->Update_Render();
}

void ApplicationStateManager::On_Update_Loading(void)
{
    if (m_Loading_State != nullptr)
    {
        std::size_t l_New_State;

        if (m_Loading_Task.Pop_Result(l_New_State))
        {
            m_Current_State_Idx = l_New_State;

            if (m_Loading_State != nullptr)
            {
                m_Loading_State->On_Exit();
            }

            Deinitialize_State(m_Loading_State.get());
            m_Loading_State.reset(nullptr);

            Switch_State();
        }
    }
    else if (m_Next_State != nullptr)
    {
        if (m_Current_State != nullptr)
        {
            m_Current_State->On_Exit();
        }
        m_Next_State->On_Entry();
        Switch_State();
    }
}

void ApplicationStateManager::Switch_State(void)
{
    if (m_Current_State != nullptr)
    {
        Deinitialize_State(m_Current_State.get());
    }
    m_Current_State.reset(m_Next_State);
    m_Active_State = m_Current_State.get();
    m_Next_State   = nullptr;
}

void ApplicationStateManager::Initialize_State(ApplicationState* s)
{
    s->m_State_Manager = this;
    s->On_Create();
}

void ApplicationStateManager::Deinitialize_State(ApplicationState* s)
{
    s->On_Destroy();
}

bool ApplicationStateManager::Loading_Task(std::size_t& next_state)
{
    m_Current_State->On_Exit();
    m_Next_State->On_Entry();
    return true;
}

}  // namespace lys
