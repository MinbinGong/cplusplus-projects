/*
 * Binary Tree Level Order Traversal II
 * Given the root of a binary tree, return the bottom-up level order traversal of its nodes' values.
 * (i.e., from left to right, level by level from leaf to root).
 *
 * Constraints:
 * 1. The number of nodes in the tree is in the range [0, 2000].
 * 2. -1000 <= Node.val <= 1000
 */
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    explicit TreeNode(int x = 0, TreeNode *l = nullptr, TreeNode *r = nullptr) : val(x), left(l), right(r) {}
};

vector<vector<int>> levelOrderBottom(TreeNode *root) {
    if (root == nullptr) {
        return {};
    }

    vector<vector<int>> ans;
    queue<TreeNode *> q;
    q.push(root);
    q.push(nullptr);
    vector<int> temp;

    while(!q.empty()) {
        auto it = q.front();
        q.pop;
        if (it != nullptr) {
            temp.push_back(it->val);
        }

        if (it == nullptr) {
            ans.push_back(temp);
            temp.clear();
            if (!q.empty()) {
                q.push(nullptr);
            }
        } else {
            if (it->left) {
                q.push(it->left);
            }

            if (it->right) {
                q.push(it->right);
            }
        }
    }

    reverse(ans.begin(), ans.end());
    return ans;
}
