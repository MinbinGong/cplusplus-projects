#include <algorithm>
#include <vector>

void dfs(const std::vector<int>& nums, std::vector<int>& path, std::vector<std::vector<int>>& result, int gap,
         int start) {
  if (gap == 0) {
    result.push_back(path);
    return;
  }

  int previous = -1;
  for (size_t i = start; i < nums.size(); i++) {
    if (previous == nums[i]) {
      continue;
    }

    if (gap < nums[i]) {
      break;
    }

    previous = nums[i];

    path.push_back(nums[i]);
    dfs(nums, path, result, gap - nums[i], i + 1);
    path.pop_back();
  }
}

std::vector<std::vector<int>> combinationSum2(std::vector<int>& nums, int target) {
  std::sort(nums.begin(), nums.end());

  std::vector<std::vector<int>> result;
  std::vector<int> path;
  dfs(nums, path, result, target, 0);
  return result;
}