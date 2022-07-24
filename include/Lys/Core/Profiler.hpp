#ifndef _LYS_PROFILER_HPP
#define _LYS_PROFILER_HPP 1

#include <mutex>
#include <fstream>

#include <SFML/System/Clock.hpp>

#define LYS_PROFILE_FUNCTION lys::profiler::ProfilerHelper l_Profiler_Helper(__PRETTY_FUNCTION__)

namespace lys
{

namespace profiler
{

void fn_Initialize_Profiler(const char* file_name);

class ProfilerHelper
{
public:
    ProfilerHelper(const char* function_name);
    ~ProfilerHelper();

private:
    const char* m_Function_Name;
};

class Profiler
{
public:

    static const char* sm_File_Name;
    static Profiler& smt_Get(void);

public:
    ~Profiler();

    void mt_Start_Function(const char* function_name);
    void mt_Stop_Function(const char* function_name);

    void mt_Begin_File(void);
    void mt_End_File(void);

private:
    Profiler(const char* file_name);

    void mt_Write_Function(const char* function_name, const char* phase);

    bool m_Enabled;
    std::ofstream m_Stream;
    bool m_First_Write;
    sf::Clock m_Clk;
    std::mutex m_Mutex;
};

}

}

#endif // _LYS_PROFILER_HPP
