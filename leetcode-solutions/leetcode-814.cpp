/*
 * 814. Binary Tree Pruning
 *
 * We are given the head node root of a binary tree, where additionally every node's value is either a 0 or a 1.
 *
 * Return the same tree where every subtree (of the given tree) not containing a 1 has been removed.
 *
 * (Recall that the subtree of a node X is X, plus every node that is a descendant of X.)
 *
 * Example:
 * Input: [1,null,0,0,1]
 * Output: [1,null,0,null,1]
 * Explanation:
 * Only the red nodes satisfy the property "every subtree not containing a 1".
 * The diagram on the right represents the answer.
 *
 * Note:
 * The binary tree will have at most 100 nodes.
 * The value of each node will only be 0 or 1.
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
  TreeNode *pruneTree(TreeNode *root) {
    if (!root) return nullptr;
    // 递归修剪左、右子树
    root->left = pruneTree(root->left);
    root->right = pruneTree(root->right);
    // 如果当前节点值为0且左右子树均为空，则删除该节点
    if (root->val == 0 && !root->left && !root->right) {
      return nullptr;
    }
    return root;
  }
};