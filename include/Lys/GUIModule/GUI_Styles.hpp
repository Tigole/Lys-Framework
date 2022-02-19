#ifndef _GUI_STYLE_HPP
#define _GUI_STYLE_HPP 1

#include "Lys/Core/Color.hpp"
#include "Lys/MathModule/Vector2.hpp"

#include <string>

namespace lys
{

namespace gui
{

enum class TextOriginMode
{
    Centered,
    Near,   /// Top or Left
    Far     /// Bottom or Right
};

enum class TextStyle
{
    Regular
};

struct BackgroundSettings
{
    Color m_Fill_Color;
    Color m_Outline_Color;
    float m_Outline_Thickness = 0.0f;
};

struct TextSettings
{
    TextStyle m_Style;
    TextOriginMode m_Vertical_Align = TextOriginMode::Near;
    TextOriginMode m_Horizontal_Align = TextOriginMode::Near;
    Vector2i m_Margin;
    Color m_Fill_Color;
    unsigned int m_Character_Size = 30;
    Color m_Outline_Color;
    float m_Outline_Thickness = 0.0f;
};

struct Style
{
	BackgroundSettings m_Background;
	TextSettings m_Text;
};

std::string fn_GUIStyleTextHAlign_ToString(const TextOriginMode& align);
TextOriginMode fn_GUIStyleTextHAlign_ToEnum(const std::string& align);

}

}



#endif // !_GUI_STYLE_HPP
