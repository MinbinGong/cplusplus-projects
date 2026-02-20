/*
 * Number of Connected Components in an Undirected Graph
 * 
 * You have a graph of n nodes. You are given an integer n and an array edges where edges[i] = [ai, bi] indicates that there is an edge between ai and bi in the graph.
 * Return the number of connected components in the graph.
 * 
 * Example 1:
 * Input: n = 5, edges = [[0,1],[1,2],[3,4]]
 * Output: 2
 * 
 * Example 2:
 * Input: n = 5, edges = [[0,1],[1,2],[2,3],[3,4]]
 * Output: 1
 * 
 */
#include <vector>
#include <numeric> // for iota

using namespace std;

class Solution {
public:
    int countComponents(int n, vector<vector<int>>& edges) {
        vector<int> parent(n);
        // 初始化每个节点的父节点为自己
        iota(parent.begin(), parent.end(), 0);
        int components = n; // 初始连通分量数等于节点数

        for (const auto& edge : edges) {
            int a = edge[0], b = edge[1];
            int rootA = find(parent, a);
            int rootB = find(parent, b);
            if (rootA != rootB) {
                parent[rootA] = rootB; // 合并两个集合
                components--;           // 连通分量减少一个
            }
        }
        return components;
    }

private:
    int find(vector<int>& parent, int x) {
        // 路径压缩
        if (parent[x] != x) {
            parent[x] = find(parent, parent[x]);
        }
        return parent[x];
    }
};