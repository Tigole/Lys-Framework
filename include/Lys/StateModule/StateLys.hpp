#ifndef _LYS_STATE_LYS_HPP
#define _LYS_STATE_LYS_HPP 1

#include "State.hpp"

#include <cstddef>

namespace lys
{

class State_Lys : public State
{
public:
    State_Lys();

    void mt_OnEvent(const Event& event) override;
    void mt_OnUpdate(float elapsed_time) override;

    std::size_t m_Next_State;

    bool m_Condition_Change_State;
};



}


#endif // _LYS_STATE_LYS_HPP
