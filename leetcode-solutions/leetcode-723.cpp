/*
 * Candy Crush
 *
 * This question is about implementing a basic elimination algorithm for Candy Crush.
 * 
 * Given a 2D integer array board representing the grid of candy, different positive integers board[i][j] represent different types of candies. A value of board[i][j] = 0 represents that the cell at position (i, j) is empty. The given board represents the state of the game following the player's move. Now, you need to restore the board to a stable state by crushing candies according to the following rules:
 * 
 * If three or more candies of the same type are adjacent vertically or horizontally, "crush" them all at the same time - these positions become empty.
 * After crushing all candies simultaneously, if an empty space on the board has candies on top of itself, then these candies will drop until they hit a candy or bottom at the same time. (No new candies will drop outside the top boundary.)
 * After the above steps, there may exist more candies that can be crushed. If so, you need to repeat the above steps.
 * 
 * If there are no more candies that can be crushed, then return the current board.
 * 
 * Note:
 * 1. The length of board will be in the range [3, 50].
 * 2. The length of board[i] will be in the range [3, 50].
 * 3. Each board[i][j] will initially start as an integer in the range [1, 2000].
 * 4. The number of candies in the board will not exceed 2000.
 * 5. The number of operations will not exceed 5000.
 * 6. The given board contains only integers in the range [-1, 2000].
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> candyCrush(vector<vector<int>>& board) {
        int m = board.size(), n = board[0].size();
        bool changed = true;  // 标记本轮是否有消除发生
        
        while (changed) {
            changed = false;
            
            // 1. 横向标记可消除的糖果（连续三个以上）
            for (int i = 0; i < m; ++i) {
                for (int j = 0; j < n - 2; ++j) {
                    int val = abs(board[i][j]);
                    if (val != 0 && abs(board[i][j + 1]) == val && abs(board[i][j + 2]) == val) {
                        board[i][j] = board[i][j + 1] = board[i][j + 2] = -val;
                        changed = true;
                    }
                }
            }
            
            // 2. 纵向标记可消除的糖果（连续三个以上）
            for (int j = 0; j < n; ++j) {
                for (int i = 0; i < m - 2; ++i) {
                    int val = abs(board[i][j]);
                    if (val != 0 && abs(board[i + 1][j]) == val && abs(board[i + 2][j]) == val) {
                        board[i][j] = board[i + 1][j] = board[i + 2][j] = -val;
                        changed = true;
                    }
                }
            }
            
            // 3. 如果有消除发生，执行重力下落
            if (changed) {
                // 按列处理下落
                for (int j = 0; j < n; ++j) {
                    int writePos = m - 1;  // 从底部开始填充
                    
                    // 从下往上，将正数（未消除的糖果）移到 writePos 位置
                    for (int i = m - 1; i >= 0; --i) {
                        if (board[i][j] > 0) {
                            board[writePos][j] = board[i][j];
                            --writePos;
                        }
                    }
                    
                    // 上方剩余位置填充0
                    for (int i = writePos; i >= 0; --i) {
                        board[i][j] = 0;
                    }
                }
            }
        }
        
        return board;
    }
};