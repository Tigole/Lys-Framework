#include "Lys/Core/Color.hpp"


namespace lys
{


Color::Color(float red, float green, float blue, float alpha) : r(red), g(green), b(blue), a(alpha){}
Color::Color(float _rgba[4]) : Color(_rgba[0], _rgba[1], _rgba[2], _rgba[3]){}
Color::Color() : Color(1.0f, 1.0f, 1.0f, 1.0f){}
Color::Color(uint32_t rgb, uint8_t alpha) : Color(static_cast<float>(rgb >> 16) / 255.0f,
                                                  static_cast<float>((rgb >> 8) & 0xff) / 255.0f,
                                                  static_cast<float>(rgb & 0xff) / 255.0f,
                                                  static_cast<float>(alpha) / 255.0f){}
Color::Color(uint32_t argb) : Color(argb & 0xffffff, argb >> 24){}

Color Color::White(1.0f, 1.0f, 1.0f, 1.0f);
Color Color::Black(0.0f, 0.0f, 0.0f, 1.0f);
Color Color::Transparent(0.0f, 0.0f, 0.0f, 0.0f);

}
