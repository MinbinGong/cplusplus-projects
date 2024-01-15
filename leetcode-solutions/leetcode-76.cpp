/*
题目描述
给定两个字符串 S 和 T，求 S 中包含 T 所有字符的最短连续子字符串的长度，同时要求时间复杂度不得超过 O(n)。

题解
本题使用滑动窗口求解，即两个指针 l 和 r 都是从最左端向最右端移动，且 l 的位置一定在r 的左边或重合。
注意本题虽然在 for 循环里出现了一个 while 循环，但是因为 while 循环负责移动 l 指针，且 l 只会从左到右移动一次，
因此总时间复杂度仍然是 O(n)。本题使用了长度为 128的数组来映射字符，也可以用哈希表替代；
其中 chars 表示目前每个字符缺少的数量，flag 表示每个字符是否在 T 中存在。
 */
#include <string>
#include <vector>
using namespace std;

string minWindow(string& src, string& target) {
  vector<int> chars(128, 0);
  vector<bool> flag(128, false);

  // 先统计target中字符的情况
  for (int i = 0; i < target.size(); i++) {
    flag[target[i]] = true;
    ++chars[target[i]];
  }

  int cnt = 0, l = 0, minLeft = 0, minSize = src.size() + 1;
  for (int r = 0; r < src.size(); r++) {
    if (flag[src[r]]) {
      if (--chars[src[r]] >= 0) {
        ++cnt;
      }
      // 若目前滑动窗口已包含target中全部字符
      // 则尝试将l右移，在不影响结果的情况下获得最短子字符串
      while (cnt == target.size()) {
        if (r - l + 1 < minSize) {
          minLeft = l;
          minSize = r - l + 1;
        }
        if (flag[src[l]] && ++chars[src[l]] > 0) {
          --cnt;
        }
        ++l;
      }
    }
  }
  return minSize > src.size() ? "" : src.substr(minLeft, minSize);
}