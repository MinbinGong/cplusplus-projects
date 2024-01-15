struct TreeNode {
  int val = 0;
  TreeNode *left = nullptr, *right = nullptr;
  TreeNode(int x = 0, TreeNode *l = nullptr, TreeNode *r = nullptr) : val(x), left(l), right(r) {}
};

int dfs(TreeNode *root, int sum) {
  if (root == nullptr) {
    return 0;
  }

  if (root->left == nullptr && root->right == nullptr) {
    return sum * 10 + root->val;
  }

  return dfs(root->left, sum * 10 + root->val) + dfs(root->right, sum * 10 + root->val);
}

int sumNumbers(TreeNode *root) { return dfs(root, 0); }
