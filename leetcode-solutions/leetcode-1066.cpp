/**
 * 1066. Campus Bikes II
 * 
 * On a campus represented as a 2D grid, there are N workers and M bikes, with N <= M. Each worker and bike is a 2D coordinate on this grid.
 * 
 * Our goal is to assign a bike to each worker. Among the available bikes and workers, we choose the (worker, bike) pair with the shortest Manhattan distance between each other, and assign the bike to that worker. (If there are multiple (worker, bike) pairs with the same shortest Manhattan distance, we choose the pair with the smallest worker index; if there are multiple ways to do that, we choose the pair with the smallest bike index). We repeat this process until there are no available workers.
 * 
 * The Manhattan distance between two points p1 and p2 is Manhattan(p1, p2) = |p1.x - p2.x| + |p1.y - p2.y|.
 * 
 * Return a vector ans of length N, where ans[i] is the index (0-indexed) of the bike that the i-th worker is assigned to.
 * 
 * 
 * Example 1:
 * Input: workers = [[0,0],[2,1]], bikes = [[1,2],[3,3]]
 * Output: [1,0]
 * Explanation: 
 * Worker 1 grabs Bike 0 as they are closest (without ties), and Worker 0 is assigned Bike 1. So the output is [1, 0].
 * 
 * Example 2:
 * Input: workers = [[0,0],[1,1],[2,0]], bikes = [[1,0],[2,2],[2,1]]
 * Output: [0,2,1]
 * Explanation: 
 * Worker 0 grabs Bike 0 at first. Worker 1 and Worker 2 share the same distance to Bike 2, thus Worker 1 is assigned to Bike 2, and Worker 2 will take Bike 1. So the output is [0,2,1].
 * 
 * Note:
 * 0 <= workers[i][j], bikes[i][j] < 1000
 * All worker and bike locations are distinct.
 * 1 <= workers.length <= bikes.length <= 1000
 * 
 */
#include <vector>
#include <algorithm>
#include <climits>
#include <functional>
using namespace std;

class Solution1 {
public:
    int assignBikes(vector<vector<int>>& workers, vector<vector<int>>& bikes) {
        int n = workers.size(), m = bikes.size();
        // dp[mask] 表示在自行车使用状态为 mask 时，已经分配的工人的最小距离和
        // 由于我们按顺序分配工人，mask 中 1 的个数就是已分配的工人数
        vector<int> dp(1 << m, INT_MAX / 2); // 避免加法溢出
        dp[0] = 0;
        int ans = INT_MAX;
        
        // 遍历所有状态
        for (int mask = 0; mask < (1 << m); mask++) {
            // 当前已分配的工人数 = mask 中 1 的个数
            int workerIdx = __builtin_popcount(mask);
            if (workerIdx == n) {
                ans = min(ans, dp[mask]); // 所有工人都分配完了，更新答案
                continue;
            }
            
            // 尝试为下一个工人（workerIdx）分配一辆未使用的自行车
            for (int bike = 0; bike < m; bike++) {
                if (!(mask >> bike & 1)) { // 自行车 bike 未被使用
                    int newMask = mask | (1 << bike);
                    int dist = abs(workers[workerIdx][0] - bikes[bike][0]) +
                               abs(workers[workerIdx][1] - bikes[bike][1]);
                    dp[newMask] = min(dp[newMask], dp[mask] + dist);
                }
            }
        }
        return ans;
    }
};

class Solution2 {
public:
    int assignBikes(vector<vector<int>>& workers, vector<vector<int>>& bikes) {
        int n = workers.size(), m = bikes.size();
        vector<vector<int>> memo(n, vector<int>(1 << m, -1));
        
        // 预处理所有曼哈顿距离，避免重复计算
        vector<vector<int>> dist(n, vector<int>(m));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                dist[i][j] = abs(workers[i][0] - bikes[j][0]) +
                             abs(workers[i][1] - bikes[j][1]);
            }
        }
        
        function<int(int, int)> dfs = [&](int worker, int mask) {
            if (worker == n) return 0; // 所有工人都分配完成
            if (memo[worker][mask] != -1) return memo[worker][mask];
            
            int res = INT_MAX;
            for (int bike = 0; bike < m; bike++) {
                if (!(mask >> bike & 1)) { // 自行车 bike 可用
                    res = min(res, dist[worker][bike] + dfs(worker + 1, mask | (1 << bike)));
                }
            }
            return memo[worker][mask] = res;
        };
        
        return dfs(0, 0);
    }
};