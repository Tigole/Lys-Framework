#include "GUI_Manager.hpp"

namespace lys
{


namespace gui
{


bool Manager::mt_OnMouseMove(const Vector2f& screen_pos)
{
    bool l_b_Ret = false;

    for (std::size_t ii = 0; ii < m_Interfaces.size() && (l_b_Ret == false); ii++)
    {
        l_b_Ret = m_Interfaces[ii]->mt_OnMouseMove(screen_pos);
    }

    return l_b_Ret;
}

bool Manager::mt_OnMouseClick(const Vector2f& screen_pos)
{
    bool l_b_Ret = false;

    for (std::size_t ii = 0; ii < m_Interfaces.size() && (l_b_Ret == false); ii++)
    {
        l_b_Ret = m_Interfaces[ii]->mt_OnMouseClick(screen_pos);
    }

    return l_b_Ret;
}

bool Manager::mt_OnMouseRelease(const Vector2f& screen_pos)
{
    bool l_b_Ret = false;

    for (std::size_t ii = 0; ii < m_Interfaces.size() && (l_b_Ret == false); ii++)
    {
        l_b_Ret = m_Interfaces[ii]->mt_OnMouseRelease(screen_pos);
    }

    return l_b_Ret;
}


void Manager::mt_OnUpdate(float elapsed_time)
{
    for (auto& i : m_Interfaces)
    {
        i->mt_OnUpdate(elapsed_time);
    }
}

void Manager::mt_Push_Interface(Interface* interface)
{
    m_Interfaces.push_back(interface);
}

void Manager::mt_Pop_Interface(Interface* interface)
{
    auto l_it = std::find(m_Interfaces.begin(), m_Interfaces.end(), interface);

    if (l_it != m_Interfaces.end())
    {
        m_Interfaces.erase(l_it);
    }
}


}

}
