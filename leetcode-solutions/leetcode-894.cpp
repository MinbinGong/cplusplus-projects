/**
 * 894. All Possible Full Binary Trees
 *
 * A full binary tree is a binary tree where each node has exactly 0 or 2 children.
 * Return a list of all possible full binary trees with N nodes.  Each element of the answer is the root node of one
 * possible tree. Each node of each tree in the answer must have node.val = 0. You may return the final list of trees in
 * any order.
 *
 * Example 1:
 * Input: 7
 * Output:
 * [[0,0,0,null,null,0,0,null,null,0,0],[0,0,0,null,null,0,0,0,0],[0,0,0,0,0,0,0],[0,0,0,0,0,null,null,null,null,0,0],[0,0,0,0,0,null,null,0,0]]
 * Explanation:
 *
 * Note:
 * 1 <= N <= 20
 *
 */
#include <vector>
#include <unordered_map>
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
  vector<TreeNode*> allPossibleFBT(int n) {
    // 偶数个节点无法构成满二叉树
    if (n % 2 == 0) return {};
    unordered_map<int, vector<TreeNode*>> memo;
    return build(n, memo);
  }

 private:
  vector<TreeNode*> build(int n, unordered_map<int, vector<TreeNode*>>& memo) {
    if (memo.count(n)) return memo[n];
    vector<TreeNode*> res;
    if (n == 1) {
      res.push_back(new TreeNode(0));
      return memo[n] = res;
    }
    // 左子树节点数必须为奇数，从 1 到 n-2 步长为 2
    for (int leftCnt = 1; leftCnt < n; leftCnt += 2) {
      int rightCnt = n - 1 - leftCnt;
      vector<TreeNode*> leftTrees = build(leftCnt, memo);
      vector<TreeNode*> rightTrees = build(rightCnt, memo);
      for (TreeNode* left : leftTrees) {
        for (TreeNode* right : rightTrees) {
          TreeNode* root = new TreeNode(0);
          root->left = left;
          root->right = right;
          res.push_back(root);
        }
      }
    }
    return memo[n] = res;
  }
};