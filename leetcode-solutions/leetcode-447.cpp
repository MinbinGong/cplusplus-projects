/*
 * Number of Boomerangs
 *
 * You are given n points in the plane that are all distinct, where points[i] = [xi, yi]. A boomerang is a tuple of points (i, j, k) such that the distance between i and j equals the distance between i and k (the order of the tuple matters).
 * 
 * Return the number of boomerangs.
 * 
 * Constraints:
 * n == points.length
 * 1 <= n <= 500
 * points[i].length == 2
 * -104 <= xi, yi <= 104
 * All the points are unique.
 * 
 */
#include <unordered_map>
#include <vector>
using namespace std;

int numberOfBoomerangs(vector<vector<int>> &points) {
  int n = points.size();
  int cnt = 0, tmp = 0;
  for (int i = 0; i < n; ++i) {
    unordered_map<int, int> m;
    for (int j = 0; j < n; ++j) {
      if (j == i) continue;
      tmp = pow(points[i][0] - points[j][0], 2) + pow(points[i][1] - points[j][1], 2);
      m[tmp]++;
    }
    for (auto &[key, value] : m) cnt += value * (value - 1);  // C(n,2)
  }
  return cnt;
}