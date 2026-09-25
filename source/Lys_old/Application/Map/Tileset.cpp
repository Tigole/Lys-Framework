#include "Lys/Application/Map/Tileset.hpp"

namespace lys
{

Vector2f fn_Tileset_Get_Tile_Normalized_Pos(const TilesetInfo& tileset_data, uint32_t tile_id)
{
    const Vector2f l_Tile_To_Pix = fn_Tileset_Get_Tile_Normalized_Size(tileset_data);
    Vector2f l_Ret;

    if ((tile_id > 0) && (tile_id <= (tileset_data.m_Tile_Count.x * tileset_data.m_Tile_Count.y)))
    {
        tile_id--;
        l_Ret.x = (tile_id % tileset_data.m_Tile_Count.x) * l_Tile_To_Pix.x;
        l_Ret.y = (tile_id / tileset_data.m_Tile_Count.x) * l_Tile_To_Pix.y;
    }

    return l_Ret;
}

Vector2f LYS_API fn_Tileset_Get_Tile_Normalized_Size(const TilesetInfo& tileset_data)
{
    Vector2f l_Ret(tileset_data.m_Tile_Size);

    l_Ret.x /= tileset_data.m_Texture_Size.x;
    l_Ret.y /= tileset_data.m_Texture_Size.y;

    return l_Ret;
}

}
