#ifndef _LYS_MAP_LAYOUT_HPP
#define _LYS_MAP_LAYOUT_HPP 1

#include <lys-types/lys-vec2.hpp>

namespace lys
{

template<typename __Vec2f, typename __Vec2i>
class __MapLayout
{
public:
    virtual ~__MapLayout() = default;

    virtual __Vec2f Coord_To_Normalized_Space(__Vec2i coord, bool center) const = 0;
    virtual __Vec2f Get_Cell_Size_Normalized_Space(void) const                  = 0;
};

template<typename __Vec2f, typename __Vec2i>
class __MapLayout_Hexagonal: public __MapLayout<__Vec2f, __Vec2i>
{
public:
    __Vec2f Coord_To_Normalized_Space(__Vec2i coord, bool center) const override;
    __Vec2f Get_Cell_Size_Normalized_Space(void) const override;
};

using MapLayout = __MapLayout<lys::Vec2f32, lys::Vec2i32>;

// using MapLayout_Hexagonal = __MapLayout_Hexagonal<lys::Vec2f32, lys::Vec2i32>;

}  // namespace lys

#include <lys-tiled-map-loading/lys-map-layout.inl>

#endif  // _LYS_MAP_LAYOUT_HPP
