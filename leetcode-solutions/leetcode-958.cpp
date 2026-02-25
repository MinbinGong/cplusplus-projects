/*
 * 958. Check Completeness of a Binary Tree
 *
 * Given the root of a binary tree, determine if it is a complete binary tree.
 *
 * In a complete binary tree, every level, except possibly the last, is completely filled, and all nodes in the last level are as far left as possible. It can have between 1 and 2h nodes inclusive at the last level h.
 *
 * Example 1:
 *
 * Input: root = [1,2,3,4,5,6]
 * Output: true
 * Explanation: Every level before the last is full (ie. levels with node-values {1} and {2, 3}), and all nodes in the last level ({4, 5, 6}) are as far left as possible.
 * 
 * Example 2:
 *
 * Input: root = [1,2,3,4,5,null,7]
 * Output: false
 * Explanation: The node with value 7 isn't as far left as possible.
 * 
 * Note:
 * 1 <= The number of nodes in the tree <= 100.
 * 1 <= Node.val <= 1000
 * 
 */
#include <queue>
using namespace std;

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    bool isCompleteTree(TreeNode* root) {
        if (!root) return true;          // 空树视为完全二叉树
        queue<TreeNode*> q;
        q.push(root);
        bool seenNull = false;            // 是否已经遇到过空节点
        
        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop();
            
            if (node == nullptr) {
                seenNull = true;          // 遇到空节点，标记
            } else {
                if (seenNull) return false; // 空节点之后还有非空节点，不符合条件
                // 继续将左右孩子入队（包括空指针）
                q.push(node->left);
                q.push(node->right);
            }
        }
        return true;
    }
};