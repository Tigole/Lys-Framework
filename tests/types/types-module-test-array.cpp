#include <gtest/gtest.h>

#include "lys-types/lys-array-2d.hpp"

TEST(Array2D, _)
{
    lys::Array2D<int> arr;

    EXPECT_EQ(arr.GetElementCount(), (std::size_t)0);
    EXPECT_EQ(arr.GetSizeX(), (std::size_t)0);
    EXPECT_EQ(arr.GetSizeY(), (std::size_t)0);
    EXPECT_EQ(arr.GetLength().x, (std::size_t)0);
    EXPECT_EQ(arr.GetLength().y, (std::size_t)0);

    arr.Resize(2, 1);
    EXPECT_EQ(arr.GetElementCount(), (std::size_t)2);
    EXPECT_EQ(arr.GetSizeX(), (std::size_t)2);
    EXPECT_EQ(arr.GetSizeY(), (std::size_t)1);
    EXPECT_EQ(arr.GetLength().x, (std::size_t)2);
    EXPECT_EQ(arr.GetLength().y, (std::size_t)1);
    EXPECT_EQ(arr.Get(0, 0), 0);
    EXPECT_EQ(arr.Get(1, 0), 0);

    arr.Get(0, 0) = 10;
    arr.Get(1, 0) = 20;
    EXPECT_EQ(arr.Get(0, 0), 10);
    EXPECT_EQ(arr(0, 0), 10);
    EXPECT_EQ(arr.Get(1, 0), 20);
    EXPECT_EQ(arr(1, 0), 20);

    arr.Resize(1, 2, 50);
    EXPECT_EQ(arr(0, 0), 50);
    EXPECT_EQ(arr(0, 1), 50);
}
