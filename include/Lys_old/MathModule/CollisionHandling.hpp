#ifndef _LYS_COLLISION_HANDLING_HPP
#define _LYS_COLLISION_HANDLING_HPP 1

#include "Vector2.hpp"
#include "Rect.hpp"

namespace lys
{

template<typename T>
bool fn_Check_Collision_Point_Circle(const Vector2<T>& point, const Vector2<T>& circle_center, float circle_radius)
{
    T l_Distance = Vector2<T>::smt_Get_Distance(point, circle_center);

    return l_Distance <= circle_radius;
}

template<typename T>
bool fn_Check_Collision_Point_Rect(const Vector2<T>& point, const Rect<T>& rect)
{
    return (    (point.x >= rect.m_Top_Left.x)
            &&  (point.x <= (rect.m_Top_Left.x + rect.m_Width_Height.x))
            &&  (point.y >= rect.m_Top_Left.y)
            &&  (point.y <= (rect.m_Top_Left.y + rect.m_Width_Height.y)));
}

template<typename T>
bool fn_Check_Collision_Point_Rect(const Vector2<T>& point, const Vector2<T>& top_left, const Vector2<T>& width_height)
{
    return fn_Check_Collision_Point_Rect(point, Rect<T>(top_left, width_height));
}

template<typename T>
bool fn_Check_Collision_Circle_Rect(const Vector2<T>& circle_center, float circle_radius, const Rect<T>& rect)
{
    float l_Squared_Circle_Radius = circle_radius * circle_radius;

    if (fn_Check_Collision_Point_Rect(circle_center, rect))
    {
        return true;
    }

    if (Vector2<T>(circle_center - rect.m_Top_Left).mt_Get_Length_Square() <= l_Squared_Circle_Radius)
    {
        return true;
    }

    if (Vector2<T>(circle_center - rect.mt_Get_Top_Right()).mt_Get_Length_Square() <= l_Squared_Circle_Radius)
    {
        return true;
    }

    if (Vector2<T>(circle_center - rect.mt_Get_Bottom_Left()).mt_Get_Length_Square() <= l_Squared_Circle_Radius)
    {
        return true;
    }

    if (Vector2<T>(circle_center - rect.mt_Get_Bottom_Right()).mt_Get_Length_Square() <= l_Squared_Circle_Radius)
    {
        return true;
    }

    return false;
}

template<typename T>
bool fn_Check_Collision_Circle_Rect(const Vector2<T>& circle_center, float circle_radius, const Vector2<T>& top_left, const Vector2<T>& width_height)
{
    return fn_Check_Collision_Circle_Rect(circle_center, circle_radius, Rect<T>(top_left, width_height));
}

}

#endif // _LYS_COLLISION_HANDLING_HPP
