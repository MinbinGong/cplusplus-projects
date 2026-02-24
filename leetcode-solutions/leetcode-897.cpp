/**
 * 897. Increasing Order Search Tree
 *
 * Given a binary search tree, rearrange the tree in in-order so that the leftmost node in the tree is now the root of
 * the tree, and every node has no left child and only 1 right child.
 *
 * Example 1:
 * Input: [5,3,6,2,4,null,8,1,null,null,null,7,9]
 *
 *        5
 *       / \
 *     3    6
 *    / \    \
 *   2   4    8
 *  /        / \
 * 1        7   9
 *
 * Output: [1,null,2,null,3,null,4,null,5,null,6,null,7,null,8,null,9]
 *
 *  1
 *   \
 *    2
 *     \
 *      3
 *       \
 *        4
 *         \
 *          5
 *           \
 *            6
 *             \
 *              7
 *               \
 *                8
 *                 \
 *                  9
 *
 * Note:
 * The number of nodes in the given tree will be between 1 and 100.
 * Each node will have a unique integer value from 0 to 1000.
 */
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
  TreeNode* increasingBST(TreeNode* root) {
    TreeNode dummy(0);       // 虚拟头节点
    TreeNode* cur = &dummy;  // 当前尾节点
    inorder(root, cur);
    return dummy.right;
  }

 private:
  void inorder(TreeNode* node, TreeNode*& cur) {
    if (!node) return;
    // 遍历左子树
    inorder(node->left, cur);
    // 将当前节点接入结果树
    cur->right = node;
    node->left = nullptr;  // 断开左指针
    cur = node;            // 移动尾指针
    // 遍历右子树
    inorder(node->right, cur);
  }
};