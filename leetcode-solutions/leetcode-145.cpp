/*
 * Binary Tree Postorder Traversal
 * 
 * Given the root of a binary tree, return the postorder traversal of its nodes' values.
 * 
 * Example 1: 
 * Input: root = [1,null,2,3]
 * Output: [3,2,1]
 * 
 * Example 2:
 * Input: root = []
 * Output: []
 * 
 * Example 3:
 * Input: root = [1]
 * Output: [1]
 * 
 * Example 4:
 * Input: root = [1,2]
 * Output: [2,1]
 * 
 * Example 5:
 * Input: root = [1,null,2]
 * Output: [2,1]
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
