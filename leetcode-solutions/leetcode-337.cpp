#include <algorithm>
#include <utility>
using namespace std;

class TreeNode {
 public:
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

pair<int, int> findMaxMoney(TreeNode *root) {
  if (root == nullptr) return {0, 0};
  int choose, not_choose;
  auto left = findMaxMoney(root->left);
  auto right = findMaxMoney(root->right);
  choose = root->val + left.second + right.second;
  not_choose = max(left.first, left.second) + max(right.first, right.second);
  return {choose, not_choose};
}

int rob(TreeNode *root) {
  auto maxPair = findMaxMoney(root);
  return max(maxPair.first, maxPair.second);
}