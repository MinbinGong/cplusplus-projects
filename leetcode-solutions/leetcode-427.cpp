/*
 * Construct Quad Tree
 *
 * Given a n * n matrix grid of 0's and 1's only. We want to represent the grid with a Quad-Tree.
 * Return the root of the Quad-Tree representing the grid.
 * Notice that you can assign the value of a node to True or False when isLeaf is False, and both are accepted in the answer.
 * 
 * Example 1:
 * Input: grid = [[0,1],[1,0]]
 * Output: [[0,1],[1,0],[1,1],[1,1],[1,0]]
 * Explanation: The explanation of this example is shown below:
 * Notice that 0 represnts False and 1 represents True in the photo representing the Quad-Tree.
 * 
 * Example 2:
 * Input: grid = [[1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0],[1,1,1,1,1,1,1,1],[1,1,1,1,1,1,1,1],[1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0]]
 * Output: [[0,1],[1,1],[0,1],[1,1],[1,0],null,null,null,null,[1,0],[1,0],[1,1],[1,1]]
 * Explanation: All values in the grid are not the same. We divide the grid into four sub-grids.
 * The topLeft, bottomLeft, topRight, bottomRight each has the same value.
 * Notice that the bottomRight is not the same as the other three sub-grids.
 * 
 * Constraints:
 * n == grid.length == grid[i].length
 * n == 2^x where 0 <= x <= 6
 * 
 */
#include <vector>
using namespace std;

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
    Node* construct(vector<vector<int>>& grid) {
        return build(grid, 0, 0, grid.size());
    }

private:
    Node* build(vector<vector<int>>& grid, int r, int c, int size) {
        // Check if all values in the current square are the same
        int val = grid[r][c];
        bool isUniform = true;
        for (int i = r; i < r + size && isUniform; ++i) {
            for (int j = c; j < c + size; ++j) {
                if (grid[i][j] != val) {
                    isUniform = false;
                    break;
                }
            }
        }
        
        if (isUniform) {
            return new Node(val == 1, true);
        }
        
        // Otherwise, split into four quadrants
        int newSize = size / 2;
        Node* topLeft = build(grid, r, c, newSize);
        Node* topRight = build(grid, r, c + newSize, newSize);
        Node* bottomLeft = build(grid, r + newSize, c, newSize);
        Node* bottomRight = build(grid, r + newSize, c + newSize, newSize);
        
        return new Node(false, false, topLeft, topRight, bottomLeft, bottomRight);
    }
};