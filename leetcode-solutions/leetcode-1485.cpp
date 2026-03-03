/*
 * 1485. Clone Binary Tree With Random Pointer
 *
 * A binary tree node is defined as follows:
 *
 * struct Node {
 int val;
 Node *left;
 Node *right;
 Node *random;
 Node(int x) : val(x), left(NULL), right(NULL), random(NULL) {}
 * };
 *
 *
 * You are given the root of a binary tree that has n nodes, each node has a unique value from 1 to n.
 *
 * You are also given the array queries of size m, where queries[i] = x_i.
 *
 * For each query x_i, you need to find the node with value x_i in the original tree and create a copy of it.
 *
 * Return an array of size m where ans[i] is the value of the root of the copied tree for the query x_i.
 *
 * Example 1:
 * Input: root = [1,2,3,4,5,6,7], queries = [3,1,5,6]
 * Output: [4,2,6,7]
 * Explanation: The tree is shown in the figure above. The nodes with values of 3, 1, 5, and 6 are the nodes that are
 copied.
 *
 * Example 2:
 * Input: root = [1,2,3,null,null,4,5], queries = [3,4,5,1]
 * Output: [4,5,6,2]
 * Explanation: The tree is shown in the figure above. The nodes with values of 3, 4, 5, and 1 are the nodes that are
 copied.
 *
 * Example 3:
 * Input: root = [1,null,2,null,3,null,4,null,5], queries = [4,5,6,7]
 * Output: [3,4,5,6]
 *
 * Constraints:
 * The number of nodes in the tree is in the range [1, 10^4].
 * Each node has a unique value from 1 to n.
 * m == queries.length
 * 1 <= m <= 10^4
 * 1 <= queries[i] <= n
 *
 */
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

/**
 * Definition for a Node.
 */
struct Node {
    int val;
    Node* left;
    Node* right;
    Node* random;
    Node(int x) : val(x), left(NULL), right(NULL), random(NULL) {}
};
struct NodeCopy {
    int val;
    NodeCopy* left;
    NodeCopy* right;
    NodeCopy* random;
    NodeCopy(int x) : val(x), left(NULL), right(NULL), random(NULL) {}
};

class Solution1 {
    unordered_map<Node*, NodeCopy*> mp;  // 原节点 -> 拷贝节点
public:
    NodeCopy* copyRandomBinaryTree(Node* root) {
        if (!root) return nullptr;
        
        // 如果当前节点已经拷贝过，直接返回
        if (mp.count(root)) return mp[root];
        
        // 创建新节点
        NodeCopy* newNode = new NodeCopy(root->val);
        mp[root] = newNode;  // 先存入哈希表，防止循环引用
        
        // 递归拷贝三个指针
        newNode->left = copyRandomBinaryTree(root->left);
        newNode->right = copyRandomBinaryTree(root->right);
        newNode->random = copyRandomBinaryTree(root->random);
        
        return newNode;
    }
};

class Solution2 {
public:
    NodeCopy* copyRandomBinaryTree(Node* root) {
        if (!root) return nullptr;
        
        unordered_map<Node*, NodeCopy*> mp;
        queue<Node*> q;
        q.push(root);
        mp[root] = new NodeCopy(root->val);  // 拷贝根节点
        
        while (!q.empty()) {
            Node* cur = q.front(); q.pop();
            NodeCopy* curCopy = mp[cur];
            
            // 处理左孩子
            if (cur->left) {
                if (!mp.count(cur->left)) {
                    mp[cur->left] = new NodeCopy(cur->left->val);
                    q.push(cur->left);
                }
                curCopy->left = mp[cur->left];
            }
            
            // 处理右孩子
            if (cur->right) {
                if (!mp.count(cur->right)) {
                    mp[cur->right] = new NodeCopy(cur->right->val);
                    q.push(cur->right);
                }
                curCopy->right = mp[cur->right];
            }
            
            // 处理随机指针
            if (cur->random) {
                if (!mp.count(cur->random)) {
                    mp[cur->random] = new NodeCopy(cur->random->val);
                    q.push(cur->random);
                }
                curCopy->random = mp[cur->random];
            }
        }
        
        return mp[root];
    }
};
