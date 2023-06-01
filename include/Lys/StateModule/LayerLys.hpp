#ifndef _LYS_LAYER_LYS_HPP
#define _LYS_LAYER_LYS_HPP 1

#include "Lys/StateModule/Layer.hpp"

#include <cstddef>

namespace lys
{

struct KeyEvent;

class LYS_API LayerLys : public Layer
{
public:
    LayerLys();

    LayerForward mt_On_Update([[maybe_unused]] float elapsed_time) override;
    void mt_On_Render(void) override;

    LayerForward mt_On_Event_Key_Released(const KeyEvent& event) override;

    std::size_t m_Next_State;

    bool m_Condition_Change_State;

    float m_Remaining_Time;
};


}

#endif // _LYS_LAYER_LYS_HPP
