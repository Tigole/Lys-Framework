#ifndef _LYS_WORKING_TASK_HPP
#define _LYS_WORKING_TASK_HPP 1

#include <functional>
#include <queue>
#include <vector>
#include <mutex>

#include "Lys/Core/Core.hpp"
#include "WorkingThread.hpp"

namespace lys
{

class AWorkingTask
{
    LYS_CLASS_NO_COPY(AWorkingTask)

    friend WorkingThread;
public:
    AWorkingTask(const char* name);
    virtual ~AWorkingTask();

    void mt_Call_Thread_Task(void);

    const char* mt_Get_Name(void) const;

private:

    virtual void mt_Call_Task(void) = 0;
    void mt_Stop(void);

    bool m_Working;
    std::mutex m_Mutex;
    const char* m_Name;
};

template <typename MsgType>
class WorkingTask : public AWorkingTask
{
public:
    template<class C>
    WorkingTask(const char* name, bool (C::*pmt_Callback)(MsgType&), C* obj)
     :  AWorkingTask(name),
        m_Host_Job(std::bind(pmt_Callback, obj, std::placeholders::_1)),
        m_Host_Mutex(),
        m_Orders(),
        m_Results()
    {}

    void mt_Push_Order(const MsgType& order)
    {
        m_Host_Mutex.lock();

        m_Orders.push(order);

        WorkingThread::smt_Get().mt_Add_Task(this);

        m_Host_Mutex.unlock();
    }

    bool mt_Pop_Result(MsgType& result)
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

    void mt_Call_Task(void) override
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

}


#endif // _LYS_WORKING_TASK_HPP
