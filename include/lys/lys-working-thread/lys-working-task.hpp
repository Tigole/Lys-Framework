#ifndef _LYS_WORKING_TASK_HPP
#define _LYS_WORKING_TASK_HPP 1

#include <functional>
#include <mutex>
#include <queue>
#include <vector>

#include "lys-config.hpp"
#include "lys-working-thread.hpp"

namespace lys
{

class LYS_API AWorkingTask
{
    LYS_CLASS_NO_COPY(AWorkingTask)

    friend WorkingThread;

public:
    AWorkingTask(const char* name);
    virtual ~AWorkingTask();

    void Call_Thread_Task(void);

    const char* Get_Name(void) const;

private:
    virtual void Call_Task(void) = 0;
    void Stop(void);

    bool m_Working;
    std::mutex m_Mutex;
    const char* m_Name;
};

template<typename MsgType>
class WorkingTask: public AWorkingTask
{
public:
    template<class C>
    WorkingTask(const char* name, bool (C::*callback)(MsgType&), C* obj) :
        AWorkingTask(name), m_Host_Job(std::bind(callback, obj, std::placeholders::_1)), m_Host_Mutex(), m_Orders(), m_Results()
    {}

    void Push_Order(const MsgType& order, WorkingThread& working_thread)
    {
        m_Host_Mutex.lock();

        m_Orders.push(order);

        working_thread.Add_Task(this);

        m_Host_Mutex.unlock();
    }

    bool Pop_Result(MsgType& result)
    {
        bool l_b_Ret = false;

        m_Host_Mutex.lock();

        if (m_Results.size() > 0)
        {
            result = m_Results.front();
            m_Results.pop();
            l_b_Ret = true;
        }

        m_Host_Mutex.unlock();

        return l_b_Ret;
    }

    void Call_Task(void) override
    {
        MsgType l_Data;
        bool l_Work = false;

        m_Host_Mutex.lock();
        if (m_Orders.size() > 0)
        {
            l_Data = m_Orders.front();
            m_Orders.pop();
            l_Work = true;
        }
        m_Host_Mutex.unlock();

        if (l_Work == true)
        {
            if (m_Host_Job(l_Data) == true)
            {
                m_Host_Mutex.lock();
                m_Results.push(l_Data);
                m_Host_Mutex.unlock();
            }
        }
    }

private:
    std::function<bool(MsgType&)> m_Host_Job;

    std::mutex m_Host_Mutex;
    std::queue<MsgType> m_Orders;
    std::queue<MsgType> m_Results;
};

}  // namespace lys

#endif  // _LYS_WORKING_TASK_HPP
