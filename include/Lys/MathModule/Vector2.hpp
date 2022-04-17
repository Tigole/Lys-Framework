#ifndef _LYS_VECTOR2_HPP
#define _LYS_VECTOR2_HPP 1

#include <cstdint>
#include <cmath>

#include "MathCore.hpp"

namespace lys
{


template<typename T>
struct Vector2
{
    Vector2() : x(0), y(0) {}
    Vector2(T X, T Y) : x(X), y(Y) {}
    Vector2(T v) : x(v), y(v) {}
    template<typename U>
    Vector2(const Vector2<U>& rhs) : x(rhs.x), y(rhs.y) {}
    T x;
    T y;

    template<typename U>
    Vector2<T>& operator+=(const Vector2<U>& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    template<typename U>
    Vector2<T>& operator-=(const Vector2<U>& rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    Vector2<T>& operator*=(float rhs)
    {
        x *= rhs;
        y *= rhs;
        return *this;
    }

    template<typename U>
    Vector2<T>& operator*=(const Vector2<U>& rhs)
    {
        x *= rhs.x;
        y *= rhs.y;
        return *this;
    }

    float mt_Get_Length_Square(void) const
    {
        return POW_2(x) + POW_2(y);
    }

    float mt_Get_Length(void) const
    {
        return std::sqrt(mt_Get_Length_Square());
    }

    Vector2 mt_Get_Normalized(void) const
    {
        float l_Lenght = mt_Get_Length();

        if (l_Lenght > 0.0f)
        {
            return Vector2(x / l_Lenght, y / l_Lenght);
        }

        return Vector2();
    }

    template<typename U>
    static float smt_Get_Distance(const Vector2<U>& a, const Vector2<U>& b)
    {
        Vector2<U> l_Diff = a - b;

        return l_Diff.mt_Get_Length();
    }

    Vector2 mt_Get_Inverse(void) const
    {
        return Vector2(1.0f / x, 1.0f / y);
    }


};

using Vector2f = Vector2<float>;
using Vector2i = Vector2<int32_t>;
using Vector2u = Vector2<uint32_t>;

template<typename T>
bool operator==(const Vector2<T>& a, const Vector2<T>& b)
{
    return a.x == b.x && a.y == b.y;
}

template<typename T>
Vector2<T> operator+(const Vector2<T>& a, const Vector2<T>& b)
{
    return Vector2<T>(a.x + b.x, a.y + b.y);
}

template<typename T>
Vector2<T> operator+(const Vector2<T>& a, T b)
{
    return Vector2(a.x + b, a.y + b);
}

template<typename T>
Vector2<T> operator-(const Vector2<T>& a, const Vector2<T>& b)
{
    return Vector2<T>(a.x - b.x, a.y - b.y);
}

template<typename T>
Vector2<T> operator*(const Vector2<T>& v, float m)
{
    return Vector2<T>(v.x * m, v.y * m);
}

template<typename T>
Vector2<T> operator*(float m, const Vector2<T>& v)
{
    return Vector2<T>(v.x * m, v.y * m);
}

template<typename T>
Vector2<T> operator*(const Vector2<T>& a, const Vector2<T>& b)
{
    return Vector2<T>(a.x * b.x, a.y * b.y);
}

template<typename T>
Vector2<T> operator/(const Vector2<T>& a, float d)
{
    return Vector2<T>(a.x / d, a.y / d);
}

template<typename T>
Vector2<T> operator/(const Vector2<T>& a, const Vector2<T>& b)
{
    return Vector2<T>(a.x / b.x, a.y / b.y);
}

}

#endif // _LYS_VECTOR2_HPP
