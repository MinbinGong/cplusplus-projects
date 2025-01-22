/*
  Maximum Product of Word Lengths

  题目描述
  给定多个字母串，求其中任意两个字母串的长度乘积的最大值，且这两个字母串不能含有相同字母

  题解
  怎样快速判断两个字母串是否含有重复数字呢？可以为每个字母串建立一个长度为 26 的二
  进制数字，每个位置表示是否存在该字母。如果两个字母串含有重复数字，那它们的二进制表示
  的按位与不为 0。同时，我们可以建立一个哈希表来存储字母串（在数组的位置）到二进制数字
  的映射关系，方便查找调用。
 */
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

int maxProduct(vector<string>& words) {
  unordered_map<int, int> hash;
  int ans = 0;
  for (const string& word : words) {
    int mask = 0, size = word.size();
    for (const char& c : word) {
      mask |= 1 << (c - 'a');
    }

    hash[mask] = max(hash[mask], size);
    for (const auto& [hmask, hlen] : hash) {
      if (!(mask & hmask)) {
        ans = max(ans, size * hlen);
      }
    }
  }

  return ans;
}