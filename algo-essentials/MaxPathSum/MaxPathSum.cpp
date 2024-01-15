#include <algorithm>
#include <climits>
#include <vector>

struct TreeNode {
  int val = 0;
  TreeNode *left = nullptr, *right = nullptr;
  TreeNode(int x = 0, TreeNode *l = nullptr, TreeNode *r = nullptr) : val(x), left(l), right(r) {}
};

int dfs(TreeNode const *root, int &max_sum) {
  if (root == nullptr) {
    return 0;
  }

  int left = dfs(root->left, max_sum);
  int right = dfs(root->right, max_sum);
  int sum = root->val;
  if (left > 0) {
    sum += left;
  }
  if (right > 0) {
    sum += right;
  }

  max_sum = max_sum > sum ? max_sum : sum;
  return std::max(right, left) > 0 ? max(right, left) + root->val : root->val;
}

int maxPathSum(TreeNode *root) {
  int max_sum = INT_MIN;
  dfs(root, max_sum);
  return max_sum;
}
