#include "Lys/Application/Map/MapLoader.hpp"
#include "Lys/Application/Map/Map.hpp"
#include "XMLFileLoader.hpp"

namespace lys
{


bool MapLoader::mt_Load_Map(const File& file_path, MapData& map_data)
{
    bool l_b_Ret = false;
    TiXmlDocument l_Document;
    const TiXmlElement* l_Root;

    if (l_Document.LoadFile(file_path.mt_Get_Path_Name_Ext().c_str()))
    {
        TiledHeader l_Tiled_Header;
        bool l_b_Header = true;
        l_Root = l_Document.RootElement();

        l_b_Header &= l_Root->QueryBoolAttribute("infinite", &l_Tiled_Header.m_Is_Infinite) == TIXML_SUCCESS;
        l_b_Header &= l_Root->QueryStringAttribute("version", &l_Tiled_Header.m_Version) == TIXML_SUCCESS;
        l_b_Header &= l_Root->QueryStringAttribute("tiledversion", &l_Tiled_Header.m_Tiled_Version) == TIXML_SUCCESS;
        l_b_Header &= l_Root->QueryStringAttribute("orientation", &l_Tiled_Header.m_Orientation) == TIXML_SUCCESS;
        l_b_Header &= l_Root->QueryIntAttribute("width", &l_Tiled_Header.m_Map_Dimension.x) == TIXML_SUCCESS;
        l_b_Header &= l_Root->QueryIntAttribute("height", &l_Tiled_Header.m_Map_Dimension.y) == TIXML_SUCCESS;
        l_b_Header &= l_Root->QueryIntAttribute("tilewidth", &l_Tiled_Header.m_Tile_Dimension.x) == TIXML_SUCCESS;
        l_b_Header &= l_Root->QueryIntAttribute("tileheight", &l_Tiled_Header.m_Tile_Dimension.y) == TIXML_SUCCESS;

        if (l_b_Header == true)
        {
            if (l_Tiled_Header.m_Version == "1.9")
            {
                MapLoader_Tiled_1_9 l_Loader(file_path.mt_Get_Path());

                map_data.m_Tiles_Layers.mt_Clear();
                map_data.m_Objects_Layers.mt_Clear();

                l_b_Ret = l_Loader.mt_Load(*l_Root, map_data);
            }
        }
    }

    return l_b_Ret;
}





MapLoader_Tiled_1_9::MapLoader_Tiled_1_9(const std::string& file_directory) :
    m_File_Directory(file_directory)
{}


bool MapLoader_Tiled_1_9::mt_Load(const TiXmlElement& root, MapData& map_data)
{
    bool l_b_Ret = true;
    const TiXmlElement* l_Child;

    for (l_Child = root.FirstChildElement(); (l_Child != nullptr) && (l_b_Ret == true); l_Child = l_Child->NextSiblingElement())
    {
        if (l_Child->ValueStr() == "tileset")
        {
            MapData::TilesetData l_Tileset_Data;
            TiXmlDocument l_Tileset_File;

            l_b_Ret = l_Child->QueryUnsignedAttribute("firstgid", &l_Tileset_Data.m_First_Gid) == TIXML_SUCCESS;
            l_b_Ret &= l_Child->QueryStringAttribute("source", &l_Tileset_Data.m_Source_File) == TIXML_SUCCESS;

            if (l_b_Ret == true)
            {
                l_b_Ret &= l_Tileset_File.LoadFile(std::string(m_File_Directory + l_Tileset_Data.m_Source_File.c_str()));

                if (l_b_Ret == true)
                {
                    const TiXmlElement* l_Root = l_Tileset_File.RootElement();
                    Vector2u l_Cell_Size_Pix;
                    unsigned int l_Tile_Count;
                    unsigned int l_Column_Count;

                    l_b_Ret &= l_Root->QueryUnsignedAttribute("tilewidth", &l_Cell_Size_Pix.x) == TIXML_SUCCESS;
                    l_b_Ret &= l_Root->QueryUnsignedAttribute("tileheight", &l_Cell_Size_Pix.y) == TIXML_SUCCESS;
                    l_b_Ret &= l_Root->QueryUnsignedAttribute("tilecount", &l_Tile_Count) == TIXML_SUCCESS;
                    l_b_Ret &= l_Root->QueryUnsignedAttribute("columns", &l_Column_Count) == TIXML_SUCCESS;

                    l_Tileset_Data.m_Tileset_Info.m_Tile_Count.x = l_Column_Count;
                    l_Tileset_Data.m_Tileset_Info.m_Tile_Count.y = l_Tile_Count / l_Column_Count;
                    l_Tileset_Data.m_Tileset_Info.m_Texture_Size = l_Cell_Size_Pix * l_Tileset_Data.m_Tileset_Info.m_Tile_Count;
                }

                map_data.m_Tileset_Data.push_back(l_Tileset_Data);
            }
        }
        else if (l_Child->ValueStr() == "layer")
        {
            MapData::TileLayer l_Tile_Layer;
            l_b_Ret = mt_Load_Layer(*l_Child, l_Tile_Layer);

            if (l_b_Ret == true)
            {
                map_data.m_Tiles_Layers.mt_Add_Element(l_Tile_Layer, l_Tile_Layer.m_Tile_Layer_Id, l_Tile_Layer.m_Tile_Layer_Name);
            }
        }
        else if (l_Child->ValueStr() == "objectgroup")
        {
            const TiXmlElement* l_Object;
            MapData::ObjectLayer l_Layer;
            unsigned int l_Layer_Id;

            l_Child->QueryStringAttribute("name", &l_Layer.m_Object_Layer_Name);
            l_b_Ret = l_Child->QueryUnsignedAttribute("id", &l_Layer_Id) == TIXML_SUCCESS;

            for (l_Object = l_Child->FirstChildElement("object"); (l_Object != nullptr) && (l_b_Ret == true); l_Object = l_Object->NextSiblingElement("object"))
            {
                l_b_Ret &= mt_Load_Object(*l_Object, l_Layer);
            }

            if (l_b_Ret == true)
            {
                l_Layer.m_Object_Layer_Id = l_Layer_Id;
                map_data.m_Objects_Layers.mt_Add_Element(l_Layer, l_Layer.m_Object_Layer_Id, l_Layer.m_Object_Layer_Name);
            }
        }
    }

    return l_b_Ret;
}

bool MapLoader_Tiled_1_9::mt_Load_Layer(const TiXmlElement& layer, MapData::TileLayer& tile_layer)
{
    bool l_b_Ret = true;
    const TiXmlElement* l_Data = layer.FirstChildElement("data");

    layer.QueryStringAttribute("name", &tile_layer.m_Tile_Layer_Name);
    l_b_Ret &= layer.QueryUnsignedAttribute("id", &tile_layer.m_Tile_Layer_Id) == TIXML_SUCCESS;
    l_b_Ret &= layer.QueryUnsignedAttribute("width", &tile_layer.m_Tile_Layer_Size.x) == TIXML_SUCCESS;
    l_b_Ret &= layer.QueryUnsignedAttribute("height", &tile_layer.m_Tile_Layer_Size.y) == TIXML_SUCCESS;

    l_b_Ret &= l_Data != nullptr;
    if (l_Data != nullptr)
    {
        std::string l_Data_Encoding;

        l_b_Ret &= l_Data->QueryStringAttribute("encoding", &l_Data_Encoding) == TIXML_SUCCESS;

        tile_layer.m_Tiles.mt_Resize(tile_layer.m_Tile_Layer_Size.x, tile_layer.m_Tile_Layer_Size.y, 0);

        if (l_Data_Encoding == "csv")
        {
            l_b_Ret &= mt_Load_Layer_Data_CSV(l_Data->GetText(), tile_layer);
        }
    }

    return l_b_Ret;
}

bool MapLoader_Tiled_1_9::mt_Load_Layer_Data_CSV(const char* csv_encoded_data, MapData::TileLayer& tile_layer)
{
    bool l_b_Ret = false;
    uint32_t l_Tile_Index = 0;
    Index2D l_Tile_Array_Index(0, 0);

    if (csv_encoded_data != nullptr)
    {
        while ((*csv_encoded_data != '\0') && (tile_layer.m_Tiles.mt_Is_Index_Valid(l_Tile_Array_Index)))
        {
            if (*csv_encoded_data == ',')
            {
                tile_layer.m_Tiles[l_Tile_Array_Index] = l_Tile_Index;
                l_Tile_Index = 0;
                tile_layer.m_Tiles.mt_Increment_Index(l_Tile_Array_Index);
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

bool MapLoader_Tiled_1_9::mt_Load_Object(const TiXmlElement& object, MapData::ObjectLayer& object_layer)
{
    bool l_b_Ret = true;
    const TiXmlElement* l_Property = object.FirstChildElement("properties");
    MapData::Object l_Object;

    l_b_Ret &= object.QueryUnsignedAttribute("id", &l_Object.m_Object_Id) == TIXML_SUCCESS;
    l_b_Ret &= object.QueryStringAttribute("name", &l_Object.m_Object_Name) == TIXML_SUCCESS;
    l_b_Ret &= object.QueryFloatAttribute("x", &l_Object.m_Object_Pix_Pos.x) == TIXML_SUCCESS;
    l_b_Ret &= object.QueryFloatAttribute("y", &l_Object.m_Object_Pix_Pos.y) == TIXML_SUCCESS;
    object.QueryStringAttribute("class", &l_Object.m_Object_Class);
    object.QueryFloatAttribute("width", &l_Object.m_Object_Pix_Size.x);
    object.QueryFloatAttribute("height", &l_Object.m_Object_Pix_Size.y);

    if (l_Property != nullptr)
    {
        for (l_Property = l_Property->FirstChildElement("property"); (l_Property != nullptr) && (l_b_Ret == true); l_Property = l_Property->NextSiblingElement("property"))
        {
            l_b_Ret = mt_Load_Object_Property(*l_Property, l_Object);
        }
    }

    if (l_b_Ret == true)
    {
        object_layer.m_Objects.mt_Add_Element(l_Object, l_Object.m_Object_Id, l_Object.m_Object_Name);
    }

    return l_b_Ret;
}

bool MapLoader_Tiled_1_9::mt_Load_Object_Property(const TiXmlElement& property, MapData::Object& object)
{
    std::string l_Property_Name;
    std::string l_Property_Type;
    bool l_Bool_Value = false;
    int l_Int_Value = 0;
    float l_Float_Value = 0.0f;
    std::string l_String_Value;
    Color l_Color;

    if (property.QueryStringAttribute("name", &l_Property_Name) == TIXML_SUCCESS)
    {
        if (property.QueryStringAttribute("type", &l_Property_Type) == TIXML_SUCCESS)
        {
            if (l_Property_Type == "bool")
            {
                property.QueryBoolAttribute("value", &l_Bool_Value);
                object.m_Object_Properties_Bool.emplace(l_Property_Name, l_Bool_Value);
            }
            else if (l_Property_Type == "int")
            {
                property.QueryIntAttribute("value", &l_Int_Value);
                object.m_Object_Properties_Int.emplace(l_Property_Name, l_Int_Value);
            }
            else if (l_Property_Type == "float")
            {
                property.QueryFloatAttribute("value", &l_Float_Value);
                object.m_Object_Properties_Float.emplace(l_Property_Name, l_Float_Value);
            }
            else if (l_Property_Type == "color")
            {
                property.QueryStringAttribute("value", &l_String_Value);
                object.m_Object_Properties_Color.emplace(l_Property_Name, l_Color);
            }
        }
        else
        {
            property.QueryStringAttribute("value", &l_String_Value);
            object.m_Object_Properties_String.emplace(l_Property_Name, l_String_Value);
        }

        return true;
    }

    return false;
}

}
