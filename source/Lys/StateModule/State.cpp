#include "Lys/StateModule/State.hpp"
#include "Lys/StateModule/Layer.hpp"
#include "Lys/Application/Application.hpp"

namespace lys
{

State::~State()
{}

bool State::mt_OnCreate(void)
{
    return true;
}

bool State::mt_OnDestroy(void)
{
    return true;
}

bool State::mt_OnEntry(void)
{
    return true;
}

bool State::mt_OnExit(void)
{
    return true;
}

void State::mt_OnUpdate(float elapsed_time)
{
    LayerEventForward l_Event_Forward = LayerEventForward::Continue;
    Layer* l_Layer;

    for (auto l_it = m_Layers.rbegin(); l_it != m_Layers.rend() && l_Event_Forward == LayerEventForward::Continue; l_it++)
    {
        l_Layer = *l_it;
        l_Event_Forward = l_Layer->mt_OnUpdate(elapsed_time);
    }

    for (auto l_it = m_Layers.rbegin(); l_it != m_Layers.rend() && l_Event_Forward == LayerEventForward::Continue; l_it++)
    {
        l_Layer = *l_it;
        l_Event_Forward = l_Layer->mt_OnRender();
    }
}

void State::mt_OnEvent([[maybe_unused]] const Event& event)
{
    Layer* l_Layer;
    auto l_it = m_Layers.rbegin();

    if (l_it != m_Layers.rend())
    {
        l_Layer = *l_it;
        l_Layer->mt_OnEvent(event);
    }
}

void State::mt_Push_Layer(Layer* l)
{
    l->mt_Add_Receiver(&State::mt_OnChangeState, this);
    m_Layers.push_back(l);
}

void State::mt_Pop_Layer(void)
{
    m_Layers.pop_back();
}

void State::mt_OnChangeState(const Message_ChangeState& msg)
{
    m_State_Manager->mt_Change_State(msg.m_Next_State);
}

}
