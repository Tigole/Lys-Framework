#ifndef _LYS_STATE_HPP
#define _LYS_STATE_HPP 1

#include <vector>
#include <memory>
#include <mutex>

#include "Lys/LysConfig.hpp"

namespace lys
{

class StateManager;
class Layer;

struct Event;

struct Message_ChangeState;

class LYS_API State
{
public:
    virtual ~State();

    virtual bool mt_On_Create(void);
    virtual bool mt_On_Destroy(void);

    virtual bool mt_On_Entry(void);
    virtual bool mt_On_Exit(void);

    void mt_On_Event([[maybe_unused]] const Event& event);
    void mt_On_Update(float elapsed_time);

protected:

    void mt_Push_Layer(Layer* layer);
    void mt_Pop_Layer(Layer* layer);

private:


    std::vector<lys::Layer*> m_Active_Layers;
    std::vector<lys::Layer*> m_Pop_Layers;
    std::vector<lys::Layer*> m_Push_Layers;

    void mt_On_Change_State(const Message_ChangeState& msg);

    friend StateManager;
    StateManager* m_State_Manager;
};


}

#endif // _LYS_STATE_HPP
