#ifndef _LYS_STATE_HPP
#define _LYS_STATE_HPP 1

namespace lys
{

struct Event;

class State
{
public:
    virtual ~State(){}

    virtual bool mt_OnEntry(void){return true;}
    virtual bool mt_OnExit(void){return true;}
    virtual void mt_OnUpdate([[maybe_unused]] float elapsed_time){}
    virtual void mt_OnEvent([[maybe_unused]] const Event& event){}
};


}

#endif // _LYS_STATE_HPP
