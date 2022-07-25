#ifndef _LYS_LOG_HPP
#define _LYS_LOG_HPP 1

#include "Lys/LysConfig.hpp"
#include "Log/Log_Sink.hpp"

#include <string>
#include <sys/time.h>
#include <vector>
#include <memory>
#include <cstring>
#include <unordered_map>
#include <mutex>


#define LYS_LOG_TRACE(token, ...)       lys::log::LoggerPool::smt_Get().mt_Log(token, __FILE__, __LINE__, lys::log::LogLevel::Trace,   __VA_ARGS__)
#define LYS_LOG_DEBUG(token, ...)       lys::log::LoggerPool::smt_Get().mt_Log(token, __FILE__, __LINE__, lys::log::LogLevel::Debug,   __VA_ARGS__)
#define LYS_LOG_INFORMATION(token, ...) lys::log::LoggerPool::smt_Get().mt_Log(token, __FILE__, __LINE__, lys::log::LogLevel::Info,    __VA_ARGS__)
#define LYS_LOG_WARNING(token, ...)     lys::log::LoggerPool::smt_Get().mt_Log(token, __FILE__, __LINE__, lys::log::LogLevel::Warning, __VA_ARGS__)
#define LYS_LOG_ERROR(token, ...)       lys::log::LoggerPool::smt_Get().mt_Log(token, __FILE__, __LINE__, lys::log::LogLevel::Error,   __VA_ARGS__)
#define LYS_LOG_FATAL(token, ...)       lys::log::LoggerPool::smt_Get().mt_Log(token, __FILE__, __LINE__, lys::log::LogLevel::Fatal,   __VA_ARGS__)


namespace lys
{

namespace log
{

enum class LogLevel
{
    Trace,      /// Used to hunt bugs
    Debug,      /// Used to log debug information
    Info,       /// Used to log application information
    Warning,    /// Used to log recovered issues
    Error,      /// Used to log things that should not happen
    Fatal,      /// Used to log assert
    COUNT
};

struct LYS_API LogData
{
    LogData() : m_Level(LogLevel::Trace), m_Header(), m_Message(){}
    LogLevel m_Level;
    char m_Header[64];
    std::string m_Message;
};

class LYS_API Logger
{
public:
    Logger();

    void mt_Log(const LogData& data);

    Logger& mt_Add_Sink(Sink* s);
    void mt_Set_Level(LogLevel level);

private:
    std::vector<std::unique_ptr<Sink>> m_Sinks;
    LogLevel m_Level;
	std::mutex m_Mutex;
};

class LYS_API LoggerPool
{
public:
    static LoggerPool& smt_Get(void);

    template<typename... Args>
    void mt_Log(const char* token, const char* file, int line_number, LogLevel level, const char* fmt, Args... args)
    {
        char l_Msg[1024];

        snprintf(l_Msg, sizeof(l_Msg), fmt, args...);

        mt_Log_Formated(token, file, line_number, level, l_Msg);
    }

    Logger& mt_Get_Logger(const char* token);

private:
    void mt_Log_Formated(const char* token, const char* file, int line_number, LogLevel level, const char* msg);
    void mt_Log(const char* token, const LogData& data);

    std::unordered_map<std::string, std::unique_ptr<Logger>> m_Loggers;
    std::vector<int> m_Threads;
    int mt_Get_Thread_Id(void);

private:
    LoggerPool();
};

#define LYS_LOG_TOKEN "LYS"
#define LYS_LOG_CORE_TRACE(...)        LYS_LOG_TRACE(LYS_LOG_TOKEN, __VA_ARGS__)
#define LYS_LOG_CORE_DEBUG(...)        LYS_LOG_DEBUG(LYS_LOG_TOKEN, __VA_ARGS__)
#define LYS_LOG_CORE_INFORMATION(...)  LYS_LOG_INFORMATION(LYS_LOG_TOKEN, __VA_ARGS__)
#define LYS_LOG_CORE_WARNING(...)      LYS_LOG_WARNING(LYS_LOG_TOKEN, __VA_ARGS__)
#define LYS_LOG_CORE_ERROR(...)        LYS_LOG_ERROR(LYS_LOG_TOKEN, __VA_ARGS__)
#define LYS_LOG_CORE_FATAL(...)        LYS_LOG_FATAL(LYS_LOG_TOKEN, __VA_ARGS__)

}

}

#endif // _LYS_LOG_HPP
