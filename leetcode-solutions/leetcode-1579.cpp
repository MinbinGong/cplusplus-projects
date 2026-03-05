/*
 * 1579. Remove Max Number of Edges to Keep Graph Fully Traversable
 *
 * Given two integers n and edges, where edges[i] = [typei, ui, vi] represents a bidirectional edge of type typei between nodes ui and vi, find the maximum number of edges you can remove so that after removing the edges, the graph can still be fully traversed by both Alice and Bob.
 * 
 * Example 1:
 * Input: n = 4, edges = [[3,1,2],[3,2,3],[1,1,3],[1,2,4],[1,1,2],[2,3,4]]
 * Output: 2
 * Explanation: If we remove the 2 edges [1,1,2] and [1,1,3]. The graph will still be fully traversable by Alice and Bob. Removing any additional edge will not make it so. So the maximum number of edges we can remove is 2.
 * 
 * Example 2:
 * Input: n = 4, edges = [[3,1,2],[3,2,3],[1,1,4],[2,1,4]]
 * Output: 0
 * Explanation: Notice that removing any edge will not make the graph fully traversable by Alice and Bob.
 * 
 * Constraints:
 * 1 <= n <= 10^5
 * 1 <= edges.length <= min(10^5, 3 * n * (n - 1) / 2)
 * edges[i].length == 3
 * 1 <= typei <= 3
 * 1 <= ui < vi <= n
 * All tuples (typei, ui, vi) are distinct.
 * 
 */
#include <vector>
using namespace std;

class UnionFind {
    vector<int> parent, rank;
    int components;
public:
    UnionFind(int n) : parent(n), rank(n, 0), components(n) {
        for (int i = 0; i < n; ++i) parent[i] = i;
    }
    
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    
    bool unite(int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx == ry) return false;
        if (rank[rx] < rank[ry]) parent[rx] = ry;
        else if (rank[rx] > rank[ry]) parent[ry] = rx;
        else { parent[ry] = rx; rank[rx]++; }
        components--;
        return true;
    }
    
    bool isConnected() {
        return components == 1;
    }
};

class Solution {
public:
    int maxNumEdgesToRemove(int n, vector<vector<int>>& edges) {
        UnionFind alice(n), bob(n);
        int used = 0;
        
        // first process type 3 edges (both)
        for (const auto& e : edges) {
            if (e[0] == 3) {
                int u = e[1] - 1, v = e[2] - 1;
                bool a = alice.unite(u, v);
                bool b = bob.unite(u, v);
                if (a || b) used++; // if either UF used the edge, count it
            }
        }
        
        // then type 1 (Alice only)
        for (const auto& e : edges) {
            if (e[0] == 1) {
                int u = e[1] - 1, v = e[2] - 1;
                if (alice.unite(u, v)) used++;
            }
        }
        
        // then type 2 (Bob only)
        for (const auto& e : edges) {
            if (e[0] == 2) {
                int u = e[1] - 1, v = e[2] - 1;
                if (bob.unite(u, v)) used++;
            }
        }
        
        // check if both graphs are fully connected
        if (!alice.isConnected() || !bob.isConnected())
            return -1;
        
        return edges.size() - used;
    }
};