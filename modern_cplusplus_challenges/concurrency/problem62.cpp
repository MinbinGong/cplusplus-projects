#include <algorithm>
#include <thread>
#include <vector>

template <typename Iterator, typename F>
auto pprocess(Iterator begin, Iterator end, F &&f) {
  auto size = std::distance(begin, end);
  if (size <= 10000) {
    return std::forward<F>(f)(begin, end);
  } else {
    int thread_count = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;
    std::vector<typename std::iterator_traits<Iterator>::value_type> mins(thread_count);

    auto first = begin;
    auto last = end;
    size /= thread_count;
    for (size_t i = 0; i < thread_count; i++) {
      first = last;
      if (i == thread_count - 1) {
        last = end;
      } else {
        std::advance(last, size);
      }

      threads.emplace_back([first, last, &f, &r = mins[i]]() { r = std::forward<F>(f)(first, last); });
    }

    for (auto &t : threads) {
      t.join();
    }

    return std::forward<F>(f)(std::begin(mins), std::end(mins));
  }
}

template <typename Iterator>
auto pmin(Iterator begin, Iterator end) {
  return pprocess(begin, end, [](auto b, auto e) { return *std::min_element(b, e); });
}

template <typename Iterator>
auto pmax(Iterator begin, Iterator end) {
  return pprocess(begin, end, [](auto b, auto e) { return *std::max_element(b, e); });
}
