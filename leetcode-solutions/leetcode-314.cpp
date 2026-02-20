/*
 * Binary Tree Vertical Order Traversal
 * 
 * Given the root of a binary tree, return the vertical order traversal of its nodes' values. 
 * (i.e., from top to bottom, column by column).
 * 
 * If two nodes are in the same row and column, the order should be from left to right.
 * 
 * Example 1:
 * Input: root = [3,9,20,null,null,15,7]
 * Output: [[9],[3,15],[20],[7]]
 * 
 * Example 2:
 * Input: root = [1,2,3,4,5,6,7]
 * Output: [[4],[2],[1,5,6],[3],[7]]
 * 
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
#include <vector>
#include <queue>
#include <map>
using namespace std;

// 二叉树的垂直遍历
class Solution {
public:
    vector<vector<int>> verticalOrder(TreeNode* root) {
        vector<vector<int>> result;
        if (!root) return result;

        // 使用队列进行BFS，同时存储节点及其列索引
        queue<pair<TreeNode*, int>> q;
        q.push({root, 0});

        // 用一个map来存储每一列的节点值列表（按行顺序自动保存，因为BFS按层遍历）
        map<int, vector<int>> columnTable;

        while (!q.empty()) {
            auto [node, col] = q.front();
            q.pop();

            // 将当前节点值加入对应列的列表
            columnTable[col].push_back(node->val);

            // 处理左右孩子，左孩子列-1，右孩子列+1
            if (node->left) {
                q.push({node->left, col - 1});
            }
            if (node->right) {
                q.push({node->right, col + 1});
            }
        }

        // 将map中的结果按列顺序取出
        for (auto& entry : columnTable) {
            result.push_back(move(entry.second));
        }
        return result;
    }
};