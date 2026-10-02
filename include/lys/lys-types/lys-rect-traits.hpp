#ifndef _LYS_RECT_TRAITS_HPP
#define _LYS_RECT_TRAITS_HPP 1

#include "lys-vec2-traits.hpp"

namespace lys
{

template<typename RectType>
struct RectTraits
{
    template<typename T>
    static constexpr RectType Construct(T x, T y, T width, T height)
    {
        return RectType { x, y, width, height };
    }

    template<typename Vec2Type>
    static constexpr RectType Construct(Vec2Type pos, Vec2Type size)
    {
        return RectType { Vec2Traits<Vec2Type>::x(pos), Vec2Traits<Vec2Type>::y(pos), Vec2Traits<Vec2Type>::x(size),
                          Vec2Traits<Vec2Type>::y(size) };
    }

    template<typename T>
    static inline T& x(RectType& r)
    {
        return r.x;
    }

    template<typename T>
    static inline T x(const RectType& r)
    {
        return r.x;
    }

    template<typename T>
    static inline T& y(RectType& r)
    {
        return r.y;
    }

    template<typename T>
    static inline T y(const RectType& r)
    {
        return r.y;
    }

    template<typename T>
    static inline T& width(RectType& r)
    {
        return r.width;
    }

    template<typename T>
    static inline T width(const RectType& r)
    {
        return r.width;
    }

    template<typename T>
    static inline T& height(RectType& r)
    {
        return r.height;
    }

    template<typename T>
    static inline T height(const RectType& r)
    {
        return r.height;
    }
};

template<typename RectType>
struct RectExTraits
{
    template<typename T>
    static inline T x(const RectType& r)
    {
        return RectTraits<RectType>::template x<T>(r);
    }
    template<typename T>
    static inline T y(const RectType& r)
    {
        return RectTraits<RectType>::template y<T>(r);
    }
    template<typename T>
    static inline T width(const RectType& r)
    {
        return RectTraits<RectType>::template width<T>(r);
    }
    template<typename T>
    static inline T height(const RectType& r)
    {
        return RectTraits<RectType>::template height<T>(r);
    }

    template<typename T>
    static inline T left(const RectType& r)
    {
        return std::min(x<T>(r), x<T>(r) + width<T>(r));
    }

    template<typename T>
    static inline T top(const RectType& r)
    {
        return std::min(y<T>(r), y<T>(r) + height<T>(r));
    }

    template<typename T>
    static inline T right(const RectType& r)
    {
        return std::max(x<T>(r), x<T>(r) + width<T>(r));
    }

    template<typename T>
    static inline T bottom(const RectType& r)
    {
        return std::max(y<T>(r), y<T>(r) + height<T>(r));
    }

    template<typename T>
    static inline bool Overlaps(const RectType& r1, const RectType& r2, RectType* result)
    {
        const T interLeft   = std::max(left<T>(r1), left<T>(r2));
        const T interTop    = std::max(top<T>(r1), top<T>(r2));
        const T interRight  = std::min(right<T>(r1), right<T>(r2));
        const T interBottom = std::min(bottom<T>(r1), bottom<T>(r2));

        if (result != nullptr)
        {
            *result = RectTraits<RectType>::template Construct<T>(interLeft, interTop, interRight - interLeft, interBottom - interTop);
        }

        return (interLeft < interRight) && (interTop < interBottom);
    }

    template<typename T>
    static inline bool Contains(const RectType& container, const RectType& contained)
    {
        const bool x = left<T>(container) <= left<T>(contained) && right<T>(container) >= right<T>(contained);
        const bool y = top<T>(container) <= top<T>(contained) && bottom<T>(container) >= bottom<T>(contained);
        return x && y;
    }
};

}  // namespace lys

#endif  // _LYS_RECT_TRAITS_HPP
