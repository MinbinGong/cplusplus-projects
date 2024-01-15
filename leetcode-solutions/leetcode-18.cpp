/*
 * Given an array nums of n integers, return an array of all the unique quadruplets [nums[a], nums[b], nums[c], nums[d]]
 * such that:
 *      0 <= a, b, c, d < n
 *      a, b, c, and d are distinct.
 *      nums[a] + nums[b] + nums[c] + nums[d] == target
 *
 * You may return the answer in any order.
 */
#include <algorithm>
#include <set>
#include <vector>
/*

    Time Complexity : O(N^4), Here Four nested loop creates the time complexity. Where N is the size of the
    array(nums).

    Space Complexity : O(N), Hash Table(set) space.

    Solved using Array(Four Nested Loop) + Sorting + Hash Table(set). Brute Force Approach.

    Note : this will give TLE.

*/
std::vector<std::vector<int>> fourSum(std::vector<int>& nums, int target) {
  int n = nums.size();
  std::sort(nums.begin(), nums.end());
  std::set<std::vector<int>> set;
  std::vector<std::vector<int>> output;

  for (int i = 0; i < n - 3; i++) {
    for (int j = i + 1; j < n - 2; j++) {
      for (int k = j + 1; k < n - 1; k++) {
        for (int l = k + 1; l < n; l++) {
          if ((long long)nums[i] + (long long)nums[j] + (long long)nums[k] + (long long)nums[l] == target) {
            set.insert({nums[i], nums[j], nums[k], nums[l]});
          }
        }
      }
    }
  }

  for (auto it : set) {
    output.push_back(it);
  }

  return output;
}