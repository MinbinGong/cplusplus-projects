/*
 * Closest Leaf in a Binary Tree
 *
 * Given a binary tree where every node has a unique value, and a target key k, find the value of the nearest leaf node
 * to target k in the tree.
 *
 * Here, nearest to a leaf means the least number of edges travelled on the binary tree to reach any leaf of the tree.
 * Also, a node is called a leaf if it has no children.
 *
 * In the following examples, the input tree is represented in flattened form row by row. The actual root tree given
 * will be a TreeNode object.
 *
 * Example 1:
 *
 * Input:
 * root = [1, 3, 2], k = 1
 * Diagram of binary tree:
 *           1
 *          / \
 *         3   2
 *
 * Output: 2 (or 3)
 *
 * Explanation: Either 2 or 3 is the nearest leaf node to the target of 1.
 *
 * Example 2:
 *
 * Input:
 * root = [1], k = 1
 * Output: 1
 *
 * Explanation: The nearest leaf node is the root node itself.
 *
 * Example 3:
 *
 * Input:
 * root = [1, 2, 3, 4, null, null, null, 5, null, 6], k = 2
 * Diagram of binary tree:
 *              1
 *             / \
 *            2   3
 *           /
 *          4
 *         /
 *        5
 *       /
 *      6
 *
 * Output: 3
 *
 * Explanation: The leaf node with value 3 (and not the leaf node with value 6) is nearest to the node with value 2.
 *
 * Note:
 * 1. root represents a binary tree with at least 1 node and at most 1000 nodes.
 * 2. Every node has a unique node.val in range [1, 1000].
 * 3. There exists some node in the given binary tree for which node.val == k.
 *
 */
#include <queue>
#include <unordered_map>
#include <unordered_set>
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
 private:
  unordered_map<TreeNode*, TreeNode*> parent;  // 存储每个节点的父节点
  TreeNode* targetNode = nullptr;              // 目标值k对应的节点
  unordered_set<TreeNode*> visited;            // BFS访问标记

  // DFS遍历树，记录父节点信息并找到目标节点
  void dfs(TreeNode* node, TreeNode* par, int k) {
    if (!node) return;

    // 记录父节点
    if (par) parent[node] = par;

    // 找到目标节点
    if (node->val == k) targetNode = node;

    // 递归遍历左右子树
    dfs(node->left, node, k);
    dfs(node->right, node, k);
  }

 public:
  int findClosestLeaf(TreeNode* root, int k) {
    // 1. DFS建立父节点映射并找到目标节点
    dfs(root, nullptr, k);

    // 2. BFS从目标节点开始搜索最近的叶子
    queue<TreeNode*> q;
    q.push(targetNode);
    visited.insert(targetNode);

    while (!q.empty()) {
      TreeNode* curr = q.front();
      q.pop();

      // 如果是叶子节点，直接返回其值
      if (!curr->left && !curr->right) {
        return curr->val;
      }

      // 向三个方向扩展：左孩子、右孩子、父节点
      if (curr->left && !visited.count(curr->left)) {
        visited.insert(curr->left);
        q.push(curr->left);
      }
      if (curr->right && !visited.count(curr->right)) {
        visited.insert(curr->right);
        q.push(curr->right);
      }
      if (parent.count(curr) && !visited.count(parent[curr])) {
        visited.insert(parent[curr]);
        q.push(parent[curr]);
      }
    }

    return -1;  // 理论上不会执行到这里
  }
};