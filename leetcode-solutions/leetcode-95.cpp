/*
 * Given an integer n, return all the structurally unique BST's (binary search trees),
 * which has exactly n nodes of unique values from 1 to n.
 * Return the answer in any order.
 */
#include <map>
#include <vector>
using namespace std;

struct TreeNode {
  int val;
  TreeNode *left, *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *l, TreeNode *r) : val(x), left(l), right(r) {}
};

vector<TreeNode *> solve(map<pair<int, int>, vector<TreeNode *>> &dp, int start, int end) {
  if (start > end) {
    return dp[{start, end}] = {nullptr};
  }

  if (start == end) {
    TreeNode *temp = new TreeNode(start);
    return dp[{start, end}] = {temp};
  }

  if (dp.find({start, end}) != dp.end()) {
    return dp[{start, end}];
  }

  vector<TreeNode *> ret;

  for (int i = start; i <= end; i++) {
    auto a = solve(dp, start, i - 1);
    auto b = solve(dp, i + 1, end);

    for (auto node : a) {
        for (auto c : b) {
            auto root = new TreeNode(i);
            root->left = node;
            root->right = c;
            ret.push_back(root);
        }
    }
  }

  return dp[{start, end}] = ret;
}

vector<TreeNode *> generateTrees(int n) {
    map<pair<int, int>, vector<TreeNode*>> dp;
    return solve (dp, 1, n);
}
