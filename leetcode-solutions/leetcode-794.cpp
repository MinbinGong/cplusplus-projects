/*
 * 794. Valid Tic-Tac-Toe State
 *
 * A Tic-Tac-Toe board is given as a string array board. Return True if and only if it is possible to reach this board position during the course of a valid tic-tac-toe game.
 * 
 * The board is a 3 x 3 array, and consists of characters " ", "X", and "O".  The " " character represents an empty square.
 * 
 * Here are the rules of Tic-Tac-Toe:
 * 1. Players take turns placing characters into empty squares (" ").
 * 2. The first player always places "X" characters, while the second player always places "O" characters.
 * 3. "X" and "O" characters are always placed into empty squares, never filled ones.
 * 4. The game ends when there are 3 of the same (non-empty) character filling any row, column, or diagonal.
 * 5. The game also ends if all squares are non-empty.
 * 6. No more moves can be played if the game is over.
 * 
 * Example 1:
 * Input: board = ["O  ", "   ", "   "]
 * Output: false
 * Explanation: The first player always plays "X".
 * 
 * Example 2:
 * Input: board = ["XOX", " X ", "   "]
 * Output: false
 * Explanation: Players take turns making moves.
 * 
 * Note:
 * 1. board is a length-3 array of strings, where each string board[i] has length 3.
 * 2. Each board[i][j] is a character in the set {" ", "X", "O"}.
 * 3. The answer is guaranteed to fit in a 32-bit signed integer.
 * 
 */
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    bool validTicTacToe(vector<string>& board) {
        int cntX = 0, cntO = 0;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == 'X') cntX++;
                else if (board[i][j] == 'O') cntO++;
            }
        }
        // X always moves first, so either equal or X one more
        if (cntX != cntO && cntX != cntO + 1) return false;

        bool winX = checkWin(board, 'X');
        bool winO = checkWin(board, 'O');

        // Both cannot win
        if (winX && winO) return false;
        // If X wins, countX must be countO+1
        if (winX && cntX != cntO + 1) return false;
        // If O wins, counts must be equal
        if (winO && cntX != cntO) return false;
        return true;
    }

private:
    bool checkWin(vector<string>& board, char c) {
        // rows
        for (int i = 0; i < 3; ++i) {
            if (board[i][0] == c && board[i][1] == c && board[i][2] == c) return true;
        }
        // columns
        for (int j = 0; j < 3; ++j) {
            if (board[0][j] == c && board[1][j] == c && board[2][j] == c) return true;
        }
        // diagonals
        if (board[0][0] == c && board[1][1] == c && board[2][2] == c) return true;
        if (board[0][2] == c && board[1][1] == c && board[2][0] == c) return true;
        return false;
    }
};