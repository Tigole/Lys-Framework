#include <gtest/gtest.h>

#include <cstdint>
#include <lys-module-random.hpp>

TEST(Random, _)
{
    lys::RandomEngine engine;
    uint32_t seed = 0;

    engine.Set_Seed(10);
    EXPECT_EQ(engine.Get_Seed(), 10);

    const int r = engine.Generate_Int();
    EXPECT_NE(engine.Get_Seed(), 10);

    engine.Set_Seed(10);
    EXPECT_EQ(engine.Generate_Int(), r);
}
