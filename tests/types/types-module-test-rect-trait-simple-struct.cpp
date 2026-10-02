#include <gtest/gtest.h>

#include "lys-types/lys-rect-traits.hpp"
#include "lys-types/lys-rect.hpp"

TEST(RectTraits, SimpleStruct)
{
    lys::Rect<int> r0 = lys::RectTraits<lys::Rect<int>>::Construct<int>(0, 1, 2, 3);

    EXPECT_EQ(r0.x, 0);
    EXPECT_EQ(r0.y, 1);
    EXPECT_EQ(r0.width, 2);
    EXPECT_EQ(r0.height, 3);
    EXPECT_EQ(lys::RectTraits<lys::Rect<int>>::x<int>(r0), 0);
    EXPECT_EQ(lys::RectTraits<lys::Rect<int>>::y<int>(r0), 1);
    EXPECT_EQ(lys::RectTraits<lys::Rect<int>>::width<int>(r0), 2);
    EXPECT_EQ(lys::RectTraits<lys::Rect<int>>::height<int>(r0), 3);
}

TEST(RectTraits, LeftRightTopBottom)
{
    lys::Rect<int> r0 = lys::RectTraits<lys::Rect<int>>::Construct<int>(0, 1, -2, -5);

    EXPECT_EQ(r0.x, 0);
    EXPECT_EQ(r0.y, 1);
    EXPECT_EQ(r0.width, -2);
    EXPECT_EQ(r0.height, -5);
    EXPECT_EQ(lys::RectExTraits<lys::Rect<int>>::left<int>(r0), -2);
    EXPECT_EQ(lys::RectExTraits<lys::Rect<int>>::right<int>(r0), 0);
    EXPECT_EQ(lys::RectExTraits<lys::Rect<int>>::top<int>(r0), -4);
    EXPECT_EQ(lys::RectExTraits<lys::Rect<int>>::bottom<int>(r0), 1);
}

TEST(RectTraits, Overlap)
{
    using Rect               = lys::Rect<int>;
    Rect r1                  = lys::RectTraits<Rect>::Construct<int>(0, 0, 4, 4);
    Rect r2                  = lys::RectTraits<Rect>::Construct<int>(3, 1, 2, 6);
    Rect overlap             = {};
    const bool isOverlapping = lys::RectExTraits<Rect>::Overlaps<int>(r1, r2, &overlap);

    EXPECT_EQ(isOverlapping, true);
    EXPECT_EQ(overlap.x, 3);
    EXPECT_EQ(overlap.y, 1);
    EXPECT_EQ(overlap.width, 1);
    EXPECT_EQ(overlap.height, 3);
    EXPECT_EQ(lys::RectExTraits<Rect>::Overlaps<int>(r2, r1, nullptr), true);
}

TEST(RectTraits, Contains)
{
    using Rect = lys::Rect<int>;
    Rect r1    = lys::RectTraits<Rect>::Construct<int>(0, 0, 4, 4);
    Rect r2    = lys::RectTraits<Rect>::Construct<int>(1, 1, 2, 2);

    EXPECT_EQ(lys::RectExTraits<Rect>::Contains<int>(r1, r1), true);
    EXPECT_EQ(lys::RectExTraits<Rect>::Contains<int>(r1, r2), true);
    EXPECT_EQ(lys::RectExTraits<Rect>::Contains<int>(r2, r1), false);
}
