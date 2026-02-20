/*
 * Minimum height trees
 *
 * A tree is an undirected graph in which any two vertices are connected 
 * by exactly one path. In other words, any connected graph without simple cycles is a tree.
 * 
 * Given a tree of n nodes labelled from 0 to n - 1, and an array of n - 1 edges 
 * where edges[i] = [ai, bi] indicates that there is an undirected edge 
 * between the two nodes ai and bi in the tree, you can choose any node of the tree as the root. 
 * When you select a node x as the root, the result tree has height h. 
 * Among all possible rooted trees, those with minimum height (i.e. min(h))  are called minimum height trees (MHTs).
 * 
 * Return a list of all MHTs' root labels. You can return the answer in any order.
 * The height of a rooted tree is the number of edges on the longest downward path between the root and a leaf.
 * 
 * Example 1:
 * Input: n = 4, edges = [[1,0],[1,2],[1,3]]
 * Output: [1]
 * Explanation: As shown, the height of the tree is 1 when the root is the node with label 1 which is the only MHT.
 * 
 * Example 2:
 * Input: n = 6, edges = [[3,0],[3,1],[3,2],[3,4],[5,4]]
 * Output: [3,4]
 * Explanation: As shown, the height of the tree is 2 when the root is the node with label 3 which is the only MHT.
 * 
 */
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        // 处理特殊情况：只有一个节点
        if (n == 1) return {0};

        // 构建邻接表和度数组
        vector<vector<int>> adj(n);
        vector<int> degree(n, 0);

        for (const auto& edge : edges) {
            int u = edge[0], v = edge[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
            degree[u]++;
            degree[v]++;
        }

        // 初始化队列，将所有叶子节点（度为1）入队
        queue<int> q;
        for (int i = 0; i < n; i++) {
            if (degree[i] == 1) {
                q.push(i);
            }
        }

        int remainingNodes = n;
        // 不断删除叶子节点，直到剩下1-2个节点
        while (remainingNodes > 2) {
            int leafCount = q.size();
            remainingNodes -= leafCount;

            // 处理当前层的所有叶子节点
            for (int i = 0; i < leafCount; i++) {
                int leaf = q.front();
                q.pop();

                // 更新邻居节点的度
                for (int neighbor : adj[leaf]) {
                    degree[neighbor]--;
                    if (degree[neighbor] == 1) {
                        q.push(neighbor);
                    }
                }
            }
        }

        // 队列中剩下的节点就是最小高度树的根
        vector<int> result;
        while (!q.empty()) {
            result.push_back(q.front());
            q.pop();
        }
        return result;
    }
};