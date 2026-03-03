/**
 * 1506. Find Root of N-Ary Tree
 * 
 * You are given all the nodes of an N-ary tree as an array of Node objects, where each node has a unique value.
 * Return the root of the N-ary tree.
 * Custom testing:
 * An N-ary tree can be serialized as represented in its level order traversal where each group of children is separated by the null value (see examples).
 * For example, the above tree is serialized as [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14].
 * The testing will be done in the following way:
 * The input data should be provided as a serialization of the tree.
 * The driver code will construct the tree from the serialized input data and put each Node object into an array in an arbitrary order.
 * The driver code will pass the array to findRoot, and your function should find and return the root Node object in the array.
 * 
 * Note:
 * 1 <= nodes.length <= 10^4
 * 1 <= Node.val <= nodes.length
 * Each value of nodes is unique.
 * 
 */
#include <vector>
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

class Solution {
public:
    Node* findRoot(vector<Node*> tree) {
        int rootVal = 0;
        
        // XOR all values in the tree
        for (Node* node : tree) {
            rootVal ^= node->val;
            for (Node* child : node->children) {
                rootVal ^= child->val;
            }
        }
        
        // Find the node with the rootVal
        for (Node* node : tree) {
            if (node->val == rootVal) {
                return node;
            }
        }
        
        return nullptr;
    }
};