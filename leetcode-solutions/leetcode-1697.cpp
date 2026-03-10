/*
 * 1697. Checking Existence of Edge Length Limited Paths
 * 
 * An undirected graph of n nodes is defined by edgeList, where edgeList[i] = [ui, vi, disi] denotes an edge between nodes ui and vi with distance disi. Note that there may be multiple edges between two nodes.
 * 
 * Given an array queries, where queries[j] = [pj, qj, limitj], your task is to determine for each queries[j] whether there is a path between pj and qj such that each edge on the path has a distance strictly less than limitj .
 * 
 * Return a boolean array answer, where answer.length == queries.length and the jth value of answer is true if there is a path for queries[j] is true, and false otherwise.
 * 
 * Example 1:
 * Input: n = 3, edgeList = [[0,1,2],[1,2,4],[2,0,8],[1,0,16]], queries = [[0,1,2],[0,2,5]]
 * Output: [false,true]
 * Explanation: The graph above shows the given graph. Note that there are two overlapping edges between 0 and 1 with distances 2 and 16.
 * For the first query, between 0 and 1 there is no path where each distance is less than 2, thus we return false for this query.
 * For the second query, between 0 and 2 there is a path (0 -> 1 -> 2) of two edges with distances less than 5, thus we return true for this query.
 * 
 * Example 2:
 * Input: n = 5, edgeList = [[0,1,10],[1,2,5],[2,3,9],[3,4,13]], queries = [[0,4,14],[1,4,13]]
 * Output: [true,false]
 * Explanation: The graph above shows the given graph.
 * 
 * Constraints:
 * 2 <= n <= 100000
 * 1 <= edgeList.length, queries.length <= 100000
 * edgeList[i].length == 3
 * queries[j].length == 3
 * 0 <= ui, vi, pj, qj <= n - 1
 * ui != vi
 * pj != qj
 * 1 <= disi, limitj <= 1000000
 * There may be multiple edges between two nodes.
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class UnionFind {
public:
    vector<int> parent, rank;
    
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i) parent[i] = i;
    }
    
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    
    void unite(int x, int y) {
        int rootX = find(x), rootY = find(y);
        if (rootX != rootY) {
            if (rank[rootX] < rank[rootY]) parent[rootX] = rootY;
            else if (rank[rootX] > rank[rootY]) parent[rootY] = rootX;
            else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
    
    bool connected(int x, int y) {
        return find(x) == find(y);
    }
};

class Solution {
public:
    vector<bool> distanceLimitedPathsExist(int n, vector<vector<int>>& edgeList, vector<vector<int>>& queries) {
        int m = edgeList.size();
        int q = queries.size();
        
        // 为每个查询添加索引
        vector<vector<int>> indexedQueries(q);
        for (int i = 0; i < q; ++i) {
            indexedQueries[i] = {queries[i][0], queries[i][1], queries[i][2], i};
        }
        
        // 将边按权重排序
        sort(edgeList.begin(), edgeList.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[2] < b[2];
        });
        
        // 将查询按limit排序
        sort(indexedQueries.begin(), indexedQueries.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[2] < b[2];
        });
        
        vector<bool> res(q);
        UnionFind uf(n);
        
        int edgeIdx = 0;
        for (const auto& query : indexedQueries) {
            int u = query[0], v = query[1], limit = query[2], idx = query[3];
            
            // 加入所有权重小于limit的边
            while (edgeIdx < m && edgeList[edgeIdx][2] < limit) {
                uf.unite(edgeList[edgeIdx][0], edgeList[edgeIdx][1]);
                edgeIdx++;
            }
            
            // 检查连通性
            res[idx] = uf.connected(u, v);
        }
        return res;
    }
};