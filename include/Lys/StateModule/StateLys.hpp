#ifndef _LYS_STATE_LYS_HPP
#define _LYS_STATE_LYS_HPP 1

#include "State.hpp"
#include "LayerLys.hpp"

#include <cstddef>

namespace lys
{

class LYS_API State_Lys : public State
{
public:
    State_Lys();

    bool mt_On_Entry(void) override;
    bool mt_On_Exit(void) override;

    void mt_Set_Next_State(std::size_t next_state);

private:

    LayerLys m_Layer;
};



}


#endif // _LYS_STATE_LYS_HPP
