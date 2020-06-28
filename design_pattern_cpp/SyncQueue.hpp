#ifndef SYNC_QUEUE_HPP
#define SYNC_QUEUE_HPP

#include <list>
#include <mutex>
#include <condition_variable>
#include <iostream>

template <typename T>
class SyncQueue
{
private:
    std::list<T> mQueue;
    std::mutex mMutex;
    std::condition_variable mNotEmpty;
    std::condition_variable mNotFull;

    int mMaxSize;
    bool mNeedStop;

public:
    SyncQueue(int maxSize) : mMaxSize(maxSize), mNeedStop(false) {}

    void Put(const T &x)
    {
        Add(x);
    }

    void Put(T &&x)
    {
        Add(std::forward<T>(x));
    }

    void Take(std::list<T> &list)
    {
        std::unique_lock<std::mutex> lock(mMutex);
        mNotEmpty.wait(lock, [this] { return mNeedStop || NotEmpty(); });

        if (mNeedStop)
            return;

        list = std::move(mQueue);
        mNotFull.notify_one();
    }

    void Take(T &t)
    {
        std::unique_lock<std::mutex> locker(mMutex);
        mNotEmpty.wait(locker, [this] { return mNeedStop || NotEmpty(); });

        if (mNeedStop)
            return;

        t = mQueue.front();
        mQueue.pop_front();
        mNotFull.notify_one();
    }

    void Stop()
    {
        {
            std::lock_guard<std::mutex> locker(mMutex);
            mNeedStop = true;
        }

        mNotEmpty.notify_all();
        mNotFull.notify_all();
    }

    bool Empty()
    {
        std::lock_guard<std::mutex> locker(mMutex);
        return mQueue.empty();
    }

    bool Full()
    {
        std::lock_guard<std::mutex> locker(mMutex);
        return mQueue.size() == mMaxSize;
    }

    size_t Size()
    {
        std::lock_guard<std::mutex> locker(mMutex);
        return mQueue.size();
    }

    int Count()
    {
        return mQueue.size();
    }

private:
    bool NotFull() const
    {
        bool full = mQueue.size() >= mMaxSize;
        if (full)
            std::cout << "Buffer is full, please wait..." << std::endl;
        return !full;
    }

    bool NotEmpty() const
    {
        bool empty = mQueue.empty();
        if (empty)
            std::cout << "Buffer is empty, please wait...\n Async thread ID: "
                      << this_thread.get_id() << std::endl;

        return !empty;
    }

    template <typename F>
    void Add(F &&x)
    {
        std::unique_lock<std::mutex> locker(mMutex);
        mNotFull.wait(locker, [this] { return mNeedStop || NotFull(); });
        if (mNeedStop)
            return;
        mQueue.emplace_back(std::forward<F>(x));
        mNotEmpty.notify_one();
    }
};

#endif