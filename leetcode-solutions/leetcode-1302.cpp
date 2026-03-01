/*
 * 1302. Deepest Leaves Sum
 * 
 * Given a binary tree, return the sum of values of its deepest leaves.
 * 
 * Example 1:
 * Input: root = [1,2,3,4,5,null,6,7,null,null,null,null,8]
 * Output: 15
 * 
 * Note:
 * The number of nodes in the tree is between 1 and 10^4.
 * The value of nodes is between 1 and 100.
 * 
 */
#include <queue>
using namespace std;

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution1 {
public:
    int deepestLeavesSum(TreeNode* root) {
        if (!root) return 0;
        queue<TreeNode*> q;
        q.push(root);
        int sum;
        while (!q.empty()) {
            int size = q.size();
            sum = 0;  // 每层开始时重置，最后保留最后一层的和
            for (int i = 0; i < size; ++i) {
                TreeNode* node = q.front();
                q.pop();
                sum += node->val;
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
        }
        return sum;
    }
};

class Solution2 {
public:
    int deepestLeavesSum(TreeNode* root) {
        int maxDepth = 0;
        int sum = 0;
        dfs(root, 0, maxDepth, sum);
        return sum;
    }
    
    void dfs(TreeNode* node, int depth, int& maxDepth, int& sum) {
        if (!node) return;
        if (depth > maxDepth) {
            maxDepth = depth;
            sum = node->val;
        } else if (depth == maxDepth) {
            sum += node->val;
        }
        dfs(node->left, depth + 1, maxDepth, sum);
        dfs(node->right, depth + 1, maxDepth, sum);
    }
};