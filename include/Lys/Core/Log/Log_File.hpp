#ifndef _LYS_LOG_FILE_HPP
#define _LYS_LOG_FILE_HPP 1

#include "Log_Sink.hpp"

#include <fstream>

namespace lys
{
namespace log
{

class File : public Sink
{
public:
    File(const std::string& file);

    void mt_Log(const LogData& data) override;

private:
    std::ofstream m_Stream;
};

}
}

#endif // _LYS_LOG_FILE_HPP
