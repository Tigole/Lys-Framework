#ifndef _LYS_COLOR_HPP
#define _LYS_COLOR_HPP 1

#include <cstdint>


namespace lys
{



struct Color
{
    Color(float red, float green, float blue, float alpha = 1.0f);
    Color(float _rgba[4]);
    Color(uint32_t rgb, uint8_t alpha);
    Color(uint32_t argb);
    Color();
    union
    {
        float rgba[4];
        struct
        {
            float r;
            float g;
            float b;
            float a;
        };
    };

    static Color White;
    static Color Black;
    static Color Transparent;
};


}


#endif // _LYS_COLOR_HPP
