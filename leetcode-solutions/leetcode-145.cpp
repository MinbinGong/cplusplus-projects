/*
 * Binary Tree Postorder Traversal
 */
struct TreeNode {
  int val = 0;
  TreeNode *left = nullptr, *right = nullptr;
  explicit TreeNode (int x = 0, TreeNode *l = nullptr, TreeNode *r = nullptr) : val(x), left(l), right(r) {}
};

void helper(TreeNode *root, vector<int> &res) {
  if (root == nullptr) {
    return;
  }

  helper(root->left, res);
  helper(root->right, res);
  res.push_back(root->val);
  return;
}

vector<int> postordderTraversal(TreeNode *root) {
  vector<int> res;
  helper(root, res);
  return res;
}
