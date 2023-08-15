#ifndef _LYS_LAYER_HPP
#define _LYS_LAYER_HPP 1

#include "Lys/MessageModule/MessageManager.hpp"

namespace lys
{

struct Event;
struct MouseButtonEvent;
struct MouseMoveEvent;
struct MouseWheelScrollEvent;
struct KeyEvent;
struct JoystickButtonEvent;
struct JoystickMoveEvent;
struct TextEvent;


enum class LayerForward
{
    Stop,
    Continue
};

class LYS_API Layer
{
public:
    Layer(const char* layer_id) : m_Layer_Id(layer_id) {}
    virtual ~Layer(){}

    LayerForward mt_On_Event(const Event& event);
    virtual LayerForward mt_On_Update(float elapsed_time){return LayerForward::Continue;}
    virtual void mt_On_Render(void){}
    virtual LayerForward mt_Get_Rendering_Forward_Strategy(void) const {return LayerForward::Stop;}

    template<typename MessageType>
    void mt_Send_Message(const MessageType& msg)
    {
        m_Message_Manager.mt_Send_Message(msg);
    }

    template<typename MessageType, class C>
    void mt_Add_Receiver(void(C::*pmt_Callback)(const MessageType&), C* receiver)
    {
        m_Message_Manager.mt_Add_Receiver(pmt_Callback, receiver, true);
    }

    const char* mt_Get_Layer_Id(void) const { return m_Layer_Id; }

protected:

    virtual LayerForward mt_On_Event_Text_Entered([[maybe_unused]]const TextEvent& event){return LayerForward::Stop;}

    virtual LayerForward mt_On_Event_Key_Pressed([[maybe_unused]]const KeyEvent& event){return LayerForward::Stop;}
    virtual LayerForward mt_On_Event_Key_Released([[maybe_unused]]const KeyEvent& event){return LayerForward::Stop;}

    virtual LayerForward mt_On_Event_Mouse_Button_Pressed([[maybe_unused]]const MouseButtonEvent& event){return LayerForward::Stop;}
    virtual LayerForward mt_On_Event_Mouse_Button_Released([[maybe_unused]]const MouseButtonEvent& event){return LayerForward::Stop;}
    virtual LayerForward mt_On_Event_Mouse_Move([[maybe_unused]]const MouseMoveEvent& event){return LayerForward::Stop;}
    virtual LayerForward mt_On_Event_Mouse_Wheel_Scroll([[maybe_unused]]const MouseWheelScrollEvent& event){return LayerForward::Stop;}

    virtual LayerForward mt_On_Event_Joystick_Button_Pressed([[maybe_unused]]const JoystickButtonEvent& event){return LayerForward::Stop;}
    virtual LayerForward mt_On_Event_Joystick_Button_Released([[maybe_unused]]const JoystickButtonEvent& event){return LayerForward::Stop;}
    virtual LayerForward mt_On_Event_Joystick_Move([[maybe_unused]]const JoystickMoveEvent& event){return LayerForward::Stop;}

protected:

    void mt_Change_State(std::size_t new_state);

private:

    MessageManager m_Message_Manager = {};

    const char* m_Layer_Id = nullptr;

};


}

#endif // _LYS_LAYER_HPP
