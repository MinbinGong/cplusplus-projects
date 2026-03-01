/**
 * 1315. Sum of Nodes with Even-Valued Grandparent
 * 
 * Given a binary tree, return the sum of values of nodes with even-valued grandparent.  (A grandparent of a node is the parent of its parent, if it exists.)
 * 
 * If there are no nodes with an even-valued grandparent, return 0.
 * 
 * Example 1:
 * Input: root = [6,7,8,2,7,1,3,9,null,1,4,null,null,null,5]
 * Output: 18
 * Explanation: The red nodes are the nodes with even-value grandparent while the blue nodes are the even-value grandparents.
 * 
 * Note:
 * The number of nodes in the tree is between 1 and 10^4.
 * Each node's value is between 1 and 100.
 * 
 */
/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    int sumEvenGrandparent(TreeNode* root) {
        // 从根节点开始，父节点和祖父节点初始值设为 1（奇数），因为 1 不是偶数
        return dfs(root, 1, 1);
    }

private:
    int dfs(TreeNode* node, int parent, int grandparent) {
        if (!node) return 0;
        int sum = 0;
        // 如果祖父节点是偶数，累加当前节点值
        if (grandparent % 2 == 0) {
            sum += node->val;
        }
        // 递归左右子树，更新父节点和祖父节点
        sum += dfs(node->left, node->val, parent);
        sum += dfs(node->right, node->val, parent);
        return sum;
    }
};