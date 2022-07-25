#ifndef _GRID_HPP
#define _GRID_HPP 1

#include "Lys/LysConfig.hpp"
#include "glm/glm.hpp"
#include <vector>

namespace lys
{


struct CubeCoord;
struct AxialCoord;

enum class OffsetCoordType
{
    odd_r,
};

enum class HexTileMode
{
    Flat_Top,
    Pointy_Top,

    Count
};

struct LYS_API AxialCoord
{
    AxialCoord() : q(0), r(0) {}
    AxialCoord(int _q, int _r) : q(_q), r(_r){}
    int q, r;

    CubeCoord mt_To_Cube(void) const;
};

inline bool LYS_API operator==(const AxialCoord& a, const AxialCoord& b)
{
    return ((a.q == b.q) && (a.r == b.r));
}

inline AxialCoord LYS_API operator+(const AxialCoord& a, const AxialCoord& b)
{
    return AxialCoord(a.q + b.q, a.r + b.r);
}

inline AxialCoord LYS_API operator-(const AxialCoord& a, const AxialCoord& b)
{
    return AxialCoord(a.q - b.q, a.r - b.r);
}

struct LYS_API CubeCoord
{
    CubeCoord() : x(0), y(0), z(0) {}
    CubeCoord(int _x, int _y, int _z) : x(_x), y(_y), z(_z)
    {
        assert((x+y+z) == 0);
    }
    int x, y, z;

    AxialCoord mt_To_Axial(void) const
    {
        return AxialCoord(x, z);
    }

    int mt_Distance(const CubeCoord& c) const
    {
        return (std::abs(x - c.x) + std::abs(y - c.y) + std::abs(z - c.z))/2;
    }
};

class LYS_API HexTile
{
public:
    HexTile()
    {
        mt_Set(AxialCoord(0, 0));
    }
    HexTile(int q, int r)
    {
        mt_Set(AxialCoord(q, r));
    }
    explicit HexTile(const AxialCoord& a)
    {
        mt_Set(a);
    }
    HexTile(int x, int y, int z)
    {
        mt_Set(CubeCoord(x, y, z).mt_To_Axial());
    }
    explicit HexTile(const CubeCoord& c)
    {
        mt_Set(c.mt_To_Axial());
    }

    void mt_Set(const AxialCoord& a)
    {
        m_Coords = a;
    }
    void mt_Set(const CubeCoord& c)
    {
        m_Coords = c.mt_To_Axial();
    }

    CubeCoord mt_Get_Cube(void) const
    {
        return m_Coords.mt_To_Cube();
    }

    AxialCoord mt_Get_Axial(void) const
    {
        return m_Coords;
    }

    int mt_Lenght(void) const
    {
        return 0;
    }

    int mt_Distance(const HexTile& h) const
    {
        return m_Coords.mt_To_Cube().mt_Distance(h.mt_Get_Cube());
    }

    std::vector<HexTile> mt_Neighbours(void) const
    {
        std::vector<HexTile> l_Ret =
        {
            HexTile(m_Coords - AxialCoord(1, 0)),
            HexTile(m_Coords - AxialCoord(1, -1)),
            HexTile(m_Coords - AxialCoord(0, -1)),
            HexTile(m_Coords - AxialCoord(-1, 0)),
            HexTile(m_Coords - AxialCoord(-1, 1)),
            HexTile(m_Coords - AxialCoord(0, 1)),
        };

        return l_Ret;
    }

    glm::vec2 mt_To_Pixel() const
    {
        glm::vec2 l_Ret;

        l_Ret = sm_Hex_To_Pixel_Flat * glm::vec2(m_Coords.q, m_Coords.r);

        return l_Ret;
    }

    static HexTile smt_From_Pixel(const glm::vec2& px, HexTileMode htm)
    {
        glm::vec2 l_qr;
        glm::vec3 l_Cube;
        glm::vec3 l_Round_Cube;
        glm::vec3 l_Diff;

        l_qr = sm_Pixel_To_Hex_Flat * px;

        l_Cube.x = l_qr.x;
        l_Cube.y = -l_qr.x-l_qr.y;
        l_Cube.z = l_qr.y;

        l_Round_Cube.x = std::round(l_Cube.x);
        l_Round_Cube.y = std::round(l_Cube.y);
        l_Round_Cube.z = std::round(l_Cube.z);

        l_Diff = glm::abs(l_Round_Cube - l_Cube);

        if ((l_Diff.x > l_Diff.y) && (l_Diff.x > l_Diff.y))
        {
            l_Round_Cube.x = -l_Round_Cube.y - l_Round_Cube.z;
        }
        else if (l_Diff.y > l_Diff.z)
        {
            l_Round_Cube.y = -l_Round_Cube.x - l_Round_Cube.z;
        }
        else
        {
            l_Round_Cube.z = -l_Round_Cube.x - l_Round_Cube.y;
        }

        return HexTile(l_Round_Cube.x, l_Round_Cube.y, l_Round_Cube.z);
    }

    static glm::vec3 smt_Pixel_To_Hex(glm::vec3 pos, HexTileMode htm)
    {
        HexTile l_Hex = smt_From_Pixel(glm::vec2(pos.x, pos.z), htm);

        pos.x = l_Hex.m_Coords.q;
        pos.z = l_Hex.m_Coords.r;

        return pos;
    }

private:
    AxialCoord m_Coords;
    static const glm::mat2 sm_Hex_To_Pixel_Pointy;
    static const glm::mat2 sm_Hex_To_Pixel_Flat;
    static const glm::mat2 sm_Pixel_To_Hex_Pointy;
    static const glm::mat2 sm_Pixel_To_Hex_Flat;
};

inline bool LYS_API operator==(const HexTile& a, const HexTile& b)
{
    return a.mt_Get_Axial() == b.mt_Get_Axial();
}

inline bool LYS_API operator!=(const HexTile& a, const HexTile& b)
{
    return !(a == b);
}

inline bool LYS_API operator<(const HexTile& a, const HexTile& b)
{
    if (a.mt_Get_Axial().q < b.mt_Get_Axial().q)
        return true;
    return a.mt_Get_Axial().r < b.mt_Get_Axial().r;
}

inline HexTile LYS_API operator+(const HexTile& a, const HexTile& b)
{
    return HexTile(a.mt_Get_Axial() + b.mt_Get_Axial());
}

inline HexTile LYS_API operator-(const HexTile& a, const HexTile& b)
{
    return HexTile(a.mt_Get_Axial() - b.mt_Get_Axial());
}






namespace hex
{

enum class OffsetCoordMode
{
    Odd = -1,
    Even = 1,
};

enum class OffsetCoordType
{
    r,
    q
};

struct LYS_API Hex
{
    Hex(int qq, int rr, int ss) : q(qq), r(rr), s(ss) {assert((q + r + s) == 0);}
    Hex(int axial_q, int axial_r) : q(axial_q), r(axial_r), s(-axial_q - axial_r) {assert((q + r + s) == 0);}
    explicit Hex(const glm::ivec3 vec) : v(vec) {}

    union
    {
        glm::ivec3 v;
        struct {int q, r, s;};
    };
};

inline bool LYS_API operator==(const Hex& aa, const Hex& bb)
{
    return aa.q == bb.q && aa.r == bb.r && aa.s == bb.s;
}

inline bool LYS_API operator!=(const Hex& aa, const Hex& bb)
{
    return !(aa == bb);
}

inline Hex LYS_API operator+(const Hex& aa, const Hex& bb)
{
    return Hex(aa.v + bb.v);
}

inline Hex LYS_API operator-(const Hex& aa, const Hex& bb)
{
    return Hex(aa.v - bb.v);
}

inline Hex LYS_API operator*(const Hex& aa, int k)
{
    return Hex(aa.v * k);
}

inline int LYS_API fn_Length(const Hex& hh)
{
    return (std::abs(hh.q) + std::abs(hh.r) + std::abs(hh.s)) / 2;
}

inline int LYS_API fn_Distance(const Hex& aa, const Hex& bb)
{
    return fn_Length(aa - bb);
}

namespace priv
{
    LYS_API extern const Hex gs_Directions[6];
}

inline Hex LYS_API fn_Direction(int direction)
{
    assert(direction >= 0 && direction < 6);

    return priv::gs_Directions[direction];
}

inline Hex LYS_API fn_Neighbour(const Hex& hh, int direction)
{
    return hh + fn_Direction(direction);
}

namespace orient
{
    struct LYS_API Orientation
    {
        glm::mat2 f;
        glm::mat2 b;
        float start_angle;
    };

    LYS_API extern const Orientation gs_PointyTop/*{
                                            {std::sqrt(3.0f), std::sqrt(3.0f) / 2.0f, 0.0f, 3.0f / 2.0f},
                                            {std::sqrt(3.0f) / 3.0f, -1.0f / 3.0f, 0.0f, 2.0f / 3.0f},
                                            0.5f}*/;

}

struct LYS_API Point
{
    float xx, yy;

    Point(float x, float y)
    {
        xx = x;
        yy = y;
    }
};

struct LYS_API Layout
{
    HexTileMode mode;
    Point size;
    Point origin;

    Layout(HexTileMode _mode, const Point& _size, const Point& _origin) : mode(_mode), size(_size), origin(_origin) {}
    Layout(HexTileMode _mode, float sx, float sy, float ox, float oy) : mode(_mode), size(sx, sy), origin(ox, oy) {}
};

Point LYS_API fn_Hex_To_Pixel(const Layout& ll, const Hex& hh, float& xx, float& yy);

Point LYS_API fn_Hex_To_Pixel(const Layout& ll, const Hex& hh);

Hex LYS_API fn_Round(float fq, float fr, float fs);

Hex LYS_API fn_Pixel_To_Hex(const Layout& ll, const Point& p);

std::vector<Hex> LYS_API fn_Line(const Hex& aa, const Hex& bb, int distance_limit);

struct LYS_API OffsetCoord
{
    int col, row;
    inline int x(void) {return col;}
    inline int y(void) {return row;}
};

inline OffsetCoord LYS_API fn_To_Offset(OffsetCoordMode mode, OffsetCoordType type, const Hex& hh)
{
    OffsetCoord l_Ret;

    switch(type)
    {
    case OffsetCoordType::q:
        l_Ret.col = hh.q;
        l_Ret.row = hh.r + (hh.q + static_cast<int>(mode) * (hh.q & 1)) / 2;
        break;
    case OffsetCoordType::r:
        l_Ret.col = hh.q + (hh.r + static_cast<int>(mode) * (hh.r & 1)) / 2;
        l_Ret.row = hh.r;
        break;
    }
    return l_Ret;

}

inline Hex LYS_API fn_From_Offset(OffsetCoordMode mode, OffsetCoordType type, const OffsetCoord& offset)
{
    int q = 0;
    int r = 0;
    int s = 0;

    switch(type)
    {
    case OffsetCoordType::q:
        q = offset.col;
        r = offset.row - (offset.col + static_cast<int>(mode) * (offset.col & 1)) / 2;
        s = -q - r;
        break;
    case OffsetCoordType::r:
        q = offset.col - (offset.row + static_cast<int>(mode) * (offset.row & 1)) / 2;
        r = offset.row;
        s = -q -r;
        break;
    }

    return Hex(q, r, s);
}

inline Hex LYS_API fn_Rotate_Left(const Hex& hh)
{
    return Hex(-hh.s, -hh.q, -hh.r);
}

inline Hex LYS_API fn_Rotate_Right(const Hex& hh)
{
    return Hex(-hh.r, -hh.s, -hh.q);
}



}




}

#endif // _GRID_HPP
