#include "Lys/MathModule/HexGrid.hpp"

namespace lys
{

namespace hex
{

namespace priv
{

const Hex gs_Directions[6] =
{
    Hex(1, 0, -1), Hex(1, -1, 0), Hex(0, -1, 1),
    Hex(-1, 0, 1), Hex(-1, 1, 0), Hex(0, 1, -1)
};

}

namespace orient
{

const Orientation gs_PointyTop{
                                {std::sqrt(3.0f), std::sqrt(3.0f) / 2.0f, 0.0f, 3.0f / 2.0f},
                                {std::sqrt(3.0f) / 3.0f, -1.0f / 3.0f, 0.0f, 2.0f / 3.0f},
                                0.5f};
}



Point fn_Hex_To_Pixel(const Layout& ll, const Hex& hh, float& xx, float& yy)
{
    const orient::Orientation& oo = orient::gs_PointyTop;

    xx = (oo.f[0][0] * hh.q + oo.f[0][1] * hh.r) * ll.size.xx + ll.origin.xx;
    yy = (oo.f[1][0] * hh.q + oo.f[1][1] * hh.r) * ll.size.yy + ll.origin.yy;

    return Point(xx, yy);
}

Point fn_Hex_To_Pixel(const Layout& ll, const Hex& hh)
{
    float xx;
    float yy;
    return fn_Hex_To_Pixel(ll, hh, xx, yy);
}

Hex fn_Round(float fq, float fr, float fs)
{
    int qq = std::round(fq);
    int rr = std::round(fr);
    int ss = std::round(fs);
    float q_diff = std::abs(qq - fq);
    float r_diff = std::abs(rr - fr);
    float s_diff = std::abs(ss - fs);
    if ((q_diff > r_diff) && (q_diff > s_diff))
    {
        qq = -rr -ss;
    }
    else if (r_diff > s_diff)
    {
        rr = -qq -ss;
    }
    else
    {
        ss = -qq -rr;
    }
    return Hex(qq, rr, ss);
}

Hex fn_Pixel_To_Hex(const Layout& ll, const Point& p)
{
    const orient::Orientation& oo = orient::gs_PointyTop;
    Point pp((p.xx - ll.origin.xx) / ll.size.xx, (p.yy - ll.origin.yy) / ll.size.yy);
    float fq = oo.b[0][0] * pp.xx + oo.b[0][1] * pp.yy;
    float fr = oo.b[1][0] * pp.xx + oo.b[1][1] * pp.yy;
    float fs = - fq - fr;

    return fn_Round(fq, fr, fs);
}

std::vector<Hex> fn_Line(const Hex& aa, const Hex& bb, int distance_limit)
{
    auto l_fn_Lerp = [](float a, float b, float tt)
    {
        return a + (b - a) * tt;
    };
    int l_Hex_Count = fn_Distance(aa, bb);
    std::vector<Hex> l_Ret;
    float l_Step = 1.0f / std::max(1, l_Hex_Count);

    if (distance_limit <= 0)
    {
        distance_limit = INT_MAX;
    }

    for (int ii = 0; ii <= std::min(l_Hex_Count, distance_limit); ii++)
    {
        l_Ret.push_back(fn_Round(l_fn_Lerp(aa.q, bb.q, l_Step * ii),
                                 l_fn_Lerp(aa.r, bb.r, l_Step * ii),
                                 l_fn_Lerp(aa.s, bb.s, l_Step * ii)));
    }

    return l_Ret;
}

}

}
