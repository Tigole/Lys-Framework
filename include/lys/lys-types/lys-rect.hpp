#ifndef _LYS_RECT_HPP
#define _LYS_RECT_HPP 1

#include "lys-vec2.hpp"

namespace lys
{

template<typename T>
struct Rect
{
    T x;
    T y;
    T width;
    T height;
};

using Rectfu64 = Rect<uint64_t>;
using Rectfu32 = Rect<uint32_t>;
using Rectfu16 = Rect<uint16_t>;
using Rectfu8  = Rect<uint8_t>;
using Rectfi64 = Rect<int64_t>;
using Rectfi32 = Rect<int32_t>;
using Rectfi16 = Rect<int16_t>;
using Rectfi8  = Rect<int8_t>;
using Rectf32  = Rect<float>;
using Rectf64  = Rect<double>;

}  // namespace lys

#endif  // _LYS_RECT_HPP
