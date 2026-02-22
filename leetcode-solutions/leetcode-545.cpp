/*
 * 545. Boundary of Binary Tree
 * 
 * Given a binary tree, return the values of its boundary in anti-clockwise direction starting from root. Boundary includes left boundary, leaves, and right boundary in order.
 * 
 * Note:
 * The root may be considered as the left boundary as well as the right boundary.
 * The nodes of the tree are guaranteed to be non-repetitive.
 * 
 * Example 1:
 * Input:
 *   1
 *    \
 *     2
 *    / \
 *   3   4
 * Output: [1,3,4,2]
 * Explanation:
 * The root is not left boundary, so it is not included in the output.
 * The left boundary follows the path from root to the left-most node.
 * The right boundary follows the path from root to the right-most node.
 * The leaves follow a similar process with leftmost and rightmost defined in the problem description.
 * 
 * Example 2:
 * Input:
 *     1
 *    / \
 *   2   3
 *  / \ / \
 * 4  5 6  7
 * Output: [1,2,4,5,6,7,3]
 * Explanation:
 * The left boundary follows the path from root to the left-most node.
 * The right boundary follows the path from root to the right-most node.
 * The leaves follow a similar process with leftmost and rightmost defined in the problem description.
 * 
 * Note:
 * The input binary tree will have a height in the range [1, 100000].
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
using namespace std;

class Solution {
public:
    vector<int> boundaryOfBinaryTree(TreeNode* root) {
        vector<int> res;
        if (!root) return res;
        
        // 1. Root
        res.push_back(root->val);
        
        // 2. Left boundary (excluding leaves and root)
        if (root->left) {
            addLeftBoundary(root->left, res);
        }
        
        // 3. Leaves (in left-to-right order, excluding root if it is a leaf)
        if (!isLeaf(root)) {
            addLeaves(root, res);
        }
        
        // 4. Right boundary (excluding leaves and root, collected in reverse order)
        if (root->right) {
            addRightBoundary(root->right, res);
        }
        
        return res;
    }

private:
    bool isLeaf(TreeNode* node) {
        return node && !node->left && !node->right;
    }
    
    void addLeftBoundary(TreeNode* node, vector<int>& res) {
        while (node) {
            if (!isLeaf(node)) {
                res.push_back(node->val);
            }
            if (node->left) {
                node = node->left;
            } else {
                node = node->right;
            }
        }
    }
    
    void addRightBoundary(TreeNode* node, vector<int>& res) {
        vector<int> temp;
        while (node) {
            if (!isLeaf(node)) {
                temp.push_back(node->val);
            }
            if (node->right) {
                node = node->right;
            } else {
                node = node->left;
            }
        }
        // Reverse to get the correct order (from bottom to top)
        for (int i = temp.size() - 1; i >= 0; --i) {
            res.push_back(temp[i]);
        }
    }
    
    void addLeaves(TreeNode* node, vector<int>& res) {
        if (!node) return;
        if (isLeaf(node)) {
            res.push_back(node->val);
        } else {
            addLeaves(node->left, res);
            addLeaves(node->right, res);
        }
    }
};