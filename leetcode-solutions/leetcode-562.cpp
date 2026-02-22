/*
 * Longest Line of Consecutive One in Matrix
 *
 * Given a 01 matrix M, find the longest line of consecutive one in the matrix. The line could be horizontal, vertical, diagonal or anti-diagonal.
 * 
 * Example:
 * Input:
 * [[0,1,1,0],
 *  [0,1,1,0],
 *  [0,0,0,1]]
 * Output: 3
 * 
 * Note:
 * The number of elements in the given matrix will not exceed 10,000.
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    int longestLine(vector<vector<int>>& mat) {
        int m = mat.size();
        if (m == 0) return 0;
        int n = mat[0].size();
        if (n == 0) return 0;

        // 使用四个二维数组分别记录四个方向的长度
        vector<vector<int>> horizontal(m, vector<int>(n, 0));
        vector<vector<int>> vertical(m, vector<int>(n, 0));
        vector<vector<int>> diagonal(m, vector<int>(n, 0));
        vector<vector<int>> antiDiagonal(m, vector<int>(n, 0));

        int maxLen = 0;

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (mat[i][j] == 1) {
                    // 水平方向：从左边继承
                    horizontal[i][j] = (j > 0) ? horizontal[i][j - 1] + 1 : 1;
                    // 垂直方向：从上边继承
                    vertical[i][j] = (i > 0) ? vertical[i - 1][j] + 1 : 1;
                    // 对角线（左上到右下）：从左上方继承
                    diagonal[i][j] = (i > 0 && j > 0) ? diagonal[i - 1][j - 1] + 1 : 1;
                    // 反对角线（右上到左下）：从右上方继承
                    antiDiagonal[i][j] = (i > 0 && j < n - 1) ? antiDiagonal[i - 1][j + 1] + 1 : 1;

                    // 更新全局最大值
                    maxLen = max(maxLen, horizontal[i][j]);
                    maxLen = max(maxLen, vertical[i][j]);
                    maxLen = max(maxLen, diagonal[i][j]);
                    maxLen = max(maxLen, antiDiagonal[i][j]);
                }
                // 如果 mat[i][j] == 0，对应的 dp 值保持为 0（因为初始化时就是 0）
            }
        }
        return maxLen;
    }
};