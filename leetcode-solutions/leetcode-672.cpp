/*
 * Bulb Switcher II
 *
 * There is a room with n bulbs, numbered from 1 to n, arranged in a row from left to right. Initially, all the bulbs
 * are turned off.
 *
 * At moment k (for k from 0 to n - 1), we turn on the light[k] bulb. A bulb change color to blue only if it is on and
 * all the previous bulbs (to the left) are turned on too.
 *
 * Return the number of moments in which all turned on bulbs are blue.
 *
 * Example 1:
 *
 * Input: light = [2,1,3,5,4]
 * Output: 3
 * Explanation: All bulbs turned on, are blue at the moment 1, 2, and 4.
 *
 * Example 2:
 *
 * Input: light = [3,2,4,1,5]
 * Output: 2
 * Explanation: All bulbs turned on, are blue at the moment 3, and 4 (index-0).
 *
 * Example 3:
 *
 * Input: light = [4,1,2,3]
 * Output: 1
 * Explanation: All bulbs turned on, are blue at the moment 4 (index-0).
 *
 * Note:
 *
 * The number of nodes in the given tree will be at most 10000.
 * Each node's value is an integer in the range [0, 10^9]. 
 *
 */
class Solution {
public:
    int flipLights(int n, int m) {
        // No presses: only the initial all-on state
        if (m == 0) return 1;
        // One bulb: can be on or off for any m >= 1
        if (n == 1) return 2;
        // Two bulbs: possible states depend on m
        if (n == 2) return (m == 1) ? 3 : 4;
        // Three or more bulbs:
        if (m == 1) return 4;
        if (m == 2) return 7;
        return 8;
    }
};