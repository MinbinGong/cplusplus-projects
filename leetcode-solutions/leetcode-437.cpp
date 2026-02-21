/*
 * Path Sum III
 *
 * Given the root of a binary tree and an integer targetSum, return the number of paths where the sum of the values along the path equals targetSum.
 * 
 * The path does not need to start or end at the root or a leaf, but it must go downwards (i.e., traveling only from parent nodes to child nodes).
 * 
 * Constraints:
 * The number of nodes in the tree is in the range [0, 1000].
 * -109 <= Node.val <= 109
 * -1000 <= targetSum <= 1000
 */

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

int solve(TreeNode *root, int sum, int target) {
  if (root == nullptr) {
    return 0;
  }
  sum += root->val;
  int ans = 0;
  ans += (sum == target) ? 1 : 0;
  ans += solve(root->left, sum, target);
  ans += solve(root->right, sum, target);
  return ans;
}

int pathSum(TreeNode *root, int sum) {
  if (root == nullptr) {
    return 0;
  }

  int ans = 0;
  ans += solve(root, 0, sum);
  ans += pathSum(root->left, sum);
  ans += pathSum(root->right, sum);
  return ans;
}