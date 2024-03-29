#include <algorithm>
#include <vector>

int partition(std::vector<int>& nums, int left, int right) {
  int pivot = nums[left], l = left + 1, r = right;

  while (l <= r) {
    if (nums[l] < pivot && nums[r] > pivot) {
      std::swap(nums[l++], nums[r--]);
    }

    if (nums[l] >= pivot) {
      l++;
    }

    if (nums[r] <= pivot) {
      r--;
    }
  }

  std::swap(nums[left], nums[r]);
  return r;
}

int findKthLargest(std::vector<int>& nums, int k) {
  int left = 0, right = nums.size() - 1, kth = 0;
  while (true) {
    int idx = partition(nums, left, right);
    if (idx == k - 1) {
      kth = nums[idx];
      break;
    }

    if (idx < k - 1) {
      left = idx + 1;
    } else {
      right = idx - 1;
    }
  }

  return kth;
}
