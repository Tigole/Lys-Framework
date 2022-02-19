#include "Lys/Core/Log/Log_Console.hpp"

#include <iostream>

namespace lys
{
namespace log
{


Console::Console() :
    m_Handle(nullptr),
    m_Default_Attrib(0)
{
    CONSOLE_SCREEN_BUFFER_INFO infos;

    m_Handle = GetStdHandle(STD_OUTPUT_HANDLE);

    GetConsoleScreenBufferInfo(m_Handle, &infos);

    m_Default_Attrib = infos.wAttributes;
}

Console::~Console()
{}

void Console::mt_Log(const LogData& data)
{
    mt_Set_Attribute(data.m_Level);

    std::cout << data.m_Header;
    mt_Set_Attribute(m_Default_Attrib);
    std::cout << data.m_Message << std::endl;

}

void Console::mt_Set_Attribute(LogLevel level)
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

void Console::mt_Set_Attribute(WORD attribute)
{
    SetConsoleTextAttribute(m_Handle, attribute);
}


}
}
