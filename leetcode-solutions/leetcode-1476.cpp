/**
 * 1476. Subrectangle Queries
 * 
 * Implement the class SubrectangleQueries which receives a rows x cols rectangle as a matrix of integers in the constructor and supports two methods:
 * 
 * 1. updateSubrectangle(int row1, int col1, int row2, int col2, int newValue)
 * 
 * Updates all values with newValue in the subrectangle whose upper left coordinate is (row1,col1) and bottom right coordinate is (row2,col2).
 * 
 * 2. getValue(int row, int col)
 * 
 * Returns the current value of the coordinate (row,col) from the rectangle.
 * 
 * Example 1:
 * Input: 
 * ["SubrectangleQueries","getValue","updateSubrectangle","getValue","getValue","updateSubrectangle","getValue","getValue"]
 * [[[[1,2,1],[4,3,4],[3,2,1],[1,1,1]]],[0,2],[0,0,3,2,5],[0,2],[3,1],[3,0,3,2,10],[3,1],[0,2]]
 * Output: [1,5,5,10]
 * Explanation: 
 * The initial rectangle (4x3) looks like:
 * 1 2 1
 * 4 3 4
 * 3 2 1
 * 1 1 1
 * After the updateSubrectangle operation (row1, col1, row2, col2, newValue) = (0, 0, 3, 2, 5):
 * 5 2 5
 * 5 3 5
 * 5 2 5
 * 5 1 5
 * After the second getValue operation (0, 2) = 5, we return 5.
 * After the third getValue operation (3, 1) = 10, we return 10.
 * 
 * Example 2:
 * Input: 
 * ["SubrectangleQueries","getValue","updateSubrectangle","getValue","getValue","updateSubrectangle","getValue"]
 * [[[[1,1,1],[2,2,2],[3,3,3]]],[0,0],[0,0,2,2,100],[0,0],[2,2],[1,1,2,2,20],[2,2]]
 * Output: [1,100,20]
 * Explanation: 
 * The initial rectangle (3x3) looks like:
 * 1 1 1
 * 2 2 2
 * 3 3 3
 * After the updateSubrectangle operation (row1, col1, row2, col2, newValue) = (0, 0, 2, 2, 100):
 * 100 100 100
 * 100 100 100
 * 100 100 100
 * After the second getValue operation (0, 0) = 100, we return 100.
 * After the third getValue operation (2, 2) = 20, we return 20.
 * 
 * Note:
 * 1 <= rows, cols <= 100
 * rows == rectangle.length
 * cols == rectangle[i].length
 * 0 <= row1 <= row2 < rows
 * 0 <= col1 <= col2 < cols
 * 1 <= newValue, rectangle[i][j] <= 10^9
 * 0 <= row < rows
 * 0 <= col < cols
 * At most 5000 calls will be made to updateSubrectangle and getValue.
 * 
 */
#include <vector>
using namespace std;

class SubrectangleQueries1 {
private:
    vector<vector<int>> rectangle;
    
public:
    SubrectangleQueries1(vector<vector<int>>& rect) {
        rectangle = rect;  // Store a copy of the initial matrix
    }
    
    void updateSubrectangle(int row1, int col1, int row2, int col2, int newValue) {
        // Directly update all cells in the rectangle
        for (int i = row1; i <= row2; i++) {
            for (int j = col1; j <= col2; j++) {
                rectangle[i][j] = newValue;
            }
        }
    }
    
    int getValue(int row, int col) {
        return rectangle[row][col];  // Simple lookup
    }
};

class SubrectangleQueries2 {
private:
    vector<vector<int>> rectangle;
    // Store operations as {row1, col1, row2, col2, newValue}
    vector<array<int, 5>> operations;
    
public:
    SubrectangleQueries2(vector<vector<int>>& rect) {
        rectangle = rect;
    }
    
    void updateSubrectangle(int row1, int col1, int row2, int col2, int newValue) {
        // Just record the operation - O(1)
        operations.push_back({row1, col1, row2, col2, newValue});
    }
    
    int getValue(int row, int col) {
        // Check operations from most recent to oldest
        for (int i = operations.size() - 1; i >= 0; i--) {
            auto& op = operations[i];
            if (row >= op[0] && col >= op[1] && 
                row <= op[2] && col <= op[3]) {
                return op[4];  // Found most recent applicable update
            }
        }
        // No updates affected this cell
        return rectangle[row][col];
    }
};