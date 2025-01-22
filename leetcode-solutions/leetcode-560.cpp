/*
  Subarray sum equals k

  题目描述
  给定一个数组，寻找和为 k 的连续区间个数。

  题解
  本题同样是利用前缀和，不同的是这里我们使用一个哈希表 hashmap，其键是前缀和，而值是
  该前缀和出现的次数。在我们遍历到位置 i 时，假设当前的前缀和是 psum，那么 hashmap[psum-k]
  即为以当前位置结尾、满足条件的区间个数
 */
#include <unordered_map>
#include <vector>
using namespace std;

int subarraySum(vector<int>& nums, int k) {
  int count = 0, psum = 0;
  unordered_map<int, int> hashmap;
  hashmap[0] = 1;
  for (int i : nums) {
    psum += i;
    count += hashmap[psum - k];
    ++hashmap[psum];
  }

  return count;
}