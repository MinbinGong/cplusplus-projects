/**
 * 1766. Tree of Coprimes
 * 
 * There is a tree (i.e., a connected, undirected graph that has no cycles) consisting of n nodes numbered from 0 to n - 1 and exactly n - 1 edges. Each node has a value associated with it, and the root of the tree is node 0.
 * 
 * To represent this tree, you are given an integer array nums and a 2D array edges. Each nums[i] represents the ith node's value, and each edges[j] = [uj, vj] represents an edge between nodes uj and vj in the tree.
 * 
 * Two values x and y are coprime if gcd(x, y) == 1 where gcd(x, y) is the greatest common divisor of x and y.
 * 
 * An ancestor of a node i is any other node on the shortest path from node i to the root. A node is not considered an ancestor of itself.
 * 
 * Example 1:
 * 
 * Input: nums = [2,3,3,2], edges = [[0,1],[1,2],[1,3]]
 * Output: [-1,0,0,1]
 * Explanation: In the above figure, each node's value is in parentheses.
 * - Node 0 has no coprime ancestors.
 * - Node 1 has only one ancestor, node 0. Their values are coprime (gcd(2,3) == 1).
 * - Node 2 has two ancestors, nodes 1 and 0. Node 1's value is not coprime (gcd(3,3) == 3), but node 0's
 *   value is (gcd(2,3) == 1), so node 0 is the closest valid ancestor.
 * - Node 3 has two ancestors, nodes 1 and 0. It is coprime with node 1 (gcd(3,2) == 1), so node 1 is its
 *   closest valid ancestor.
 * 
 * Example 2:
 * 
 * Input: nums = [5,6,10,2,3,6,15], edges = [[0,1],[0,2],[1,3],[1,4],[2,5],[2,6]]
 * Output: [-1,0,-1,0,0,0,-1]
 * 
 * Constraints:
 * 
 * n == nums.length
 * 1 <= n <= 105
 * 1 <= nums[i] <= 50
 * 0 <= edges.length == n - 1
 * edges[j].length == 2
 * 0 <= uj, vj < n
 * uj != vj
 * 
 */
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    vector<int> getCoprimes(vector<int>& nums, vector<vector<int>>& edges) {
        int n = nums.size();
        vector<vector<int>> adj(n);
        for (auto& e : edges) {
            int u = e[0], v = e[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        // Precompute coprime table for values 1..50
        vector<vector<bool>> coprime(51, vector<bool>(51, false));
        for (int i = 1; i <= 50; ++i) {
            for (int j = 1; j <= 50; ++j) {
                if (gcd(i, j) == 1) coprime[i][j] = true;
            }
        }

        vector<int> ans(n, -1);
        // history[v] : stack of (depth, node) for nodes with value v in current path
        vector<vector<pair<int, int>>> history(51);

        // Iterative DFS with explicit stack
        struct State {
            int node, parent, depth, state; // state 0 = enter, 1 = leave
        };
        vector<State> stk;
        stk.push_back({0, -1, 0, 0});   // start from node 0

        while (!stk.empty()) {
            State cur = stk.back();
            stk.pop_back();
            int node = cur.node;
            int parent = cur.parent;
            int depth = cur.depth;
            int state = cur.state;
            int val = nums[node];

            if (state == 0) {  // entering node
                // find nearest ancestor with coprime value
                int bestDepth = -1, bestNode = -1;
                for (int v = 1; v <= 50; ++v) {
                    if (coprime[val][v] && !history[v].empty()) {
                        int d = history[v].back().first;
                        if (d > bestDepth) {
                            bestDepth = d;
                            bestNode = history[v].back().second;
                        }
                    }
                }
                ans[node] = bestNode;

                // push current node onto its value's history
                history[val].push_back({depth, node});

                // push leave state
                stk.push_back({node, parent, depth, 1});

                // push children (any order)
                for (int child : adj[node]) {
                    if (child != parent) {
                        stk.push_back({child, node, depth + 1, 0});
                    }
                }
            } else {  // leaving node
                history[val].pop_back();
            }
        }

        return ans;
    }

private:
    int gcd(int a, int b) {
        while (b) {
            int t = a % b;
            a = b;
            b = t;
        }
        return a;
    }
};