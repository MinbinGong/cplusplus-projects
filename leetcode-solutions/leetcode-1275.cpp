/**
 * 1275. Find Winner on a Tic Tac Toe Game
 * 
 * Tic-tac-toe is played by two players A and B on a 3 x 3 grid.
 * 
 * Here are the rules of Tic-Tac-Toe:
 * Players take turns placing characters into empty squares (" ").
 * The first player A always places "X" characters, while the second player B always places "O" characters.
 * "X" and "O" characters are always placed into empty squares, never on filled ones.
 * The game ends when there are 3 of the same (non-empty) character filling any row, column, or diagonal.
 * The game also ends if all squares are non-empty.
 * No more moves can be played if the game is over.
 * Given an array moves where each element is another array of size 2 corresponding to the row and column of the grid where they mark their respective character in the order in which A and B play.
 * 
 * Example 1:
 * Input: moves = [[0,0],[2,0],[1,1],[2,1],[2,2]]
 * Output: "A"
 * Explanation: "A" wins, he always plays first.
 * "X  "    "X  "    "X  "    "X  "    "X  "
 * "   " -> "   " -> " X " -> " X " -> " X "
 * "   "    "O  "    "O  "    "OO "    "OOX"
 * 
 * Example 2:
 * Input: moves = [[0,0],[1,1],[0,1],[0,2],[1,0],[2,0]]
 * Output: "B"
 * Explanation: "B" wins.
 * "X  "    "X  "    "XX "    "XXO"    "XXO"    "XXO"
 * "   " -> " O " -> " O " -> " O " -> "XO " -> "XO " 
 * "   "    "   "    "   "    "   "    "   "    "O  "
 * 
 * Example 3:
 * Input: moves = [[0,0],[1,1],[2,0],[1,0],[1,2],[2,1],[0,1],[0,2],[2,2]]
 * Output: "Draw"
 * Explanation: The game ends in a draw since there are no moves to make.
 * "XXO"
 * "OOX"
 * "XOX"
 * 
 * Note:
 * 1 <= moves.length <= 9
 * moves[i].length == 2
 * 0 <= moves[i][j] <= 2
 * There are no repeated elements on moves.
 * moves follow the rules of tic tac toe.
 * 
 */
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    string tictactoe(vector<vector<int>>& moves) {
        // 初始化3x3棋盘，用空格表示空位
        vector<vector<char>> board(3, vector<char>(3, ' '));
        
        // 根据 moves 填充棋盘：偶数下标为 'X'（玩家A），奇数下标为 'O'（玩家B）
        for (int i = 0; i < moves.size(); ++i) {
            int r = moves[i][0], c = moves[i][1];
            board[r][c] = (i % 2 == 0) ? 'X' : 'O';
        }
        
        // 检查每一行
        for (int i = 0; i < 3; ++i) {
            if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
                return (board[i][0] == 'X') ? "A" : "B";
            }
        }
        
        // 检查每一列
        for (int j = 0; j < 3; ++j) {
            if (board[0][j] != ' ' && board[0][j] == board[1][j] && board[1][j] == board[2][j]) {
                return (board[0][j] == 'X') ? "A" : "B";
            }
        }
        
        // 检查主对角线
        if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
            return (board[0][0] == 'X') ? "A" : "B";
        }
        
        // 检查副对角线
        if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
            return (board[0][2] == 'X') ? "A" : "B";
        }
        
        // 没有赢家：如果棋盘已满则平局，否则待定
        return (moves.size() == 9) ? "Draw" : "Pending";
    }
};