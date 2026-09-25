#include "lys-application-states/lys-application-state.hpp"

#if 0
#include "Lys/Application/Application.hpp"
#include "Lys/Core/Profiler.hpp"
#endif
#include <algorithm>

#include "lys-application-states/lys-application-layer.hpp"
#include "lys-application-states/lys-application-state-manager.hpp"

namespace lys
{

ApplicationState::~ApplicationState() {}

void ApplicationState::On_Create(void) {}

void ApplicationState::On_Destroy(void) {}

void ApplicationState::On_Entry(void) {}

void ApplicationState::On_Exit(void) {}

void ApplicationState::Update_Logic(void)
{
#if 0
    LYS_PROFILE_FUNCTION;
#endif
    Pop_Pending_Layers();
    Push_Pending_Layers();
    Update_Active_Layers();
}

void ApplicationState::Update_Render(void)
{
#if 0
    LYS_PROFILE_FUNCTION;
#endif
    Render_Active_Layers();
}

void ApplicationState::Push_Layer(ApplicationLayer* layer)
{
#if 0
    layer->mt_Add_Receiver(&State::mt_On_Change_State, this);
#endif
    m_Push_Layers.push_back(layer);
}

void ApplicationState::Pop_Layer(ApplicationLayer* layer)
{
    m_Pop_Layers.push_back(layer);
}

void ApplicationState::Update_Active_Layers(void)
{
    lys::ApplicationLayerForward l_Forward;

    l_Forward = lys::ApplicationLayerForward::Continue;
    for (auto it = m_Active_Layers.rbegin(); (it != m_Active_Layers.rend()) && (l_Forward == lys::ApplicationLayerForward::Continue); it++)
    {
        l_Forward = (*it)->On_Update();
    }
}

void ApplicationState::Render_Active_Layers(void)
{
    std::size_t l_First_Rendering_Layer_Id;

    if (m_Active_Layers.empty() == true)
    {
        return;
    }

    for (l_First_Rendering_Layer_Id = m_Active_Layers.size() - 1; true; l_First_Rendering_Layer_Id--)
    {
        if (m_Active_Layers[l_First_Rendering_Layer_Id]->Get_Rendering_Forward_Strategy() == lys::ApplicationLayerForward::Stop)
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
        m_Active_Layers[l_First_Rendering_Layer_Id]->On_Render();
    }
}

void ApplicationState::Pop_Pending_Layers(void)
{
    for (std::size_t ii = 0; ii < m_Pop_Layers.size(); ii++)
    {
        auto it = std::find(m_Active_Layers.begin(), m_Active_Layers.end(), m_Pop_Layers[ii]);
        if (it != m_Active_Layers.end())
        {
            (*it)->On_Deactivate();
            m_Active_Layers.erase(it);
        }
    }
    m_Pop_Layers.clear();
}

void ApplicationState::Push_Pending_Layers(void)
{
    for (std::size_t ii = 0; ii < m_Push_Layers.size(); ii++)
    {
        m_Push_Layers[ii]->On_Activate();
        m_Active_Layers.push_back(m_Push_Layers[ii]);
    }
    m_Push_Layers.clear();
}

void ApplicationState::On_Change_State(std::size_t state_id)
{
    m_State_Manager->Change_State(state_id);
}

}  // namespace lys
