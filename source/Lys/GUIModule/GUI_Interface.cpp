#include "Lys/GUIModule/GUI_Interface.hpp"
#include "Lys/GUIModule/GUI_Element.hpp"
#include "Lys/GUIModule/GUI_Manager.hpp"

#include "Lys/Core/SFML_Conversion.hpp"
#if 0
namespace lys
{


namespace gui
{

Interface::Interface(const std::string& id) :
    m_Id(id),
    m_Is_Active(false),
    m_Allocation()
{}

Interface::~Interface()
{}

bool Interface::mt_Is_Active(void) const
{
    return m_Is_Active;
}

void Interface::mt_Set_Active(bool active)
{
    m_Is_Active = active;
}

void Interface::mt_Set_Allocation(const Rectf& allocation)
{
    m_Allocation = allocation;
}

void Interface::mt_Set_Position(const Vector2f& position)
{
    m_Allocation.m_Top_Left = position;
}

const Rectf& Interface::mt_Get_Allocation(void) const
{
    return m_Allocation;
}

const std::string& Interface::mt_Get_Id(void) const
{
    return m_Id;
}






Interface_Predefined::Interface_Predefined(const std::string& id) :
    Interface(id),
    m_Named_Elements(),
    m_Elements()
{}

Interface_Predefined::~Interface_Predefined()
{}

void Interface_Predefined::mt_OnUpdate(float elapsed_time)
{
    constexpr const ImGuiWindowFlags l_Flags = ImGuiWindowFlags_NoMove + ImGuiWindowFlags_NoSavedSettings + ImGuiWindowFlags_NoResize + ImGuiWindowFlags_NoTitleBar;

    if (ImGui::Begin(mt_Get_Id().c_str(), nullptr, l_Flags))
    {
        for (auto& e : m_Elements)
        {
            if (e->mt_Is_Active() == true)
            {
                e->mt_OnUpdate(elapsed_time);
            }
        }

        ImGui::SetWindowPos(sf_To<float>(mt_Get_Allocation().m_Top_Left));
        ImGui::SetWindowSize(sf_To<float>(mt_Get_Allocation().m_Width_Height));
    }
    ImGui::End();
}

void Interface_Predefined::mt_Set_Element_Active(const std::string& element_id, bool active)
{
    std::size_t l_Index = mt_Get_Element_Index(element_id);

    if (l_Index < m_Elements.size())
    {
        m_Elements[l_Index]->mt_Set_Active(active);
    }
}

std::size_t Interface_Predefined::mt_Get_Element_Index(const std::string& element_id)
{
    auto l_Named_It = m_Named_Elements.find(element_id);

    LYS_ASSERT(l_Named_It != m_Named_Elements.end());

    return l_Named_It->second;
}

}

}
#endif
