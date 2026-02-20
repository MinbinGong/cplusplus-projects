/*
 * Closest Binary Search Tree Value II
 *
 * 1. The number of nodes in the tree is in the range [1, 1000].
 * 2. 1 <= Node.val <= 1000
 * 3. All the values of the tree are unique.
 * 4. There exist some node in the tree where Node.val == k.
 * 5. 1 <= k <= 1000
 */
#include <vector>
#include <deque>
#include <algorithm>
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

// 时间复杂度：O(n)
// 空间复杂度：O(n)
class Solution1 {
 public:
  vector<int> closestKValues(TreeNode *root, double target, int k) {
    vector<int> vals;
    inorder(root, vals);  // 中序遍历得到有序数组

    int n = vals.size();
    // 找到第一个大于等于 target 的位置
    int idx = lower_bound(vals.begin(), vals.end(), target) - vals.begin();

    int left = idx - 1;
    int right = idx;
    vector<int> result;

    // 双指针扩展，取 k 个最接近的值
    while (result.size() < k) {
      if (left < 0) {
        result.push_back(vals[right++]);
      } else if (right >= n) {
        result.push_back(vals[left--]);
      } else {
        if (abs(vals[left] - target) < abs(vals[right] - target)) {
          result.push_back(vals[left--]);
        } else {
          result.push_back(vals[right++]);
        }
      }
    }
    return result;
  }

 private:
  void inorder(TreeNode *node, vector<int> &vals) {
    if (!node) return;
    inorder(node->left, vals);
    vals.push_back(node->val);
    inorder(node->right, vals);
  }
};

// 时间复杂度：O(n)
// 空间复杂度：O(n)
class Solution2 {
public:
    vector<int> closestKValues(TreeNode* root, double target, int k) {
        deque<int> dq;
        inorder(root, target, k, dq);
        return vector<int>(dq.begin(), dq.end());
    }

private:
    void inorder(TreeNode* node, double target, int k, deque<int>& dq) {
        if (!node) return;
        
        inorder(node->left, target, k, dq);
        
        if (dq.size() < k) {
            dq.push_back(node->val);
        } else {
            // 如果当前节点比队首更接近目标值
            if (abs(node->val - target) < abs(dq.front() - target)) {
                dq.pop_front();
                dq.push_back(node->val);
            } else {
                // 剪枝：后续节点只会更远，无需继续遍历
                // 但注意：这里不能直接 return，因为右子树中可能存在更小的值？不，中序遍历有序，当前节点比队首大，
                // 且差距已经更大，后面的节点只会更大，差距只会更大，所以可以安全剪枝[citation:5]。
                // 为了代码简洁，我们继续遍历右子树，但理论上可以提前返回。
            }
        }
        
        inorder(node->right, target, k, dq);
    }
};