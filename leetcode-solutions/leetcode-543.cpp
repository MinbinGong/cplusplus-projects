/*
 * 543. Diameter of Binary tree
 * 
 * Given a binary tree, you need to compute the length of the diameter of the tree. The diameter of a binary tree is the length of the longest path between any two nodes in a tree. This path may or may not pass through the root.
 * 
 * Example:
 * Given a binary tree 
 *           1
 *          / \
 *         2   3
 *        / \     
 *       4   5    
 * Return 3, which is the length of the path [4,2,1,3] or [5,2,1,3].
 * 
 * Note: The length of path between two nodes is represented by the number of edges between them.
 * 
 */
#include <algorithm>
using namespace std;

struct TreeNode {
  int val;
  TreeNode *left, *right;
  explicit TreeNode(int x = 0, TreeNode *l = nullptr, TreeNode *r = nullptr) : val(x), left(l), right(r) {}
};

int helper(TreeNode *node, int &diameter) {
  if (node == nullptr) {
    return 0;
  }
  int l = helper(node->left, diameter), r = helper(node->right, diameter);
  diameter = max(l + r, diameter);
  return max(l, r) + 1;
}

int diameterOfBT(TreeNode *root) {
  int diameter = 0;
  helper(root, diameter);
  return diameter;
}