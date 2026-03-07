/**
 * 1615. Maximal Network Rank
 * 
 * There is an infrastructure of n cities with some number of roads connecting these cities. Each roads[i] = [ai, bi] indicates that there is a bidirectional road between cities ai and bi.
 * 
 * The network rank of two different cities is defined as the total number of directly connected roads to either city. If a road is directly connected to both cities, it is only counted once.
 * 
 * The maximal network rank of the infrastructure is the maximum network rank of all pairs of different cities.
 * 
 * Given the integer n and the array roads, return the maximal network rank of the entire infrastructure.
 * 
 * Example 1:
 * Input: n = 4, roads = [[0,1],[0,3],[1,2],[1,3]]
 * Output: 4
 * Explanation: The network rank of cities 0 and 1 is 4 as there are 4 roads that are connected to either 0 or 1. The road between 0 and 1 is only counted once.
 * 
 * Example 2:
 * Input: n = 5, roads = [[0,1],[0,3],[1,2],[1,3],[2,3],[2,4]]
 * Output: 5
 * Explanation: There are 5 roads that are connected to cities 1 or 2.
 * 
 * Constraints:
 * 2 <= n <= 100
 * 0 <= roads.length <= n * (n - 1) / 2
 * roads[i].length == 2
 * 0 <= ai, bi <= n-1
 * ai != bi
 * Each pair of cities has at most one road connecting them.
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    int maximalNetworkRank(int n, vector<vector<int>>& roads) {
        // 度数数组
        vector<int> degree(n, 0);
        // 邻接矩阵，用于快速判断两城市是否直接相连
        vector<vector<bool>> direct(n, vector<bool>(n, false));
        
        for (const auto& road : roads) {
            int a = road[0], b = road[1];
            degree[a]++;
            degree[b]++;
            direct[a][b] = direct[b][a] = true;
        }
        
        int ans = 0;
        // 枚举所有不同的城市对
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int cur = degree[i] + degree[j];
                if (direct[i][j]) cur--;   // 有直接边则减去重复的一条
                ans = max(ans, cur);
            }
        }
        return ans;
    }
};