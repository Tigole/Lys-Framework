#ifndef _VEC_HPP
#define _VEC_HPP 1

#include <cstdint>

namespace lys
{

template<typename T>
struct Vec2
{
    T x;
    T y;
};

using Vec2u64 = Vec2<uint64_t>;
using Vec2u32 = Vec2<uint32_t>;
using Vec2u16 = Vec2<uint16_t>;
using Vec2u8  = Vec2<uint8_t>;
using Vec2i64 = Vec2<int64_t>;
using Vec2i32 = Vec2<int32_t>;
using Vec2i16 = Vec2<int16_t>;
using Vec2i8  = Vec2<int8_t>;
using Vec2f32 = Vec2<float>;
using Vec2f64 = Vec2<double>;

}  // namespace lys

#endif  // _VEC_HPP
