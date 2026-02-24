/**
 * 865. Smallest Subtree with all the Deepest Nodes
 *
 * Example 1:
 * Input: root = [3,5,1,6,2,0,8,null,null,7,4]
 * Output: [2,7,4]
 * Explanation:
 * We return the node with value 2, colored in yellow in the diagram.
 * The nodes colored in blue are the deepest nodes of the tree.
 * The input "[3, 5, 1, 6, 2, 0, 8, null, null, 7, 4]" is a serialization of the given tree.
 * The output "[2, 7, 4]" is a serialization of the subtree rooted at the node with value 2.
 * Both the input and output have TreeNode type.
 *
 * Note:
 * The number of nodes in the tree will be between 1 and 500.
 * Each node will have a unique value between 0 and 499.
 *
 */
#include <utility>
using namespace std;

// Definition for a binary tree node.
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
  TreeNode *subtreeWithAllDeepest(TreeNode *root) { return dfs(root).second; }

 private:
  // 返回 {深度, 包含所有最深节点的子树根节点}
  pair<int, TreeNode *> dfs(TreeNode *node) {
    if (!node) return {0, nullptr};
    auto left = dfs(node->left);
    auto right = dfs(node->right);
    if (left.first > right.first) return {left.first + 1, left.second};
    if (right.first > left.first) return {right.first + 1, right.second};
    return {left.first + 1, node};  // 左右深度相等，当前节点即为所求
  }
};