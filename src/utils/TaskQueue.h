//
// Created by htrap19 on 4/9/22.
//

#ifndef PRICECHECKER_TASKQUEUE_H
#define PRICECHECKER_TASKQUEUE_H

#include <queue>
#include <future>
#include <mutex>
#include <thread>
#include <functional>

namespace PC
{
    class TaskQueue // SingleTon
    {
    public:
        ~TaskQueue();
        TaskQueue(TaskQueue&) = delete;
        TaskQueue(TaskQueue&&) = delete;
        TaskQueue& operator=(TaskQueue&) = delete;
        TaskQueue& operator=(TaskQueue&&) = delete;

        inline static TaskQueue& _() { static TaskQueue instance; return instance; }

        inline void Quit();

        template<typename Callable, typename ... Args>
        void Push(Callable&& func, Args&& ... args)
        {
            auto task = std::bind(func, args...);
            // Check for deadlock safety
            if (this->m_ThisThreadID == std::this_thread::get_id()) { task(); return; }

            std::unique_lock lock(m_Mutex);
            m_TaskQueue.push(task);
            m_ConditionVariable.notify_one();
        }

    private:
        TaskQueue();
        void Update();

    private:
        std::queue<std::function<void()>> m_TaskQueue;
        std::mutex m_Mutex;
        std::thread m_Thread;
        std::condition_variable m_ConditionVariable;
        bool m_Running = true;
        std::thread::id m_ThisThreadID;
    };
}

#endif //PRICECHECKER_TASKQUEUE_H
