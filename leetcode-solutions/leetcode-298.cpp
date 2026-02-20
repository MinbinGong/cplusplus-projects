/*
 * Binary Tree Longest Consecutive Sequence
 *
 * Given the root of a binary tree, return the length of the longest consecutive sequence path.
 *
 * A consecutive sequence path is a path where the values increase by one along the path.
 *
 * Note that the path can start at any node in the tree, and you cannot go from a node to its parent in the path.
 *
 * Constraints:
 * 1. The number of nodes in the tree is in the range [1, 3 * 104].
 * 2. -3 * 104 <= Node.val <= 3 * 104
 * 3. The values of the nodes in the tree are unique.
 * 4. The height of the tree will not exceed 2000.
 */
#include <algorithm>
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

class Solution1 {
 public:
  int longestConsecutive(TreeNode* root) {
    if (root == nullptr) return 0;
    int maxLen = 0;
    dfs(root, nullptr, 0, maxLen);
    return maxLen;
  }

 private:
  void dfs(TreeNode* node, TreeNode* parent, int currentLen, int& maxLen) {
    if (node == nullptr) return;

    // 判断是否与父节点连续
    if (parent != nullptr && node->val == parent->val + 1) {
      currentLen++;
    } else {
      currentLen = 1;  // 不连续则重新开始计数
    }

    maxLen = max(maxLen, currentLen);

    // 递归左右子树
    dfs(node->left, node, currentLen, maxLen);
    dfs(node->right, node, currentLen, maxLen);
  }
};

class Solution2 {
public:
    int longestConsecutive(TreeNode* root) {
        return longest(root, nullptr, 0);
    }

private:
    int longest(TreeNode* node, TreeNode* parent, int len) {
        if (!node) return len;

        // 判断连续性
        len = (parent && node->val == parent->val + 1) ? len + 1 : 1;

        // 返回当前子树中的最大值（当前节点序列长度 vs 左右子树中的最大值）
        return max(len, max(longest(node->left, node, len), longest(node->right, node, len)));
    }
};