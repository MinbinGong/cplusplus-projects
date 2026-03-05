/*
 * 1584. Min Cost to Connect All Points
 *
 * You are given an array points representing integer coordinates of some points on a 2D-plane, where points[i] = [xi, yi].
 * 
 * The cost of connecting two points [xi, yi] and [xj, yj] is the manhattan distance between them: |xi - xj| + |yi - yj|, where |val| denotes the absolute value of val.
 * 
 * Return the minimum cost to make all points connected. All points are connected if there is exactly one simple path between any two points.
 * 
 * Example 1:
 * Input: points = [[0,0],[2,2],[3,10],[5,2],[7,0]]
 * Output: 20
 * Explanation: We can connect the points as shown above to get the minimum cost of 20.
 * Notice that there is a unique path between every pair of points.
 * 
 * Example 2:
 * Input: points = [[3,12],[-2,5],[-4,1]]
 * Output: 18
 * Explanation: We can connect the points as shown above to get the minimum cost of 18.
 * 
 * Constraints:
 * 1 <= points.length <= 1000
 * -10^6 <= xi, yi <= 10^6
 * All pairs (xi, yi) are distinct.
 * 
 */
#include <vector>
#include <climits>
using namespace std;

class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        vector<int> minDist(n, INT_MAX); // 到当前生成树的最小距离
        vector<bool> inMST(n, false);
        minDist[0] = 0;
        int ans = 0;

        for (int i = 0; i < n; ++i) {
            // 选取未加入树且距离最小的点
            int u = -1;
            for (int j = 0; j < n; ++j) {
                if (!inMST[j] && (u == -1 || minDist[j] < minDist[u])) {
                    u = j;
                }
            }
            inMST[u] = true;
            ans += minDist[u];

            // 更新其他点的最小距离
            for (int v = 0; v < n; ++v) {
                if (!inMST[v]) {
                    int dist = abs(points[u][0] - points[v][0]) + abs(points[u][1] - points[v][1]);
                    if (dist < minDist[v]) {
                        minDist[v] = dist;
                    }
                }
            }
        }
        return ans;
    }
};