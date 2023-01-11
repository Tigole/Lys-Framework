#ifndef _LYS_MAP_LOADER_HPP
#define _LYS_MAP_LOADER_HPP 1

#include <string>
#include <map>
#include <functional>

#include "Lys/Core/Color.hpp"
#include "Lys/MathModule/Vector2.hpp"
#include "Lys/Application/Map/Tileset.hpp"
#include "Lys/Core/Array2D.hpp"
#include "Lys/Core/FileManagement.hpp"

class XML_Element;


template<typename ElementType>
class MultiKeyContainer
{
public:

    void mt_Add_Element(const ElementType& element, uint32_t element_id, const std::string& element_name);
    void mt_Clear(void);

    const ElementType* mt_Get_Element_By_Name(const std::string& element_name) const;
    const ElementType* mt_Get_Element_By_Id(uint32_t element_id) const;

private:
    std::vector<ElementType> m_Elements;
    std::map<uint32_t, std::size_t> m_Elements_Id_Map;
    std::map<std::string, std::size_t> m_Elements_Name_Map;
};

template<typename ElementType>
void MultiKeyContainer<ElementType>::mt_Add_Element(const ElementType& element, uint32_t element_id, const std::string& element_name)
{
    m_Elements_Id_Map.emplace(element_id, m_Elements.size());
    if (element_name.size() > 0)
    {
        m_Elements_Name_Map.emplace(element_name, m_Elements.size());
    }
    m_Elements.push_back(element);
}

template<typename ElementType>
void MultiKeyContainer<ElementType>::mt_Clear(void)
{
    m_Elements.clear();
    m_Elements_Id_Map.clear();
    m_Elements_Name_Map.clear();
}

template<typename ElementType>
const ElementType*  MultiKeyContainer<ElementType>::mt_Get_Element_By_Name(const std::string& element_name) const
{
    auto l_It = m_Elements_Name_Map.find(element_name);

    if (l_It != m_Elements_Name_Map.end())
    {
        return &m_Elements[l_It->second];
    }

    return nullptr;
}

template<typename ElementType>
const ElementType* MultiKeyContainer<ElementType>::mt_Get_Element_By_Id(uint32_t element_id) const
{
    auto l_It = m_Elements_Id_Map.find(element_id);

    if (l_It != m_Elements_Id_Map.end())
    {
        return &m_Elements[l_It->second];
    }

    return nullptr;
}












namespace lys
{

struct LYS_API MapData
{
    struct Object
    {
        uint32_t m_Object_Id;
        std::string m_Object_Name;
        std::string m_Object_Class;
        Vector2f m_Object_Pix_Pos;
        Vector2f m_Object_Pix_Size;

        std::map<std::string, bool> m_Object_Properties_Bool;
        std::map<std::string, int> m_Object_Properties_Int;
        std::map<std::string, float> m_Object_Properties_Float;
        std::map<std::string, Color> m_Object_Properties_Color;
        std::map<std::string, std::string> m_Object_Properties_String;
        std::map<std::string, std::string> m_Object_Properties_File;
    };

    struct ObjectLayer
    {
        uint32_t m_Object_Layer_Id;
        std::string m_Object_Layer_Name;
        MultiKeyContainer<Object> m_Objects;
    };

    struct TileLayer
    {
        uint32_t m_Tile_Layer_Id;
        std::string m_Tile_Layer_Name;
        Vector2u m_Tile_Layer_Size;
        Array2D<uint32_t> m_Tiles;
    };

    struct TilesetData
    {
        uint32_t m_First_Gid;
        TilesetInfo m_Tileset_Info;
    };

    MultiKeyContainer<TileLayer> m_Tiles_Layers;
    MultiKeyContainer<ObjectLayer> m_Objects_Layers;
    std::vector<TilesetData> m_Tileset_Data;
};

class LYS_API MapLoader
{
public:

    bool mt_Load_Map(const File& file_path, MapData& map_data);

private:

    struct TiledHeader
    {
        std::string m_Version;
        std::string m_Tiled_Version;
        std::string m_Orientation;
        Vector2i m_Map_Dimension;
        Vector2i m_Tile_Dimension;
        bool m_Is_Infinite;
    };
};




class LYS_API MapLoader_Tiled_1_9
{
public:

    bool mt_Load(const File& file_path, MapData& map_data);

private:

    bool mt_Load_Layer(const XML_Element& layer);
    bool mt_Load_Layer_Data(const XML_Element& data);
    bool mt_Load_Layer_Data_CSV(const char* csv_encoded_data);

    bool mt_Load_Object(const XML_Element& object);
    bool mt_Load_Object_Property(const XML_Element& property);

    bool mt_Load_Tileset(const File& file_path, MapData::TilesetData& tileset_data);

    MapData::TileLayer m_Tile_Layer;
    MapData::ObjectLayer m_Object_Layer;
    MapData::Object m_Object;
};


}

#endif // _LYS_MAP_LOADER_HPP
