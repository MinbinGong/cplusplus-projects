/*
 * Range Sum of BST
 *
 * Given the root node of a binary search tree, return the sum of values of all nodes with value between L and R
 * (inclusive).
 *
 * The binary search tree is guaranteed to have unique values.
 *
 * Example 1:
 * Input: root = [10,5,15,3,7,null,18], L = 7, R = 15
 * Output: 32
 *
 * Example 2:
 * Input: root = [10,5,15,3,7,13,18,1,null,6], L = 6, R = 10
 * Output: 23
 *
 * Note:
 * The number of nodes in the tree is at most 10000.
 * The final answer is guaranteed to be less than 2^31.
 *
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
  int rangeSumBST(TreeNode *root, int low, int high) {
    if (!root) return 0;
    int sum = 0;
    // 当前节点值在范围内，加入总和
    if (root->val >= low && root->val <= high) {
      sum += root->val;
    }
    // 如果当前节点值大于 low，左子树可能存在符合条件的节点
    if (root->val > low) {
      sum += rangeSumBST(root->left, low, high);
    }
    // 如果当前节点值小于 high，右子树可能存在符合条件的节点
    if (root->val < high) {
      sum += rangeSumBST(root->right, low, high);
    }
    return sum;
  }
};