#ifndef _LYS_COLOR_TRAIT_HPP
#define _LYS_COLOR_TRAIT_HPP 1

#include <array>
#include <cstdint>
#include <stdexcept>
#include <string_view>

namespace lys
{

template<typename ColorType>
struct ColorTraits
{
    static constexpr ColorType Construct(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    {
        return ColorType { r, g, b, a };  // Par défaut, on suppose un constructeur simple
    }

    static constexpr ColorType ParseWebColor(std::string_view str)
    {
        if (str.empty() || str[0] != '#')
        {
            throw std::invalid_argument("Color string must start with '#'");
        }

        if (str.size() != 7 && str.size() != 9)
        {
            throw std::invalid_argument("Color string must be in format #RRGGBB or #RRGGBBAA");
        }

        uint8_t r = hexToByte(str[1], str[2]);
        uint8_t g = hexToByte(str[3], str[4]);
        uint8_t b = hexToByte(str[5], str[6]);
        uint8_t a = 255;

        if (str.size() == 9)
        {
            a = hexToByte(str[7], str[8]);
        }

        return ColorTraits<ColorType>::Construct(r, g, b, a);
    }

    static constexpr const char* ToWebColor(const ColorType& c, std::array<char, 8>& buffer)
    {
        snprintf(buffer.data(), 8, "#%02x%02x%02x", r(c), g(c), b(c));
        return buffer.data();
    }

    static constexpr const char* ToWebColorAlpha(const ColorType& c, std::array<char, 10>& buffer)
    {
        snprintf(buffer.data(), 10, "#%02x%02x%02x%02x", r(c), g(c), b(c), a(c));
        return buffer.data();
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

private:
    // Conversion hex -> byte
    static constexpr uint8_t hexToByte(char high, char low)
    {
        auto hexVal = [](char c) -> uint8_t
        {
            if (c >= '0' && c <= '9')
            {
                return c - '0';
            }
            if (c >= 'a' && c <= 'f')
            {
                return c - 'a' + 10;
            }
            if (c >= 'A' && c <= 'F')
            {
                return c - 'A' + 10;
            }
            throw std::invalid_argument("Invalid hex character");
        };
        return static_cast<uint8_t>((hexVal(high) << 4) | hexVal(low));
    }
};

}  // namespace lys

#endif  // _LYS_COLOR_TRAIT_HPP
