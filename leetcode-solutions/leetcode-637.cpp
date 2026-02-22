/*
 * Average of Levels in Binary Tree
 *
 * Given a non-empty binary tree, return the average value of the nodes on each level in the form of an array.
 * 
 * Note:
 * The range of node's value is in the range of 32-bit signed integer.
 * 
 */
#include <vector>
#include <queue>

using namespace std;
struct TreeNode {
    int val;
    TreeNode *left, *right;
    explicit TreeNode(int x = 0, TreeNode *l = nullptr, TreeNode *r = nullptr) : val(x), left(l), right(r) {}
};
vector<double> averageOfLevels(TreeNode *root) {
    vector<double> ans;
    if (root == nullptr) return ans;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        int size = q.size();
        double sum = 0;
        for (int i = 0; i < size; ++i) {
            TreeNode *node = q.front();
            q.pop();
            sum += node->val;
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        ans.push_back(sum / size);
    }
    return ans;
}