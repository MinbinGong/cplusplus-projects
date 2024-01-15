#include <algorithm>
#include <vector>
using namespace std;

int findMinArrowShots(vector<vector<int>> &points) {
  int n = points.size();
  if (n <= 0) {
    return 0;
  }

  sort(points.begin(), points.end(), [](auto &a, auto &b) {
    if (a[0] == b[0]) {
      return a[1] < b[1];
    }
    return a[0] < b[0];
  });

  int a{points[0][1]};
  int ans{1};
  for (size_t i = 0; i < n; i++) {
    if (a < points[i][0]) {
      ++ans;
      a = points[i][0];
    } else {
      a = min(a, points[i][1]);
    }
  }
  return ans;
}