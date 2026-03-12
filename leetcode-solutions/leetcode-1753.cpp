/**
 * 1753. Maximum Score From Removing Stones
 * 
 * You have a collection of stones with positive integer weights.
 * 
 * In one turn, you can choose any two stones and smash them together.
 * Suppose the stones have weights x and y with x <= y. The result of this smash is:
 * 
 * If x == y, both stones are totally destroyed;
 * If x != y, the stone of weight x is totally destroyed, and the stone of weight y has new weight y - x.
 * 
 * At the end of the game, there is at most one stone left.
 * 
 * Return the largest possible weight of the last remaining stone.
 * If there are no stones left, return 0.
 * 
 * Example 1:
 * 
 * Input: a = 2, b = 4, c = 6
 * Output: 6
 * Explanation: The starting state is (2, 4, 6). One optimal set of moves is:
 * - Combine the two 2s to form a 4. State is now (4, 4, 6)
 * - Combine the two 4s to form a 6. State is now (6, 6)
 * - Combine the two 6s to form a 12. State is now (12)
 * 
 * Example 2:
 * 
 * Input: a = 4, b = 4, c = 6
 * Output: 6
 * Explanation: The starting state is (4, 4, 6). One optimal set of moves is:
 * - Combine the two 4s to form a 8. State is now (8, 6)
 * - Combine the two 6s to form a 12. State is now (12)
 * 
 * Example 3:
 * Input: a = 1, b = 8, c = 8
 * Output: 1
 * Explanation: The starting state is (1, 8, 8). One optimal set of moves is:
 * - Combine the two 1s to form a 2. State is now (2, 8, 8)
 * - Combine the two 8s to form a 16. State is now (16)
 * 
 * Constraints:
 * 1 <= a, b, c <= 10^5
 * 
 */

#include <algorithm>

class Solution {
public:
    int maximumScore(int a, int b, int c) {
        int total = a + b + c;
        int maxVal = std::max({a, b, c});
        int sumSmall = total - maxVal;
        return std::min(total / 2, sumSmall);
    }
};