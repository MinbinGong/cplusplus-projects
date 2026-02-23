/*
 * 776. Split BST
 *
 * Given a Binary Search Tree (BST) with root node root, and a target value V, split the tree into two subtrees where one subtree has nodes that are all smaller or equal to the target value, while the other subtree has all nodes that are greater than the target value.  It's not necessarily the case that the tree contains a node with value V.
 * 
 * Additionally, most of the structure of the original tree should remain.  Formally, for any child C with parent P in the original tree, if they are both in the same subtree after the split, then node C should still have the parent P.
 * 
 * You should output the root TreeNode of both subtrees after splitting, in any order.
 * 
 * Example 1:
 * Input: root = [4,2,6,1,3,5,7], V = 2
 * Output: [[2,1],[4,3,6,null,null,5,7]]
 * Explanation:
 * Note that root, output[0], and output[1] are TreeNode objects, not arrays.
 * The following constraints apply:
 * 1. The size of the given tree will be between 1 and 50.
 * 2. The BST is always valid and each node's value is different.
 * 3. 0 <= V <= 1000.
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
class Solution {
public:
    vector<TreeNode*> splitBST(TreeNode* root, int V) {
        if (!root) return {nullptr, nullptr};
        
        if (root->val <= V) {
            // root and its left subtree belong to the left result
            auto rightSplit = splitBST(root->right, V);
            root->right = rightSplit[0]; // left part of right subtree becomes new right child
            return {root, rightSplit[1]};
        } else {
            // root and its right subtree belong to the right result
            auto leftSplit = splitBST(root->left, V);
            root->left = leftSplit[1]; // right part of left subtree becomes new left child
            return {leftSplit[0], root};
        }
    }
};