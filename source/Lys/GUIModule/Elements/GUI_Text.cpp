#include "Lys/GUIModule/Elements/GUI_Text.hpp"
#if 0
#include "imgui.h"

namespace lys
{
namespace gui
{


Text::Text(const std::string& text) :
    m_Text(text)
{}

void Text::mt_OnUpdate(float elapsed_time)
{
    ImGui::Text("%s", m_Text.c_str());
}

void Text::mt_Set_Text(const std::string& text)
{
    m_Text = text;
}

}
}
#endif
