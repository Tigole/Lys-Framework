#include <gtest/gtest.h>

#include "lys-types/lys-color-traits.hpp"
#include "lys-types/lys-color.hpp"

TEST(Color, _)
{
    lys::Color c = lys::ColorTraits<lys::Color>::Construct(1, 2, 3, 4);

    EXPECT_EQ(c.r, 1);
    EXPECT_EQ(c.g, 2);
    EXPECT_EQ(c.b, 3);
    EXPECT_EQ(c.a, 4);
    EXPECT_EQ(lys::ColorTraits<lys::Color>::r(c), 1);
    EXPECT_EQ(lys::ColorTraits<lys::Color>::g(c), 2);
    EXPECT_EQ(lys::ColorTraits<lys::Color>::b(c), 3);
    EXPECT_EQ(lys::ColorTraits<lys::Color>::a(c), 4);
}
