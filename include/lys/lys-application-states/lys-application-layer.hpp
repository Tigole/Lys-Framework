#ifndef _LYS_APPLICATION_LAYER_HPP
#define _LYS_APPLICATION_LAYER_HPP 1

#if 0
#include "Lys/Application/Event.hpp"
#include "Lys/MessageModule/MessageManager.hpp"
#endif
#include "lys-config.hpp"

namespace lys
{

enum class ApplicationLayerForward
{
    Stop,
    Continue
};

class LYS_API ApplicationLayer
{
public:
    ApplicationLayer(const char* layer_id) : m_Layer_Id(layer_id) {}
    ApplicationLayer(const ApplicationLayer&)            = delete;
    ApplicationLayer& operator=(const ApplicationLayer&) = delete;
    virtual ~ApplicationLayer()                          = default;

    virtual void On_Activate(void) {}
    virtual void On_Deactivate(void) {}

    virtual ApplicationLayerForward On_Update(void)
    {
        return ApplicationLayerForward::Continue;
    }
    virtual void On_Render(void) {}

    virtual ApplicationLayerForward Get_Rendering_Forward_Strategy(void) const
    {
        return ApplicationLayerForward::Stop;
    }

    const char* Get_Layer_Id(void) const
    {
        return m_Layer_Id;
    }

protected:
    void Change_State(std::size_t new_state);

private:
    const char* m_Layer_Id = nullptr;
};

}  // namespace lys

#endif  // _LYS_APPLICATION_LAYER_HPP
