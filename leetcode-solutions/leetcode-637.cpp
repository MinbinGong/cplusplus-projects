/*
 * Average of Levels in Binary Tree
 * 题目描述
 *     给定一个二叉树，求每一层的节点值的平均数。
 * 
 * 题解：
 *     利用广度优先搜索，对每一层的节点进行遍历，然后求和，最后求平均数。
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