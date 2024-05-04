/*
 * Binary Tree Right Side View
 *
 * Given the root of a binary tree, imagine yourself standing on the right side of it,
 * return the values of the nodes you can see ordered from top to bottom.
 */
#include <vector>
#include <queue>
using namespace std;

struct TreeNode {
    int val = 0;
    TreeNode *left = nullptr;
    TreeNode *right = nullptr;
    explicit TreeNode(int x = 0, TreeNode *left = nullptr, TreeNode *right = nullptr) : val(x), left(left), right(right) {}
};

vector<int> rightSideView(TreeNode *root) {
    if (root == nullptr) {
        return {};
    }

    vector<int> ans;
    queue<TreeNode *> q;
    q.push(root);
    while (!q.empty()) {
        int size = q.size();
        if (size == 0) {
            return ans;
        }

        vector<int> data;
        while (size--) {
            TreeNode *temp = q.front();
            q.pop();
            data.push_back(temp->val);

            if (temp->left){
                q.push(temp->left);
            }

            if (temp->right){
                q.push(temp->right);
            }
        }

        ans.push_back(data.back());
    }

    return ans;
}
