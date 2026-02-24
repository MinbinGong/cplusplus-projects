/**
 * 858. Mirror Reflection
 * 
 * Example 1:
 * Input: p = 2, q = 1
 * Output: 2
 * Explanation: The ray meets receptor 2 the first time it gets reflected back to the left wall.
 * 
 * Example 2:
 * Input: p = 3, q = 1
 * Output: 1
 * 
 * Note:
 * 1 <= p <= 1000
 * 1 <= q <= 1000
 * 
 */
#include <numeric> // for gcd (C++17)

class Solution {
public:
    int mirrorReflection(int p, int q) {
        int g = std::gcd(p, q);
        int m = p / g; // 水平方向到达的格子数
        int n = q / g; // 垂直方向到达的格子数
        if (m % 2 == 1 && n % 2 == 1) return 2;
        if (m % 2 == 1 && n % 2 == 0) return 1;
        if (m % 2 == 0 && n % 2 == 1) return 3;
        return -1; // 不会执行
    }
};