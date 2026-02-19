/*
  Symmetric tree
  Given the root of a binary tree, check whether it is a mirror of itself
  (i.e., symmetric around its center).
 */
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

bool isSymmetric(TreeNode *left, TreeNode *right) {
  if (left == nullptr && right == nullptr) {
    return true;
  }
  if (left == nullptr || right == nullptr) {
    return false;
  }
  if (left->val != right->val) {
    return false;
  }
  return isSymmetric(left->left, left->right) && isSymmetric(right->right, right->left);
}

bool isSymmetric(TreeNode *root) {
  if (root == nullptr) {
    return true;
  }
  return isSymmetric(root->left, root->right);
}