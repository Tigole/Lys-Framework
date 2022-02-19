#ifndef _LYS_LOG_CONSOLE_HPP
#define _LYS_LOG_CONSOLE_HPP 1

#include "Log_Sink.hpp"
#include "Lys/Core/Log.hpp"

#include <windows.h>

namespace lys
{
namespace log
{


class Console : public Sink
{
public:
    Console();
    ~Console();
    Console(const Console& rhs) = delete;
    Console& operator=(const Console& rhs) = delete;

    void mt_Log(const LogData& data) override;

private:

    void mt_Set_Attribute(LogLevel level);
    void mt_Set_Attribute(WORD attribute);

    void* m_Handle;
    WORD m_Default_Attrib;

};


}
}

#endif // _LYS_LOG_CONSOLE_HPP
