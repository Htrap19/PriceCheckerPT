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
        m_IdleCallback = []() {};
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
            std::unique_lock lock(m_TaskMutex);
            m_ConditionVariable.wait(lock, [&]()
            {
                m_IdleCallback();
                m_IdleCallback = []() {};
                return !m_TaskQueue.empty();
            });
            std::unique_lock queue_lock(m_QueueMutex);
            auto task = std::move(m_TaskQueue.front());
            queue_lock.unlock();
            task();
            queue_lock.lock();
            m_TaskQueue.pop();
        }
    }
}