#include "Lys/StateModule/StateLys.hpp"

namespace lys
{


State_Lys::State_Lys() : m_Layer()
{}

bool State_Lys::mt_OnEntry(void)
{
    mt_Push_Layer(&m_Layer);

    return true;
}

bool State_Lys::mt_OnExit(void)
{
    mt_Pop_Layer();

    return true;
}

void State_Lys::mt_Set_Next_State(std::size_t next_state)
{
    m_Layer.m_Next_State = next_state;
}


}
