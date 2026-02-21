/*
 * leetcode-365: Water and Jug Problem
 *
 * You are given two jugs with capacities jug1Capacity and jug2Capacity liters.
 * There is an infinite amount of water supply available.
 * Determine whether it is possible to measure exactly targetCapacity liters using these two jugs.
 * 
 * If targetCapacity liters of water are measurable, you must have targetCapacity liters of water contained within one or both buckets by the end.
 * 
 * Operations allowed:
 * 
 * Fill any of the jugs with water.
 * Empty any of the jugs.
 * Pour water from one jug into another till the other jug is completely full, or the first jug itself is empty.
 * 
 * Example 1:
 * Input: jug1Capacity = 3, jug2Capacity = 5, targetCapacity = 4
 * Output: true
 * Explanation: The famous Die Hard example 
 * 
 * Example 2:
 * Input: jug1Capacity = 2, jug2Capacity = 6, targetCapacity = 5
 * Output: false
 * 
 * Example 3:
 * Input: jug1Capacity = 1, jug2Capacity = 2, targetCapacity = 3
 * Output: true
 * 
 * Constraints:
 * 1 <= jug1Capacity, jug2Capacity, targetCapacity <= 106
 * 
 */
#include <numeric> // for std::gcd (C++17)
class Solution {
public:
    bool canMeasureWater(int x, int y, int z) {
        // 特殊情况：z == 0 总是可行的（两个空壶）
        if (z == 0) return true;
        // 如果总容量小于 z，不可能量出
        if (x + y < z) return false;
        // 贝祖定理：z 必须是 x 和 y 的最大公约数的倍数
        return z % std::gcd(x, y) == 0;
    }
};