/*
 * 968. Binary Tree Cameras
 *
 * Given a binary tree, we install cameras on the nodes of the tree.
 *
 * Each camera at a node can monitor its parent, itself, and its immediate children.
 *
 * Calculate the minimum number of cameras needed to monitor all nodes of the tree.
 *
 * Example 1:
 *
 * Input: [0,0,null,0,0]
 * Output: 1
 * Explanation: One camera is enough to monitor all nodes if placed as shown.
 * 
 * Example 2:
 *
 * Input: [0,0,null,0,null,0,null,null,0]
 * Output: 2
 * Explanation: At least two cameras are needed to monitor all nodes of the tree. The above image shows one of the valid configurations of camera placement.
 * 
 * Note:
 *
 * The number of nodes in the given tree will be in the range [1, 1000].
 * Every node has value 0.
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
    int minCameraCover(TreeNode* root) {
        int cameras = 0;
        int state = dfs(root, cameras);
        // 如果根节点未被覆盖，需要额外安装一个摄像头
        if (state == 0) cameras++;
        return cameras;
    }

private:
    // 返回值定义：
    // 0 - 当前节点未被覆盖（需要父节点帮忙）
    // 1 - 当前节点已被覆盖，但本身没有摄像头
    // 2 - 当前节点安装了摄像头
    int dfs(TreeNode* node, int& cameras) {
        if (!node) return 1; // 空节点视为已覆盖（不需要摄像头）

        int left = dfs(node->left, cameras);
        int right = dfs(node->right, cameras);

        // 情况1：左右孩子中有一个未被覆盖，则当前节点必须安装摄像头
        if (left == 0 || right == 0) {
            cameras++;
            return 2;
        }

        // 情况2：左右孩子中有一个有摄像头，则当前节点可以被覆盖
        if (left == 2 || right == 2) {
            return 1;
        }

        // 情况3：左右孩子都被覆盖（且无摄像头），则当前节点未被覆盖
        return 0;
    }
};