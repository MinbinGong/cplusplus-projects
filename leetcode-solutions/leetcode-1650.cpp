/*
 * 1650. Lowest Common Ancestor of a Binary Tree III
 *
 * Given two nodes of a binary tree p and q, return their lowest common ancestor (LCA).
 * Each node will have a reference to its parent node. The definition for Node is below:
 * 
 * class Node {
 * public:
 *     int val;
 *     Node* left;
 *     Node* right;
 *     Node* parent;
 * }
 * 
 * According to the definition of LCA on Wikipedia: "The lowest common ancestor of two nodes p and q in a tree T is the lowest node that has both p and q as descendants (where we allow a node to be a descendant of itself)."
 * 
 * Example 1:
 * Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
 * Output: 3
 * Explanation: The LCA of nodes 5 and 1 is 3.
 * 
 * Example 2:
 * Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
 * Output: 5
 * Explanation: The LCA of nodes 5 and 4 is 5 since a node can be a descendant of itself according to the LCA definition.
 * 
 * Constraints:
 * The number of nodes in the tree is in the range [2, 10^5].
 * -10^9 <= Node.val <= 10^9
 * All Node.val are unique.
 * p != q
 * p and q exist in the tree.
 * 
 */
#include <unordered_set>
using namespace std;

// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* parent;
};

class Solution1 {
public:
    Node* lowestCommonAncestor(Node* p, Node * q) {
        unordered_set<Node*> visited; // 用于存储 p 的所有祖先
        // 1. 将从 p 到根节点的路径上的所有节点加入集合
        while (p != nullptr) {
            visited.insert(p);
            p = p->parent;
        }
        // 2. 从 q 开始向上遍历，第一个在集合中出现的节点就是 LCA
        while (q != nullptr) {
            if (visited.count(q)) {
                return q;
            }
            q = q->parent;
        }
        return nullptr; // 根据题目设定，p 和 q 都在树中，这行不会执行
    }
};

class Solution2 {
public:
    Node* lowestCommonAncestor(Node* p, Node * q) {
        Node* a = p;
        Node* b = q;
        // 两个指针分别从 p 和 q 出发，直到相遇
        while (a != b) {
            // 如果 a 走到空（根节点的 parent），则从 q 重新开始；否则继续向上
            a = (a == nullptr) ? q : a->parent;
            // 如果 b 走到空（根节点的 parent），则从 p 重新开始；否则继续向上
            b = (b == nullptr) ? p : b->parent;
        }
        return a; // 相遇点即为 LCA
    }
};

class Solution {
public:
    Node* lowestCommonAncestor(Node* p, Node * q) {
        Node* pp = p;
        Node* qq = q;
        int depthP = 0, depthQ = 0;

        // 1. 计算 p 和 q 的深度
        while (pp != nullptr) {
            depthP++;
            pp = pp->parent;
        }
        while (qq != nullptr) {
            depthQ++;
            qq = qq->parent;
        }

        // 2. 让较深的节点先向上走，使两者深度相等
        while (depthP > depthQ) {
            p = p->parent;
            depthP--;
        }
        while (depthQ > depthP) {
            q = q->parent;
            depthQ--;
        }

        // 3. 两个节点一起向上走，第一个相遇点即为 LCA
        while (p != q) {
            p = p->parent;
            q = q->parent;
        }
        return p;
    }
};
