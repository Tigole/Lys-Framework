#ifndef _LYS_WORKING_THREAD_HPP
#define _LYS_WORKING_THREAD_HPP 1

#include <condition_variable>
#include <mutex>
#include <thread>
#include <vector>

#include "lys-config.hpp"

namespace lys
{

class AWorkingTask;

class LYS_API WorkingThread
{
public:
    WorkingThread();
    ~WorkingThread();

    void Add_Task(AWorkingTask* task);

    void Stop_Thread(void);

private:
    std::mutex m_Mutex;
    std::thread m_Thread;
    bool m_Run;
    void Thread(void);

    std::mutex m_Condition_Mutex;
    std::condition_variable m_Condition_Variable;
    std::vector<AWorkingTask*> m_Pending_Tasks;
};

}  // namespace lys

#endif  // _LYS_WORKING_THREAD_HPP
