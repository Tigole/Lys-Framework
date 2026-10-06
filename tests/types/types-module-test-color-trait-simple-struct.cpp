#include <gtest/gtest.h>

#include "lys-types/lys-color-traits.hpp"
#include "lys-types/lys-color.hpp"

TEST(Color, _)
{
    const lys::Color c = lys::ColorTraits<lys::Color>::Construct(1, 2, 3, 4);

    EXPECT_EQ(c.r, 1);
    EXPECT_EQ(c.g, 2);
    EXPECT_EQ(c.b, 3);
    EXPECT_EQ(c.a, 4);
    EXPECT_EQ(lys::ColorTraits<lys::Color>::r(c), 1);
    EXPECT_EQ(lys::ColorTraits<lys::Color>::g(c), 2);
    EXPECT_EQ(lys::ColorTraits<lys::Color>::b(c), 3);
    EXPECT_EQ(lys::ColorTraits<lys::Color>::a(c), 4);

    const lys::Color fromString = lys::ColorTraits<lys::Color>::ParseWebColor("#dd7755");
    EXPECT_EQ(fromString.r, 0xdd);
    EXPECT_EQ(fromString.g, 0x77);
    EXPECT_EQ(fromString.b, 0x55);
    EXPECT_EQ(fromString.a, 0xff);

    const lys::Color fromStringAlpha = lys::ColorTraits<lys::Color>::ParseWebColor("#dd775566");
    EXPECT_EQ(fromStringAlpha.r, 0xdd);
    EXPECT_EQ(fromStringAlpha.g, 0x77);
    EXPECT_EQ(fromStringAlpha.b, 0x55);
    EXPECT_EQ(fromStringAlpha.a, 0x66);

    char buffer[8];
    lys::ColorTraits<lys::Color>::ToWebColor(c, buffer);
    EXPECT_EQ(buffer[0], '#');
    EXPECT_EQ(buffer[1], '0');
    EXPECT_EQ(buffer[2], '1');
    EXPECT_EQ(buffer[3], '0');
    EXPECT_EQ(buffer[4], '2');
    EXPECT_EQ(buffer[5], '0');
    EXPECT_EQ(buffer[6], '3');
    EXPECT_EQ(buffer[7], '\0');

    char bufferAlpha[10];
    lys::ColorTraits<lys::Color>::ToWebColorAlpha(c, bufferAlpha);
    EXPECT_EQ(bufferAlpha[0], '#');
    EXPECT_EQ(bufferAlpha[1], '0');
    EXPECT_EQ(bufferAlpha[2], '1');
    EXPECT_EQ(bufferAlpha[3], '0');
    EXPECT_EQ(bufferAlpha[4], '2');
    EXPECT_EQ(bufferAlpha[5], '0');
    EXPECT_EQ(bufferAlpha[6], '3');
    EXPECT_EQ(bufferAlpha[7], '0');
    EXPECT_EQ(bufferAlpha[8], '4');
    EXPECT_EQ(bufferAlpha[9], '\0');
}
