#include "Lys/GraphicModule/Renderer.hpp"

#include "Lys/Application/Window.hpp"

#include "Lys/Core/SFML_Conversion.hpp"

#include "Lys/GraphicModule/EmbeddedFonts/JackInput.hpp"


#if LYS_USE_IMGUI
#include "imgui-SFML.h"
#endif // LYS_USE_IMGUI

namespace lys
{

std::unique_ptr<Renderer> Renderer::sm_Renderer;

void Renderer::smt_Create(Window* wnd)
{
    sm_Renderer.reset(new Renderer(wnd));
}

Renderer& Renderer::smt_Get(void)
{
    return *sm_Renderer;
}



Renderer::Renderer(Window* wnd) :
    m_Wnd(&wnd->m_Wnd)
{
    m_Default_Font.loadFromMemory(font::jack_input, font::jack_input_length);
}

void Renderer::mt_Begin_Scene(float elapsed_time)
{
    sf::Color l_Clear_Color(sf::Color::Black);

#if LYS_USE_IMGUI
    ImGui::SFML::Update(*m_Wnd, sf::Time(sf::seconds(elapsed_time)));
#endif // LYS_USE_IMGUI

    m_Wnd->clear(l_Clear_Color);
}

void Renderer::mt_End_Scene(void)
{

#if LYS_USE_IMGUI
    ImGui::SFML::Render(*m_Wnd);
#endif // LYS_USE_IMGUI

    m_Wnd->display();
}

void Renderer::mt_Draw_Line(const LineSettings& line_settings)
{
    std::array<sf::Vertex, 2> l_Line =
    {
        sf::Vertex(sf_To<float>(line_settings.m_Start_Pos), sf_To(line_settings.m_Start_Color)),
        sf::Vertex(sf_To<float>(line_settings.m_End_Pos), sf_To(line_settings.m_End_Color))
    };

    m_Wnd->draw(l_Line.data(), l_Line.size(), sf::Lines);
}

void Renderer::mt_Draw_Rectangle(const RectangleSettings& rectangle_settings)
{
    sf::RectangleShape l_Shape;

    l_Shape.setPosition(sf_To<float, float>(rectangle_settings.m_Position));
    l_Shape.setSize(sf_To<float, float>(rectangle_settings.m_Size));
    l_Shape.setFillColor(sf_To(rectangle_settings.m_Fill_Color));
    l_Shape.setOutlineThickness(rectangle_settings.m_Outline_Thickness);
    l_Shape.setOutlineColor(sf_To(rectangle_settings.m_Outline_Color));

    mt_Set_Texture(l_Shape, rectangle_settings.m_Texture_Data);

    m_Wnd->draw(l_Shape);
}

void Renderer::mt_Draw_Circle(const CircleSettings& circle_settings)
{
    sf::CircleShape l_Shape;

    l_Shape.setPointCount(circle_settings.m_Point_Count);
    l_Shape.setFillColor(sf_To(circle_settings.m_Fill_Color));

    l_Shape.setOutlineThickness(circle_settings.m_Outline_Thickness);
    l_Shape.setOutlineColor(sf_To(circle_settings.m_Outline_Color));

    l_Shape.setRadius(circle_settings.m_Radius);
    l_Shape.setOrigin(circle_settings.m_Radius, circle_settings.m_Radius);
    l_Shape.setPosition(sf_To<float, float>(circle_settings.m_Center));

    m_Wnd->draw(l_Shape);
}

Rectf Renderer::mt_Draw_Text(const char* text, const Vector2f& screen_pos, const gui::TextSettings& text_settings)
{
    sf::Text l_Text;
    sf::Vector2f l_Origin;
    sf::FloatRect l_Bound;
    auto l_fn_Handle_Mode = [](gui::TextOriginMode mode, float& f, float near, float far)
    {
        switch(mode)
        {
        case gui::TextOriginMode::Centered:
            f = (near + far) / 2.0f;
            break;
        case gui::TextOriginMode::Far:
            f = far;
            break;
        case gui::TextOriginMode::Near:
            f = near;
        default:
            break;
        }
    };

    l_Text.setString(text);
    l_Text.setFont(m_Default_Font);
    l_Text.setCharacterSize(text_settings.m_Character_Size);
    l_Text.setFillColor(sf_To(text_settings.m_Fill_Color));
    l_Text.setOutlineColor(sf_To(text_settings.m_Outline_Color));
    l_Text.setOutlineThickness(text_settings.m_Outline_Thickness);
    l_Text.setStyle(sf_To(text_settings.m_Style));

    l_Text.setPosition(sf_To<float, float>(screen_pos));

    l_Bound = l_Text.getLocalBounds();
    l_fn_Handle_Mode(text_settings.m_Horizontal_Align, l_Origin.x, l_Bound.left, l_Bound.left + l_Bound.width);
    l_fn_Handle_Mode(text_settings.m_Vertical_Align, l_Origin.y, l_Bound.top, l_Bound.top + l_Bound.height);

    l_Text.setOrigin(l_Origin);

    m_Wnd->draw(l_Text);

    return Rectf(l_Bound.left, l_Bound.top, l_Bound.width, l_Bound.height);
}

void Renderer::mt_Draw_VertexArray(const VertexArray& va)
{
    m_Wnd->draw(va.m_SFML_VA);
}

const sf::Font& Renderer::mt_Get_Default_Font(void) const
{
    return m_Default_Font;
}



void Renderer::mt_Set_Texture(sf::Shape& s, const TextureData& data)
{
    if (data.m_Texture != nullptr)
    {
        s.setTexture(&data.m_Texture->m_SFML_Texture, true);
        s.setTextureRect(sf_To<int>(data.m_Normalized_Texture_Area.mt_Get_Scale_XY(sf_From<float>(data.m_Texture->m_SFML_Texture.getSize()))));
    }
}

}
