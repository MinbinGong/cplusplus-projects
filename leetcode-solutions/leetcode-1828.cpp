/*
 * 1828. Queries on Number of Points Inside a Circle
 * 
 * You are given an array points where points[i] = [xi, yi] is the coordinates of the ith point on a 2D plane. Multiple points can have the same coordinates.
 * 
 * You are also given an array queries where queries[j] = [xj, yj, rj] describes a circle centered at (xj, yj) with a radius of rj.
 * 
 * For each query queries[j], compute the number of points inside the jth circle. Points on the border of the circle are considered inside.
 * 
 * Return an array answer, where answer[j] is the answer to the jth query.
 * 
 * Example 1:
 * Input: points = [[1,3],[3,3],[5,3],[2,2]], queries = [[2,3,1],[4,3,1],[1,1,2]]
 * Output: [3,2,2]
 * Explanation: The points and circles are shown above.
 * 
 * Example 2:
 * Input: points = [[1,1],[2,2],[3,3],[4,4],[5,5]], queries = [[1,2,2],[2,2,2],[4,3,2],[4,3,3]]
 * Output: [2,3,2,4]
 * Explanation: The points and circles are shown above.
 * 
 * Constraints:
 * 
 * 1 <= points.length <= 500
 * points[i].length == 2
 * 0 <= xi, yi <= 500
 * 1 <= queries.length <= 500
 * queries[j].length == 3
 * 0 <= xj, yj <= 500
 * 1 <= rj <= 500
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> countPoints(vector<vector<int>>& points, vector<vector<int>>& queries) {
        vector<int> result;
        for (const auto& q : queries) {
            int x = q[0], y = q[1], r = q[2];
            int r2 = r * r;
            int cnt = 0;
            for (const auto& p : points) {
                int dx = p[0] - x;
                int dy = p[1] - y;
                if (dx * dx + dy * dy <= r2) {
                    ++cnt;
                }
            }
            result.push_back(cnt);
        }
        return result;
    }
};