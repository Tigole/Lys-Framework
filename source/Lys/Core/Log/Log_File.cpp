#include "Lys/Core/Log/Log_File.hpp"

#include "Lys/Core/Log.hpp"

namespace lys
{
namespace log
{

File::File(const std::string& file) :
    m_Stream()
{
    m_Stream.open(file);

    if (m_Stream.is_open() == false)
    {
        LYS_LOG_CORE_ERROR("Could not open file: '%s'", file.c_str());
    }
}

void File::mt_Log(const LogData& data)
{
    m_Stream << data.m_Header << data.m_Message << std::endl;
}

}
}
