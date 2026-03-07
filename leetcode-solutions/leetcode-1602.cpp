/*
 * 1602. Find Nearest Right Node in Binary Tree
 *
 * Given the root of a binary tree and a node u in the tree, return the nearest node on the same level that is to the right of u, or return null if u is the rightmost node in its level.
 * 
 * Example 1:
 * Input: root = [1,2,3,null,4,5,6], u = 4
 * Output: 5
 * Explanation: The nearest node on the same level to the right of node 4 is node 5.
 * 
 * Example 2:
 * Input: root = [3,null,4,2], u = 2
 * Output: null
 * Explanation: There are no nodes to the right of 2.
 * 
 * Example 3:
 * Input: root = [1], u = 1
 * Output: null
 * 
 * Example 4:
 * Input: root = [3,4,2,null,null,null,1], u = 4
 * Output: 2
 * 
 * Constraints:
 * The number of nodes in the tree is in the range [1, 105].
 * 1 <= Node.val <= 105
 * All values in the tree are distinct.
 * u is a node in the binary tree rooted at root.
 * 
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
    TreeNode* findNearestRightNode(TreeNode* root, TreeNode* u) {
        if (!root) return nullptr;
        queue<TreeNode*> q;
        q.push(root);
        
        while (!q.empty()) {
            int levelSize = q.size();
            for (int i = 0; i < levelSize; ++i) {
                TreeNode* cur = q.front(); q.pop();
                if (cur == u) {
                    // If u is not the last node in this level, return the next node in the queue
                    return (i < levelSize - 1) ? q.front() : nullptr;
                }
                if (cur->left) q.push(cur->left);
                if (cur->right) q.push(cur->right);
            }
        }
        return nullptr;
    }
};