/*
 * 963. Minimum Area Rectangle II
 *
 * Given a set of points in the xy-plane, determine the minimum area of any rectangle formed from these points, with sides not necessarily parallel to the x and y axes.
 *
 * If there isn't any rectangle, return 0.
 *
 * Example 1:
 *
 * Input: [[1,2],[2,1],[1,0],[0,1]]
 * Output: 2.00000
 * Explanation: The minimum area rectangle occurs at [1,2],[2,1],[1,0],[0,1], with an area of 2.
 * 
 * Example 2:
 *
 * Input: [[0,1],[2,1],[1,1],[1,0],[2,0]]
 * Output: 1.00000
 * Explanation: The minimum area rectangle occurs at [1,0],[1,1],[2,1],[2,0], with an area of 1.
 * 
 * Example 3:
 *
 * Input: [[0,3],[1,2],[3,1],[1,3],[2,1]]
 * Output: 0.00000
 * Explanation: There are no rectangles to form.
 * 
 * Example 4:
 *
 * Input: [[3,1],[1,1],[0,1],[2,1],[3,3],[3,2],[0,2],[2,3]]
 * Output: 2.00000
 * Explanation: The minimum area rectangle occurs at [2,1],[2,3],[3,3],[3,1], with an area of 2.
 * 
 * Note:
 *
 * 4 <= points.length <= 100
 * 0 <= points[i][0] <= 40000
 * 0 <= points[i][1] <= 40000
 * All points are distinct.
 * Answers within 10^-5 of the actual value will be accepted as correct.
 * 
 */
#include <vector>
#include <unordered_map>
#include <cmath>
#include <limits>
#include <algorithm>

using namespace std;

class Solution {
public:
    double minAreaFreeRect(vector<vector<int>>& points) {
        int n = points.size();
        // 使用哈希表存储具有相同 (中点x, 中点y, 对角线长度平方) 的点对
        // 键通过字符串组合，以确保浮点数精度不会导致错误分组
        unordered_map<string, vector<pair<int, int>>> groups;

        // 步骤1：枚举所有点对，计算中点和对角线长度，并分组
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                long long x1 = points[i][0], y1 = points[i][1];
                long long x2 = points[j][0], y2 = points[j][1];

                // 计算中点（使用乘以2的方式避免浮点数，但为了后续叉积计算，这里仍使用double）
                // 为了精确分组，使用中点坐标乘以2和距离平方作为键，完全避免浮点数
                long long mx2 = x1 + x2; // 中点的两倍 x
                long long my2 = y1 + y2; // 中点的两倍 y
                long long dist2 = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2); // 距离平方

                // 生成唯一键
                string key = to_string(mx2) + "," + to_string(my2) + "," + to_string(dist2);
                groups[key].emplace_back(i, j);
            }
        }

        double min_area = numeric_limits<double>::max();

        // 步骤2：遍历每个分组，组内的点对都可以作为矩形的对角线
        for (const auto& [key, pairs] : groups) {
            int m = pairs.size();
            if (m < 2) continue; // 至少需要两条对角线才能构成矩形

            // 枚举组内的所有点对组合
            for (int p = 0; p < m; ++p) {
                for (int q = p + 1; q < m; ++q) {
                    int i1 = pairs[p].first, j1 = pairs[p].second;
                    int i2 = pairs[q].first, j2 = pairs[q].second;

                    // 获取四个点的坐标
                    const auto& a = points[i1];
                    const auto& b = points[j1];
                    const auto& c = points[i2];
                    const auto& d = points[j2];

                    // 步骤3：验证并计算面积
                    // 两条对角线为 ab 和 cd。矩形的边是 a-c 和 a-d 或类似组合。
                    // 取其中一个点作为基准，计算到另外两个点的向量，然后取叉积的绝对值即为面积。
                    // 但需要确保这四个点不重合且能形成矩形。由于它们属于同一个 (中点, 长度) 组，已经保证了对角线条件。
                    // 现在只需用任意一个点（例如 a）和它所在对角线的另一端点（b）以及另一条对角线的任一端点（c）来计算向量。
                    // 使用向量 a->c 和 a->b
                    double v1x = c[0] - a[0];
                    double v1y = c[1] - a[1];
                    double v2x = b[0] - a[0];
                    double v2y = b[1] - a[1];

                    // 矩形面积 = |v1 x v2|
                    double area = abs(v1x * v2y - v1y * v2x);
                    if (area > 1e-12) { // 忽略面积为0的情况（四点共线或重合）
                        min_area = min(min_area, area);
                    }
                }
            }
        }

        return min_area == numeric_limits<double>::max() ? 0.0 : min_area;
    }
};