/*
 * 1120. Maximum Average Subtree
 *
 * Given the root of a binary tree, return the maximum average value of a subtree of that tree. Answers within 10-5 of
 * the actual answer will be accepted.
 *
 * A subtree of a tree is any node of that tree plus all its descendants.
 *
 * The average value of a tree is the sum of its values, divided by the number of nodes.
 *
 * The number of nodes in the tree is in the range [1, 104].
 * -20000 <= Node.val <= 20000
 */
#include <numeric>
#include <vector>
using namespace std;

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
 public:
  double maximumAverageSubtree(TreeNode *root) {
    // Initialize with the smallest possible double value.
    double maxAvg = numeric_limits<double>::lowest();
    dfs(root, maxAvg);
    return maxAvg;
  }

 private:
  // Returns a pair (sum of values, number of nodes) for the subtree rooted at 'node'.
  // Updates maxAvg with the maximum average found so far.
  pair<int, int> dfs(TreeNode *node, double &maxAvg) {
    if (!node) return {0, 0};

    auto left = dfs(node->left, maxAvg);
    auto right = dfs(node->right, maxAvg);

    int sum = left.first + right.first + node->val;
    int cnt = left.second + right.second + 1;
    double avg = static_cast<double>(sum) / cnt;

    if (avg > maxAvg) maxAvg = avg;

    return {sum, cnt};
  }
};