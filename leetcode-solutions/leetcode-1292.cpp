/**
 * 1292. Maximum Side Length of a Square with Sum Less than or Equal to Threshold
 * 
 * Given a m x n matrix mat and an integer threshold.
 * Return the maximum side-length of a square with a sum less than or equal to threshold or return 0 if there is no such square.
 * 
 * Example 1:
 * Input: mat = [[1,1,3,2,4,3,2],[1,1,3,2,4,3,2],[1,1,3,2,4,3,2]], threshold = 4
 * Output: 2
 * Explanation: The maximum side length of square with sum less than 4 is 2 as shown.
 * 
 * Example 2:
 * Input: mat = [[2,2,2,2,2],[2,2,2,2,2],[2,2,2,2,2],[2,2,2,2,2],[2,2,2,2,2]], threshold = 1
 * Output: 0
 * 
 * Example 3:
 * Input: mat = [[1,1,1,1],[1,0,0,0],[1,0,0,0],[1,0,0,0]], threshold = 6
 * Output: 3
 * 
 * Example 4:
 * Input: mat = [[18,70],[61,1],[25,85],[14,40],[11,96],[97,96],[63,45]], threshold = 40184
 * Output: 2
 * 
 * Note:
 * 1 <= m, n <= 300
 * m == mat.length
 * n == mat[i].length
 * 0 <= mat[i][j] <= 10000
 * 0 <= threshold <= 10^5
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxSideLength(vector<vector<int>>& mat, int threshold) {
        int m = mat.size(), n = mat[0].size();
        // 计算二维前缀和
        vector<vector<int>> prefix(m + 1, vector<int>(n + 1, 0));
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                prefix[i][j] = mat[i-1][j-1] 
                             + prefix[i-1][j] 
                             + prefix[i][j-1] 
                             - prefix[i-1][j-1];
            }
        }

        int left = 1, right = min(m, n), ans = 0;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            bool found = false;

            // 遍历所有可能的左上角 (i-mid, j-mid) 对应的右下角 (i,j)
            for (int i = mid; i <= m; ++i) {
                for (int j = mid; j <= n; ++j) {
                    int sum = prefix[i][j] 
                            - prefix[i-mid][j] 
                            - prefix[i][j-mid] 
                            + prefix[i-mid][j-mid];
                    if (sum <= threshold) {
                        found = true;
                        break;
                    }
                }
                if (found) break;
            }

            if (found) {
                ans = mid;
                left = mid + 1;      // 尝试更大的边长
            } else {
                right = mid - 1;      // 当前边长太大，减小边长
            }
        }
        return ans;
    }
};