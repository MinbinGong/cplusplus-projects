/*
 * 1198. Find Smallest Common Element in All Rows
 *
 * Given a matrix mat where every row is sorted in increasing order, return the smallest common element in all rows.
 * 
 * If there is no common element, return -1.
 * 
 * Example 1:
 * Input: mat = [[1,2,3,4,5],[2,4,5,8,10],[3,5,7,9,11],[1,3,5,7,9]]
 * Output: 5
 * 
 * Note:
 * 1 <= mat.length, mat[i].length <= 500
 * 1 <= mat[i][j] <= 10^4
 * mat[i] is sorted in increasing order.
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int smallestCommonElement(vector<vector<int>>& mat) {
        int m = mat.size(), n = mat[0].size();
        // 遍历第一行的每个元素，因为第一行已经排序，所以从小到大的顺序
        for (int j = 0; j < n; ++j) {
            int candidate = mat[0][j];
            bool found = true;
            // 检查该元素是否在其他每一行中出现
            for (int i = 1; i < m; ++i) {
                if (!binary_search(mat[i].begin(), mat[i].end(), candidate)) {
                    found = false;
                    break;
                }
            }
            if (found) return candidate;
        }
        return -1;
    }
};