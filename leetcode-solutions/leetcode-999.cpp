/*
 * 999. Available Captures for Rook
 * 
 * Given the initial configuration of the chessboard, return the number of available captures for the white rook.
 * 
 * Example 1:
 * 
 * Input: [[".",".",".",".",".",".",".","."],[".",".",".","p",".",".",".","."],[".",".",".","R",".",".",".","p"],[".",".",".",".",".",".",".","."],[".",".",".",".",".",".",".","."],[".",".",".","p",".",".",".","."],[".",".",".",".",".",".",".","."],[".",".",".",".",".",".",".","."]]
 * Output: 3
 * Explanation: 
 * In the above diagram, the rook is marked in bold.
 * If the white pawns are captured, the rook is able to move three times.
 * 
 * Example 2:
 * 
 * Input: [[".",".",".",".",".",".",".","."],[".","p","p","p","p","p",".","."],[".","p","p","B","p","p",".","."],[".","p","B","R","B","p",".","."],[".","p","p","B","p","p",".","."],[".","p","p","p","p","p",".","."],[".",".",".",".",".",".",".","."],[".",".",".",".",".",".",".","."]]
 * Output: 0
 * Explanation: 
 * The bishops are blocking the rook from capturing any of the white pawns.
 * 
 * Example 3:
 * 
 * Input: [[".",".",".",".",".",".",".","."],[".",".",".","p",".",".",".","."],[".",".",".","R",".",".",".","."],[".",".",".",".",".",".",".","."],[".",".",".",".",".",".",".","."],[".",".",".","p",".",".",".","."],[".",".",".",".",".",".",".","."],[".",".",".",".",".",".",".","."]]
 * Output: 3
 * Explanation: 
 * The rook is able to capture the three pawns.
 * 
 * Note:
 * 
 * board.length == board[i].length == 8
 * board[i][j] is either 'R', '.', 'B', or 'p'
 * There is exactly one cell with board[i][j] == 'R'
 */
#include <vector>

using namespace std;

class Solution {
public:
    int numRookCaptures(vector<vector<char>>& board) {
        // Locate the rook
        int rx = -1, ry = -1;
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (board[i][j] == 'R') {
                    rx = i;
                    ry = j;
                    break;
                }
            }
            if (rx != -1) break;
        }

        int captures = 0;
        // Four directions: up, down, left, right
        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};

        for (int d = 0; d < 4; ++d) {
            int x = rx + dx[d];
            int y = ry + dy[d];
            while (x >= 0 && x < 8 && y >= 0 && y < 8) {
                if (board[x][y] == 'B') break;        // blocked by bishop
                if (board[x][y] == 'p') {              // pawn found
                    captures++;
                    break;
                }
                x += dx[d];
                y += dy[d];
            }
        }
        return captures;
    }
};