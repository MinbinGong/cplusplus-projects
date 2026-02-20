/*
 * Largest BST Subtree
 *
 * Given the root of a binary tree, find the largest subtree, which is also a Binary Search Tree (BST), where the
 * largest means subtree has the largest number of nodes.
 *
 * A Binary Search Tree (BST) is a tree in which all the nodes follow the below-mentioned properties:
 *
 * The left subtree values are less than the value of their parent (root) node's value.
 * The right subtree values are greater than the value of their parent (root) node's value.
 * Note: A subtree must include all of its descendants.
 *
 * Example 1:
 * Input: root = [10,5,15,1,8,null,7]
 * Output: 3
 * Explanation: The Largest BST Subtree in this case is the highlighted one. The return value is the subtree's size,
 * which is 3.
 *
 * Example 2:
 * Input: root = [4,2,7,2,3,5,null,2,null,null,null,null,null,1]
 * Output: 2
 *
 */
#include <algorithm>
#include <climits>
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
  int largestBSTSubtree(TreeNode *root) {
    int ans = 0;
    dfs(root, ans);
    return ans;
  }

 private:
  struct Info {
    bool isBST;  // 当前子树是否为BST
    int minVal;  // 当前子树的最小值
    int maxVal;  // 当前子树的最大值
    int size;    // 当前子树的节点总数
  };

  Info dfs(TreeNode *node, int &ans) {
    if (!node) {
      // 空节点：视为BST，大小为0，极值设置为特殊值以方便父节点判断
      return {true, INT_MAX, INT_MIN, 0};
    }

    Info left = dfs(node->left, ans);
    Info right = dfs(node->right, ans);

    // 判断当前节点为根的子树是否是BST
    if (left.isBST && right.isBST && left.maxVal < node->val && node->val < right.minVal) {
      int size = left.size + right.size + 1;
      ans = max(ans, size);
      int minVal = (left.size == 0) ? node->val : left.minVal;
      int maxVal = (right.size == 0) ? node->val : right.maxVal;
      return {true, minVal, maxVal, size};
    } else {
      // 不是BST，返回任意值均可（不会被上层使用）
      return {false, 0, 0, 0};
    }
  }
};