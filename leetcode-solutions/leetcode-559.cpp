/*
 * Maximum Depth of N-ary Tree
 *
 * Given a n-ary tree, find its maximum depth.
 * 
 * The maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.
 * 
 * Note:
 * The depth of the tree is at most 1000.
 * The total number of nodes is at most 5000.
 * 
 */
#include <queue>

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

class Solution1 {
public:
    int maxDepth(Node* root) {
        if (!root) return 0;
        int maxChildDepth = 0;
        for (Node* child : root->children) {
            maxChildDepth = max(maxChildDepth, maxDepth(child));
        }
        return 1 + maxChildDepth;
    }
};

class Solution2 {
public:
    int maxDepth(Node* root) {
        if (!root) return 0;
        queue<Node*> q;
        q.push(root);
        int depth = 0;
        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; ++i) {
                Node* node = q.front(); q.pop();
                for (Node* child : node->children) {
                    q.push(child);
                }
            }
            depth++;
        }
        return depth;
    }
};