#include <gtest/gtest.h>

#include <cstdint>
#include <lys-module-log.hpp>

constexpr const char* token = "TEST";

class TestSink: public lys::log::Sink
{
public:
    void Log(const lys::log::LogData& d) override
    {
        data.push_back(d);
    }

    std::vector<lys::log::LogData> data;
};

TEST(LogModule, _)
{
    TestSink* sink = new TestSink;

    lys::log::LoggerPool::Get_Singleton().Get_Logger(token).Add_Sink(sink).Set_Level(lys::log::LogLevel::Trace);
    LYS_LOG_TRACE(token, "Trace");

    EXPECT_EQ(sink->data.size(), (std::size_t)1);
}
