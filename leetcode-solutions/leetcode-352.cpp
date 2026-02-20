/*
 * Data Stream as Disjoint Intervals
 * 
 * Given a data stream input of non-negative integers a1, a2, ..., an, summarize the numbers seen so far as a list of disjoint intervals.
 * 
 * Implement the SummaryRanges class:
 * 
 * SummaryRanges() Initializes the object with an empty stream.
 * void addNum(int val) Adds the integer val to the stream.
 * int[][] getIntervals() Returns a summary of the integers in the stream currently as a list of disjoint intervals [starti, endi].
 * 
 * Example 1:
 * Input
 * ["SummaryRanges", "addNum", "getIntervals", "addNum", "getIntervals", "addNum", "getIntervals", "addNum", "getIntervals", "addNum", "getIntervals"]
 * [[], [1], [], [3], [], [7], [], [2], [], [6], []]
 * Output
 * [null, null, [[1, 1]], null, [[1, 1], [3, 3]], null, [[1, 1], [3, 3], [7, 7]], null, [[1, 3], [7, 7]], null, [[1, 3], [6, 7]]]
 * 
 */
#include <set>
#include <utility>
#include <vector>
using namespace std;

class SummaryRanges {
  set<pair<int, int>> s;
  set<int> ins;

 public:
  /** Initialize your data structure here. */
  SummaryRanges() {}

  void addNum(int val) {
    if (ins.count(val)) return;
    ins.insert(val);
    auto lb = s.lower_bound({val, -1e9});
    auto prv = lb;
    if (prv != s.begin()) prv--;
    if (prv != s.end() && lb != s.end() && prv->second == val - 1 && lb->first == val + 1) {
      s.insert({prv->first, lb->second});
      s.erase(prv);
      s.erase(lb);
    } else if (prv != s.end() && prv->second == val - 1) {
      s.insert({prv->first, val});
      s.erase(prv);
    } else if (lb != s.end() && lb->first == val + 1) {
      s.insert({val, lb->second});
      s.erase(lb);
    } else {
      s.insert({val, val});
    }
  }

  vector<vector<int>> getIntervals() {
    vector<vector<int>> v;
    for (auto x : s) v.push_back({x.first, x.second});
    return v;
  }
};