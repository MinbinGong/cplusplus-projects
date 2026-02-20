/*
 * Longest Increasing Subsequent
 *
 * Given an unsorted array of integers, find the length of longest increasing subsequence.
 * 
 * Example:
 * Input: [10,9,2,5,3,7,101,18]
 * Output: 4 
 * Explanation: The longest increasing subsequence is [2,3,7,101], therefore the length is 4. 
 * 
 */

#include <iterator>
#include <vector>
using namespace std;

int lengthOfLIS(vector<int>& nums) {
  vector<int> dp;
  for (const auto& num : nums) {
    auto up = lower_bound(nums.begin(), nums.end(), num);
    if (up != dp.end()) {
      *up = num;
    } else {
      dp.emplace_back(num);
    }
  }
  return dp.size();
}