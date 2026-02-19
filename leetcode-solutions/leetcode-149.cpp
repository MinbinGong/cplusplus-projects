/*
 * Max Points on a Line
 * 
 * Given an array of points where points[i] = [xi, yi] represents a point on the X-Y plane, return the maximum number of points that lie on the same straight line.
 * 
 * Example 1: 
 * Input: points = [[1,1],[2,2],[3,3]]
 * Output: 3
 * 
 * Example 2:
 * Input: points = [[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]
 * Output: 4
 * 
 * Constraints:
 * 1 <= points.length <= 300
 * points[i].length == 2
 * -104 <= xi, yi <= 104
 * All the points are unique.
 */
#include <unordered_map>
#include <vector>
using namespace std;

int maxPoints(vector<vector<int>>& points) {
  unordered_map<double, int> hash;
  int maxCount = 0, same = 1, sameY = 1;
  for (int i = 0; i < points.size(); ++i) {
    same = 1, sameY = 1;
    for (int j = i + 1; j < points.size(); ++j) {
      if (points[i][1] == points[j][1]) {
        ++sameY;
        if (points[i][0] == points[j][0]) {
          ++same;
        }
      } else {
        double dx = points[i][0] - points[j][0], dy = points[i][1] - points[j][1];
        ++hash[dx / dy];
      }
    }

    maxCount = max(maxCount, sameY);
    for (auto item : hash) {
      maxCount = max(maxCount, same + item.second);
    }
    hash.clear();
  }
  return maxCount;
}