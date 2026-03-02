/**
 * 1377. Frog Position After T Seconds
 * 
 * Given an undirected tree consisting of n vertices numbered from 1 to n. A frog starts jumping from the vertex 1. In one second, the frog jumps from its current vertex to another unvisited vertex if they are directly connected. The frog can not jump back to a visited vertex. In case the frog can jump to several vertices it jumps randomly to one of them with the same probability. Otherwise, when the frog can not jump to any unvisited vertex it jumps forever on the same vertex.
 * 
 * The edges of the undirected tree are given in the array edges, where edges[i] = [ai, bi] means that exists an edge connecting the vertices ai and bi.
 * 
 * Return the probability that after t seconds the frog is on the vertex target. Answers within 10-5 of the actual answer will be accepted.
 * 
 * Example 1:
 * Input: n = 7, edges = [[1,2],[1,3],[1,7],[2,4],[2,6],[3,5]], t = 2, target = 4
 * Output: 0.16666666666666666 
 * Explanation: The figure above shows the given graph. The frog starts at vertex 1, jumping with 1/3 probability to the vertex 2 after second 1. Then, it jumps with 1/2 probability to vertex 4 after second 2. Thus the probability for the frog is on the vertex 4 after 2 seconds is 1/3 * 1/2 = 1/6 = 0.16666666666666666. 
 * 
 * Example 2:
 * Input: n = 7, edges = [[1,2],[1,3],[1,7],[2,4],[2,6],[3,5]], t = 1, target = 7
 * Output: 0.3333333333333333
 * Explanation: The figure above shows the given graph. The frog starts at vertex 1, jumping with 1/3 = 0.3333333333333333 probability to the vertex 7 after second 1. 
 * 
 * Note:
 * 1 <= n <= 100
 * edges.length == n - 1
 * edges[i].length == 2
 * 1 <= ai, bi <= n
 * 1 <= t <= 50
 * 1 <= target <= n
 * 
 */
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    double frogPosition(int n, vector<vector<int>>& edges, int t, int target) {
        // Trivial case: only one vertex
        if (n == 1) return 1.0;
        
        // Build adjacency list (1‑based)
        vector<vector<int>> adj(n + 1);
        for (auto& e : edges) {
            int u = e[0], v = e[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        
        // BFS from vertex 1 to obtain parent, depth and number of children
        vector<int> parent(n + 1, 0);
        vector<int> childrenCount(n + 1, 0);
        vector<int> depth(n + 1, -1);
        queue<int> q;
        q.push(1);
        parent[1] = -1;
        depth[1] = 0;
        
        while (!q.empty()) {
            int u = q.front(); q.pop();
            int cnt = 0;
            for (int v : adj[u]) {
                if (v != parent[u]) {
                    parent[v] = u;
                    depth[v] = depth[u] + 1;
                    ++cnt;
                    q.push(v);
                }
            }
            childrenCount[u] = cnt;
        }
        
        // Special case: target is the root
        if (target == 1) {
            if (t == 0) return 1.0;
            // If root has children, frog leaves at t=1; otherwise it stays forever
            return (childrenCount[1] == 0) ? 1.0 : 0.0;
        }
        
        int dist = depth[target];
        if (dist > t) return 0.0;          // cannot reach target in time
        
        // Compute probability along the unique path from root to target
        double prob = 1.0;
        int node = target;
        while (parent[node] != -1) {
            prob /= childrenCount[parent[node]];
            node = parent[node];
        }
        
        if (dist == t) {
            return prob;                    // arrives exactly at time t
        } else { // dist < t
            // If target is a leaf, the frog stays; otherwise it jumps away
            return (childrenCount[target] == 0) ? prob : 0.0;
        }
    }
};