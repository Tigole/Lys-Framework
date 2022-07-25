#ifndef _LYS_LOG_SINK_HPP
#define _LYS_LOG_SINK_HPP 1

#include "Lys/LysConfig.hpp"

namespace lys
{
namespace log
{

struct LogData;

class LYS_API Sink
{
public:
    virtual ~Sink(){}

    virtual void mt_Log(const LogData& data) = 0;
};

}
}

#endif // _LYS_LOG_SINK_HPP
