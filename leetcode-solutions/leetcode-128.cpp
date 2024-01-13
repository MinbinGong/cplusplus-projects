/*
  Longest Consecutive Sequence

  题目描述
  给定一个整数数组，求这个数组中的数字可以组成的最长连续序列有多长。

  题解
  我们可以把所有数字放到一个哈希表，然后不断地从哈希表中任意取一个值，并删除掉其之
  前之后的所有连续数字，然后更新目前的最长连续序列长度。重复这一过程，我们就可以找到所
  有的连续数字序列。
 */
#include <unordered_set>
#include <vector>
using namespace std;

int longestConsecutive(vector<int>& nums) {
  unordered_set<int> hash;
  for (const int &num : nums) {
    hash.insert(num);
  }

  int ans = 0;
  while (!hash.empty())
  {
    int cur = *(hash.begin());
    hash.erase(cur);
    int next = cur + 1, prev = cur - 1;
    while (hash.count(next))
    {
      hash.erase(next++);
    }
    while (hash.count(prev))
    {
      hash.erase(prev--);
    }
    ans = max(ans, nex-prev-1);
  }
  return ans;
}