#include <algorithm>
#include <thread>
#include <vector>

template <typename RandomAccessIterator, typename F>
void ptransform(RandomAccessIterator begin, RandomAccessIterator end, F &&f) {
  auto size = std::distance(begin, end);
  if (size <= 10000) {
    std::transform(begin, end, begin, std::forward<F>(f));
  } else {
    std::vector<std::thread> threads;
    int thread_count = std::thread::hardware_concurrency();
    auto first = begin;
    auto last = first;
    size /= thread_count;
    for (int i = 0; i < thread_count; i++) {
      first = last;
      if (i == thread_count - 1) {
        last = end;
      } else {
        std::advance(last, size);
      }

      threads.emplace_back([first, last, &f]() { std::transform(first, last, first, std::forward<F>(f)); });
    }

    for (auto &t : threads) {
      t.join();
    }
  }
}

template <typename T, typename F>
std::vector<T> palter(std::vector<T> data, F &&f) {
  ptransform(std::begin(data), std::end(data), std::forward<F>(f));
  return data;
}
