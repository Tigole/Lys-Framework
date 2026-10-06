#include <lys-tiled-map-loading/lys-map-loader-tiled-1.9.hpp>
#include <lys-tiled-map-loading/lys-map-loader-tiled.hpp>

#ifndef LYS_LOG_CORE_ERROR
#define LYS_LOG_CORE_ERROR(...)
#endif

namespace lys
{

template<typename __Vec2i>
template<typename ___Vec2f, typename ___Vec2u, typename ___Color>
bool __MapLoaderTiled<__Vec2i>::Load_Map(const char* file_path, __MapData<___Vec2f, ___Vec2u, ___Color>& map_data,
                                         std::unique_ptr<__MapLayout<___Vec2f, __Vec2i>>& map_layout)
{
    XML_Loader l_Loader;
    TiledHeader l_Tiled_Header;

    l_Loader.Add_On_Entry_Callback("/map", [&](const XML_Element& map)
    {
        if (map.Get_XML_Attribute("infinite", l_Tiled_Header.m_Is_Infinite) == false)
        {
            return false;
        }
        if (map.Get_XML_Attribute("version", l_Tiled_Header.m_Version) == false)
        {
            return false;
        }
        if (map.Get_XML_Attribute("tiledversion", l_Tiled_Header.m_Tiled_Version) == false)
        {
            return false;
        }
        if (map.Get_XML_Attribute("orientation", l_Tiled_Header.m_Orientation) == false)
        {
            return false;
        }
        if (map.Get_XML_Attribute("width", l_Tiled_Header.m_Map_Dimension.x) == false)
        {
            return false;
        }
        if (map.Get_XML_Attribute("height", l_Tiled_Header.m_Map_Dimension.y) == false)
        {
            return false;
        }
        if (map.Get_XML_Attribute("tilewidth", l_Tiled_Header.m_Tile_Dimension.x) == false)
        {
            return false;
        }
        if (map.Get_XML_Attribute("tileheight", l_Tiled_Header.m_Tile_Dimension.y) == false)
        {
            return false;
        }

        return true;
    });

    if (l_Loader.Load_From_File(file_path) == false)
    {
        return false;
    }

    if (l_Tiled_Header.m_Version == "1.9")
    {
        __MapLoaderTiled_1_9<___Vec2f, ___Vec2u, ___Color> l_Map_Loader;

        map_data.m_Tiles_Layers.mt_Clear();
        map_data.m_Objects_Layers.mt_Clear();

        return l_Map_Loader.template Load<___Vec2f, __Vec2i>(file_path, map_data, map_layout);
    }

    LYS_LOG_CORE_ERROR("Tiled version not handled: '%s'", l_Tiled_Header.m_Version.c_str());

    return false;
}

}  // namespace lys
