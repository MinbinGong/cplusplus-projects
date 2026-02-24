/**
 * 863. All Nodes Distance K in Binary Tree
 *
 * Example 1:
 * Input: root = [3,5,1,6,2,0,8,null,null,7,4], target = 5, K = 2
 * Output: [7,4,1]
 * Explanation:
 * The nodes that are a distance 2 from the target node (with value 5)
 * have values 7, 4, and 1.
 *
 * Note:
 * The given tree is non-empty.
 * Each node in the tree has unique values 0 <= node.val <= 500.
 * The target node is a node in the tree.
 * 0 <= K <= 1000.
 *
 */

#include <queue>
#include <unordered_map>
#include <vector>
#include <unordered_set>
#include <functional>
using namespace std;

// Definition for a binary tree node.
struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
 public:
  vector<int> distanceK(TreeNode* root, TreeNode* target, int K) {
    // 1. 记录每个节点的父节点
    unordered_map<TreeNode*, TreeNode*> parent;
    function<void(TreeNode*, TreeNode*)> dfs = [&](TreeNode* node, TreeNode* par) {
      if (!node) return;
      parent[node] = par;
      dfs(node->left, node);
      dfs(node->right, node);
    };
    dfs(root, nullptr);

    // 2. 从 target 开始 BFS
    queue<TreeNode*> q;
    unordered_set<TreeNode*> visited;
    q.push(target);
    visited.insert(target);
    int dist = 0;
    vector<int> ans;

    while (!q.empty()) {
      int size = q.size();
      if (dist == K) {
        for (int i = 0; i < size; ++i) {
          ans.push_back(q.front()->val);
          q.pop();
        }
        return ans;
      }
      for (int i = 0; i < size; ++i) {
        TreeNode* cur = q.front();
        q.pop();
        // 左孩子
        if (cur->left && !visited.count(cur->left)) {
          visited.insert(cur->left);
          q.push(cur->left);
        }
        // 右孩子
        if (cur->right && !visited.count(cur->right)) {
          visited.insert(cur->right);
          q.push(cur->right);
        }
        // 父节点
        TreeNode* par = parent[cur];
        if (par && !visited.count(par)) {
          visited.insert(par);
          q.push(par);
        }
      }
      ++dist;
    }
    return ans;  // 理论上不会执行到这里
  }
};