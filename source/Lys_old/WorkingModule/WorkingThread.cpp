#include "Lys/WorkingModule/WorkingThread.hpp"

#include "Lys/Core/Log.hpp"
#include "Lys/WorkingModule/WorkingTask.hpp"

namespace lys
{

WorkingThread& WorkingThread::smt_Get(void)
{
    static WorkingThread ls_Singleton;

    return ls_Singleton;
}

WorkingThread::WorkingThread() :
    m_Mutex(), m_Thread(&WorkingThread::mt_Thread, this), m_Run(true), m_Condition_Mutex(), m_Condition_Variable(), m_Pending_Tasks()
{}

WorkingThread::~WorkingThread() {}

void WorkingThread::mt_Add_Task(AWorkingTask* task)
{
    m_Mutex.lock();

    LYS_LOG_CORE_DEBUG("Adding task '%s'", task->mt_Get_Name());
    m_Pending_Tasks.push_back(task);

    m_Condition_Variable.notify_one();

    m_Mutex.unlock();
}

void WorkingThread::mt_Stop_Thread(void)
{
    LYS_LOG_CORE_DEBUG("Stopping WorkingThread: %p", this);
    m_Mutex.lock();
    LYS_LOG_CORE_DEBUG("locked");
    m_Run = false;
    m_Condition_Variable.notify_one();
    m_Mutex.unlock();
    LYS_LOG_CORE_DEBUG("unlocked");

    m_Thread.join();
    LYS_LOG_CORE_DEBUG("Stopped WorkingThread");
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
