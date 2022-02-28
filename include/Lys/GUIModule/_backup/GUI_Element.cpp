#include "GUI_Element.hpp"

#include "Lys/MathModule/CollisionHandling.hpp"
#include "Lys/Core/SFML_Conversion.hpp"

#include <iostream>


#include "Lys/Core/FormatHelpers.hpp"

namespace lys
{


namespace gui
{



Element::Element() :
    m_Parent(nullptr),
    m_Current_State(ElementState::Neutral),
    m_Styles(),
    m_Position(),
    m_Size(),
    m_Required_Size()
{}

void Element::mt_OnUpdate([[maybe_unused]]float elapsed_time)
{
    //
}

bool Element::mt_OnMouseMove(const Vector2f& screen_pos)
{
    bool l_b_Is_Clicked = (m_Current_State == ElementState::Clicked);

    if (l_b_Is_Clicked == false)
    {
        std::cout << screen_pos << " ? " << mt_Get_Area() << " : " << fn_Check_Collision_Point_Rect(screen_pos, mt_Get_Area()) << '\n';

        if (fn_Check_Collision_Point_Rect(screen_pos, mt_Get_Area()))
        {
            mt_Set_State(ElementState::Focused);
        }
        else if (m_Current_State == ElementState::Focused)
        {
            mt_Set_State(ElementState::Neutral);
        }
        //return true;
    }
    return false;
}

bool Element::mt_OnMouseClick(const Vector2f& screen_pos)
{
    mt_Set_State(ElementState::Clicked);
    return false;
}

bool Element::mt_OnMouseRelease(const Vector2f& screen_pos)
{
    mt_Set_State(fn_Check_Collision_Point_Rect(screen_pos, mt_Get_Area()) ? ElementState::Focused : ElementState::Neutral);
    return false;
}


void Element::mt_Set_Position(const Vector2f& pos)
{
    m_Position = pos;
}

void Element::mt_Set_Size(const Vector2f& size)
{
    m_Size = size;
}

void Element::mt_Set_Area(const Rectf& area)
{
    mt_Set_Position(area.m_Top_Left);
    mt_Set_Size(area.m_Width_Height);
}



Vector2f Element::mt_Get_Position(void) const
{
    return m_Position;
}

Vector2f Element::mt_Get_Size(void) const
{
    return m_Size;
}

Vector2f Element::mt_Get_Required_Size(void) const
{
    return m_Required_Size;
}

Rectf Element::mt_Get_Area(void) const
{
    return Rectf(m_Position, m_Size);
}

void Element::mt_Redraw(void)
{
    //
}



void Element::mt_Set_Parent(Element* parent)
{
    m_Parent = parent;
}




void Element::mt_Set_State(ElementState state)
{
    std::cout << "Set State: " << static_cast<int>(state) << '\n';
    if (state != m_Current_State)
    {
        auto l_it = m_Styles.find(state);

        m_Current_State = state;
        if (l_it != m_Styles.end())
        {
            mt_Apply_Style(l_it->second);
        }
    }
}

void Element::mt_Add_Style(ElementState state, const ElementStyle& style)
{
    m_Styles.emplace(state, style);
}

void Element::mt_Add_Style(ElementState state,
                           TextOriginMode x_origin_mode, TextOriginMode y_origin_mode,
                           TextStyle style, unsigned int character_size, const Color& fill_color, const Color& outline_color, float outline_thickness,
                           const Color& background_fill_color, const Color& background_outline_color, float background_outline_thickness)
{
    ElementStyle l_Style;

    l_Style.m_Text.m_Origin.m_X_Mode = x_origin_mode;
    l_Style.m_Text.m_Origin.m_Y_Mode = y_origin_mode;
    l_Style.m_Text.m_Style.m_Style = style;
    l_Style.m_Text.m_Style.m_Character_Size = character_size;
    l_Style.m_Text.m_Style.m_Fill_Color = fill_color;
    l_Style.m_Text.m_Style.m_Outline_Color = outline_color;
    l_Style.m_Text.m_Style.m_Outline_Thickness = outline_thickness;

    l_Style.m_Background.m_Fill_Color = background_fill_color;
    l_Style.m_Background.m_Outline_Color = background_outline_color;
    l_Style.m_Background.m_Outline_Thickness = background_outline_thickness;

    mt_Add_Style(state, l_Style);
}

void Element::mt_Apply_Style(const ElementStyle& style)
{
    //
}

ElementStyle Element::mt_Get_Style(void) const
{
    auto l_it = m_Styles.find(m_Current_State);

    if (l_it != m_Styles.end())
    {
        return l_it->second;
    }

    return ElementStyle();
}


Vector2f Element::smt_Get_Text_Size(const std::string& text, const TextSettings& style)
{
    sf::Text l_Text;
    sf::FloatRect l_Bounds;

    l_Text.setString(text);
    l_Text.setFont(Renderer::smt_Get().mt_Get_Default_Font());
    l_Text.setCharacterSize(style.m_Style.m_Character_Size);
    l_Text.setStyle(sf_To(style.m_Style.m_Style));

    l_Bounds = l_Text.getGlobalBounds();

    return Vector2f(l_Bounds.width, l_Bounds.height);
}


}


}
