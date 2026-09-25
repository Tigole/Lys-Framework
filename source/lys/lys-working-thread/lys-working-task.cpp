#include "lys-working-task.hpp"

namespace lys
{

AWorkingTask::AWorkingTask(const char* name) : m_Working(true), m_Mutex(), m_Name(name) {}

AWorkingTask::~AWorkingTask()
{
    Stop();
}

void AWorkingTask::Call_Thread_Task(void)
{
    m_Mutex.lock();

    if (m_Working == true)
    {
        Call_Task();
    }

    m_Mutex.unlock();
}

const char* AWorkingTask::Get_Name(void) const
{
    return m_Name;
}

void AWorkingTask::Stop(void)
{
    m_Mutex.lock();
    m_Working = false;
    m_Mutex.unlock();
}

}  // namespace lys
