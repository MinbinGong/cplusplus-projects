/**
 * 1145. Binary Tree Coloring Game
 * Medium
 * 
 * (This problem is an interactive problem.)
 * 
 * Two players play a turn based game on a binary tree. We are given the root of this binary tree, and the number of nodes n in the tree. n is odd, and each node has a distinct value from 1 to n.
 * 
 * Initially, the first player names a value x with 1 <= x <= n, and the second player names a value y with 1 <= y <= n and y != x. The first player colors the node with value x red, and the second player colors the node with value y blue.
 * 
 * Then, the players take turns starting with the first player. In each turn, that player chooses a node of their color (red if player 1, blue if player 2) and colors an uncolored neighbor of the chosen node (either the left child, right child, or parent of the chosen node.)
 * 
 * Example 1:
 * Input: root = [1,2,3,4,5,6,7,8,9,10,11], n = 11, x = 3
 * Output: 2
 * Explanation: The second player can choose the node with value 2.
 * 
 * Example 2:
 * Input: root = [1,2,3], n = 3, x = 1
 * Output: 0
 * 
 * Note:
 * 1 <= n <= 1000
 * n is odd.
 * 1 <= x <= n
 * 1 <= y <= n
 * y != x
 * All the values of the binary tree are unique.
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
#include <vector>
using namespace std;

class Solution {
public:
    bool btreeGameWinningMove(TreeNode* root, int n, int x) {
        // 先找到节点x
        TreeNode* target = findNode(root, x);
        // 计算左子树大小
        int leftSize = countNodes(target->left);
        int rightSize = countNodes(target->right);
        // 父节点方向的大小 = 总节点数 - (左+右+1)
        int parentSize = n - (leftSize + rightSize + 1);
        
        // 玩家2可以选这三个部分中最大的一个
        int maxPart = max({leftSize, rightSize, parentSize});
        // 如果最大部分超过一半，则玩家2必胜
        return maxPart > n / 2;
    }
    
private:
    TreeNode* findNode(TreeNode* root, int x) {
        if (!root) return nullptr;
        if (root->val == x) return root;
        TreeNode* left = findNode(root->left, x);
        if (left) return left;
        return findNode(root->right, x);
    }
    
    int countNodes(TreeNode* node) {
        if (!node) return 0;
        return 1 + countNodes(node->left) + countNodes(node->right);
    }
};