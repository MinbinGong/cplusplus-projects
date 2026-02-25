/*
 * 988. Smallest String Starting From Leaf
 *
 * Given the root of a binary tree, each node has a value from 0 to 25 representing the letters 'a' to 'z': a value of 0 represents 'a', a value of 1 represents 'b', and so on.
 *
 * Find the lexicographically smallest string that starts at a leaf of this tree and ends at the root.
 *
 * (As a reminder, any shorter prefix of a string is lexicographically smaller: for example, "ab" is lexicographically smaller than "aba".  A leaf of a node is a node that has no children.)
 *
 * Example 1:
 *
 * Input: [0,1,2,3,4,3,4]
 * Output: "dba"
 *
 * Example 2:
 *
 * Input: [25,1,3,1,3,0,2]
 * Output: "adz"
 *
 * Example 3:
 *
 * Input: [2,2,1,null,1,0,null,0]
 * Output: "abc"
 *
 * Note:
 * 1 <= A.length <= 8500
 * 0 <= A[i] <= 25
 * 1 <= queries.length <= 3 * 10^4
 * 0 <= queries[i][0] <= 25
 * 0 <= queries[i][1] < A.length
 * 
 */
#include <string>
#include <algorithm>

using namespace std;

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
    string smallestFromLeaf(TreeNode* root) {
        string best;
        string path;
        dfs(root, path, best);
        return best;
    }

private:
    void dfs(TreeNode* node, string& path, string& best) {
        if (!node) return;

        // Append current node's character to path (root -> current)
        path.push_back('a' + node->val);

        // If it's a leaf, construct leaf->root string and compare
        if (!node->left && !node->right) {
            string leafToRoot(path.rbegin(), path.rend()); // reverse path
            if (best.empty() || leafToRoot < best) {
                best = leafToRoot;
            }
        } else {
            // Recurse to children
            dfs(node->left, path, best);
            dfs(node->right, path, best);
        }

        // Backtrack
        path.pop_back();
    }
};