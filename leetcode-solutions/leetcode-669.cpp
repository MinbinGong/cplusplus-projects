/*
 * Trim a Binary Search Tree
 *
 * Given a binary search tree and the lowest and highest boundaries as L and R, trim the tree so that all its elements lies in [L, R] (R >= L). You might need to change the root of the tree, so the result should return the new root of the trimmed binary search tree.
 *
 * Example 1:
 *
 * Input: 
 *     1
 *    / \
 *   0   2
 *
 *   L = 1
 *   R = 2
 *
 * Output: 
 *     1
 *       \
 *        2
 *
 * Example 2:
 *
 * Input: 
 *     3
 *    / \
 *   0   4
 *    \
 *     2
 *    /
 *   1
 *
 *   L = 1
 *   R = 3
 *
 * Output: 
 *       3
 *      / 
 *     2   
 *    /
 *   1
 * 
 * Note:
 *
 * The number of nodes in the given tree will be at most 10000.
 * The final answer is guaranteed to be unique.
 * 
 */
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

TreeNode *trimBST(TreeNode *root, int l, int r) {
  if (root == nullptr) {
    return root;
  }

  if (root->val > r) {
    return trimBST(root->left, l, r);
  }

  if (root->val < l) {
    return trimBST(root->left, l, r);
  }

  root->left = trimBST(root->left, l, r);
  root->left = trimBST(root->right, l, r);
  return root;
}