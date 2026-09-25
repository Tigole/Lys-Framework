#ifndef _LYS_RECT_HPP
#define _LYS_RECT_HPP 1

#include "Lys/MathModule/Vector2.hpp"

namespace lys
{


template<typename T>
struct Rect
{
    Rect() : m_Top_Left(), m_Width_Height() {}
    Rect(T v) : m_Top_Left(v), m_Width_Height(v) {}
    Rect(T tl, T wh) : m_Top_Left(tl), m_Width_Height(wh) {}
    Rect(T left, T top, T width, T height) : m_Top_Left(left, top), m_Width_Height(width, height) {}
    Rect(const Vector2<T>& top_left, const Vector2<T>& width_height) : m_Top_Left(top_left), m_Width_Height(width_height) {}
    Vector2<T> m_Top_Left;
    Vector2<T> m_Width_Height;

    Vector2<T> mt_Get_Top_Right(void) const
    {
        return Vector2<T>(m_Top_Left.x + m_Width_Height.x, m_Top_Left.y);
    }

    Vector2<T> mt_Get_Bottom_Left(void) const
    {
        return Vector2<T>(m_Top_Left.x, m_Top_Left.y + m_Width_Height.y);
    }

    Vector2<T> mt_Get_Bottom_Right(void) const
    {
        return m_Top_Left + m_Width_Height;
    }

    template<typename U>
    Rect<T> mt_Get_Scale_XY(const Vector2<U>& v) const
    {
        return Rect<T>(m_Top_Left.x * v.x,
                       m_Top_Left.y * v.y,
                       m_Width_Height.x * v.x,
                       m_Width_Height.y * v.y);
    }

    Rect<T> mt_Get_Scale(const Rect<T>& r, float factor) const
    {
        return Rect<T>(r.m_Top_Left * factor, r.m_Width_Height * factor);
    }
};

using Rectf = Rect<float>;


}


#endif // _LYS_RECT_HPP
