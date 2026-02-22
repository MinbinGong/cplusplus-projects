/*
 * Logical OR of Two Binary Grids Represented as Quad-Trees
 *
 * A binary matrix means that all elements are 0 or 1. For each individual binary matrix, we can choose any size of a sub-matrix, and count how many 1s are there in the sub-matrix.
 * 
 * Given two binary matrices A and B, return the result of ORing them.
 * 
 * Example:
 * Input: A = [[0,1],[1,1]], B = [[1,1],[1,0]]
 * Output: [[1,1],[1,1]]
 * 
 * Note:
 * The number of rows and columns of A is in the range [1, 32].
 * 0 <= A[i][j], B[i][j] <= 1
 * 
 */
// Definition for a QuadTree node.
class Node {
public:
    bool val;
    bool isLeaf;
    Node* topLeft;
    Node* topRight;
    Node* bottomLeft;
    Node* bottomRight;
    
    Node() {
        val = false;
        isLeaf = false;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }
    
    Node(bool _val, bool _isLeaf) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }
    
    Node(bool _val, bool _isLeaf, Node* _topLeft, Node* _topRight, Node* _bottomLeft, Node* _bottomRight) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = _topLeft;
        topRight = _topRight;
        bottomLeft = _bottomLeft;
        bottomRight = _bottomRight;
    }
};

class Solution {
public:
    Node* intersect(Node* quadTree1, Node* quadTree2) {
        // If either node is a leaf, handle directly
        if (quadTree1->isLeaf) {
            if (quadTree1->val) return quadTree1;   // 1 OR anything = 1
            else return quadTree2;                   // 0 OR x = x
        }
        if (quadTree2->isLeaf) {
            if (quadTree2->val) return quadTree2;
            else return quadTree1;
        }
        
        // Recursively combine children
        Node* tl = intersect(quadTree1->topLeft, quadTree2->topLeft);
        Node* tr = intersect(quadTree1->topRight, quadTree2->topRight);
        Node* bl = intersect(quadTree1->bottomLeft, quadTree2->bottomLeft);
        Node* br = intersect(quadTree1->bottomRight, quadTree2->bottomRight);
        
        // If all four children are leaves with the same value, merge them
        if (tl->isLeaf && tr->isLeaf && bl->isLeaf && br->isLeaf &&
            tl->val == tr->val && tr->val == bl->val && bl->val == br->val) {
            return new Node(tl->val, true);
        } else {
            return new Node(false, false, tl, tr, bl, br);
        }
    }
};