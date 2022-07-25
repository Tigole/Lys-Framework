#ifndef _LYS_MAP_HPP
#define _LYS_MAP_HPP 1

#include "Lys/MathModule/Vector2.hpp"
#include "Lys/LysGraphics.hpp"

#include <map>
#include <memory>
#include <string>

namespace lys
{





class LYS_API GridSettings
{
public:
    GridSettings(const Vector2f& cell_size);
    virtual ~GridSettings();

    virtual Vector2f mt_Pix_To_Coord(const Vector2f& pix) const = 0;
    virtual Vector2f mt_Coord_To_Pix(const Vector2f& coord) const = 0;
    virtual float mt_Coord_Radius_To_Pix(float coord_radius) const = 0;

    Vector2f mt_Get_Cell_Size_Pix(void) const;

protected:
    Vector2f m_Cell_Size_Pix;
};

class LYS_API GridSettings_Square : public GridSettings
{
public:
    GridSettings_Square(const Vector2f& cell_size);

    Vector2f mt_Pix_To_Coord(const Vector2f& pix) const override;
    Vector2f mt_Coord_To_Pix(const Vector2f& coord) const override;
    float mt_Coord_Radius_To_Pix(float coord_radius) const override;
};


class LYS_API MapGrid2D
{
public:

    struct LayerData
    {
        VertexArray m_VA;
        const Texture* m_Texture;
    };

    void mt_Set_Grid_Settings(GridSettings* settings);

    Vector2f mt_Pix_To_Coord(const Vector2f& pix)const;
    Vector2f mt_Coord_To_Pix(const Vector2f& coord) const;
    float mt_Coord_Radius_To_Pix(float coord_radius) const;

    Vector2f mt_Get_Cell_Size_Pix(void) const;

    float mt_Get_Distance_Pix(const Vector2f& aa, const Vector2f& bb);
    float mt_Get_Distance_Coord(const Vector2f& aa, const Vector2f& bb);

    void mt_Set_Layer(std::size_t layer_id, LayerData* layer_data);
    void mt_Clear_Layer(std::size_t layer_id);
    void mt_Draw_Layer(std::size_t layer_id);

private:

    /*struct MapChunkDescription
    {
        std::string m_Texture_Id;
        Vector2f m_Pos;
        Vector2f m_Dim;
        float m_Rotation;
    };*/

    /*struct TileChunkDescription
    {
        Vector2f m_Posf;
        Vector2i m_Posi;
        int m_Tile_Index;
    };*/


    //std::map<std::string, std::unique_ptr<GeneratedTileset>> m_Generated_Tilesets;
    std::map<std::size_t, std::unique_ptr<LayerData>> m_Layers;

    std::unique_ptr<GridSettings> m_Grid_Settings;



};


}


#endif // _LYS_MAP_HPP
