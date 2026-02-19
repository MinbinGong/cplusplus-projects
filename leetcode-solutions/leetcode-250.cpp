/*
 * Count Univalue Subtrees
 * 
 * Given the root of a binary tree, return the number of uni-value subtrees.
 * 
 * A uni-value subtree means all nodes of the subtree have the same value.
 * 
 * Constraints:
 * 1. The number of the node in the tree will be in the range [0, 1000].
 * 2. -1000 <= Node.val <= 1000
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
class Solution {
public:
    int countUnivalSubtrees(TreeNode* root) {
        int count = 0;
        isUnival(root, count);
        return count;
    }

private:
    bool isUnival(TreeNode* node, int& count) {
        if (!node) return true;
        
        // Check left and right subtrees
        bool leftUnival = isUnival(node->left, count);
        bool rightUnival = isUnival(node->right, count);
        
        // If both subtrees are univalue and their values match the current node's value
        if (leftUnival && rightUnival) {
            // Check left child value
            if (node->left && node->left->val != node->val) return false;
            // Check right child value
            if (node->right && node->right->val != node->val) return false;
            
            // Current subtree is univalue
            count++;
            return true;
        }
        return false;
    }
};