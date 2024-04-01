/*
 * Minimum Depth of Binary Tree
 * Given a binary tree, find its minimum depth.
 * The minimum depth is the number of nodes along the shortest path from the root node down to the nearest leaf node.
 * Note: A leaf is a node with no children.
 *
 * Constraints:
 * 1. The number of nodes in the tree is in the range [0, 105].
 * 2. -1000 <= Node.val <= 1000
 */
struct TreeNode {
  int val = 0;
  TreeNode *left = nullptr;
  TreeNode *right = nullptr;
  TreeNode(int x) : val(x) {}
  TreeNode(int x, TreeNode *l, TreeNode *r) : val(x), left(l), right(r) {}
};

int solve (TreeNode *root) {
  if (root == nullptr) {
    return 0;
  }

  if (root->left == nullptr && root->right == nullptr) {
    return 1;
  }

  if (root->left == nullptr) {
    return solve(root->right) + 1;
  }

  if (root->right == nullptr) {
    return solve(root->left) + 1;
  }

  int leftHeight = solve(root->left);
  int rightHeight = solve(root->right);

  return min(leftHeight, rightHeight) + 1;
}

int minDepth(TreeNode *root) {
  return solve(root);
}
