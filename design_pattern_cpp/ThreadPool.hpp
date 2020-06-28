#ifndef THREAD_POOL_HPP
#define THREAD_POOL_HPP

#include <list>
#include <thread>
#include <functional>
#include <memory>
#include <atomic>
#include "SyncQueue.hpp"

namespace
{
const int MAXTASKCOUNT = 100;
} // namespace

class ThreadPool
{
public:
    using Task = std::function<void()>;

    ThreadPool(int numThreads = std::thread::hardware_concurrency())
        : mQueue(MAXTASKCOUNT)
    {
        Start(numThreads);
    }

    ~ThreadPool(void)
    {
        Stop();
    }

    void Stop()
    {
        std::call_once(mFlag, [this]{StopThreadGroup();});
    }

    void AddTask(Task&& task)
    {
        mQueue.Put(std::forward<Task>(task));
    }

    void AddTask(const Task& task)
    {
        mQueue.Put(task);
    }

private:
    void RunInThread()
    {
        while (mRunning)
        {
            std::list<Task> list{};
            mQueue.Take(list);

            for (auto &task : list)
            {
                if (!mRunning)
                    return;

                task();
            }
        }
    }

    void Start(int numThreads)
    {
        mRunning = true;
        for (size_t i = 0; i < numThreads; ++i)
        {
            mThreadGroup.emplace_back(std::make_shared<std::thread>(&ThreadPool::RunInThread, this));
        }
    }

    void StopThreadGroup()
    {
        mQueue.Stop();
        mRunning = false;

        for (auto thread : mThreadGroup)
        {
            if (thread)
            {
                thread->join();
            }
            
        }
        mThreadGroup.clear();
    }

private:
    std::list<std::shared_ptr<std::thread>> mThreadGroup;
    SyncQueue<Task> mQueue;
    std::atomic_bool mRunning;
    std::once_flag mFlag;
};

#endif