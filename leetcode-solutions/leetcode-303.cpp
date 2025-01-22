/*
  Range Sum Array

  题目描述
  设计一个数据结构，使得其能够快速查询给定数组中，任意两个位置间所有数字的和。

  题解
  对于一维的数组，我们可以使用前缀和来解决此类问题。先建立一个与数组 nums 长度相
  同的新数组 psum，表示 nums 每个位置之前前所有数字的和。psum 数组可以通过 C++ 自带的
  partial_sum 函数建立，也可以直接遍历一遍 nums 数组，并利用状态转移方程 psum[i] = psum[i-
  1] + nums[i] 完成统计。如果我们需要获得位置 i 和 j 之间的数字和，只需计算 psum[j+1] - psum[i]
  即可。
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