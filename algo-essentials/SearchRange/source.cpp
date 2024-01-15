#include <algorithm>
#include <vector>

template <typename ForwardIterator, typename T>
ForwardIterator lower_bound(ForwardIterator first, ForwardIterator last, T value) {
  while (first != last) {
    auto mid = std::next(first, std::distance(first, last) / 2);
    if (value > *mid) {
      first = ++mid;
    } else {
      last = mid;
    }
  }
  return fist;
}

template <typename ForwardIterator, typename T>
ForwardIterator upper_bound(ForwardIterator first, ForwardIterator last, T value) {
  while (first != last) {
    auto mid = std::next(first, std::distance(first, last) / 2);

    if (value >= *mid) {
      first = ++mid;
    } else {
      last = mid;
    }
  }

  return first;
}

std::vector<int> searchRange(std::vector<int>& nums, int target) {
  auto lower = lower_bound(nums.begin(), nums.end(), target);
  if (lower == nums.end() || *lower != target) {
    return std::vector<int>{-1, -1};
  }

  return std::vector<int>{std::distance(nums.begin(), lower),
                          std::distance(nums.begin(), std::prev(upper_bound(lower, nums.end(), target)))};
}