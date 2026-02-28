/**
 * 1222. Queens That Can Attack the King
 *
 * On an 8x8 chessboard, there can be multiple Black Queens and one White King.
 *
 * Given an array of integer coordinates queens that represents the positions of the Black Queens, and a pair of coordinates king that represent the position of the White King, return the coordinates of all the queens (in any order) that can attack the King.
 *
 *
 *
 * Example 1:
 *
 * Input: queens = [[0,1],[1,0],[4,0],[0,4],[3,3],[2,4]], king = [0,0]
 * Output: [[0,1],[1,0],[3,3]]
 * Explanation:
 * The queen at [0,1] can attack the king cause they're in the same row.
 * The queen at [1,0] can attack the king cause they're in the same column.
 * The queen at [3,3] can attack the king cause they're in the same diagnal.
 * 
 * Example 2:
 *
 * Input: queens = [[0,0],[1,1],[2,2],[3,4],[3,5],[4,4],[4,5]], king = [3,3]
 * Output: [[2,2],[3,4],[4,4]]
 * Explanation:
 * The queen at [2,2] can attack the king cause they're in the same diagnal.
 * The queen at [3,4] can attack the king cause they're in the same diagnal.
 * The queen at [4,4] can attack the king cause they're in the same row.
 * 
 * Example 3:
 *
 * Input: queens = [[5,6],[7,7],[2,1],[0,7],[1,6],[5,1],[3,7],[0,3],[4,0],[1,2],[6,3],[5,0],[0,4],[2,2],[1,1],[6,4],[5,4],[0,0],[2,6],[4,5],[5,2],[1,4],[7,5],[2,3],[0,5],[4,2],[1,0],[2,7],[0,1],[4,6],[6,1],[0,6],[4,3],[1,7]], king = [3,4]
 * Output: [[2,3],[1,4],[1,6],[3,7],[4,3],[5,4],[4,5]]
 * Explanation:
 * The queen at [2,3] can attack the king cause they're in the same diagnal.
 * The queen at [1,4] can attack the king cause they're in the same column.
 * The queen at [1,6] can attack the king cause they're in the same row.
 * The queen at [3,7] can attack the king cause they're in the same diagnal.
 * The queen at [4,3] can attack the king cause they're in the same row.
 * The queen at [5,4] can attack the king cause they're in the same diagnal.
 * The queen at [4,5] can attack the king cause they're in the same row.
 * 
 * Constraints:
 *
 * 1 <= queens.length <= 63
 * queens[i].length == 2
 * 0 <= queens[i][j] < 8
 * king.length == 2
 * 0 <= king[0], king[1] < 8
 * At most one piece is allowed in a cell.
 * 
 */
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <string>

using namespace std;

class Solution1 {
public:
    vector<vector<int>> queensAttacktheKing(vector<vector<int>>& queens, vector<int>& king) {
        // 使用8x8的棋盘标记皇后的位置
        bool board[8][8] = {false};
        for (const auto& queen : queens) {
            board[queen[0]][queen[1]] = true;
        }
        
        // 8个方向：上、下、左、右、左上、右上、左下、右下
        vector<vector<int>> directions = {
            {-1, 0}, {1, 0}, {0, -1}, {0, 1},
            {-1, -1}, {-1, 1}, {1, -1}, {1, 1}
        };
        
        vector<vector<int>> result;
        int kx = king[0], ky = king[1];
        
        // 向每个方向搜索
        for (const auto& dir : directions) {
            int dx = dir[0], dy = dir[1];
            int x = kx + dx, y = ky + dy;
            
            // 沿着当前方向一直搜索直到超出棋盘边界
            while (x >= 0 && x < 8 && y >= 0 && y < 8) {
                if (board[x][y]) {
                    // 找到皇后，加入结果并停止当前方向的搜索
                    result.push_back({x, y});
                    break;
                }
                x += dx;
                y += dy;
            }
        }
        
        return result;
    }
};

// 另一种实现：使用哈希表存储皇后位置
class Solution2 {
public:
    vector<vector<int>> queensAttacktheKing(vector<vector<int>>& queens, vector<int>& king) {
        // 使用哈希表存储皇后位置，便于快速查找
        unordered_set<string> queenSet;
        for (const auto& queen : queens) {
            queenSet.insert(to_string(queen[0]) + "," + to_string(queen[1]));
        }
        
        vector<vector<int>> directions = {
            {-1, 0}, {1, 0}, {0, -1}, {0, 1},
            {-1, -1}, {-1, 1}, {1, -1}, {1, 1}
        };
        
        vector<vector<int>> result;
        int kx = king[0], ky = king[1];
        
        for (const auto& dir : directions) {
            int x = kx + dir[0], y = ky + dir[1];
            while (x >= 0 && x < 8 && y >= 0 && y < 8) {
                string pos = to_string(x) + "," + to_string(y);
                if (queenSet.find(pos) != queenSet.end()) {
                    result.push_back({x, y});
                    break;
                }
                x += dir[0];
                y += dir[1];
            }
        }
        
        return result;
    }
};
