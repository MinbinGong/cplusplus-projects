/*
 * 1719. Number Of Ways To Reconstruct A Tree
 *
 * You are given an array pairs, where pairs[i] = [xi, yi], and:
 * 
 * There are no duplicates.
 * xi < yi
 * Let ways be the number of rooted trees that satisfy the following conditions:
 * 
 * The tree consists of nodes whose values appeared in pairs.
 * A pair [xi, yi] exists in pairs if and only if xi is an ancestor of yi or yi is an ancestor of xi.
 * Note: the tree does not have to be a binary tree.
 * Two ways are considered to be different if there is at least one node that has different parents in both ways.
 * 
 * Return:
 * 
 * 0 if ways == 0
 * 1 if ways == 1
 * 2 if ways > 1
 * 
 * Constraints:
 * 1 <= pairs.length <= 105
 * 1 <= xi < yi <= 500
 * The elements in pairs are unique.
 * 
 */
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class Solution {
public:
    int checkWays(vector<vector<int>>& pairs) {
        // 构建邻接关系图：记录每个节点相关的所有节点
        unordered_map<int, unordered_set<int>> adj;
        for (auto& p : pairs) {
            adj[p[0]].insert(p[1]);
            adj[p[1]].insert(p[0]);
        }

        // 1. 寻找根节点：根节点必须与所有其他节点都有直接关系
        int n = adj.size();  // 节点总数
        int root = -1;
        for (auto& [node, neighbors] : adj) {
            if (neighbors.size() == n - 1) {
                root = node;
                break;
            }
        }
        if (root == -1) return 0;  // 无根节点，无法构建树

        int ans = 1;  // 默认1种构建方式

        // 2. 为每个非根节点寻找父节点
        for (auto& [node, neighbors] : adj) {
            if (node == root) continue;  // 根节点跳过

            // 寻找可能的父节点：必须是node的邻居，且度数 >= node的度数
            int parent = -1;
            int parentDegree = INT_MAX;
            int nodeDegree = neighbors.size();

            for (int candidate : neighbors) {
                int candDegree = adj[candidate].size();
                if (candDegree >= nodeDegree && candDegree < parentDegree) {
                    parent = candidate;
                    parentDegree = candDegree;
                }
            }

            if (parent == -1) return 0;  // 找不到父节点，无法构建

            // 3. 检查node的所有邻居是否都是parent的邻居（子集关系）
            for (int neighbor : neighbors) {
                if (neighbor == parent) continue;  // 父节点本身不需要检查
                if (!adj[parent].count(neighbor)) {
                    return 0;  // node的邻居不在parent的邻居中，违反祖先关系
                }
            }

            // 4. 如果node的度数与parent相同，说明存在多种构建方式
            if (parentDegree == nodeDegree) {
                ans = 2;
            }
        }

        return ans;
    }
};