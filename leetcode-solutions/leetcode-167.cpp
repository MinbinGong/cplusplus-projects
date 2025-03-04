/*
题目描述
在一个增序的整数数组里找到两个数，使它们的和为给定值。已知有且只有一对解。

题解
因为数组已经排好序，我们可以采用方向相反的双指针来寻找这两个数字，一个初始指向最
小的元素，即数组最左边，向右遍历；一个初始指向最大的元素，即数组最右边，向左遍历。
如果两个指针指向元素的和等于给定值，那么它们就是我们要的结果。如果两个指针指向元
素的和小于给定值，我们把左边的指针右移一位，使得当前的和增加一点。如果两个指针指向元
素的和大于给定值，我们把右边的指针左移一位，使得当前的和减少一点。
 */
#include <vector>
using namespace std;

vector<int> twoSum(vector<int>& nums, int target) {
  int l = 0, r = nums.size() - 1, sum;
  while (l < r) {
      sum = numbers[l] + numbers[r];
      if (sum == target) {
          break;
      }

      if (sum < target) {
          ++l;
      } else {
          --r;
      }
  }
  return vector<int>{l+1, r+1};
}
