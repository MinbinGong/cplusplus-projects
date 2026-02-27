/**
 * 1059. All Paths from Source Lead to Destination
 * 
 * Given the edges of a directed graph, and two nodes source and destination of this graph, determine whether or not all paths starting from source eventually end at destination, that is:
 * 
 * At least one path exists from the source node to the destination node
 * If a path exists from the source node to a node with no outgoing edges, then that node is equal to destination.
 * The number of possible paths from source to destination is a finite number.
 * Return true if and only if all roads from source lead to destination.
 * 
 * 
 * Example 1:
 * Input: n = 3, edges = [[0,1],[0,2]], source = 0, destination = 2
 * Output: false
 * Explanation: It is possible to reach and get stuck on both node 1 and node 2.
 * 
 * Example 2:
 * Input: n = 4, edges = [[0,1],[0,3],[1,2],[2,1]], source = 0, destination = 3
 * Output: false
 * 
 * Example 3:
 * Input: n = 4, edges = [[0,1],[0,2],[1,3],[2,3]], source = 0, destination = 3
 * Output: true
 * 
 * Note:
 * The given graph may have self-loops and parallel edges.
 * The number of nodes n in the graph is between 1 and 10000
 * The number of edges in the graph is between 0 and 10000
 * 0 <= edges.length <= 10000
 * edges[i].length == 2
 * 0 <= source <= n - 1
 * 0 <= destination <= n - 1
 */
#include <vector>
#include <functional>

using namespace std;

class Solution {
public:
    bool leadsToDestination(int n, vector<vector<int>>& edges, int source, int destination) {
        // build adjacency list
        vector<vector<int>> graph(n);
        for (auto& e : edges) {
            graph[e[0]].push_back(e[1]);
        }

        // destination must have no outgoing edges (guaranteed by problem statement)
        // but we can still check for safety
        if (!graph[destination].empty()) return false;

        // state: 0 = unvisited, 1 = visiting (on current DFS stack), 2 = fully processed and safe
        vector<int> state(n, 0);

        // depth-first search with memoization
        function<bool(int)> dfs = [&](int u) -> bool {
            // base case: reached destination
            if (u == destination) return true;

            // dead end (and not destination)
            if (graph[u].empty()) return false;

            // already proven safe
            if (state[u] == 2) return true;

            // cycle detected
            if (state[u] == 1) return false;

            // mark as visiting
            state[u] = 1;

            // check all outgoing edges
            for (int v : graph[u]) {
                if (!dfs(v)) return false;
            }

            // all neighbours lead to destination → this node is safe
            state[u] = 2;
            return true;
        };

        return dfs(source);
    }
};
