/**
 * 867. Transpose Matrix
 * 
 * Example 1:
 * Input: [[1,2,3],[4,5,6],[7,8,9]]
 * Output: [[1,4,7],[2,5,8],[3,6,9]]
 * 
 * Example 2:
 * Input: [[1,2,3],[4,5,6]]
 * Output: [[1,4],[2,5],[3,6]]
 * 
 * Note:
 * 1 <= A.length <= 1000
 * 1 <= A[0].length <= 1000
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> transpose(vector<vector<int>>& matrix) {
        int m = matrix.size();       // number of rows
        int n = matrix[0].size();    // number of columns
        // Create a new matrix with dimensions n x m
        vector<vector<int>> result(n, vector<int>(m));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                result[j][i] = matrix[i][j];
            }
        }
        return result;
    }
};