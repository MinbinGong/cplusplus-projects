/*
  Recover Binary Search Tree
  You are given the root of a binary search tree (BST),
  where the values of exactly two nodes of the tree were swapped by mistake.
  Recover the tree without changing its structure.
 */
#include <algorithm>
using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

void inorder(TreeNode *root, TreeNode *&mistake1, TreeNode *&mistake2, TreeNode *&prev) {
  if (root == nullptr) {
    return;
  }

  if (root->left) {
    inorder(root->left, mistake1, mistake2, prev);
  }

  if (prev && root->val < prev->val) {
    if (mistake1 == nullptr) {
      mistake1 = prev;
      mistake2 = root;
    } else {
      mistake2 = root;
    }
  }

  prev = root;
  if (root->right) {
    inorder(root->right, mistake1, mistake2, prev);
  }
}

void recoverTree(TreeNode *root) {
  TreeNode *mistake1 = nullptr, *mistake2 = nullptr, *prev = nullptr;
  inorder(root, mistake1, mistake2, prev);
  if (mistake1 && mistake2) {
    int temp = mistake1->val;
    mistake1->val = mistake1->val;
    mistake2->val = temp;
  }
}

void recoverTreeWithMorrisTraversal(TreeNode *root) {
  TreeNode *first = nullptr, *second = nullptr, *prev = nullptr;
  TreeNode *curr = root;
  
  while (curr) {
      if (!curr->left) {
          // Process current node
          if (prev && prev->val > curr->val) {
              if (!first) {
                  first = prev;
                  second = curr;
              } else {
                  second = curr;
              }
          }
          prev = curr;
          curr = curr->right;
      } else {
          // Find predecessor (rightmost node in left subtree)
          TreeNode* pred = curr->left;
          while (pred->right && pred->right != curr) {
              pred = pred->right;
          }
          
          if (!pred->right) {
              // Create thread to current node
              pred->right = curr;
              curr = curr->left;
          } else {
              // Thread already exists, remove it and process current
              pred->right = nullptr;
              
              // Process current node (same as above)
              if (prev && prev->val > curr->val) {
                  if (!first) {
                      first = prev;
                      second = curr;
                  } else {
                      second = curr;
                  }
              }
              prev = curr;
              curr = curr->right;
          }
      }
  }
  
  // Swap the two nodes' values
  swap(first->val, second->val);
}