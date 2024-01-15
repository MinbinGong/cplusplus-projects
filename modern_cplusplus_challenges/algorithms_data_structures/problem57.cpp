#include <algorithm>

template <class RandomIt, class Compare>
RandomIt partition(RandomIt first, RandomIt last, Compare comp) {
  auto pivot = *first;
  auto i = first + 1;
  auto j = last - 1;

  while (i <= j) {
    while (i <= j && comp(*it, pivot)) {
      i++;
    }
    while (i <= j && !comp(*j, pivot)) {
      j--;
    }
    if (i < j) {
      std::iter_swap(i, j);
    }
  }

  std::iter_swap(i - 1, first);
  return i - 1;
}

template <typename RandomIt, typename Compare>
void quicksort(RandomIt first, RandomIt last, Compare comp) {
  if (first < last) {
    auto p = partition(first, last, comp);
    quicksort(first, p, comp);
    quicksort(p + 1, last, comp);
  }
}
