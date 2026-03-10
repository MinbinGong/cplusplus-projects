/**
 * 1738. Find Kth Largest XOR Coordinate Value
 * 
 * You are given a 2D matrix of size m x n, consisting of non-negative integers. You are also given an integer k.
 * The value of coordinate (a, b) of the matrix is the XOR of all matrix[i][j] where 0 <= i <= a < m and 0 <= j <= b < n (0-indexed).
 * Find the kth largest value (1-indexed) of all the coordinates of matrix.
 * 
 * Example 1:
 * Input: matrix = [[5,2],[1,6]], k = 1
 * Output: 7
 * Explanation: The value of coordinate (0,1) is 5 XOR 2 = 7, which is the largest value.
 * 
 * Example 2:
 * Input: matrix = [[5,2],[1,6]], k = 2
 * Output: 5
 * Explanation: The value of coordinate (0,0) is 5 = 5, which is the 2nd largest value.
 * 
 * Constraints:
 * m == matrix.length
 * n == matrix[i].length
 * 1 <= m, n <= 1000
 * 0 <= matrix[i][j] <= 106
 * 1 <= k <= m * n
 * 
 */
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    int kthLargestValue(vector<vector<int>>& matrix, int k) {
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        // 最小堆，用于维护最大的 k 个数
        priority_queue<int, vector<int>, greater<int>> pq;

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                // 二维前缀异或
                dp[i + 1][j + 1] = dp[i][j + 1] ^ dp[i + 1][j] ^ dp[i][j] ^ matrix[i][j];
                int val = dp[i + 1][j + 1];
                pq.push(val);
                if (pq.size() > k) {
                    pq.pop(); // 保持堆中只有最大的 k 个
                }
            }
        }
        return pq.top(); // 堆顶即为第 k 大的值
    }
};