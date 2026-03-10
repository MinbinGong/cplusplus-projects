/**
 * 1740. Find Distance in a Binary Tree
 * 
 * Given the root of a binary tree and two integers p and q, return the distance between the nodes of value p and value q in the tree.
 * The distance between two nodes is the number of edges on the path from one to the other.
 * 
 * Example 1:
 * Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 0
 * Output: 3
 * Explanation: There are 3 edges between 5 and 0: 5-3-1-0.
 * 
 * Example 2:
 * Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 7
 * Output: 2
 * Explanation: There are 2 edges between 5 and 7: 5-2-7.
 * 
 * Example 3:
 * Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
 * Output: 2
 * Explanation: There are 2 edges between 5 and 4: 5-2-4.
 * 
 * Constraints:
 * The number of nodes in the tree is in the range [1, 104].
 * 0 <= Node.val <= 109
 * All Node.val are unique.
 * p and q are values in the tree.
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
private:
    int ans;         // 最终结果：p 和 q 的距离
    int pDepth;      // 节点 p 的深度
    int qDepth;      // 节点 q 的深度

    // DFS 函数，返回值表示当前子树中是否包含 p 或 q 其中之一
    bool dfs(TreeNode* root, int depth, int p, int q) {
        if (root == nullptr) return false;

        // 记录 p 和 q 的深度
        if (root->val == p) pDepth = depth;
        if (root->val == q) qDepth = depth;

        // 递归搜索左右子树
        bool left = dfs(root->left, depth + 1, p, q);
        bool right = dfs(root->right, depth + 1, p, q);

        // 情况1：p 和 q 分别位于当前节点的左右子树中，则当前节点是最近公共祖先
        if (left && right) {
            ans = pDepth + qDepth - 2 * depth;
            return true;
        }

        // 情况2：当前节点本身就是 p 或 q，并且另一个节点在其子树中
        if ((root->val == p || root->val == q) && (left || right)) {
            ans = abs(pDepth - qDepth);
            return true;
        }

        // 返回当前子树中是否找到了 p 或 q 中的至少一个
        return root->val == p || root->val == q || left || right;
    }

public:
    int findDistance(TreeNode* root, int p, int q) {
        // 如果是同一个节点，距离为 0
        if (p == q) return 0;
        ans = 0;
        pDepth = 0;
        qDepth = 0;
        dfs(root, 0, p, q);
        return ans;
    }
};