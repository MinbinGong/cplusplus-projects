#include <algorithm>
#include <thread>

template <typename RandomIt>
RandomIt partition(RandomIt first, RandomIt last) {
  auto pivot = *first;
  auto i = first + 1;
  auto j = last - 1;
  while (i <= j) {
    while (i <= j && *i <= pivot) {
      i++;
    }
    while (i <= j && *j > pivot) {
      j--;
    }

    if (i < j) {
      std::iter_swap(i, j);
    }
  }

  std::iter_swap(i - 1, first);
  return i - 1;
}

template <typename RandomIt>
void pquicksort(RandomIt first, RandomIt last) {
  if (first < last) {
    auto p = partition(first, last);
    if (last - first <= 10000) {
      pquicksort(first, p);
      pquicksort(p + 1, last);
    } else {
      auto f1 = std::async(std::launch::async, [first, p]() { pquicksort(first, p); });
      auto f2 = std::async(std::launch::async, [last, p]() { pquicksort(p + 1, last); });
      f1.wait();
      f2.wait();
    }
  }
}
