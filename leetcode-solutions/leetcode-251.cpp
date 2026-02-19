/*
 * Flatten 2D Vector
 * 
 * Implement an iterator to flatten a 2d vector.
 * 
 * Design an iterator to flatten a 2D vector. It should support the next and hasNext operations.
 * 
 * Implement the Vector2D class:
 * 
 * Vector2D(int[][] vec) initializes the object with the 2D vector vec.
 * next() returns the next element from the 2D vector and moves the pointer one step forward. You may assume that all
 * the calls to next are valid.
 * hasNext() returns true if there are still some elements in the vector, and false otherwise.
 * 
 * Constraints:
 * 1. 0 <= vec.length <= 200
 * 2. 0 <= vec[i].length <= 500
 * 3. -105 <= vec[i][j] <= 105
 * 4. At most 105 calls will be made to next and hasNext.
 */
#include <vector>
using namespace std;

class Vector2D {
private:
    vector<vector<int>>& data;  // reference to the 2D vector
    int row;
    int col;

    // Move to the next valid position (skip empty rows)
    void advance() {
        while (row < data.size() && col >= data[row].size()) {
            ++row;
            col = 0;
        }
    }

public:
    Vector2D(vector<vector<int>>& vec) : data(vec), row(0), col(0) {
        advance(); // start at the first valid element
    }

    int next() {
        // Assume hasNext() is true; otherwise behavior undefined
        int val = data[row][col];
        ++col;           // move column forward
        advance();       // skip to next valid position
        return val;
    }

    bool hasNext() {
        return row < data.size();
    }
};