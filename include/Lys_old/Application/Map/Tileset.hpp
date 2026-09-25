#ifndef _LYS_TILESET_HPP
#define _LYS_TILESET_HPP 1

#include "Lys/LysGraphics.hpp"

namespace lys
{




class LYS_API GeneratedTilesetTexture
{
public:

private:
    Texture m_Texture;
};


class LYS_API Tileset
{
public:
    virtual ~Tileset() = default;

    Rectf mt_Tileset_Get_Tile_Normalized_Rect(uint32_t tile_id);

protected:

};


struct LYS_API TilesetInfo
{
    Vector2u m_Tile_Count = {};
    Vector2u m_Texture_Size = {};
    Vector2f m_Tile_Size = {};
};

Vector2f LYS_API fn_Tileset_Get_Tile_Normalized_Pos(const TilesetInfo& tileset_data, uint32_t tile_id);
Vector2f LYS_API fn_Tileset_Get_Tile_Normalized_Size(const TilesetInfo& tileset_data);

}

#endif // _LYS_TILESET_HPP
