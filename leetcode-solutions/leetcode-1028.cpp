/*
 * 1028. Recover a Tree From Preorder Traversal
 *
 * We run a preorder depth first search on the root of a binary tree.
 *
 * At each node in this traversal, we output D dashes (where D is the depth of this node), then we output the value of this node.  (If the depth of a node is D, the depth of its immediate child is D+1.  The depth of the root node is 0.)
 *
 * If a node has only one child, that child is guaranteed to be the left child.
 *
 * Given the output S of this traversal, recover the tree and return its root.
 *
 * Example 1:
 *
 * Input: "1-2--3--4-5--6--7"
 * Output: [1,2,5,3,4,6,7]
 * 
 * Example 2:
 *
 * Input: "1-2--3---4-5--6---7"
 * Output: [1,2,5,3,null,6,null,4,null,7]
 * 
 * Note:
 *
 * 1 <= S.length <= 1000
 * S[0] = '1'
 * S consists of nodes with values between 1 and 10^9.
 * 
 */
#include <string>
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
    TreeNode* recoverFromPreorder(string traversal) {
        vector<TreeNode*> stack;  // stack of nodes at different depths
        int i = 0;
        int n = traversal.size();

        while (i < n) {
            // Count depth (number of dashes)
            int depth = 0;
            while (i < n && traversal[i] == '-') {
                depth++;
                i++;
            }

            // Parse the value
            int val = 0;
            while (i < n && isdigit(traversal[i])) {
                val = val * 10 + (traversal[i] - '0');
                i++;
            }

            TreeNode* node = new TreeNode(val);

            // Adjust stack to the correct depth
            // Stack size should be exactly the depth of the new node (0-based depth)
            // If depth < stack size, pop until stack size == depth
            while (stack.size() > depth) {
                stack.pop_back();
            }

            // Attach node to its parent (top of stack)
            if (!stack.empty()) {
                TreeNode* parent = stack.back();
                if (parent->left == nullptr) {
                    parent->left = node;
                } else {
                    parent->right = node;
                }
            }

            // Push current node onto stack
            stack.push_back(node);
        }

        // Root is the first node pushed
        return stack[0];
    }
};