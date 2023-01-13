#include "Lys/Core/Log.hpp"

#include "Lys/Core/Log/Log_Console.hpp"

#include <time.h>
#include <sys/time.h>
#include <array>
#include <iostream>
#include <algorithm>
#if (PLATFORM == PLATFORM_WINDOWS)
    #include <windows.h>
#endif

namespace lys
{
namespace log
{

static constexpr const std::array<const char*, static_cast<std::size_t>(LogLevel::COUNT)> sg_Levels =
{
    "TRC",
    "DBG",
    "INF",
    "WAR",
    "ERR",
    "FTL"
};

Logger::Logger() :
    m_Sinks(),
    m_Level(LogLevel::Trace),
    m_Mutex()
{}

void Logger::mt_Log(const LogData& data)
{
	m_Mutex.lock();
    if (data.m_Level >= m_Level)
    {
        for (std::size_t ii = 0; ii < m_Sinks.size(); ii++)
        {
            m_Sinks[ii]->mt_Log(data);
        }
    }
	m_Mutex.unlock();
}

Logger& Logger::mt_Add_Sink(Sink* s)
{
    m_Sinks.push_back(std::unique_ptr<Sink>(s));

    return *this;
}

void Logger::mt_Set_Level(LogLevel level)
{
    m_Level = level;
}




LoggerPool::LoggerPool() :
    m_Loggers(),
    m_Threads()
{}

Logger& LoggerPool::mt_Get_Logger(const char* token)
{
    auto l_it = m_Loggers.find(token);

    if (l_it == m_Loggers.end())
    {
        l_it = m_Loggers.emplace(token, new Logger).first;
    }

    return *l_it->second;
}

LoggerPool& LoggerPool::smt_Get(void)
{
    static LoggerPool ls_Singleton;

    return ls_Singleton;
}

void LoggerPool::mt_Log_Formated(const char* token, const char* file, int line_number, LogLevel level, const char* msg)
{
    LogData l_Data;
    char l_Time[16];
    struct timeval l_Time_Val;
    struct tm* l_TM;
    const char* l_Short_File_Name;
    time_t t;

    gettimeofday(&l_Time_Val, nullptr);
    t = l_Time_Val.tv_sec;
    l_TM = localtime(&t);

    l_Time[strftime(l_Time, sizeof(l_Time), "%H:%M:%S", l_TM)] = '\0';


    l_Short_File_Name = file;
    while(*file != '\0')
    {
        file++;
        if (*file == '/' || *file == '\\')
        {
            l_Short_File_Name = file + 1;
        }
    }

    ///"[date - level - thread - file:line]:"
#if (PLATFORM == PLATFORM_WINDOWS)
    sprintf_s(l_Data.m_Header,
              sizeof(l_Data.m_Header),
              "[%s:%03d - %s - %02d - %s - %s:%d] ",
              l_Time,
              l_Time_Val.tv_usec / 1000,
              sg_Levels[static_cast<std::size_t>(level)],
              mt_Get_Thread_Id(),
              token,
              l_Short_File_Name,
              line_number);
#else
    std::snprintf(l_Data.m_Header,
              sizeof(l_Data.m_Header),
              "[%s:%03d - %s - %02d - %s - %s:%d] ",
              l_Time,
              static_cast<int>(l_Time_Val.tv_usec / 1000),
              sg_Levels[static_cast<std::size_t>(level)],
              mt_Get_Thread_Id(),
              token,
              l_Short_File_Name,
              line_number);
#endif
    l_Data.m_Level = level;
    l_Data.m_Message = msg;
    mt_Log(token, l_Data);
}

void LoggerPool::mt_Log(const char* token, const LogData& data)
{
    mt_Get_Logger(token).mt_Log(data);
}

#if (PLATFORM == PLATFORM_WINDOWS)
    #define FUNC_GET_CURRENT_THREAD_IS GetCurrentThreadId
#else
    #define FUNC_GET_CURRENT_THREAD_IS pthread_self
#endif

int LoggerPool::mt_Get_Thread_Id(void)
{
    auto it = std::find(m_Threads.begin(), m_Threads.end(), static_cast<int>(FUNC_GET_CURRENT_THREAD_IS()));

    if (it == m_Threads.end())
    {
        m_Threads.push_back(FUNC_GET_CURRENT_THREAD_IS());
        it = std::find(m_Threads.begin(), m_Threads.end(), static_cast<int>(FUNC_GET_CURRENT_THREAD_IS()));
    }

    return std::distance(m_Threads.begin(), it);
}

}
}
