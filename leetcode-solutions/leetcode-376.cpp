/*
 * @lc app=leetcode.cn id=376 lang=cpp
 * Wiggle Subsequence
 * A wiggle sequence is a sequence where the differences between successive numbers strictly alternate between positive and negative.
 * The first difference (if one exists) may be either positive or negative. 
 * A sequence with one element and a sequence with two non-equal elements are trivially wiggle sequences.
 * 
 * For example, [1, 7, 4, 9, 2, 5] is a wiggle sequence because the differences (6, -3, 5, -7, 3) alternate between positive and negative.
 * In contrast, [1, 4, 7, 2, 5] and [1, 7, 4, 5, 5] are not wiggle sequences.
 * The first is not because its first two differences are positive, and the second is not because its last difference is zero.
 * A subsequence is obtained by deleting some elements (possibly zero) from the original sequence,
 * leaving the remaining elements in their original order.
 * 
 * Given an integer array nums, return the length of the longest wiggle subsequence of nums.
 */
#include <vector>
using namespace std;

int wiggleMaxLength(vector<int> &nums) {
  int len = nums.size();
  if (len == 0 || len == 1) return len;

  // vector<int> copy=nums;
  vector<bool> dp;
  for (int i = 0; i < len - 1; i++) {
    int diff = nums[i] - nums[i + 1];
    if (diff == 0)
      continue;
    else {
      if (diff < 0)
        dp.push_back(false);
      else
        dp.push_back(true);
    }
  }

  if (dp.size() == 0 || dp.size() == 1) return 1;

  int count = 1;
  bool cur = dp[0];
  for (int i = 1; i < dp.size(); i++) {
    if (dp[i] == !cur) {
      count++;
      cur = !cur;
    }
  }
  return count + 1;
}

int wiggleMaxLength2(vector<int> &nums) {
  int len = nums.size();
  if (len == 0 || len == 1) return len;
  int up = 1, down = 1;
  for (int i = 1; i < len; i++) {
    if (nums[i] > nums[i - 1]) {
      up = down + 1;
    } else if (nums[i] < nums[i - 1]) {
      down = up + 1;
    }
  }
  return max(up, down);
}