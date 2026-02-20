/*
 * Game of Life
 *
 * According to the Wikipedia's article: "The Game of Life, also known simply as Life,
 * is a cellular automaton devised by the British mathematician John Horton Conway in 1970."
 * 
 * Given a board with m by n cells, each cell has an initial state live (1) or dead (0).
 * Each cell interacts with its eight neighbors (horizontal, vertical, diagonal) using the following four rules
 * (taken from the above Wikipedia article):
 * 
 * 1. Any live cell with fewer than two live neighbors dies, as if caused by under-population.
 * 2. Any live cell with two or three live neighbors lives on to the next generation.
 * 3. Any live cell with more than three live neighbors dies, as if by over-population..
 * 4. Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
 * 
 * Write a function to compute the next state (after one update) of the board given its current state.
 * The next state is created by applying the above rules simultaneously to every cell in the current state,
 * where births and deaths occur simultaneously.
 * 
 * Example:
 * 
 * Input: 
 * [
 *   [0,1,0],
 *   [0,0,1],
 *   [1,1,1],
 *   [0,0,0]
 * ]
 * Output: 
 * [
 *   [0,0,0],
 *   [1,0,1],
 *   [0,1,1],
 *   [0,1,0]
 * ]
 * 
 * Follow up:
 * 
 * 1. Could you solve it in-place? Remember that the board needs to be updated at the same time:
 *    You cannot update some cells first and then use their updated values to update other cells.
 * 2. In this question, we represent the board using a 2D array. In principle, the board is infinite,
 *    which would cause problems when the active area encroaches the border of the array.
 *    How would you address these problems?
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    void gameOfLife(vector<vector<int>>& board) {
        int m = board.size();
        int n = board[0].size();
        
        // 方向数组：八个邻居的偏移量
        int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
        int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};
        
        // 第一遍遍历：计算每个细胞的下一状态，并编码到高位（第1位）
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                int liveNeighbors = 0;
                // 统计八个邻居中的原始活细胞（即最低位为1）
                for (int k = 0; k < 8; ++k) {
                    int ni = i + dx[k];
                    int nj = j + dy[k];
                    if (ni >= 0 && ni < m && nj >= 0 && nj < n) {
                        // 通过 & 1 获取原始状态
                        liveNeighbors += (board[ni][nj] & 1);
                    }
                }
                
                // 当前细胞原始状态
                int cur = board[i][j] & 1;
                
                // 应用生命游戏规则，确定下一状态
                if (cur == 1) {
                    // 活细胞：邻居为2或3则继续活，否则死亡
                    if (liveNeighbors < 2 || liveNeighbors > 3) {
                        // 下一状态为0，高位保持0即可（即 board[i][j] 不变，但高位已经是0）
                        // 实际上不需要额外操作，因为高位默认为0
                        // 为了清晰，可以留空
                    } else {
                        // 下一状态为1，将高位设置为1（即给第1位赋1）
                        board[i][j] |= 2; // 设置高位为1
                    }
                } else {
                    // 死细胞：邻居正好3个则复活
                    if (liveNeighbors == 3) {
                        // 下一状态为1，将高位设置为1
                        board[i][j] |= 2;
                    }
                }
            }
        }
        
        // 第二遍遍历：将所有细胞右移一位，将下一状态变为当前状态
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                board[i][j] >>= 1; // 右移后，高位（下一状态）移动到低位
            }
        }
    }
};