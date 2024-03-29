/*
 * Binary Tree Zigzag Level Order Traversal
 * Given the root of a binary tree, return the zigzag level order traversal of its nodes' values.
 * (i.e., from left to right, then right to left for the next level and alternate between).
 * Constraints:
 * 1. The number of nodes in the tree is in the range [0, 2000].
 * 2. -100 <= Node.val <= 100
 */
#include <queue>
#include <vector>
using namespace std;

struct TreeNode {
  int val;
  TreeNode *left, *right;
  TreeNode(int x = 0, TreeNode *l = nullptr, TreeNode *r = nullptr) : val(x), left(l), right(r) {}
};

vector<vector<int>> zigzagLevelOrder(TreeNode *root) {
  if (root == nullptr) {
    return {};
  }

  vector<vector<int>> ans;
  queue<TreeNode *> q;
  q.push(root);

  bool leftToRight = true;
  while (!q.empty()) {
    int size = q.size();
    vector<int> output(size);
    for(int i = 0; i < size; i++) {
      TreeNode *p = q.front();
      q.pop();

      int index = (leftToRight) ? i : (size - i - 1);
      output[index] = p->val;
      if (p->left != nullptr) {
        q.push(p->left);
      }

      if (p->right != nullptr) {
        q.push(p->right);
      }
    }

    leftToRight = !leftToRight;
    ans.push_back(output);
  }
  return ans;
}

