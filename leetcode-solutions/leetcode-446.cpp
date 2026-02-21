/*
 * Arithmetic Slices II - Subsequence
 *
 *  A sequence of numbers is called arithmetic if it consists of at least three elements and if the difference between any two consecutive elements is the same.
 * 
 *  For example, [1, 3, 5, 7, 9], [7, 7, 7, 7], and [3, -1, -5, -9] are arithmetic sequences.
 *  Given an integer array nums, return the number of arithmetic subsequences of nums.
 * 
 *  A subsequence of an array is a sequence that can be derived from the array by deleting some or no elements without changing the order of the remaining elements. For example, [2,5,10] is a subsequence of [1,2,1,2,4,1,5,10].
 * 
 *  Constraints:
 *  1  <= nums.length <= 1000
 *  -231 <= nums[i] <= 231 - 1
 * 
 */
#include <unordered_map>
#include <vector>
using namespace std;

int numberOfArithmethicsSlices(vector<int> &A) {
  int res = 0;
  unordered_map<int, vector<int>> a_idx;
  vector<vector<int>> dp(A.size(), vector<int>(A.size()));
  for (size_t i = 0; i < A.size(); i++) {
    a_idx[A[i]].push_back(i);
  }

  for (size_t i = 0; i < A.size(); i++) {
    for (size_t j = 0; j < i; j++) {
      auto prev = 2l * A[j] - A[i];
      if (prev < INT_MIN || prev > INT_MAX) {
        continue;
      }
      auto it = a_idx.find(prev);
      if (it != a_idx.end()) {
        for (auto k : it->second) {
          if (k >= j) {
            break;
          }
          dp[i][j] += dp[j][k] + 1;
        }
      }
      res += dp[i][j];
    }
  }
  return res;
}