/*
 * 1033. Moving Stones Until Consecutive
 *
 * Three stones are on a number line at positions a, b, and c.
 *
 * Each turn, you pick up a stone at an endpoint (ie., either the lowest or highest position stone), and move it to an unoccupied position between those endpoints.  Formally, let's say the stones are currently at positions x, y, z with x < y < z.  You pick up the stone at either position x or position z, and move that stone to an integer position k, with x < k < z and k != y.
 *
 * The game ends when you cannot make any more moves, ie. the stones are in consecutive positions.
 *
 * When the game ends, what is the minimum and maximum number of moves that you could have made?  Return the answer as an length 2 array: answer = [minimum_moves, maximum_moves]
 * 
 * Example 1:
 *
 * Input: a = 1, b = 2, c = 5
 * Output: [1,2]
 * Explanation: Move the stone from 5 to 3, or move the stone from 5 to 4 to 3.
 * 
 * Example 2:
 *
 * Input: a = 4, b = 3, c = 2
 * Output: [0,0]
 * Explanation: We cannot make any moves.
 * 
 * Example 3:
 *
 * Input: a = 3, b = 5, c = 1
 * Output: [1,2]
 * Explanation: Move the stone from 1 to 4; or move the stone from 1 to 2 to 4.
 * 
 * Note:
 * 1 <= a <= 100
 * 1 <= b <= 100
 * 1 <= c <= 100
 * a != b, b != c, c != a
 * 
 */
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> numMovesStones(int a, int b, int c) {
        vector<int> stones = {a, b, c};
        sort(stones.begin(), stones.end());
        int x = stones[0], y = stones[1], z = stones[2];

        // Maximum moves: each empty slot between x and z can be filled one by one
        int maxMoves = (z - x) - 2;

        // Minimum moves
        int minMoves;
        if (z - x == 2) {               // already consecutive
            minMoves = 0;
        } else if (y - x <= 2 || z - y <= 2) {
            minMoves = 1;                // can fill a gap of size 1 or 2 in one move
        } else {
            minMoves = 2;                // otherwise need two moves
        }

        return {minMoves, maxMoves};
    }
};