/*
 * 1530. Number of Good Leaf Nodes Pairs
 *
 * You are given the root of a binary tree and an integer distance. A pair of two different leaf nodes of a binary tree is said to be good if the length of the shortest path between them is less than or equal to distance.
 *
 * Return the number of good leaf node pairs in the tree.
 *
 * Example 1:
 * Input: root = [1,2,3,null,4], distance = 3
 * Output: 1
 * Explanation: The only good pair is [4,5] with shortest path = 2.
 * 
 * Example 2:
 * Input: root = [1,2,3,4,5,6,7], distance = 3
 * Output: 2
 * Explanation: The good pairs are [4,5] and [6,7] with shortest path = 2. The pair [4,6] is not good because the length of ther shortest path between them is 4.
 * 
 * Constraints:
 * The number of nodes in the tree is in the range [1, 2^10].
 * 1 <= Node.val <= 100
 * 1 <= distance <= 10
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
    int countPairs(TreeNode* root, int distance) {
        int ans = 0;
        dfs(root, distance, ans);
        return ans;
    }

private:
    vector<int> dfs(TreeNode* node, int distance, int& ans) {
        if (!node) return {};
        // leaf node
        if (!node->left && !node->right) {
            return {0};                     // distance from leaf to itself = 0
        }

        vector<int> left = dfs(node->left, distance, ans);
        vector<int> right = dfs(node->right, distance, ans);

        // increase distances by 1 to account for edge to parent
        for (int& d : left) d++;
        for (int& d : right) d++;

        // count good pairs through current node
        for (int l : left) {
            for (int r : right) {
                if (l + r <= distance) {
                    ans++;
                }
            }
        }

        // merge all distances from children and return
        left.insert(left.end(), right.begin(), right.end());
        return left;
    }
};