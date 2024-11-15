#ifndef _LYS_LOG_CONSOLE_HPP
#define _LYS_LOG_CONSOLE_HPP 1

#include "Log_Sink.hpp"
#include "Lys/Core/Log.hpp"

namespace lys
{
namespace log
{

#if (PLATFORM == PLATFORM_WINDOWS)
#    define CONSOLE_TYPE ConsoleWindows
class LYS_API ConsoleWindows: public Sink
{
public:
    ConsoleWindows();
    ~ConsoleWindows();
    ConsoleWindows(const ConsoleWindows& rhs)            = delete;
    ConsoleWindows& operator=(const ConsoleWindows& rhs) = delete;

    void mt_Log(const LogData& data) override;

private:
    void mt_Set_Attribute(LogLevel level);

    void* m_Handle;
};

#else
#    define CONSOLE_TYPE ConsoleLinux
class LYS_API ConsoleLinux: public Sink
{
public:
    ConsoleLinux();
    ~ConsoleLinux();
    ConsoleLinux(const ConsoleLinux& rhs)            = delete;
    ConsoleLinux& operator=(const ConsoleLinux& rhs) = delete;

    void mt_Log(const LogData& data) override;

private:
    const char* mt_Get_Level_String(LogLevel level);
    const char* mt_Get_Reset_String(void);
};
#endif

using Console = CONSOLE_TYPE;

}  // namespace log
}  // namespace lys

#endif  // _LYS_LOG_CONSOLE_HPP
