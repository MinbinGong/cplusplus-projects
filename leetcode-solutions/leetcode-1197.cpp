/*
 * 1197. Minimum Knight Moves
 *
 * In an infinite chess board with coordinates from -infinity to +infinity, you have a knight at square [0, 0].
 * 
 * A knight has 8 possible moves it can make, as illustrated below. Each move is two squares in a cardinal direction, then one square in an orthogonal direction.
 * 
 * Return the minimum number of steps needed to move the knight to the square [x, y].  It is guaranteed the answer exists.
 * 
 * Example 1:
 * Input: x = 2, y = 1
 * Output: 1
 * Explanation: [0, 0] → [2, 1]
 * 
 * Example 2:
 * Input: x = 5, y = 5
 * Output: 4
 * Explanation: [0, 0] → [2, 1] → [4, 2] → [3, 4] → [5, 5]
 * 
 * Note:
 * |x| + |y| <= 300
 * 
 */
#include <cmath>
#include <algorithm>
using namespace std;

class Solution {
public:
    int minKnightMoves(int x, int y) {
        // 利用对称性，只考虑第一象限，并保证 x >= y
        x = abs(x);
        y = abs(y);
        if (x < y) swap(x, y);
        
        // 处理两个特殊边界情况
        if (x == 1 && y == 0) return 3;
        if (x == 2 && y == 2) return 4;
        
        // 贪心公式：取两种下界的最大值，并调整奇偶性
        int d = max((x + 1) / 2, (x + y + 2) / 3);
        if ((d % 2) != ((x + y) % 2)) d++;
        return d;
    }
};