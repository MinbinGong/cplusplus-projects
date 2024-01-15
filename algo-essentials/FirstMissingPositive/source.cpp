#include <algorithm>
#include <vector>

int firstMissingPositive(std::vector<int>& nums) {
  const int n = nums.size();

  for (size_t i = 0; i < n;) {
    if (nums[i] > 0 && nums[i] <= n && nums[i] != nums[nums[i] - 1]) {
      std::swap(nums[i], nums[nums[i] - 1]);
    } else {
      i++;
    }
  }

  for (size_t i = 0; i < n; i++) {
    if (nums[i] != i + 1) {
      return i + 1;
    }
  }
  return n + 1;
}