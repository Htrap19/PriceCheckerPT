//
// Created by htrap19 on 4/9/22.
//

#ifndef PRICECHECKER_TASKQUEUE_H
#define PRICECHECKER_TASKQUEUE_H

#include <queue>
#include <mutex>
#include <thread>
#include <functional>
#include <condition_variable>
#include "utils/Utils.h"

namespace PC
{
    class TaskQueue // SingleTon
    {
    public:
        ~TaskQueue();
        SINGLE_TON(TaskQueue)

        void Quit();
        void Clear();

        template<typename Callable, typename ... Args>
        void Push(Callable&& func, Args&& ... args)
        {
            auto task = std::bind(func, args...);

            std::unique_lock lock(m_Mutex);
            m_TaskQueue.template emplace(task);
            m_ConditionVariable.notify_one();
        }

    private:
        TaskQueue();
        void Update();

    private:
        std::queue<std::function<void()>> m_TaskQueue;
        std::mutex m_Mutex;
        std::vector<std::thread> m_Threads;
        std::condition_variable m_ConditionVariable;
        bool m_Running = true;
    };
}

#endif //PRICECHECKER_TASKQUEUE_H
