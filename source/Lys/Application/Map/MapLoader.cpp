#include "Lys/Application/Map/MapLoader.hpp"
#include "Lys/Application/Map/Map.hpp"
#include "Lys/Core/Log.hpp"
#include "TinyXML_Boosted/XMLFileLoader.hpp"

namespace lys
{


bool MapLoader::mt_Load_Map(const File& file_path, MapData& map_data)
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
        MapLoader_Tiled_1_9 l_Loader;

        map_data.m_Tiles_Layers.mt_Clear();
        map_data.m_Objects_Layers.mt_Clear();

        return l_Loader.mt_Load(file_path.mt_Get_Path_Name_Ext(), map_data);
    }

    LYS_LOG_CORE_ERROR("Tiled version not handled: '%s'", l_Tiled_Header.m_Version.c_str());

    return false;
}


bool MapLoader_Tiled_1_9::mt_Load(const File& file_path, MapData& map_data)
{
    bool l_b_Ret = true;
    const TiXmlElement* l_Child;
    XMLFileLoader l_Loader;

    l_Loader.mt_Add_On_Entry_Callback("/map/tileset", [&](const XML_Element& tileset)
    {
        std::string l_Source_File;
        MapData::TilesetData l_Tileset_Data;

        if (tileset.mt_Get_Attribute("firstgid", l_Tileset_Data.m_First_Gid) == false) return false;
        if (tileset.mt_Get_Attribute("source", l_Source_File) == false) return false;

        if (mt_Load_Tileset(file_path.mt_Get_Path() + l_Source_File, l_Tileset_Data) == false) return false;

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
    l_Loader.mt_Add_On_Exit_Callback("/map/layer", [&](const XML_Element& layer)
    {
        map_data.m_Tiles_Layers.mt_Add_Element(m_Tile_Layer, m_Tile_Layer.m_Tile_Layer_Id, m_Tile_Layer.m_Tile_Layer_Name);

        return true;
    });
    l_Loader.mt_Add_On_Entry_Callback("/map/objectgroup", [&](const XML_Element& objectgroup)
    {
        if (objectgroup.mt_Get_Attribute("name", m_Object_Layer.m_Object_Layer_Name) == false) return false;
        if (objectgroup.mt_Get_Attribute("id", m_Object_Layer.m_Object_Layer_Id) == false) return false;

        return true;
    });
    l_Loader.mt_Add_On_Entry_Callback("/map/objectgroup/object", [&](const XML_Element& object)
    {
        return mt_Load_Object(object);
    });
    l_Loader.mt_Add_On_Entry_Callback("/map/objectgroup/object/property", [&](const XML_Element& object)
    {
        return mt_Load_Object_Property(object);
    });
    l_Loader.mt_Add_On_Exit_Callback("/map/objectgroup/object", [&](const XML_Element& object)
    {
        m_Object_Layer.m_Objects.mt_Add_Element(m_Object, m_Object.m_Object_Id, m_Object.m_Object_Name);
        return true;
    });
    l_Loader.mt_Add_On_Exit_Callback("/map/objectgroup", [&](const XML_Element& )
    {
        map_data.m_Objects_Layers.mt_Add_Element(m_Object_Layer, m_Object_Layer.m_Object_Layer_Id, m_Object_Layer.m_Object_Layer_Name);
        return true;
    });
    l_Loader.mt_Add_On_Entry_Callback("", [&](const XML_Element& )
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
    });
    l_Loader.mt_Add_On_Entry_Callback("", [&](const XML_Element& )
    {
        return true;
    });


    return l_Loader.mt_Load(file_path.mt_Get_Path_Name_Ext());
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
    if (object.mt_Get_Attribute("id", m_Object.m_Object_Id) == false) return false;
    if (object.mt_Get_Attribute("name", m_Object.m_Object_Name) == false) return false;
    if (object.mt_Get_Attribute("x", m_Object.m_Object_Pix_Pos.x) == false) return false;
    if (object.mt_Get_Attribute("y", m_Object.m_Object_Pix_Pos.y) == false) return false;

    object.mt_Get_Attribute("class", m_Object.m_Object_Class);
    object.mt_Get_Attribute("width", m_Object.m_Object_Pix_Size.x);
    object.mt_Get_Attribute("height", m_Object.m_Object_Pix_Size.y);

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
    if (property.mt_Get_Attribute("type", l_Property_Type) == false)
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
    }
    else
    {
        property.mt_Get_Attribute("value", l_String_Value);
        m_Object.m_Object_Properties_String.emplace(l_Property_Name, l_String_Value);
        return true;
    }

    return false;
}


bool MapLoader_Tiled_1_9::mt_Load_Tileset(const File& file_path, MapData::TilesetData& tileset_data)
{
    XMLFileLoader l_Loader;

    l_Loader.mt_Add_On_Entry_Callback("/tileset", [&](const XML_Element& tileset)
    {
        Vector2u l_Cell_Size_Pix;
        unsigned int l_Tile_Count;
        unsigned int l_Column_Count;

        if (tileset.mt_Get_Attribute("tilewidth", l_Cell_Size_Pix.x) == false) return false;
        if (tileset.mt_Get_Attribute("tileheight", l_Cell_Size_Pix.y) == false) return false;
        if (tileset.mt_Get_Attribute("tilecount", l_Tile_Count) == false) return false;
        if (tileset.mt_Get_Attribute("columns", l_Column_Count) == false) return false;

        tileset_data.m_Tileset_Info.m_Tile_Count.x = l_Column_Count;
        tileset_data.m_Tileset_Info.m_Tile_Count.y = l_Tile_Count / l_Column_Count;
        tileset_data.m_Tileset_Info.m_Texture_Size = l_Cell_Size_Pix * tileset_data.m_Tileset_Info.m_Tile_Count;

        return true;
    });

    return l_Loader.mt_Load(file_path.mt_Get_Path_Name_Ext());
}


}
