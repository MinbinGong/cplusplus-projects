/*
 *  Diagonal Traverse
 *
 *  Given an m x n matrix mat, return an array of all the elements of the array in a diagonal order.
 *
 *  Constraints:
 *  m == mat.length
 *  n == mat[i].length
 *  1 <= m, n <= 104
 *  1 <= m * n <= 104
 *  -105 <= mat[i][j] <= 105
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& mat) {
        if (mat.empty() || mat[0].empty()) return {};
        int m = mat.size(), n = mat[0].size();
        vector<int> result;
        int r = 0, c = 0;
        int dir = 1; // 1 = up-right, -1 = down-left

        for (int i = 0; i < m * n; ++i) {
            result.push_back(mat[r][c]);

            // Determine next cell based on current direction
            if (dir == 1) { // moving up-right
                if (c == n - 1) {       // hit right boundary -> move down
                    ++r;
                    dir = -1;
                } else if (r == 0) {     // hit top boundary -> move right
                    ++c;
                    dir = -1;
                } else {                  // continue up-right
                    --r;
                    ++c;
                }
            } else { // moving down-left
                if (r == m - 1) {       // hit bottom boundary -> move right
                    ++c;
                    dir = 1;
                } else if (c == 0) {     // hit left boundary -> move down
                    ++r;
                    dir = 1;
                } else {                  // continue down-left
                    ++r;
                    --c;
                }
            }
        }
        return result;
    }
};