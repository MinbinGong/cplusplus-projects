/**
 * 834. Sum of Distances in Tree
 * 
 * An undirected, connected tree with N nodes labelled 0...N-1 is given.
 * 
 * The ith edge connects nodes edges[i][0] and edges[i][1] together.
 * 
 * Return a list ans, where ans[i] is the sum of the distances between node i and all other nodes.
 * 
 * Example:
 * Input: N = 6, edges = [[0,1],[0,2],[2,3],[2,4],[2,5]]
 * Output: [8,12,6,10,10,10]
 * Explanation: 
 * Here is a diagram of the given tree:
 *   0
 *  / \
 * 1   2
 *    /|\
 *   3 4 5
 * We can see that dist(0,1) + dist(0,2) + dist(0,3) + dist(0,4) + dist(0,5)
 * equals to 8.  Hence, ans[0] = 8, and so on.
 * 
 * Note:
 * 1 <= N <= 10000
 * 
 */
#include <vector>
#include <unordered_map>
#include <functional>
using namespace std;

class Solution {
public:
    vector<int> sumOfDistancesInTree(int n, vector<vector<int>>& edges) {
        vector<vector<int>> adj(n);
        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        vector<int> count(n, 1);      // size of subtree rooted at node (including itself)
        vector<int> ans(n, 0);        // sum of distances from node to all others

        // First DFS: compute subtree sizes and answer for root 0
        function<void(int, int)> dfs1 = [&](int u, int parent) {
            for (int v : adj[u]) {
                if (v == parent) continue;
                dfs1(v, u);
                count[u] += count[v];
                ans[u] += ans[v] + count[v];   // nodes in v's subtree are one step farther from u
            }
        };
        dfs1(0, -1);

        // Second DFS: propagate answers to all nodes using the formula
        function<void(int, int)> dfs2 = [&](int u, int parent) {
            for (int v : adj[u]) {
                if (v == parent) continue;
                ans[v] = ans[u] - count[v] + (n - count[v]);
                dfs2(v, u);
            }
        };
        dfs2(0, -1);

        return ans;
    }
};