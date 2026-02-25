/*
 * 1008. Construct Binary Search Tree from Preorder Traversal
 *
 * Return the root node of a binary search tree that matches the given preorder traversal.
 *
 * (Recall that a binary search tree is a binary tree where for every node, any descendant of node.left has a value < node.val, and any descendant of node.right has a value > node.val.  Also recall that a preorder traversal displays the value of the node first, then traverses node.left, then traverses node.right.)
 *
 * Example 1:
 *
 * Input: [8,5,1,7,10,12]
 * Output: [8,5,10,1,7,null,12]
 * 
 * Note:
 *
 * 1 <= preorder.length <= 100
 * The values of preorder are distinct.
 * 
 */
#include <vector>
#include <algorithm>

using namespace std;

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
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        int i = 0;
        return build(preorder, i, INT_MIN, INT_MAX);
    }

private:
    TreeNode* build(vector<int>& preorder, int& i, int lower, int upper) {
        if (i >= preorder.size()) return nullptr;
        int val = preorder[i];
        if (val < lower || val > upper) return nullptr; // not in valid range for this subtree

        // consume this node
        TreeNode* root = new TreeNode(val);
        ++i;

        // left subtree must have values less than val
        root->left = build(preorder, i, lower, val);
        // right subtree must have values greater than val
        root->right = build(preorder, i, val, upper);

        return root;
    }
};