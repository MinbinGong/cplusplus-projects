/*
 * Design Tic-Tac-Toe
 * 
 * Design a Tic-tac-toe game that is played between two players on a n x n grid.
 * 
 * You may assume the following rules:
 * 
 * A move is guaranteed to be valid and is placed on an empty block.
 * Once a winning condition is reached, no more moves is allowed.
 * A player who succeeds in placing n of their marks in a horizontal, vertical, or diagonal row wins the game.
 * 
 * Example:
 * Given n = 3, assume that player 1 is "X" and player 2 is "O" in the board.
 * 
 * TicTacToe toe = new TicTacToe(3);
 * 
 * toe.move(0, 0, 1); -> Returns 0 (no one wins)
 * |X| | |
 * | | | |    // Player 1 makes a move at (0, 0).
 * | | | |
 * 
 * toe.move(0, 2, 2); -> Returns 0 (no one wins)
 * |X| |O|
 */
#include <vector>
#include <cstdlib> // for abs

using namespace std;

class TicTacToe {
private:
    vector<int> rows;   // 每行的累计值（player1 +1, player2 -1）
    vector<int> cols;   // 每列的累计值
    int diag;           // 主对角线累计值
    int antiDiag;       // 副对角线累计值
    int n;              // 棋盘大小

public:
    /** Initialize your data structure here. */
    TicTacToe(int n) {
        this->n = n;
        rows.resize(n, 0);
        cols.resize(n, 0);
        diag = 0;
        antiDiag = 0;
    }
    
    /** Player {player} makes a move at ({row}, {col}).
        @param row The row of the board.
        @param col The column of the board.
        @param player The player, can be either 1 or 2.
        @return The current winning condition, can be either:
                0: No one wins.
                1: Player 1 wins.
                2: Player 2 wins. */
    int move(int row, int col, int player) {
        int delta = (player == 1) ? 1 : -1;   // player1 加1，player2 减1

        rows[row] += delta;
        cols[col] += delta;

        // 主对角线：行号等于列号
        if (row == col) {
            diag += delta;
        }
        // 副对角线：行号 + 列号 = n - 1
        if (row + col == n - 1) {
            antiDiag += delta;
        }

        // 检查是否有玩家获胜
        if (abs(rows[row]) == n || abs(cols[col]) == n ||
            abs(diag) == n || abs(antiDiag) == n) {
            return player;
        }
        return 0;
    }
};

/**
 * Your TicTacToe object will be instantiated and called as such:
 * TicTacToe* obj = new TicTacToe(n);
 * int param_1 = obj->move(row,col,player);
 */