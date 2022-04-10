//
// Created by htrap19 on 4/9/22.
//

#include "TaskQueue.h"

namespace PC
{
    TaskQueue::TaskQueue()
        : m_Thread(&TaskQueue::Update, this)
    {
        m_ThisThreadID = m_Thread.get_id();
    }

    TaskQueue::~TaskQueue()
    {
        Quit();
    }

    void TaskQueue::Quit()
    {
        m_Running = false;
        // pushing an empty function(task) to meet the predicate condition of the condition_variable
        Push([]() {});
        m_ConditionVariable.notify_all();
        if (m_Thread.joinable())
            m_Thread.join();
    }

    void TaskQueue::Update()
    {
        while (m_Running)
        {
            std::unique_lock lock(m_Mutex);
            m_ConditionVariable.wait(lock, [&]() { return !m_TaskQueue.empty(); });
            auto task = m_TaskQueue.front();
            task();
            m_TaskQueue.pop();
        }
    }
}