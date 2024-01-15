#include <algorithm>
#include <vector>
using namespace std;

struct info {
  int start;
  int end;
  int index;
};

vector<int> findRightInterval(vector<vector<int>> &intervals) {
  int n = intervals.size();
  vector<info> intervalsinfo;
  for (size_t i = 0; i < n; i++) {
    intervalsinfo.push_back({intervals[i][0], intervals[i][1], i});
  }
  sort(intervalsinfo.begin(), intervalsinfo.end(), [](const auto &a, const auto &b) { return a.start < b.start; });

  vector<int> result(n, -1);
  for (size_t i = 0; i < n; i++) {
    auto temp = lower_bound(intervalsinfo.begin() + i + 1, intervalsinfo.end(), intervalsinfo[i].end,
                            [](auto &it, int val) { return it.start < val; });
    result[intervalsinfo[i].index] = (temp == intervalsinfo.end()) ? -1 : temp->index;
  }
  return result;
}