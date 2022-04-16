#ifndef _LYS_LAYER_LYS_HPP
#define _LYS_LAYER_LYS_HPP 1

#include "Lys/StateModule/Layer.hpp"

#include <cstddef>

namespace lys
{

struct KeyEvent;

class LayerLys : public Layer
{
public:
    LayerLys();

    LayerEventForward mt_OnUpdate([[maybe_unused]] float elapsed_time) override;
    LayerEventForward mt_OnRender(void) override;

    void mt_OnKeyEvent(const KeyEvent& key_event);

    std::size_t m_Next_State;

    bool m_Condition_Change_State;
};


}

#endif // _LYS_LAYER_LYS_HPP
