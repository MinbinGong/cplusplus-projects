/*
 * @lc app=leetcode.cn id=287 lang=cpp
 * Find the duplicate number
 *   Given an array of integers nums containing n + 1 integers
 *   where each integer is in the range [1, n] inclusive.
 *   There is only one repeated number in nums, return this repeated number.
 *   You must solve the problem without modifying the array nums and using only constant extra space.
 */
#include <iostream>
#include <vector>
using namespace std;

int findDuplicate(vector<int> &nums) {
  int n = nums.size();
  if (n == 0) return -1;
  int slow = 0, fast = 0;
  while (1) {
    slow = nums[slow];
    fast = nums[nums[fast]];
    if (slow == fast) break;
  }
  slow = 0;
  while (1) {
    slow = nums[slow];
    fast = nums[fast];
    if (slow == fast) return fast;
  }
  return -1;
}

int main() {
  vector<int> nums = {1, 3, 4, 2, 2};
  cout << findDuplicate(nums) << endl;
  return 0;
}