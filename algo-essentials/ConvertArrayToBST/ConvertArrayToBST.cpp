#include <algorithm>
#include <vector>

struct TreeNode {
  int val = 0;
  TreeNode *left = nullptr, *right = nullptr;
  TreeNode(int x = 0, TreeNode *l = nullptr, TreeNode *r = nullptr) : val(x), left(l), right(r) {}
};

template <typename RandomAccessIterator>
TreeNode *sortedArrayToBST(RandomAccessIterator first, RandomAccessIterator last) {
  const auto length = std::distance(first, last);

  if (length <= 0) {
    return nullptr;
  }

  auto mid = first + length >> 1;
  TreeNode *root = new TreeNode(*mid);
  root->left = sortedArrayToBST(first, mid);
  root->right = sortedArrayToBST(mid + 1, last);

  return root;
}

TreeNode *sortedArrayToBST(std::vector<int> &num) { return sortedArrayToBST(num.begin(), num.end()); }
