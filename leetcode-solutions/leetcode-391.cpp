/*
 * Perfect Rectangle
 * 
 * Given an array rectangles where rectangles[i] = [xi, yi, ai, bi] represents an axis-aligned rectangle. The bottom-left point of the rectangle is (xi, yi) and the top-right point of it is (ai, bi).
 * 
 * Return true if all the rectangles together form an exact cover of a rectangular region.
 * 
 * Example 1:
 * Input: rectangles = [[1,1,3,3],[3,1,4,2],[3,2,4,4],[1,3,2,4],[2,3,3,4]]
 * Output: true
 * Explanation: All 5 rectangles together form an exact cover of a rectangular region.
 * 
 * Example 2:
 * Input: rectangles = [[1,1,2,3],[1,3,2,4],[3,1,4,2],[3,2,4,4]]
 * Output: false
 * Explanation: Because there is a gap between the two rectangular regions.
 * 
 * Example 3: 
 * Input: rectangles = [[1,1,3,3],[3,1,4,2],[1,3,2,4],[3,2,4,4]]
 * Output: false
 * Explanation: Because there is a gap between the two rectangular regions.
 * 
 * Example 4:
 * Input: rectangles = [[1,1,3,3],[3,1,4,2],[1,3,2,4],[2,2,4,4]]
 * Output: false
 * Explanation: Because two of the rectangles overlap with each other.
 * 
 */
#include <set>
#include <vector>
using namespace std;

bool isRectangleCover(vector<vector<int>> &rectangles) {
  set<pair<int, int>> Set;
  int area = 0;
  for (auto &x : rectangles) {
    pair<int, int> p1{x[0], x[1]};
    pair<int, int> p2{x[2], x[3]};
    pair<int, int> p3{x[0], x[3]};
    pair<int, int> p4{x[2], x[1]};

    area += (x[2] - x[0]) * (x[3] - x[1]);

    if (Set.count(p1)) {
      Set.erase(p1);
    } else {
      Set.insert(p1);
    }

    if (Set.count(p2)) {
      Set.erase(p2);
    } else {
      Set.insert(p2);
    }

    if (Set.count(p3)) {
      Set.erase(p3);
    } else {
      Set.insert(p3);
    }

    if (Set.count(p4)) {
      Set.erase(p4);
    } else {
      Set.insert(p4);
    }
  }
  return Set.size() == 4 &&
         area == ((*Set.rbegin()).second - (*Set.begin()).second) * ((*Set.rbegin()).first - (*Set.begin()).first);
}