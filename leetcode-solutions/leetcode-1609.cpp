/**
 * 1609. Even Odd Tree
 * 
 * Given the root of a binary tree, check whether it is a mirror of itself (i.e., symmetric around its center).
 * 
 * Example 1:
 * Input: root = [1,2,2,3,4,4,3]
 * Output: true
 * 
 * Example 2:
 * Input: root = [1,2,2,null,3,null,3]
 * Output: false
 * 
 * Constraints:
 * The number of nodes in the tree is in the range [1, 1000].
 * -100 <= Node.val <= 100
 * 
 * Follow up: Could you solve it both recursively and iteratively?
 */
#include <queue>
using namespace std;

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
    bool isEvenOddTree(TreeNode* root) {
        if (!root) return true; // not needed per constraints, but safe
        
        std::queue<TreeNode*> q;
        q.push(root);
        int level = 0;
        
        while (!q.empty()) {
            int levelSize = q.size();
            int prev;
            
            // Set initial comparison value based on level parity
            if (level % 2 == 0) { // even level: strictly increasing odd numbers
                prev = INT_MIN;
            } else { // odd level: strictly decreasing even numbers
                prev = INT_MAX;
            }
            
            for (int i = 0; i < levelSize; ++i) {
                TreeNode* node = q.front();
                q.pop();
                int val = node->val;
                
                // Check parity and order conditions
                if (level % 2 == 0) {
                    if (val % 2 == 0 || val <= prev) return false;
                } else {
                    if (val % 2 != 0 || val >= prev) return false;
                }
                prev = val;
                
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            ++level;
        }
        return true;
    }
};