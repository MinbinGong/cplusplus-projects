/*
 * Knight Probability in Chessboard
 *
 * On an NxN chessboard, a knight starts at the r-th row and c-th column and attempts to make exactly K moves. The rows and columns are 0 indexed, so the top-left square is (0, 0), and the bottom-right square is (N-1, N-1).
 *
 * A chess knight has 8 possible moves it can make, as illustrated below. Each move is two squares in a cardinal direction, then one square in an orthogonal direction.
 *
 * Each time the knight is to move, it chooses one of eight possible moves uniformly at random (even if the piece would go off the chessboard) and moves there.
 *
 * The knight continues moving until it has made exactly K moves or has moved off the chessboard. Return the probability that the knight remains on the board after it has stopped moving.
 * 
 * Example:
 *
 * Input: 3, 2, 0, 0
 * Output: 0.0625
 * 
 * Note:
 *
 * The knight probability is calculated based on the number of valid moves the knight can make.
 * 
 */
#include <vector>
#include <numeric>
using namespace std;

class Solution {
public:
    double knightProbability(int n, int k, int row, int column) {
        // 八个可能的移动方向
        vector<pair<int, int>> dirs = {
            {-2, -1}, {-2, 1}, {-1, -2}, {-1, 2},
            {1, -2}, {1, 2}, {2, -1}, {2, 1}
        };

        // dp[i][j] 表示当前步数后位于 (i, j) 的概率
        vector<vector<double>> dp(n, vector<double>(n, 0.0));
        dp[row][column] = 1.0;

        for (int step = 0; step < k; ++step) {
            vector<vector<double>> next(n, vector<double>(n, 0.0));
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (dp[i][j] == 0.0) continue;
                    for (auto& d : dirs) {
                        int ni = i + d.first;
                        int nj = j + d.second;
                        if (ni >= 0 && ni < n && nj >= 0 && nj < n) {
                            // 从 (i,j) 移动到 (ni,nj) 的概率为 dp[i][j] / 8
                            next[ni][nj] += dp[i][j] / 8.0;
                        }
                    }
                }
            }
            dp = move(next);
        }

        // 累加所有位置的概率，即最终仍在棋盘上的总概率
        double ans = 0.0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                ans += dp[i][j];
            }
        }
        return ans;
    }
};