#include <algorithm>
#include <bitset>
#include <numeric>
#include <vector>
using namespace std;

bool dfs(int index, int sum, vector<int> &nums, bitset<15> &track) {
  if (sum == 0) {
    return true;
  }

  for (size_t i = index; i < nums.size(); ++i) {
    if (!track[i] && (sum - nums[i] >= 0)) {
      track[i] = true;

      if (dfs(i + 1, sum - nums[i], nums, track)) {
        return true;
      }
      track[i] = false;
    }
  }
  return false;
}

bool makesquare(vector<int> &nums) {
  if (nums.size() == 0) {
    return false;
  }

  sort(nums.begin(), nums.end(), greater<int>());

  bitset<15> track;
  int side = accumulate(nums.begin(), nums.end(), 0) / 4;
  for (size_t i = 0; i < 3; ++i) {
    if (!dfs(0, side, nums, track)) {
      return false;
    }
  }
  return true;
}