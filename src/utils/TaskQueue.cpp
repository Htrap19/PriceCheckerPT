//
// Created by htrap19 on 4/9/22.
//

#include "TaskQueue.h"
#include <iostream>

namespace PC
{
    TaskQueue::TaskQueue()
    {
        uint32_t hardware_concurrency = std::thread::hardware_concurrency();
        if (hardware_concurrency <= 0)
            hardware_concurrency = 1;

        for (uint32_t i = 0; i < hardware_concurrency; i++)
            m_Threads.emplace_back(&TaskQueue::Update, this);

//        m_IdleCallback = []() {};
    }

    TaskQueue::~TaskQueue()
    {
        Quit();
    }

    void TaskQueue::Quit()
    {
        m_Running = false;
        m_ConditionVariable.notify_all();
        for (auto& thread : m_Threads)
            if (thread.joinable())
                thread.join();
    }

    void TaskQueue::Update()
    {
        while (m_Running)
        {
            std::unique_lock lock(m_Mutex);
            m_ConditionVariable.wait(lock, [&]()
            {
//                m_IdleCallback();
//                m_IdleCallback = []() {};
                return m_Running ? !m_TaskQueue.empty() : !m_Running;
            });
            if (!m_Running)
                break;

            auto task = std::move(m_TaskQueue.front());
            m_TaskQueue.pop();
            lock.unlock();
            task();
        }
    }
}