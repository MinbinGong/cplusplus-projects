/*
 * Range Sum Array
 *
 * Given an integer array nums, find the sum of the elements between indices i and j (i ≤ j), inclusive.
 * 
 * Example:
 * Given nums = [-2, 0, 3, -5, 2, -1]
 * sumRange(0, 2) -> 1
 * sumRange(2, 5) -> -1
 * sumRange(0, 5) -> -3
 * 
 * Note:
 * You may assume that the array does not change.
 * There are many calls to sumRange function.
 * 
 */
#include <numeric>
#include <vector>
using namespace std;

class NumArr {
  vector<int> psum;

 public:
  NumArr(vector<int> &nums) : psum(nums.size() + 1, 0) { partial_sum(nums.begin(), nums.end(), psum.begin() + 1); }

  int sumRange(int i, int j) { return psum[j + 1] - psum[i]; }
};