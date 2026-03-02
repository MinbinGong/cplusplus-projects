/*
 * 1337. The K Weakest Rows in a Matrix
 *
 * Given a m * n matrix mat of ones (representing soldiers) and zeros (representing civilians), return the indexes of the k weakest rows in the matrix ordered from the weakest to the strongest.
 * 
 * A row i is weaker than row j, if the number of soldiers in row i is less than the number of soldiers in row j, or they have the same number of soldiers but i is less than j. Soldiers are always stand in the frontier of a row, that is, always ones may appear first and then zeros.
 * 
 * Example 1:
 * Input: mat = 
 * [[1,1,0,0,0],
 *  [1,1,1,1,0],
 *  [1,0,0,0,0],
 *  [1,1,0,0,0],
 *  [1,1,1,1,1]], 
 * k = 3
 * Output: [2,0,3]
 * Explanation: 
 * The number of soldiers for each row is: 
 * row 0 -> 2 
 * row 1 -> 4 
 * row 2 -> 1 
 * row 3 -> 2 
 * row 4 -> 5 
 * Rows ordered from the weakest to the strongest are [2,0,3,1,4]
 * 
 * Example 2:
 * Input: mat = 
 * [[1,0,0,0],
 *  [1,1,1,1],
 *  [1,0,0,0],
 *  [1,0,0,0]], 
 * k = 2
 * Output: [0,2]
 * Explanation: 
 * The number of soldiers for each row is: 
 * row 0 -> 1 
 * row 1 -> 4 
 * row 2 -> 1 
 * row 3 -> 1 
 * Rows ordered from the weakest to the strongest are [0,2,3,1]
 * 
 * Note:
 * m == mat.length
 * n == mat[i].length
 * 2 <= n, m <= 100
 * 1 <= k <= m
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<int> kWeakestRows(vector<vector<int>>& mat, int k) {
        int m = mat.size();
        int n = mat[0].size();
        vector<pair<int,int>> rows; // (soldier count, row index)
        
        for (int i = 0; i < m; ++i) {
            // Binary search for the first 0 (since row is sorted)
            int left = 0, right = n;
            while (left < right) {
                int mid = left + (right - left) / 2;
                if (mat[i][mid] == 0)
                    right = mid;
                else
                    left = mid + 1;
            }
            int strength = left; // number of 1's = index of first 0
            rows.emplace_back(strength, i);
        }
        
        // Sort by soldier count ascending, then by index ascending
        sort(rows.begin(), rows.end());
        
        // Take first k indices
        vector<int> result;
        for (int i = 0; i < k; ++i) {
            result.push_back(rows[i].second);
        }
        return result;
    }
};