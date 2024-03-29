/*
 * Validate Binary Search Tree
 * Given the root of a binary tree, determine if it is a valid binary search tree (BST).
 * A valid BST is defined as follows:
 * 1. The left subtree of a node contains only nodes with keys less than the node's key.
 * 2. The right subtree of a node contains only nodes with keys greater than the node's key.
 * 3. Both the left and right subtrees must also be binary search trees.
 *
 * Constraints:
 * 1. The number of nodes in the tree is in the range [1, 104].
 * 2. -231 <= Node.val <= 231 - 1
 */
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *l = nullptr, TreeNode *r = nullptr) : val(x), left(l), right(r) {}
};

bool validateBST(TreeNode *root, long min, long max) {
  if (root == nullptr) {
    return true;
  }

  if (root->val <= min || root->val >= max) {
    return false;
  }

  return validateBST(root->left, min, root->val) && validateBST(root->right, root->val, max);
}

bool isValidBST(TreeNode *root) {
  if (root == nullptr) {
    return true;
  }

  return validateBST(root, LONG_MIN, LONG_MAX);
}
