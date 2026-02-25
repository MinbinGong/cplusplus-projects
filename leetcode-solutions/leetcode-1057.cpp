/*
 * 1057. Campus Bikes
 *
 * On a campus represented as a 2D grid, there are N workers and M bikes, with N <= M. Each worker and bike is a 2D coordinate on this grid.
 * 
 * Our goal is to assign a bike to each worker. Among the available bikes and workers, we choose the (worker, bike) pair with the shortest Manhattan distance between each other, and assign the bike to that worker. (If there are multiple (worker, bike) pairs with the same shortest Manhattan distance, we choose the pair with the smallest worker index; if there are multiple ways to do that, we choose the pair with the smallest bike index). We repeat this process until there are no available workers.
 * 
 * The Manhattan distance between two points p1 and p2 is Manhattan(p1, p2) = |p1.x - p2.x| + |p1.y - p2.y|.
 * 
 * Return a vector ans of length N, where ans[i] is the index (0-indexed) of the bike that the i-th worker is assigned to.
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
 * 1. 0 <= workers[i][j], bikes[i][j] < 1000
 * 2. All worker and bike locations are distinct.
 * 3. 1 <= workers.length <= bikes.length <= 1000
 * 4. workers.length == bikes.length
 * 
 */
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
using namespace std;

class Solution1 {
public:
    vector<int> assignBikes(vector<vector<int>>& workers, vector<vector<int>>& bikes) {
        int n = workers.size(), m = bikes.size();
        vector<tuple<int, int, int>> pairs;  // (distance, worker, bike)
        
        // 计算所有距离组合
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int dist = abs(workers[i][0] - bikes[j][0]) + 
                          abs(workers[i][1] - bikes[j][1]);
                pairs.push_back({dist, i, j});
            }
        }
        
        // 排序：先按距离，再按工人索引，最后按自行车索引
        sort(pairs.begin(), pairs.end());
        
        vector<int> result(n, -1);
        vector<bool> workerAssigned(n, false);
        vector<bool> bikeAssigned(m, false);
        int assigned = 0;
        
        // 贪心分配
        for (const auto& [dist, i, j] : pairs) {
            if (!workerAssigned[i] && !bikeAssigned[j]) {
                result[i] = j;
                workerAssigned[i] = true;
                bikeAssigned[j] = true;
                assigned++;
                if (assigned == n) break;
            }
        }
        
        return result;
    }
};

class Solution2 {
public:
    vector<int> assignBikes(vector<vector<int>>& workers, vector<vector<int>>& bikes) {
        int n = workers.size(), m = bikes.size();
        vector<vector<pair<int, int>>> buckets(2001);  // 距离范围 0-2000
        
        // 将工人-自行车对放入对应距离的桶
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int dist = abs(workers[i][0] - bikes[j][0]) + 
                          abs(workers[i][1] - bikes[j][1]);
                buckets[dist].push_back({i, j});
            }
        }
        
        vector<int> result(n, -1);
        vector<bool> workerAssigned(n, false);
        vector<bool> bikeAssigned(m, false);
        int assigned = 0;
        
        // 按距离从小到大遍历
        for (int d = 0; d <= 2000 && assigned < n; ++d) {
            for (const auto& [worker, bike] : buckets[d]) {
                if (!workerAssigned[worker] && !bikeAssigned[bike]) {
                    result[worker] = bike;
                    workerAssigned[worker] = true;
                    bikeAssigned[bike] = true;
                    assigned++;
                }
            }
        }
        
        return result;
    }
};