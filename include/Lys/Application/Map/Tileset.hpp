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

struct LYS_API TilesetInfo
{
    Vector2u m_Tile_Count;
    Vector2u m_Texture_Size;
};

LYS_API Rectf fn_Tileset_Get_Tile_Normalized_Rect(const TilesetInfo& tileset_data, const Vector2u& tile_cell);

}

#endif // _LYS_TILESET_HPP
