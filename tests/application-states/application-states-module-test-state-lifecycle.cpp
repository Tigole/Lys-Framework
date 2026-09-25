#include <gtest/gtest.h>

#include <lys-module-application-states.hpp>

std::vector<uint8_t> phases;

class State: public lys::ApplicationState
{
public:
    State() {}

    void On_Create(void)
    {
        phases.push_back(0);
    }

    void On_Destroy(void)
    {
        phases.push_back(3);
    }

    void On_Entry(void)
    {
        phases.push_back(1);
    }

    void On_Exit(void)
    {
        phases.push_back(2);
    }
};

TEST(ApplicationStateModule, StateLifeCycle)
{
    {
        lys::ApplicationStateManager applicationStateManager;

        applicationStateManager.Register_State<State>(0);

        applicationStateManager.Set_Initial_State<State>(0, nullptr);

        ASSERT_EQ(phases.size(), (std::size_t)1);
        EXPECT_EQ(phases[0], 0);
        applicationStateManager.On_Update_Logic();

        ASSERT_EQ(phases.size(), (std::size_t)2);
        EXPECT_EQ(phases[0], 0);
        EXPECT_EQ(phases[1], 1);
        applicationStateManager.On_Update_Render();

        ASSERT_EQ(phases.size(), (std::size_t)2);
        EXPECT_EQ(phases[0], 0);
        EXPECT_EQ(phases[1], 1);

        applicationStateManager.Clear();
        ASSERT_EQ(phases.size(), (std::size_t)4);
        EXPECT_EQ(phases[0], 0);
        EXPECT_EQ(phases[1], 1);
        EXPECT_EQ(phases[2], 2);
        EXPECT_EQ(phases[3], 3);
    }

    ASSERT_EQ(phases.size(), (std::size_t)4);
    EXPECT_EQ(phases[0], 0);
    EXPECT_EQ(phases[1], 1);
    EXPECT_EQ(phases[2], 2);
    EXPECT_EQ(phases[3], 3);
}
