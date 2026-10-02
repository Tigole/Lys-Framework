#ifndef _LYS_LOG_HPP
#define _LYS_LOG_HPP 1

#include <sys/time.h>

#include <cstring>
#include <lys-config.hpp>
#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

#define LYS_LOG_TRACE(token, fmt, ...) \
    lys::log::LoggerPool::Get_Singleton().Log(token, __FILE__, __LINE__, lys::log::LogLevel::Trace, fmt, ##__VA_ARGS__)
#define LYS_LOG_DEBUG(token, fmt, ...) \
    lys::log::LoggerPool::Get_Singleton().Log(token, __FILE__, __LINE__, lys::log::LogLevel::Debug, fmt, ##__VA_ARGS__)
#define LYS_LOG_INFORMATION(token, fmt, ...) \
    lys::log::LoggerPool::Get_Singleton().Log(token, __FILE__, __LINE__, lys::log::LogLevel::Info, fmt, ##__VA_ARGS__)
#define LYS_LOG_WARNING(token, fmt, ...) \
    lys::log::LoggerPool::Get_Singleton().Log(token, __FILE__, __LINE__, lys::log::LogLevel::Warning, fmt, ##__VA_ARGS__)
#define LYS_LOG_ERROR(token, fmt, ...) \
    lys::log::LoggerPool::Get_Singleton().Log(token, __FILE__, __LINE__, lys::log::LogLevel::Error, fmt, ##__VA_ARGS__)
#define LYS_LOG_FATAL(token, fmt, ...) \
    lys::log::LoggerPool::Get_Singleton().Log(token, __FILE__, __LINE__, lys::log::LogLevel::Fatal, fmt, ##__VA_ARGS__)

namespace lys
{

namespace log
{

enum class LogLevel
{
    Trace,    /// Used to hunt bugs
    Debug,    /// Used to log debug information
    Info,     /// Used to log application information
    Warning,  /// Used to log recovered issues
    Error,    /// Used to log things that should not happen
    Fatal,    /// Used to log assert
    // COUNT
};

struct LYS_API LogData
{
    LogData() : m_Level(LogLevel::Trace), m_Header(), m_Message() {}
    LogLevel m_Level;
    char m_Header[128];
    std::string m_Message;
};

class LYS_API Sink
{
public:
    virtual ~Sink() {}

    virtual void Log(const LogData& data) = 0;
};

class LYS_API Logger
{
public:
    Logger();

    void Log(const LogData& data);

    Logger& Add_Sink(Sink* s);
    void Set_Level(LogLevel level);

private:
    std::vector<std::unique_ptr<Sink>> m_Sinks;
    LogLevel m_Level;
    std::mutex m_Mutex;
};

class LYS_API LoggerPool
{
public:
    static LoggerPool& Get_Singleton(void);

    template<typename... Args>
    void Log(const char* token, const char* file, int line_number, LogLevel level, const char* fmt, Args... args)
    {
        char l_Msg[1024];

        snprintf(l_Msg, sizeof(l_Msg), fmt, args...);

        Log_Formated(token, file, line_number, level, l_Msg);
    }

    Logger& Get_Logger(const char* token);

private:
    void Log_Formated(const char* token, const char* file, int line_number, LogLevel level, const char* msg);
    void Log(const char* token, const LogData& data);

    std::unordered_map<std::string, std::unique_ptr<Logger>> m_Loggers;
    std::vector<int> m_Threads;
    int Get_Thread_Id(void);

private:
    LoggerPool();
};

#define LYS_LOG_TOKEN "LYS"
#define LYS_LOG_CORE_TRACE(fmt, ...) LYS_LOG_TRACE(LYS_LOG_TOKEN, fmt, ##__VA_ARGS__)
#define LYS_LOG_CORE_DEBUG(fmt, ...) LYS_LOG_DEBUG(LYS_LOG_TOKEN, fmt, ##__VA_ARGS__)
#define LYS_LOG_CORE_INFORMATION(fmt, ...) LYS_LOG_INFORMATION(LYS_LOG_TOKEN, fmt, ##__VA_ARGS__)
#define LYS_LOG_CORE_WARNING(fmt, ...) LYS_LOG_WARNING(LYS_LOG_TOKEN, fmt, ##__VA_ARGS__)
#define LYS_LOG_CORE_ERROR(fmt, ...) LYS_LOG_ERROR(LYS_LOG_TOKEN, fmt, ##__VA_ARGS__)
#define LYS_LOG_CORE_FATAL(fmt, ...) LYS_LOG_FATAL(LYS_LOG_TOKEN, fmt, ##__VA_ARGS__)

}  // namespace log

}  // namespace lys

#endif  // _LYS_LOG_HPP
