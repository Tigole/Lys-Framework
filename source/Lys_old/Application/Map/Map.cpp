#include "Lys/Application/Map/Map.hpp"

namespace lys
{






GridSettings::GridSettings(const Vector2f& cell_size) :
    m_Cell_Size_Pix(cell_size)
{}

GridSettings::~GridSettings()
{}

Vector2f GridSettings::mt_Get_Cell_Size_Pix(void) const
{
    return m_Cell_Size_Pix;
}


GridSettings_Square::GridSettings_Square(const Vector2f& cell_size) : GridSettings(cell_size)
{}

Vector2f GridSettings_Square::mt_Pix_To_Coord(const Vector2f& pix) const
{
    return Vector2f(pix / m_Cell_Size_Pix);
}

Vector2f GridSettings_Square::mt_Coord_To_Pix(const Vector2f& coord) const
{
    return Vector2f(coord * m_Cell_Size_Pix);
}

float GridSettings_Square::mt_Coord_Radius_To_Pix(float coord_radius) const
{
    return coord_radius * std::min(m_Cell_Size_Pix.x, m_Cell_Size_Pix.y);
}







void MapGrid2D::mt_Set_Grid_Settings(GridSettings* settings)
{
    m_Grid_Settings.reset(settings);
}

Vector2f MapGrid2D::mt_Pix_To_Coord(const Vector2f& pix) const
{
    return m_Grid_Settings->mt_Pix_To_Coord(pix);
}

Vector2f MapGrid2D::mt_Coord_To_Pix(const Vector2f& coord) const
{
    return m_Grid_Settings->mt_Coord_To_Pix(coord);
}

float MapGrid2D::mt_Coord_Radius_To_Pix(float coord_radius) const
{
    return m_Grid_Settings->mt_Coord_Radius_To_Pix(coord_radius);
}

Vector2f MapGrid2D::mt_Get_Cell_Size_Pix(void) const
{
    return m_Grid_Settings->mt_Get_Cell_Size_Pix();
}

float MapGrid2D::mt_Get_Distance_Pix(const Vector2f& aa, const Vector2f& bb)
{
    return Vector2f(aa - bb).mt_Get_Length();
}

float MapGrid2D::mt_Get_Distance_Coord(const Vector2f& aa, const Vector2f& bb)
{
    return Vector2f(aa - bb).mt_Get_Length();
}


void MapGrid2D::mt_Set_Layer(std::size_t layer_id, LayerData* layer_data)
{
    m_Layers.emplace(layer_id, std::unique_ptr<LayerData>(layer_data));
}

void MapGrid2D::mt_Clear_Layer(std::size_t layer_id)
{
    m_Layers.erase(layer_id);
}

void MapGrid2D::mt_Draw_Layer(std::size_t layer_id)
{
    auto l_it = m_Layers.find(layer_id);

    if (l_it != m_Layers.end())
    {
        Renderer::smt_Get().mt_Draw_VertexArray(l_it->second->m_VA, l_it->second->m_Texture);
    }
}


}
