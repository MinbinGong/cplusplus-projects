/*
 * Minimum Number of Arrows to Burst Balloons
 *
 * There are some spherical balloons taped onto a flat wall that represents the XY-plane. The balloons are represented as a 2D integer array points where points[i] = [xstart, xend] denotes a balloon whose horizontal diameter stretches between xstart and xend. You do not know the exact y-coordinates of the balloons.
 *
 * Arrows can be shot up directly vertically (in the positive y-direction) from different points along the x-axis. A balloon with xstart and xend is burst by an arrow shot at x if xstart <= x <= xend. There is no limit to the number of arrows that can be shot. A shot arrow keeps traveling up infinitely, bursting any balloons in its path.
 *
 * Given the array points, return the minimum number of arrows that must be shot to burst all balloons.
 *
 * Constraints:
 * 1 <= points.length <= 105
 * points[i].length == 2
 * -231 <= xstart < xend <= 231 - 1
 * 
 */
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