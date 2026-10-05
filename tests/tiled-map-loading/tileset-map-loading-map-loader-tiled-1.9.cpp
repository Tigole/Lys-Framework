#include "test.hpp"

TEST(MapLoaderTiled1_9, lys)
{
    lys::MapLoaderTiled_1_9 loader;
    lys::MapData data;
    std::unique_ptr<lys::MapLayout> layout;

    EXPECT_FALSE(loader.Load(std::filesystem::path(""), data, layout));
}

TEST(MapLoader1_9, other)
{
    lys::__MapLoaderTiled_1_9<Vf, Vu, C> loader;
}
