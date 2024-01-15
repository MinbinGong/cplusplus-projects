/*
Trim a Binary Search Tree
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