#ifndef _LYS_COLOR_TRAIT_HPP
#define _LYS_COLOR_TRAIT_HPP 1

namespace lys
{

template<typename ColorType>
struct ColorTraits
{
    static constexpr ColorType Construct(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    {
        return ColorType { r, g, b, a };  // Par défaut, on suppose un constructeur simple
    }

    static constexpr uint8_t r(const ColorType& c)
    {
        return c.r;
    }
    static constexpr uint8_t g(const ColorType& c)
    {
        return c.g;
    }
    static constexpr uint8_t b(const ColorType& c)
    {
        return c.b;
    }
    static constexpr uint8_t a(const ColorType& c)
    {
        return c.a;
    }
};

}  // namespace lys

#endif  // _LYS_COLOR_TRAIT_HPP
