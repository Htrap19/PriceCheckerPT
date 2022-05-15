//
// Created by Htrap19 on 5/12/2022.
//

#include "UIQueue.h"

namespace PC
{
    bool UIQueue::Idle()
    {
        while (!m_TaskQueue.empty())
        {
            std::unique_lock lock(m_QueueMutex);
            auto task = std::move(m_TaskQueue.front());
            lock.unlock();
            task();
            lock.lock();
            m_TaskQueue.pop();
            g_main_context_iteration(nullptr, false);
        }

        return false;
    }
}