/*
 * 1074. Number of Submatrices That Sum to Target
 *
 * Given a matrix, and a target, return the number of non-empty submatrices that sum to target.
 * A submatrix x1, y1, x2, y2 is the set of all cells matrix[x][y] with x1 <= x <= x2 and y1 <= y <= y2.
 * Two submatrices (x1, y1, x2, y2) and (x1', y1', x2', y2') are different if they have some coordinate that is different: for example, if x1 != x1'.
 * 
 * Example 1:
 * Input: matrix = [[0,1,0],[1,1,1],[0,1,0]], target = 0
 * Output: 4
 * Explanation: The four 1x1 submatrices that only contain 0.
 * 
 * Example 2:
 * Input: matrix = [[1,-1],[-1,1]], target = 0
 * Output: 5
 * Explanation: The two 1x2 submatrices, plus the two 2x1 submatrices, plus the 2x2 submatrix.
 * 
 * Note:
 * 1 <= matrix.length <= 300
 * 1 <= matrix[0].length <= 300
 * -1000 <= matrix[i] <= 1000
 * -10^8 <= target <= 10^8
 * 
 */
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        int n = matrix[0].size();
        int result = 0;
        
        // 计算列方向的前缀和，便于快速计算任意两行之间的列和
        vector<vector<int>> prefixSum(m + 1, vector<int>(n, 0));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                prefixSum[i + 1][j] = prefixSum[i][j] + matrix[i][j];
            }
        }
        
        // 枚举上下边界
        for (int top = 0; top < m; top++) {
            for (int bottom = top; bottom < m; bottom++) {
                // 将 top 到 bottom 之间的行压缩成一维数组
                unordered_map<int, int> sumCount;
                sumCount[0] = 1; // 初始化和为0的情况
                int currentSum = 0;
                
                // 遍历每一列
                for (int col = 0; col < n; col++) {
                    // 计算当前列在 top 到 bottom 之间的和
                    int colSum = prefixSum[bottom + 1][col] - prefixSum[top][col];
                    currentSum += colSum;
                    
                    // 查找是否存在 prefixSum = currentSum - target
                    if (sumCount.find(currentSum - target) != sumCount.end()) {
                        result += sumCount[currentSum - target];
                    }
                    
                    // 更新当前和的出现次数
                    sumCount[currentSum]++;
                }
            }
        }
        
        return result;
    }
};