/*
  Max Chunks To Make Sorted

  题目描述
  给定一个含有 0 到 n 整数的数组，每个整数只出现一次，求这个数组最多可以分割成多少个
  子数组，使得对每个子数组进行增序排序后，原数组也是增序的。

  题解
  从左往右遍历，同时记录当前的最大值，每当当前最大值等于数组位置时，我们可以多一次
  分割。
  为什么可以通过这个算法解决问题呢？如果当前最大值大于数组位置，则说明右边一定有小
  于数组位置的数字，需要把它也加入待排序的子数组；又因为数组只包含不重复的 0 到 n，所以
  当前最大值一定不会小于数组位置。所以每当当前最大值等于数组位置时，假设为 p，我们可以
  成功完成一次分割，并且其与上一次分割位置 q 之间的值一定是 q + 1 到 p 的所有数字。
 */
#include <vector>
using namespace std;

int maxChunkToSorted(vector<int>& arr) {
  int chunks = 0, cur_max = 0;
  for (int i = 0; i < arr.size(); ++i) {
    cur_max = max(cur_max, arr[i]);
    if (cur_max == i) {
      ++chunks;
    }
  }
  return chunks;
}