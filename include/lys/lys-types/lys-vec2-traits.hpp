#ifndef _LYS_VEC2_TRAIT_HPP
#define _LYS_VEC2_TRAIT_HPP 1

namespace lys
{

template<typename Vec2Type>
struct Vec2Traits
{
    template<typename T>
    static constexpr Vec2Type Construct(T x, T y)
    {
        return Vec2Type { x, y };
    }
    template<typename T>
    static inline T& x(Vec2Type& v)
    {
        return v.x;
    }
    template<typename T>
    static inline T& y(Vec2Type& v)
    {
        return v.y;
    }
};

}  // namespace lys

#endif  // _LYS_VEC2_TRAIT_HPP
