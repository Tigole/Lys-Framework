#include "Lys/Core/Log/Log_Console.hpp"

#include <iostream>

namespace lys
{
namespace log
{

#if (PLATFORM == PLATFORM_WINDOWS)

ConsoleWindows::ConsoleWindows() :
    m_Handle(nullptr),
    m_Default_Attrib(0)
{
    CONSOLE_SCREEN_BUFFER_INFO infos;

    m_Handle = GetStdHandle(STD_OUTPUT_HANDLE);

    GetConsoleScreenBufferInfo(m_Handle, &infos);

    m_Default_Attrib = infos.wAttributes;
}

ConsoleWindows::~ConsoleWindows()
{}

void ConsoleWindows::mt_Log(const LogData& data)
{
    mt_Set_Attribute(data.m_Level);

    std::cout << data.m_Header;
    mt_Set_Attribute(m_Default_Attrib);
    std::cout << data.m_Message << std::endl;

}

void ConsoleWindows::mt_Set_Attribute(LogLevel level)
{
    WORD attribute;

    switch(level)
    {
    case LogLevel::Trace:
        attribute = FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
        break;
    case LogLevel::Debug:
        attribute = FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN;
        break;
    case LogLevel::Info:
        attribute = FOREGROUND_INTENSITY | FOREGROUND_GREEN;
        break;
    case LogLevel::Warning:
        attribute = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED;
        break;
    case LogLevel::Error:
        attribute = FOREGROUND_INTENSITY | FOREGROUND_RED;
        break;
    case LogLevel::Fatal:
        attribute = FOREGROUND_INTENSITY | BACKGROUND_RED;
        break;
    default:
        attribute = 0;
        break;
    }

    mt_Set_Attribute(attribute);
}

void ConsoleWindows::mt_Set_Attribute(WORD attribute)
{
    SetConsoleTextAttribute(m_Handle, attribute);
}



#else




ConsoleLinux::ConsoleLinux()
{}

ConsoleLinux::~ConsoleLinux()
{}

void ConsoleLinux::mt_Log(const LogData& data)
{
    std::cout << mt_Get_Level_String(data.m_Level);
    std::cout << data.m_Header;
    std::cout << mt_Get_Reset_String();
    std::cout << data.m_Message << std::endl;

}

const char* ConsoleLinux::mt_Get_Level_String(LogLevel level)
{
    switch(level)
    {
    case LogLevel::Trace: return "\033[39m";
    case LogLevel::Debug: return "\033[34m";
    case LogLevel::Info: return "\033[32m";
    case LogLevel::Warning: return "\033[33m";
    case LogLevel::Error: return "\033[31m";
    case LogLevel::Fatal: return "\033[31m";
    case LogLevel::COUNT: return "";
    default: return "";
    }
    return "";
}

const char* ConsoleLinux::mt_Get_Reset_String(void)
{
    return "\033[0m";
}

#endif

}
}
