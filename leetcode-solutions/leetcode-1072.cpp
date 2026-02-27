/*
 * 1072. Flip Columns For Maximum Number of Equal Rows
 *
 * Given a matrix consisting of 0s and 1s, we may choose any number of columns in the matrix and flip every cell in that column.  Flipping a cell changes the value of that cell from 0 to 1 or from 1 to 0.
 * Return the maximum number of rows that have all values equal after some number of flips.
 * 
 * Example 1:
 * Input: [[0,1],[1,1]]
 * Output: 1
 * Explanation: After flipping no values, 1 row has all values equal.
 * 
 * Example 2:
 * Input: [[0,1],[1,0]]
 * Output: 2
 * Explanation: After flipping values in the first column, both rows have equal values.
 * 
 * Example 3:
 * Input: [[0,0,0],[0,0,1],[1,1,0]]
 * Output: 2
 * Explanation: After flipping values in the first two columns, the last two rows have equal values.
 * 
 * Note:
 * 1 <= matrix.length <= 300
 * 1 <= matrix[i].length <= 300
 * All matrix[i].length's are equal
 * matrix[i][j] is 0 or 1
 * 
 */
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxEqualRowsAfterFlips(vector<vector<int>>& matrix) {
        unordered_map<string, int> patternCount;
        int maxRows = 0;
        
        for (const auto& row : matrix) {
            // 构建标准化模式字符串
            string pattern;
            // 如果行首是1，则翻转整行（即每个元素与行首异或）
            int first = row[0];
            for (int num : row) {
                pattern.push_back((num ^ first) + '0'); // 异或操作实现标准化
            }
            
            patternCount[pattern]++;
            maxRows = max(maxRows, patternCount[pattern]);
        }
        
        return maxRows;
    }
};