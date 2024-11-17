#ifndef _LYS_LAYER_HPP
#define _LYS_LAYER_HPP 1

#include "Lys/Application/Event.hpp"
#include "Lys/MessageModule/MessageManager.hpp"

namespace lys
{

enum class LayerForward
{
    Stop,
    Continue
};

class LYS_API Layer
{
public:
    Layer(const char* layer_id) : m_Layer_Id(layer_id) {}
    Layer(const Layer&)            = delete;
    Layer& operator=(const Layer&) = delete;
    virtual ~Layer() {}

    virtual LayerForward mt_On_Update(float /*elapsed_time*/)
    {
        return LayerForward::Continue;
    }
    virtual void mt_On_Render(void) {}
    virtual LayerForward mt_Get_Rendering_Forward_Strategy(void) const
    {
        return LayerForward::Stop;
    }

    template<typename MessageType>
    void mt_Send_Message(const MessageType& msg)
    {
        m_Message_Manager.mt_Send_Message(msg);
    }

    template<typename MessageType, class C>
    void mt_Add_Receiver(void (C::*pmt_Callback)(const MessageType&), C* receiver)
    {
        m_Message_Manager.mt_Add_Receiver(pmt_Callback, receiver, true);
    }

    const char* mt_Get_Layer_Id(void) const
    {
        return m_Layer_Id;
    }

    virtual LayerForward mt_On_Event_TextEntered([[maybe_unused]] const TextEvent& event)
    {
        return LayerForward::Stop;
    }

    virtual LayerForward mt_On_Event_KeyPressed([[maybe_unused]] const KeyPressedEvent& event)
    {
        return LayerForward::Stop;
    }
    virtual LayerForward mt_On_Event_KeyReleased([[maybe_unused]] const KeyReleasedEvent& event)
    {
        return LayerForward::Stop;
    }

    virtual LayerForward mt_On_Event_MouseButtonPressed([[maybe_unused]] const MouseButtonPressedEvent& event)
    {
        return LayerForward::Stop;
    }
    virtual LayerForward mt_On_Event_MouseButtonReleased([[maybe_unused]] const MouseButtonReleasedEvent& event)
    {
        return LayerForward::Stop;
    }
    virtual LayerForward mt_On_Event_MouseMove([[maybe_unused]] const MouseMoveEvent& event)
    {
        return LayerForward::Stop;
    }
    virtual LayerForward mt_On_Event_MouseWheelScroll([[maybe_unused]] const MouseWheelScrollEvent& event)
    {
        return LayerForward::Stop;
    }

    virtual LayerForward mt_On_Event_JoystickConnected([[maybe_unused]] const JoystickConnectedEvent& event)
    {
        return LayerForward::Continue;
    }
    virtual LayerForward mt_On_Event_JoystickDisconnected([[maybe_unused]] const JoystickDisconnectedEvent& event)
    {
        return LayerForward::Continue;
    }
    virtual LayerForward mt_On_Event_JoystickButtonPressed([[maybe_unused]] const JoystickButtonPressedEvent& event)
    {
        return LayerForward::Stop;
    }
    virtual LayerForward mt_On_Event_JoystickButtonReleased([[maybe_unused]] const JoystickButtonReleasedEvent& event)
    {
        return LayerForward::Stop;
    }
    virtual LayerForward mt_On_Event_JoystickMove([[maybe_unused]] const JoystickMoveEvent& event)
    {
        return LayerForward::Stop;
    }

protected:
    void mt_Change_State(std::size_t new_state);

private:
    MessageManager m_Message_Manager = {};

    const char* m_Layer_Id = nullptr;
};

}  // namespace lys

#endif  // _LYS_LAYER_HPP
