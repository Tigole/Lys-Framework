#include <gtest/gtest.h>

#include <lys-module-window-inputs.hpp>

TEST(WindowInputs_SFML, Close_Request)
{
    EXPECT_FALSE(lys::Inputs::Is_Close_Requested());
    lys::Inputs::On_SFML_Close_Request();
    EXPECT_TRUE(lys::Inputs::Is_Close_Requested());
    lys::Inputs::Refresh();
    EXPECT_FALSE(lys::Inputs::Is_Close_Requested());
}

TEST(WindowInputs_SFML, Text_Entered)
{
    uint32_t unicode;
    EXPECT_FALSE(lys::Inputs::Extract_Text(unicode));

    lys::Inputs::On_SFML_Text({ 0 });
    EXPECT_TRUE(lys::Inputs::Extract_Text(unicode));
    EXPECT_EQ(unicode, 0);
    lys::Inputs::Refresh();

    lys::Inputs::On_SFML_Text({ 1 });
    lys::Inputs::On_SFML_Text({ 2 });
    lys::Inputs::On_SFML_Text({ 3 });
    lys::Inputs::On_SFML_Text({ 4 });
    lys::Inputs::On_SFML_Text({ 5 });
    lys::Inputs::On_SFML_Text({ 6 });
    lys::Inputs::On_SFML_Text({ 7 });
    lys::Inputs::On_SFML_Text({ 8 });
    lys::Inputs::On_SFML_Text({ 9 });
    lys::Inputs::On_SFML_Text({ 10 });
    lys::Inputs::On_SFML_Text({ 11 });
    lys::Inputs::On_SFML_Text({ 12 });
    lys::Inputs::On_SFML_Text({ 13 });
    lys::Inputs::On_SFML_Text({ 14 });
    lys::Inputs::On_SFML_Text({ 15 });
    lys::Inputs::On_SFML_Text({ 16 });

    EXPECT_TRUE(lys::Inputs::Extract_Text(unicode));
    EXPECT_EQ(unicode, 1);
    EXPECT_TRUE(lys::Inputs::Extract_Text(unicode));
    EXPECT_EQ(unicode, 2);
    EXPECT_TRUE(lys::Inputs::Extract_Text(unicode));
    EXPECT_EQ(unicode, 3);
    EXPECT_TRUE(lys::Inputs::Extract_Text(unicode));
    EXPECT_EQ(unicode, 4);
    EXPECT_TRUE(lys::Inputs::Extract_Text(unicode));
    EXPECT_EQ(unicode, 5);
    EXPECT_TRUE(lys::Inputs::Extract_Text(unicode));
    EXPECT_EQ(unicode, 6);
    EXPECT_TRUE(lys::Inputs::Extract_Text(unicode));
    EXPECT_EQ(unicode, 7);
    EXPECT_TRUE(lys::Inputs::Extract_Text(unicode));
    EXPECT_EQ(unicode, 8);
    EXPECT_TRUE(lys::Inputs::Extract_Text(unicode));
    EXPECT_EQ(unicode, 9);
    EXPECT_TRUE(lys::Inputs::Extract_Text(unicode));
    EXPECT_EQ(unicode, 10);
    EXPECT_TRUE(lys::Inputs::Extract_Text(unicode));
    EXPECT_EQ(unicode, 11);
    EXPECT_TRUE(lys::Inputs::Extract_Text(unicode));
    EXPECT_EQ(unicode, 12);
    EXPECT_TRUE(lys::Inputs::Extract_Text(unicode));
    EXPECT_EQ(unicode, 13);
    EXPECT_TRUE(lys::Inputs::Extract_Text(unicode));
    EXPECT_EQ(unicode, 14);
    EXPECT_TRUE(lys::Inputs::Extract_Text(unicode));
    EXPECT_EQ(unicode, 15);
    EXPECT_FALSE(lys::Inputs::Extract_Text(unicode));
    EXPECT_EQ(unicode, 15);

    lys::Inputs::Refresh();
    lys::Inputs::On_SFML_Text({ 16 });
    EXPECT_TRUE(lys::Inputs::Extract_Text(unicode));
    EXPECT_EQ(unicode, 16);
}
