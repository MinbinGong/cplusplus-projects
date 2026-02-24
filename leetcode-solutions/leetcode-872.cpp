/**
 * 872. Leaf-Similar Trees
 * 
 * Example 1:
 * Input: root1 = [3,5,1,6,2,9,8,null,null,7,4], root2 = [3,5,1,6,7,4,2,null,null,null,null,null,null,9,8]
 * Output: true
 * 
 * Example 2:
 * Input: root1 = [1], root2 = [1]
 * Output: true
 * 
 * Example 3:
 * Input: root1 = [1], root2 = [2]
 * Output: false
 * 
 * Example 4:
 * Input: root1 = [1,2], root2 = [2,2]
 * Output: true
 * 
 * Example 5:
 * Input: root1 = [1,2,3], root2 = [1,3,2]
 * Output: false
 * 
 * Note:
 * Both trees will have between 1 and 100 nodes.
 * 
 */
#include <vector>
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
    bool leafSimilar(TreeNode* root1, TreeNode* root2) {
        vector<int> leaves1, leaves2;
        dfs(root1, leaves1);
        dfs(root2, leaves2);
        return leaves1 == leaves2;
    }

    void dfs(TreeNode* node, vector<int>& leaves) {
        if (!node) return;
        if (!node->left && !node->right) {
            leaves.push_back(node->val);
            return;
        }
        dfs(node->left, leaves);
        dfs(node->right, leaves);
    }
};