#include <gtest/gtest.h>

#include <cstdint>
#include <lys-module-working-thread.hpp>

TEST(WorkingThreadModule, Stop)
{
    class TestTask
    {
    public:
        bool Callback(uint8_t& data)
        {
            data = 1;
            return true;
        }
    };
    uint8_t msg  = 0;
    int tryCount = 0;
    TestTask test;
    lys::WorkingThread wt;
    lys::WorkingTask<uint8_t> task("test task", &TestTask::Callback, &test);

    task.Push_Order(msg, wt);

    while ((task.Pop_Result(msg) == false) && (tryCount < 10))
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    EXPECT_LT(tryCount, 10);
    ASSERT_EQ(msg, 1);
}
