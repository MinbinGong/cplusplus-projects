/*
 * Minimum Moves to Equal Array Elements II
 *
 * Given an integer array nums of size n, return the minimum number of moves required to make all array elements equal.
 *
 * In one move, you can increment or decrement an element of the array by 1.
 *
 * Test cases are designed so that the answer will fit in a 32-bit integer.
 *
 * Constraints:
 * n == nums.length
 * 1 <= nums.length <= 105
 * -109 <= nums[i] <= 109
 * 
 */
#include <algorithm>
#include <vector>
using namespace std;

int minMove2(vector<int> &nums) {
  int ans{0};

  sort(nums.begin(), nums.end());

  int x = nums[nums.size() / 2];
  for (int num : nums) {
    ans += abs(x - num);
  }

  return ans;
}