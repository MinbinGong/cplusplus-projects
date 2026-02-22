/*
 * Erect the Fence
 *
 * You are given an array trees where trees[i] = [xi, yi] represents the location of a tree in the garden.
 *
 * You are asked to fence the entire garden using the minimum length of rope as it is expensive. The garden is well
 * fenced only if all the trees are enclosed.
 *
 * Return the coordinates of trees that are exactly located on the fence perimeter.
 *
 * Example:
 * Input: points = [[1,1],[2,2],[2,0],[2,4],[3,3],[4,2]]
 * Output: [[1,1],[2,0],[3,3],[2,4],[4,2]]
 *
 * Input: points = [[1,2],[2,2],[4,2]]
 * Output: [[4,2],[2,2],[1,2]]
 *
 * Note:
 * 1 <= points.length <= 3000
 * points[i].length == 2
 * 0 <= xi, yi <= 100
 * All the given points are unique.
 *
 */

#include <algorithm>
#include <set>
#include <vector>
using namespace std;

struct Point {
  int x;
  int y;
  Point() : x(0), y(0) {}
  Point(int a, int b) : x(a), y(b) {}
};

class Solution {
 public:
  vector<Point> outerTrees(vector<Point>& points) {
    int n = points.size();
    if (n <= 1) return points;

    // Sort points lexicographically (by x, then by y)
    sort(points.begin(), points.end(),
         [](const Point& a, const Point& b) { return a.x < b.x || (a.x == b.x && a.y < b.y); });

    // Build the lower hull
    vector<Point> hull;
    for (int i = 0; i < n; ++i) {
      while (hull.size() >= 2 && cross(hull[hull.size() - 2], hull.back(), points[i]) < 0) {
        hull.pop_back();
      }
      hull.push_back(points[i]);
    }

    // Build the upper hull
    for (int i = n - 2, lower_size = hull.size(); i >= 0; --i) {
      while (hull.size() > lower_size && cross(hull[hull.size() - 2], hull.back(), points[i]) < 0) {
        hull.pop_back();
      }
      hull.push_back(points[i]);
    }

    // Remove duplicates (the starting point is added twice)
    hull.pop_back();

    // Use set to remove any remaining duplicates (collinear points may appear twice)
    set<pair<int, int>> unique;
    for (const Point& p : hull) {
      unique.insert({p.x, p.y});
    }

    vector<Point> result;
    for (auto& p : unique) {
      result.push_back(Point(p.first, p.second));
    }
    return result;
  }

 private:
  // Cross product (p × q × r) > 0 means counter-clockwise turn
  // < 0 means clockwise turn, = 0 means collinear
  int cross(const Point& p, const Point& q, const Point& r) {
    return (q.x - p.x) * (r.y - p.y) - (q.y - p.y) * (r.x - p.x);
  }
};