#include "Lys/Application/Map/MapLoader.hpp"
#include "Lys/Application/Map/Map.hpp"
#include "Lys/Core/Log.hpp"
#include "Lys/MathModule/HexGrid.hpp"
#include "TinyXML_Boosted/XMLFileLoader.hpp"

#include <sstream>

namespace lys
{


class MapLayout_Hexagonal : public MapLayout
{
public:
    Vector2f mt_Coord_To_Normalized_Space(const Vector2i& coord, bool center) const override;
    Vector2f mt_Get_Cell_Size_Normalized_Space(void) const override;
};

Vector2f MapLayout_Hexagonal::mt_Coord_To_Normalized_Space(const Vector2i& coord, bool center) const
{
    hex::Layout l_Layout(HexTileMode::Pointy_Top, 52.0f, 52.0f, 0.0f, 0.0f);
    //hex::Layout l_Layout(HexTileMode::Pointy_Top, 52.0f, 52.0f, tile_size.x / 2.0f, tile_size.y / 2.0f);
    //hex::Point l_Point = hex::fn_Hex_To_Pixel(l_Layout, hex::fn_From_Offset(hex::OffsetCoordMode::Odd, hex::OffsetCoordType::r, {coord.x, coord.y}));

    Vector2f l_Pix;

    l_Pix.x = (coord.x + (0.5f * (coord.y & 1)));
    l_Pix.y = coord.y * 0.75f;

    if (center == true)
    {
        l_Pix.x += 0.5f;
        l_Pix.y += 0.5f;
    }

    return l_Pix * mt_Get_Cell_Size_Normalized_Space();
}

Vector2f MapLayout_Hexagonal::mt_Get_Cell_Size_Normalized_Space(void) const
{
    return Vector2f(sqrt(3) / 2.0f, 1.0f);
}










bool MapLoader::mt_Load_Map(const File& file_path, MapData& map_data, std::unique_ptr<MapLayout>& map_layout)
{
    XMLFileLoader l_Loader;
    TiledHeader l_Tiled_Header;

    l_Loader.mt_Add_On_Entry_Callback("/map", [&](const XML_Element& map)
    {
        if (map.mt_Get_Attribute("infinite", l_Tiled_Header.m_Is_Infinite) == false) return false;
        if (map.mt_Get_Attribute("version", l_Tiled_Header.m_Version) == false) return false;
        if (map.mt_Get_Attribute("tiledversion", l_Tiled_Header.m_Tiled_Version) == false) return false;
        if (map.mt_Get_Attribute("orientation", l_Tiled_Header.m_Orientation) == false) return false;
        if (map.mt_Get_Attribute("width", l_Tiled_Header.m_Map_Dimension.x) == false) return false;
        if (map.mt_Get_Attribute("height", l_Tiled_Header.m_Map_Dimension.y) == false) return false;
        if (map.mt_Get_Attribute("tilewidth", l_Tiled_Header.m_Tile_Dimension.x) == false) return false;
        if (map.mt_Get_Attribute("tileheight", l_Tiled_Header.m_Tile_Dimension.y) == false) return false;

        return true;
    });

    if (l_Loader.mt_Load(file_path.mt_Get_Path_Name_Ext()) == false)
    {
        return false;
    }

    if (l_Tiled_Header.m_Version == "1.9")
    {
        MapLoader_Tiled_1_9 l_Map_Loader;

        map_data.m_Tiles_Layers.mt_Clear();
        map_data.m_Objects_Layers.mt_Clear();

        return l_Map_Loader.mt_Load(file_path.mt_Get_Path_Name_Ext(), map_data, map_layout);
    }

    LYS_LOG_CORE_ERROR("Tiled version not handled: '%s'", l_Tiled_Header.m_Version.c_str());

    return false;
}


bool MapLoader_Tiled_1_9::mt_Load(const File& file_path, MapData& map_data, std::unique_ptr<MapLayout>& map_layout)
{
    auto l_fn_Orientation = [](const std::string& value, MapData::TileType& res) -> bool
    {
        if (value == "orthogonal")
        {
            res = MapData::TileType::Orthogonal;
            return true;
        }
        if (value == "hexagonal")
        {
            res = MapData::TileType::Hexagonal;
            return true;
        }

        return false;
    };
    auto l_fn_Axis = [](const std::string& value, MapData::StaggerAxis& res) -> bool
    {
        if (value == "x")
        {
            res = MapData::StaggerAxis::X;
            return true;
        }
        if (value == "y")
        {
            res = MapData::StaggerAxis::Y;
            return true;
        }
        return false;
    };
    auto l_fn_Index = [](const std::string& value, MapData::StaggerIndex& res) -> bool
    {
        if (value == "even")
        {
            res = MapData::StaggerIndex::Even;
            return true;
        }
        if (value == "odd")
        {
            res = MapData::StaggerIndex::Odd;
            return true;
        }
        return false;
    };
    XMLFileLoader l_Loader;

    l_Loader.mt_Add_On_Entry_Callback("/map", [&](const XML_Element& map)
    {
        if (map.mt_Get_Attribute("orientation", map_data.m_Tile_Type, l_fn_Orientation) == false) return false;
        if (map_data.m_Tile_Type == MapData::TileType::Hexagonal)
        {
            if (map.mt_Get_Attribute("staggeraxis", map_data.m_Stagger_Axis, l_fn_Axis) == false) return false;
            if (map.mt_Get_Attribute("staggerindex", map_data.m_Stagger_Index, l_fn_Index) == false) return false;
        }

        return true;
    });
    l_Loader.mt_Add_On_Entry_Callback("/map/tileset", [&](const XML_Element& tileset)
    {
        std::string l_Source_File;
        MapData::TilesetData l_Tileset_Data;

        if (tileset.mt_Get_Attribute("firstgid", l_Tileset_Data.m_First_Gid) == false) return false;
        if (tileset.mt_Get_Attribute("source", l_Source_File) == false) return false;

        if (mt_Load_Tileset(file_path.mt_Get_Path() + l_Source_File, l_Tileset_Data) == false) return false;

/// fixme multiple images
        map_data.m_Tileset_Data.push_back(l_Tileset_Data);

        return true;
    });
    l_Loader.mt_Add_On_Entry_Callback("/map/layer", [&](const XML_Element& layer)
    {
        return mt_Load_Layer(layer);
    });
    l_Loader.mt_Add_On_Entry_Callback("/map/layer/data", [&](const XML_Element& layer)
    {
        return mt_Load_Layer_Data(layer);
    });
    l_Loader.mt_Add_On_Exit_Callback("/map/layer", [&](const XML_Element&)
    {
        map_data.m_Tiles_Layers.mt_Add_Element(m_Tile_Layer, m_Tile_Layer.m_Tile_Layer_Id, m_Tile_Layer.m_Tile_Layer_Name);

        return true;
    });
    l_Loader.mt_Add_On_Entry_Callback("/map/objectgroup", [&](const XML_Element& objectgroup)
    {
        m_Object_Layer = MapData::ObjectLayer();

        if (objectgroup.mt_Get_Attribute("name", m_Object_Layer.m_Object_Layer_Name) == false) return false;
        if (objectgroup.mt_Get_Attribute("id", m_Object_Layer.m_Object_Layer_Id) == false) return false;

        return true;
    });
    l_Loader.mt_Add_On_Entry_Callback("/map/objectgroup/object", [&](const XML_Element& object)
    {
        return mt_Load_Object(object);
    });
    l_Loader.mt_Add_On_Entry_Callback("/map/objectgroup/object/polygon", [&](const XML_Element& polygon)
    {
        return mt_Load_Object_Polygon(polygon);
    });
    l_Loader.mt_Add_On_Entry_Callback("/map/objectgroup/object/properties/property", [&](const XML_Element& object)
    {
        return mt_Load_Object_Property(object);
    });
    l_Loader.mt_Add_On_Exit_Callback("/map/objectgroup/object", [&](const XML_Element&)
    {
        m_Object_Layer.m_Objects.mt_Add_Element(m_Object, m_Object.m_Object_Id, m_Object.m_Object_Name);
        return true;
    });
    l_Loader.mt_Add_On_Exit_Callback("/map/objectgroup", [&](const XML_Element& )
    {
        map_data.m_Objects_Layers.mt_Add_Element(m_Object_Layer, m_Object_Layer.m_Object_Layer_Id, m_Object_Layer.m_Object_Layer_Name);
        return true;
    });
    /*l_Loader.mt_Add_On_Entry_Callback("", [&](const XML_Element& )
    {
        return true;
    });
    l_Loader.mt_Add_On_Entry_Callback("", [&](const XML_Element& )
    {
        return true;
    });
    l_Loader.mt_Add_On_Entry_Callback("", [&](const XML_Element& )
    {
        return true;
    });*/

    if (l_Loader.mt_Load(file_path.mt_Get_Path_Name_Ext()) == false)
    {
        LYS_LOG_CORE_ERROR("%s", l_Loader.mt_Get_Error_Description().c_str());
        return false;
    }

    if (map_data.m_Tile_Type == MapData::TileType::Hexagonal)
    {
/// fixme Multiple layouts (1 by tileset ?) ?
        map_layout.reset(new MapLayout_Hexagonal());
    }

    return true;
}

bool MapLoader_Tiled_1_9::mt_Load_Layer(const XML_Element& layer)
{
    if (layer.mt_Get_Attribute("name", m_Tile_Layer.m_Tile_Layer_Name) == false) return false;
    if (layer.mt_Get_Attribute("id", m_Tile_Layer.m_Tile_Layer_Id) == false) return false;
    if (layer.mt_Get_Attribute("width", m_Tile_Layer.m_Tile_Layer_Size.x) == false) return false;
    if (layer.mt_Get_Attribute("height", m_Tile_Layer.m_Tile_Layer_Size.y) == false) return false;

    m_Tile_Layer.m_Tiles.mt_Resize(m_Tile_Layer.m_Tile_Layer_Size.x, m_Tile_Layer.m_Tile_Layer_Size.y, 0);

    return true;
}

bool MapLoader_Tiled_1_9::mt_Load_Layer_Data(const XML_Element& data)
{
    std::string l_Data_Encoding_Type;

    if (data.mt_Get_Attribute("encoding", l_Data_Encoding_Type) == false) return false;

    if (l_Data_Encoding_Type == "csv")
    {
        std::string l_CSV_Content;

        if (data.mt_Get_Text(l_CSV_Content) == false) return false;

        return mt_Load_Layer_Data_CSV(l_CSV_Content.c_str());
    }

    return false;
}

bool MapLoader_Tiled_1_9::mt_Load_Layer_Data_CSV(const char* csv_encoded_data)
{
    bool l_b_Ret = false;
    uint32_t l_Tile_Index = 0;
    Index2D l_Tile_Array_Index(0, 0);

    if (csv_encoded_data != nullptr)
    {
        while ((*csv_encoded_data != '\0') && (m_Tile_Layer.m_Tiles.mt_Is_Index_Valid(l_Tile_Array_Index)))
        {
            if (*csv_encoded_data == ',')
            {
                m_Tile_Layer.m_Tiles[l_Tile_Array_Index] = l_Tile_Index;
                l_Tile_Index = 0;
                m_Tile_Layer.m_Tiles.mt_Increment_Index(l_Tile_Array_Index);
            }
            else if (*csv_encoded_data != ' ')
            {
                l_Tile_Index *= 10;
                l_Tile_Index += *csv_encoded_data - '0';
            }

            csv_encoded_data++;
        }
        l_b_Ret = true;
    }

    return l_b_Ret;
}

bool MapLoader_Tiled_1_9::mt_Load_Object(const XML_Element& object)
{
    m_Object = MapData::Object();

    if (object.mt_Get_Attribute("id", m_Object.m_Object_Id) == false) return false;
    if (object.mt_Get_Attribute("x", m_Object.m_Object_Pix_Pos.x) == false) return false;
    if (object.mt_Get_Attribute("y", m_Object.m_Object_Pix_Pos.y) == false) return false;

    object.mt_Get_Attribute("name", m_Object.m_Object_Name);
    object.mt_Get_Attribute("class", m_Object.m_Object_Class);
    object.mt_Get_Attribute("width", m_Object.m_Object_Pix_Size.x);
    object.mt_Get_Attribute("height", m_Object.m_Object_Pix_Size.y);
    object.mt_Get_Attribute("rotation", m_Object.m_Object_Rotation_Degres);
    object.mt_Get_Attribute("gid", m_Object.m_Object_Gid);

    return true;
}

bool MapLoader_Tiled_1_9::mt_Load_Object_Property(const XML_Element& property)
{
    std::string l_Property_Name;
    std::string l_Property_Type;
    bool l_Bool_Value = false;
    int l_Int_Value = 0;
    float l_Float_Value = 0.0f;
    std::string l_String_Value;
    Color l_Color;

    if (property.mt_Get_Attribute("name", l_Property_Name) == false) return false;
    if (property.mt_Get_Attribute("type", l_Property_Type) == true)
    {
        if (l_Property_Type == "bool")
        {
            property.mt_Get_Attribute("value", l_Bool_Value);
            m_Object.m_Object_Properties_Bool.emplace(l_Property_Name, l_Bool_Value);
            return true;
        }
        else if (l_Property_Type == "int")
        {
            property.mt_Get_Attribute("value", l_Int_Value);
            m_Object.m_Object_Properties_Int.emplace(l_Property_Name, l_Int_Value);
            return true;
        }
        else if (l_Property_Type == "float")
        {
            property.mt_Get_Attribute("value", l_Float_Value);
            m_Object.m_Object_Properties_Float.emplace(l_Property_Name, l_Float_Value);
            return true;
        }
        else if (l_Property_Type == "color")
        {
            property.mt_Get_Attribute("value", l_String_Value);
            m_Object.m_Object_Properties_Color.emplace(l_Property_Name, l_Color);
            return true;
        }
        else if (l_Property_Type == "file")
        {
            property.mt_Get_Attribute("value", l_String_Value);
            m_Object.m_Object_Properties_String.emplace(l_Property_Name, l_String_Value);
            return true;
        }
        else if (l_Property_Type == "object")
        {
            property.mt_Get_Attribute("value", l_Int_Value);
            m_Object.m_Object_Properties_Int.emplace(l_Property_Name, l_Int_Value);
            return true;
        }
    }
    else
    {
        property.mt_Get_Attribute("value", l_String_Value);
        m_Object.m_Object_Properties_String.emplace(l_Property_Name, l_String_Value);
        return true;
    }

    LYS_LOG_CORE_ERROR("Failed to load property '%s' of type '%s' (unsupported)", l_Property_Name.c_str(), l_Property_Type.c_str());

    return false;
}

bool MapLoader_Tiled_1_9::mt_Load_Object_Polygon(const XML_Element& polygon)
{
    std::stringstream l_ss;
    std::string l_Polygon_Points;

    if (polygon.mt_Get_Attribute("points", l_Polygon_Points) == false) return false;
    l_ss.str(l_Polygon_Points);

    while(std::getline(l_ss, l_Polygon_Points, ' '))
    {
        std::stringstream l_ss2;
        Vector2f l_Offset;
        char l_Coma;

        l_ss2.str(l_Polygon_Points);

        l_ss2 >> l_Offset.x >> l_Coma >> l_Offset.y;

        m_Object.m_Polygon.push_back(l_Offset);
    }

    return true;
}

bool MapLoader_Tiled_1_9::mt_Load_Tileset(const File& file_path, MapData::TilesetData& tileset_data)
{
    XMLFileLoader l_Loader;

    l_Loader.mt_Add_On_Entry_Callback("/tileset", [&](const XML_Element& tileset)
    {
        unsigned int l_Tile_Count;
        unsigned int l_Column_Count;

        if (tileset.mt_Get_Attribute("tilewidth", tileset_data.m_Tileset_Info.m_Tile_Size.x) == false) return false;
        if (tileset.mt_Get_Attribute("tileheight", tileset_data.m_Tileset_Info.m_Tile_Size.y) == false) return false;
        if (tileset.mt_Get_Attribute("tilecount", l_Tile_Count) == false) return false;
        if (tileset.mt_Get_Attribute("columns", l_Column_Count) == false) return false;

        tileset_data.m_Tileset_Info.m_Tile_Count.x = l_Column_Count;
        tileset_data.m_Tileset_Info.m_Tile_Count.y = (l_Column_Count == 0) ? 1 : (l_Tile_Count / l_Column_Count);
        tileset_data.m_Tileset_Info.m_Texture_Size.x = tileset_data.m_Tileset_Info.m_Tile_Size.x * tileset_data.m_Tileset_Info.m_Tile_Count.x;
        tileset_data.m_Tileset_Info.m_Texture_Size.y = tileset_data.m_Tileset_Info.m_Tile_Size.y * tileset_data.m_Tileset_Info.m_Tile_Count.y;

        return true;
    });

    if (l_Loader.mt_Load(file_path.mt_Get_Path_Name_Ext()) == false)
    {
        LYS_LOG_CORE_ERROR("'%s': %s", file_path.mt_Get_Path_Name_Ext().c_str(), l_Loader.mt_Get_Error_Description().c_str());
        return false;
    }

    return true;
}


}
