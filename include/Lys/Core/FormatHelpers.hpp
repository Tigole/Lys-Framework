#ifndef _LYS_FORMAT_HELPERS_HPP
#define _LYS_FORMAT_HELPERS_HPP 1

#include "MathModule/Vector2.hpp"
#include "MathModule/Rect.hpp"

#include <ostream>

namespace lys
{

template<typename T>
std::ostream& operator<<(std::ostream& o, const Vector2<T>& v)
{
    o << '[' << v.x << ' ' << v.y << ']';
    return o;
}

template<typename T>
std::ostream& operator<<(std::ostream& o, const Rect<T>& r)
{
    o << '[' << r.m_Top_Left << ' ' << r.m_Width_Height << ']';
    return o;
}

}

#endif // _LYS_FORMAT_HELPERS_HPP
