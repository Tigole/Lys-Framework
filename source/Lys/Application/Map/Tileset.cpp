#include "Lys/Application/Map/Tileset.hpp"

namespace lys
{

Rectf fn_Tileset_Get_Tile_Normalized_Rect(const TilesetInfo& tileset_data, const Vector2u& tile_cell)
{
    Rectf l_Ret;

    l_Ret.m_Width_Height.x = static_cast<float>(tileset_data.m_Texture_Size.x) / static_cast<float>(tileset_data.m_Tile_Count.x);
    l_Ret.m_Width_Height.y = static_cast<float>(tileset_data.m_Texture_Size.y) / static_cast<float>(tileset_data.m_Tile_Count.y);
    l_Ret.m_Top_Left = l_Ret.m_Width_Height * lys::Vector2f(tile_cell.x, tile_cell.y);

    return l_Ret;

}

}
