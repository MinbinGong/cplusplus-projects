/*
 * Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]]
 * such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.
 * Notice that the solution set must not contain duplicate triplets.
 */

#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

std::vector<std::vector<int>> threeSum1(std::vector<int>& nums) {
  int n = nums.size();
  std::sort(nums.begin(), nums.end());
  std::set<std::vector<int>> set;
  std::vector<std::vector<int>> output;

  for (int i = 0; i < n - 2; i++) {
    for (int j = i + 1; j < n - 1; j++) {
      for (int k = j + 1; k < n; k++) {
        if ((nums[i] + nums[j] + nums[k] == 0) && (i != j && j != k && k != i)) {
          set.insert({nums[i], nums[j], nums[k]});
        }
      }
    }
  }

  for (auto it : set) {
    output.push_back(it);
  }

  return output;
}

std::vector<std::vector<int>> threeSum2(std::vector<int>& nums) {
  int n = nums.size();
  std::sort(nums.begin(), nums.end());
  std::set<std::vector<int>> set;
  std::vector<std::vector<int>> output;

  for (int i = 0; i < n - 2; i++) {
    int low = i + 1, high = n - 1;
    while (low < high) {
      if (nums[i] + nums[low] + nums[high] < 0) {
        low++;
      } else if (nums[i] + nums[low] + nums[high] > 0) {
        high--;
      } else {
        set.insert({nums[i], nums[low], nums[high]});
        low++;
        high--;
      }
    }
  }

  for (auto it : set) {
    output.push_back(it);
  }

  return output;
}

std::vector<std::vector<int>> threeSum3(std::vector<int>& nums) {
  int n = nums.size();
  std::sort(nums.begin(), nums.end());
  std::vector<std::vector<int>> output;

  for (int i = 0; i < n - 1; i++) {
    int low = i + 1, high = n - 1;
    while (low < high) {
      if (nums[i] + nums[low] + nums[high] < 0) {
        low++;
      } else if (nums[i] + nums[low] + nums[high] > 0) {
        high--;
      } else {
        output.push_back({nums[i], nums[low], nums[high]});

        int tempIndex1 = low, tempIndex2 = high;
        while (low < high && nums[low] == nums[tempIndex1]) {
          low++;
        }
        while (low < high && nums[high] == nums[tempIndex2]) {
          high--;
        }
      }
    }
    while (i + 1 < n && nums[i] == nums[i + 1]) {
      i++;
    }
  }

  return output;
}