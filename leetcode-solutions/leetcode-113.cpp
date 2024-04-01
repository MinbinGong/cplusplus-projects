/*
 * Path Sum II
 * Given the root of a binary tree and an integer targetSum,
 * return all root-to-leaf paths where the sum of the node values in the path equals targetSum.
 * Each path should be returned as a list of the node values, not node references.
 *
 * A root-to-leaf path is a path starting from the root and ending at any leaf node.
 * A leaf is a node with no children.
 */
#include <vector>
using namespace std;

struct TreeNode {
  int val = 0;
  TreeNode *left = nullptr;
  TreeNode *right = nullptr;
  TreeNode(int x) : val(x) {}
  TreeNode(int x, TreeNode *l, TreeNode *r) : val(x), left(l), right(r) {}
};

void dfs(TreeNode *root, int target, vector<int> temp, vector<vector<int>> &ans) {
  if (root == nullptr) {
    return;
  }

  target -= root->val;
  temp.push_back(root->val);
  if (target == 0 && root->left == nullptr && root->right == nullptr) {
    ans.push_back(temp);
  }

  dfs(root->left, target, temp, ans);
  dfs(root->right, target, temp, ans);
}

vector<vector<int>> pathSum(TreeNode *root, int targetSum) {
  vector<vector<int>> ans;
  dfs(root, targetSum, {}, ans);
  return ans;
}
