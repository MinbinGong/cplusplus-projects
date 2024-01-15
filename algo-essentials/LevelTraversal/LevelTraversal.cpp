// LevelTraversal.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

struct TreeNode {
  int val = 0;
  TreeNode* left = nullptr;
  TreeNode* right = nullptr;
  TreeNode(int x = 0, TreeNode* l = nullptr, TreeNode* r = nullptr) : val(x), left(l), right(r) {}
};

void traverseRecursive(TreeNode* root, int level, std::vector<std::vector<int>>& result) {
  if (root == nullptr) {
    return;
  }

  if (level > result.size()) {
    result.push_back(std::vector<int>());
  }

  result[level - 1].push_back(root->val);
  traverseRecursive(root->left, level + 1, result);
  traverseRecursive(root->right, level + 1, result);
}

std::vector<std::vector<int>> levelOrderRecursive(TreeNode* root) {
  std::vector<std::vector<int>> result;
  traverseRecursive(root, 1, result);
  return result;
}

std::vector<std::vector<int>> levelOrderIterative(TreeNode* root) {
  std::vector<std::vector<int>> result;
  std::queue<TreeNode*> curr, next;

  if (root == nullptr) {
    return result;
  }

  curr.push(root);

  while (!curr.empty()) {
    std::vector<int> level;
    while (!curr.empty()) {
      TreeNode* node = curr.front();
      curr.pop();
      level.push_back(node->val);
      if (node->left != nullptr) {
        next.push(node->left);
      }

      if (node->right != nullptr) {
        next.push(node->right);
      }
    }
    result.push_back(level);
    swap(next, curr);
  }

  return result;
}

int main() { std::cout << "Hello World!\n"; }

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files
//   to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
