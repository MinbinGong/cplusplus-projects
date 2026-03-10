/**
 * 1724. Checking Existence of Edge Length Limited Paths II
 * 
 * Given an undirected graph with n vertices, where each edge is weighted,
 * this problem asks whether there exists a path between two vertices that is
 * strictly less than a given limit.
 * 
 * Example 1:
 * Input: n = 3, edges = [[0,1,2],[1,2,4],[2,0,8],[1,0,16]], queries = [[0,1,2],[0,2,5]]
 * Output: [false,true]
 * Explanation: The graph is shown above.
 * Note that there are two paths between vertices 0 and 1 with weights 2 and 16.
 * For the first query, the limit is 2. We cannot go from 0 to 1 with a weight of 2.
 * For the second query, the limit is 5. We can go from 0 to 2 with a weight of 4.
 * 
 * Example 2:
 * Input: n = 5, edges = [[0,1,10],[1,2,5],[2,3,9],[3,4,13]], queries = [[0,4,14],[1,4,13]]
 * Output: [true,false]
 * Explanation: The graph is shown above.
 * 
 * Constraints:
 * 1 <= n <= 105
 * 0 <= edges.length <= 105
 * edges[i].length == 3
 * 0 <= ui, vi < n
 * ui != vi
 * 0 <= weighti <= 109
 * 1 <= queries.length <= 105
 * queries[j].length == 3
 * 0 <= pj, qj < n
 * pj != qj
 * 0 <= limitj <= 109
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class DistanceLimitedPathsExist {
private:
    vector<int> parent;
    vector<int> rank;
    vector<pair<int, pair<int, int>>> edges; // {distance, {u, v}}
    vector<pair<int, pair<pair<int, int>, int>>> queries; // {query_index, {{p, q}, limit}}
    vector<bool> answers;
    
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
    
public:
    DistanceLimitedPathsExist(int n, vector<vector<int>>& edgeList) {
        // Initialize Union-Find
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
        
        // Store edges with their distances
        for (auto& edge : edgeList) {
            edges.push_back({edge[2], {edge[0], edge[1]}});
        }
        
        // Sort edges by distance
        sort(edges.begin(), edges.end());
    }
    
    bool query(int p, int q, int limit) {
        // Process all edges with distance < limit that haven't been processed yet
        static int edgeIndex = 0;
        
        while (edgeIndex < edges.size() && edges[edgeIndex].first < limit) {
            int u = edges[edgeIndex].second.first;
            int v = edges[edgeIndex].second.second;
            unite(u, v);
            edgeIndex++;
        }
        
        // Check if p and q are connected
        return find(p) == find(q);
    }
};

/**
 * Your DistanceLimitedPathsExist object will be instantiated and called as such:
 * DistanceLimitedPathsExist* obj = new DistanceLimitedPathsExist(n, edgeList);
 * bool param_1 = obj->query(p,q,limit);
 */