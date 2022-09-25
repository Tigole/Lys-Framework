#include "Lys/Core/Array2D.hpp"

namespace lys
{


Index2D::Index2D(){}
Index2D::Index2D(std::size_t x, std::size_t y) : xx(x), yy(y) {}

bool operator<(const Index2D& a, const Index2D& b)
{
    if (a.xx < b.xx)
    {
        return true;
    }
    if (a.xx == b.xx)
    {
        return a.yy < b.yy;
    }
    return false;
}


}
