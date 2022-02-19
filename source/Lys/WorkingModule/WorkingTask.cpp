#include "Lys/WorkingModule/WorkingTask.hpp"

namespace lys
{


AWorkingTask::AWorkingTask(const char* name) : m_Working(true), m_Mutex(), m_Name(name)
{}

AWorkingTask::~AWorkingTask()
{
    mt_Stop();
}

void AWorkingTask::mt_Call_Thread_Task(void)
{
    m_Mutex.lock();

    if (m_Working == true)
    {
        mt_Call_Task();
    }

    m_Mutex.unlock();
}

const char* AWorkingTask::mt_Get_Name(void) const
{
    return m_Name;
}

void AWorkingTask::mt_Stop(void)
{
    m_Mutex.lock();
    m_Working = false;
    m_Mutex.unlock();
}





}



