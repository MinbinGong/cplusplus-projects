/*
 * Is Graph Bipartite
 *
 * Given an undirected graph, return true if and only if it is bipartite.
 * 
 * A graph is bipartite if we can split its set of nodes into two independent subsets A and B, such that every edge in the graph has one node in A and another node in B.
 * 
 * Note:
 * 1. graph will have length in range [1, 100].
 * 2. graph[i] will contain integers in range [0, graph.length - 1].
 * 3. graph[i] will not contain i or duplicate values.
 * 4. The graph is undirected: if any element j is in graph[i], then i will be in graph[j].
 * 
 */
#include <queue>
#include <vector>
using namespace std;

bool isBipartite(vector<vector<int>>& graph) {
  if (graph.empty()) {
    return true;
  }

  int n = graph.size();
  vector<int> color(n, 0);
  queue<int> q;
  for (int i = 0; i < n; ++i) {
    if (color[i] == 0) {
      q.push(i);
      color[i] = 1;
    }

    while (!q.empty()) {
      int node = q.front();
      q.pop();
      for (const auto& j : graph[node]) {
        if (color[j] == 0) {
          q.push(j);
          color[j] = color[node] == 2 ? 1 : 2;
        } else if (color[node] == color[j]) {
          return false;
        }
      }
    }
  }
  return true;
}