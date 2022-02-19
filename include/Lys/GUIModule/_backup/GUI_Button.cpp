#include "GUI_Button.hpp"


namespace lys
{

namespace gui
{

Button::Button(const std::string& text) :
    m_Text(text)
{
    mt_Add_Style(ElementState::Neutral,
                 TextOriginMode::Centered, TextOriginMode::Centered,
                 TextStyle::Regular, 30, Color::White, Color::Black, 0.0f,
                 Color(0.1f, 0.2f, 0.7f), Color(0.05f, 0.1f, 0.35f), 10.0f);

    mt_Add_Style(ElementState::Focused,
                 TextOriginMode::Centered, TextOriginMode::Centered,
                 TextStyle::Regular, 30, Color::White, Color::Black, 0.0f,
                 Color(0xff8c00), Color(0xff4500), 10.0f);

    m_Required_Size = smt_Get_Text_Size(m_Text, mt_Get_Style().m_Text);
    m_Size = m_Required_Size;
}

void Button::mt_Update_String(const std::string& str)
{
    Vector2f l_Old_Size = m_Required_Size;

    m_Text = str;

    m_Required_Size = smt_Get_Text_Size(m_Text, mt_Get_Style().m_Text);
    if (m_Size == l_Old_Size)
    {
        m_Size = m_Required_Size;
    }
}

void Button::mt_OnUpdate(float elapsed_time)
{
    ElementStyle l_Style = mt_Get_Style();
    RectangleSettings l_Rect_Settings;
    Rectf l_Text_Area;
    Vector2f l_Margin(15.0f);

    l_Rect_Settings.m_Position = m_Position - l_Margin;
    l_Rect_Settings.m_Size = m_Size + l_Margin * 2;
    l_Rect_Settings.m_Fill_Color = l_Style.m_Background.m_Fill_Color;
    l_Rect_Settings.m_Outline_Thickness = l_Style.m_Background.m_Outline_Thickness;
    l_Rect_Settings.m_Outline_Color = l_Style.m_Background.m_Outline_Color;

    Renderer::smt_Get().mt_Draw_Rectangle(l_Rect_Settings);

    m_Required_Size = Renderer::smt_Get().mt_Draw_Text(m_Text.c_str(), m_Position, l_Style.m_Text).m_Width_Height;
}

}

}
