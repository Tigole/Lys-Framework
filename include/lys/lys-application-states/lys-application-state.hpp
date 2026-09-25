#ifndef _LYS_APPLICATION_STATE_HPP
#define _LYS_APPLICATION_STATE_HPP 1

#include <memory>
#include <mutex>
#include <vector>

#if 0
#include "Lys/Application/Event.hpp"
#endif
#include "lys-application-states/lys-application-layer-stack.hpp"
#include "lys-application-states/lys-application-layer.hpp"
#include "lys-config.hpp"

namespace lys
{

class ApplicationStateManager;

class LYS_API ApplicationState
{
    friend ApplicationStateManager;

public:
    virtual ~ApplicationState();

    /// Should not take a lot of time (frame friendly)
    virtual void On_Create(void);
    /// Should not take a lot of time (frame friendly)
    virtual void On_Destroy(void);

    /// May take a lot of time (may be called inside dedicated thread)
    virtual void On_Entry(void);
    /// May take a lot of time (may be called inside dedicated thread)
    virtual void On_Exit(void);

    void Update_Logic(void);
    void Update_Render(void);

protected:
    void Push_Layer(ApplicationLayer* layer);
    void Pop_Layer(ApplicationLayer* layer);

private:
    void Update_Active_Layers(void);
    void Render_Active_Layers(void);
    void Pop_Pending_Layers(void);
    void Push_Pending_Layers(void);

    std::vector<ApplicationLayer*> m_Active_Layers;
    std::vector<ApplicationLayer*> m_Pop_Layers;
    std::vector<ApplicationLayer*> m_Push_Layers;

    void On_Change_State(std::size_t state_id);

    ApplicationLayerStack m_Layer_Stack      = {};
    ApplicationStateManager* m_State_Manager = nullptr;
};

template<class LayerType>
class SingleApplicationLayerState: public ApplicationState
{
public:
    SingleApplicationLayerState() : m_Layer() {}

    void On_Entry(void) override
    {
        Push_Layer(&m_Layer);
    }

    void On_Exit(void) override
    {
        Pop_Layer(&m_Layer);
    }

private:
    LayerType m_Layer;
};

}  // namespace lys

#endif  // _LYS_APPLICATION_STATE_HPP
