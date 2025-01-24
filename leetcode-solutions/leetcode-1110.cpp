/*
  Delete nodes and return forests

  题目描述
  给定一个整数二叉树和一些整数，求删掉这些整数对应的节点后，剩余的子树

  题解
  这道题最主要需要注意的细节是如果通过递归处理原树，以及需要在什么时候断开指针。同
  时，为了便于寻找待删除节点，可以建立一个哈希表方便查找。笔者强烈建议读者在看完题解后，
  自己写一遍本题，加深对于递归的理解和运用能力
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