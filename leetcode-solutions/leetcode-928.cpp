/*
 * Minimize Malware Spread II
 *
 * (Same as leetcode-924, but with 2 differences:
 * 1. The graph is not guaranteed to be connected.
 * 2. We can't remove a node that is initially infected.
 * )
 */
#include <vector>
#include <unordered_set>
#include <queue>
using namespace std;

class Solution {
public:
    int minMalwareSpread(vector<vector<int>>& graph, vector<int>& initial) {
        int n = graph.size();
        unordered_set<int> initSet(initial.begin(), initial.end());
        int bestNode = -1;
        int minInfected = n + 1; // larger than any possible count

        // Try removing each initially infected node
        for (int removed : initial) {
            // infected[i] will be true if node i becomes infected after removal
            vector<bool> infected(n, false);
            queue<int> q;

            // Start BFS from all initially infected nodes except 'removed'
            for (int node : initial) {
                if (node != removed) {
                    infected[node] = true;
                    q.push(node);
                }
            }

            // Multi-source BFS in the graph without node 'removed'
            while (!q.empty()) {
                int cur = q.front();
                q.pop();
                for (int nei = 0; nei < n; ++nei) {
                    if (graph[cur][nei] == 1 && nei != removed && !infected[nei]) {
                        infected[nei] = true;
                        q.push(nei);
                    }
                }
            }

            // Count total infected nodes
            int cnt = 0;
            for (bool v : infected) {
                if (v) cnt++;
            }

            // Update best answer (minimize infected count, choose smallest index on tie)
            if (cnt < minInfected || (cnt == minInfected && removed < bestNode)) {
                minInfected = cnt;
                bestNode = removed;
            }
        }

        return bestNode;
    }
};