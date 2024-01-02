#include "Lys/Core/Profiler.hpp"

#include <SFML/System/Time.hpp>

#if (PLATFORM == PLATFORM_WINDOWS)
    #include <windows.h>
#endif

namespace lys
{

namespace profiler
{

const char* Profiler::sm_File_Name = nullptr;
Profiler& Profiler::smt_Get(void)
{
    static Profiler ls_Profiler(sm_File_Name);

    return ls_Profiler;
}

Profiler::Profiler(const char* file_name)
{
    m_Enabled = file_name != nullptr;

    if (m_Enabled == true)
    {
        m_Clk.restart();
        m_Stream.open(file_name);
        m_First_Write = true;
        mt_Begin_File();
    }
}

Profiler::~Profiler()
{
    if (m_Enabled == true)
    {
        mt_End_File();
    }
}

void Profiler::mt_Start_Function(const char* function_name)
{
    if (m_Enabled == true)
    {
        mt_Write_Function(function_name, "B");
    }
}

void Profiler::mt_Stop_Function(const char* function_name)
{
    if (m_Enabled == true)
    {
        mt_Write_Function(function_name, "E");
    }
}

void Profiler::mt_Begin_File(void)
{
    if (m_Enabled == true)
    {
        m_Stream << "{\"traceEvents\":[";
    }
}

void Profiler::mt_End_File(void)
{
    if (m_Enabled == true)
    {
        m_Stream << "\n]}";
    }
}

#if (PLATFORM == PLATFORM_WINDOWS)
    #define GET_CURRENT_THREAD_ID GetCurrentThreadId
#else
    #define GET_CURRENT_THREAD_ID pthread_self
#endif

void Profiler::mt_Write_Function(const char* function_name, const char* phase)
{
    int l_PID = GET_CURRENT_THREAD_ID();
    int l_Milliseconds;

    m_Mutex.lock();
    l_Milliseconds = m_Clk.getElapsedTime().asMilliseconds();

    if (m_First_Write == true)
    {
        m_Stream << "\n\t";
        m_First_Write = false;
    }
    else
    {
        m_Stream << ",\n\t";
    }

    m_Stream << "{\"name\": \""
             << function_name
             << "\", \"cat\": \"PERF\", \"ph\": \""
             << phase
             << "\", \"pid\": "
             << l_PID
             << ", \"tid\": "
             << l_PID
             << ", \"ts\": "
             << l_Milliseconds
             << "}";

    m_Mutex.unlock();
}



ProfilerHelper::ProfilerHelper(const char* function_name) :
    m_Function_Name(function_name)
{
    Profiler::smt_Get().mt_Start_Function(m_Function_Name);
}

ProfilerHelper::~ProfilerHelper()
{
    Profiler::smt_Get().mt_Stop_Function(m_Function_Name);
}



void fn_Initialize_Profiler(const char* file_name)
{
    Profiler::sm_File_Name = file_name;
    Profiler::smt_Get();
}

}

}
