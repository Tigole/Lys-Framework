#ifndef _LYS_LOG_SINK_HPP
#define _LYS_LOG_SINK_HPP 1

namespace lys
{
namespace log
{

struct LogData;

class Sink
{
public:
    virtual ~Sink(){}

    virtual void mt_Log(const LogData& data) = 0;
};

}
}

#endif // _LYS_LOG_SINK_HPP
