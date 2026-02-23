/*
 * Network Delay Time
 *
 * You are given a network of n nodes, labeled from 1 to n. You are also given times, a list of travel times as directed edges times[i] = (ui, vi, wi), where ui is the source node, vi is the target node, and wi is the time it takes for a signal to travel from source to target.
 * 
 * We will send a signal from a given node k. Return the time it takes for all the n nodes to receive the signal. If it is impossible for all the n nodes to receive the signal, return -1.
 * 
 * Example 1:
 * 
 * Input: times = [[2,1,1],[2,3,1],[3,4,1]], n = 4, k = 2
 * Output: 2
 * 
 * Example 2:
 * 
 * Input: times = [[1,2,1]], n = 2, k = 1
 * Output: 1
 * 
 * Example 3:
 * 
 * Input: times = [[1,2,1]], n = 2, k = 2
 * Output: -1
 * 
 * Note:
 * 1. n is in the range [1, 100].
 * 2. k is in the range [1, n].
 * 3. 1 <= times.length <= 6000.
 * 4. times[i].length == 3.
 * 5. 1 <= ui, vi <= n.
 * 6. ui != vi.
 * 7. 0 <= wi <= 100.
 * 8. All the pairs (ui, vi) are unique. (i.e., no multiple edges.)
 * 
 */
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        // Build graph: adjacency list
        vector<vector<pair<int, int>>> graph(n + 1); // 1-indexed nodes
        for (const auto& t : times) {
            int u = t[0], v = t[1], w = t[2];
            graph[u].emplace_back(v, w);
        }

        // Dijkstra's algorithm
        vector<int> dist(n + 1, INT_MAX);
        dist[k] = 0;
        // min-heap: (distance, node)
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.emplace(0, k);

        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (d > dist[u]) continue; // stale entry
            for (auto [v, w] : graph[u]) {
                if (dist[v] > d + w) {
                    dist[v] = d + w;
                    pq.emplace(dist[v], v);
                }
            }
        }

        // Find maximum distance among all nodes
        int maxTime = 0;
        for (int i = 1; i <= n; ++i) {
            if (dist[i] == INT_MAX) return -1; // unreachable node
            maxTime = max(maxTime, dist[i]);
        }
        return maxTime;
    }
};