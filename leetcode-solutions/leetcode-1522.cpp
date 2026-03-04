/*
 * 1522. Diameter of N-Ary Tree
 *
 * Given a root of an N-ary tree, you need to compute the length of the diameter of the tree.
 *
 * The diameter of an N-ary tree is the length of the longest path between any two nodes in the tree. This path may or may not pass through the root.
 *
 * (Nary-Tree input serialization is represented in their level order traversal, each group of children is separated by the null value.)
 *
 * Example 1:
 * Input: root = [1,null,3,2,4,null,5,6]
 * Output: 3
 * Explanation: The diameter of the tree is the length of the longest path [4,2,3,1,5] or [5,2,3,1,4].
 * 
 * Example 2:
 * Input: root = [1,null,2,null,3,4,null,5,null,6]
 * Output: 4
 * Explanation: The diameter of the tree is the length of the longest path [4,2,3,1,2,5,6].
 * 
 * Constraints:
 * The depth of the n-ary tree is less than or equal to 1000.
 * The total number of nodes is between [1, 10^4].
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};

class Solution {
public:
    int diameter(Node* root) {
        int ans = 0;
        dfs(root, ans);
        return ans;
    }

private:
    // returns the maximum depth (in edges) from the given node to a leaf
    int dfs(Node* node, int& ans) {
        int max1 = 0, max2 = 0; // two largest depths among children

        for (Node* child : node->children) {
            int depth = dfs(child, ans) + 1; // child depth + edge to child
            if (depth > max1) {
                max2 = max1;
                max1 = depth;
            } else if (depth > max2) {
                max2 = depth;
            }
        }

        ans = max(ans, max1 + max2); // path through current node
        return max1;
    }
};