/*
 * Find All Numbers Disappeared in an Array
 *
 * Given an array nums of n integers where nums[i] is in the range [1, n], return an array of all the integers in the range [1, n] that do not appear in nums.
 *
 * Constraints:
 * n == nums.length
 * 1 <= n <= 105
 * 1 <= nums[i] <= n
 *
 * Follow up: Could you do it without extra space and in O(n) runtime? You may assume the returned list does not count as extra space.
 */
#include <cmath>
#include <vector>
using namespace std;

vector<int> findDisappearedNumbers(vector<int>& nums) {
  int n = nums.size();

  for (size_t i = 0; i < n; i++) {
    while (nums[i] != i + 1) {
      if (nums[i] != nums[nums[i] - 1]) {
        swap(nums[i], nums[nums[i] - 1]);
      } else {
        break;
      }
    }
  }

  vector<int> res;
  for (size_t i = 0; i < n; i++) {
    if (nums[i] != i + 1) {
      res.push_back(i + 1);
    }
  }

  return res;
}

vector<int> findDisappearedNumbers1(vector<int>& nums) {
  for (const int& num : nums) {
    int pos = abs(num) - 1;
    if (nums[pos] > 0) {
      nums[pos] = -nums[pos];
    }
  }

  vector<int> ans{};
  for (int i = 0; i < nums.size(); ++i) {
    if (nums[i] > 0) {
      ans.push_back(i + 1);
    }
  }
  return ans;
}