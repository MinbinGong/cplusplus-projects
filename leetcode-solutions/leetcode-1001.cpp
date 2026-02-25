/*
 * 1001. Grid Illumination
 *
 * On a N x N grid of cells, each cell (x, y) with 0 <= x < N and 0 <= y < N has a lamp.
 *
 * Initially, some number of lamps are on.  lamps[i] tells us the location of the i-th lamp that is on.  Each lamp that is on illuminates every square on its x-axis, y-axis, and both diagonals (similar to a Queen in chess).
 *
 * For the i-th query queries[i] = (x, y), the answer to the query is 1 if the cell (x, y) is illuminated, else 0.
 *
 * After each query (x, y) [in the order given by queries], we turn off any lamps that are at cell (x, y) or are adjacent 8-directionally (ie., share a corner or edge with cell (x, y).)
 *
 * Return an array of answers.  Each value answer[i] should be equal to the answer of the i-th query queries[i].
 *
 * Example 1:
 * 
 * Input: N = 5, lamps = [[0,0],[4,4]], queries = [[1,1],[1,0]]
 * Output: [1,0]
 * Explanation: 
 * Before performing the first query we have both lamps [0,0] and [4,4] on.
 * The grid representing which cells are lit looks like this, where [0,0] is the top left corner, and [4,4] is the bottom right corner:
 * 1 1 1 1 1
 * 1 1 0 0 1
 * 1 0 1 0 1
 * 1 0 0 1 1
 * 1 1 1 1 1
 * Then the query at [1, 1] returns 1 because the cell is lit.  After this query, the lamp at [0, 0] turns off, and the grid now looks like this:
 * 1 0 0 0 1
 * 0 1 0 0 1
 * 0 0 1 0 1
 * 0 0 0 1 1
 * 
 * Example 2:
 * 
 * Input: N = 5, lamps = [[0,0],[4,4]], queries = [[1,1],[1,0]]
 * Output: [1,0]
 * Explanation: 
 * Before performing the first query we have both lamps [0,0] and [4,4] on.
 * The grid representing which cells are lit looks like this, where [0,0] is the top left corner, and [4,4] is the bottom right corner:
 * 1 1 1 1 1
 * 1 1 0 0 1
 * 1 0 1 0 1
 * 1 0 0 1 1
 * 1 1 1 1 1
 * Then the query at [1, 1] returns 1 because the cell is lit.  After this query, the lamp at [0, 0] turns off, and the grid now looks like this:
 * 1 0 0 0 1
 * 0 1 0 0 1
 * 0 0 1 0 1
 * 0 0 0 1 1
 * 
 * Example 3:
 * 
 * Input: N = 5, lamps = [[0,0],[4,4]], queries = [[1,1],[1,0]]
 * Output: [1,0]
 * Explanation: 
 * Before performing the first query we have both lamps [0,0] and [4,4] on.
 * The grid representing which cells are lit looks like this, where [0,0] is the top left corner, and [4,4] is the bottom right corner:
 * 1 1 1 1 1
 * 1 1 0 0 1
 * 1 0 1 0 1
 * 1 0 0 1 1
 * 1 1 1 1 1
 * Then the query at [1, 1] returns 1 because the cell is lit.  After this query, the lamp at [0, 0] turns off, and the grid now looks like this:
 * 1 0 0 0 1
 * 0 1 0 0 1
 * 0 0 1 0 1
 * 0 0 0 1 1
 * 
 * Note:
 * 
 * 1 <= N <= 10^9
 * 0 <= lamps.length <= 20000
 * 0 <= queries.length <= 20000
 * lamps[i].length == queries[i].length == 2
 * 0 <= lamps[i][j], queries[i][j] < N
 * 
 */
#include <vector>
#include <unordered_map>
#include <set>

using namespace std;

class Solution {
public:
    vector<int> gridIllumination(int N, vector<vector<int>>& lamps, vector<vector<int>>& queries) {
        unordered_map<int, int> rowCnt, colCnt, diag1Cnt, diag2Cnt;
        set<pair<int, int>> lampSet;

        // Add lamps, skip duplicates
        for (auto& l : lamps) {
            int r = l[0], c = l[1];
            if (lampSet.count({r, c})) continue;
            lampSet.insert({r, c});
            rowCnt[r]++;
            colCnt[c]++;
            diag1Cnt[r - c]++;   // diagonal from top-left to bottom-right
            diag2Cnt[r + c]++;   // diagonal from top-right to bottom-left
        }

        vector<int> ans;
        for (auto& q : queries) {
            int r = q[0], c = q[1];

            // Check if the cell is illuminated
            if (rowCnt[r] > 0 || colCnt[c] > 0 || diag1Cnt[r - c] > 0 || diag2Cnt[r + c] > 0)
                ans.push_back(1);
            else
                ans.push_back(0);

            // Turn off lamps in the 3x3 block centered at (r, c)
            for (int i = r - 1; i <= r + 1; ++i) {
                for (int j = c - 1; j <= c + 1; ++j) {
                    if (i < 0 || i >= N || j < 0 || j >= N) continue;
                    if (lampSet.count({i, j})) {
                        lampSet.erase({i, j});
                        rowCnt[i]--;
                        colCnt[j]--;
                        diag1Cnt[i - j]--;
                        diag2Cnt[i + j]--;
                    }
                }
            }
        }
        return ans;
    }
};