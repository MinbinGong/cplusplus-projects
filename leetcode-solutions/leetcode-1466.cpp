/**
 * 1466. Reorder Routes to Make All Paths Lead to the City Zero
 * 
 * There are n cities numbered from 0 to n-1 and n-1 roads such that there is only one way to travel between two different cities (this network form a tree). Last year, The ministry of transport decided to orient the roads in one direction because they are too narrow.
 * 
 * Roads are represented by connections where connections[i] = [a, b] represents a road from city a to b.
 * 
 * This year, there will be a big event in the capital (city 0), and many people want to travel to this city.
 * 
 * Your task consists of reorienting some roads such that each city can visit the city 0. Return the minimum number of edges changed.
 * 
 * It's guaranteed that each city can reach the city 0 after reorder.
 * 
 * Example 1:
 * 
 * Input: n = 6, connections = [[0,1],[1,3],[2,3],[4,0],[4,5]]
 * Output: 3
 * Explanation: Change the direction of edges show in red such that each node can reach the node 0 (capital).
 * 
 * Example 2:
 * 
 * Input: n = 5, connections = [[1,0],[1,2],[3,2],[3,4]]
 * Output: 2
 * Explanation: Change the direction of edges show in red such that each node can reach the node 0 (capital).
 * 
 * Example 3:
 * 
 * Input: n = 3, connections = [[1,0],[2,0]]
 * Output: 0
 * 
 * Note:
 * 2 <= n <= 5 * 10^4
 * connections.length == n-1
 * connections[i].length == 2
 * 0 <= connections[i][0], connections[i][1] <= n-1
 * connections[i][0] != connections[i][1]
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int minReorder(int n, vector<vector<int>>& connections) {
        // adjacency list: each element stores (neighbor, direction)
        // direction = 1 means the original edge is from current node to neighbor
        // direction = 0 means the original edge is from neighbor to current node
        vector<vector<pair<int, int>>> adj(n);
        for (auto& e : connections) {
            int a = e[0], b = e[1];
            adj[a].emplace_back(b, 1); // original a -> b
            adj[b].emplace_back(a, 0); // original a -> b, so from b it's incoming
        }

        int ans = 0;
        vector<bool> visited(n, false);
        dfs(0, adj, visited, ans);
        return ans;
    }

private:
    void dfs(int u, vector<vector<pair<int, int>>>& adj, vector<bool>& visited, int& ans) {
        visited[u] = true;
        for (auto [v, dir] : adj[u]) {
            if (!visited[v]) {
                // If the original direction is from u to v, we need to flip it
                // to make it point towards u (the root)
                if (dir == 1) ++ans;
                dfs(v, adj, visited, ans);
            }
        }
    }
};
