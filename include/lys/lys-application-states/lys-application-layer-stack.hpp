#ifndef _LYS_APPLICATION_LAYER_STACK_HPP
#define _LYS_APPLICATION_LAYER_STACK_HPP 1

#include <utility>
#include <vector>

#if 0
#include "Lys/Application/Event.hpp"
#endif
#include "lys-application-states/lys-application-layer.hpp"
#include "lys-config.hpp"

namespace lys
{

class StateManager;

struct Event;

struct Message_ChangeState;

class LYS_API ApplicationLayerStack
{
public:
    /// Last registered is on top
    void Register_Layer(ApplicationLayer* layer, bool default_activation);
    void Activate_Layer(ApplicationLayer* layer);
    void Deactivate_Layer(ApplicationLayer* layer);

    void Clean_Active_Layers(void);
    void On_Update(void);
    void On_Render(void);

private:
    void Set_Layer_Activation(ApplicationLayer* layer, bool activation);

    std::vector<std::pair<ApplicationLayer*, bool>> m_Layers = {};
};
}  // namespace lys

#endif  // _LYS_APPLICATION_LAYER_STACK_HPP
