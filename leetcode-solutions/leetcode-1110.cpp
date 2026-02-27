/*
 * Delete nodes and return forests
 * 
 * Given the root of a binary tree, each node in the tree has a distinct value.
 * 
 * After deleting all nodes with a value in to_delete, we are left with a forest (a disjoint union of trees).
 * 
 * Return the roots of the trees in the remaining forest. You may return the result in any order.
 * 
 * 1 <= to_delete.length <= 1000
 * 1 <= to_delete[i] <= 1000
 * The number of nodes in the given tree is at most 1000.
 * Each node has a distinct value between 1 and 1000.
 */
#include <unordered_set>
#include <vector>
using namespace std;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

TreeNode* helper(TreeNode* root, unordered_set<int>& dict, vector<TreeNode*>& forest) {
  if (root == nullptr) {
    return root;
  }

  root->left = helper(root->left, dict, forest);
  root->right = helper(root->right, dict, forest);

  if (dict.count(root->val)) {
    if (root->left) {
      forest.push_back(root->left);
    }
    if (root->right) {
      forest.push_back(root->right);
    }
    root = nullptr;
  }
  return root;
}

vector<TreeNode*> delNodes(TreeNode* root, vector<int>& toDelete) {
  vector<TreeNode*> forest;
  unordered_set<int> dict(toDelete.begin(), toDelete.end());
  root = helper(root, dict, forest);
  if (root) {
    forest.push_back(root);
  }
  return forest;
}