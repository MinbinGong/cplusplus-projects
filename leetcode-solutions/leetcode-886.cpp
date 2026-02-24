/**
 * 886. Possible Bipartition
 *
 * Given a set of N people (numbered 1, 2, ..., N), we would like to split everyone into two groups of any size.
 * Each person may dislike some other people, and they should not go into the same group.
 * Formally, if dislikes[i] = [a, b], it means it is not allowed to put the people numbered a and b into the same group.
 * Return true if and only if it is possible to split everyone into two groups in this way.
 *
 * Example 1:
 * Input: N = 4, dislikes = [[1,2],[1,3],[2,4]]
 * Output: true
 * Explanation: group1 [1,4], group2 [2,3]
 *
 * Example 2:
 * Input: N = 3, dislikes = [[1,2],[1,3],[2,3]]
 * Output: false
 *
 * Example 3:
 * Input: N = 5, dislikes = [[1,2],[2,3],[3,4],[4,5],[1,5]]
 * Output: false
 *
 * Note:
 * 1 <= N <= 2000
 * 0 <= dislikes.length <= 10000
 * 1 <= dislikes[i][j] <= N
 * dislikes[i][0] < dislikes[i][1]
 * There does not exist i != j for which dislikes[i] == dislikes[j].
 * 
 */
#include <vector>
#include <unordered_map>
#include <functional>
using namespace std;

class Solution {
public:
    bool possibleBipartition(int n, vector<vector<int>>& dislikes) {
        // Build adjacency list
        vector<vector<int>> graph(n + 1);
        for (auto& d : dislikes) {
            graph[d[0]].push_back(d[1]);
            graph[d[1]].push_back(d[0]);
        }
        // 0: uncolored, 1 and -1: two colors
        vector<int> color(n + 1, 0);
        
        // DFS function to color the graph
        function<bool(int, int)> dfs = [&](int node, int col) -> bool {
            color[node] = col;
            for (int nei : graph[node]) {
                if (color[nei] == col) return false; // same color -> conflict
                if (color[nei] == 0 && !dfs(nei, -col)) return false;
            }
            return true;
        };
        
        // Check each connected component
        for (int i = 1; i <= n; ++i) {
            if (color[i] == 0 && !dfs(i, 1)) return false;
        }
        return true;
    }
};