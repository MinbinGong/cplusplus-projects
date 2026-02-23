/*
 * 782. Transform to Chessboard
 *
 * An N x N board contains only 0s and 1s. In each move, you can swap any 2 rows with each other, or any 2 columns with each other.
 * 
 * What is the minimum number of moves to transform the board into a "chessboard" - a board where no 0s and no 1s are 4-directionally adjacent? If the task is impossible, return -1.
 * 
 * Examples:
 * Input: board = [[0,1,1,0],[0,1,1,0],[1,0,0,1],[1,0,0,1]]
 * Output: 2
 * Explanation:
 * One potential sequence of moves is shown below, from left to right:
 * 0110     1010     1010
 * 0110 --> 1010 --> 0101
 * 1001     0101     1010
 * 
 * Input: board = [[0,1],[1,0]]
 * Output: 0
 * Explanation:
 * Note that the top left corner, board[0][0], is not a 0 or 1.
 * 
 * Input: board = [[1,0],[1,0]]
 * Output: -1
 * Explanation:
 * No matter what sequence of moves you make, you cannot end with a valid chessboard.
 * 
 * Note:
 * 1. board will have the same number of rows and columns, a number in the range [2, 30].
 * 2. board[i][j] will be only 0s or 1s.
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    int movesToChessboard(vector<vector<int>>& board) {
        int n = board.size();
        // Check rows: they must be either the same as row0 or its complement
        vector<int> row0 = board[0];
        int cntRow0 = 0; // number of rows equal to row0
        vector<bool> rowIs0(n, false);
        for (int i = 0; i < n; ++i) {
            bool same = true, comp = true;
            for (int j = 0; j < n; ++j) {
                if (board[i][j] != row0[j]) same = false;
                if (board[i][j] != (1 - row0[j])) comp = false;
            }
            if (!same && !comp) return -1;
            if (same) {
                rowIs0[i] = true;
                cntRow0++;
            }
        }

        // Check columns: similarly with col0
        vector<int> col0(n);
        for (int i = 0; i < n; ++i) col0[i] = board[i][0];
        int cntCol0 = 0;
        vector<bool> colIs0(n, false);
        for (int j = 0; j < n; ++j) {
            bool same = true, comp = true;
            for (int i = 0; i < n; ++i) {
                if (board[i][j] != col0[i]) same = false;
                if (board[i][j] != (1 - col0[i])) comp = false;
            }
            if (!same && !comp) return -1;
            if (same) {
                colIs0[j] = true;
                cntCol0++;
            }
        }

        // Count how many rows of type 0 are at even indices (0-based)
        int evenRows = (n + 1) / 2; // number of even indices
        int oddRows = n / 2;
        int evenRowZero = 0;
        for (int i = 0; i < n; i += 2) if (rowIs0[i]) evenRowZero++;

        int rowSwaps = INT_MAX;
        if (cntRow0 == evenRows) // can put type0 on even indices
            rowSwaps = min(rowSwaps, evenRows - evenRowZero);
        if (cntRow0 == oddRows)  // can put type0 on odd indices
            rowSwaps = min(rowSwaps, evenRowZero); // even indices should be type1, so type0 there need to be swapped
        if (rowSwaps == INT_MAX) return -1;

        // Similarly for columns
        int evenColZero = 0;
        for (int j = 0; j < n; j += 2) if (colIs0[j]) evenColZero++;
        int colSwaps = INT_MAX;
        if (cntCol0 == evenRows) colSwaps = min(colSwaps, evenRows - evenColZero);
        if (cntCol0 == oddRows)  colSwaps = min(colSwaps, evenColZero);
        if (colSwaps == INT_MAX) return -1;

        return rowSwaps + colSwaps;
    }
};