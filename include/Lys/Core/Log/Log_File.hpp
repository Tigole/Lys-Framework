#ifndef _LYS_LOG_FILE_HPP
#define _LYS_LOG_FILE_HPP 1

#include <fstream>
#include <map>
#include <memory>
#include <mutex>

#include "Log_Sink.hpp"

namespace lys
{
namespace log
{

class LYS_API File: public Sink
{
public:
    File(const std::string& file);

    void mt_Log(const LogData& data) override;

private:
    std::mutex m_Mutex;
    std::ofstream* m_Stream;

    static std::map<std::string, std::shared_ptr<std::ofstream>> sm_Stream_Pool;
    static std::ofstream* smt_Get_Stream(const std::string& file);
};

}  // namespace log
}  // namespace lys

#endif  // _LYS_LOG_FILE_HPP
