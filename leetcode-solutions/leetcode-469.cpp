/*
 * Convex Polygon
 *
 *  Given a list of points that form a polygon when joined sequentially, find if this polygon is convex (Convex polygon definition).
 *
 *  Note:
 *  There are at least 3 and at most 10,000 points.
 *  Coordinates are in the range -10,000 to 10,000.
 *  You may assume the polygon formed by given points is always a simple polygon (Simple polygon definition). In other words, we ensure that exactly two edges intersect at each vertex, and that edges otherwise don't intersect each other.
 *
 *  Constraints:
 *  3 <= points.length <= 10000
 *  -10000 <= points[i][0] <= 10000
 *  -10000 <= points[i][1] <= 10000
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    bool isConvex(vector<vector<int>>& points) {
        int n = points.size();
        long long prev = 0;
        bool hasNonZero = false;
        for (int i = 0; i < n; ++i) {
            int x1 = points[i][0], y1 = points[i][1];
            int x2 = points[(i + 1) % n][0], y2 = points[(i + 1) % n][1];
            int x3 = points[(i + 2) % n][0], y3 = points[(i + 2) % n][1];
            long long cross = (long long)(x2 - x1) * (y3 - y2) - (long long)(y2 - y1) * (x3 - x2);
            if (cross != 0) {
                if (prev * cross < 0) return false;
                prev = cross;
                hasNonZero = true;
            }
        }
        return hasNonZero;
    }
};