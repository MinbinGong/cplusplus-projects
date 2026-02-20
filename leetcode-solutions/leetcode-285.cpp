/*
 * Inorder Successor in BST
 *
 * Given the root of a binary search tree and a node p in it, return the in-order successor of that node in the BST.
 * If the given node has no in-order successor in the tree, return null.
 *
 * The successor of a node p is the node with the smallest key greater than p.val.
 *
 * Constraints:
 * 1. The number of nodes in the tree is in the range [1, 104].
 * 2. -105 <= Node.val <= 105
 * 3. All Nodes will have unique values.
 */
#include <iostream>
#include <stack>
using namespace std;

 /**
 * Definition for a binary tree node.
 */
struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// Solution1: Iterative
class Solution1 {
 public:
  TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
    TreeNode* successor = nullptr;

    while (root != nullptr) {
      if (p->val < root->val) {
        // 当前节点可能是后继，记录下来
        successor = root;
        // 继续向左找，看是否有更小的候选
        root = root->left;
      } else {
        // p->val >= root->val，后继在右子树
        root = root->right;
      }
    }

    return successor;
  }
};

// Solution2: Recursive
class Solution2 {
public:
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        stack<TreeNode*> st;
        TreeNode* prev = nullptr;
        TreeNode* curr = root;
        
        while (!st.empty() || curr != nullptr) {
            // 一路向左
            while (curr != nullptr) {
                st.push(curr);
                curr = curr->left;
            }
            
            curr = st.top();
            st.pop();
            
            // 如果前一个节点就是 p，当前节点就是后继
            if (prev == p) {
                return curr;
            }
            
            prev = curr;
            curr = curr->right;
        }
        
        return nullptr;
    }
};