// BSTConstruction.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

struct TreeNode {
  int val = 0;
  TreeNode *left = nullptr, *right = nullptr;
  TreeNode(int x = 0, TreeNode* l = nullptr, TreeNode* r = nullptr) : val(x), left(l), right(r) {}
};

template <typename InputIt>
TreeNode* buildTree(InputIt in_first, InputIt in_last, InputIt post_first, InputIt post_last) {
  if (in_first == in_last) {
    return nullptr;
  }

  if (post_first == post_last) {
    return nullptr;
  }

  const auto val = *std::prev(post_last);
  TreeNode* root = new TreeNode(val);

  auto in_root_pos = std::find(in_first, in_last, val);
  auto left_size = std::distance(in_first, in_root_pos);
  auto post_left_last = std::next(post_first, left_size);

  root->left = buildTree(in_first, in_root_pos, post_first, post_left_last);
  root->right = buildTree(std::next(in_root_pos), in_last, post_left_last, std::prev(post_last));

  return root;
}

TreeNode* buildTree(std::vector<int>& inorder, std::vector<int>& postorder) {
  return buildTree(std::begin(inorder), std::end(inorder), std::begin(postorder), std::end(postorder));
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
