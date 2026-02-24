/**
 * 861. Score After Flipping Matrix
 * 
 * Example 1:
 * Input: [[0,0,1,1],[1,0,1,0],[1,1,0,0]]
 * Output: 39
 * Explanation:
 * Toggled to [[1,1,1,1],[1,0,0,1],[1,1,1,1]].
 * 0b1111 + 0b1001 + 0b1111 = 15 + 9 + 15 = 39
 * 
 * Note:
 * 1 <= A.length <= 20
 * 1 <= A[0].length <= 20
 * A[i][j] is 0 or 1.
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    int matrixScore(vector<vector<int>>& A) {
        int m = A.size(), n = A[0].size();
        // 确保每行第一个元素为1
        for (int i = 0; i < m; ++i) {
            if (A[i][0] == 0) {
                for (int j = 0; j < n; ++j) {
                    A[i][j] ^= 1; // 翻转整行
                }
            }
        }
        // 计算总分：第一列贡献固定为 m * 2^(n-1)
        int res = m * (1 << (n - 1));
        // 处理剩余列
        for (int j = 1; j < n; ++j) {
            int cnt1 = 0;
            for (int i = 0; i < m; ++i) {
                if (A[i][j] == 1) cnt1++;
            }
            // 取该列1的最大可能个数
            cnt1 = max(cnt1, m - cnt1);
            res += cnt1 * (1 << (n - 1 - j));
        }
        return res;
    }
};