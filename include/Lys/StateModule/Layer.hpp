#ifndef _LYS_LAYER_HPP
#define _LYS_LAYER_HPP 1

#include "Lys/MessageModule/MessageManager.hpp"

namespace lys
{

struct Event;

enum class LayerEventForward
{
    Stop,
    Continue
};

class Layer
{
public:
    Layer(){}
    virtual ~Layer(){}

    void mt_OnEvent(const Event& event);
    virtual LayerEventForward mt_OnUpdate([[maybe_unused]] float elapsed_time) = 0;
    virtual LayerEventForward mt_OnRender(void) = 0;

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

protected:

    void mt_Change_State(std::size_t new_state);

private:

    MessageManager m_Message_Manager;

};


}

#endif // _LYS_LAYER_HPP
