#include "lys-working-thread.hpp"

#if 0
#include "Lys/Log/Log.hpp"
#endif
#include "lys-working-task.hpp"

namespace lys
{

WorkingThread::WorkingThread() :
    m_Mutex(), m_Thread(&WorkingThread::Thread, this), m_Run(true), m_Condition_Mutex(), m_Condition_Variable(), m_Pending_Tasks()
{}

WorkingThread::~WorkingThread()
{
    Stop_Thread();
}

void WorkingThread::Add_Task(AWorkingTask* task)
{
    if (task != nullptr)
    {
        m_Mutex.lock();

#if 0
        LYS_LOG_CORE_DEBUG("Adding task '%s'", task->Get_Name());
#endif
        m_Pending_Tasks.push_back(task);

        m_Condition_Variable.notify_one();

        m_Mutex.unlock();
    }
}

void WorkingThread::Stop_Thread(void)
{
#if 0
    LYS_LOG_CORE_DEBUG("Stopping WorkingThread: %p", this);
#endif
    if (m_Thread.joinable())
    {
        m_Mutex.lock();
        m_Run = false;
        m_Condition_Variable.notify_one();
        m_Mutex.unlock();

        m_Thread.join();
    }
#if 0
    LYS_LOG_CORE_DEBUG("Stopped WorkingThread");
#endif
}

void WorkingThread::Thread(void)
{
    bool l_Run = true;
    std::vector<AWorkingTask*> l_Tasks;
    bool l_Has_Pending_Tasks;

    while (l_Run == true)
    {
        m_Mutex.lock();
        l_Has_Pending_Tasks = m_Pending_Tasks.empty() == false;
        m_Mutex.unlock();

        if (l_Has_Pending_Tasks == false)
        {
            std::unique_lock<std::mutex> l_Lock(m_Condition_Mutex);
            m_Condition_Variable.wait(l_Lock, [this]() { return m_Pending_Tasks.size() > 0 || m_Run == false; });
        }

        m_Mutex.lock();
        l_Tasks = m_Pending_Tasks;
        m_Pending_Tasks.clear();
        l_Run = m_Run;
        m_Mutex.unlock();

        for (std::size_t ii = 0; ii < l_Tasks.size(); ii++)
        {
            l_Tasks[ii]->Call_Thread_Task();
        }
    }
}

}  // namespace lys
