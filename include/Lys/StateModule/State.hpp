#ifndef _LYS_STATE_HPP
#define _LYS_STATE_HPP 1

#include <vector>
#include <memory>

namespace lys
{

class StateManager;
class Layer;

struct Event;

struct Message_ChangeState;

class State
{
public:
    virtual ~State();

    virtual bool mt_OnCreate(void);
    virtual bool mt_OnDestroy(void);

    virtual bool mt_OnEntry(void);
    virtual bool mt_OnExit(void);

    void mt_OnEvent([[maybe_unused]] const Event& event);
    void mt_OnUpdate(float elapsed_time);

protected:

    void mt_Push_Layer(Layer* l);
    void mt_Pop_Layer(void);

private:

    std::vector<Layer*> m_Layers;

    void mt_OnChangeState(const Message_ChangeState& msg);

    friend StateManager;
    StateManager* m_State_Manager;
};


}

#endif // _LYS_STATE_HPP
