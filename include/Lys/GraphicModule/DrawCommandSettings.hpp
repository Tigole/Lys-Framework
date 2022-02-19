#ifndef _LYS_DRAW_COMMAND_SETTINGS_HPP
#define _LYS_DRAW_COMMAND_SETTINGS_HPP 1

#include "Lys/Core/Color.hpp"
#include "Lys/MathModule/Vector2.hpp"
#include "Lys/MathModule/Rect.hpp"
#include "Lys/GUIModule/GUI_Styles.hpp"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>

namespace lys
{

struct Texture
{
    sf::Texture m_SFML_Texture;
};

struct TextureData
{
    Rectf m_Normalized_Texture_Area;
    const Texture* m_Texture;
};

struct LineSettings
{
    Vector2f m_Start_Pos;
    Vector2f m_End_Pos;

    Color m_Start_Color;
    Color m_End_Color;
};

struct RectangleSettings
{
    Vector2f m_Position;
    Vector2f m_Size;
    Color m_Fill_Color;

    float m_Outline_Thickness = 0.0f;
    Color m_Outline_Color;

    TextureData m_Texture_Data;
};

struct CircleSettings
{
    Vector2f m_Center;
    float m_Radius = 0.0f;
    Color m_Fill_Color;
    std::size_t m_Point_Count = 30;

    float m_Outline_Thickness = 0.0f;
    Color m_Outline_Color;

    TextureData m_Texture_Data;
};

struct VertexArray
{
    sf::VertexArray m_SFML_VA;
};


}

#endif // _LYS_DRAW_COMMAND_SETTINGS_HPP
