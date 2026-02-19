/*
 * Binary Tree Preorder Traversal
 * 
 * Given the root of a binary tree, return the preorder traversal of its nodes' values.
 * 
 * Example 1: 
 * Input: root = [1,null,2,3]
 * Output: [1,2,3]
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
 * Output: [1,2]
 * 
 * Example 5:
 * Input: root = [1,null,2]
 * Output: [1,2]
 */
#include <stack>
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

vector<int> preorderTraversal(TreeNode *root) {
  if (root == nullptr) {
    return {};
  }
  vector<int> ans;
  stack<TreeNode *> s;
  s.push(root);
  while (!s.empty()) {
    TreeNode *node = s.top();
    s.pop();
    ans.push_back(node->val);
    if (node->right) {
      s.push(node->right);
    }

    if (node->left) {
      s.push(node->left);
    }
  }
  return ans;
}