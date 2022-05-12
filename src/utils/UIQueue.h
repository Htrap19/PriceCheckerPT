//
// Created by Htrap19 on 5/12/2022.
//

#ifndef PRICECHECKER_UIQUEUE_H
#define PRICECHECKER_UIQUEUE_H

#include <queue>
#include <functional>
#include <mutex>
#include <gtkmm.h>
#include "utils/Utils.h"

namespace PC
{
    class UIQueue // Single-Ton
    {
    public:
        SINGLE_TON(UIQueue)

        template <typename Callable, typename ... Args>
        void Push(Callable&& func, Args&& ... args)
        {
            auto task = std::bind(func, args...);

            std::unique_lock lock(m_QueueMutex);
            m_TaskQueue.push(task);
            if (!m_IdleConnection)
                m_IdleConnection = Glib::signal_idle().connect(sigc::mem_fun(*this, &UIQueue::Idle));
        }

    private:
        UIQueue() = default;
        bool Idle();

    private:
        std::queue<std::function<void()>> m_TaskQueue;
        std::mutex m_QueueMutex;
        sigc::connection m_IdleConnection;
    };
}

#endif //PRICECHECKER_UIQUEUE_H
