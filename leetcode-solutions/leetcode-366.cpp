/*
 * leetcode-366: Find Leaves of Binary Tree
 *
 * Given the root of a binary tree, collect a tree's nodes as if you were doing this:
 * 
 * Collect all the leaf nodes.
 * Remove all the leaf nodes.
 * Repeat until the tree is empty.
 * 
 * Example 1:
 * Input: root = [1,2,3,4,5]
 * Output: [[4,5,3],[2],[1]]
 * Explanation:
 * [[3,5,4],[2],[1]] and [[3,4,5],[2],[1]] are also considered correct answers since per each level it does not matter the order on which elements are returned.
 * 
 * Example 2:
 * Input: root = [1]
 * Output: [[1]]
 * 
 * Constraints:
 * The number of nodes in the tree is in the range [1, 100].
 * -100 <= Node.val <= 100
 * 
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> findLeaves(TreeNode* root) {
        vector<vector<int>> result;
        dfs(root, result);
        return result;
    }

private:
    int dfs(TreeNode* node, vector<vector<int>>& result) {
        if (!node) return -1;  // 空节点高度为-1，使叶子节点高度为0
        int leftHeight = dfs(node->left, result);
        int rightHeight = dfs(node->right, result);
        int height = max(leftHeight, rightHeight) + 1;
        
        // 确保结果列表有足够空间
        if (result.size() == height) {
            result.push_back({});
        }
        result[height].push_back(node->val);
        
        return height;
    }
};