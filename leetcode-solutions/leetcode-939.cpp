/*
 * Minimum Area Rectangle
 *
 * Given a set of points in the xy-plane, determine the minimum area of a rectangle formed from these points, with sides parallel to the x and y axes.
 *
 * If there isn't any rectangle, return 0.
 *
 * Example 1:
 * Input: [[1,1],[1,3],[3,1],[3,3],[2,2]]
 * Output: 4
 * 
 * Example 2:
 * Input: [[1,1],[1,3],[3,1],[3,3],[4,1],[4,3]]
 * Output: 2
 * 
 * Note:
 * 1 <= points.length <= 500
 * 0 <= points[i][0] <= 40000
 * 0 <= points[i][1] <= 40000
 * All points are distinct.
 * 
 */
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

class Solution {
public:
    int minAreaRect(vector<vector<int>>& points) {
        // 使用整数编码存储点，加速查找
        unordered_set<int> pointSet;
        for (const auto& p : points) {
            // 将坐标编码为一个整数：x * 40001 + y
            // 40001 是因为坐标范围是 [0, 40000]
            pointSet.insert(p[0] * 40001 + p[1]);
        }

        int n = points.size();
        int minArea = INT_MAX;

        // 枚举所有点对作为矩形的对角线
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int x1 = points[i][0], y1 = points[i][1];
                int x2 = points[j][0], y2 = points[j][1];

                // 对角线两个点不能共线（必须有不同的 x 和 y 坐标）
                if (x1 == x2 || y1 == y2) continue;

                // 检查矩形的另外两个点 (x1, y2) 和 (x2, y1) 是否存在
                int p1 = x1 * 40001 + y2;
                int p2 = x2 * 40001 + y1;

                if (pointSet.count(p1) && pointSet.count(p2)) {
                    int area = abs(x1 - x2) * abs(y1 - y2);
                    minArea = min(minArea, area);
                }
            }
        }

        return minArea == INT_MAX ? 0 : minArea;
    }
};