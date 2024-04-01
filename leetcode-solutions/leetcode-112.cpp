/*
 * Path Sum
 * Given the root of a binary tree and an integer targetSum,
 * return true if the tree has a root-to-leaf path
 * such that adding up all the values along the path equals targetSum.
 *
 * A leaf is a node with no children.
 *
 * Constraints:
 * 1. The number of nodes in the tree is in the range [0, 5000].
 * 2. -1000 <= Node.val <= 1000
 * 3. -1000 <= targetSum <= 1000
 */
struct TreeNode {
  int val = 0;
  TreeNode *left = nullptr;
  TreeNode *right = nullptr;
  TreeNode(int x) : val(x) {}
  TreeNode(int x, TreeNode *l, TreeNode *r) : val(x), left(l), right(r) {}
};

bool hasPathSum(TreeNode *root, int targetSum) {
  if (root == nullptr) {
    return false;
  }

  if (root->left == nullptr && root->right == nullptr) {
    return root->val == targetSum;
  }

  return hasPathSum(root->left, targetSum - root->val) ||
    hasPathSum(root->right, targetSum - root->val);
}
