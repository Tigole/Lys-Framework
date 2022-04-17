#include "Lys/WorkingModule/WorkingThread.hpp"
#include "Lys/WorkingModule/WorkingTask.hpp"

namespace lys
{





WorkingThread::WorkingThread() :
    Singleton<WorkingThread>("WorkingThread"),
    m_Mutex(),
    m_Thread(&WorkingThread::mt_Thread, this),
    m_Run(true),
    m_Condition_Mutex(),
    m_Condition_Variable(),
    m_Pending_Tasks()
{}

WorkingThread::~WorkingThread()
{
    mt_Stop_Thread();
}

void WorkingThread::mt_Add_Task(AWorkingTask* task)
{
    m_Mutex.lock();

    m_Pending_Tasks.push_back(task);

    m_Condition_Variable.notify_one();

    m_Mutex.unlock();
}

void WorkingThread::mt_Stop_Thread(void)
{
    m_Mutex.lock();
    m_Run = false;
    m_Condition_Variable.notify_one();
    m_Mutex.unlock();

    m_Thread.join();
}

void WorkingThread::mt_Thread(void)
{
    bool l_Run = true;
    std::vector<AWorkingTask*> l_Tasks;
    std::unique_lock<std::mutex> l_Lock(m_Condition_Mutex);
    bool l_Has_Pending_Tasks;

    while (l_Run == true)
    {
        m_Mutex.lock();
        l_Has_Pending_Tasks = m_Pending_Tasks.empty() == false;
        m_Mutex.unlock();

        if (l_Has_Pending_Tasks == false)
        {
            m_Condition_Variable.wait(l_Lock);
        }

        m_Mutex.lock();
        l_Tasks = m_Pending_Tasks;
        m_Pending_Tasks.clear();
        l_Run = m_Run;
        m_Mutex.unlock();

        for(std::size_t ii = 0; ii < l_Tasks.size(); ii++)
        {
            l_Tasks[ii]->mt_Call_Thread_Task();
        }
    }
}





}
