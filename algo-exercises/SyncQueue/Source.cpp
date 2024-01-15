#include <condition_variable>
#include <iostream>
#include <list>
#include <mutex>
#include <thread>

template <typename T>
class SyncQueue {
 private:
  std::list<T> mQueue;
  std::mutex mMutex;
  std::condition_variable_any mNotEmpty;
  std::condition_variable_any mNotFull;
  int mMaxSize;

 private:
  bool isFull() const { return mQueue.size() == mMaxSize; }

  bool isEmpty() const { return mQueue.empty(); }

 public:
  SyncQueue(int maxSize) : mMaxSize(maxSize) {}

  void Put(const T& x) {
    std::lock_guard<std::mutex> locker(mMutex);
    while (isFull()) {
      std::cout << "Full, hold on... " << std::endl;
      mNotFull.wait(mMutex);
    }
    mQueue.push_back(x);
    mNotEmpty.notify_one();
  }

  void Take(T& x) {
    std::lock_guard<std::mutex> locker(mMutex);
    while (isEmpty()) {
      std::cout << "Empty, hold on..." << std::endl;
      mNotEmpty.wait(mMutex);
    }

    x = mQueue.front();
    mQueue.pop_front();
    mNotFull.notify_one();
  }

  bool Full() {
    std::lock_guard<std::mutex> locker(mMutex);
    return mQueue.size() == mMaxSize;
  }

  bool Empty() {
    std::lock_guard<std::mutex> locker(mMutex);
    return mQueue.empty();
  }

  size_t Size() {
    std::lock_guard<std::mutex> locker(mMutex);
    return mQueue.size();
  }

  int Count() { return mQueue.size(); }
};