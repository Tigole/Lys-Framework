#ifndef _LYS_WORKING_THREAD_HPP
#define _LYS_WORKING_THREAD_HPP 1

#include <vector>
#include <mutex>
#include <thread>
#include <condition_variable>

#include "Lys/LysConfig.hpp"

namespace lys
{

class AWorkingTask;

class LYS_API WorkingThread
{
    WorkingThread();
    ~WorkingThread();
public:

    static WorkingThread& smt_Get(void);

    void mt_Add_Task(AWorkingTask* task);

    void mt_Stop_Thread(void);

private:
    std::mutex m_Mutex;
    std::thread m_Thread;
    bool m_Run;
    void mt_Thread(void);

    std::mutex m_Condition_Mutex;
    std::condition_variable m_Condition_Variable;
    std::vector<AWorkingTask*> m_Pending_Tasks;
};

}

#endif // _LYS_WORKING_THREAD_HPP
