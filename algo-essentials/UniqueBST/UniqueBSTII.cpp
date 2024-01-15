#include <algorithm>
#include <vector>

struct TreeNode {
  int val = 0;
  TreeNode *left = nullptr, *right = nullptr;
  TreeNode(int x = 0, TreeNode *l = nullptr, TreeNode *r = nullptr) : val(x), left(l), right(r) {}
};

std::vector<TreeNode *> generate(int start, int end) {
  std::vector<TreeNode *> subTree;
  if (start > end) {
    subTree.push_back(nullptr);
    return subTree;
  }

  for (size_t k = start; k <= end; k++) {
    std::vector<TreeNode *> leftSubs = generate(start, k - 1);
    std::vector<TreeNode *> rightSubs = generate(k + 1, end);

    for (auto i : leftSubs) {
      for (auto j : rightSubs) {
        TreeNode *node = new TreeNode(k);
        node->left = i;
        node->right = j;
        subTree.push_back(node);
      }
    }
  }

  return subTree;
}

std::vector<TreeNode *> generateTrees(int n) {
  if (n == 0) {
    return std::vector<TreeNode *>();
  }

  return generate(1, n);
}
