/*
 * Balanced binary tree
 * Given a binary tree, determine if it is height-balanced.
 * For this problem, a height-balanced binary tree is defined as:
 * a binary tree in which the left and right subtrees of every node differ in height by no more than 1.
 */

struct TreeNode {
  int val = 0;
  TreeNode *left = nullptr;
  TreeNode *right = nullptr;
  TreeNode(int x) : val(0){}
  TreeNode(int x, TreeNode *l, TreeNode *r) : val(x), left(l), right(r) {}
};

int height (TreeNode *root) {
  if (root == nullptr) {
    return 0;
  }

  int left = height(root->left);
  int right = height(root->right);

  return max(left, right) + 1;
}

bool isBalanced (TreeNode *root) {
  if (root == nullptr) {
    return true;
  }

  bool left = isBalanced(root->left);
  bool right = isBalanced(root->right);
  bool diff = abs(root->left) - height(root->right) <= 1;
  if (left & right & diff) {
    return true;
  } else {
    return false;
  }
}
