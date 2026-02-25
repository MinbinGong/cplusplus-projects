/**
 * 979. Distribute Coins in Binary Tree
 *
 * You are given the root of a binary tree with n nodes where each node in the tree has node.val coins. There are n coins in total throughout the whole tree.
 *
 * In one move, we may choose two adjacent nodes and move one coin from one node to another. A move may be from parent to child, or from child to parent.
 *
 * Return the minimum number of moves required to make every node have exactly one coin.
 *
 * Example 1:
 *
 * Input: root = [3,0,0]
 * Output: 2
 * Explanation: From the root of the tree, we move one coin to its left child, and one coin to its right child.
 * 
 * Example 2:
 *
 * Input: root = [0,3,0]
 * Output: 3
 * Explanation: From the left child of the root, we move two coins to the root [taking two moves]. Then, we move one coin from the root of the tree to the right child.
 * 
 * Example 3:
 *
 * Input: root = [1,0,2]
 * Output: 2
 * 
 * Example 4:
 *
 * Input: root = [1,0,0,null,3]
 * Output: 4
 * 
 * Note:
 *
 * The number of nodes in the tree is n.
 * 1 <= n <= 100
 * 0 <= node.val <= n
 * The sum of all node.val is n.
 */
#include <algorithm>
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

class Solution {
public:
    int distributeCoins(TreeNode* root) {
        ans = 0;
        dfs(root);
        return ans;
    }
    
private:
    int ans;
    
    // 返回：当前节点需要从父节点接收（正数）或向父节点送出（负数）的硬币数量
    int dfs(TreeNode* node) {
        if (!node) return 0;
        
        int left = dfs(node->left);   // 左子树的硬币盈亏
        int right = dfs(node->right); // 右子树的硬币盈亏
        
        // 移动次数累加：左右子树的硬币都需要经过当前节点移动
        ans += abs(left) + abs(right);
        
        // 当前节点及其子树的硬币盈亏 = 当前节点硬币数 + 左子树盈亏 + 右子树盈亏 - 1（目标值）
        return node->val + left + right - 1;
    }
};