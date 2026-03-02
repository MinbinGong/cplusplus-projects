/*
 * 1339. Maximum Product of Splitted Binary Tree
 *
 * Given a binary tree root. Split the binary tree into two subtrees by removing 1 edge such that the product of the sums of the subtrees are maximized.
 * 
 * Since the answer may be too large, return it modulo 10^9 + 7.
 * 
 * Example 1:
 * Input: root = [1,2,3,4,5,6]
 * Output: 110
 * Explanation: Remove the red edge and get 2 binary trees with sum 11 and 10. Their product is 110 (11*10)
 * 
 * Example 2:
 * Input: root = [1,null,2,3,4,null,null,5,6]
 * Output: 90
 * Explanation:  Remove the red edge and get 2 binary trees with sum 15 and 6.Their product is 90 (15*6)
 * 
 * Example 3:
 * Input: root = [2,3,9,10,7,8,6,5,4,11,1]
 * Output: 1025
 * 
 * Example 4:
 * Input: root = [1,1]
 * Output: 1
 * 
 * Note:
 * The number of nodes in the tree is between 2 and 5 * 10^4.
 * Each node's value is between [1, 10000].
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
    int maxProduct(TreeNode* root) {
        const int MOD = 1e9 + 7;
        // First pass: compute total sum of the tree
        long long total = sumTree(root);
        
        long long best = 0;
        // Second pass: compute subtree sums and update best product
        dfs(root, total, best);
        
        return best % MOD;
    }
    
private:
    long long sumTree(TreeNode* node) {
        if (!node) return 0;
        return node->val + sumTree(node->left) + sumTree(node->right);
    }
    
    long long dfs(TreeNode* node, long long total, long long& best) {
        if (!node) return 0;
        
        long long leftSum = dfs(node->left, total, best);
        long long rightSum = dfs(node->right, total, best);
        long long subSum = node->val + leftSum + rightSum;
        
        // Product of the two parts after cutting the edge above this node
        // (except for the root, where product is 0 – it's harmless)
        long long prod = subSum * (total - subSum);
        if (prod > best) best = prod;
        
        return subSum;
    }
};