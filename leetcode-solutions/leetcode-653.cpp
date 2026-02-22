/*
 * 653. Two Sum IV - Input is a BST
 *
 * Given a Binary Search Tree and a target number, return true if there exist two elements in the BST such that their
 * sum is equal to the given target.
 *
 * Example 1:
 *
 * Input:
 *     5
 *    / \
 *   3   6
 *  / \   \
 * 2   4   7
 *
 * Target = 9
 *
 * Output: True
 *
 * Example 2:
 *
 * Input:
 *     5
 *    / \
 *   3   6
 *  / \   \
 * 2   4   7
 *
 * Target = 28
 *
 * Output: False
 *
 * Note:
 *
 * The number of nodes in the tree is between 1 and 10^4.
 * Each node's value is between -10^5 and 10^5.
 *
 */
#include <unordered_set>
using namespace std;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution {
 public:
  bool findTarget(TreeNode* root, int k) {
    unordered_set<int> seen;
    return dfs(root, k, seen);
  }

 private:
  bool dfs(TreeNode* node, int k, unordered_set<int>& seen) {
    if (!node) return false;
    // Check if complement exists
    if (seen.count(k - node->val)) return true;
    // Add current value
    seen.insert(node->val);
    // Recurse left and right
    return dfs(node->left, k, seen) || dfs(node->right, k, seen);
  }
};