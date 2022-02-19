#ifndef _LYS_SFML_CONVERSION_HPP
#define _LYS_SFML_CONVERSION_HPP 1

#include "Lys/Core/Core.hpp"
#include "Lys/GraphicModule/DrawCommandSettings.hpp"

#include <SFML/Graphics/Text.hpp>

namespace lys
{

template<typename T, typename U>
sf::Vector2<T> constexpr sf_To(const Vector2<U>& v)
{
    return sf::Vector2<T>(v.x, v.y);
}

template<typename T, typename U>
Vector2<T> constexpr sf_From(const sf::Vector2<U>& v)
{
    return Vector2<T>(v.x, v.y);
}

template<typename T, typename U>
sf::Rect<T> constexpr sf_To(const Rect<U>& r)
{
    return sf::Rect<T>(r.m_Top_Left.x, r.m_Top_Left.y, r.m_Width_Height.x, r.m_Width_Height.y);
}

template<typename T, typename U>
Rect<T> constexpr sf_From(const sf::Rect<U>& r)
{
    return Rect<T>(r.left, r.top, r.width, r.height);
}

inline sf::Color sf_To(const Color& c)
{
    return sf::Color(c.r * 255, c.g * 255, c.b * 255, c.a * 255);
}

inline Color sf_From(const sf::Color& c)
{
    return Color(c.r / 255.0f, c.g / 255.0f, c.b / 255.0f, c.a / 255.0f);
}

inline sf::Uint32 sf_To(gui::TextStyle style)
{
    sf::Uint32 l_Ret;

    switch(style)
    {
    case gui::TextStyle::Regular:
        l_Ret = sf::Text::Style::Regular;
        break;
    default:
        l_Ret = sf::Text::Style::Regular;
        break;
    }

    return l_Ret;
}



}



#endif // _LYS_SFML_CONVERSION_HPP
