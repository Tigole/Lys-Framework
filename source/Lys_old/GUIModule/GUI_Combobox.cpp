#include "Lys/GUIModule/GUI_Combobox.hpp"
#include "imgui.h"
#include <algorithm>

namespace lys
{

ComboBox::ComboBox()
 :  m_List(), m_Current_Selected(0)
{}

void ComboBox::mt_Reset(void)
{
    m_List.clear();
    m_Current_Selected = 0;
    m_Reset = true;
}

void ComboBox::mt_Setup(const std::string& first)
{
    m_List.push_back(first);
    m_Current_Selected = 0;
    m_Reset = true;
}

void ComboBox::mt_Add(const std::string& str)
{
    m_List.push_back(str);
    m_Current_Selected = 0;
    m_Reset = true;
}

bool ComboBox::mt_Draw(const std::string& name)
{
    std::size_t l_Current = m_Current_Selected;
    bool l_b_Ret;

    if ((m_Current_Selected < m_List.size()) && ImGui::BeginCombo(name.c_str(), m_List[m_Current_Selected].c_str()))
    {
        for (std::size_t ii = 0; ii < m_List.size(); ii++)
        {
            bool l_Selected = (m_Current_Selected == ii);

            if (ImGui::Selectable(m_List[ii].c_str(), l_Selected))
            {
                m_Current_Selected = ii;
            }

            if (l_Selected)
            {
                ImGui::SetItemDefaultFocus();
            }
        }
        ImGui::EndCombo();
    }

    l_b_Ret = l_Current != m_Current_Selected;
    l_b_Ret |= m_Reset;

    m_Reset = false;

    return l_b_Ret;
}

void ComboBox::mt_Init(const std::string& init_value)
{
    auto l_it = std::find(m_List.begin(), m_List.end(), init_value);

    if (l_it != m_List.end())
    {
        m_Current_Selected = std::distance(m_List.begin(), l_it);
        m_Reset = false;
    }
}

void ComboBox::mt_Init(std::size_t init_index)
{
    m_Current_Selected = init_index;
    m_Reset = false;
}

const std::string& ComboBox::mt_Get(void) const
{
    if (m_Current_Selected < m_List.size())
    {
        return m_List[m_Current_Selected];
    }
    return m_Empty;
}

std::size_t ComboBox::mt_Get_Index(void) const
{
    return m_Current_Selected;
}

const std::vector<std::string>& ComboBox::mt_Get_List(void) const
{
    return m_List;
}

}
