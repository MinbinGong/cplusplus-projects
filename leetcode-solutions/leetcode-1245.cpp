/*
 * 1245. Tree Diameter
 *
 * Given an undirected tree, return its diameter: the number of edges in a longest path in that tree.
 *
 * The tree is given as an array of edges where edges[i] = [u, v] is a bidirectional edge between nodes u and v.  Each node has labels in the set {0, 1, ..., edges.length}.
 *
 * Example 1:
 * Input: edges = [[0,1],[0,2]]
 * Output: 2
 * Explanation:
 * A longest path of the tree is the path 1 - 0 - 2.
 *
 * Example 2:
 * Input: edges = [[0,1],[1,2],[2,3],[1,4],[4,5]]
 * Output: 4
 * Explanation:
 * A longest path of the tree is the path 3 - 2 - 1 - 4 - 5.
 *
 * Constraints:
 * 0 <= edges.length < 10^4
 * edges[i][0] != edges[i][1]
 * 0 <= edges[i][j] <= edges.length
 * 
 */
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class Solution {
public:
    int treeDiameter(vector<vector<int>>& edges) {
        int n = edges.size() + 1;
        if (n <= 1) return 0;               // no edges or single node
        
        vector<vector<int>> adj(n);
        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }
        
        // BFS returns the farthest node from start and its distance
        auto bfs = [&](int start) -> pair<int, int> {
            vector<int> dist(n, -1);
            queue<int> q;
            dist[start] = 0;
            q.push(start);
            int farthest = start;
            
            while (!q.empty()) {
                int u = q.front(); q.pop();
                for (int v : adj[u]) {
                    if (dist[v] == -1) {
                        dist[v] = dist[u] + 1;
                        q.push(v);
                        if (dist[v] > dist[farthest]) {
                            farthest = v;
                        }
                    }
                }
            }
            return {farthest, dist[farthest]};
        };
        
        // Step 1: find one endpoint of the diameter (start from node 0)
        auto [endpoint, _] = bfs(0);
        // Step 2: from that endpoint, BFS to get the actual diameter length
        auto [other, diameter] = bfs(endpoint);
        
        return diameter;
    }
};