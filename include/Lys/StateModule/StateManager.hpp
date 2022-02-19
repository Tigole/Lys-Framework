#ifndef _LYS_STATE_MANAGER_HPP
#define _LYS_STATE_MANAGER_HPP 1

#include "State.hpp"
#include "Lys/WorkingModule/WorkingTask.hpp"

#include <map>
#include <memory>

namespace lys
{

struct Event;

class StateManager
{
public:
    StateManager();

    void mt_Add_State(std::size_t state_id, State* s);
    void mt_Set_Loading_State(State* s);
    void mt_Change_State(std::size_t new_state_id);
    std::size_t mt_Get_Current_State(void) const;

    void mt_OnUpdate(float elapsed_time);
    void mt_OnEvent(const Event& event);


private:
    std::map<std::size_t, std::unique_ptr<State>> m_States;
    std::unique_ptr<State> m_Loading_State;
    std::size_t m_Current_State;

    WorkingTask<std::size_t> m_Loading_Task;
    bool m_Loading;
    bool mt_Loading_Task(std::size_t& next_state);
};



}


#endif // _LYS_STATE_MANAGER_HPP
