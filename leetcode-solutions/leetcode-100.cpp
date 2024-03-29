/*
 * Same Tree
 *
 * Given the roots of two binary trees p and q, write a function to check if they are the same or not.
 * Two binary trees are considered the same if they are structurally identical, and the nodes have the same value.
 */
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x = 0, TreeNode *l = nullptr, TreeNode *r = nullptr) : val(x), left(l), right(r) {}
};

bool isSameTree(TreeNode *p, TreeNode *q) {
  if (p == nullptr && q == nullptr) {
    return true;
  }

  if (p != nullptr && q == nullptr) {
    return false;
  }

  if (p == nullptr && q != nullptr) {
    return false;
  }

  if (p->val != q->val) {
    return false;
  }

  return isSameTree(p->right, q->right) && isSameTree(p->left, q->left);
}

