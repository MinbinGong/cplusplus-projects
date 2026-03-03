/**
 * 1504. Count Submatrices With All Ones
 * 
 * Given a rows * columns matrix mat of ones and zeros, return how many submatrices have all ones.
 * 
 * Example 1:
 * Input: mat = [[1,0,1],
 *               [1,1,0],
 *               [1,1,0]]
 * Output: 13
 * Explanation:
 * There are 6 rectangles of side 1x1.
 * There are 2 rectangles of side 1x2.
 * There are 3 rectangles of side 2x1.
 * There is 1 rectangle of side 2x2. 
 * There is 1 rectangle of side 3x1.
 * Total number of rectangles = 6 + 2 + 3 + 1 + 1 = 13.
 * 
 * Example 2:
 * Input: mat = [[0,1,1,0],
 *               [0,1,1,1],
 *               [1,1,1,0]]
 * Output: 24
 * Explanation:
 * There are 8 rectangles of side 1x1.
 * There are 5 rectangles of side 1x2.
 * There are 2 rectangles of side 1x3. 
 * There are 4 rectangles of side 2x1.
 * There are 2 rectangles of side 2x2. 
 * There are 2 rectangles of side 3x1. 
 * There is 1 rectangle of side 3x2. 
 * Total number of rectangles = 8 + 5 + 2 + 4 + 2 + 2 + 1 = 24.
 * 
 * Note:
 * 1 <= rows <= 150
 * 1 <= columns <= 150
 * 0 <= mat[i][j] <= 1
 * 
 */
#include <vector>
#include <stack>
using namespace std;

class Solution {
public:
    int numSubmat(vector<vector<int>>& mat) {
        int m = mat.size(), n = mat[0].size();
        vector<int> height(n, 0);      // 柱状图高度
        int total = 0;

        for (int i = 0; i < m; ++i) {
            // 更新高度
            for (int j = 0; j < n; ++j) {
                if (mat[i][j] == 1) height[j]++;
                else height[j] = 0;
            }

            // 单调栈计算以当前行为底的子矩形数
            stack<int> st;               // 存储索引，高度递增
            vector<int> dp(n, 0);        // dp[j] = 以j结尾的子数组的最小值之和
            for (int j = 0; j < n; ++j) {
                // 弹出所有大于当前高度的栈顶（保持单调递增）
                while (!st.empty() && height[st.top()] > height[j]) {
                    st.pop();
                }
                // 左边第一个小于等于当前高度的索引
                int prev = st.empty() ? -1 : st.top();
                // 递推公式
                dp[j] = (j - prev) * height[j] + (prev >= 0 ? dp[prev] : 0);
                st.push(j);
                total += dp[j];
            }
        }
        return total;
    }
};