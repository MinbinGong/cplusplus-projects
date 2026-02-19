/*
  Tree level traversal
  Given the root of a binary tree, return the level order traversal of its nodes' values.
  (i.e., from left to right, level by level).
 */
#include <queue>
#include <vector>
using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

vector<vector<int>> levelTraversal(TreeNode *root) {
  if (root == nullptr) {
    return {};
  }

  vector<vector<int>> res;
  queue<TreeNode *> q;
  q.push(root);
  while (!q.empty()) {
    int levelSize = q.size();
    vector<int> output;
    for (int i = 0; i < levelSize; i++) {
      auto p = q.front();
      q.pop();

      output.push_back(p->val);
      if (p->left != nullptr) {
        q.push(p->left);
      }
      if (p->right != nullptr) {
        q.push(p->right);
      }
    }

    res.push_back(output);
  }
  return res;
}