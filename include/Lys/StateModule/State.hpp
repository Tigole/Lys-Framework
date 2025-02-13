#ifndef _LYS_STATE_HPP
#define _LYS_STATE_HPP 1

#include <memory>
#include <mutex>
#include <vector>

#include "Lys/Application/Event.hpp"
#include "Lys/LysConfig.hpp"
#include "Lys/StateModule/Layer.hpp"
#include "Lys/StateModule/LayerStack.hpp"

namespace lys
{

class StateManager;

class LYS_API State
{
    friend StateManager;

public:
    virtual ~State();

    [[nodiscard]] virtual bool mt_On_Create(void);
    [[nodiscard]] virtual bool mt_On_Destroy(void);

    [[nodiscard]] virtual bool mt_On_Entry(void);
    [[nodiscard]] virtual bool mt_On_Exit(void);

    void mt_On_Event_Closed(const WindowCloseRequestEvent& event);
    void mt_On_Event_Resized(const WindowResizeEvent& event);
    void mt_On_Event_FocusLost(const WindowFocusLostEvent& event);
    void mt_On_Event_FocusGained(const WindowFocusGainedEvent& event);

    void mt_On_Event_TextEntered(const TextEvent& event);

    void mt_On_Event_KeyPressed(const KeyPressedEvent& event);
    void mt_On_Event_KeyReleased(const KeyReleasedEvent& event);

    void mt_On_Event_MouseButtonPressed(const MouseButtonPressedEvent& event);
    void mt_On_Event_MouseButtonReleased(const MouseButtonReleasedEvent& event);
    void mt_On_Event_MouseMoved(const MouseMovedEvent& event);
    void mt_On_Event_MouseWheelScrolled(const MouseWheelScrolledEvent& event);

    void mt_On_Event_JoystickConnected(const JoystickConnectedEvent& event);
    void mt_On_Event_JoystickDisconnected(const JoystickDisconnectedEvent& event);
    void mt_On_Event_JoystickButtonPressed(const JoystickButtonPressedEvent& event);
    void mt_On_Event_JoystickButtonReleased(const JoystickButtonReleasedEvent& event);
    void mt_On_Event_JoystickMoved(const JoystickMovedEvent& event);

    void mt_UpdateLogic([[maybe_unused]] float elapsed_time);
    void mt_UpdateRender(void);

protected:
    void mt_Push_Layer(Layer* layer);
    void mt_Pop_Layer(Layer* layer);

private:
    void mt_Update_Active_Layers(float elapsed_time);
    void mt_Render_Active_Layers(void);
    void mt_Pop_Pending_Layers(void);
    void mt_Push_Pending_Layers(void);

    std::vector<lys::Layer*> m_Active_Layers;
    std::vector<lys::Layer*> m_Pop_Layers;
    std::vector<lys::Layer*> m_Push_Layers;

    void mt_On_Change_State(const Message_ChangeState& msg);

    LayerStack m_Layer_Stack      = {};
    StateManager* m_State_Manager = nullptr;
};

template<class LayerType>
class SingleLayerState: public State
{
public:
    SingleLayerState() : m_Layer() {}

    bool mt_On_Entry(void) override
    {
        mt_Push_Layer(&m_Layer);
        return true;
    }
    bool mt_On_Exit(void) override
    {
        mt_Pop_Layer(&m_Layer);
        return true;
    }

private:
    LayerType m_Layer;
};

}  // namespace lys

#endif  // _LYS_STATE_HPP
