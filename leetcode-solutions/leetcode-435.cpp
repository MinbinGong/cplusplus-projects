/*
    题目描述
    给定多个区间，计算让这些区间互不重叠所需要移除区间的最少个数。起止相连不算重叠。

    题解
    在选择要保留区间时，区间的结尾十分重要：选择的区间结尾越小，余留给其它区间的空间
    就越大，就越能保留更多的区间。因此，我们采取的贪心策略为，优先保留结尾小且不相交的区
    间。
    具体实现方法为，先把区间按照结尾的大小进行增序排序，每次选择结尾最小且和前一个选
    择的区间不重叠的区间。我们这里使用 C++ 的 Lambda，结合 std::sort() 函数进行自定义排
    序。
 */

#include <algorithm>
#include <vector>
using namespace std;

int eraseOverlapIntervals(vector<vector<int>> &intervals) {
  if (intervals.empty()) {
    return 0;
  }

  int ans{-1};
  sort(intervals.begin(), intervals.end(), [](auto &a, auto &b) { return a[1] < b[1]; });

  vector<int> prev{intervals[0]};
  for (const auto &i : intervals) {
    if (prev[1] > i[0]) {
      ans++;
    } else {
      prev = i;
    }
  }
  return ans;
}