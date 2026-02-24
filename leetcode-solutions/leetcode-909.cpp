/*
 * Snakes and Ladders
 * 
 * On an N x N board, the numbers from 1 to N*N are written boustrophedonically starting from the bottom left of the board,
 * and alternating direction each row.  For example, for a 6 x 6 board, the numbers are written as follows:
 * 
 * 36 35 34 33 32 31
 * 25 26 27 28 29 30
 * 24 23 22 21 20 19
 * 13 14 15 16 17 18
 * 12 11 10  9  8  7
 *  1  2  3  4  5  6
 * 
 * Example 1:
 * Input: [-1,-1,-1,-1,-1,-1], [6,5,4,3,2,1]
 * Output: 0
 * Explanation: 
 * The board is [-1,6,5,4,3,2,1].
 * The snakes and ladders are [-1,6,5,4,3,2,1].
 * The minimum number of moves is 0.
 * 
 * Example 2:
 * Input: [-1,-1,-1,-1,-1,-1], [-1,-1,-1,-1,-1,-1]
 * Output: -1
 * Explanation: 
 * The board is [-1,-1,-1,-1,-1,-1].
 * There are no snakes or ladders.
 * The minimum number of moves is -1.
 * 
 * Note:
 * 2 <= N <= 20
 * board.length == board[0].length == N*N
 * Each board[i][j] is distinct.
 * board[N-1][N-1] == -1.
 * 
 */
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    int snakesAndLadders(vector<vector<int>>& board) {
        int n = board.size();
        int target = n * n;
        vector<int> dist(target + 1, -1);
        queue<int> q;
        dist[1] = 0;
        q.push(1);

        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            if (curr == target) return dist[curr];

            for (int dice = 1; dice <= 6; ++dice) {
                int next = curr + dice;
                if (next > target) continue;

                // Convert square number to board coordinates
                int r = (next - 1) / n;          // row from bottom (0 = bottom row)
                int c = (next - 1) % n;
                if (r % 2 == 1) {                 // odd rows (from bottom) go right-to-left
                    c = n - 1 - c;
                }
                int actualRow = n - 1 - r;        // actual row in board (0 = top)
                int cell = board[actualRow][c];

                if (cell != -1) {
                    next = cell;                   // snake or ladder
                }

                if (dist[next] == -1) {
                    dist[next] = dist[curr] + 1;
                    q.push(next);
                }
            }
        }
        return -1;
    }
};