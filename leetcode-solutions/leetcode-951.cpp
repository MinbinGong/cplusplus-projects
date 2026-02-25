/*
 * 951. Flip Equivalent Binary Trees
 *
 * For a binary tree T, we can define a flip operation as follows: choose any node, and swap the left and right child
 * subtrees.
 *
 * A binary tree X is flip equivalent to a binary tree Y if and only if we can make X equal to Y after some number of
 * flip operations.
 *
 * Given the roots of two binary trees root1 and root2, return true if the two trees are flip equivalent or false
 * otherwise.
 *
 * Example 1:
 *
 * Input: root1 = [1,2,3,4,5,6,null,null,null,7,8], root2 = [1,3,2,null,6,4,5,null,null,null,null,8,7]
 * Output: true
 * Explanation: We flipped at nodes with values 1, 3, and 5.
 *
 * Example 2:
 *
 * Input: root1 = [], root2 = []
 * Output: true
 *
 * Note:
 *
 * Each tree will have at most 100 nodes each.
 * Each value in each tree will be a unique integer in the range [0, 99].
 */
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
  bool flipEquiv(TreeNode *root1, TreeNode *root2) {
    // Both null -> equivalent
    if (!root1 && !root2) return true;
    // One null, the other not -> not equivalent
    if (!root1 || !root2) return false;
    // Values differ -> not equivalent
    if (root1->val != root2->val) return false;

    // Check both possibilities: no flip or flip
    return (flipEquiv(root1->left, root2->left) && flipEquiv(root1->right, root2->right)) ||
           (flipEquiv(root1->left, root2->right) && flipEquiv(root1->right, root2->left));
  }
};