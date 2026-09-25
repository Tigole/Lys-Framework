#include <gtest/gtest.h>

#include <cstdint>
#include <lys-module-working-thread.hpp>

TEST(WorkingThreadModule, NullTask)
{
    lys::WorkingThread wt;
    EXPECT_NO_THROW(wt.Add_Task(nullptr));
    EXPECT_NO_THROW(std::this_thread::sleep_for(std::chrono::milliseconds(300)));
}
