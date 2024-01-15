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