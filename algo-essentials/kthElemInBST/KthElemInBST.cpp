#include <stack>

struct TreeNode {
  int val = 0;
  TreeNode *left = nullptr, *right = nullptr;
  TreeNode(int x = 0, TreeNode *l = nullptr, TreeNode *r = nullptr) : val(x), left(l), right(r) {}
};

int kthSmallest(TreeNode *root, int k) {
  std::stack<TreeNode *> st;
  TreeNode *p = root;

  while (!st.empty() || p != nullptr) {
    if (p != nullptr) {
      st.push(p);
      p = p->left;
    } else {
      p = st.top();
      st.pop();
      --k;
      if (k == 0) {
        return p->val;
      }
      p = p->right;
    }
  }

  return -1;
}
