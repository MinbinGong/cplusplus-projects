/**
 * 1428. Leftmost Column with at Least a One
 * 
 * (This problem is an interactive problem.)
 * 
 * A binary matrix means that all elements are 0 or 1. For each individual row of the matrix, this row is sorted in non-decreasing order.
 * 
 * Given a row-sorted binary matrix binaryMatrix, return leftmost column index(0-indexed) with at least a 1 in it. If such index doesn't exist, return -1.
 * 
 * You can't access the Binary Matrix directly.  You may only access the matrix using a BinaryMatrix interface:
 * 
 * BinaryMatrix.get(x, y) returns the element of the matrix at index (x, y) (0-indexed).
 * BinaryMatrix.dimensions() returns a list of 2 elements [n, m], which means the matrix is n * m.
 * Submissions making more than 1000 calls to BinaryMatrix.get will be judged Wrong Answer.  Also, any solutions that attempt to circumvent the judge will result in disqualification.
 * 
 * Example 1:
 * 
 * Input: mat = [[0,0],[1,1]]
 * Output: 0
 * 
 * Example 2:
 * 
 * Input: mat = [[0,0],[0,1]]
 * Output: 1
 * 
 * Example 3:
 * 
 * Input: mat = [[0,0],[0,0]]
 * Output: -1
 * 
 * Note:
 * 1 <= mat.length, mat[i].length <= 100
 * mat[i][j] is either 0 or 1.
 * mat[i] is sorted in a non-decreasing way.
 * 
 */
/**
 * // This is the BinaryMatrix's API interface.
 * // You should not implement it, or speculate about its implementation
 * class BinaryMatrix {
 *   public:
 *     int get(int row, int col);
 *     vector<int> dimensions();
 * };
 */
#include <vector>
using namespace std;

class Solution {
public:
    int leftMostColumnWithOne(BinaryMatrix &binaryMatrix) {
        // Get matrix dimensions
        vector<int> dim = binaryMatrix.dimensions();
        int rows = dim[0], cols = dim[1];
        
        int row = 0, col = cols - 1;
        int leftmost = -1;          // track the leftmost column with a 1 found so far
        
        // Start from top‑right corner
        while (row < rows && col >= 0) {
            if (binaryMatrix.get(row, col) == 1) {
                leftmost = col;      // found a 1 at this column
                --col;                // try to find an even leftmost column in the same row
            } else {
                ++row;                // no 1 in this row at or left of current column → go down
            }
        }
        
        return leftmost;
    }
};
