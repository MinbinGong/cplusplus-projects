/*
 * Find Mode in Binary Search Tree
 *
 *  Given the root of a binary search tree (BST) with duplicates, return all the mode(s) (i.e., the most frequently
 * occurred element) in it.
 *
 *  If the tree has more than one mode, return them in any order.
 *
 *  Assume a BST is defined as follows:
 *
 *  The left subtree of a node contains only nodes with keys less than or equal to the node's key.
 *  The right subtree of a node contains only nodes with keys greater than or equal to the node's key.
 *  Both the left and right subtrees must also be binary search trees.
 *
 *  Constraints:
 *  The number of nodes in the tree is in the range [1, 104].
 *  -105 <= Node.val <= 105
 *
 */
#include <vector>
using namespace std;

/**
 * Definition for a binary tree node.
 */
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
  vector<int> findMode(TreeNode* root) {
    vector<int> modes;
    int curVal = 0, curCount = 0, maxCount = 0;
    inorder(root, curVal, curCount, maxCount, modes);
    // Handle the last value
    if (curCount > maxCount) {
      modes.clear();
      modes.push_back(curVal);
    } else if (curCount == maxCount && curCount > 0) {
      modes.push_back(curVal);
    }
    return modes;
  }

 private:
  void inorder(TreeNode* node, int& curVal, int& curCount, int& maxCount, vector<int>& modes) {
    if (!node) return;
    inorder(node->left, curVal, curCount, maxCount, modes);

    // Process current node
    if (curCount == 0) {
      curVal = node->val;
      curCount = 1;
    } else if (node->val == curVal) {
      curCount++;
    } else {
      // Previous value ended
      if (curCount > maxCount) {
        maxCount = curCount;
        modes.clear();
        modes.push_back(curVal);
      } else if (curCount == maxCount) {
        modes.push_back(curVal);
      }
      curVal = node->val;
      curCount = 1;
    }

    inorder(node->right, curVal, curCount, maxCount, modes);
  }
};