#include "Lys/Core/Log/Log_File.hpp"

#include "Lys/Core/Log.hpp"

namespace lys
{
namespace log
{

std::map<std::string, std::shared_ptr<std::ofstream>> File::sm_Stream_Pool;

std::ofstream* File::smt_Get_Stream(const std::string& file)
{
    auto it = sm_Stream_Pool.find(file);
    if (it == sm_Stream_Pool.end())
    {
        it = sm_Stream_Pool.emplace(file, std::make_shared<std::ofstream>()).first;
        it->second->open(file);
        if (it->second->is_open() == false)
        {
            LYS_LOG_CORE_ERROR("Could not open file: '%s'", file.c_str());
        }
    }

    return it->second.get();
}

File::File(const std::string& file) : m_Stream(smt_Get_Stream(file)) {}

void File::mt_Log(const LogData& data)
{
    std::unique_lock l(m_Mutex);
    (*m_Stream) << data.m_Header << data.m_Message << std::endl;
}

}  // namespace log
}  // namespace lys
