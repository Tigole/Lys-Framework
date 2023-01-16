#include "Lys/GUIModule/Elements/GUI_Button.hpp"
#if 0
#include "Lys/GraphicModule/DrawCommandSettings.hpp"
#include "Lys/GraphicModule/Renderer.hpp"

namespace lys
{
namespace gui
{
#if LYS_USE_IMGUI

Button::Button(const std::string& text) :
    m_Text(text),
    m_Is_Clicked(false),
    m_Is_Hovered(false)
{}

void Button::mt_OnUpdate(float elapsed_time)
{
    if (m_Text.size() > 0)
    {
        m_Is_Clicked = ImGui::Button(m_Text.c_str());

        if (m_Is_Clicked == true)
        {
            //Manager::smt_Get().mt_Push_Event(BtnClicked(*m_Interface_Id, m_Element_Id));
        }
    }
}

void Button::mt_Set_Text(const std::string& text)
{
    m_Text = text;
}

const std::string& Button::mt_Get_Text(void) const
{
    return m_Text;
}

/*bool Button::mt_Is_Clicked(void) const
{
    return m_Is_Clicked;
}

bool Button::mt_Is_Hovered(void) const
{
    return m_Is_Hovered;
}*/

#else
Button::Button(const std::string& id, const std::string& text, Element* owner) :
    Element(id, owner),
    m_Text()
{
    mt_Set_Style(Element_State::Neutral,
                 {
                    {Color(0.1f, 0.2f, 0.7f), Color(0.05f, 0.1f, 0.35f), 0.0f},
                    {TextStyle::Regular, TextOriginMode::Near, TextOriginMode::Near, Vector2i(0, 0), Color::White, 30, Color::Black, 0.0f}
                 });
    mt_Set_Style(Element_State::Focused,
                 {
                    {Color(0xff8c00, 0xff), Color(0xff4500, 0xff), 0.0f},
                    {TextStyle::Regular, TextOriginMode::Near, TextOriginMode::Near, Vector2i(0, 0), Color::White, 30, Color::Black, 0.0f}
                 });

    mt_Set_Text(text);

    m_Allocation.m_Top_Left = Vector2f(500.0f, 300.0f);
}

void Button::mt_Set_Text(const std::string& text)
{
    m_Text = text;

    m_Allocation.m_Width_Height = smt_Get_Text_Size(m_Text, mt_Get_Current_Style()->m_Text);
}

void Button::mt_OnUpdate(float delta_time_s)
{
	//
}

void Button::mt_OnDraw(void)
{
    const Style* l_Style = mt_Get_Current_Style();

    if (l_Style != nullptr)
    {
        RectangleSettings l_Rect;

        l_Rect.m_Position = m_Allocation.m_Top_Left;
        l_Rect.m_Size = m_Allocation.m_Width_Height;
        l_Rect.m_Fill_Color = l_Style->m_Background.m_Fill_Color;
        l_Rect.m_Outline_Color = l_Style->m_Background.m_Outline_Color;
        l_Rect.m_Outline_Thickness = l_Style->m_Background.m_Outline_Thickness;

        Renderer::smt_Get().mt_Draw_Rectangle(l_Rect);
        Renderer::smt_Get().mt_Draw_Text(m_Text.c_str(), m_Allocation.m_Top_Left, l_Style->m_Text).m_Width_Height;
    }
}

Vector2f Button::mt_Get_Required_Space(void) const
{
    return m_Required_Space;
}
#endif
}

}
#endif
