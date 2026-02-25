/*
 * 1022. Sum of Root To Leaf Binary Numbers
 *
 * Given a binary tree, each node has value 0 or 1.  Each root-to-leaf path represents a binary number starting with the most significant bit.  For example, if the path is 0 -> 1 -> 1 -> 0 -> 1, then this could represent 01101 in binary, which is 13.
 *
 * For all leaves in the tree, consider the numbers represented by the path from the root to that leaf.
 *
 * Return the sum of these numbers.
 *
 * Example 1:
 *
 * Input: [1,0,1,0,1,0,1]
 * Output: 22
 * Explanation: (100) + (101) + (110) + (111) = 4 + 5 + 6 + 7 = 22
 * 
 * Example 2:
 *
 * Input: [0,1,0,1,1,0,1]
 * Output: 26
 * Explanation: (010) + (011) + (100) + (101) + (110) + (111) = 2 + 3 + 4 + 5 + 6 + 7 = 26
 * 
 * Example 3:
 *
 * Input: [0]
 * Output: 0
 * Explanation: (0) = 0
 * 
 * Example 4:
 *
 * Input: [1,1,0,1,1,0,1,0,0,0,0,1,0,0,1,1,0,1,0,0,0,1,0,0,0,0,0,1,1,0,0,1,0,1,1,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,1,0,0,1,0,0,1,1,0,1,0,0,0,1,0,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
 * Output: 1073741824
 * Explanation: The binary number represented by this path is 11011100101100100110100000000000.
 * 
 * Note:
 * 
 * The number of nodes in the tree is between 1 and 1000.
 * node.val is 0 or 1.
 * The answer will not exceed 2^31 - 1.
 * 
 */
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

class Solution {
public:
    int sumRootToLeaf(TreeNode* root) {
        long long total = 0;
        dfs(root, 0, total);
        return static_cast<int>(total);
    }

private:
    void dfs(TreeNode* node, int curr, long long& total) {
        if (!node) return;
        curr = (curr << 1) | node->val;          // append current node's bit
        if (!node->left && !node->right) {
            total += curr;                        // leaf: add the binary number
            return;
        }
        dfs(node->left, curr, total);
        dfs(node->right, curr, total);
    }
};