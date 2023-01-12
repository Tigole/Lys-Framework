#include "Lys/StateModule/State.hpp"
#include "Lys/StateModule/Layer.hpp"
#include "Lys/Application/Application.hpp"
#include "Lys/Core/Profiler.hpp"

namespace lys
{

State::~State()
{}

bool State::mt_On_Create(void)
{
    return true;
}

bool State::mt_On_Destroy(void)
{
    return true;
}

bool State::mt_On_Entry(void)
{
    return true;
}

bool State::mt_On_Exit(void)
{
    return true;
}

void State::mt_On_Update(float elapsed_time)
{
    LYS_PROFILE_FUNCTION;
    lys::LayerForward l_Forward;
    std::size_t l_First_Rendering_Layer_Id;

    l_Forward = lys::LayerForward::Continue;
    for (auto it = m_Active_Layers.rbegin(); (it != m_Active_Layers.rend()) && (l_Forward == lys::LayerForward::Continue); it++)
    {
        l_Forward = (*it)->mt_On_Update(elapsed_time);
    }

    for (l_First_Rendering_Layer_Id = m_Active_Layers.size() - 1; true; l_First_Rendering_Layer_Id--)
    {
        if (m_Active_Layers[l_First_Rendering_Layer_Id]->mt_Get_Rendering_Forward_Strategy() == lys::LayerForward::Stop)
        {
            break;
        }
        if (l_First_Rendering_Layer_Id == 0)
        {
            break;
        }
    }

    for (; l_First_Rendering_Layer_Id < m_Active_Layers.size(); l_First_Rendering_Layer_Id++)
    {
        m_Active_Layers[l_First_Rendering_Layer_Id]->mt_On_Render();
    }

    for (std::size_t ii = 0; ii < m_Pop_Layers.size(); ii++)
    {
        auto it = std::find(m_Active_Layers.begin(), m_Active_Layers.end(), m_Pop_Layers[ii]);
        if (it != m_Active_Layers.end())
        {
            m_Active_Layers.erase(it);
        }
    }
    m_Pop_Layers.clear();

    for (std::size_t ii = 0; ii < m_Push_Layers.size(); ii++)
    {
        m_Active_Layers.push_back(m_Push_Layers[ii]);
    }
    m_Push_Layers.clear();
}

void State::mt_On_Event([[maybe_unused]] const Event& event)
{
    lys::LayerForward l_Forward;

    l_Forward = lys::LayerForward::Continue;
    for (auto it = m_Active_Layers.rbegin(); (it != m_Active_Layers.rend()) && (l_Forward == lys::LayerForward::Continue); it++)
    {
        l_Forward = (*it)->mt_On_Event(event);
    }
}

void State::mt_Push_Layer(Layer* layer)
{
    layer->mt_Add_Receiver(&State::mt_On_Change_State, this);
    m_Push_Layers.push_back(layer);
}

void State::mt_Pop_Layer(Layer* layer)
{
    m_Pop_Layers.push_back(layer);
}

void State::mt_On_Change_State(const Message_ChangeState& msg)
{
    m_State_Manager->mt_Change_State(msg.m_Next_State);
}

}
