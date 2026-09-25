#ifndef _LYS_APPLICATION_STATE_MANAGER_HPP
#define _LYS_APPLICATION_STATE_MANAGER_HPP 1

#include <map>
#include <memory>

#if 0
#include "Lys/Application/Event.hpp"
#include "Lys/Core/Profiler.hpp"
#include "Lys/Log/Log.hpp"
#endif
#include "lys-application-states/lys-application-state.hpp"
#include "lys-config.hpp"
#include "lys-working-thread/lys-working-task.hpp"

namespace lys
{

class LYS_API ApplicationStateManager
{
public:
    ApplicationStateManager();
    ~ApplicationStateManager();

    template<class StateType>
    void Register_State(std::size_t state_id)
    {
        auto it = m_State_Registry.find(state_id);
        if (it != m_State_Registry.end())
        {
#if 0
            LYS_LOG_CORE_FATAL("State with id is already registered: %zu", state_id);
#endif
            LYS_ASSERT(false);
        }
        m_State_Registry.emplace(state_id, [this]()
        {
            ApplicationState* state = new StateType();
            Initialize_State(state);
            return state;
        });
    }
    template<class StateType>
    void Set_Initial_State(std::size_t state_id, std::function<void(StateType&)> init = nullptr)
    {
#if 0
        LYS_LOG_CORE_INFORMATION("Set initial state: %zu", state_id);
#endif
        auto it = m_State_Registry.find(state_id);
        if (it == m_State_Registry.end())
        {
#if 0
            LYS_LOG_CORE_FATAL("No state registered: %zu", state_id);
#endif
            LYS_ASSERT(false);
        }
        m_Next_State = it->second();
        if (init != nullptr)
        {
            StateType* s = dynamic_cast<StateType*>(m_Next_State);
            if (s == nullptr)
            {
#if 0
            LYS_LOG_CORE_FATAL("State type does not match");
#endif
                LYS_ASSERT(false);
            }
            init(*s);
        }
    }
    void Change_State(std::size_t new_state_id, std::size_t loading_state_id = -1);
    std::size_t Get_Current_State(void) const;

    void Clear(void);

    void On_Update_Logic(void);
    void On_Update_Render(void);

private:
    std::map<std::size_t, std::function<ApplicationState*()>> m_State_Registry;
    std::unique_ptr<ApplicationState> m_Loading_State;
    std::unique_ptr<ApplicationState> m_Current_State;
    ApplicationState* m_Next_State;
    ApplicationState* m_Active_State;
    std::size_t m_Current_State_Idx;
    void Initialize_State(ApplicationState* s);
    void Deinitialize_State(ApplicationState* s);

    WorkingThread m_Working_Thread;
    WorkingTask<std::size_t> m_Loading_Task;
    bool Loading_Task(std::size_t& next_state);

    void On_Update_Loading(void);
    void Switch_State(void);
};

}  // namespace lys

#endif  // _LYS_APPLICATION_STATE_MANAGER_HPP
