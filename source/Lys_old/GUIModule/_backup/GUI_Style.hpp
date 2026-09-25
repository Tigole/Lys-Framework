#ifndef _LYS_GUI_STYLE_HPP
#define _LYS_GUI_STYLE_HPP 1

#include "MathModule/Vector2.hpp"
#include "Core/Color.hpp"

namespace lys
{

enum class TextOriginMode
{
    Centered,
    Near,   /// Top or Left
    Far     /// Bottom or Right
};

struct TextOriginSettings
{
    TextOriginMode m_X_Mode = TextOriginMode::Near;
    TextOriginMode m_Y_Mode = TextOriginMode::Near;
};

enum class TextStyle
{
    Regular
};

struct TextStyleSettings
{
    TextStyle m_Style = TextStyle::Regular;
    unsigned int m_Character_Size = 30;
    Color m_Fill_Color = Color::White;
    Color m_Outline_Color = Color::Black;
    float m_Outline_Thickness = 0.0f;
};

struct TextSettings
{
    TextOriginSettings m_Origin;
    TextStyleSettings m_Style;
};


}

#endif // _LYS_GUI_STYLE_HPP
