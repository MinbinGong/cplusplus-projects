/*
 * Sum of left leaves
 * 
 * Given the root of a binary tree, return the sum of all left leaves.
 *
 * Example 1:
 * Input: root = [3,9,20,null,null,15,7]
 * Output: 24
 * Explanation: There are two left leaves in the binary tree, with values 9 and 15 respectively.
 * 
 * Example 2:
 * Input: root = [1]
 * Output: 0
 * 
 * Constraints:
 * The number of nodes in the tree is in the range [1, 1000].
 * -1000 <= Node.val <= 1000
 * 
 */
#include <queue>
#include <set>
using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

int sumOfLeftLeaves(TreeNode *root) {
  if (root == NULL) {
    return 0;
  }
  int sum = 0;
  set<TreeNode *> s;
  queue<TreeNode *> q;
  q.push(root);
  while (!q.empty()) {
    TreeNode *temp = q.front();
    if (temp->left == NULL && temp->right == NULL) {
      if (s.find(temp) != s.end()) {
        sum = sum + temp->val;
      }
    }

    if (temp->left != NULL) {
      q.push(temp->left);
      s.insert(temp->left);
    }
    if (temp->right != NULL) {
      q.push(temp->right);
    }
    q.pop();
  }
  s.clear();
  return sum;
}