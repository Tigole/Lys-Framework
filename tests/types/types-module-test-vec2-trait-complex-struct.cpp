#include <gtest/gtest.h>

#include <cstdint>

#include "lys-types/lys-vec2-traits.hpp"

struct ComplexVec2
{
    ComplexVec2(int xx, int yy) : x(xx), y(yy) {}
    int x;
    int y;
};

TEST(Vec2Traits, ComplexStruct)
{
    ComplexVec2 vec = lys::Vec2Traits<ComplexVec2>::Construct<int>(22, 34);

    EXPECT_EQ(vec.x, 22);
    EXPECT_EQ(vec.y, 34);
    EXPECT_EQ(lys::Vec2Traits<ComplexVec2>::x<int>(vec), 22);
    EXPECT_EQ(lys::Vec2Traits<ComplexVec2>::y<int>(vec), 34);

    lys::Vec2Traits<ComplexVec2>::x<int>(vec) = 4;
    EXPECT_EQ(vec.x, 4);
    EXPECT_EQ(lys::Vec2Traits<ComplexVec2>::x<int>(vec), 4);

    lys::Vec2Traits<ComplexVec2>::y<int>(vec) = 56;
    EXPECT_EQ(vec.y, 56);
    EXPECT_EQ(lys::Vec2Traits<ComplexVec2>::y<int>(vec), 56);
}
