/*
 * @lc app=leetcode.cn id=583 lang=cpp
 * Product of Array Except Self
 * Given an integer array nums, return an array answer
 * such that answer[i] is equal to the product of all the elements of nums except nums[i].
 * 
 * The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.
 * 
 * You must write an algorithm that runs in O(n) time and without using the division operation.
 */
#include <vector>
using namespace std;
class Solution {
 public:
  vector<int> productExceptSelf(vector<int>& nums) {
    int n = nums.size();
    vector<int> ans(n, 1);
    for (int i = 1; i < n; i++) {
      ans[i] = ans[i - 1] * nums[i - 1];
    }
    int right = 1;
    for (int i = n - 1; i >= 0; i--) {
      ans[i] *= right;
      right *= nums[i];
    }
    return ans;
  }
};