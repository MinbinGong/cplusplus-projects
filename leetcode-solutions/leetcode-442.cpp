/*
 * Find All Duplicates in an Array
 *
 * Given an integer array nums of length n where all the integers of nums are in the range [1, n] and each integer appears once or twice, return an array of all the integers that appears twice.
 * 
 * You must write an algorithm that runs in O(n) time and uses only constant extra space.
 * 
 * Constraints:
 * n == nums.length
 * 1 <= n <= 105
 * 1 <= nums[i] <= n
 * Each element in nums appears once or twice.
 * 
 */
#include <vector>
using namespace std;

vector<int> findDuplicates(vector<int> &nums) {
  vector<int> ans{};
  for (size_t i = 0; i < nums.size(); i++) {
    nums[abs(nums[i]) - 1] = -nums[abs(nums[i]) - 1];
    if (nums[abs(nums[i]) - 1] > 0) {
      ans.push_back(abs(nums[i]));
    }
  }
  return ans;
}