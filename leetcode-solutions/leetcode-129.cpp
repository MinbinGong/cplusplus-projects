/*
  Sum Root to Leaf Numbers

  You are given the root of a binary tree containing digits from 0 to 9 only.

  Each root-to-leaf path in the tree represents a number.

  For example, the root-to-leaf path 1 -> 2 -> 3 represents the number 123.
  Return the total sum of all root-to-leaf numbers. Test cases are generated so that the answer will fit in a 32-bit integer.

  A leaf node is a node with no children.
*/
struct TreeNode
{
  int val = 0;
  TreeNode *left = nullptr;
  TreeNode *right = nullptr;
  explicit TreeNode(int x = 0, TreeNode *left = nullptr, TreeNode *right = nullptr) : val(x), left(left), right(right) {}
};

void solve(TreeNode *curr, int sum, int &totalSum) {
  int temp = sum;
  sum = sum * 10 + curr->val;
  if (curr->left == nullptr && curr->right == nullptr)
  {
    totalSum += sum;
    return;
  }
  
  if (curr->left != nullptr)
  {
    solve(curr->left, sum, totalSum);
  }
  if (curr->right != nullptr)
  {
    solve(curr->right, sum, totalSum);
  }
  sum = temp;
}

int sumNumbers(TreeNode *root) {
  int totalSum = 0;
  solve(root, 0, totalSum);
  return totalSum;
}
